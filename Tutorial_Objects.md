## Scene management ##

The engine offers a mecanism of objects and scenes for the developers.

An **object** is a rectangular drawable with position and size, and can add children to itself.<br />
A **scene** is an object with the window size.

We create a new script in order to draw an object on screen :

```
local window = WindowManager.Get()
window:Create(VideoMode(800, 600), "Scene management", Style.Close)

local sceneManager = SceneManager.Get()
local scene = Scene("FirstScene")
scene:SetColor(Color(123, 0, 123))

local object = Object("FirstObject")
object:SetSize(200, 100)
object:Move((window:GetWidth() - object:GetSize().x) / 2, (window:GetHeight() - object:GetSize().y) / 2)

scene:Add(object)
sceneManager:AddScene(scene)

-- Main loop
while (window:IsOpened()) do

    -- Get the current event
    local event = Event()
    while (window:GetEvent(event)) do
        if (event.Type == Event.KeyPressed) then
           window:Close()
        end
        sceneManager:GetEvent(event)
    end

    -- Clear the window
    window:Clear(Color(0, 0, 0))

    sceneManager:Display()

    window:Display()
end

```

Execute the script, you should obtain this :

![http://betadine.clanfree.net/sfui/scene.png](http://betadine.clanfree.net/sfui/scene.png)