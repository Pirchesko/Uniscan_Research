#include "pch.h"
#include "../PacketQueue.h"
#include "../Packet.h"
#include "../Packet.cpp"

#define MAX_PACKET_SIZE 128
#define MAX_PACKET_COUNT 10
#define MAX_QUEUE_SIZE (MAX_PACKET_SIZE * MAX_PACKET_COUNT)

//--------------- Push ---------------

// Тест: успешное добавления пакета
TEST(PacketQueueTestPush, PushSuccess) {
    PacketQueue<MAX_PACKET_SIZE, MAX_PACKET_COUNT, MAX_QUEUE_SIZE> queue;

    unsigned char data[100] = { 0 };
    EXPECT_TRUE(queue.Push(data, 100, 1));
}

// Тест: превышение максимальной длины пакета
TEST(PacketQueueTestPush, PushPacketIsLarge) {
    PacketQueue<MAX_PACKET_SIZE, MAX_PACKET_COUNT, MAX_QUEUE_SIZE> queue;

    unsigned char data[MAX_PACKET_SIZE * 2] = { 0 };
    EXPECT_FALSE(queue.Push(data, MAX_PACKET_SIZE * 2, 1));
}

// Тест: превышение числа пакетов в очереди
TEST(PacketQueueTestPush, PushMorePackets) {
    const unsigned int MaxPacketCount = MAX_PACKET_COUNT / 2;
    PacketQueue<MAX_PACKET_SIZE, MaxPacketCount, MAX_QUEUE_SIZE> queue;

    unsigned char data[10] = { 0 };
    for (unsigned int i = 0; i < MaxPacketCount; ++i) {
        EXPECT_TRUE(queue.Push(data, 10, i));
    }

    EXPECT_FALSE(queue.Push(data, 10, MaxPacketCount));
}

// Тест: превышение общего размера очереди
TEST(PacketQueueTestPush, PushQueueIsLarge) {
    const unsigned int MaxQueueSize = 50;
    PacketQueue<MAX_PACKET_SIZE, MAX_PACKET_COUNT, MaxQueueSize> queue;

    unsigned char data1[30] = { 0 };
    unsigned char data2[30] = { 0 };

    EXPECT_TRUE(queue.Push(data1, 30, 1));
    EXPECT_FALSE(queue.Push(data2, 30, 2));
}

//--------------- Pop ---------------

// Тест: успешное извлечения пакета
TEST(PacketQueueTestPop, PopSuccess) {
    PacketQueue<MAX_PACKET_SIZE, MAX_PACKET_COUNT, MAX_QUEUE_SIZE> queue;

    unsigned char data[100] = { 0 };
    queue.Push(data, 100, 1);

    unsigned char buffer[100] = { 0 };
    unsigned int dataCount = 0;
    unsigned int packetId = 0;
    EXPECT_TRUE(queue.Pop(buffer, 100, dataCount, packetId));
}

// Тест: попытка извлечения из пустой очереди
TEST(PacketQueueTestPop, PopEmptyQueue) {
    PacketQueue<MAX_PACKET_SIZE, MAX_PACKET_COUNT, MAX_QUEUE_SIZE> queue;

    unsigned char buffer[100] = { 0 };
    unsigned int dataCount = 0;
    unsigned int packetId = 0;
    EXPECT_FALSE(queue.Pop(buffer, 100, dataCount, packetId));
}

// Тест: потеря данных при слишком маленьком буфере
TEST(PacketQueueTestPop, PopBufferIsSmall) {
    PacketQueue<MAX_PACKET_SIZE, MAX_PACKET_COUNT, MAX_QUEUE_SIZE> queue;

    unsigned char data[100] = { 0 };
    queue.Push(data, 100, 1);

    unsigned char smallBuffer[50] = { 0 };
    unsigned int dataCount = 0;
    unsigned int packetId = 0;
    EXPECT_TRUE(queue.Pop(smallBuffer, 50, dataCount, packetId));
    EXPECT_EQ(dataCount, 50);
}

// Основная функция запуска тестов Google Test
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
