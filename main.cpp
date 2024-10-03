#include <iostream>
#include "PacketQueue.h"

using namespace std;

int main()
{
    const unsigned int MaxPacketSize = 128; // максимальный размер пакета
    const unsigned int MaxPacketCount = 10; // максимальное число пакетов
    const unsigned int MaxQueueSize = MaxPacketSize * MaxPacketCount; // максимальный размер всех пакетов в очереди

    PacketQueue<MaxPacketSize, MaxPacketCount, MaxQueueSize> queue;

    unsigned char data[100] = { 0 }; 
    queue.Push(data, 100, 1);
    queue.Push(data, 100, 4);
    queue.Push(data, 100, 2);

    unsigned char buffer[100] = { 0 };
    unsigned int dataCount;
    unsigned int packetId;
    queue.Pop(buffer, 100, dataCount, packetId);
    cout << packetId << endl;
    queue.Pop(buffer, 100, dataCount, packetId);
    cout << packetId << endl;
    queue.Pop(buffer, 100, dataCount, packetId);
    cout << packetId << endl;

    return 0;
}