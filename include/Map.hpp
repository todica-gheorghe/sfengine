#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include <vector>
#include <Object.hpp>
#include <Scene.hpp>
#include <AnimatedObject.hpp>

#define MAP_LAYER_MAX   (4)
#define MAP_BLOCK_SIZE  (32)

class Layer : public eng::Object
{
    public:
        Layer(const sf::Vector2i& size);
        Layer(Layer* copy);

        void    SetCollidable(bool collidable);
        bool    IsCollidable() const;

        void    SetTile(const sf::Vector2i& position, eng::AnimatedObject* object);
        eng::AnimatedObject* GetTile(const sf::Vector2i& position);
        void    RemoveTile(const sf::Vector2i& position);

        void    Reset(eng::AnimatedObject* prototype);

    private:
        std::map<sf::String, eng::AnimatedObject*>    myTiles;
        bool            myCollidable;
        sf::Vector2i    mySize;

};

typedef std::vector<Layer*> Layers;

class Map : public eng::Scene
{
    public :
        Map(const sf::Vector2i& size);

        void    Resize(const sf::Vector2i& size);

        void    AddLayer(Layer* layer);
        Layer*  GetLayer(int layer) const;
        void    RemoveLayer(Layer* layer);

        const sf::Vector2i& GetMapSize() const;
        int     GetNbLayers() const;

        void    LoadFromFile(const sf::String& filename);

    protected:


    private :
        sf::Vector2i    mySize;
        Layers          myLayers;



};

#endif // MAP_HPP_INCLUDED
