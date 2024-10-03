#include "Packet.h"
#include <cstring>

Packet::Packet(unsigned char* dataInput, unsigned int dataSize, unsigned int packetId)
    : size(dataSize), id(packetId)
{
    data = new unsigned char[size];
    memcpy(data, dataInput, size);
}   