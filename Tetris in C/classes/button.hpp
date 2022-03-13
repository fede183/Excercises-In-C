#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

#ifndef BUTTON_HPP
#define BUTTON_HPP
class Button : public Drawable
{
private:
    RectangleShape rectagle;
    string text;
public:
    Button(string text_string, Vector2f location, Vector2f size);
    ~Button();
    void setText(string text);
    void draw(RenderTarget& target, RenderStates states) const;
    void update(Event& e, RenderWindow& window);
};

#endif