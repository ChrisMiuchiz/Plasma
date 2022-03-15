#include <iostream>
#include "Object.h"
#include "GLEngine.h"

int main()
{
    plasma::GLEngine engine;
    plasma::Object obj(&engine);
    std::cout << "Engine: " << obj.GetEngine() << std::endl;
}
