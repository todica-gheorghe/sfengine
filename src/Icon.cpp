

#include <Icon.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Renderer.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <iostream>

namespace eng
{
    Icon::Icon(const sf::String& image)
        :   eng::Object("Icon")
    {
        SetImage(image);
        SetColor(sf::Color(0, 0, 0, 0));
    }

    Icon::Icon(const ImagePtr& ptr)
        :   eng::Object("Icon")
    {
        SetImage(ptr);
        SetColor(sf::Color(0, 0, 0, 0));
    }

    void    Icon::SetImage(const sf::String& image, bool resize)
    {
        SetImage(ResourceManager::Get()->GetResource<sf::Image>(image), resize);
    }

    void    Icon::SetImage(const ImagePtr& ptr, bool resize)
    {
        myImage = ptr;

        SetSubRect(sf::IntRect(0, 0, ptr->GetWidth(), ptr->GetHeight()));

        if (resize)
            SetSize(ptr->GetWidth(), ptr->GetHeight());
    }

    void    Icon::SetSubRect(const sf::IntRect& subRect)
    {
        mySubRect = subRect;
    }

    const sf::IntRect&  Icon::GetSubRect() const
    {
        return mySubRect;
    }

    void    Icon::Render(sf::RenderTarget& target, sf::Renderer& renderer) const
    {
        Object::Render(target, renderer);

        if (myImage)
        {
            sf::Sprite spr;
            spr.SetImage(*myImage);
            spr.SetSubRect(mySubRect);
            spr.Resize(GetSize());

            renderer.SetColor(spr.GetColor());
            target.Draw(spr);
        }
    }
}
