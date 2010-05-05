
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
        //target.Draw(myText);


        const sf::Font& font = myText.GetFont();
        const sf::String& string = myText.GetString();
        unsigned int characterSize = myText.GetCharacterSize();

        // No text or not font: nothing to render
        if (string.IsEmpty())
            return;

        // Bind the font texture
        renderer.SetTexture(&font.GetImage(characterSize));

        // Initialize the rendering coordinates
        float space       = static_cast<float>(font.GetGlyph(L' ', characterSize, false).Advance);
        float lineSpacing = static_cast<float>(font.GetLineSpacing(characterSize));
        float x = 0.f;
        float y = static_cast<float>(characterSize);

        // Note:
        // Here we use a Begin/End pair for each quad because
        // the font's texture may change in a call to GetGlyph

        // Draw one quad for each character
        sf::Uint32 prevChar = 0;
        for (std::size_t i = 0; i < string.GetSize(); ++i)
        {
            sf::Uint32 curChar = string[i];

            if (curChar == '\x01')
            {
                ++i;
                renderer.SetColor(const_cast<std::map<sf::Uint32, sf::Color>& >(myColors)[i]);
                curChar = string[i];
            }

            // Apply the kerning offset
            x += static_cast<float>(font.GetKerning(prevChar, curChar, characterSize));
            prevChar = curChar;

            // Handle special characters
            switch (curChar)
            {
                case L' ' :  x += space;              continue;
                case L'\t' : x += space * 4;          continue;
                case L'\n' : y += lineSpacing; x = 0; continue;
                case L'\v' : y += lineSpacing * 4;    continue;
            }

            // Extract the current glyph's description
            const sf::Glyph& curGlyph = font.GetGlyph(curChar, characterSize, false);
            int advance = curGlyph.Advance;
            const sf::IntRect&   rect     = curGlyph.Rectangle;
            const sf::FloatRect& coord    = curGlyph.TexCoords;

            // Draw a textured quad for the current character
            renderer.Begin(sf::Renderer::QuadList);
                renderer.AddVertex(x + rect.Left,    y + rect.Top,    coord.Left,  coord.Top);
                renderer.AddVertex(x + rect.Right,    y + rect.Top,    coord.Right, coord.Top);
                renderer.AddVertex(x + rect.Right, y + rect.Bottom, coord.Right, coord.Bottom);
                renderer.AddVertex(x + rect.Left, y + rect.Bottom, coord.Left,  coord.Bottom);
            renderer.End();

            // Advance to the next character
            x += advance;
        }

    }

}
