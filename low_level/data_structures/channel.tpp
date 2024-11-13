#ifndef CHANNEL_TPP
#define CHANNEL_TPP

#include "channel.hpp"

template <typename T>
Channel<T>::~Channel()
{
    clear();
}

template <typename T>
bool Channel<T>::send(T data)
{
    std::unique_lock<std::mutex> lock(this->mtx);
    this->channelHasSpace.wait(lock, [this]
                               { return this->maxSize == -1 || this->size < this->maxSize; });
    this->queue.enqueue(data);
    this->size++;
    lock.unlock();
    this->channelHasData.notify_one();
    return true;
};
template <typename T>
std::optional<T> Channel<T>::receive()
{
    std::unique_lock<std::mutex> lock(this->mtx);
    this->channelHasData.wait(lock, [this]
                              { return this->size > 0; });
    T data = this->queue.dequeue();
    this->size--;
    lock.unlock();
    this->channelHasSpace.notify_one();
    return data;
}
template <typename T>
void Channel<T>::close()
{
    this->maxSize = 0;
    this->channelHasSpace.notify_all();
    this->channelHasData.notify_all();
}
template <typename T>
void Channel<T>::clear()
{
    delete this->queue;
    this->size = 0;
}
template <typename T>
bool Channel<T>::isEmpty()
{
    return this->size == 0;
}
#endif