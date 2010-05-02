#ifndef _SCRIPTMANAGER_HPP
#define	_SCRIPTMANAGER_HPP

#include <Singleton.hpp>
#include <SFML/System/String.hpp>

extern "C"
{
    #include <lua.h>
    #include <lualib.h>
}

#include <luabind/luabind.hpp>

#include <SFML/System/Thread.hpp>
#include <boost/thread/thread.hpp>

namespace eng
{
    class ScriptManager : public Singleton<ScriptManager>
    {
        public:
            friend ScriptManager*       Singleton<ScriptManager>::Get();
            friend void                 Singleton<ScriptManager>::Kill();

            lua_State*                  GetLuaState() const;

            void                        Run(const sf::String& pack, const sf::String& script);
            void                        Run(const sf::String& script);

            virtual ~ScriptManager();

        protected:
            ScriptManager();

        private:
            lua_State                   *myState;


    };
}
#endif	/* _SCRIPTMANAGER_HPP */

