

#include <sfengine/LogManager.hpp>

namespace eng
{

    template<>
    LogManager* Singleton<LogManager>::myInstance = 0;

    LogManager::LogManager()
    {
        SetLogFile("engine.log");
    }

    LogManager::~LogManager()
    {
        myLogFile.close();
    }

    void    LogManager::SetLogFile(const sf::String& logFile)
    {
        myLogFile.open(logFile.ToAnsiString().c_str(), std::ios::out | std::ios::trunc);

        if (!myLogFile)
            std::cerr << "Impossible d'ouvrir le fichier " << logFile.ToAnsiString() << std::endl;
    }

    void    LogManager::Log(const sf::String& message)
    {
        myLogFile << message.ToAnsiString() << std::endl;
    }

    void    LogManager::Error(const sf::String& message)
    {
        myLogFile << "Error : " << message.ToAnsiString() << std::endl;
    }

    void    LogManager::Warning(const sf::String& message)
    {
        myLogFile << "Warning : " << message.ToAnsiString() << std::endl;
    }


}
