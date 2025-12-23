#pragma once

#include <cstdint>
#include <string>
#include <vector>

// things are bad when I'm using windows naming conventions. Forgive me future self.

struct ICONDIRENTRY{
    uint8_t bWidth;
    uint8_t bHeight;
    uint8_t bColorCount;
    uint8_t bReserved = 0;
    uint16_t wPlanes;// fk if I know what this is. Layers?
    uint16_t wBitCount;
    uint32_t dwBytesInRes;// image size in bytes.
    uint32_t dwImageOffset;
    std::vector<uint8_t> img_data;
};

struct ICONDIR{
    uint16_t idReserved = 0;
    uint16_t idType = 1;// means ICO format. We are ignoring CUR format.
    uint16_t idCount = 0;
    std::vector<ICONDIRENTRY> DIRS;
};

bool save_file(std::string file,ICONDIR ico);
