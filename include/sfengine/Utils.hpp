#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

#include <sstream>
#include <SFML/System/String.hpp>

namespace eng
{
    class Utils
    {
        public:

            template<typename T>
            static sf::String ToString(const T& value)
            {
                std::ostringstream oss;
                oss << value;
                return sf::String(oss.str().c_str());
            }

            template<typename T>
            static T    GetFromString(const sf::String& str, T defaultValue)
            {
                T val;
                std::istringstream iss(str.ToAnsiString());
                if (!(iss >> val))
                    return defaultValue;
                return val;
            }

    };

}

#endif // UTILS_HPP_INCLUDED
