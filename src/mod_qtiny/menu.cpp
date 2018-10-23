#include "menu.h"
#include "event.h"
#include "window.h"
#include <QMenu>
#include <QMenuBar>
#include <QMainWindow>

Menu::Menu(QMenu* qmenu) {
    SetQtWidget(qmenu);
}

void Menu::AddItem(int id, const String& text, const String& shortcut) {
    QAction* action = ((QMenu*)QtWidget())->addAction(text.ToCString(), &GetEventDispatcher(), SLOT(MenuAction()), QKeySequence(shortcut.ToCString()));
    action->setProperty("id", QVariant::fromValue(id));
}

void Menu::AddSeparator() {
    ((QMenu*)QtWidget())->addSeparator();
}

MenuBar::MenuBar(Window* parent) {
    // Fix parent
    QMainWindow* qtParent = NULL;
    if ( parent ) qtParent = (QMainWindow*)parent->QtWidget();

    // Create MenuBar
    QMenuBar* menubar = qtParent->menuBar();

    // Set Qt widget
    SetQtWidget(menubar);
}

MenuBar::~MenuBar() {
    for ( int i = 0; i < menus.Size(); i++ ) {
        delete menus[i];
    }
}

Menu* MenuBar::AddTitle(const String& title) {
    Menu* menu = new Menu(((QMenuBar*)QtWidget())->addMenu(title.ToCString()));
    menus.Add(menu);
    return menu;
}
