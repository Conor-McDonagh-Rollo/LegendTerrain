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
    void render() override {
        //printf("render");
    }
};

int main()
{
    Input::MapButton("Jump", GLFW_KEY_SPACE);
    Input::MapButton("Sprint", GLFW_KEY_LEFT_SHIFT);
    Input::MapAxis("Horizontal", GLFW_KEY_D, GLFW_KEY_A);
    Input::MapAxis("Vertical", GLFW_KEY_W, GLFW_KEY_S);

    auto player = GameObject::create<Player>();

    Engine::getInstance().start(800,600,"Legend Terrain");

    return 0;
}

