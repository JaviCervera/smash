#include "button.h"
#include "event.h"
#include <QPushButton>

Button::Button(Widget* parent, const String& text) {
    // Fix parent
    QWidget* qtParent = NULL;
    if ( parent ) qtParent = parent->QtWidget();

    // Create button
    QPushButton* button = new QPushButton(text.ToCString(), qtParent);
    QObject::connect(button, SIGNAL(clicked(bool)), &GetEventDispatcher(), SLOT(ButtonPressed(bool)));

    // Set Qt widget
    SetQtWidget(button);
}

String Button::Text() const {
    return ((QPushButton*)QtWidget())->text().toStdString().c_str();
}

void Button::SetText(const String& text) {
    ((QPushButton*)QtWidget())->setText(text.ToCString());
}
