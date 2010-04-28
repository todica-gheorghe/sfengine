
#include <AnimatedObject.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
// CLASSE Animation

#include <iostream>

namespace eng
{

    Animation::Animation(ImagePtr& image)
        :   myImage(image)
    {

    }

    Animation::Animation(const sf::String& image)
        :   myImage(ResourceManager::Get()->GetResource<sf::Image>(image))
    {

    }

    void    Animation::Clear()
    {
        myFrames.clear();
    }

    void    Animation::AddFrame(const sf::IntRect& rect, const sf::Color& color)
    {
        Frame fr;
        fr.color = color;
        fr.rect = rect;

        myFrames.push_back(fr);
    }

    void    Animation::SetImage(const ImagePtr& imagePtr)
    {
        myImage = imagePtr;
    }

    const ImagePtr& Animation::GetImage() const
    {
        return myImage;
    }

    sf::Uint8  Animation::GetSize() const
    {
        return myFrames.size();
    }

    Animation::Frame&   Animation::operator [](size_t n)
    {
        return myFrames[n];
    }


    Animation::Frame*   Animation::GetFrame(size_t n)
    {
        return &myFrames[n];
    }
    // ----------



    // CLASSE AnimatedObject
    AnimatedObject::AnimatedObject(AnimatedObject* object)
        :   Object("AnimatedObject"),
            myAnimation(object->GetAnimation()),
            myCurrentFrame(object->GetCurrentFrame()),
            myFrameTime(object->GetFrameTime()),
            myElapsedTime(object->myElapsedTime),
            myPaused(object->myPaused),
            myLoop(object->myLoop)
    {
        SetColor(sf::Color(0, 0, 0, 0));
    }

    AnimatedObject::AnimatedObject(const sf::String& image)
        :   Object("AnimatedObject"),
            myAnimation(0),
            myCurrentFrame(0),
            myFrameTime(0),
            myElapsedTime(0),
            myPaused(true),
            myLoop(false)
    {
        ImagePtr imgAnim = eng::ResourceManager::Get()->GetResource<sf::Image>(image);
        myAnimation = new Animation(imgAnim);
        myAnimation->AddFrame(sf::IntRect(0, 0, imgAnim->GetWidth(), imgAnim->GetHeight()));

        SetCurrentFrame(0);
        SetColor(sf::Color(0, 0, 0, 0));
    }

    AnimatedObject::AnimatedObject(Animation* anim, bool loop, float frameTime)
        :   Object("AnimatedObject"),
            myAnimation(anim),
            myCurrentFrame(0),
            myFrameTime(frameTime),
            myElapsedTime(0),
            myPaused(true),
            myLoop(loop)
    {
        SetCurrentFrame(0);
        SetColor(sf::Color(0, 0, 0, 0));
    }

    void    AnimatedObject::SetAnimation(Animation* anim)
    {
        if (anim == myAnimation)
            return;

        myAnimation = anim;
        SetCurrentFrame(0);
    }

    Animation*  AnimatedObject::GetAnimation() const
    {
        return myAnimation;
    }

    void    AnimatedObject::SetCurrentFrame(int index)
    {
        if (!myAnimation)
            return;
        if (!myAnimation->GetSize())
            return;
        if (index < 0)
            return;


        if (myAnimation->GetImage())
            mySprite.SetImage(*myAnimation->GetImage());
        mySprite.SetSubRect((*myAnimation)[index].rect);
        mySprite.SetColor((*myAnimation)[index].color);

        SetSize(mySprite.GetSize());

        myCurrentFrame = index;
    }

    int     AnimatedObject::GetCurrentFrame() const
    {
        return myCurrentFrame;
    }


    void    AnimatedObject::SetFrameTime(float time)
    {
        myFrameTime = time;
    }

    float   AnimatedObject::GetFrameTime() const
    {
        return myFrameTime;
    }

    void    AnimatedObject::SetLoop(bool loop)
    {
        myLoop = loop;
    }

    bool    AnimatedObject::IsLoop() const
    {
        return myLoop;
    }

    void    AnimatedObject::Pause()
    {
        myPaused = true;
    }

    void    AnimatedObject::Play()
    {
        myPaused = false;
    }

    bool    AnimatedObject::IsPaused() const
    {
        return myPaused;
    }

    void    AnimatedObject::Stop()
    {
        SetCurrentFrame(0);
        myElapsedTime = myFrameTime;
        myPaused = true;
    }

    bool    AnimatedObject::IsStoped() const
    {
        return (myPaused && (myCurrentFrame == 0) && (myElapsedTime == myFrameTime));
    }

    void    AnimatedObject::Update(float elapsedTime)
    {
        Object::Update(elapsedTime);

        if (myPaused || !myAnimation)
            return;

        myElapsedTime -= elapsedTime;

        if (myElapsedTime <= 0.f)
        {
            myElapsedTime = myFrameTime;

            if (myCurrentFrame + 1 < myAnimation->GetSize())
                ++myCurrentFrame;
            else
            {
                if (myLoop)
                    myCurrentFrame = 0;
                else
                    Stop();
            }

            SetCurrentFrame(myCurrentFrame);
        }
    }


    void    AnimatedObject::Render(sf::RenderTarget& target, sf::Renderer& renderer) const
    {
        Object::Render(target, renderer);

        renderer.SetColor(mySprite.GetColor());
        target.Draw(mySprite);
    }

}

// ----------
