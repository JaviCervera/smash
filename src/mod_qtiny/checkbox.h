#ifndef CHECKBOX_H
#define CHECKBOX_H

#include "widget.h"

// CheckBox states
#define QCHECKBOX_UNCHECK       0
#define QCHECKBOX_CHECK         1
#define QCHECKBOX_PARTIALCHECK  2

class CheckBox : public Widget {
public:
    CheckBox(Widget* parent, const String& text);

    int State() const;
    void SetState(int state);
};

#endif // CHECKBOX_H
