#include "event.h"
#include "app.h"
#include "widget.h"
#include "window.h"
#include <QVariant>

static EventDispatcher dispatcher;

EventDispatcher::~EventDispatcher() {}

EventDispatcher& GetEventDispatcher() {
    return dispatcher;
}

void EventDispatcher::Init() {
    handler(QEVENT_APPINIT, NULL, 0);
}

void EventDispatcher::ButtonPressed(bool checked) {
    handler(QEVENT_WIDGETACTION, Widget::WidgetForQtWidget((QWidget*)sender()), (int)checked);
}

void EventDispatcher::EditorTextChanged() {
    handler(QEVENT_WIDGETACTION, Widget::WidgetForQtWidget((QWidget*)sender()), 0);
}

void EventDispatcher::EditorCursorMoved() {
    handler(QEVENT_WIDGETACTION, Widget::WidgetForQtWidget((QWidget*)sender()), 1);
}

void EventDispatcher::LineEditTextChanged(const QString &text) {
    handler(QEVENT_WIDGETACTION, Widget::WidgetForQtWidget((QWidget*)sender()), 0);
}

void EventDispatcher::MenuAction() {
    handler(QEVENT_MENUACTION, NULL, sender()->property("id").value<int>());
}

void EventDispatcher::TabBarChangedIndex(int index) {
    handler(QEVENT_WIDGETACTION, Widget::WidgetForQtWidget((QWidget*)sender()), index);
}

void EventDispatcher::CloseWindow(Window* win) {
    handler(QEVENT_WINDOWCLOSE, win, 0);
}

void EventDispatcher::SizeWindow(Window* win) {
    handler(QEVENT_WINDOWSIZE, win, 0);
}

void EventDispatcher::ProgramError(QProcess::ProcessError error) {
    handler(QEVENT_PROGRAMERROR, (Widget*)sender(), error == QProcess::Crashed);
}

void EventDispatcher::ProgramFinished(int exitCode, QProcess::ExitStatus exitStatus) {
    handler(QEVENT_PROGRAMFINISH, (Widget*)sender(), exitCode);
}

void EventDispatcher::ProgramOutputAvailable() {
    handler(QEVENT_PROGRAMOUTPUT, (Widget*)sender(), 0);
}
