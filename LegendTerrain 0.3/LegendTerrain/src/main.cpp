
#include "../include/Engine.h"
#include "../include/Generator.h"

int main()
{
    // ENGINE CREATION
    Engine* engine = new Engine{ "LegendTerrain 0.3" };

    // SET TEXTURE MAP
    Texture* stone = new Texture();
    stone->set("stone", "assets/defaults/stone.jpg");
    Texture* water = new Texture();
    water->set("water", "assets/defaults/water.jpg");
    Texture* ground = new Texture();
    ground->set("ground", "assets/defaults/ground.jpg");

    // GAMEOBJECT CREATION
    Noise noise;
    Noise::instance->Load();
    auto generator = GameObject::create<Generator>();
    generator->run();

    // GAME RUN AND END
    engine->start();
    return 0;
}

