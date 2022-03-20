#include <SFML/Graphics.hpp>
#include <functional>

using namespace sf;
using namespace std;

#ifndef BUTTON_HPP
#define BUTTON_HPP
class Button : public Drawable
{
private:
    RectangleShape rectagle;
    string text;
    function<void(void)> clickEventFunction;
public:
    Button(string text_string, Vector2f location, Vector2f size);
    ~Button();
    void setText(string text);
    void draw(RenderTarget& target, RenderStates states) const;
    void update(Event& event);
    void setClickEvent(function<void(void)> eventFunction);
};

#endif