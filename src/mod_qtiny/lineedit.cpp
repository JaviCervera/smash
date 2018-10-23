#include "lineedit.h"
#include "event.h"
#include <QLineEdit>

LineEdit::LineEdit(Widget* parent, const String& text) {
    // Fix parent
    QWidget* qtParent = NULL;
    if ( parent ) qtParent = parent->QtWidget();

    // Create LineEdit
    QLineEdit* lineedit = new QLineEdit(text.ToCString(), qtParent);
    QObject::connect(lineedit, SIGNAL(textChanged(QString)), &GetEventDispatcher(), SLOT(LineEditTextChanged(QString)));

    // Set Qt widget
    SetQtWidget(lineedit);
}

String LineEdit::Text() const {
    return ((QLineEdit*)QtWidget())->text().toStdString().c_str();
}

void LineEdit::SetText(const String& text) {
    ((QLineEdit*)QtWidget())->setText(text.ToCString());
}
