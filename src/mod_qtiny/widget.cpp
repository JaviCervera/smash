#include "widget.h"
#include <QWidget>

Dictionary<Widget*> Widget::widgets;

Widget::~Widget() {
    if ( widget ) {
        widgets.Remove(String::FromInt((int)widget));
        delete widget;
    }
}

void Widget::SetLayout(int x, int y, int w, int h) {
    widget->move(x, y);
    widget->resize(w, h);
}

int Widget::X() const {
    return widget->pos().x();
}

int Widget::Y() const {
    return widget->pos().y();
}

int Widget::Width() const {
    return widget->size().width();
}

int Widget::Height() const {
    return widget->size().height();
}

void Widget::Enable(bool enable) {
    widget->setEnabled(enable);
}

void Widget::Show(bool show) {
    widget->setVisible(show);
}

void Widget::Focus() {
    widget->setFocus();
}

void* Widget::OSHandle() const {
    return (void*)widget->winId();
}

void Widget::SetStyleSheet(const String& sheet) {
    widget->setStyleSheet(sheet.ToCString());
}
