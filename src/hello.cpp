/*
* hello
*
* Hacky
*/

#include "hello.h"
#include "utils.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define VERSION "0.0.1"

bool log_to_file = true;
std::string log_dir_prefix = "./";
std::ofstream log_stream;

void set_log_dir(const char* dir){
    if(dir != nullptr){
        struct stat st;
        if(stat(dir, &st) == 0){
            if(S_ISDIR(st.st_mode)){
                //dir is exist
                log_to_file = true;
                log_dir_prefix = dir;
                return;
            }
        }
    }
    log_to_file = false;
    log_dir_prefix = "";
}

std::string version(){
    std::string date = __DATE__, time = __TIME__;
    std::stringstream ss;
    ss<<VERSION<<"."<<date.substr(date.length()-4);
    //Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec
    std::string month = date[2] == 'n' ? (date[1] == 'a' ? "01" : "06") :
        date[2] == 'b' ? "02" : date[2] == 'r' ? (date[1] == 'a' ? "03" : "04") :
        date[2] == 'y' ? "05" : date[2] == 'l' ? "07" : date[2] == 'g' ? "08" :
        date[2] == 'p' ? "09" : date[2] == 't' ? "10" : date[2] == 'v' ? "11" :
        date[2] == 'c' ? "12" : "99";
    std::remove(time.begin(),time.end(),':');
    ss<<month<<date.substr(4,2)<<time.substr(0,6);
    return ss.str();
}

bool Hello::login(const char* user, const char* passwd){
    if(user == nullptr || *user == '\0'){
        return false;
    }
    if(passwd == nullptr || *passwd == '\0'){
        return false;
    }
    if(!strcmp(user,"hello") && !strcmp(passwd,"hello")){
        return true;
    }
    return false;
}

std::string Hello::hello(){
    log("INFO")<<"call hello()"<<std::endl;
    return "hello from cpp";
}

int Hello::add(const std::vector<int>& v){
    int sum = 0;
    for(auto i : v){
        sum += i;
    }
    log("INFO")<<"call add() result: "<<sum<<std::endl;
    return sum;
}

std::vector<std::string> Hello::split(const char* str, const char* sep){
    log("INFO")<<"call split() str: "<<str<<std::endl;
    std::string src(str);
    std::vector<std::string> vs;
    size_t start = 0, pos = src.find_first_of(sep);
    while(pos != std::string::npos){
        vs.push_back(src.substr(start, pos));
        start = pos + 1;
        pos = src.find_first_of(sep, pos);
    }
    return vs;
}
