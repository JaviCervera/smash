#include "requester.h"
#include "widget.h"
#include <QFileDialog>
#include <QMessageBox>

int Requester::Confirm(Widget* parent, const String& title, const String& text, bool cancelButton) {
    // Fix parent
    QWidget* qtParent = NULL;
    if ( parent ) qtParent = parent->QtWidget();

    // Show Confirm dialog
    QMessageBox::StandardButtons buttons = QMessageBox::Yes | QMessageBox::No;
    if ( cancelButton )
        buttons |= QMessageBox::Cancel;
    switch ( QMessageBox::question(qtParent, title.ToCString(), text.ToCString(), buttons) ) {
    case QMessageBox::No:
        return QCONFIRM_NO;
    case QMessageBox::Yes:
        return QCONFIRM_YES;
    default:
        return QCONFIRM_CANCEL;
    }
}

void Requester::Notify(Widget* parent, const String& title, const String& text, int warningLevel) {
    // Fix parent
    QWidget* qtParent = NULL;
    if ( parent ) qtParent = parent->QtWidget();

    // Show Notify dialog
    switch ( warningLevel ) {
    case QNOTIFY_INFORMATION:
        QMessageBox::information(qtParent, title.ToCString(), text.ToCString());
        break;
    case QNOTIFY_WARNING:
        QMessageBox::warning(qtParent, title.ToCString(), text.ToCString());
        break;
    case QNOTIFY_ERROR:
        QMessageBox::critical(qtParent, title.ToCString(), text.ToCString());
        break;
    }
}

String Requester::RequestFile(Widget* parent, const String& caption, const String& dir, const String& filter, bool save) {
    // Fix parent
    QWidget* qtParent = NULL;
    if ( parent ) qtParent = parent->QtWidget();

    // Show File dialog
    if ( save ) {
        return QFileDialog::getSaveFileName(qtParent, caption.ToCString(), dir.ToCString(), filter.ToCString()).toStdString().c_str();
    } else {
        return QFileDialog::getOpenFileName(qtParent, caption.ToCString(), dir.ToCString(), filter.ToCString()).toStdString().c_str();
    }
}
