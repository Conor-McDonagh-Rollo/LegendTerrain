#pragma once
#include <memory>
#include <string>
#include <type_traits>

class Engine;

class GameObject : public std::enable_shared_from_this<GameObject> {
protected:
    GameObject() = default;
    GameObject(const char* _name) { name = _name; }
public:
    std::string name = "GameObject";
    virtual void awake() = 0;
    virtual void start() = 0;
    virtual void render() = 0;
    virtual void update(float dt) = 0;
    virtual void on_object_add() = 0;
    virtual void on_object_remove() = 0;
    virtual ~GameObject() = default;

    //Factory
    template<typename T, typename... Args>
    static std::shared_ptr<T> create(Args&&... args) {
        static_assert(std::is_base_of<GameObject, T>::value, "T must be a GameObject");

        // Create the object
        std::shared_ptr<T> obj = std::make_shared<T>(std::forward<Args>(args)...);

        // Register with the Engine
        Engine::getInstance().addObject(obj);

        return obj;
    }
};