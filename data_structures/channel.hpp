#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <mutex>
#include <condition_variable>
#include <optional>
#include <stdexcept>

template <typename T>
class BroadcastChannelNode
{
public:
    BroadcastChannelNode(const T &value, size_t lifes);
    ~BroadcastChannelNode();

    T getValue() const;
    size_t getLifes() const;
    BroadcastChannelNode *getNext() const;
    void setNext(BroadcastChannelNode *next);
    void decreaseLifes();
    bool shouldDelete() const;

private:
    T value;
    size_t lifes;
    BroadcastChannelNode *next;
};

template <typename T>
class BroadcastChannel
{
public:
    BroadcastChannel();
    ~BroadcastChannel();

    void broadcast(const T &value, size_t lifes);
    void send(const T &value);
    std::optional<T> receive();
    void close();
    bool isEmpty() const;
    size_t getSize() const;
    bool isClosed() const;

private:
    std::mutex channelMutex;
    std::condition_variable conditionVariable;
    BroadcastChannelNode<T> *head;
    BroadcastChannelNode<T> *tail;
    size_t size;
    bool closed;

    void push(const T &value, size_t lifes);
    std::optional<T> pop();
    void clear();
};

#include "channel.tpp"

#endif // CHANNEL_HPP