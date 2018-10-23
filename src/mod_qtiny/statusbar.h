#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "widget.h"

class QLabel;
class Window;

class StatusBar : public Widget {
public:
    StatusBar(Window* parent);

    void SetText(const String& text);
private:
    QLabel* label;
};

#endif // STATUSBAR_H
