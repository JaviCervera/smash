#ifndef MENU_H
#define MENU_H

#include "widget.h"
#include "../core/array.h"

class Window;
class QMenu;

class Menu : public Widget {
public:
    void AddItem(int id, const String& text, const String& shortcut);
    void AddSeparator();

    // Do not export
    Menu(QMenu* qmenu);
};

class MenuBar : public Widget {
public:
    MenuBar(Window* parent);
    virtual ~MenuBar();

    Menu* AddTitle(const String& title);
private:
    Array<Menu*> menus;
};

#endif // MENU_H
