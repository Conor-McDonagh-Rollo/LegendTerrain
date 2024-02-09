#include "../include/Engine.h"
#include <iostream>

class Player : public GameObject {
public:
    void update(float dt) override {
        //printf("update");
        if (Input::GetButtonDown("Jump"))
        {
            printf("Jump Pressed!\n");
        }
        if (Input::GetButtonUp("Jump"))
        {
            printf("Jump Released!\n");
        }
        if (Input::GetButtonDown("GetScene"))
        {
            std::cout << Engine::getInstance()->GetCurrentScene()->name << std::endl;
        }
        if (Input::GetButton("Sprint"))
        {
            printf("Sprinting!\n");
        }
        if (Input::GetMouseButton(0))
        {
            printf("Shoot!\n");
        }
        if (Input::GetMouseButton(1))
        {
            printf("Aim!\n");
        }

        glm::vec2 movement = glm::vec2(Input::GetAxis("Horizontal"), Input::GetAxis("Vertical"));
        
        if (movement != glm::vec2{0.f,0.f})
        {
            std::cout << movement.x << ", " << movement.y << std::endl;
        }


    }
    void start() override {
        Input::MapButton("Jump", GLFW_KEY_SPACE);
        Input::MapButton("Sprint", GLFW_KEY_LEFT_SHIFT);
        Input::MapButton("GetScene", GLFW_KEY_G);
        Input::MapAxis("Horizontal", GLFW_KEY_D, GLFW_KEY_A);
        Input::MapAxis("Vertical", GLFW_KEY_W, GLFW_KEY_S);
    }
};

int main()
{
    Engine::load(800, 600, "Legend Terrain");
    //auto player = GameObject::create<Player>();
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
    
    auto testMesh = MeshGameObject::create<MeshGameObject>(ms);
    testMesh->SetTexture("assets/defaults/default_texture2.jpg");
    testMesh->SetShader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");


    Engine::getInstance()->start();

    return 0;
}

