#ifndef BUTTON_H
#define BUTTON_H

#include "widget.h"

class Button : public Widget {
public:
    Button(Widget* parent, const String& text);

    String Text() const;
    void SetText(const String& text);
};

#endif // BUTTON_H
