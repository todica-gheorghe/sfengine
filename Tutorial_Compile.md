# Compilation #

sfengine use CMake cross-plateform open-source build system.

First, [check-out the svn repository](http://code.google.com/p/sfengine/source/checkout) to download source.<br />
Then you have to download two dependencies : [Boost](http://www.boost.org/) 1.41.0 or above, and [SFML 2.0](http://sfml.svn.sourceforge.net/viewvc/sfml/branches/sfml2.tar.gz?view=tar) snapshot.

## Windows ##

  * [Download CMake Win32 installer](http://www.cmake.org/cmake/resources/software.html) and install
  * Launch cmake-gui. In the "Where is the source code" box, type the sfengine root directory.
  * CMake have to find SFML dependency. It uses macros to define paths :
    * SFML\_INCLUDEDIR / SFML\_LIBRARYDIR
> > You can define them with "Add entry" button.
  * Press Configure button and choose your target compiler.
  * You now just have to go to the build directory and open your solution or project and compile it !

## Unix ##

  * Download CMake using
```
sudo apt-get install cmake
```

> or using [this link](http://www.cmake.org/cmake/resources/software.html)
  * Goto your sfengine root path, and generate cmake files.
```
cd sfengine/
cmake . 
```
  * Then compile the library using the generated Makefile
```
make
```

# Your first project #

Now we have our precompiled library, we create a new project :<br />
_**main.cpp**_
```
#include <sfengine/ScriptManager.hpp>

int    main(int ac, char **av)
{
    eng::ScriptManager::Get()->Run("main.lua")
    return 0;
}
```
_**main.lua**_
```
print("LUA script executed.")
```

Add these include paths to your project

```
boost_1_41_0/
sfengine/include
sfengine/extlibs/luabind
sfengine/extlibs/lua/src
sfengine/extlibs/tinyxml/include
sfml2/include
```

You have to setup the linker correctly :
```
sfengine-s
sfml-audio-s
sfml-network-s
sfml-graphics-s
sfml-window-s
sfml-system-s
boost-filesystem (or like this)
boost-system
```

Try to compile (if failed, post an issue) and run.