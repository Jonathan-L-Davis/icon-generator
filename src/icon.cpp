#include "icon.h"
#include "util/util.h"

#include <iostream>

// should only work for the correct type of png file, and silently fail otherwise. May be missing some mask data for the icons.
bool save_file(std::string file,ICONDIR ico){
    
    std::vector<uint8_t> saveMe;
    
    uint32_t total_size = 6+16*ico.DIRS.size();
    
    for(ICONDIRENTRY d:ico.DIRS) total_size += d.img_data.size();
    
    try{
        saveMe.reserve(total_size);
    }catch(const std::bad_alloc& e){
        std::cout << "Failed to allocate memory while generating output file.\nExiting...\n";// bad times are here.
    }
    
    ico.idCount = ico.DIRS.size();
    
    // write header to buffer.
    saveMe.push_back(ico.idReserved);
    saveMe.push_back(ico.idReserved>>8);
    saveMe.push_back(ico.idType);
    saveMe.push_back(ico.idType>>8);
    saveMe.push_back(ico.idCount);
    saveMe.push_back(ico.idCount>>8);
    
    uint32_t offset = 6+16*ico.DIRS.size();
    
    // save each dir entry
    for(ICONDIRENTRY& dir: ico.DIRS){
        saveMe.push_back(dir.bWidth);
        saveMe.push_back(dir.bHeight);
        saveMe.push_back(dir.bColorCount);
        saveMe.push_back(dir.bReserved);
        saveMe.push_back(dir.wPlanes);
        saveMe.push_back(dir.wPlanes>>8);
        saveMe.push_back(dir.wBitCount);
        saveMe.push_back(dir.wBitCount>>8);
        saveMe.push_back(dir.dwBytesInRes);
        saveMe.push_back(dir.dwBytesInRes>>8);
        saveMe.push_back(dir.dwBytesInRes>>16);
        saveMe.push_back(dir.dwBytesInRes>>24);
        
        // ignore what's in the struct since we're rewriting the file.
        saveMe.push_back(offset);
        saveMe.push_back(offset>>8);
        saveMe.push_back(offset>>16);
        saveMe.push_back(offset>>24);
        
        offset += dir.img_data.size();// this is wrong if I need to include extra mask data.
    }
    
    // save image data
    // I expect this to fail since I am skipping generating the masks.
    for(const ICONDIRENTRY& dir: ico.DIRS){// technically we could write these in any order, but it's expected to be written in the order they are entered in the dirs.
        saveMe.insert(saveMe.end(),dir.img_data.begin(),dir.img_data.end());
    }
    return save_file(file,saveMe);
}

