
#include <WindowManager.hpp>

namespace eng
{
    template<>
    WindowManager*  Singleton<WindowManager>::myInstance = 0;

    WindowManager::WindowManager()
    {

    }

    void    WindowManager::Create(const sf::VideoMode& videoMode, const char* title, unsigned long style)
    {
        sf::RenderWindow::Create(videoMode, title, style);
    }

    WindowManager::~WindowManager()
    {

    }

}
