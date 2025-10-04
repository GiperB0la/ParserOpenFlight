#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdint>
#include <iomanip>
#include "OpenFlightRecords.hpp"

inline uint16_t swap16(uint16_t v) {
    return (v >> 8) | (v << 8);
}

inline uint32_t swap32(uint32_t v) {
    return ((v >> 24) & 0x000000FF) |
        ((v >> 8) & 0x0000FF00) |
        ((v << 8) & 0x00FF0000) |
        ((v << 24) & 0xFF000000);
}

class ParserOpenFlight
{
public:
    static void parse_records(std::ifstream& file, int depth = 0);
};