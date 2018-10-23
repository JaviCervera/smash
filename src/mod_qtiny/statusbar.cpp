#include "statusbar.h"
#include "window.h"
#include <QLabel>
#include <QMainWindow>
#include <QStatusBar>

StatusBar::StatusBar(Window* parent) {
    // Fix parent
    QMainWindow* qtParent = NULL;
    if ( parent ) qtParent = (QMainWindow*)parent->QtWidget();

    // Create StatusBar
    QStatusBar* statusbar = qtParent->statusBar();
    statusbar->setStyleSheet("QStatusBar::item { border: none; }");
    label = new QLabel();
    statusbar->addWidget(label);

    // Set Qt widget
    SetQtWidget(statusbar);
}

void StatusBar::SetText(const String& text) {
    label->setText(text.ToCString());
}
