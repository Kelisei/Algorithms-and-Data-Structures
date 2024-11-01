#include <gtest/gtest.h>
#include "channel.tpp"

TEST(BroadcastChannelTest, BroadcastAndReceive)
{
    BroadcastChannel<int> channel;
    channel.broadcast(42, 2);

    auto value1 = channel.receive();
    ASSERT_TRUE(value1.has_value());
    EXPECT_EQ(value1.value(), 42);

    auto value2 = channel.receive();
    ASSERT_TRUE(value2.has_value());
    EXPECT_EQ(value2.value(), 42);
    ASSERT_TRUE(channel.isEmpty());
}

TEST(BroadcastChannelTest, SendAndReceive)
{
    BroadcastChannel<int> channel;
    channel.send(42);

    auto value = channel.receive();
    ASSERT_TRUE(value.has_value());
    EXPECT_EQ(value.value(), 42);

    ASSERT_TRUE(channel.isEmpty());
}

TEST(BroadcastChannelTest, CloseChannel)
{
    BroadcastChannel<int> channel;
    channel.send(42);
    channel.close();

    auto value = channel.receive();
    ASSERT_TRUE(value.has_value());
    EXPECT_EQ(value.value(), 42);

    auto noValue = channel.receive();
    ASSERT_FALSE(noValue.has_value());
}

TEST(BroadcastChannelTest, EmptyChannel)
{
    BroadcastChannel<int> channel;
    EXPECT_TRUE(channel.isEmpty());

    channel.send(42);
    EXPECT_FALSE(channel.isEmpty());

    channel.receive();
    EXPECT_TRUE(channel.isEmpty());
}

TEST(BroadcastChannelTest, ChannelSize)
{
    BroadcastChannel<int> channel;
    EXPECT_EQ(channel.getSize(), 0);

    channel.send(42);
    EXPECT_EQ(channel.getSize(), 1);

    channel.receive();
    EXPECT_EQ(channel.getSize(), 0);
}

TEST(BroadcastChannelTest, IsClosed)
{
    BroadcastChannel<int> channel;
    EXPECT_FALSE(channel.isClosed());

    channel.close();
    EXPECT_TRUE(channel.isClosed());
}
#include <thread>
#include <vector>

TEST(BroadcastChannelTest, ConcurrentSendAndReceive)
{
    BroadcastChannel<int> channel;
    const int numThreads = 10;
    const int numMessages = 100;

    // Sender threads
    std::vector<std::thread> senders;
    for (int i = 0; i < numThreads; ++i) {
        senders.emplace_back([&channel, numMessages, i]() {
            for (int j = 0; j < numMessages; ++j) {
                channel.send(i * numMessages + j);
            }
        });
    }

    // Receiver threads
    std::vector<std::thread> receivers;
    std::vector<int> receivedMessages;
    std::mutex mtx;
    for (int i = 0; i < numThreads; ++i) {
        receivers.emplace_back([&channel, &receivedMessages, &mtx, numMessages]() {
            for (int j = 0; j < numMessages; ++j) {
                auto value = channel.receive();
                if (value.has_value()) {
                    std::lock_guard<std::mutex> lock(mtx);
                    receivedMessages.push_back(value.value());
                }
            }
        });
    }

    // Join all threads
    for (auto& sender : senders) {
        sender.join();
    }
    for (auto& receiver : receivers) {
        receiver.join();
    }

    // Check if all messages were received
    EXPECT_EQ(receivedMessages.size(), numThreads * numMessages);
    std::sort(receivedMessages.begin(), receivedMessages.end());
    for (int i = 0; i < numThreads * numMessages; ++i) {
        EXPECT_EQ(receivedMessages[i], i);
    }
}
