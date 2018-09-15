%module hello
%include "std_string.i"
%include "std_vector.i"
%template(StringVector) std::vector<std::string>;
%template(IntVector) std::vector<int>;
%{
#include "hello.h"
%}
%include "hello.h"
