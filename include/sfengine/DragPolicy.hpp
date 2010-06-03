
#ifndef BUTTONPOLICY_HPP_INCLUDED
#define BUTTONPOLICY_HPP_INCLUDED

#include <Engine/ObjectPolicy.hpp>

#include <boost/function.hpp>
#include <iostream>

namespace eng
{
    class DragPolicy : public ButtonPolicy
    {
        public:
            DragPolicy(Object& object)
                :   ButtonPolicy(object)
            {}

            virtual ~DragPolicy() {}


            virtual void    OnEvent(const sf::Event& event)
            {
                ButtonPolicy::OnEvent(event);
                if (event.Type == sf::Event::MouseButtonPressed)
                {
                    myIsPressed = true;
                }
                else if (event.Type == sf::Event::MouseButtonReleased && myIsPressed)
                {
                    myIsPressed = false;

                    if (OnClick)
                        OnClick();
                }
                else if (event.Type == sf::Event::MouseLeft)
                {
                    myIsPressed = false;
                }

            }

            boost::function<void()>     OnClick;

        private:
            bool                        myIsPressed;

    };
}

#endif // BUTTONPOLICY_HPP_INCLUDED
