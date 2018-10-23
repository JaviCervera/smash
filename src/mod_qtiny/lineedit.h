#ifndef LINEEDIT_H
#define LINEEDIT_H

#include "widget.h"

class LineEdit : public Widget {
public:
    LineEdit(Widget* parent, const String& text);

    String Text() const;
    void SetText(const String& text);
};

#endif // LINEEDIT_H
