#ifndef EDITOR_H
#define EDITOR_H

#include "widget.h"

class GUIFont;
class Highlighter;

class Editor : public Widget {
public:
    Editor(Widget* parent, bool readOnly, bool syntaxHighlighting);
    virtual ~Editor();

    void AddRule(const String& rule, bool caseSensitive, int color);

    unsigned int Column() const;
    unsigned int CursorPos() const;
    void SetCursorPos(unsigned int pos);
    unsigned int Line() const;
    String Text() const;
    void SetText(const String& text);
    unsigned int SelectionLength() const;
    unsigned int SelectionPos() const;
    void SelectText(unsigned int pos, unsigned int length);
    void SetFont(GUIFont* font);
    void SetLineWrap(bool wrap);
    void SetMultiLineComments(const String& start, const String& end, int color);
    void SetTabSize(unsigned int size);

    void Copy();
    void Cut();
    void Paste();

    void Redo();
    unsigned int RedoSteps();
    void Undo();
    unsigned int UndoSteps();
private:
    Highlighter* highlighter;
};

#endif // EDITOR_H
