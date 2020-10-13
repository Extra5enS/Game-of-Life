#ifndef __MACHIN
#define __MACHIN

#include<vector>
#include<functional>
#include<list>

#include"control.h"

using map = std::vector<std::vector<char>>;
using map_printer = std::function<void(coord, char)>; 

class machin {
public:
    machin();
    void set_start_map(control*);
    void next_step();
    void visit_map(map_printer printer);
private:
    map __map;
    std::list<coord> lifes;
    std::list<coord> around_lifes;
    control* __cont;
    int step_num = 0;
};

#endif
