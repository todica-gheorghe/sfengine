#ifndef ANIMATEDOBJECT_HPP_INCLUDED
#define ANIMATEDOBJECT_HPP_INCLUDED

#include <Object.hpp>
#include <ResourceManager.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Color.hpp>

#include <vector>

namespace eng
{
    class Animation
    {
        public :

            struct Frame
            {
                sf::Color   color;

                void    SetColor(const sf::Color& c)
                {
                    color = c;
                }


                sf::IntRect rect;
            };

            Animation(const ImagePtr& ptr);
            Animation(const sf::String& str);

            void            Clear();

            void            AddFrame(const sf::IntRect& rect, const sf::Color& color = sf::Color(255, 255, 255));

            void            SetImage(const ImagePtr& imagePtr);
            const ImagePtr& GetImage() const;

            sf::Uint8       GetSize() const;

            Frame*          GetFrame(size_t n);

            Frame&          operator [](size_t n);

        private:
            std::vector<Frame>  myFrames;
            ImagePtr            myImage;
    };


    class AnimatedObject : public Object
    {
        public:
            AnimatedObject(AnimatedObject* object);
            AnimatedObject(const sf::String& image);
            AnimatedObject(Animation* anim, bool loop, float frameTime);

            void        SetAnimation(Animation* anim);
            Animation*  GetAnimation() const;

            void        SetCurrentFrame(int index);
            int         GetCurrentFrame() const;

            void        SetFrameTime(float time);
            float       GetFrameTime() const;

            void        SetLoop(bool loop);
            bool        IsLoop() const;

            void        Pause();
            bool        IsPaused() const;

            void        Play();

            void        Stop();
            bool        IsStoped() const;

            void        Update(float elapsedTime);

        protected:
            virtual void    Render(sf::RenderTarget& target, sf::Renderer& renderer) const;

        private:
            Animation*      myAnimation;
            sf::Sprite      mySprite;

            int             myCurrentFrame;
            float           myFrameTime, myElapsedTime;

            bool            myPaused;
            bool            myLoop;


    };

}

#endif // ANIMATEDOBJECT_HPP_INCLUDED
