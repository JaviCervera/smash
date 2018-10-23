#ifndef FRAME_H
#define FRAME_H

#include "widget.h"

// Frame styles
#define QFRAME_NOBORDER 0
#define QFRAME_BOX      0x0001
#define QFRAME_PANEL    0x0002
#define QFRAME_STYLED   0x0006
#define QFRAME_PLAIN    0x0010
#define QFRAME_RAISED   0x0020
#define QFRAME_SUNKEN   0x0030

class Frame : public Widget {
public:
    Frame(Widget* parent, int style);
};

#endif // FRAME_H
