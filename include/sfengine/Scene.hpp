#ifndef SCENE_HPP_INCLUDED
#define SCENE_HPP_INCLUDED

#include <sfengine/Object.hpp>

namespace eng
{
    class Scene : public Object
    {
        public :
            Scene(const sf::String& name);
            virtual ~Scene();
    };
}
#endif // SCENE_HPP_INCLUDED
