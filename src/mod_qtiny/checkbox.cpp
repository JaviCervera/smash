#include "checkbox.h"
#include "event.h"
#include <QCheckBox>

CheckBox::CheckBox(Widget* parent, const String& text) {
    // Fix parent
    QWidget* qtParent = NULL;
    if ( parent ) qtParent = parent->QtWidget();

    // Create check box
    QCheckBox* checkbox = new QCheckBox(text.ToCString(), qtParent);
    QObject::connect(checkbox, SIGNAL(clicked(bool)), &GetEventDispatcher(), SLOT(ButtonPressed(bool)));

    // Set Qt widget
    SetQtWidget(checkbox);
}

int CheckBox::State() const {
    switch ( ((QCheckBox*)QtWidget())->checkState() ) {
    case Qt::Checked:
        return QCHECKBOX_CHECK;
        break;
    case Qt::PartiallyChecked:
        return QCHECKBOX_PARTIALCHECK;
        break;
    default:
        return QCHECKBOX_UNCHECK;
        break;
    }
}

void CheckBox::SetState(int state) {
    switch ( state ) {
    case QCHECKBOX_UNCHECK:
        ((QCheckBox*)QtWidget())->setCheckState(Qt::Unchecked);
        break;
    case QCHECKBOX_CHECK:
        ((QCheckBox*)QtWidget())->setCheckState(Qt::Checked);
        break;
    case QCHECKBOX_PARTIALCHECK:
        ((QCheckBox*)QtWidget())->setCheckState(Qt::PartiallyChecked);
        break;
    }
}
