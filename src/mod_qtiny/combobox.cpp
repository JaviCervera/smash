#include "combobox.h"
#include "event.h"
#include <QComboBox>

ComboBox::ComboBox(Widget* parent) {
    // Fix parent
    QWidget* qtParent = NULL;
    if ( parent ) qtParent = parent->QtWidget();

    // Create ComboBox
    QComboBox* combobox = new QComboBox(qtParent);
    combobox->setDuplicatesEnabled(true);
    QObject::connect(combobox, SIGNAL(currentIndexChanged(int)), &GetEventDispatcher(), SLOT(TabBarChangedIndex(int)));

    // Set Qt widget
    SetQtWidget(combobox);
}

void ComboBox::AddItem(const String& text) {
    ((QComboBox*)QtWidget())->addItem(text.ToCString());
}

unsigned int ComboBox::CountItems() const {
    return ((QComboBox*)QtWidget())->count();
}

void ComboBox::RemoveItem(unsigned int index) {
    ((QComboBox*)QtWidget())->removeItem(index);
}

unsigned int ComboBox::Index() const {
    return ((QComboBox*)QtWidget())->currentIndex();
}

void ComboBox::SetIndex(unsigned int index) {
    ((QComboBox*)QtWidget())->setCurrentIndex(index);
}

String ComboBox::Text(unsigned int index) const {
    return ((QComboBox*)QtWidget())->itemText(index).toStdString().c_str();
}

void ComboBox::SetText(unsigned int index, const String& text) {
    ((QComboBox*)QtWidget())->setItemText(index, text.ToCString());
}
