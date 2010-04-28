
#include <UserInterface.hpp>

#include <SceneManager.hpp>
#include <WindowManager.hpp>
#include <iostream>

eng::Object* UserInterface::myLastHovered = 0;
eng::Object* UserInterface::myLastFocused = 0;

template<>
UserInterface*  eng::Singleton<UserInterface>::myInstance = 0;

UserInterface::UserInterface()
    :   eng::Scene("UI")
{
    SetColor(sf::Color(0, 0, 0, 0));
    SetZValue(999);
}

void    UserInterface::OnReceiveEvent(const sf::Event& event)
{
    if (event.Type == sf::Event::Closed || event.Type == sf::Event::LostFocus || event.Type == sf::Event::GainedFocus ||
        event.Type == sf::Event::MouseEntered || event.Type == sf::Event::MouseLeft)
        return;

    if (event.Type == sf::Event::Resized)
    {
        eng::WindowManager* window = eng::WindowManager::Get();
        SetSize(window->GetWidth(), window->GetHeight());
        return;
    }
    else if (event.Type == sf::Event::MouseMoved)
    {
        myHoveredObject = this;
        HandleHoveredObject(this, sf::Vector2f(event.MouseMove.X, event.MouseMove.Y));

        if (myHoveredObject)
        {
            if (myHoveredObject != myLastHovered)
            {
                sf::Event newEvent;
                if (myLastHovered)
                {
                    newEvent.Type = sf::Event::MouseLeft;
                    myLastHovered->OnReceiveEvent(newEvent);
                }
                if (myHoveredObject)
                {
                    newEvent.Type = sf::Event::MouseEntered;
                    myHoveredObject->OnReceiveEvent(newEvent);
                }
                myLastHovered = myHoveredObject;
            }
        }
    }
    else if (event.Type == sf::Event::MouseButtonPressed)
    {
        if (myHoveredObject)
        {
            if (myHoveredObject->IsFocusable())
            {
                myFocusedObject = myHoveredObject;

                if (myFocusedObject != myLastFocused)
                {
                    sf::Event newEvent;
                    if (myLastFocused)
                    {
                        newEvent.Type = sf::Event::LostFocus;
                        myLastFocused->OnReceiveEvent(newEvent);
                    }
                    if (myFocusedObject)
                    {
                        newEvent.Type = sf::Event::GainedFocus;
                        myFocusedObject->OnReceiveEvent(newEvent);
                    }
                    myLastFocused = myFocusedObject;
                }
            }
        }
    }

    // we send the current event to the object
    if (myFocusedObject && myFocusedObject != this)
    {
        myFocusedObject->OnReceiveEvent(event);
    }
}

void UserInterface::CleanFocus()
{
    myFocusedObject = 0;
    myHoveredObject = 0;
    myLastFocused = 0;
    myLastHovered = 0;
}

void    UserInterface::Update(float elapsedTime)
{
    eng::WindowManager* window = eng::WindowManager::Get();
    window->SetView(window->GetDefaultView());

    Object::Update(elapsedTime);
}

void    UserInterface::HandleHoveredObject(Object* object, const sf::Vector2f& mousePos)
{
    const eng::Objects& children = object->GetChildren();

    size_t max = children.size();
    for (size_t i = 0; i < max; ++i)
    {
        Object* child = children[i];
        if (child)
        {
            const sf::Vector2f& absPos = child->GetAbsolutePosition();

            if (mousePos.x >= absPos.x && mousePos.x <= absPos.x + child->GetSize().x &&
                mousePos.y >= absPos.y && mousePos.y <= absPos.y + child->GetSize().y && child->IsEnabled() && child->IsFocusable())
            {
                myHoveredObject = child;
                HandleHoveredObject(child, mousePos);
            }
        }
    }
}
