
#include <SceneManager.hpp>

#include <WindowManager.hpp>

#include <iostream>

namespace eng
{
    template<>
    SceneManager*   Singleton<SceneManager>::myInstance = 0;

    SceneManager::SceneManager()
    {

    }

    SceneManager::~SceneManager()
    {
        myScenes.clear();
    }

    void    SceneManager::GetEvent(const sf::Event& event)
    {
        size_t max = myScenes.size();
        for (size_t it = 0; it != max; ++it)
        {
            Scene* scene = myScenes[it];

            if (scene)
                if (scene->IsEnabled())
                {
                    scene->OnReceiveEvent(event);
                }
        }
    }


    static bool    OrderByZOrder(Scene* sc1, Scene* sc2)
    {
        return sc1->GetZValue() < sc2->GetZValue();
    }

    void    SceneManager::Display()
    {
        std::sort(myScenes.begin(), myScenes.end(), &OrderByZOrder);
        // order scene by zvalue

        WindowManager* window = WindowManager::Get();

        size_t max = myScenes.size();

        for (size_t it = 0;it != max; ++it)
        {
            Scene* scene = myScenes[it];

            if (scene)
            {
                if (scene->IsEnabled())
                    scene->Update(window->GetFrameTime());

                if (scene->IsVisible())
                    window->Draw(*scene);

            }
        }

        window->SetView(window->GetDefaultView());
    }


    void    SceneManager::AddScene(Scene* scene)
    {
        if (!scene)
            return;

        myScenes.push_back(scene);
    }

    void    SceneManager::RemoveScene(Scene* scene)
    {
        if (!scene)
            return;

        for (Scenes::iterator it = myScenes.begin(); it != myScenes.end(); ++it)
            if (*it == scene)
            {
                myScenes.erase(it);
                return;
            }
    }

    Scene*  SceneManager::GetScene(const sf::String& sceneName)
    {
        for (Scenes::iterator it = myScenes.begin(); it != myScenes.end(); ++it)
        {
            Scene* scene = *it;
            if (scene->GetName() == sceneName)
            {
                return scene;
            }
        }
        return 0;
    }

}
