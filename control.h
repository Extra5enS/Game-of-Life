#ifndef __CONTROL
#define __CONTROL

#include<vector>
#include<istream>

using map = std::vector<std::vector<char>>;
using settings = std::pair<long, long>;
using coord = std::pair<long, long>; 

class control {
public:
    control(settings s);
    void io_start_frame(std::istream&);
    map get_start_frame();
private:
    map __start_frame;
};

#endif
