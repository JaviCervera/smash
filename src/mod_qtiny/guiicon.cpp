#include "guiicon.h"
#include <QIcon>

GUIIcon::GUIIcon(const String& file) : handle(NULL) {
    handle = new QIcon(file.ToCString());
}

GUIIcon::~GUIIcon() {
    if ( handle ) delete handle;
}
