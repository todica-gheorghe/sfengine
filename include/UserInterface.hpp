
#ifndef USERINTERFACE_HPP_INCLUDED
#define USERINTERFACE_HPP_INCLUDED

#include <Scene.hpp>
#include <Singleton.hpp>
#include <Label.hpp>

class UserInterface : public eng::Scene, public eng::Singleton<UserInterface>
{
    public:
        friend UserInterface*   eng::Singleton<UserInterface>::Get();
        friend void             eng::Singleton<UserInterface>::Kill();

        virtual void    Update(float elapsedTime);

        virtual void    OnReceiveEvent(const sf::Event& event);

        static void     CleanFocus();

    protected:
        UserInterface();

    private:
        void            HandleHoveredObject(Object* object, const sf::Vector2f& mousePos);

        static eng::Object     *myLastHovered, *myLastFocused;

};


#endif // USERINTERFACE_HPP_INCLUDED
