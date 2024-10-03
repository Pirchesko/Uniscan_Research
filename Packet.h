#pragma once

class Packet {
public:
    unsigned char* data;
    unsigned int size;
    unsigned int id;

    Packet(unsigned char* dataInput, unsigned int dataSize, unsigned int packetId);
};