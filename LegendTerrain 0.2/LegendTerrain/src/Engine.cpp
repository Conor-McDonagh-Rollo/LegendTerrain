#include "../include/Engine.h"

std::unique_ptr<Engine> Engine::instance = nullptr;
std::unique_ptr<Camera> Engine::mainCamera = nullptr;
std::shared_ptr<Shader> Engine::defaultShader = nullptr;

Engine::Engine()
{
}