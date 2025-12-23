#include "util/util.h"
#include "icon.h"

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

// ignores stack overflows (we are so shallow on the stack) but should otherwise be pretty darned robust against errors.
int main(int argc, char** argv){
    
    std::vector<std::string> args;
    
    try{
        for( int i = 0; i < argc; i++) args.push_back(argv[i]);// unnecessary, but also fuck you bill gates. Give me a damned vector for my args by default.
    }catch(...){
        std::cout << "Failed to allocate memory for the argument strings. You have issues...\n";
    }
    
    int width = 0;
    int height = 0;
    std::string output_file;
    
    ICONDIR ico_file;
    
    for( int i = 0; i < args.size(); i++ ){// can't use a for each because I want to skip over 2 args at a time and I'm not willing to add an extra state variable. (I guess 'i' is a state var, but ehh).
        std::string arg = args[i];
        std::cout << "args[" << i << "] = " << arg << "\n";
        
        if(arg == "-o"){
            i++;
            try{
                arg = args[i];
                output_file = arg;
            }catch(const std::bad_alloc& e){
                std::cout << "Failed to allocate memory while parsing args.\nExiting...\n";// bad times are here.
            }
            continue;
        }
        
        if(arg == "-w"){
            i++;
            if(i>=args.size())break;
            arg = args[i];
            try{
                width = std::stoi(arg);// not perfect. '123abcxyz' converts to 123. Don't care enough.
            }catch(...){
                std::cout << "Failed to convert width argument " << arg << " in position " << i << " to an integer.\nExiting...\n";
                std::exit(-1);
            }
            continue;
        }
        
        if(arg == "-h"){
            i++;
            if(i>=args.size())break;
            arg = args[i];
            try{
                height = std::stoi(arg);// not perfect. '123abcxyz' converts to 123. Don't care enough.
            }catch(...){
                std::cout << "Failed to convert height argument " << arg << " in position " << i << " to an integer.\nExiting...\n";
                std::exit(-1);
            }
            continue;
        }
        
        if(arg == "-f"){
            i++;
            
            if(i>=args.size())break;
            arg = args[i];
            
            try{
                
                if( !std::filesystem::exists(arg)){
                    std::cout << "File '" << arg << "' does not exist.\n";
                    std::exit(-1);
                }
                
                if( arg.size()<4 || arg.substr(arg.size()-4)!=".png"){
                    std::cout << "File '" << arg << "' is not a png.\n";
                    std::exit(-1);
                }
                
                ICONDIRENTRY dir;
                dir.img_data = load_file(arg);
                dir.bWidth = width;
                dir.bHeight = height;
                dir.dwBytesInRes = dir.img_data.size();
                std::cout << dir.dwBytesInRes << "\n";
                ico_file.DIRS.push_back(dir);
            }catch(const std::bad_alloc& e){
                std::cout << "Failed to allocate memory while loading a file.\nExiting...\n";// bad times are here.
            }catch(...){
                std::cout << "File " << arg << " either does not exist, or does not have read permissions.\nExiting...\n";
                std::exit(-1);
            }
            continue;
        }
        
    }
    
    if(!save_file(output_file,ico_file)){
        std::cout << "Failed to write output file.\n";
        std::exit(-1);
    }
    
    return 0;
}
