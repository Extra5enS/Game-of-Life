#include"machin.h"
#include<omp.h>
#include<iostream>

machin::machin() {}

void machin::set_start_map(control* c) {
    __map = c -> get_start_frame();
}

void machin::visit_map(map_printer printer) {
    for(size_t x = 0; x < __map.size(); ++x) {
        for(size_t y = 0; y < __map[0].size(); ++y) {
            if(__map[x][y] == 'x') {
                printer({y, x}, 'x');
            }
        }
    }
}

int looking_around(map m, coord place, char find_char) {
    int counter = 0;
    for(int i = place.first - 1; i <= place.first + 1; i++) {
        for(int j = place.second - 1; j <= place.second + 1; j++) {
            if(i == place.first && j == place.second) {
                continue;
            }
            int x = (i < 0) ? (m.size() - 1) : ((i >= m.size()) ? (0) : (i));
            int y = (j < 0) ? (m[0].size() - 1) : ((j >= m[0].size()) ? (0) : (j));
            if(m[x][y] == find_char) {
                counter++;
            }
        }
    }
    return counter;
}

void machin::next_step() {
    map __new_map = __map;
    for(size_t x = 0; x < __new_map.size(); ++x) {
        for(size_t y = 0; y < __new_map[0].size(); ++y) {
            if(__new_map[x][y] == 'x') {
                int num = looking_around(__new_map, {x, y}, 'x');
                if(num < 2 || num > 3) {
                    __map[x][y] = '\0';
                }
            }
            if(__new_map[x][y] == '\0') {
                int num = looking_around(__new_map, {x, y}, 'x');
                if(num == 3) {
                    __map[x][y] = 'x';
                }
            }
        }
    }
}

void machin::next_step_omp(size_t num_threads) {
    map __new_map = __map;
    #pragma omp parallel num_threads(num_threads)
    {
        #pragma omp for
        for(size_t x = 0; x < __new_map.size(); ++x) {
            //#pragma omp for
            for(size_t y = 0; y < __new_map[0].size(); ++y) {
                if(__new_map[x][y] == 'x') {
                    int num = looking_around(__new_map, {x, y}, 'x');
                    if(num < 2 || num > 3) {
                        __map[x][y] = '\0';
                    }
                }
                if(__new_map[x][y] == '\0') {
                    int num = looking_around(__new_map, {x, y}, 'x');
                    if(num == 3) {
                        __map[x][y] = 'x';
                    }
                }
            }
        }

    }
}
