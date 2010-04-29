#ifndef PACKAGE_HPP_INCLUDED
#define PACKAGE_HPP_INCLUDED

#include <SFML/System/String.hpp>
#include <vector>
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
        ~Package();

        bool                    Create(const std::vector<sf::String>& fileList, const sf::String& filename);
        bool                    Read(const sf::String& filename);

        char*                   GetFile(const sf::String& filename);
        sf::Uint32              GetFileSize(const sf::String& filename);


    private:
        sf::String              myFilename;
        PackHeader              myHeader;
        std::vector<PackEntry>  myEntries;
        char*                   myBuffer;


};

#endif // PACKAGE_HPP_INCLUDED
