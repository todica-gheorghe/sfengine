#ifndef TEXTINPUT_HPP_INCLUDED
#define TEXTINPUT_HPP_INCLUDED

#include <sfengine/Label.hpp>

namespace eng
{
    class TextInput : public Object
    {
        public:
            TextInput(const sf::String& caption, int size);

            void    SetMaxLength(unsigned int length);
            unsigned int GetMaxLength() const;

            void    SetText(const sf::String& text);
            const sf::String&   GetText() const;

            void    SetTextColor(const sf::Color& color);
            const sf::Color&    GetTextColor() const;

            void    SetTextSize(int size);
            int     GetTextSize() const;

            void    SetFont(const sf::Font& font);
            const sf::Font& GetFont() const;

            void    SetEditable(bool editable = true);
            bool    IsEditable() const;

            void    ClearSelection();

            bool    EraseSelection();

            void    SetSelection(unsigned int start, unsigned int cursorPos);

            void    SetSelectionColor(const sf::Color& color);
            const sf::Color&    GetSelectionColor() const;

            unsigned int    GetCharacterAtPos(float xOffset);
            unsigned int    GetSelectionSize();

            virtual void    OnReceiveEvent(const sf::Event& event);

            virtual void    Update(float elapsedTime);

        protected:
            virtual void    Render(sf::RenderTarget& target, sf::Renderer& renderer) const;

        private:
            void        AdjustSize();

            Label       myText;
            bool        myEditable;
            sf::Color   mySelectionColor;
            bool        mySelectionDragged, mySelectionShifted;
            unsigned int    mySelectionStart;


            unsigned int    myMaxLength;
            unsigned int    myCursorPos;
            int             myCursorOffset;



    };
}
#endif // TEXTINPUT_HPP_INCLUDED
