#ifndef OBJECT_HPP_INCLUDED
#define OBJECT_HPP_INCLUDED

#include <map>
#include <vector>

#include <SFML/System/String.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Drawable.hpp>

#include <luabind/luabind.hpp>

namespace eng
{
    class Object;
    class ObjectPolicy;

    typedef std::vector<Object*>        Objects;
    typedef std::vector<ObjectPolicy*>  Policies;

    class Object : public sf::Drawable
    {
        public :

            Object(const sf::String& name);

            const sf::Uint32    GetId() const;

            void                SetName(const sf::String& name);
            const sf::String&   GetName() const;

            void                SetParent(Object* parent);
            Object*             GetParent() const;

            void                SetSize(const sf::Vector2f& size);
            void                SetSize(float width, float height);
            const sf::Vector2f& GetSize() const;

            void                Add(Object* object);
            void                Remove(Object* object);
            void                Clear();

            virtual void        OnAdded(Object* object) {}
            virtual void        OnRemoved(Object* object) {}

            Objects&            GetChildren();
            Object*             FindObjectByName(const sf::String& name);

            sf::Vector2f        GetAbsolutePosition() const;

            bool                IsFocused() const;
            bool                IsHovered() const;

            void                SetZValue(sf::Uint8 zvalue);
            sf::Uint8           GetZValue() const;

            void                SetVisible(bool visible);
            bool                IsVisible() const;

            void                SetFocusable(bool focusable);
            bool                IsFocusable() const;

            void                SetEnabled(bool enabled);
            bool                IsEnabled() const;

            void                SetScissor(int x, int y, int width, int height);
            void                UseScissor(bool use);

            void                AddPolicy(ObjectPolicy* policy);
            void                RemovePolicy(ObjectPolicy* policy);

            virtual void        OnReceiveEvent(const sf::Event& event);

            void                SetResizeCallback(const luabind::object& callback);
            void                SetUpdateCallback(const luabind::object& callback);
            void                SetDrawCallback(const luabind::object& callback);
            void                SetEventCallback(const luabind::object& callback);

            virtual void        Update(float elapsedTime);

            static Object*      myFocusedObject;
            static Object*      myHoveredObject;

            static sf::Uint32   NextId;


        protected:
            virtual void        Render(sf::RenderTarget& target, sf::Renderer& renderer) const;

        private:

            sf::String          myName;
            sf::Uint32          myId;

            Objects             myChildren;
            Object*             myParent;

            Policies            myPolicies;

            sf::Uint8           myZValue;
            sf::Vector2f        mySize;

            bool                myVisible;
            bool                myEnabled;
            bool                myFocusable;

            bool                myUseScissor;
            sf::Vector2i        myScissorPos, myScissorSize;

            luabind::object     myUpdateCallback, myEventCallback, myResizeCallback, myDrawCallback;
    };
}

#endif // OBJECT_HPP_INCLUDED
