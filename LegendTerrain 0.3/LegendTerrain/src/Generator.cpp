#include "../include/Generator.h"
#include "../include/Engine.h"

Generator::Generator()
{

    glm::vec3 pos{ 0.f,0.f,0.f };
    generateTerrain(pos);

    Input::MapAxis("Horizontal", GLFW_KEY_D, GLFW_KEY_A);
    Input::MapAxis("Vertical", GLFW_KEY_W, GLFW_KEY_S);
    Input::MapButton("Close", GLFW_KEY_ESCAPE);

    mainCamera = Engine::mainCamera.get();
}

void Generator::run()
{
}


void Generator::update(float dt)
{

    if (Input::GetAxis("Horizontal") > 0.f)
    {
        mainCamera->ProcessKeyboard(RIGHT, dt);
    }
    if (Input::GetAxis("Horizontal") < 0.f)
    {
        mainCamera->ProcessKeyboard(LEFT, dt);
    }
    if (Input::GetAxis("Vertical") > 0.f)
    {
        mainCamera->ProcessKeyboard(FORWARD, dt);
    }
    if (Input::GetAxis("Vertical") < 0.f)
    {
        mainCamera->ProcessKeyboard(BACKWARD, dt);
    }
    if (Input::GetButtonDown("Close"))
    {
        Engine::getInstance().stop();
    }
    
    generateTerrain(mainCamera->Position);
    
}

void Generator::generateTerrain(const glm::vec3& position)
{
    int posX = static_cast<int>(position.x);
    int posZ = static_cast<int>(position.z);

    auto checkAndCreate = [&](int x, int z) {
        if (currentTerrain[{x, z}] == false) {
            currentTerrain[{x, z}] = true;
            terrain.push_back(GameObject::create<Terrain>(glm::vec3{ x, 0, z }, 5));
        }
    };

    checkAndCreate(posX, posZ);

    for (int i = 1; i <= GEN_DIST; ++i) {
        for (int dx = -i; dx <= i; ++dx) {
            for (int dz = -i; dz <= i; ++dz) {
                checkAndCreate(posX + dx, posZ + dz);
            }
        }
    }
}
