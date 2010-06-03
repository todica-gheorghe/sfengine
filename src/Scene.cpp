
#include <sfengine/Scene.hpp>
#include <sfengine/WindowManager.hpp>

#include <algorithm>

namespace eng
{
    Scene::Scene(const sf::String& name)
        :   Object(name)
    {
        WindowManager* window = WindowManager::Get();
        SetSize(window->GetWidth(), window->GetHeight());

        SetColor(sf::Color(0, 0, 0));
    }

    Scene::~Scene()
    {

    }



}
