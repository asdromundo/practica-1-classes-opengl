#include "Entity.hpp"

Entity::Entity(const std::string &name) : name(name) {}

void Entity::addComponent(std::shared_ptr<Component> component)
{
    components.push_back(component);
}

const std::string &Entity::getName() const
{
    return name;
}

// Las funciones template deben definirse en el archivo de cabecera
// el linker se queja si se definen aquí
/* template <typename T>
T *Entity::getComponent()
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
} */
