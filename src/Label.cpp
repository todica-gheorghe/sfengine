
#include <Label.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Renderer.hpp>

namespace eng
{
    Label::Label(const sf::String& text, unsigned int size)
        :   Object("Label")
    {
        SetText(text);
        SetTextSize(size);
        SetColor(sf::Color(0, 0, 0, 0));
    }

    void    Label::SetText(const sf::String& text)
    {
        myText.SetString(text);
        SetSize(myText.GetRect().GetSize());
    }

    const sf::String&   Label::GetText() const
    {
        return myText.GetString();
    }

    void    Label::SetFont(const sf::Font& font)
    {
        myText.SetFont(font);
    }

    const sf::Font& Label::GetFont() const
    {
        return myText.GetFont();
    }

    void    Label::SetTextStyle(unsigned int style)
    {
        myText.SetStyle(style);
    }

    unsigned int    Label::GetTextStyle() const
    {
        return myText.GetStyle();
    }

    void    Label::SetTextSize(unsigned int size)
    {
        myText.SetCharacterSize(size);
        SetSize(myText.GetRect().GetSize());
    }

    unsigned int    Label::GetTextSize() const
    {
        return myText.GetCharacterSize();
    }

    void    Label::SetTextColor(const sf::Color& color)
    {
        myText.SetColor(color);
    }

    const sf::Color&    Label::GetTextColor() const
    {
        return myText.GetColor();
    }

    sf::FloatRect   Label::GetRect(bool relative)
    {
        if (relative)
            return myText.GetRect();
        sf::Vector2f absPos = GetAbsolutePosition();
        return sf::FloatRect(absPos.x, absPos.y, GetSize().x, GetSize().y);
    }

    void    Label::Render(sf::RenderTarget& target, sf::Renderer& renderer) const
    {
        Object::Render(target, renderer);

        renderer.SetColor(GetTextColor());
        target.Draw(myText);
    }

}
