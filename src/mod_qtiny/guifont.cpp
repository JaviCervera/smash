#include "guifont.h"
#include <QFont>
#include <QFontDatabase>

GUIFont::GUIFont(const String& family, unsigned int size, bool bold, bool italic, bool underline) {
    handle = new QFont(family.ToCString());
    handle->setPointSize(size);
    handle->setBold(bold);
    handle->setItalic(italic);
    handle->setUnderline(underline);
}

GUIFont::~GUIFont() {
    delete handle;
}

int GUIFont::Register(const String& file) {
    return QFontDatabase::addApplicationFont(file.ToCString());
}

void GUIFont::Unregister(int id) {
    QFontDatabase::removeApplicationFont(id);
}
