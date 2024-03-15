#include "Input.h"
std::unordered_map<std::string, sf::Keyboard::Key> Input::buttonKeys;
std::unordered_map<sf::Keyboard::Key, bool> Input::keyState;
std::unordered_map<sf::Keyboard::Key, bool> Input::lastKeyState;