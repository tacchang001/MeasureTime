#include <iostream>

#include "StopWatch.h"

int main(int argc, char* argv[])
{
    std::cout << "Hello Example" << std::endl;
    
    auto sw = new StopWatch();
    sw->Start();
    sw->Stop();
    std::cout << sw->GetElapsedCount() << std::endl;

    return 0;
}