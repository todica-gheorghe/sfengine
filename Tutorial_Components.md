## [Object](http://code.google.com/p/sfengine/source/browse/trunk/include/Object.hpp) ##

Object class is the standard base class for drawable components.
You can use the frame loop on each object with OnUpdate() method :

```
local object = Object("grid")
object:SetColor(Color(255, 0, 0))
grid:OnUpdate(
    function (elapsedTime)
        print("new frame")
    end
)
```

## [Scene](http://code.google.com/p/sfengine/source/browse/trunk/include/Scene.hpp) ##

The scene class is like an Object but can also receive events.
```
local scene = Scene("map")
scene:OnEvent(
    function (event)
        print("received event")
    end
)
```

## [Icon](http://code.google.com/p/sfengine/source/browse/trunk/include/Icon.hpp) ##

Icon is a base class for drawing an image on screen.
```
local icon = Icon(ResourceManager.Get():GetImage("data/icon.png"))
icon:SetSize(100, 100)
```

## [AnimatedObject](http://code.google.com/p/sfengine/source/browse/trunk/include/AnimatedObject.hpp) ##

This class inherits from Object and play an Animation on screen.

```
local anim = Animation(ResourceManager.Get():GetImage(String("data/anim.png")))
anim:AddFrame(IntRect(0, 0, 32, 32), Color(255, 255, 255))

local animatedObject = AnimatedObject(anim, false, 0.2)
animatedObject:Play()
```