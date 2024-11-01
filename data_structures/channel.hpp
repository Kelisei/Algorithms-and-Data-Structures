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

/*
* @class BroadcastChannel
* @brief An asynchronous broadcast channel implementation where messages have "lifes," allowing multiple readings.
*
* @tparam T The type of elements stored in the channel.
*/
template <typename T>
class BroadcastChannel
{
public:
    BroadcastChannel();
    ~BroadcastChannel();
    /*
    * @brief This method broadcasts a value to the number of receivers specified by the lifes parameter.
    * 
    * @param value The value to be broadcasted.
    * @param lifes The number of receivers that will receive the value.
    */
    void broadcast(const T &value, size_t lifes);
    /*
    * @brief This method sends a value to a single receiver.
    *
    * @param value The value to be sent.
    */
    void send(const T &value);
    /*
    * @brief BLOCKING! This method attempts to receive a value from the channel. If the channel is empty but not closed, it will block until a value is available. If the channel is closed and empty, it returns std::nullopt.
    *
    * @return An optional containing the value if the channel is not closed, otherwise std::nullopt.
    */
    std::optional<T> receive();
    /*
    * @brief This method closes the channel, making it impossible to send more values.
    */
    void close();
    /*
    * @brief This method checks if the channel is empty.
    */
    bool isEmpty() const;
    /*
    * @brief This method returns the number of values in the channel.
    */
    size_t getSize() const;
    /*
    * @brief This method checks if the channel is closed.
    */
    bool isClosed() const;

private:
    std::mutex channelMutex;
    std::condition_variable conditionVariable;
    BroadcastChannelNode<T> *head;
    BroadcastChannelNode<T> *tail;
    size_t size;
    bool closed;
    /*
    * @brief This method pushes a value to the channel.
    *
    * @param value The value to be pushed.
    * @param lifes The number of receivers that will receive the value.
    */
    void push(const T &value, size_t lifes);
    /*
    * @brief This method pops a value from the channel.
    *
    * @return An optional containing the value if the channel is not empty, otherwise an empty optional.
    */
    std::optional<T> pop();
    /*
    * @brief This method clears the channel.
    */
    void clear();
};

#include "channel.tpp"

#endif // CHANNEL_HPP