#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include "queue.hpp"
#include <mutex>

template <typename T>
class Channel
{
private:
    Queue<T> queue;
    std::mutex mtx;
    std::condition_variable channelHasSpace;
    std::condition_variable channelHasData;
    size_t maxSize;
    size_t size;
    
public:
    Channel(size_t maxSize) : mtx(), queue(), maxSize(maxSize), size(0) {};
    Channel() : mtx(), queue(), maxSize(-1), size(0) {};
    ~Channel();
    bool send(T data);
    std::optional<T> receive();
    void close();
    void clear();
    bool isEmpty();
};

#endif