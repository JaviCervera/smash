#ifndef WINDOW_H
#define WINDOW_H

#include "widget.h"

#define QWINDOW_STANDARD    0
#define QWINDOW_TOOL        1
#define QWINDOW_MODAL       2
#define QWINDOW_SHEET       4
#define QWINDOW_CENTERED    8

class Window : public Widget {
public:
    Window(Widget* parent, int x, int y, int w, int h, int flags);

    void SetTitle(const String& title);
};

#endif // WINDOW_H
