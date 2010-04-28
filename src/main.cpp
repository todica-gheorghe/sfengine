
#include <ScriptManager.hpp>
#include <WindowManager.hpp>
#include <SceneManager.hpp>
#include <UserInterface.hpp>

#include <SFML/Graphics.hpp>

int main(int ac, char **av)
{
    eng::ScriptManager* script = eng::ScriptManager::Get();
    script->LoadScript("main.lua");

/*
    eng::WindowManager* window = eng::WindowManager::Get();
    window->Create(sf::VideoMode(800, 600), "Lua Simple");


    eng::SceneManager* sceneManager = eng::SceneManager::Get();
    UserInterface* sceneUI = UserInterface::Get();

    eng::Object obj("Object");
    obj.Move(123, 123);
    obj.SetColor(sf::Color(255, 0, 0));
    obj.SetSize(20, 20);

    sceneUI->Add(&obj);
    sceneManager->AddScene(sceneUI);

    window->SetFramerateLimit(60);

    while (window->IsOpened())
    {
        sf::Event event;
        while (window->GetEvent(event))
        {
            if (event.Type == sf::Event::Closed)
                window->Close();

            sceneManager->GetEvent(event);
        }

        window->Clear(sf::Color(123, 0, 0));

        sceneManager->Display();

        window->Display();
    }
*/
    return 0;
}
