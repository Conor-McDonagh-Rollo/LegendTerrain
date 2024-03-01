#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm/vec2.hpp>
#include <unordered_map>
#include <string>

struct Key
{
    int code;
    bool isPressed;
    bool wasPressed;
    bool wasReleased;

    Key(int keyCode = 0) : code(keyCode), isPressed(false), wasPressed(false), wasReleased(true) {}
};

struct Axis
{
    int positiveKey;
    int negativeKey;
    Axis(int posKey = 0, int negKey = 0) : positiveKey(posKey), negativeKey(negKey) {}
};

class Input
{
private:
    static std::unordered_map<int, Key> keyStates;
    static std::unordered_map<std::string, int> buttonMappings;
    static std::unordered_map<std::string, Axis> axisMappings;
    static glm::vec2 mousePosition;
    static std::unordered_map<int, bool> mouseButtons;

    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
    static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);

public:
    static void Initialize(GLFWwindow* window, int SCR_WIDTH, int SCR_HEIGHT);
    static void Update(); 
    static void MapButton(const std::string& buttonName, int keyCode);
    static void MapAxis(const std::string& axisName, int positiveKey, int negativeKey);
    static bool GetButton(const std::string& buttonName);
    static bool GetButtonDown(const std::string& buttonName);
    static bool GetButtonUp(const std::string& buttonName);
    static float GetAxis(const std::string& axisName);
    static glm::vec2 GetMousePosition();
    static bool GetMouseButton(int button);
};