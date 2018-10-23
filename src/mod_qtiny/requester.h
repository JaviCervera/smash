#ifndef REQUESTER_H
#define REQUESTER_H

#include "../core/string.h"

// Confirm results
#define QCONFIRM_CANCEL      0
#define QCONFIRM_NO          1
#define QCONFIRM_YES         2

// Notify levels
#define QNOTIFY_INFORMATION 0
#define QNOTIFY_WARNING     1
#define QNOTIFY_ERROR       2

class Widget;

class Requester {
public:
    static int Confirm(Widget* parent, const String& title, const String& text, bool cancelButton);
    static void Notify(Widget* parent, const String& title, const String& text, int warningLevel);
    static String RequestFile(Widget* parent, const String& caption, const String& dir, const String& filter, bool save);
protected:
    Requester() {}
    ~Requester() {}
};

#endif // REQUESTER_H
