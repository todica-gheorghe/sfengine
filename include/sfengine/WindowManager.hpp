#ifndef WINDOWMANAGER_HPP_INCLUDED
#define WINDOWMANAGER_HPP_INCLUDED

#include <sfengine/Singleton.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/String.hpp>

namespace eng
{
    class WindowManager : public Singleton<WindowManager>, public sf::RenderWindow
    {
        public:
            friend WindowManager*   Singleton<WindowManager>::Get();
            friend void             Singleton<WindowManager>::Kill();

            void        Create(const sf::VideoMode& videoMode, const char* title, unsigned long style);

            virtual ~WindowManager();

        protected:
            WindowManager();


        private:

    };
}

#endif // WINDOWMANAGER_HPP_INCLUDED
