#ifndef GUIICON_H
#define GUIICON_H

#include "../common/refcounter.h"
#include "../core/string.h"

class QIcon;

class GUIIcon : public RefCounter {
public:
    GUIIcon(const String& file);
    virtual ~GUIIcon();

    // Do not export
    QIcon* QtHandle() { return handle; }
private:
    QIcon* handle;
};

#endif // GUIICON_H
