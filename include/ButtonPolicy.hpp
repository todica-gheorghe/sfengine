
#ifndef BUTTONPOLICY_HPP_INCLUDED
#define BUTTONPOLICY_HPP_INCLUDED

#include <Engine/ObjectPolicy.hpp>

#include <Engine/WindowManager.hpp>
#include <boost/function.hpp>
#include <iostream>

namespace eng
{
    class ButtonPolicy : public ObjectPolicy
    {
        public:
            ButtonPolicy(Object& object)
                :   ObjectPolicy(object)
            {}

            virtual ~ButtonPolicy() {}


            virtual void    OnEvent(const sf::Event& event)
            {
                if (event.Type == sf::Event::MouseButtonPressed)
                {
                    myIsPressed = true;
                    WindowManager* window = WindowManager::Get();
                    myDragOffset = sf::Vector2f(window->GetInput().GetMouseX(), window->GetInput().GetMouseY()) - myObject.GetAbsolutePosition();
                }
                else if (event.Type == sf::Event::MouseButtonReleased && myIsPressed)
                {
                    myIsPressed = false;

                    if (OnClick)
                        OnClick(event.MouseButton);
                }

                if (myIsPressed && event.Type == sf::Event::MouseMoved)
                {
                    if (OnDragged)
                        OnDragged(myDragOffset);
                }

            }

            boost::function<void(const sf::Event::MouseButtonEvent&)>   OnClick;
            boost::function<void(const sf::Vector2f&)>                  OnDragged;

        private:
            bool                        myIsPressed;
            sf::Vector2f                myDragOffset;

    };
}

#endif // BUTTONPOLICY_HPP_INCLUDED
