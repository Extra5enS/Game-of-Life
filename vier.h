#ifndef __VIER
#define __VIER

#include <utility>
#include <signal.h>
#include <termios.h>
#include <time.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <poll.h>
#include <iostream>


#include"machin.h"

struct timer : public std::pair<long, std::function<void()>> {
    timer() {}
    timer(long first, std::function<void()> second) : pair(first, second) {}
    void set_time(long time);
    void time_update(long time);
}; 

class vier {
public:
    static vier* get();
    void set_machin(machin*);
    void print();
    void run();
    ~vier();
    
    settings get_settings();
    void print_coord(coord, char);
    void print_col(int);
    void print_row(int);
    void clean();

    timer __timer;

private:
    vier();

    machin* __machin; 
};

#endif
