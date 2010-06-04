
#include <sfengine/TextInput.hpp>
#include <sfengine/WindowManager.hpp>

#include <iostream>

#include <SFML/Graphics/Renderer.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Shape.hpp>

namespace eng
{
    TextInput::TextInput(const sf::String& text, int size)
        :   Object("TextInput"),
            myText(text, size),
            myEditable(true),
            mySelectionColor(sf::Color(0, 0, 0, 123)),
            mySelectionDragged(false),
            mySelectionShifted(false),
            mySelectionStart(0),
            myMaxLength(0),
            myCursorPos(0),
            myCursorOffset(0)
    {
        Add(&myText);
        myText.SetFocusable(false);
        UseScissor(true);

        SetColor(sf::Color(255, 255, 255));
        SetTextColor(sf::Color(0, 0, 0));

        SetSize(124, size + 10);
    }

    void    TextInput::SetMaxLength(unsigned int length)
    {
        myMaxLength = length;
    }

    unsigned int TextInput::GetMaxLength() const
    {
        return myMaxLength;
    }

    void    TextInput::SetText(const sf::String& text)
    {
        myText.SetText(text);
    }

    const sf::String& TextInput::GetText() const
    {
        return myText.GetText();
    }

    void    TextInput::SetTextColor(const sf::Color& color)
    {
        myText.SetTextColor(color);
    }

    const sf::Color&    TextInput::GetTextColor() const
    {
        return myText.GetTextColor();
    }

    void    TextInput::SetTextSize(int size)
    {
        myText.SetTextSize(size);
    }

    int     TextInput::GetTextSize() const
    {
        return myText.GetTextSize();
    }

    void    TextInput::SetFont(const sf::Font& font)
    {
        myText.SetFont(font);
    }

    const sf::Font& TextInput::GetFont() const
    {
        return myText.GetFont();
    }

    void    TextInput::SetEditable(bool editable)
    {
        myEditable = editable;
    }

    bool    TextInput::IsEditable() const
    {
        return myEditable;
    }

    void    TextInput::ClearSelection()
    {
        mySelectionStart = myCursorPos;
    }

    bool    TextInput::EraseSelection()
    {
        if (mySelectionStart == myCursorPos)
        {
            return false;
        }

        sf::String currentText = GetText();
        unsigned int newPos = std::min(mySelectionStart, myCursorPos);

        currentText.Erase(newPos, GetSelectionSize());
        SetText(currentText);

        mySelectionStart = myCursorPos = newPos;
        return true;
    }

    void    TextInput::SetSelection(unsigned int start, unsigned int cursorPos)
    {
        const sf::String& str = GetText();

        mySelectionStart = start;
        myCursorPos = (cursorPos > str.GetSize()) ? str.GetSize() : cursorPos;
    }

    unsigned int TextInput::GetSelectionSize()
    {
        if (mySelectionStart < myCursorPos)
        {
            return myCursorPos - mySelectionStart;
        }
        return mySelectionStart - myCursorPos;
    }

    void    TextInput::SetSelectionColor(const sf::Color& color)
    {
        mySelectionColor = color;
    }

    const sf::Color&    TextInput::GetSelectionColor() const
    {
        return mySelectionColor;
    }

    void    TextInput::AdjustSize()
    {
        const std::wstring& text = GetText().ToWideString();

        myText.SetText(text.substr(0, myCursorPos));

        const sf::FloatRect& rect = myText.GetRect();
        if (rect.Width - myCursorOffset >= GetSize().x || rect.Width - myCursorOffset <= 0)
        {
            myCursorOffset = rect.Width - GetSize().x;
        }

        myText.SetText(text);

        if (myCursorOffset < 0)
            myCursorOffset = 0;

        myText.SetX(-myCursorOffset);
    }

    void    TextInput::OnReceiveEvent(const sf::Event& event)
    {
        if (event.Type == sf::Event::MouseButtonPressed)
        {
            if (event.MouseButton.Button != sf::Mouse::Left)
                return;

            myCursorPos = GetCharacterAtPos(event.MouseButton.X - GetAbsolutePosition().x - myCursorOffset);
            mySelectionDragged = true;
            ClearSelection();
        }
        else if (event.Type == sf::Event::MouseButtonReleased)
        {
            if (event.MouseButton.Button != sf::Mouse::Left)
                return;

            if (mySelectionDragged)
                mySelectionDragged = false;
        }
        else if (event.Type == sf::Event::MouseMoved)
        {
            if (mySelectionDragged)
            {
                myCursorPos = GetCharacterAtPos(event.MouseMove.X - GetAbsolutePosition().x - myCursorOffset);
            }
        }
        else if (event.Type == sf::Event::TextEntered)
        {
            const sf::Event::TextEvent& text = event.Text;
            if (text.Unicode <= 30 || (text.Unicode >= 127 && text.Unicode <= 159) || !myEditable)
                return;

            EraseSelection();

            sf::String str = GetText();
            if (str.GetSize() < myMaxLength || !myMaxLength)
            {
                sf::String c;
                c += text.Unicode;
                str.Insert(myCursorPos, c);
                ++myCursorPos;
            }

            SetText(str);
            ClearSelection();
            AdjustSize();
        }
        else if (event.Type == sf::Event::KeyPressed)
        {
            sf::String str = GetText();

            if (event.Key.Code == sf::Key::Left)
            {
                if (myCursorPos)
                    --myCursorPos;

                if (!mySelectionShifted)
                    ClearSelection();
            }
            else if (event.Key.Code == sf::Key::Right)
            {
                if (myCursorPos < str.GetSize())
                    ++myCursorPos;

                if (!mySelectionShifted)
                    ClearSelection();
            }
            else if (event.Key.Code == sf::Key::Home)
            {
                if (mySelectionShifted)
                {
                    mySelectionStart = myCursorPos;
                    myCursorPos = 0;
                }
                else
                {
                    myCursorPos = 0;
                    ClearSelection();
                }
            }
            else if (event.Key.Code == sf::Key::End)
            {
                if (mySelectionShifted)
                {
                    mySelectionStart = myCursorPos;
                    myCursorPos = str.GetSize();
                }
                else
                {
                    myCursorPos = str.GetSize();
                    ClearSelection();
                }
            }
            else if (event.Key.Code == sf::Key::LShift || event.Key.Code == sf::Key::RShift)
            {
                mySelectionShifted = true;
            }
            else if ((event.Key.Code == sf::Key::Delete || event.Key.Code == sf::Key::Back) && (myEditable))
            {
                if (!EraseSelection())
                {
                    if (event.Key.Code == sf::Key::Back && !str.IsEmpty() && myCursorPos)
                    {
                        str.Erase(--myCursorPos, 1);
                    }
                    else if (event.Key.Code == sf::Key::Delete && myCursorPos < str.GetSize())
                    {
                        str.Erase(myCursorPos, 1);
                    }
                    ClearSelection();
                    SetText(str);
                }
            }
            AdjustSize();
        }
        else if (event.Type == sf::Event::KeyReleased)
        {
            if (event.Key.Code == sf::Key::LShift || event.Key.Code == sf::Key::RShift)
            {
                mySelectionShifted = false;
            }
        }
    }

    unsigned int TextInput::GetCharacterAtPos(float xOffset)
    {
        const std::wstring& text = GetText().ToWideString();
        for (unsigned int i = 0; i < text.size(); ++i)
        {
            myText.SetText(text.substr(0, i));
            const sf::FloatRect& rect = myText.GetSFMLText().GetRect();
            myText.SetText(text);

            if (rect.Width > xOffset)
            {
                return i;
            }
        }
        return text.length();
    }

    void    TextInput::Update(float elapsedTime)
    {
        Object::Update(elapsedTime);

        const sf::Vector2f& absPos = GetAbsolutePosition();
        SetScissor(absPos.x, eng::WindowManager::Get()->GetHeight() - absPos.y - GetSize().y, GetSize().x, GetSize().y);
    }

    void    TextInput::Render(sf::RenderTarget& target, sf::Renderer& renderer) const
    {
        Object::Render(target, renderer);

        if (IsFocused())
        {
            float yPos = 2.f;
            const sf::Text& str = myText.GetSFMLText();

            sf::Vector2f realPos = str.GetCharacterPos(myCursorPos);
            realPos.x = realPos.x - myCursorOffset;
            realPos.y = GetSize().y - yPos;

            renderer.SetColor(GetTextColor());
            target.Draw(sf::Shape::Line(realPos.x, yPos, realPos.x + 1, realPos.y, 1.f, GetTextColor()));

            if (mySelectionStart != myCursorPos)
            {
                sf::Vector2f selPos(str.GetCharacterPos(mySelectionStart).x, str.GetCharacterPos(myCursorPos).x);

                renderer.SetColor(GetSelectionColor());
                target.Draw(sf::Shape::Rectangle(selPos.x, yPos, selPos.y - selPos.x, realPos.y, GetSelectionColor()));
            }
        }
    }

}
