#ifndef GUIFONT_H
#define GUIFONT_H

#include "../common/refcounter.h"
#include "../mod_core/string.h"

class QFont;

class GUIFont : public RefCounter {
public:
    GUIFont(const String& family, unsigned int size, bool bold, bool italic, bool underline);
    virtual ~GUIFont();

    static int Register(const String& file);
    static void Unregister(int id);

    // Do not export
    QFont* QtHandle() { return handle; }
private:
    QFont* handle;
};

#endif // GUIFONT_H
