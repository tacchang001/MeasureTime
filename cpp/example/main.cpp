#include <iostream>

#include "StopWatch.h"

int main(int argc, char* argv[])
{
    std::cout << "Hello Example" << std::endl;
    
    auto sw = new StopWatch();
    sw->start();
    sw->stop();
    std::cout << sw->getElapsedSec() << std::endl;

    return 0;
}