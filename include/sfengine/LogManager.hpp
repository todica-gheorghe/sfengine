#ifndef _LOGMANAGER_HPP
#define	_LOGMANAGER_HPP

#include <sfengine/Singleton.hpp>

#include <SFML/System/String.hpp>
#include <fstream>
#include <iostream>

namespace eng
{
    class LogManager : public Singleton<LogManager>
    {
        public:
            friend LogManager*  Singleton<LogManager>::Get();
            friend void         Singleton<LogManager>::Kill();

            void                SetLogFile(const sf::String& logFile);

            void                Log(const sf::String& message);
            void                Error(const sf::String& message);
            void                Warning(const sf::String& message);

            virtual ~LogManager();

        protected:

            LogManager();

        private:
            std::ofstream       myLogFile;

    };
}

#endif	/* _LOGMANAGER_HPP */

