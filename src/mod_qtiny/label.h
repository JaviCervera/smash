#ifndef LABEL_H
#define LABEL_H

#include "widget.h"

class Label : public Widget {
public:
    Label(Widget* parent, const String& text);

    String Text() const;
    void SetText(const String& text);
};

#endif // LABEL_H
