

#include <SFML/Graphics.hpp>
#include <Object.hpp>
#include <luabind/object.hpp>

int main(int ac, char **av)
{
    eng::Object obj("name");
    sf::RenderWindow win(sf::VideoMode(800, 600), "Object");

    return 0;
}
