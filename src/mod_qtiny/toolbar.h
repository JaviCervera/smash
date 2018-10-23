#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "widget.h"

class GUIIcon;
class Window;

class ToolBar : public Widget {
public:
    ToolBar(Window* parent);

    void AddButton(int id, GUIIcon* icon, const String& tooltip);
    void AddSeparator();
    void AddWidget(Widget* widget);
};

#endif // TOOLBAR_H
