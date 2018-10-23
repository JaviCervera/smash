#ifndef WIDGET_H
#define WIDGET_H

#include "../common/refcounter.h"
#include "../mod_core/dictionary.h"
#include "../mod_core/string.h"

class QWidget;

class Widget : public RefCounter {
public:
    Widget() : widget(NULL) {}
    virtual ~Widget();

    void SetLayout(int x, int y, int w, int h);
    int X() const;
    int Y() const;
    int Width() const;
    int Height() const;
    void Enable(bool enable);
    void Show(bool show);
    void Focus();
    void* OSHandle() const;
    void SetStyleSheet(const String& sheet);

    // Do not export
    const QWidget* QtWidget() const { return widget; }
    QWidget* QtWidget() { return widget; }
    static Widget* WidgetForQtWidget(QWidget* widget) { return widgets.Value(String::FromInt((int)widget)); }
protected:
    //Widget() : widget(NULL) {}
    void SetQtWidget(QWidget* widget) { this->widget = widget; widgets.Set(String::FromInt((int)widget), this); }
private:
    QWidget* widget;

    static Dictionary<Widget*> widgets; // Uses string with QWidget* as key
};

#endif // WIDGET_H
