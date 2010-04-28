

#include <ResourceManager.hpp>

namespace eng
{
    template<>
    ResourceManager*    Singleton<ResourceManager>::myInstance = 0;

    ResourceManager::ResourceManager()
    {

    }

    ResourceManager::~ResourceManager()
    {
        myResources.clear();
    }

    template<>
    sf::Image*  ResourceManager::Load<sf::Image>(const sf::String& filename)
    {
        sf::Image* img = new sf::Image();
        img->SetSmooth(false);
        if (!img->LoadFromFile(filename))
        {
            delete img;
            return 0;
        }
        return img;
    }

}
