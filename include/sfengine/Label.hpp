
#ifndef LABEL_HPP_INCLUDED
#define	LABEL_HPP_INCLUDED

#include <sfengine/Object.hpp>
#include <SFML/Graphics/Text.hpp>

namespace eng
{
    class Label : public Object
    {
        public :
            Label(const sf::String& label, unsigned int size = 30);

            void                SetText(const sf::String& text);
            const sf::String&   GetText() const;

            const sf::Text&     GetSFMLText() const;

            void                SetFont(const sf::Font& font);
            const sf::Font&     GetFont() const;

            void                SetTextStyle(unsigned int style);
            unsigned int        GetTextStyle() const;

            void                SetTextSize(unsigned int size);
            unsigned int        GetTextSize() const;

            void                SetTextColor(const sf::Color& color);
            const sf::Color&    GetTextColor() const;

            sf::FloatRect       GetRect(bool relative = true);

        protected :
            virtual void        Render(sf::RenderTarget& target, sf::Renderer& renderer) const;

        private :
            sf::String          ParseText(const sf::String& text);
            sf::Color           ParseColor(const sf::String& color);

            void                AdjustSize();

            sf::Text            myText;

            std::map<sf::Uint32, sf::Color>   myColors;

    };

}


#endif	/* LABEL_HPP_INCLUDED */

