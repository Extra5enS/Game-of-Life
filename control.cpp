#include"control.h"
#include<iostream>

control::control(settings set) { 
    __start_frame.resize(set.second);
    for(auto& col : __start_frame) {
        col.resize(set.first);
    }
}

void control::io_start_frame(std::istream& in) {
    int x = 2, y = 2;
    while(!in.eof()) {
        std::string pos;
        getline(in, pos);
        x = 2;
        for(auto c : pos) {
            if(c == 'x') {
                __start_frame[y][x] = 'x';
            }
            x++;
        }  
        y++;
    } 
}

map control::get_start_frame() {
    return __start_frame;
}
