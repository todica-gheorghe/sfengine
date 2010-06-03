#ifndef RESOURCEMANAGER_HPP_INCLUDED
#define RESOURCEMANAGER_HPP_INCLUDED

#include <sfengine/Singleton.hpp>
#include <SFML/System/String.hpp>

#include <vector>
#include <map>
#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>

// RESOURCES definitions --------------------
#include <sfengine/Package.hpp>
typedef boost::shared_ptr<Package>          PackagePtr;

#include <SFML/Graphics/Image.hpp>
typedef boost::shared_ptr<sf::Image>        ImagePtr;

#include <SFML/Audio.hpp>
typedef boost::shared_ptr<sf::SoundBuffer>  SoundPtr;

// ------------------------------------------

namespace eng
{
    class ResourceManager : public Singleton<ResourceManager>
    {
        public:
            friend ResourceManager* Singleton<ResourceManager>::Get();
            friend void             Singleton<ResourceManager>::Kill();

            typedef std::map<sf::String, boost::any>    Resources;

            template<typename T>
            boost::shared_ptr<T>  GetResource(const sf::String& filename)
            {
                if (myResources.find(filename) == myResources.end())
                {
                    T* res = Load<T>(filename);
                    myResources[filename] = boost::shared_ptr<T>(res);
                }
                return boost::any_cast<boost::shared_ptr<T> >(myResources[filename]);
            }

            Package*    CreatePackage(const sf::String& filename, const sf::String& directory)
            {
                Package* pack = new Package(filename, directory);
                myResources[filename] = boost::shared_ptr<Package>(pack);
                return pack;
            }

            template<typename T>
            T*  Load(const sf::String& filename);

            virtual ~ResourceManager();

        protected:
            ResourceManager();

        private:
            Resources               myResources;

    };
}

#endif // RESOURCEMANAGER_HPP_INCLUDED
