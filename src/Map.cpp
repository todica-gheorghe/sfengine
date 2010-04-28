
#include <Map.hpp>
#include <Utils.hpp>

#include <iostream>
#include <algorithm>
#include <Utils.hpp>
#include <xml/tinyxml.h>

#include <WindowManager.hpp>

// Layer class

Layer::Layer(const sf::Vector2i& size)
    :   eng::Object("Layer"),
        myCollidable(false),
        mySize(size)
{
    SetColor(sf::Color(0, 0, 0, 0));
}

Layer::Layer(Layer* copy)
    :   eng::Object("Layer"),
        mySize(copy->mySize)
{
    myCollidable = copy->myCollidable;
    myTiles = copy->myTiles;

    SetColor(sf::Color(0, 0, 0, 0));
}

void    Layer::SetCollidable(bool collidable)
{
    myCollidable = collidable;
}

bool    Layer::IsCollidable() const
{
    return myCollidable;
}

void    Layer::Reset(eng::AnimatedObject* prototype)
{
    for (int j = 0; j < mySize.y; ++j)
        for (int i = 0; i < mySize.x; ++i)
        {
            eng::AnimatedObject* tile = new eng::AnimatedObject(prototype->GetAnimation(), false, 0);
            tile->SetPosition(i * prototype->GetSize().x, j * prototype->GetSize().y);
            SetTile(sf::Vector2i(i, j), tile);
        }

    SetSize(mySize.x * prototype->GetSize().x, mySize.y * prototype->GetSize().y);
}

void    Layer::SetTile(const sf::Vector2i& position, eng::AnimatedObject* object)
{
    if (!object)
        return;

    sf::String pos = eng::Utils::ToString(position.x) + sf::String("_") + eng::Utils::ToString(position.y);
    if (myTiles.find(pos) != myTiles.end())
    {
        Remove(myTiles[pos]);
    }

    myTiles[pos] = object;
    Add(object);
}

void    Layer::RemoveTile(const sf::Vector2i& position)
{
    sf::String pos = eng::Utils::ToString(position.x) + sf::String("_") + eng::Utils::ToString(position.y);
    eng::AnimatedObject* object = GetTile(position);

    if (object)
    {
        Remove(object);
        myTiles.erase(pos);
    }
}

eng::AnimatedObject*    Layer::GetTile(const sf::Vector2i& position)
{
    sf::String pos = eng::Utils::ToString(position.x) + sf::String("_") + eng::Utils::ToString(position.y);
    if (myTiles.find(pos) == myTiles.end())
        return 0;

    return myTiles[pos];
}



// Map class

Map::Map(const sf::Vector2i& size)
    :   eng::Scene("Map"),
        mySize(size)
{
    SetSize(size.x * MAP_BLOCK_SIZE, size.y * MAP_BLOCK_SIZE);
    SetColor(sf::Color(123, 123, 0));
}

void    Map::Resize(const sf::Vector2i& size)
{
    mySize = size;
    SetSize(size.x * MAP_BLOCK_SIZE, size.y * MAP_BLOCK_SIZE);
}

void    Map::LoadFromFile(const sf::String& filename)
{
    TiXmlDocument doc;
    if (!doc.LoadFile(filename.ToAnsiString().c_str()))
    {
        std::cout << "Map file \"" << filename.ToAnsiString() << "\" not found." << std::endl;
        return;
    }

    Clear();
    myLayers.clear();

    TiXmlElement* map = doc.FirstChildElement("map");
    Resize(sf::Vector2i(eng::Utils::GetFromString<int>(sf::String(map->Attribute("width")), 20),
                        eng::Utils::GetFromString<int>(sf::String(map->Attribute("height")), 20)));

    TiXmlElement* layer = map->FirstChildElement("layer");
    while (layer)
    {
        Layer* l = new Layer(sf::Vector2i(eng::Utils::GetFromString<int>(sf::String(layer->Attribute("width")), 1),
                                          eng::Utils::GetFromString<int>(sf::String(layer->Attribute("height")), 1)));

        if (layer->Attribute("tile"))
        {
            eng::AnimatedObject* proto = new eng::AnimatedObject(layer->Attribute("tile"));
            l->Reset(proto);
            delete proto;
        }

        if (layer->Attribute("x"))
        {
            l->SetX(MAP_BLOCK_SIZE * eng::Utils::GetFromString<int>(sf::String(layer->Attribute("x")), 0));
        }
        if (layer->Attribute("y"))
        {
            l->SetY(MAP_BLOCK_SIZE * eng::Utils::GetFromString<int>(sf::String(layer->Attribute("y")), 0));
        }

        if (sf::String(layer->Attribute("collidable")) == sf::String("true"))
        {
            l->SetCollidable(true);
        }
        else
        {
            l->SetCollidable(false);
        }

        AddLayer(l);

        TiXmlElement* tile = layer->FirstChildElement("tile");
        while (tile)
        {
            eng::AnimatedObject* tileSprite = new eng::AnimatedObject(sf::String(tile->Attribute("src")));
            tileSprite->SetZValue(1);

            sf::Vector2i tilePos(eng::Utils::GetFromString<int>(sf::String(tile->Attribute("x")), 0),
                                 eng::Utils::GetFromString<int>(sf::String(tile->Attribute("y")), 0));
            l->SetTile(tilePos, tileSprite);
            tileSprite->SetPosition(tilePos.x * MAP_BLOCK_SIZE, tilePos.y * MAP_BLOCK_SIZE);

            tile = tile->NextSiblingElement("tile");
        }


        layer = layer->NextSiblingElement("layer");
    }




}

void    Map::AddLayer(Layer* layer)
{
    if (layer)
    {
        myLayers.push_back(layer);
        Add(layer);
    }
}

const sf::Vector2i&    Map::GetMapSize() const
{
    return mySize;
}

int     Map::GetNbLayers() const
{
    return myLayers.size();
}

Layer*  Map::GetLayer(int layer) const
{
    return myLayers[layer];
}

void    Map::RemoveLayer(Layer* layer)
{
    if (!layer)
        return;

    for (Layers::iterator it = myLayers.begin(); it != myLayers.end(); ++it)
    {
        if (*it == layer)
        {
            myLayers.erase(it);
            return;
        }
    }
}
