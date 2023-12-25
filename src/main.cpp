
#include <iostream>
#include "engine/core/InfEngine.h"

int main(int argc, char* argv[])
{
    if(!InfEngine::Initialize())
    {
        std::cout << "Engine initialization failed!" << std::endl;
        return -1;
    }

    INF_ENGINE->Cycle();

    return 0;
}
