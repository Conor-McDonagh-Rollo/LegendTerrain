#include "../include/Engine.h"
#include <iostream>

class Player : public MeshGameObject {
public:
    Player(MeshShape ms) : MeshGameObject(ms) {}

    void update(float dt) override {
        
        if (Input::GetButton("Jump"))
        {
            Move({ 0,1 / 100.f,0 });
            std::cout << GetPosition().x << ", " << GetPosition().y << ", " << GetPosition().z << ".\n";
        }
        if (Input::GetButton("Crouch"))
        {
            Move({ 0,-1 / 100.f,0 });
            std::cout << GetPosition().x << ", " << GetPosition().y << ", " << GetPosition().z << ".\n";
        }
        glm::vec2 movement = glm::vec2(Input::GetAxis("Horizontal"), Input::GetAxis("Vertical"));
        
        if (movement != glm::vec2{0.f,0.f})
        {
            Move({ movement.x / 100.f, 0, movement.y / 100.f });
            std::cout << GetPosition().x << ", " << GetPosition().y << ", " << GetPosition().z << ".\n";
        }


    }
    void start() override {
        Input::MapButton("Jump", GLFW_KEY_SPACE);
        Input::MapButton("Crouch", GLFW_KEY_LEFT_CONTROL);
        Input::MapButton("GetScene", GLFW_KEY_G);
        Input::MapAxis("Horizontal", GLFW_KEY_D, GLFW_KEY_A);
        Input::MapAxis("Vertical", GLFW_KEY_W, GLFW_KEY_S);
    }
};

int main()
{
    Engine::load(1920, 1080, "Legend Terrain");


    MeshShape ms;
    ms.indices = {
        //Front
        0, 1, 2,
        0, 3, 2,

    };
    ms.vertices = {
        Vertex(0, 0,  0), //0
        Vertex(1, 0,  0), //1
        Vertex(1,  -1,  0), //2
        Vertex(0,  -1,  0), //3
    };
    
    auto testMesh = MeshGameObject::create<Player>(ms);
    testMesh->SetTexture("assets/defaults/default_texture2.jpg");
    testMesh->SetShader(Engine::defaultShader);


    Engine::getInstance()->start();

    return 0;
}

