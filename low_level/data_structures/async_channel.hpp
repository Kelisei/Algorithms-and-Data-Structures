#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <optional>

/*
* @class AsyncChannel
* @brief An asynchronous channel interface.
*
* @tparam T The type of elements stored in the channel.
*/
template <typename T>
class AsyncChannel
{
public:
    virtual ~AsyncChannel() = default;
    virtual void send(const T &value) = 0;
    virtual std::optional<T> receive() = 0;
    virtual void close() = 0;
    virtual bool isEmpty() const = 0;
    virtual size_t getSize() const = 0;
    virtual bool isClosed() const = 0;
};

#endif // CHANNEL_HPP