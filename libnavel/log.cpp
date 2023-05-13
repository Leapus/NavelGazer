#include <iostream>
#include "concurrent.hpp"
#include "log.hpp"


using namespace std;
using namespace leapus::navelgazer;


void leapus::navelgazer::log::info(const std::string &msg){
    static critical_section cs;
    auto lock=cs.lock();
    std::cout << msg << std::endl;
}