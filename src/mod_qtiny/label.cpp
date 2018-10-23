#include "label.h"
#include <QLabel>

Label::Label(Widget* parent, const String& text) {
    // Fix parent
    QWidget* qtParent = NULL;
    if ( parent ) qtParent = parent->QtWidget();

    // Create Label
    QLabel* label = new QLabel(text.ToCString(), qtParent);

    // Set Qt widget
    SetQtWidget(label);
}

String Label::Text() const {
    return ((QLabel*)QtWidget())->text().toStdString().c_str();
}

void Label::SetText(const String& text) {
    ((QLabel*)QtWidget())->setText(text.ToCString());
}
