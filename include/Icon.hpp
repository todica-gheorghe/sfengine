
#ifndef ICON_HPP_INCLUDED
#define	ICON_HPP_INCLUDED

#include <Object.hpp>
#include <SFML/Graphics/Image.hpp>

#include <ResourceManager.hpp>

namespace eng
{
    class Icon : public Object
    {
        public :
            Icon(const sf::String& img);
            Icon(const ImagePtr& ptr);

            void                    SetImage(const sf::String& img, bool resize = true);
            void                    SetImage(const ImagePtr& ptr, bool resize = true);

            void                    SetSubRect(const sf::IntRect& subRect);
            const sf::IntRect&      GetSubRect() const;

        protected :
            virtual void            Render(sf::RenderTarget& target, sf::Renderer& renderer) const;

        private :
            ImagePtr                myImage;
            sf::IntRect             mySubRect;

    };

}


#endif	/* ICON_HPP_INCLUDED */

