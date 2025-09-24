#pragma once
#include <vector>
#include <memory>
#include "Component.hpp"

class Entity
{
public:
    Entity(const std::string &name);
    void addComponent(std::shared_ptr<Component> component);
    template <typename T>
    T *getComponent()
    {
        for (auto &comp : components)
        {
            T *casted = dynamic_cast<T *>(comp.get());
            if (casted)
            {
                return casted;
            }
        }
        return nullptr;
    }
    const std::string &getName() const;

private:
    std::string name;
    std::vector<std::shared_ptr<Component>> components;
};
