#ifndef EVENT_H
#define EVENT_H

#include <QObject>
#include <QProcess>
#include <QString>

// Events
#define QEVENT_APPINIT          0
#define QEVENT_WINDOWCLOSE      1
#define QEVENT_WINDOWSIZE       2
#define QEVENT_MENUACTION       3
#define QEVENT_WIDGETACTION     4
#define QEVENT_PROGRAMFINISH    5
#define QEVENT_PROGRAMOUTPUT    6
#define QEVENT_PROGRAMERROR     7

class Widget;
class Window;

typedef void (*EventHandler)(int,Widget*,int);

// Internal class, not exported to Smash
class EventDispatcher : public QObject {
    Q_OBJECT
public:
    EventDispatcher() : handler(NULL) {}
    virtual ~EventDispatcher();

    void SetHandler(EventHandler handler) { this->handler = handler; }
public slots:
    void Init();
    void ButtonPressed(bool checked);
    void EditorTextChanged();
    void EditorCursorMoved();
    void LineEditTextChanged(const QString& text);
    void MenuAction();
    void TabBarChangedIndex(int index);
    void CloseWindow(Window* win);
    void SizeWindow(Window* win);
    void ProgramError(QProcess::ProcessError error);
    void ProgramFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void ProgramOutputAvailable();
private:
    EventHandler handler;
};

EventDispatcher& GetEventDispatcher();

#endif // EVENT_H
