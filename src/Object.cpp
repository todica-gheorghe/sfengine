
#include <Object.hpp>
#include <ObjectPolicy.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>


// 0549069378
namespace eng
{
    Object*     Object::myFocusedObject = 0;
    Object*     Object::myHoveredObject = 0;

    sf::Uint32  Object::NextId = 0;

    Object::Object(const sf::String& name)
        :   sf::Drawable(),
            myName(name),
            myParent(0),
            myZValue(0),
            myVisible(true),
            myEnabled(true),
            myFocusable(true),
            myUpdateCallback()
    {
        myId = NextId;
        ++NextId;
    }

    void    Object::SetName(const sf::String& name)
    {
        myName = name;
    }

    const sf::String&   Object::GetName() const
    {
        return myName;
    }

    const sf::Uint32    Object::GetId() const
    {
        return myId;
    }

    void    Object::SetZValue(sf::Uint8 zvalue)
    {
        myZValue = zvalue;
    }

    sf::Uint8   Object::GetZValue() const
    {
        return myZValue;
    }

    void    Object::SetVisible(bool visible)
    {
        myVisible = visible;
    }

    bool    Object::IsVisible() const
    {
        return myVisible;
    }

    void    Object::SetEnabled(bool enabled)
    {
        myEnabled = enabled;
    }

    bool    Object::IsEnabled() const
    {
        return myEnabled;
    }

    void    Object::SetFocusable(bool focusable)
    {
        myFocusable = focusable;
    }

    bool    Object::IsFocusable() const
    {
        return myFocusable;
    }

    bool    Object::IsHovered() const
    {
        return (myHoveredObject == this);
    }

    void    Object::SetParent(Object* parent)
    {
        myParent = parent;
    }

    Object* Object::GetParent() const
    {
        return myParent;
    }

    void    Object::Add(Object* object)
    {
        if (!object)
            return;

        for (Objects::const_iterator it = myChildren.begin(); it != myChildren.end(); ++it)
            if (*it == object)
                return;

        myChildren.push_back(object);
        object->SetParent(this);

        OnAdded(object);
    }

    void    Object::Remove(Object* object)
    {
        if (!object)
            return;

        for (Objects::iterator it = myChildren.begin(); it != myChildren.end(); ++it)
            if (*it == object)
            {
                object->SetParent(0);
                myChildren.erase(it);
                return;
            }

        OnRemoved(object);
    }

    void    Object::Clear()
    {
        myChildren.clear();
    }

    void    Object::AddPolicy(ObjectPolicy* policy)
    {
        if (!policy)
            return;

        for (Policies::const_iterator it = myPolicies.begin(); it != myPolicies.end(); ++it)
            if (*it == policy)
                return;

        myPolicies.push_back(policy);
    }

    Objects& Object::GetChildren()
    {
        return myChildren;
    }

    void    Object::SetSize(const sf::Vector2f& size)
    {
        mySize = size;

        if (myResizeCallback && luabind::type(myResizeCallback) == LUA_TFUNCTION)
            luabind::call_function<void>(myResizeCallback);
    }

    void    Object::SetSize(float width, float height)
    {
        SetSize(sf::Vector2f(width, height));
    }

    const sf::Vector2f& Object::GetSize() const
    {
        return mySize;
    }

    sf::Vector2f    Object::GetAbsolutePosition() const
    {
        sf::Vector2f absPos = GetPosition();
        Object* p = GetParent();

        while (p)
        {
            const sf::Vector2f& pos = p->GetPosition();
            absPos.x += pos.x;
            absPos.y += pos.y;

            p = p->GetParent();
        }
        return absPos;
    }

    void    Object::OnReceiveEvent(const sf::Event& event)
    {
        if (!IsEnabled())
            return;

        if (myEventCallback && luabind::type(myEventCallback) == LUA_TFUNCTION)
            luabind::call_function<void>(myEventCallback, event);

        // send the event to object's policies
        size_t max = myPolicies.size();
        for (size_t it = 0; it != max; ++it)
        {
            ObjectPolicy* policy = myPolicies[it];
            policy->OnEvent(event);
        }
    }

    void    Object::SetResizeCallback(const luabind::object& callback)
    {
        myResizeCallback = callback;
    }

    void    Object::SetUpdateCallback(const luabind::object& callback)
    {
        myUpdateCallback = callback;
    }

    void    Object::SetEventCallback(const luabind::object& callback)
    {
        myEventCallback = callback;
    }

    static bool    OrderByZOrder(Object* obj1, Object* obj2)
    {
        return obj1->GetZValue() < obj2->GetZValue();
    }

    void    Object::Update(float elapsedTime)
    {
        if (myUpdateCallback && luabind::type(myUpdateCallback) == LUA_TFUNCTION)
            luabind::call_function<void>(myUpdateCallback);

        // on trie d'abord notre liste d'objets
        std::sort(myChildren.begin(), myChildren.end(), &OrderByZOrder);

        size_t max = myChildren.size();
        for (size_t i = 0; i < max; ++i)
        {
            Object* child = myChildren[i];

            if (child)
                if (child->IsEnabled())
                    child->Update(elapsedTime);
        }
    }

    void    Object::Render(sf::RenderTarget& target, sf::Renderer& renderer) const
    {
        if (!IsVisible())
            return;

        renderer.SetColor(GetColor());
        renderer.SetTexture(0);

        renderer.Begin(sf::Renderer::TriangleStrip);
        renderer.AddVertex(0, 0);
        renderer.AddVertex(mySize.x, 0);
        renderer.AddVertex(0, mySize.y);
        renderer.AddVertex(mySize.x, mySize.y);
        renderer.End();

        size_t max = myChildren.size();
        for (size_t i = 0; i < max; ++i)
        {
            Object* child = myChildren[i];

            if (child->IsVisible())
                target.Draw(*child);
        }
    }

    Object* Object::FindObjectByName(const sf::String& name)
    {
        size_t max = myChildren.size();
        for (size_t it = 0; it != max; ++it)
        {
            Object* child = myChildren[it];

            if (child->GetName() == name)
                return child;
        }
        return 0;
    }
}
