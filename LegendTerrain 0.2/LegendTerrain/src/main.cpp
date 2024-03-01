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
        //Top
        2, 6, 7,
        2, 3, 7,

        //Bottom
        0, 4, 5,
        0, 1, 5,

        //Left
        0, 2, 6,
        0, 4, 6,

        //Right
        1, 3, 7,
        1, 5, 7,

        //Front
        0, 2, 3,
        0, 1, 3,

        //Back
        4, 6, 7,
        4, 5, 7
    };
    ms.vertices = {
        Vertex(- 1, -1,  0.5), //0
        Vertex(1, -1,  0.5), //1
        Vertex(-1,  1,  0.5), //2
        Vertex(1,  1,  0.5), //3
        Vertex(-1, -1, -0.5), //4
        Vertex(1, -1, -0.5), //5
        Vertex(-1,  1, -0.5), //6
        Vertex(1,  1, -0.5)  //7
    };
    
    auto testMesh = MeshGameObject::create<Player>(ms);
    testMesh->SetTexture("assets/defaults/default_texture2.jpg");
    testMesh->SetShader(Engine::defaultShader);


    Engine::getInstance()->start();

    return 0;
}

