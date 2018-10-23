#include "editor.h"
#include "event.h"
#include "guifont.h"
#include "../core/array.h"
#include <QSyntaxHighlighter>
#include <QTextCursor>
#include <QTextEdit>

class Highlighter : public QSyntaxHighlighter {
public:
    Highlighter(QTextDocument* parent = 0) : QSyntaxHighlighter(parent) {
        supportsMultiLineComments = false;
        multiLineCommentFormat.setForeground(QColor(0xFFFF0000));
        commentStartExp = QRegExp("/\\*");
        commentEndExp = QRegExp("\\*/");
    }

    void AddRule(const String& rulestr, bool caseSensitive, int color) {
        Qt::CaseSensitivity cs = caseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive;

        QTextCharFormat format;
        format.setForeground(QColor(color));

        HighlightingRule rule;
        rule.pattern = QRegExp(rulestr.ToCString(), cs);
        rule.format = format;

        rules.Add(rule);
    }

    void SetMultiLineComments(const String& start, const String& end, int color) {
        supportsMultiLineComments = true;
        multiLineCommentFormat.setForeground(QColor(color));
        commentStartExp = QRegExp(start.ToCString());
        commentEndExp = QRegExp(end.ToCString());
    }

protected:
    void highlightBlock(const QString& text) {
        // Apply rules
        for ( int i = 0; i < rules.Size(); i++ ) {
            HighlightingRule& rule = rules[i];
            QRegExp exp(rule.pattern);
            int index = exp.indexIn(text);
            while ( index >= 0 ) {
                int length = exp.matchedLength();
                setFormat(index, length, rule.format);
                index = exp.indexIn(text, index + length);
            }
        }

        // Special case for multiline comments
        if ( supportsMultiLineComments ) {
            setCurrentBlockState(0);
            int startIndex = 0;
            if ( previousBlockState() != 1 ) {
                startIndex = commentStartExp.indexIn(text);
            }

            while ( startIndex >= 0 ) {
                int endIndex = commentEndExp.indexIn(text, startIndex);
                int commentLength;
                if ( endIndex == -1 ) {
                    setCurrentBlockState(1);
                    commentLength = text.length() - startIndex;
                } else {
                    commentLength = endIndex - startIndex + commentEndExp.matchedLength();
                }
                setFormat(startIndex, commentLength, multiLineCommentFormat);
                startIndex = commentStartExp.indexIn(text, startIndex + commentLength);
            }
        }
    }
private:
    struct HighlightingRule {
        QRegExp pattern;
        QTextCharFormat format;
    };
    Array<HighlightingRule> rules;

    bool supportsMultiLineComments;
    QRegExp commentStartExp;
    QRegExp commentEndExp;
    QTextCharFormat multiLineCommentFormat;
};

Editor::Editor(Widget* parent, bool readOnly, bool syntaxHighlighting) : highlighter(NULL) {
    // Fix parent
    QWidget* qtParent = NULL;
    if ( parent ) qtParent = parent->QtWidget();

    // Create Editor
    QTextEdit* editor = new QTextEdit(qtParent);
    if ( readOnly ) editor->setReadOnly(true);
    if ( syntaxHighlighting ) {
        highlighter = new Highlighter(editor->document());
    }
    editor->setLineWrapMode(QTextEdit::NoWrap);
    editor->setPlainText("");
    QObject::connect(editor, SIGNAL(textChanged()), &GetEventDispatcher(), SLOT(EditorTextChanged()));
    QObject::connect(editor, SIGNAL(cursorPositionChanged()), &GetEventDispatcher(), SLOT(EditorCursorMoved()));

    // Set Qt widget
    SetQtWidget(editor);
}

Editor::~Editor() {
    if ( highlighter ) delete highlighter;
}

void Editor::AddRule(const String& rule, bool caseSensitive, int color) {
    if ( highlighter ) highlighter->AddRule(rule, caseSensitive, color);
}

unsigned int Editor::Column() const {
    QTextCursor cursor = ((QTextEdit*)QtWidget())->textCursor();
    return cursor.columnNumber();
}

unsigned int Editor::CursorPos() const {
    return ((QTextEdit*)QtWidget())->textCursor().position();
}

void Editor::SetCursorPos(unsigned int pos) {
    QTextCursor cursor = ((QTextEdit*)QtWidget())->textCursor();
    cursor.setPosition(pos);
    ((QTextEdit*)QtWidget())->setTextCursor(cursor);
}

unsigned int Editor::Line() const {
    QTextCursor cursor = ((QTextEdit*)QtWidget())->textCursor();
    return cursor.blockNumber();
}

String Editor::Text() const {
    return ((QTextEdit*)QtWidget())->toPlainText().toStdString().c_str();
}

void Editor::SetText(const String& text) {
    ((QTextEdit*)QtWidget())->setText(text.ToCString());
}

unsigned int Editor::SelectionLength() const {
    QTextCursor cursor = ((QTextEdit*)QtWidget())->textCursor();
    return abs(cursor.position() - cursor.anchor());
}

unsigned int Editor::SelectionPos() const {
    QTextCursor cursor = ((QTextEdit*)QtWidget())->textCursor();
    return cursor.anchor();
}

void Editor::SelectText(unsigned int pos, unsigned int length) {
    QTextCursor cursor = ((QTextEdit*)QtWidget())->textCursor();
    cursor.setPosition(pos);
    cursor.setPosition(pos+length, QTextCursor::KeepAnchor);
    ((QTextEdit*)QtWidget())->setTextCursor(cursor);
}

void Editor::SetFont(GUIFont* font) {
    ((QTextEdit*)QtWidget())->setFont(*font->QtHandle());
}

void Editor::SetLineWrap(bool wrap) {
    if ( wrap )
        ((QTextEdit*)QtWidget())->setLineWrapMode(QTextEdit::WidgetWidth);
    else
        ((QTextEdit*)QtWidget())->setLineWrapMode(QTextEdit::NoWrap);
}

void Editor::SetMultiLineComments(const String& start, const String& end, int color) {
    if ( highlighter ) highlighter->SetMultiLineComments(start, end, color);
}

void Editor::SetTabSize(unsigned int size) {
    QFontMetrics metrics(((QTextEdit*)QtWidget())->font());
    ((QTextEdit*)QtWidget())->setTabStopWidth(size * metrics.width(' '));
}

void Editor::Copy() {
    ((QTextEdit*)QtWidget())->copy();
}

void Editor::Cut() {
    ((QTextEdit*)QtWidget())->cut();
}

void Editor::Paste() {
    ((QTextEdit*)QtWidget())->paste();
}

void Editor::Redo() {
    ((QTextEdit*)QtWidget())->redo();
}

unsigned int Editor::RedoSteps() {
    return ((QTextEdit*)QtWidget())->document()->availableRedoSteps();
}

void Editor::Undo() {
    ((QTextEdit*)QtWidget())->undo();
}

unsigned int Editor::UndoSteps() {
    return ((QTextEdit*)QtWidget())->document()->availableUndoSteps();
}
