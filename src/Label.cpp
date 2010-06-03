
#include <Label.hpp>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Renderer.hpp>
#include <SFML/System/Randomizer.hpp>

#include <Utils.hpp>
#include <cstring>
#include <iostream>

namespace eng
{
    Label::Label(const sf::String& text, unsigned int size)
        :   Object("Label")
    {
        SetText(text);
        SetTextSize(size);
        SetColor(sf::Color(0, 0, 0, 0));
    }

    const sf::Text&     Label::GetSFMLText() const
    {
        return myText;
    }

    sf::Color   Label::ParseColor(const sf::String& strColor)
    {
        sf::Uint8 i = 0;
        sf::Color col;

        char *str = strdup(strColor.ToAnsiString().c_str());
        char *tok = strtok(str,",");
        while (tok != NULL)
        {
            sf::Uint32 value;
            value = Utils::GetFromString(tok, 255);

            if (i == 0)
                col.r = value;
            else if (i == 1)
                col.g = value;
            else if (i == 2)
                col.b = value;
            else if (i == 3)
                col.a = value;
            ++i;

            tok = strtok(NULL, ",");
        }

        delete str;

        return col;
    }

    sf::String  Label::ParseText(const sf::String& text)
    {
        sf::Uint32 i = 0, pos = 0;
        bool isColor = false;

        sf::String newText, bufferColor;


        while (text[i])
        {
            if (text[i] == '<' && !isColor)
            {
                isColor = true;
            }
            else if (text[i] == '<' && isColor)
            {
                if (i - 1 >= 0)
                {
                    if (text[i - 1] == '<')
                    {
                        isColor = false;
                        ++pos;
                        newText += '<';
                    }
                }
            }
            else if (text[i] == '>' && isColor)
            {
                ++pos;
                myColors[pos] = ParseColor(bufferColor);
                bufferColor = "";
                newText += '\x01';
                isColor = false;
            }
            else if (isColor)
            {
                bufferColor += text[i];
            }
            else
            {
                pos += 1;
                newText += text[i];
                isColor = false;
            }
            ++i;
        }
        return newText;
    }

    void    Label::SetText(const sf::String& text)
    {
        const sf::String& newText = ParseText(text);
        myText.SetString(newText);
        const sf::FloatRect& rect = myText.GetRect();
        SetSize(sf::Vector2f(rect.Width, rect.Height));
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
        const sf::FloatRect& rect = myText.GetRect();
        SetSize(sf::Vector2f(rect.Width, rect.Height));
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
