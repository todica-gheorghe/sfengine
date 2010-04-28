
#include <SoundManager.hpp>

#include <SFML/Audio/Sound.hpp>
#include <iostream>

namespace eng
{
    template<>
    SoundManager*   Singleton<SoundManager>::myInstance = 0;

    SoundManager::SoundManager()
    {

    }

    SoundManager::~SoundManager()
    {
    }

    sf::Sound   SoundManager::GetSound(const SoundPtr& buffer)
    {
        sf::Sound sound;
        sound.SetBuffer(*buffer);
        return sound;
    }

    sf::Sound    SoundManager::GetSound(const sf::String& sound)
    {
        return GetSound(ResourceManager::Get()->GetResource<sf::SoundBuffer>(sound));
    }


}
