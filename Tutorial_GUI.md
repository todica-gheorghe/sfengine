# [The UI scene](http://code.google.com/p/sfengine/source/browse/trunk/include/UserInterface.hpp) #

sfengine provides a scene for gui integration. The scene manages events, focus, and hierarchy of widgets.

```
local sceneManager = SceneManager.Get()
local ui = UIManager.Get()

sceneManager:AddScene(ui)
```

# Widgets #


## [Label](http://code.google.com/p/sfengine/source/browse/trunk/include/sfengine/Label.hpp) ##

Label is a class wich prints a message on screen.
```
local label = Label("My first label", 15)
label:SetColor(Color(255, 255, 255))
label:SetTextColor(Color(0, 0, 0))
```

You can use RGB multicolor in each label you create, like this :
```
label:SetText("<0,0,0>Hello <255,0,0>World !")
```

## [TextInput](http://code.google.com/p/sfengine/source/browse/trunk/include/sfengine/TextInput.hpp) ##

TextInput is the base class for listening user text input.
It manages text selection with keyboard and mouse.

```
local textinput = TextInput("", 12)
textinput:SetSelectionColor(Color(255, 0, 0, 123))
textinput:SetMaxLength(8)
```