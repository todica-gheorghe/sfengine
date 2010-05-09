
#include <ScriptManager.hpp>

#include <LogManager.hpp>
#include <WindowManager.hpp>
#include <SceneManager.hpp>
#include <ResourceManager.hpp>

#include <AnimatedObject.hpp>
#include <UserInterface.hpp>
#include <Icon.hpp>
#include <Utils.hpp>
#include <Package.hpp>

#include <SFML/Graphics/View.hpp>
#include <boost/any.hpp>
#include <vector>
#include <xml/tinyxml.h>

#include <SFML/Network.hpp>

#include <SFML/OpenGL.hpp>

#include <luabind/operator.hpp>
#include <luabind/return_reference_to_policy.hpp>
#include <luabind/out_value_policy.hpp>
#include <luabind/dependency_policy.hpp>

namespace sf
{
    class KeyBind
    {

    };

    class StyleBind
    {

    };

    class SocketBind
    {

    };

    static const char* StringToChars(const sf::String& str)
    {
        return str.ToAnsiString().c_str();
    }

}

bool    TiXmlDocument::LoadFile()
{
    return LoadFile(TIXML_DEFAULT_ENCODING);
}


#include <SFML/Graphics.hpp>

sf::Shape   Shape_Line(float x1, float x2, float y1, float y2, float t, const sf::Color& col)
{
    return sf::Shape::Line(x1, x2, y1, y2, t, col, 0, sf::Color(0, 0, 0, 0));
}

sf::Shape   Shape_Rectangle(float x1, float x2, float y1, float y2, const sf::Color& col)
{
    return sf::Shape::Rectangle(x1, x2, y1, y2, col);
}

sf::Shape   Shape_Circle(float x, float y, float radius, const sf::Color& color)
{
    return sf::Shape::Circle(x, y, radius, color);
}

sf::Sound    Sound_Create(const char* name)
{
    sf::Sound sound;
    sound.SetBuffer(*eng::ResourceManager::Get()->GetResource<sf::SoundBuffer>(name));
    return sound;
}

namespace eng
{

    template<>
    ScriptManager*  Singleton<ScriptManager>::myInstance = 0;

    ScriptManager::ScriptManager()
    {
        myState = lua_open();

        luaL_openlibs(myState);
        luabind::open(myState);

        luabind::module(myState)
        [

            luabind::class_<sf::VideoMode>("VideoMode").def(luabind::constructor<int, int>()),

            luabind::class_<std::string>("StdString")
                .def(luabind::constructor<const char*>())
                .def("Get", &std::string::c_str),

            luabind::class_<sf::String>("String")
                .def(luabind::constructor<const char*>())
                .def("Get", &sf::StringToChars)
                .def(luabind::const_self == sf::String()),

            luabind::class_<sf::StyleBind>("Style")
                .enum_("Style")
                [
                    luabind::value("None", 0),
                    luabind::value("Titlebar", 1 << 0),
                    luabind::value("Resize", 1 << 1),
                    luabind::value("Close", 1 << 2),
                    luabind::value("Fullscreen", 1 << 3)
                ],

            luabind::class_<sf::KeyBind>("Key")
                .enum_("Key")
                [
                    luabind::value("A", 'a'),
                    luabind::value("B", 'b'),
                    luabind::value("C", 'c'),
                    luabind::value("D", 'd'),
                    luabind::value("E", 'e'),
                    luabind::value("F", 'f'),
                    luabind::value("G", 'g'),
                    luabind::value("H", 'h'),
                    luabind::value("I", 'i'),
                    luabind::value("J", 'j'),
                    luabind::value("K", 'k'),
                    luabind::value("L", 'l'),
                    luabind::value("M", 'm'),
                    luabind::value("N", 'n'),
                    luabind::value("O", 'o'),
                    luabind::value("P", 'p'),
                    luabind::value("Q", 'q'),
                    luabind::value("R", 'r'),
                    luabind::value("S", 's'),
                    luabind::value("T", 't'),
                    luabind::value("U", 'u'),
                    luabind::value("V", 'v'),
                    luabind::value("W", 'w'),
                    luabind::value("X", 'x'),
                    luabind::value("Y", 'y'),
                    luabind::value("Z", 'z'),
                    luabind::value("Num0", '0'),
                    luabind::value("Num1", '1'),
                    luabind::value("Num2", '2'),
                    luabind::value("Num3", '3'),
                    luabind::value("Num4", '4'),
                    luabind::value("Num5", '5'),
                    luabind::value("Num6", '6'),
                    luabind::value("Num7", '7'),
                    luabind::value("Num8", '8'),
                    luabind::value("Num9", '9'),
                    luabind::value("Escape", 256),
                    luabind::value("LControl", 257),
                    luabind::value("LShift", 258),
                    luabind::value("LAlt", 259),
                    luabind::value("LSystem", 260),
                    luabind::value("RControl", 261),
                    luabind::value("RShift", 262),
                    luabind::value("RAlt", 263),
                    luabind::value("RSystem", 264),
                    luabind::value("Menu", 265),
                    luabind::value("LBracket", 266),
                    luabind::value("RBracket", 267),
                    luabind::value("SemiColon", 268),
                    luabind::value("Coma", 269),
                    luabind::value("Period", 270),
                    luabind::value("Quote", 271),
                    luabind::value("Slash", 272),
                    luabind::value("BackSlash", 273),
                    luabind::value("Tilde", 274),
                    luabind::value("Equal", 275),
                    luabind::value("Dash", 276),
                    luabind::value("Space", 277),
                    luabind::value("Return", 278),
                    luabind::value("Back", 279),
                    luabind::value("Tab", 280),
                    luabind::value("PageUp", 281),
                    luabind::value("PageDown", 282),
                    luabind::value("End", 283),
                    luabind::value("Home", 284),
                    luabind::value("Insert", 285),
                    luabind::value("Delete", 286),
                    luabind::value("Add", 287),
                    luabind::value("Subtract", 288),
                    luabind::value("Multiply", 289),
                    luabind::value("Divide", 290),
                    luabind::value("Left", 291),
                    luabind::value("Right", 292),
                    luabind::value("Up", 293),
                    luabind::value("Down", 294),
                    luabind::value("Numpad0", 295),
                    luabind::value("Numpad1", 296),
                    luabind::value("Numpad2", 297),
                    luabind::value("Numpad3", 298),
                    luabind::value("Numpad4", 299),
                    luabind::value("Numpad5", 300),
                    luabind::value("Numpad6", 301),
                    luabind::value("Numpad7", 302),
                    luabind::value("Numpad8", 303),
                    luabind::value("Numpad9", 304),
                    luabind::value("F1", 305),
                    luabind::value("F2", 306),
                    luabind::value("F3", 307),
                    luabind::value("F4", 308),
                    luabind::value("F5", 309),
                    luabind::value("F6", 310),
                    luabind::value("F7", 311),
                    luabind::value("F8", 312),
                    luabind::value("F9", 313),
                    luabind::value("F10", 314),
                    luabind::value("F11", 315),
                    luabind::value("F12", 316),
                    luabind::value("F13", 317),
                    luabind::value("F14", 318),
                    luabind::value("F15", 319),
                    luabind::value("Pause", 320),
                    luabind::value("Count", 321)
                ],

            luabind::class_<sf::Event>("Event")
                .def(luabind::constructor<>())
                .def_readonly("Type", &sf::Event::Type)
                .enum_("EventType")
                [
                    luabind::value("Closed", 0),
                    luabind::value("Resized", 1),
                    luabind::value("LostFocus", 2),
                    luabind::value("GainedFocus", 3),
                    luabind::value("TextEntered", 4),
                    luabind::value("KeyPressed", 5),
                    luabind::value("KeyReleased", 6),
                    luabind::value("MouseWheelMoved", 7),
                    luabind::value("MousePressed", 8),
                    luabind::value("MouseReleased", 9),
                    luabind::value("MouseMoved", 10),
                    luabind::value("MouseEntered", 11),
                    luabind::value("MouseLeft", 12)
                ]
                .def_readonly("Key", &sf::Event::Key)
                .def_readonly("Mouse", &sf::Event::MouseMove),

            luabind::class_<sf::Event::KeyEvent>("KeyEvent")
                .def_readonly("Code", &sf::Event::KeyEvent::Code)
                .def_readonly("Alt", &sf::Event::KeyEvent::Alt)
                .def_readonly("Control", &sf::Event::KeyEvent::Control)
                .def_readonly("Shit", &sf::Event::KeyEvent::Shift),

            luabind::class_<sf::Event::MouseMoveEvent>("MouseMoveEvent")
                .def_readonly("X", &sf::Event::MouseMoveEvent::X)
                .def_readonly("Y", &sf::Event::MouseMoveEvent::Y),

            luabind::class_<sf::Vector2i>("Vector2i")
                .def(luabind::constructor<int, int>())
                .def_readwrite("x", &sf::Vector2i::x)
                .def_readwrite("y", &sf::Vector2i::y),

            luabind::class_<sf::Vector2f>("Vector2f")
                .def(luabind::constructor<float, float>())
                .def_readwrite("x", &sf::Vector2f::x)
                .def_readwrite("y", &sf::Vector2f::y),

            luabind::class_<sf::IntRect>("IntRect")
                .def(luabind::constructor<int, int, int, int>())
                .def("Contains", (bool (sf::IntRect::*)(int, int) const)&sf::IntRect::Contains)
                .def_readwrite("Left", &sf::IntRect::Left)
                .def_readwrite("Top", &sf::IntRect::Top)
                .def_readwrite("Width", &sf::IntRect::Width)
                .def_readwrite("Height", &sf::IntRect::Height),

            luabind::class_<sf::FloatRect>("FloatRect")
                .def(luabind::constructor<float, float, float, float>())
                .def("Contains", (bool (sf::FloatRect::*)(float, float) const)&sf::FloatRect::Contains)
                .def_readwrite("Left", &sf::FloatRect::Left)
                .def_readwrite("Top", &sf::FloatRect::Top)
                .def_readwrite("Width", &sf::FloatRect::Width)
                .def_readwrite("Height", &sf::FloatRect::Height),

            luabind::class_<sf::Color>("Color")
                .def(luabind::constructor<int, int, int>())
                .def(luabind::constructor<int, int, int, int>())
                .def_readwrite("r", &sf::Color::r)
                .def_readwrite("g", &sf::Color::g)
                .def_readwrite("b", &sf::Color::b)
                .def_readwrite("a", &sf::Color::a),

            luabind::class_<sf::Drawable>("Drawable")
                .def("SetColor", &sf::Drawable::SetColor)
                .def("GetColor", &sf::Drawable::GetColor)
                .def("SetOrigin", (void (sf::Drawable::*)(float, float))&sf::Drawable::SetOrigin)
                .def("GetOrigin", &sf::Drawable::GetOrigin)
                .def("SetScale", (void (sf::Drawable::*)(float, float))&sf::Drawable::SetScale)
                .def("SetScaleX", &sf::Drawable::SetScaleX)
                .def("SetScaleY", &sf::Drawable::SetScaleY)
                .def("SetPosition", (void (sf::Drawable::*)(float, float))&sf::Drawable::SetPosition)
                .def("SetX", &sf::Drawable::SetX)
                .def("SetY", &sf::Drawable::SetY)
                .def("GetPosition", &sf::Drawable::GetPosition)
                .def("Move", (void (sf::Drawable::*)(float, float))&sf::Drawable::Move)
                .def("Move", (void (sf::Drawable::*)(const sf::Vector2f&))&sf::Drawable::Move)
                .def("SetBlendMode", &sf::Drawable::SetBlendMode)
                .enum_("BlendMode")
                [
                    luabind::value("Alpha", 0),
                    luabind::value("Add", 1),
                    luabind::value("Multiply", 2),
                    luabind::value("None", 3)
                ],

            luabind::class_<sf::Sprite, sf::Drawable>("Sprite")
                .def(luabind::constructor<>())
                .def("Resize", (void (sf::Sprite::*)(float, float))&sf::Sprite::Resize)
                .def("Resize", (void (sf::Sprite::*)(const sf::Vector2f&))&sf::Sprite::Resize)
                .def("GetSize", &sf::Sprite::GetSize)
                .def("Rotate", &sf::Sprite::Rotate)
                .def("SetImage", (void (sf::Sprite::*)(sf::Image*))&sf::Sprite::SetImage)
                .def("SetSubRect", &sf::Sprite::SetSubRect)
                .def("GetSubRect", &sf::Sprite::GetSubRect),

            luabind::class_<sf::Text, sf::Drawable>("Text")
                .def(luabind::constructor<const char*>())
                .def("GetRect", &sf::Text::GetRect),

            luabind::class_<sf::Image>("Image")
                .def(luabind::constructor<>())
                .def("LoadFromFile", &sf::Image::LoadFromFile)
                .def("LoadFromMemory", &sf::Image::LoadFromMemory)
                .def("GetWidth", &sf::Image::GetWidth)
                .def("GetHeight", &sf::Image::GetHeight)
                .def("CopyScreen", &sf::Image::CopyScreen),


            luabind::class_<sf::Shape, sf::Drawable>("Shape")
                .def(luabind::constructor<>())
                .scope
                [
                    luabind::def("Line", &Shape_Line),
                    luabind::def("Rectangle", &Shape_Rectangle),
                    luabind::def("Circle", &Shape_Circle)
                ],

            luabind::class_<sf::View>("View")
                .def(luabind::constructor<>())
                .def("Reset", &sf::View::Reset)
                .def("Zoom", &sf::View::Zoom)
                .def("Rotate", &sf::View::Rotate),

            luabind::class_<sf::Input>("Input")
                .def(luabind::constructor<>())
                .def("IsKeyDown", &sf::Input::IsKeyDown)
                .def("GetMouseX", &sf::Input::GetMouseX)
                .def("GetMouseY", &sf::Input::GetMouseY)
                .def("IsMouseButtonDown", &sf::Input::IsMouseButtonDown),

            luabind::class_<sf::Renderer>("Renderer")
                .def("SetShader", &sf::Renderer::SetShader)
                .def("SetTexture", &sf::Renderer::SetTexture)
                .def("SetColor", &sf::Renderer::SetColor)
                .def("ApplyColor", &sf::Renderer::ApplyColor),

            luabind::class_<sf::RenderWindow>("RenderWindow")
                .def(luabind::constructor<sf::VideoMode, const char*>())
                .def("Clear", &sf::RenderTarget::Clear)
                .def("Draw", (void (sf::RenderTarget::*)(const sf::Drawable&))&sf::RenderTarget::Draw)
                .def("Draw", (void (sf::RenderTarget::*)(const sf::Drawable&, const sf::Shader&))&sf::RenderTarget::Draw)
                .def("GetWidth", &sf::RenderTarget::GetWidth)
                .def("GetHeight", &sf::RenderTarget::GetHeight)
                .def("SetView", &sf::RenderTarget::SetView)
                .def("GetDefaultView", &sf::RenderTarget::GetDefaultView)
                .def("GetView", &sf::RenderTarget::GetView)
                .def("Close", &sf::RenderWindow::Close)
                .def("Display", &sf::RenderWindow::Display)
                .def("GetEvent", &sf::RenderWindow::GetEvent)
                .def("GetFrameTime", &sf::RenderWindow::GetFrameTime)
                .def("IsOpened", &sf::RenderWindow::IsOpened)
                .def("GetInput", &sf::RenderWindow::GetInput)
                .def("ShowMouseCursor", &sf::RenderWindow::ShowMouseCursor)
                .def("SetCursorPosition", &sf::RenderWindow::SetCursorPosition)
                .def("SetFramerateLimit", &sf::RenderWindow::SetFramerateLimit)
                .def("SetPosition", &sf::RenderWindow::SetPosition)
                .def("SetSize", &sf::RenderWindow::SetSize)
                .def("UseVerticalSync", &sf::RenderWindow::UseVerticalSync),

            luabind::class_<eng::Object, sf::Drawable>("Object")
                .def(luabind::constructor<const char*>())
                .def("SetName", &eng::Object::SetName)
                .def("GetName", &eng::Object::GetName)
                .def("GetId", &eng::Object::GetId)
                .def("SetVisible", &eng::Object::SetVisible)
                .def("IsVisible", &eng::Object::IsVisible)
                .def("SetParent", &eng::Object::SetParent)
                .def("GetParent", &eng::Object::GetParent)
                .def("SetEnabled", &eng::Object::SetEnabled)
                .def("IsEnabled", &eng::Object::IsEnabled)
                .def("SetZValue", &eng::Object::SetZValue)
                .def("GetZValue", &eng::Object::GetZValue)
                .def("GetAbsolutePosition", &eng::Object::GetAbsolutePosition)
                .def("SetSize", (void (eng::Object::*)(float, float))&eng::Object::SetSize)
                .def("SetSize", (void (eng::Object::*)(const sf::Vector2f&))&eng::Object::SetSize)
                .def("GetSize", &eng::Object::GetSize)
                .def("UseScissor", &eng::Object::UseScissor)
                .def("SetScissor", &eng::Object::SetScissor)
                .def("Add", &eng::Object::Add)
                .def("Remove", &eng::Object::Remove)
                .def("Clear", &eng::Object::Clear)
                .def("Find", &eng::Object::FindObjectByName)
                .def("OnUpdate", &eng::Object::SetUpdateCallback)
                .def("OnDraw", &eng::Object::SetDrawCallback)
                .def("OnResize", &eng::Object::SetResizeCallback)
                .def("OnEvent", &eng::Object::SetEventCallback),

            luabind::class_<sf::Shader>("Shader")
                .def(luabind::constructor<>())
                .def("LoadFromFile", &sf::Shader::LoadFromFile)
                .def("LoadFromMemory", &sf::Shader::LoadFromMemory)
                .def("SetParameter", (void (sf::Shader::*)(const std::string&, float))&sf::Shader::SetParameter)
                .def("SetParameter", (void (sf::Shader::*)(const std::string&, float, float))&sf::Shader::SetParameter)
                .def("SetParameter", (void (sf::Shader::*)(const std::string&, float, float, float))&sf::Shader::SetParameter)
                .def("SetParameter", (void (sf::Shader::*)(const std::string&, float, float, float, float))&sf::Shader::SetParameter)
                .def("SetParameter", (void (sf::Shader::*)(const std::string&, const sf::Vector2f&))&sf::Shader::SetParameter)
                .def("SetParameter", (void (sf::Shader::*)(const std::string&, const sf::Vector3f&))&sf::Shader::SetParameter)
                .def("SetTexture", &sf::Shader::SetTexture),

            luabind::class_<eng::Scene, eng::Object>("Scene")
                .def(luabind::constructor<const char*>()),

            luabind::class_<ImagePtr>("ImagePtr")
                .def(luabind::constructor<>())
                .def(luabind::constructor<sf::Image*>())
                .def("Get", &ImagePtr::get),

            luabind::class_<SoundPtr>("SoundPtr")
                .def(luabind::constructor<>()),

            luabind::class_<sf::Sound>("Sound")
                .def("Play", &sf::Sound::Play)
                .def("Pause", &sf::Sound::Pause)
                .def("SetVolume", &sf::Sound::SetVolume)
                .def("GetVolume", &sf::Sound::GetVolume)
                .def("SetPosition", (void (sf::Sound::*)(float, float, float))&sf::Sound::SetPosition)
                .def("GetPosition", &sf::Sound::GetPosition)
                .def("SetPitch", &sf::Sound::SetPitch)
                .def("GetPitch", &sf::Sound::GetPitch),

            luabind::class_<eng::Animation::Frame>("Frame")
                .def("SetColor", &eng::Animation::Frame::SetColor)
                .def_readwrite("color", &eng::Animation::Frame::color)
                .def_readwrite("rect", &eng::Animation::Frame::rect),

            luabind::class_<eng::Animation>("Animation")
                .def(luabind::constructor<const char*>())
                .def(luabind::constructor<const ImagePtr&>())
                .def("AddFrame", &eng::Animation::AddFrame)
                .def("Clear", &eng::Animation::Clear)
                .def("GetFrame", &eng::Animation::GetFrame)
                .def("GetSize", &eng::Animation::GetSize)
                .def("SetImage", &eng::Animation::SetImage)
                .def("GetImage", &eng::Animation::GetImage),

            luabind::class_<eng::AnimatedObject, eng::Object>("AnimatedObject")
                .def(luabind::constructor<sf::String>())
                .def(luabind::constructor<eng::Animation*, bool, float>())
                .def("SetAnimation", &eng::AnimatedObject::SetAnimation)
                .def("GetAnimation", &eng::AnimatedObject::GetAnimation)
                .def("SetFrameTime", &eng::AnimatedObject::SetFrameTime)
                .def("GetFrameTime", &eng::AnimatedObject::GetFrameTime)
                .def("Play", &eng::AnimatedObject::Play)
                .def("Pause", &eng::AnimatedObject::Pause)
                .def("Stop", &eng::AnimatedObject::Stop)
                .def("IsPaused", &eng::AnimatedObject::IsPaused)
                .def("IsStoped", &eng::AnimatedObject::IsStoped)
                .def("SetLoop", &eng::AnimatedObject::SetLoop)
                .def("SetCurrentFrame", &eng::AnimatedObject::SetCurrentFrame),

            luabind::class_<sf::Font>("Font")
                .def(luabind::constructor<>())
                .def("LoadFromFile", &sf::Font::LoadFromFile)
                .def("LoadFromMemory", &sf::Font::LoadFromMemory),

            luabind::class_<eng::Label, eng::Object>("Label")
                .def(luabind::constructor<const char*, unsigned int>())
                .def("SetText", &eng::Label::SetText)
                .def("GetText", &eng::Label::GetText)
                .def("SetFont", &eng::Label::SetFont)
                .def("GetFont", &eng::Label::GetFont)
                .def("SetTextColor", &eng::Label::SetTextColor)
                .def("GetTextColor", &eng::Label::GetTextColor)
                .def("SetTextSize", &eng::Label::SetTextSize)
                .def("GetTextSize", &eng::Label::GetTextSize)
                .def("GetRect", &eng::Label::GetRect),

            luabind::class_<eng::Icon, eng::Object>("Icon")
                .def(luabind::constructor<const ImagePtr&>())
                .def(luabind::constructor<const sf::String&>())
                .def("SetImage", (void (eng::Icon::*)(const ImagePtr&, bool))&eng::Icon::SetImage)
                .def("SetImage", (void (eng::Icon::*)(const sf::String&, bool))&eng::Icon::SetImage)
                .def("SetSubRect", &eng::Icon::SetSubRect)
                .def("GetSubRect", &eng::Icon::GetSubRect),

            luabind::class_<Package>("Package")
                .def("GetFile", &Package::GetFile)
                .def("GetFileSize", &Package::GetFileSize),

            // Xml module
            luabind::class_<TiXmlElement>("XmlElement")
                .def(luabind::constructor<const char*>())
                .def("Attribute", (const char* (TiXmlElement::*)(const char*) const)&TiXmlElement::Attribute)
                .def("NextElement", (TiXmlElement* (TiXmlElement::*)(const char*))&TiXmlElement::NextSiblingElement)
                .def("FirstChild", (TiXmlElement* (TiXmlElement::*)(const char*))&TiXmlElement::FirstChildElement),

            luabind::class_<TiXmlNode>("XmlNode")
                .def("NextElement", (TiXmlElement* (TiXmlNode::*)(const char*))&TiXmlNode::NextSiblingElement)
                .def("FirstChild", (TiXmlElement* (TiXmlNode::*)(const char*))&TiXmlNode::FirstChildElement),

            luabind::class_<TiXmlDocument, TiXmlNode>("XmlDocument")
                .def(luabind::constructor<const char*>())
                .def("LoadFile", (bool (TiXmlDocument::*)())&TiXmlDocument::LoadFile)

        ];

        luabind::module(myState, "Utils")
        [
            luabind::def("GetIntFromString", &eng::Utils::GetFromString<int>),
            luabind::def("GetFloatFromString", &eng::Utils::GetFromString<float>)
        ];

        luabind::module(myState, "ResourceManager")
        [
            luabind::def("Get", &eng::ResourceManager::Get),
            luabind::class_<eng::ResourceManager>("ResourceManager")
                .def("CreatePackage", &eng::ResourceManager::CreatePackage)
                .def("GetImage", &eng::ResourceManager::GetResource<sf::Image>)
                .def("GetPackage", &eng::ResourceManager::GetResource<Package>)
                .def("GetSound", &Sound_Create)
        ];

        luabind::module(myState, "UIManager")
        [
            luabind::def("Get", &UserInterface::Get),
            luabind::class_<UserInterface, eng::Scene>("UIManager")
                .def("CleanFocus", &UserInterface::CleanFocus)
        ];

        luabind::module(myState, "LogManager")
        [
            luabind::def("Get", &LogManager::Get),
            luabind::class_<LogManager>("LogManager")
                .def("Log", &LogManager::Log)
                .def("Warning", &LogManager::Warning)
                .def("Error", &LogManager::Error)
        ];

        luabind::module(myState, "WindowManager")
        [
            luabind::def("Get", &WindowManager::Get),

            luabind::def("Sleep", sf::Sleep),

            luabind::class_<eng::WindowManager, sf::RenderWindow>("WindowManager")
                .def("Create", &eng::WindowManager::Create)
        ];

        luabind::module(myState, "SceneManager")
        [
            luabind::def("Get", &SceneManager::Get),
            luabind::class_<SceneManager>("SceneManager")
                .def("AddScene", &SceneManager::AddScene)
                .def("RemoveScene", &SceneManager::RemoveScene)
                .def("GetEvent", &SceneManager::GetEvent)
                .def("Display", &SceneManager::Display)
                .def("GetScene", &SceneManager::GetScene)
        ];

        luabind::module(myState, "ScriptManager")
        [
            luabind::def("Get", &ScriptManager::Get),
            luabind::class_<ScriptManager>("ScriptManager")
                .def("Run", (void (eng::ScriptManager::*)(const sf::String&))&ScriptManager::Run)
                .def("Run", (void (eng::ScriptManager::*)(const sf::String&, const sf::String&))&ScriptManager::Run)
        ];
    }

    lua_State*  ScriptManager::GetLuaState() const
    {
        return myState;
    }

    ScriptManager::~ScriptManager()
    {
        lua_close(myState);
    }

    void    ScriptManager::Run(const sf::String& packname, const sf::String& filename)
    {
        PackagePtr package = eng::ResourceManager::Get()->GetResource<Package>(packname);

        const char* script = package->GetFile(filename);
        sf::Uint32 size = package->GetFileSize(filename);

        char* test = new char[size + 1];
        memset(test, 0, size + 1);
        memcpy(test, script, size);

        int scriptError = luaL_dostring(myState, test);

        if (scriptError)
            LogManager::Get()->Error(sf::String(lua_tostring(myState, -1)));

        delete test;
    }

    void     ScriptManager::Run(const sf::String& script)
    {
        int scriptError = luaL_dofile(myState, script.ToAnsiString().c_str());

        if (scriptError)
            LogManager::Get()->Error(sf::String(lua_tostring(myState, -1)));
    }

}
