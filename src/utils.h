/*
* some utils
*
*/
#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <cstdio>
#include <cstdarg>
#include <ctime>
#include <cstring>
#include <fstream>
#include <sstream>
#include <chrono>
#include <random>
#include <algorithm>

//log
extern bool log_to_file;
extern std::string log_dir_prefix;
extern std::ofstream log_stream;

inline std::ostream& get_stream(){
    if (log_to_file){
        if(!log_stream.is_open()){
            std::string path = log_dir_prefix + "tool.log";
            log_stream.open(path, std::ios_base::out | std::ios_base::app);
        }
        return log_stream;
    }
    return std::cout;
}

inline std::ostream& log(const char *level){
    std::time_t t = std::time(nullptr);
    char buf[100];
    std::strftime(buf, 100, "%Y-%m-%d %H:%M:%S", std::localtime(&t));
    return get_stream()<<buf<<" ["<<level<<"] ";
}

inline std::string get_err(int err){
    std::stringstream ss;
    ss<<"("<<err<<") "<<strerror(err);
    return ss.str();
}

//sleep 1 sec
//std::this_thread::sleep_for(std::chrono::seconds(1));
class timer{
    std::chrono::time_point<std::chrono::system_clock> start,end;
public:
    timer(){
         start = std::chrono::system_clock::now();
         //std::chrono::high_resolution_clock::now()
    }
    void reset(){
        start = std::chrono::system_clock::now();
    }
    size_t elapsed(){
        end = std::chrono::system_clock::now();
        auto elp = std::chrono::duration_cast<std::chrono::milliseconds>(end-start);
        return elp.count();
    }
    bool reach(std::chrono::seconds duration){
        return std::chrono::system_clock::now() - start >= duration;
    }
};

class random_generator{
    std::default_random_engine generator;
public:
    random_generator(){
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        generator.seed(seed);
    }
    template<typename T>
    T next(T lower,T upper){
        std::uniform_int_distribution<T> distribution(lower,upper);
        return distribution(generator);
    }
};

inline uint64_t parse_obj_size(const char * arg){
    uint64_t base = std::atoi(arg);
    char unit = arg[strlen(arg)-1];
    if(std::isalpha(unit)){
        unit = std::tolower(unit);
        if(unit=='t') base *= 1024*1024*1024*1024ul;
        else if(unit=='g') base *= 1024*1024*1024ul;
        else if(unit=='m') base *= 1024*1024;
        else if(unit=='k') base *= 1024;
    }
    return base;
}

inline size_t parse_obj_size(const std::string& arg){
    return parse_obj_size(arg.c_str());
}

inline bool mkTempFile(const char* path, size_t size, random_generator& rg){
    std::ofstream os(path);
    if(!os){
        return false;
    }
    const size_t bs = 1024;
    char buf[bs];
    //random content
    for(size_t i=0; i<bs; ++i){
        buf[i] = rg.next<int>(0,25)+'a';
    }
    size_t write_bytes = 0, cur = 0;
    while(true){
        cur = std::min(size-write_bytes, bs);
        os.write(buf, cur);
        write_bytes += cur;
        if(write_bytes >= size) break;
    }
    return true;
}

#endif
