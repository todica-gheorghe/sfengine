

#include <SFML/Graphics.hpp>

#include <sfengine/TextInput.hpp>
#include <sfengine/UserInterface.hpp>
#include <sfengine/SceneManager.hpp>
#include <sfengine/WindowManager.hpp>

int main(int ac, char **av)
{
    eng::WindowManager* win = eng::WindowManager::Get();
    win->Create(sf::VideoMode(800, 600), "Object", sf::Style::Close);

    eng::TextInput input("", 50);
    input.Move(120, 120);
    UserInterface* ui = UserInterface::Get();
    ui->Add(&input);
    ui->SetColor(sf::Color(255, 0, 0));

    eng::SceneManager* sceneManager = eng::SceneManager::Get();
    sceneManager->AddScene(ui);


    while (win->IsOpened())
    {
        sf::Event event;
        while (win->GetEvent(event))
        {
            if (event.Type == sf::Event::Closed)
            {
                win->Close();
            }

            sceneManager->GetEvent(event);
        }

        win->Clear();

        sceneManager->Display();

        win->Display();
    }
    return 0;
}
