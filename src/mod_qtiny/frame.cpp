#include "frame.h"
#include <QFrame>

Frame::Frame(Widget* parent, int style) {
    // Fix parent
    QWidget* qtParent = NULL;
    if ( parent ) qtParent = parent->QtWidget();

    // Create Frame
    QFrame* frame = new QFrame(qtParent, (Qt::WindowFlags)style);

    // Set Qt widget
    SetQtWidget(frame);
}
