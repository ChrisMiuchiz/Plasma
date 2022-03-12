#include <iostream>
#include "Object.h"

int main()
{
    plasma::Object obj((plasma::Engine*)0x12345678);
    std::cout << "Engine: " << obj.GetEngine() << std::endl;
}
