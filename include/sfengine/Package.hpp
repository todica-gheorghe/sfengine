#ifndef PACKAGE_HPP_INCLUDED
#define PACKAGE_HPP_INCLUDED

#include <SFML/System/String.hpp>
#include <vector>
#include <luabind/object.hpp>

struct PackHeader
{
    char        uniqueID[5];
    char        version[3];
    sf::Uint8   nbFiles;
};

struct PackEntry
{
    char        name[300];
    sf::Uint32  size;
    sf::Uint32  offset;
};

class Package
{
    public:

        Package();
        Package(const sf::String& filename, const sf::String& directory);

        ~Package();

        char*                   GetFile(const sf::String& filename);
        sf::Uint32              GetFileSize(const sf::String& filename);


    private:

        bool                    Read(const sf::String& filename);

        bool                    Create(const sf::String&, const sf::String&);

        sf::String              myFilename;
        PackHeader              myHeader;
        std::vector<PackEntry>  myEntries;
        char*                   myBuffer;


};

#endif // PACKAGE_HPP_INCLUDED
