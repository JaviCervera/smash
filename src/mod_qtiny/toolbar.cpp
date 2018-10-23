#include "toolbar.h"
#include "event.h"
#include "guiicon.h"
#include "window.h"
#include <QAction>
#include <QIcon>
#include <QMainWindow>
#include <QToolBar>

ToolBar::ToolBar(Window* parent) {
    // Fix parent
    QMainWindow* qtParent = NULL;
    if ( parent ) qtParent = (QMainWindow*)parent->QtWidget();

    // Create ToolBar
    QToolBar* toolbar = qtParent->addToolBar("");
    toolbar->setMovable(false);
    toolbar->setIconSize(QSize(16, 16));
#ifdef Q_OS_MAC
    toolbar->resize(toolbar->size().width(), toolbar->size().height()-2);
#else
    toolbar->resize(toolbar->size().width(), 16);
#endif

    // Set Qt widget
    SetQtWidget(toolbar);
}

void ToolBar::AddButton(int id, GUIIcon* icon, const String& tooltip) {
    QAction* action = ((QToolBar*)QtWidget())->addAction(*icon->QtHandle(), "");
    action->setProperty("id", QVariant::fromValue(id));
    if ( tooltip != "" ) action->setToolTip(tooltip.ToCString());
    QObject::connect(action, SIGNAL(triggered(bool)), &GetEventDispatcher(), SLOT(MenuAction()));
}

void ToolBar::AddSeparator() {
    ((QToolBar*)QtWidget())->addSeparator();
}

void ToolBar::AddWidget(Widget* widget) {
    ((QToolBar*)QtWidget())->addWidget(widget->QtWidget());
}
