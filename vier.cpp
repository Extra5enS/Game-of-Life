#include"vier.h"

#define TIME_FOR_TIMER 1

void timer::set_time(long time) {
    first = time;
}

void timer::time_update(long time) {
    first -= time;
    if(time < 0) {
        first = 0;
    }
}

void vier::clean() {
    printf("\e[H\e[J");
}

settings vier::get_settings() {
    struct winsize argp;
    ioctl(1, TIOCGWINSZ, &argp);
    return {argp.ws_col, argp.ws_row};
}

void vier::print_row(int y) {
    int x_size = get_settings().first;
    printf("\e[%d;%dH", y, 0);
    for(int i = 0; i < x_size; ++i) {
        printf("\x1b[36m%c\x1b[0m", '#');
    }
}

void vier::print_col(int x) {
    int y_size = get_settings().second;
    for(int i = 0; i < y_size; ++i) {
        printf("\e[%d;%dH", i, x);
        printf("\x1b[36m%c\x1b[0m", '#');
    }
}

void vier::print_coord(coord __coord, char value) {
    printf("\e[%ld;%ldH", __coord.second + 1, __coord.first + 1);
    printf("\x1b[20m%c\x1b[0m", value);
}


void vier::print() {
    
    clean();
    __machin -> visit_map(std::bind(&vier::print_coord, this, 
                                    std::placeholders::_1,
                                    std::placeholders::_2));
    
    printf("\e[H");
    fflush(stdout);
}

void vier::set_machin(machin* m) {
    __machin = m;
}

vier::vier() {
    __timer = {TIME_FOR_TIMER, []() {
        #ifdef USE_OMP
        vier::get() -> __machin -> next_step_omp(4);
        #else
        vier::get() -> __machin -> next_step();
        #endif
    }};
}

void vier::run() {
    struct pollfd k = {1, POLLIN, 0};
    
    print();
    while(1) {
        if(poll(&k, 1, __timer.first)) {
            char ComeData;
            read(1, &ComeData, 1);
            if(ComeData == 'e') {
                break;
            }
        } else {
            __timer.second();
            __timer.set_time(TIME_FOR_TIMER);
            print();
        }
    }
    clean();
}

vier* self = nullptr;
vier* vier::get() {
    if(self == nullptr) {
        self = new vier;
    }
    return self;
}

vier::~vier() {
    delete self;
}
