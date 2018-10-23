#ifndef TABBAR_H
#define TABBAR_H

#include "widget.h"
#include "../core/array.h"

class TabBar : public Widget {
public:
    TabBar(Widget* parent);
    virtual ~TabBar();

    void AddItem(Widget* item, const String& text);
    unsigned int CountItems() const;
    void RemoveItem(unsigned int index);

    unsigned int Index() const;
    void SetIndex(unsigned int index);

    String Text(unsigned int index) const;
    void SetText(unsigned int index, const String& text);

    const Widget* GetConstWidget(unsigned int index) const;
    Widget* GetWidget(unsigned int index);
private:
    Array<Widget*> widgets;
};

#endif // TABBAR_H
