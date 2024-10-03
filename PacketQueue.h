#pragma once

#include <iostream>
#include <queue>
#include "Packet.h"

using namespace std;

// MaxLength - максимальная длина одного пакета
// MaxCount - максимальное число пакетов в очереди
// MaxQueueSize - максимальный размер всей очереди пакетов
template <unsigned int MaxLength, unsigned int MaxCount, unsigned int MaxQueueSize>
class PacketQueue {
private:
    unsigned int currentSize;
    std::queue<Packet> queue;

public:
    PacketQueue() : currentSize(0) {}
    ~PacketQueue() {
        while (queue.size() > 0) {
            Packet packet = queue.front();
            delete[] packet.data;
            queue.pop();
        }
    }

    // Поместить пакет в очередь
    // data - содержимое пакета
    // dataCount - длина пакета в байтах
    // packetId - идентификатор пакета
    // return - результат постановки пакета в очередь:
    // true - пакет помещен в очередь
    // false - длина пакета превышает максимально допустимую, число пакетов в очереди или 
    // суммарный размер пакетов в очереди превысили максимально допустимые
    bool Push(unsigned char* data, unsigned int dataCount, unsigned int packetId) {
        if (dataCount > MaxLength) {
            cout << "Packet size is more than maximum: " << dataCount << " > " << MaxLength << endl;
            return false;
        }

        if (queue.size() >= MaxCount) {
            cout << "The number of packets in queue is maximum: " << MaxCount << endl;
            return false;
        }

        if (currentSize + dataCount > MaxQueueSize) {
            cout << "Exceeded the maximum size limit: " << currentSize + dataCount << " > " << MaxQueueSize << endl;
            return false;
        }

        Packet packet(data, dataCount, packetId);
        queue.push(packet);
        currentSize += dataCount;

        return true;
    }

    // Извлечь пакет из очереди
    // buffer - при емный буфер, куда помещаются данные извлеченные из очереди
    // bufferSize - размер приемного буфера
    // dataCount - фактический размер пакета, извлеченного из очереди
    // packetId - идентификатор пакета, извлеченного из очереди
    // return - результат извлечения пакета из очереди:
    // true - пакет извлечен и помещен в буфер (в том числе, если размер пакета превысил 
    // размер приемного буфера)
    // false - очередь пуста
    bool Pop(unsigned char* buffer, unsigned int bufferSize, unsigned int& dataCount, unsigned int& packetId) {
        if (queue.size() == 0) {
            cout << "Queue is empty" << endl;
            return false;
        }

        Packet packet = queue.front();
        queue.pop();
        currentSize -= packet.size;

        if (bufferSize < packet.size) {
            cout << "Warning! Data loss: Packet size exceeds the size of the receiving buffer!" << endl;
        }

        unsigned int bufferOutput = min(bufferSize, packet.size);
        memcpy(buffer, packet.data, bufferOutput);
        packetId = packet.id;
        dataCount = bufferOutput;
        delete[] packet.data;

        return true;
    }
};