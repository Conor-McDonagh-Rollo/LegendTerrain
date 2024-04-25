
#include "../include/Engine.h"
#include "../include/Generator.h"

int main()
{
    // ENGINE CREATION
    Engine* engine = new Engine{ "LegendTerrain 0.3" };

    // GAMEOBJECT CREATION
    Noise noise;
    Noise::instance->Load();
    auto generator = GameObject::create<Generator>();
    generator->run();

    // GAME RUN AND END
    engine->start();
    return 0;
}

