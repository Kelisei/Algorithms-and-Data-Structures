#ifndef BROADCAST_CHANNEL_TPP
#define BROADCAST_CHANNEL_TPP

#include <mutex>
#include <condition_variable>

#include <optional>
#include <stdexcept>

template <typename T>
class BroadcastChannelNode
{
public:
    BroadcastChannelNode(const T &value, size_t lifes) : value(value), lifes(lifes), next(nullptr) {}
    ~BroadcastChannelNode() = default;

    T getValue() const { return value; }
    size_t getLifes() const { return lifes; }
    BroadcastChannelNode *getNext() const { return next; }
    void setNext(BroadcastChannelNode *next) { this->next = next; }
    void decreaseLifes() { lifes--; }
    bool shouldDelete() const { return lifes == 0; }

private:
    T value;
    size_t lifes;
    BroadcastChannelNode *next;
};

template <typename T>
class BroadcastChannel
{
public:
    BroadcastChannel() : head(nullptr), tail(nullptr), size(0), closed(false) {}
    ~BroadcastChannel() { clear(); }

    void broadcast(const T &value, size_t lifes)
    {
        std::lock_guard<std::mutex> lock(channelMutex);
        push(value, lifes);
        conditionVariable.notify_all();
    }

    void send(const T &value)
    {
        std::lock_guard<std::mutex> lock(channelMutex);
        push(value, 1);
        conditionVariable.notify_one();
    }

    std::optional<T> receive()
    {
        std::unique_lock<std::mutex> lock(channelMutex);
        conditionVariable.wait(lock, [this]
                               { return head != nullptr || closed; });
        if (closed && head == nullptr)
        {
            return std::nullopt;
        }
        return pop();
    }

    void close()
    {
        std::lock_guard<std::mutex> lock(channelMutex);
        closed = true;
        conditionVariable.notify_all();
    }

    bool isEmpty() const
    {
        std::lock_guard<std::mutex> lock(channelMutex);
        return head == nullptr;
    }

    size_t getSize() const
    {
        std::lock_guard<std::mutex> lock(channelMutex);
        return size;
    }

    bool isClosed() const
    {
        std::lock_guard<std::mutex> lock(channelMutex);
        return closed;
    }

private:
    mutable std::mutex channelMutex;
    std::condition_variable conditionVariable;
    BroadcastChannelNode<T> *head;
    BroadcastChannelNode<T> *tail;
    size_t size;
    bool closed;

    void push(const T &value, size_t lifes)
    {
        size++;
        auto newNode = new BroadcastChannelNode<T>(value, lifes);
        if (tail == nullptr)
        {
            head = tail = newNode;
        }
        else
        {
            tail->setNext(newNode);
            tail = newNode;
        }
    }

    std::optional<T> pop()
    {
        if (head == nullptr)
        {
            return std::nullopt;
        }
        auto temp = head;
        temp->decreaseLifes();
        auto value = temp->getValue();
        if (temp->shouldDelete())
        {
            size--;
            head = head->getNext();
            if (head == nullptr)
            {
                tail = nullptr;
            }
            delete temp;
        }
        return value;
    }

    void clear()
    {
        while (head != nullptr)
        {
            auto temp = head;
            head = head->getNext();
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }
};

#include "broadcast_channel.tpp"

#endif // CHANNEL_TPP