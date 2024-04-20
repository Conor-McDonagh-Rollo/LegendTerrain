#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "Globals.h"

class Input {
public:
    static void Update() {
        lastKeyState = keyState;
    }

    static void SetButton(const std::string& name, sf::Keyboard::Key key) {
        buttonKeys[name] = key;
    }

    static bool GetButton(const std::string& name) {
        auto key = buttonKeys[name];
        return keyState[key];
    }

    static bool GetButtonDown(const std::string& name) {
        auto key = buttonKeys[name];
        return keyState[key] && !lastKeyState[key];
    }

    static bool GetButtonUp(const std::string& name) {
        auto key = buttonKeys[name];
        return !keyState[key] && lastKeyState[key];
    }

    static bool GetMouseButton(int num)
    {
        return sf::Mouse::isButtonPressed((sf::Mouse::Button)num);
    }

    static sf::Vector2f GetMousePositionInWorld()
    {
        return Globals::window->mapPixelToCoords(sf::Mouse::getPosition(*Globals::window), *Globals::view);
    }

    static sf::Vector2f GetMousePositionInScreen()
    {
        return (sf::Vector2f)sf::Mouse::getPosition(*Globals::window);
    }

    static std::unordered_map<sf::Keyboard::Key, bool> keyState;
private:
    static std::unordered_map<std::string, sf::Keyboard::Key> buttonKeys;
    static std::unordered_map<sf::Keyboard::Key, bool> lastKeyState;
};
