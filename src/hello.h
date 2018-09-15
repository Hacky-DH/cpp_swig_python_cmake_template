/*
* hello
* header file
*
* Hacky
*/
#ifndef HELLO_H
#define HELLO_H

#include <string>
#include <vector>

class Hello {
public:
    bool login(const char* user, const char* passwd);
    std::string hello();
    int add(const std::vector<int>& v);
    std::vector<std::string> split(const char* str, const char* sep);
};

extern void set_log_dir(const char* dir);
extern std::string version();

#endif
