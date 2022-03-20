#include "../classes/button.hpp"


Button::Button(string text_string, Vector2f location, Vector2f size) {    
    RectangleShape rectagle;

    rectagle.setSize(size);
    rectagle.setPosition(location);

    this->rectagle = rectagle;

    this->text = text_string;
}

Button::~Button() {}

void Button::setText(string text_string) {
    this->text = text_string;
}

void Button::draw(RenderTarget& target, RenderStates states) const
{
    target.draw(this->rectagle, states);

    Text button_text;
    Font font;

    if (!font.loadFromFile("../fonts/textFont.ttf"))
        throw("Error al cargar la fuente");
    

    button_text.setCharacterSize(24);
    button_text.setStyle(Text::Bold);
    button_text.setFont(font);
    button_text.setFillColor(Color::Black);
    button_text.setString(this->text);
    button_text.setPosition(this->rectagle.getPosition());

    target.draw(button_text, states);
}

void Button::update(Event& event) 
{
    auto xCoord = event.mouseButton.x;
    auto yCoord = event.mouseButton.y;
    Vector2f worldPos = Vector2f(xCoord, yCoord);

    if (event.type == Event::MouseButtonPressed && this->rectagle.getGlobalBounds().contains(worldPos)) {
        this->clickEventFunction();
    }
}

void Button::setClickEvent(function<void(void)> eventFunction) {
    this->clickEventFunction = eventFunction;
}