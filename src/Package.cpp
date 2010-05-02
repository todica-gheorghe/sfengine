
#include <Package.hpp>

#include <fstream>
#include <iostream>
#include <cstring>

#include <boost/filesystem.hpp>

Package::Package()
    :   myBuffer(0)
{

}

Package::Package(const sf::String& filename, const sf::String& directory)
    :   myBuffer(0)
{
    Create(filename, directory);
    Read(filename);
}

Package::~Package()
{
    delete myBuffer;
}

bool    Package::Create(const sf::String& filename, const sf::String& directory)
{
    // Create the file list from the directory (using boost::filesystem)
    if (!boost::filesystem::exists(directory.ToAnsiString()))
        return false;

    std::vector<std::string> fileList;

    boost::filesystem::directory_iterator end;
    for (boost::filesystem::directory_iterator it(directory.ToAnsiString()); it != end; ++it)
    {
        if (!boost::filesystem::is_directory(it->status()))
        {
            fileList.push_back((boost::filesystem::path(directory.ToAnsiString()) / it->filename()).string());
        }
    }

    PackEntry   entry;
    std::ifstream in;
    std::ofstream out;
    char buffer[1];


    // HEADER
    memset(&myHeader, 0, sizeof(myHeader));
    memcpy(myHeader.uniqueID, "PACKB", 5);
    memcpy(myHeader.version, "0.1", 3);
    myHeader.nbFiles = fileList.size();

    // FILE LIST
    for (sf::Uint8 i = 0; i < fileList.size(); ++i)
    {
        std::string str = fileList[i];
        in.open(str.c_str(), std::ifstream::in | std::ifstream::binary);
        if (in.is_open())
        {
            memset(&entry, 0, sizeof(PackEntry));

            const std::string entryName = boost::filesystem::path(str).filename();
            memcpy(entry.name, entryName.c_str(), strlen(entryName.c_str()));

            in.seekg(0, std::ios::end);
            entry.size = in.tellg();
            entry.offset = 0;
            in.close();
            myEntries.push_back(entry);
        }
        else
        {
            std::cerr << "Unable to open \"" << str << "\" file." << std::endl;
            return false;
        }
    }

    // UPDATE FILE OFFSETS
    sf::Uint32 actualOffset = sizeof(PackHeader) + myHeader.nbFiles * sizeof(PackEntry);
    for (sf::Uint8 i = 0; i < fileList.size(); ++i)
    {
        myEntries[i].offset = actualOffset;
        actualOffset += myEntries[i].size;
    }

    // WRITE PKG FILE
    out.open(filename.ToAnsiString().c_str(), std::ofstream::out | std::ofstream::binary);
    out.write(reinterpret_cast<char*>(&myHeader), sizeof(PackHeader));

    for (sf::Uint8 i = 0; i < fileList.size(); ++i)
    {
        out.write(reinterpret_cast<char*>(&myEntries[i]), sizeof(PackEntry));
    }

    for (sf::Uint8 i = 0; i < fileList.size(); ++i)
    {
        in.open(fileList[i].c_str(), std::ifstream::in | std::ifstream::binary);
        if (in.is_open())
        {
            in.seekg(0, std::ios::beg);
            while (in.read(buffer, 1))
            {
                *buffer += 3;
                out.write(buffer, 1);
            }
            in.close();
        }
        in.clear();
    }

    out.close();

    myFilename = filename;
    myEntries.clear();

    return true;
}

bool    Package::Read(const sf::String& filename)
{
    std::ifstream in;
    PackEntry entry;

    memset(&myHeader, 0, sizeof(myHeader));

    in.open(filename.ToAnsiString().c_str(), std::ifstream::in | std::ifstream::binary);

    if (in.is_open())
    {
        in.seekg(0, std::ios::beg);
        in.read((char*)(&myHeader), sizeof(PackHeader));

        for (sf::Uint8 i = 0; i < myHeader.nbFiles; ++i)
        {
            in.read((char*)(&entry), sizeof(PackEntry));
            myEntries.push_back(entry);
        }

        myFilename = filename;
    }
    else
    {
        std::cerr << "Could not open \"" << filename.ToAnsiString() << "\"" << std::endl;
        return false;
    }

    in.close();
    return true;
}

char*   Package::GetFile(const sf::String& name)
{
    std::ifstream in;

    delete myBuffer;
    myBuffer = 0;

    for (sf::Uint8 i = 0; i < myHeader.nbFiles; ++i)
    {
        if (myEntries[i].name == name.ToAnsiString())
        {
            if (!(myBuffer = new char[myEntries[i].size]))
                return 0;

            in.open(myFilename.ToAnsiString().c_str(), std::ifstream::in | std::ifstream::binary);
            if (in.is_open())
            {
                in.seekg(myEntries[i].offset, std::ios::beg);
                in.read(myBuffer, myEntries[i].size);
                in.close();

                // decrypte les donnees
                for (sf::Uint32 j = 0; j < myEntries[i].size; ++j)
                {
                    myBuffer[j] -= 3;
                }

                return myBuffer;
            }
            else
            {
                std::cerr << "You must read the package file before using GetFile() method." << std::endl;
                return 0;
            }
        }
    }
    std::cerr << "Sorry, there is no \"" << name.ToAnsiString() << "\" in \"" << myFilename.ToAnsiString() << "\"." << std::endl;
    return 0;
}

sf::Uint32  Package::GetFileSize(const sf::String& name)
{
    for (sf::Uint8 i = 0; i < myHeader.nbFiles; ++i)
    {
        if (myEntries[i].name == name.ToAnsiString())
        {
            return myEntries[i].size;
        }
    }
    return 0;
}
