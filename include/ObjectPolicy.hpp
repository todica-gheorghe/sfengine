#ifndef OBJECTPOLICY_HPP_INCLUDED
#define OBJECTPOLICY_HPP_INCLUDED

#include <Object.hpp>
#include <SFML/Window/Event.hpp>

namespace eng
{
    class ObjectPolicy
    {
        public:
            ObjectPolicy(Object& object)
                :   myObject(object)
            {}

            virtual void    OnEvent(const sf::Event& event) = 0;

        protected:
            Object&     myObject;
    };

}

#endif // OBJECTPOLICY_HPP_INCLUDED
