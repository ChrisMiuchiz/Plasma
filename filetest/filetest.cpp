#include <iostream>
#include "Object.h"
#include "GLEngine.h"
#include "PLXStreamReader.h"

int main()
{
    plasma::GLEngine engine;
    plasma::Object obj(&engine);
    std::cout << "Engine: " << obj.GetEngine() << std::endl;

    std::ifstream input("C:\\Users\\a\\Desktop\\Picroma Plasma\\gui-elements.plx", std::ios::binary);
    //std::ifstream input("C:\\Users\\a\\Desktop\\plasma\\gui-elements.plx", std::ios::binary);

    std::vector<u64> keys;
    keys.push_back(plasma::StringHash("PlasmaXGraphics"));
    engine.ReadPLXFile(nullptr, nullptr, (u32)plasma::PLXStreamReader::FLAGS::CHECK_FORMAT, &input, keys);
}
