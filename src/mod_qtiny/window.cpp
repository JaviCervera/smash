#include "window.h"
#include "event.h"
#include <QApplication>
#include <QCloseEvent>
#include <QDesktopWidget>
#include <QEvent>
#include <QMainWindow>

class MyWindow : public QMainWindow {
public:
    MyWindow(QWidget* parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {}
protected:
    virtual void closeEvent(QCloseEvent *event) {
        GetEventDispatcher().CloseWindow((Window*)Widget::WidgetForQtWidget(this));
        event->ignore();
    }

    virtual void resizeEvent(QResizeEvent *) {
        GetEventDispatcher().SizeWindow((Window*)Widget::WidgetForQtWidget(this));
    }
};

Window::Window(Widget* parent, int x, int y, int w, int h, int flags) {
    // Fix parent
    QWidget* qtParent = NULL;
    if ( parent ) qtParent = parent->QtWidget();

    // Fix flags
    Qt::WindowFlags qtFlags = 0;
    if ( flags & QWINDOW_TOOL ) qtFlags |= Qt::Tool;

    // Create window
    MyWindow* win = new MyWindow(qtParent, qtFlags);
    //win->setUnifiedTitleAndToolBarOnMac(true);
    if ( flags & QWINDOW_MODAL ) win->setWindowModality(Qt::ApplicationModal);
    if ( flags & QWINDOW_SHEET ) win->setWindowModality(Qt::WindowModal);
    if ( flags & QWINDOW_CENTERED ) {
        if ( parent ) {
            int wdiff = parent->Width() - w;
            int hdiff = parent->Height() - h;
            x = parent->X() + wdiff/2;
            y = parent->Y() + hdiff/2;
        } else {
            QDesktopWidget* desktop = QApplication::desktop();
            x = (desktop->width() - w) / 2;
            y = (desktop->height() - h) / 2;
        }
    }
    win->move(x, y);
    win->resize(w, h);

    // Set Qt widget
    SetQtWidget(win);
}

void Window::SetTitle(const String& title) {
    ((QMainWindow*)QtWidget())->setWindowTitle(title.ToCString());
}
