#include "../include/Input.h"

std::unordered_map<int, Key> Input::keyStates;
std::unordered_map<std::string, int> Input::buttonMappings;
std::unordered_map<std::string, Axis> Input::axisMappings;
glm::vec2 Input::mousePosition;
std::unordered_map<int, bool> Input::mouseButtons;

void Input::Initialize(GLFWwindow* window, int SCR_WIDTH, int SCR_HEIGHT)
{
    glfwSetKeyCallback(window, Input::KeyCallback);
    glfwSetMouseButtonCallback(window, Input::MouseButtonCallback);
    glfwSetCursorPosCallback(window, Input::CursorPositionCallback);
}

void Input::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        keyStates[key].isPressed = true;
        keyStates[key].wasPressed = true;
    }
    else if (action == GLFW_RELEASE)
    {
        keyStates[key].isPressed = false;
    }
}

void Input::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        mouseButtons[button] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        mouseButtons[button] = false;
    }
}

void Input::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    mousePosition = glm::vec2(static_cast<float>(xpos), static_cast<float>(ypos));
}

void Input::Update()
{
    for (auto& keyState : keyStates)
    {
        keyState.second.wasPressed = false;
        keyState.second.wasReleased = false;
        if (!keyState.second.isPressed)
            keyState.second.wasReleased = true;
    }
}

void Input::MapButton(const std::string& buttonName, int keyCode)
{
    buttonMappings[buttonName] = keyCode;
}

void Input::MapAxis(const std::string& axisName, int positiveKey, int negativeKey)
{
    axisMappings[axisName] = Axis(positiveKey, negativeKey);
}

bool Input::GetButton(const std::string& buttonName)
{
    int keyCode = buttonMappings[buttonName];
    return keyStates[keyCode].isPressed;
}

bool Input::GetButtonDown(const std::string& buttonName)
{
    int keyCode = buttonMappings[buttonName];
    return keyStates[keyCode].wasPressed;
}

bool Input::GetButtonUp(const std::string& buttonName)
{
    int keyCode = buttonMappings[buttonName];
    return !keyStates[keyCode].isPressed && !keyStates[keyCode].wasReleased;
}

float Input::GetAxis(const std::string& axisName)
{
    Axis& axis = axisMappings[axisName];
    float value = 0.0f;
    if (keyStates[axis.positiveKey].isPressed)
        value += 1.0f;
    if (keyStates[axis.negativeKey].isPressed)
        value -= 1.0f;
    return value;
}

bool Input::GetMouseButton(int button)
{
    return mouseButtons[button];
}

glm::vec2 Input::GetMousePosition()
{
    return mousePosition;
}