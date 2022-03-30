#include <iostream>
#include "Object.h"
#include "GLEngine.h"
#include "PLXStreamReader.h"
#include "Vector.h"

int main()
{
    //plasma::GLEngine engine;
    //plasma::Object obj(&engine);
    //std::cout << "Engine: " << obj.GetEngine() << std::endl;

    ////std::ifstream input("C:\\Users\\a\\Desktop\\Picroma Plasma\\gui-elements.plx", std::ios::binary);
    ////std::ifstream input("C:\\Users\\a\\Desktop\\plasma\\gui-elements.plx", std::ios::binary);
    //std::ifstream input("C:\\Users\\a\\Desktop\\AndyMyers.plg", std::ios::binary);

    //std::vector<u64> keys;
    //keys.push_back(plasma::StringHash("PlasmaXGraphics"));
    //engine.ReadPLXFile(nullptr, nullptr, (u32)plasma::PLXStreamReader::FLAGS::CHECK_FORMAT, &input, keys);

    plasma::Vector<4, float> vec({ 5,6,7,8 });

    plasma::Vector<4, float> vec2 = vec;

    vec.Set(0, 0.0);

    for (u32 i = 0; i < 4; i++) {
        std::cout << vec2.Get(i) << std::endl;
    }
}
