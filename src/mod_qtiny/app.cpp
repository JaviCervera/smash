#include "app.h"
#include <QApplication>

#ifdef BUILD_SHARED
#include <qplugin.h>
#if defined(_WIN32)
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
Q_IMPORT_PLUGIN(QWindowsPrinterSupportPlugin)
#elif defined(__APPLE__)
Q_IMPORT_PLUGIN(QCocoaIntegrationPlugin)
Q_IMPORT_PLUGIN(QCocoaPrinterSupportPlugin)
#endif
#endif

int RunApp(EventHandler handler) {
    int argc = 0;
    GetEventDispatcher().SetHandler(handler);
    QApplication* app = new QApplication(argc, NULL);
    GetEventDispatcher().Init();
    int ret = app->exec();
    delete app;
    return ret;
}
