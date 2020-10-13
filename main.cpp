#include"vier.h"
#include<fstream>
#include<iostream>

int main() { 
    struct termios term, copy_term;
    tcgetattr(1, &term);
    copy_term = term;
    cfmakeraw(&term);
    tcsetattr(1, TCSANOW, &term);
    signal(SIGWINCH, [](int x) {
        vier::get() -> print();
    });
    
    machin m;
    vier* v = vier::get();
    v -> set_machin(&m);
    control c(v -> get_settings());
    std::ifstream in("start.txt");     
    c.io_start_frame(in);
    m.set_start_map(&c);

    v -> run();
    tcsetattr(1, TCSANOW, &copy_term);
    std::cout << "There was good life, thank you!" << std::endl;

    return 0;
}
