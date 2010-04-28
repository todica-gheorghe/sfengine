
#include <Scene.hpp>

#include <algorithm>
#include <WindowManager.hpp>

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
