#ifndef COMBOBOX_H
#define COMBOBOX_H

#include "widget.h"

class ComboBox : public Widget {
public:
    ComboBox(Widget* parent);

    void AddItem(const String& text);
    unsigned int CountItems() const;
    void RemoveItem(unsigned int index);

    unsigned int Index() const;
    void SetIndex(unsigned int index);

    String Text(unsigned int index) const;
    void SetText(unsigned int index, const String& text);
};

#endif // COMBOBOX_H
