#ifndef SCENEMANAGER_HPP_INCLUDED
#define SCENEMANAGER_HPP_INCLUDED

#include <sfengine/Singleton.hpp>
#include <sfengine/Scene.hpp>
#include <map>

namespace eng
{
    typedef std::vector<Scene*>     Scenes;

    class SceneManager : public Singleton<SceneManager>
    {
        public:
            friend SceneManager*    Singleton<SceneManager>::Get();
            friend void             Singleton<SceneManager>::Kill();

            void                    AddScene(Scene* scene);
            void                    RemoveScene(Scene* scene);

            Scene*                  GetScene(const sf::String& sceneName);

            void                    GetEvent(const sf::Event& event);
            void                    Display();

            virtual ~SceneManager();

        protected:
            SceneManager();

        private:
            Scenes                  myScenes;

    };

}

#endif // SCENEMANAGER_HPP_INCLUDED
