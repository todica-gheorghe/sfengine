## Window creation ##

sfengine is based on SFML multimedia library, so the window creation is very easy.
```
-- We create the window
local window = WindowManager:Get()
window:Create(VideoMode(800, 600), "My first window", Style.Close)

-- Main loop
while (window:IsOpened()) do

    -- Get the current event
    local event = Event()
    while (window:GetEvent(event)) do
        if (event.Type == Event.KeyPressed) then
           window:Close()
        end
    end

    -- Clear the window
    window:Clear(Color(0, 0, 0))

    window:Display()
end
```

The above syntax is like SFML C++ methods, without namespaces.<br />
We get the window from the WindowManager wich inherits from sf::RenderWindow.

Execute this code into the sfengine.