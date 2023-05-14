#pragma
#include <cstdint>

namespace leapus{

//Generalization of strlen for a null-terminated array of whatever
template<typename T, T Null=T{0}>
size_t stringlen(T *p){
    T *q=p;
    while(*(q++)!=Null){}
    return q-p;
}


}
