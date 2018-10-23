#include "../sdk/smashsdk.h"
#include "app.h"
#include "button.h"
#include "checkbox.h"
#include "combobox.h"
#include "editor.h"
#include "frame.h"
#include "guifont.h"
#include "guiicon.h"
#include "label.h"
#include "lineedit.h"
#include "menu.h"
#include "process.h"
#include "requester.h"
#include "statusbar.h"
#include "tabbar.h"
#include "toolbar.h"
#include "widget.h"
#include "window.h"

static SmashSDK* globSDK = NULL;

static int qCheckBoxUncheck = QCHECKBOX_UNCHECK;
static int qCheckBoxCheck = QCHECKBOX_CHECK;
static int qCheckBoxPartialCheck = QCHECKBOX_PARTIALCHECK;
static int qFrameNoBorder = QFRAME_NOBORDER;
static int qFrameBox = QFRAME_BOX;
static int qFramePanel = QFRAME_PANEL;
static int qFrameStyled = QFRAME_STYLED;
static int qFramePlain = QFRAME_PLAIN;
static int qFrameRaised = QFRAME_RAISED;
static int qFrameSunken = QFRAME_SUNKEN;
static int qConfirmCancel = QCONFIRM_CANCEL;
static int qConfirmNo = QCONFIRM_NO;
static int qConfirmYes = QCONFIRM_YES;
static int qNotifyInformation = QNOTIFY_INFORMATION;
static int qNotifyWarning = QNOTIFY_WARNING;
static int qNotifyError = QNOTIFY_ERROR;
static int qWindowStandard = QWINDOW_STANDARD;
static int qWindowTool = QWINDOW_TOOL;
static int qWindowModal = QWINDOW_MODAL;
static int qWindowSheet = QWINDOW_SHEET;
static int qWindowCentered = QWINDOW_CENTERED;

static asIScriptObject* AppInstance();

void HandleEvent(int event, Widget* source, int data) {
    // Get application singleton
    static asIObjectType* type = globSDK->ScriptType("Application");
    static asIScriptObject* instance = AppInstance();
    asIScriptFunction* method = NULL;

    // Call method depending on event
    switch ( event ) {
    case QEVENT_APPINIT:
        method = globSDK->ScriptMethod(type, "void OnInit()");
        globSDK->PrepareScriptFunction(method);
        break;
    case QEVENT_WINDOWCLOSE:
        method = globSDK->ScriptMethod(type, "void OnCloseWindow(Window@)");
        globSDK->PrepareScriptFunction(method);
        globSDK->SetArgAddress(0, (void*)source);
        break;
    case QEVENT_WINDOWSIZE:
        method = globSDK->ScriptMethod(type, "void OnSizeWindow(Window@)");
        globSDK->PrepareScriptFunction(method);
        globSDK->SetArgAddress(0, (void*)source);
    case QEVENT_MENUACTION:
        method = globSDK->ScriptMethod(type, "void OnMenuAction(int)");
        globSDK->PrepareScriptFunction(method);
        globSDK->SetArgInt(0, data);
        break;
    case QEVENT_WIDGETACTION:
        method = globSDK->ScriptMethod(type, "void OnWidgetAction(Widget@, int)");
        globSDK->PrepareScriptFunction(method);
        globSDK->SetArgAddress(0, (void*)source);
        globSDK->SetArgInt(1, data);
        break;
    case QEVENT_PROGRAMFINISH:
        method = globSDK->ScriptMethod(type, "void OnProcessFinish(Process@, int)");
        globSDK->PrepareScriptFunction(method);
        globSDK->SetArgAddress(0, (void*)source);
        globSDK->SetArgInt(1, data);
        break;
    case QEVENT_PROGRAMOUTPUT:
        method = globSDK->ScriptMethod(type, "void OnProcessOutput(Process@)");
        globSDK->PrepareScriptFunction(method);
        globSDK->SetArgAddress(0, (void*)source);
        break;
    case QEVENT_PROGRAMERROR:
        method = globSDK->ScriptMethod(type, "void OnProcessError(Process@, bool)");
        globSDK->PrepareScriptFunction(method);
        globSDK->SetArgAddress(0, (void*)source);
        globSDK->SetArgInt(1, data);
        break;
    }

    // If method has been found, call it
    if ( method ) {
        globSDK->SetScriptThis(instance);
        if ( globSDK->ExecuteContext() != asEXECUTION_FINISHED ) {
            globSDK->Error((String("Error running event handler '") + method->GetName() + "'").ToCString());
        }
    }
}

void EntryPoint() {
    RunApp(HandleEvent);
}

static GUIFont* GUIFontFactory(const String& family, unsigned int size, bool bold, bool italic, bool underline) {
    return new GUIFont(family, size, bold, italic, underline);
}

static GUIIcon* GUIIconFactory(const String& file) {
    return new GUIIcon(file);
}

static Widget* WidgetFactory() {
    return new Widget();
}

static Button* ButtonFactory(Widget* parent, const String& text) {
    return new Button(parent, text);
}

static CheckBox* CheckBoxFactory(Widget* parent, const String& text) {
    return new CheckBox(parent, text);
}

static ComboBox* ComboBoxFactory(Widget* parent) {
    return new ComboBox(parent);
}

static Editor* EditorFactory(Widget* parent, bool readOnly, bool syntaxHighlighting) {
    return new Editor(parent, readOnly, syntaxHighlighting);
}

static Frame* FrameFactory(Widget* parent, int style) {
    return new Frame(parent, style);
}

static Label* LabelFactory(Widget* parent, const String& text) {
    return new Label(parent, text);
}

static LineEdit* LineEditFactory(Widget* parent, const String& text) {
    return new LineEdit(parent, text);
}

static MenuBar* MenuBarFactory(Window* parent) {
    return new MenuBar(parent);
}

static StatusBar* StatusBarFactory(Window* parent) {
    return new StatusBar(parent);
}

static TabBar* TabBarFactory(Widget* parent) {
    return new TabBar(parent);
}

static ToolBar* ToolBarFactory(Window* parent) {
    return new ToolBar(parent);
}

static Window* WindowFactory(Widget& parent, int x, int y, int w, int h, int flags) {
    return new Window(&parent, x, y, w, h, flags);
}

static Process* ProcessFactory(const String& name) {
    return new Process(name);
}

static asIScriptObject* AppInstance() {
    static asIScriptObject* instance = NULL;
    if ( !instance ) {
        asIObjectType* type = globSDK->ScriptType("Application");
        if ( !type ) {
            globSDK->Error("An 'Application' class is required when using the 'qtiny' module.");
            globSDK->Context()->Abort();
            return NULL;
        }

        instance = globSDK->CreateScriptObject(type, "Application@ Application()");
        if ( !instance ) {
            globSDK->Error("An instance of 'Application' could not be created.");
            globSDK->Context()->Abort();
            return NULL;
        }
    }

    return instance;
}

template<typename A, typename B>
B* RefCast(A* a) {
    // If the handle already is a null handle, then just return the null handle
    if( !a ) return 0;

    // Now try to dynamically cast the pointer to the wanted type
    B* b = dynamic_cast<B*>(a);
    if( b != 0 ) {
        // Since the cast was made, we need to increase the ref counter for the returned handle
        b->AddRef();
    }

    return b;
}

template <typename T>
void RegisterWidgetMembers(const char* type) {
    globSDK->RegisterMethod(type, "void SetLayout(int, int, int, int)", asMETHOD(T, SetLayout), asCALL_THISCALL);
    globSDK->RegisterMethod(type, "int X() const", asMETHOD(T, X), asCALL_THISCALL);
    globSDK->RegisterMethod(type, "int Y() const", asMETHOD(T, Y), asCALL_THISCALL);
    globSDK->RegisterMethod(type, "int Width() const", asMETHOD(T, Width), asCALL_THISCALL);
    globSDK->RegisterMethod(type, "int Height() const", asMETHOD(T, Height), asCALL_THISCALL);
    globSDK->RegisterMethod(type, "void Enable(bool)", asMETHOD(T, Enable), asCALL_THISCALL);
    globSDK->RegisterMethod(type, "void Show(bool)", asMETHOD(T, Show), asCALL_THISCALL);
    globSDK->RegisterMethod(type, "void Focus()", asMETHOD(T, Focus), asCALL_THISCALL);
    globSDK->RegisterMethod(type, "uint OSHandle() const", asMETHOD(T, OSHandle), asCALL_THISCALL);
    globSDK->RegisterMethod(type, "void SetStyleSheet(const String& in)", asMETHOD(T, SetStyleSheet), asCALL_THISCALL);
}

extern "C" SDKFUNC void LoadModule(SmashSDK* sdk) {
    globSDK = sdk;

    // This module defines a custom entry point
    sdk->SetEntryPoint(EntryPoint);

    // GUIFont
    sdk->RegisterClass("GUIFont", 0, asOBJ_REF);
    sdk->RegisterBehaviour("GUIFont", asBEHAVE_FACTORY, "GUIFont@ f(const String& in, uint, bool, bool, bool)", asFUNCTION(GUIFontFactory), asCALL_CDECL);
    sdk->RegisterBehaviour("GUIFont", asBEHAVE_ADDREF, "void f()", asMETHOD(GUIFont, AddRef), asCALL_THISCALL);
    sdk->RegisterBehaviour("GUIFont", asBEHAVE_RELEASE, "void f()", asMETHOD(GUIFont, Release), asCALL_THISCALL);
    sdk->RegisterFunction("int RegisterGUIFont(const String& in)", asFUNCTION(GUIFont::Register), asCALL_CDECL);
    sdk->RegisterFunction("void UnregisterGUIFont(int)", asFUNCTION(GUIFont::Unregister), asCALL_CDECL);

    // GUIIcon
    sdk->RegisterClass("GUIIcon", 0, asOBJ_REF);
    sdk->RegisterBehaviour("GUIIcon", asBEHAVE_FACTORY, "GUIIcon@ f(const String& in)", asFUNCTION(GUIIconFactory), asCALL_CDECL);
    sdk->RegisterBehaviour("GUIIcon", asBEHAVE_ADDREF, "void f()", asMETHOD(GUIIcon, AddRef), asCALL_THISCALL);
    sdk->RegisterBehaviour("GUIIcon", asBEHAVE_RELEASE, "void f()", asMETHOD(GUIIcon, Release), asCALL_THISCALL);

    // Widget
    sdk->RegisterClass("Widget", 0, asOBJ_REF);
    sdk->RegisterBehaviour("Widget", asBEHAVE_FACTORY, "Widget@ f()", asFUNCTION(WidgetFactory), asCALL_CDECL);
    sdk->RegisterBehaviour("Widget", asBEHAVE_ADDREF, "void f()", asMETHOD(Widget, AddRef), asCALL_THISCALL);
    sdk->RegisterBehaviour("Widget", asBEHAVE_RELEASE, "void f()", asMETHOD(Widget, Release), asCALL_THISCALL);
    RegisterWidgetMembers<Widget>("Widget");

    // Button
    sdk->RegisterClass("Button", 0, asOBJ_REF);
    sdk->RegisterBehaviour("Button", asBEHAVE_FACTORY, "Button@ f(Widget@, const String& in)", asFUNCTION(ButtonFactory), asCALL_CDECL);
    sdk->RegisterBehaviour("Button", asBEHAVE_ADDREF, "void f()", asMETHOD(Button, AddRef), asCALL_THISCALL);
    sdk->RegisterBehaviour("Button", asBEHAVE_RELEASE, "void f()", asMETHOD(Button, Release), asCALL_THISCALL);
    sdk->RegisterBehaviour("Button", asBEHAVE_IMPLICIT_REF_CAST, "Widget@ f()", asFUNCTION((RefCast<Button, Widget>)), asCALL_CDECL_OBJFIRST);
    sdk->RegisterMethod("Button", "String Text() const", asMETHOD(Button, Text), asCALL_THISCALL);
    sdk->RegisterMethod("Button", "void SetText(const String& in)", asMETHOD(Button, SetText), asCALL_THISCALL);
    RegisterWidgetMembers<Button>("Button");

    // CheckBox
    sdk->RegisterGlobal("const int QCHECKBOX_UNCHECK", &qCheckBoxUncheck);
    sdk->RegisterGlobal("const int QCHECKBOX_CHECK", &qCheckBoxCheck);
    sdk->RegisterGlobal("const int QCHECKBOX_PARTIALCHECK", &qCheckBoxPartialCheck);
    sdk->RegisterClass("CheckBox", 0, asOBJ_REF);
    sdk->RegisterBehaviour("CheckBox", asBEHAVE_FACTORY, "CheckBox@ f(Widget@, const String& in)", asFUNCTION(CheckBoxFactory), asCALL_CDECL);
    sdk->RegisterBehaviour("CheckBox", asBEHAVE_ADDREF, "void f()", asMETHOD(CheckBox, AddRef), asCALL_THISCALL);
    sdk->RegisterBehaviour("CheckBox", asBEHAVE_RELEASE, "void f()", asMETHOD(CheckBox, Release), asCALL_THISCALL);
    sdk->RegisterBehaviour("CheckBox", asBEHAVE_IMPLICIT_REF_CAST, "Widget@ f()", asFUNCTION((RefCast<CheckBox, Widget>)), asCALL_CDECL_OBJFIRST);
    sdk->RegisterMethod("CheckBox", "int State() const", asMETHOD(CheckBox, State), asCALL_THISCALL);
    sdk->RegisterMethod("CheckBox", "void SetState(int)", asMETHOD(CheckBox, SetState), asCALL_THISCALL);
    RegisterWidgetMembers<CheckBox>("CheckBox");

    // ComboBox
    sdk->RegisterClass("ComboBox", 0, asOBJ_REF);
    sdk->RegisterBehaviour("ComboBox", asBEHAVE_FACTORY, "ComboBox@ f(Widget@)", asFUNCTION(ComboBoxFactory), asCALL_CDECL);
    sdk->RegisterBehaviour("ComboBox", asBEHAVE_ADDREF, "void f()", asMETHOD(ComboBox, AddRef), asCALL_THISCALL);
    sdk->RegisterBehaviour("ComboBox", asBEHAVE_RELEASE, "void f()", asMETHOD(ComboBox, Release), asCALL_THISCALL);
    sdk->RegisterBehaviour("ComboBox", asBEHAVE_IMPLICIT_REF_CAST, "Widget@ f()", asFUNCTION((RefCast<ComboBox, Widget>)), asCALL_CDECL_OBJFIRST);
    sdk->RegisterMethod("ComboBox", "void AddItem(const String& in)", asMETHOD(ComboBox, AddItem), asCALL_THISCALL);
    sdk->RegisterMethod("ComboBox", "uint CountItems() const", asMETHOD(ComboBox, CountItems), asCALL_THISCALL);
    sdk->RegisterMethod("ComboBox", "void RemoveItem(uint index)", asMETHOD(ComboBox, RemoveItem), asCALL_THISCALL);
    sdk->RegisterMethod("ComboBox", "uint Index() const", asMETHOD(ComboBox, Index), asCALL_THISCALL);
    sdk->RegisterMethod("ComboBox", "void SetIndex(uint index)", asMETHOD(ComboBox, SetIndex), asCALL_THISCALL);
    sdk->RegisterMethod("ComboBox", "String Text(uint index) const", asMETHOD(ComboBox, Text), asCALL_THISCALL);
    sdk->RegisterMethod("ComboBox", "void SetText(uint index, const String& in)", asMETHOD(ComboBox, SetText), asCALL_THISCALL);
    RegisterWidgetMembers<ComboBox>("ComboBox");

    // Editor
    sdk->RegisterClass("Editor", 0, asOBJ_REF);
    sdk->RegisterBehaviour("Editor", asBEHAVE_FACTORY, "Editor@ f(Widget@, bool, bool)", asFUNCTION(EditorFactory), asCALL_CDECL);
    sdk->RegisterBehaviour("Editor", asBEHAVE_ADDREF, "void f()", asMETHOD(Editor, AddRef), asCALL_THISCALL);
    sdk->RegisterBehaviour("Editor", asBEHAVE_RELEASE, "void f()", asMETHOD(Editor, Release), asCALL_THISCALL);
    sdk->RegisterBehaviour("Editor", asBEHAVE_IMPLICIT_REF_CAST, "Widget@ f()", asFUNCTION((RefCast<Editor, Widget>)), asCALL_CDECL_OBJFIRST);
    sdk->RegisterMethod("Editor", "void AddRule(const String& in, bool, int)", asMETHOD(Editor, AddRule), asCALL_THISCALL);
    sdk->RegisterMethod("Editor", "uint Column() const", asMETHOD(Editor, Column), asCALL_THISCALL);
    sdk->RegisterMethod("Editor", "uint CursorPos() const", asMETHOD(Editor, CursorPos), asCALL_THISCALL);
    sdk->RegisterMethod("Editor", "void SetCursorPos(uint)", asMETHOD(Editor, SetCursorPos), asCALL_THISCALL);
    sdk->RegisterMethod("Editor", "uint Line() const", asMETHOD(Editor, Line), asCALL_THISCALL);
    sdk->RegisterMethod("Editor", "String Text() const", asMETHOD(Editor, Text), asCALL_THISCALL);
    sdk->RegisterMethod("Editor", "void SetText(const String& in)", asMETHOD(Editor, SetText), asCALL_THISCALL);
    sdk->RegisterMethod("Editor", "uint SelectionLength() const", asMETHOD(Editor, SelectionLength), asCALL_THISCALL);
    sdk->RegisterMethod("Editor", "uint SelectionPos() const", asMETHOD(Editor, SelectionPos), asCALL_THISCALL);
    sdk->RegisterMethod("Editor", "void SelectText(uint, uint)", asMETHOD(Editor, SelectText), asCALL_THISCALL);
    sdk->RegisterMethod("Editor", "void SetFont(GUIFont& in)", asMETHOD(Editor, SetFont), asCALL_THISCALL);
    sdk->RegisterMethod("Editor", "void SetLineWrap(bool)", asMETHOD(Editor, SetLineWrap), asCALL_THISCALL);
    sdk->RegisterMethod("Editor", "void SetMultiLineComments(const String& in, const String& in, int)", asMETHOD(Editor, SetMultiLineComments), asCALL_THISCALL);
    sdk->RegisterMethod("Editor", "void SetTabSize(uint)", asMETHOD(Editor, SetTabSize), asCALL_THISCALL);
    sdk->RegisterMethod("Editor", "void Copy()", asMETHOD(Editor, Copy), asCALL_THISCALL);
    sdk->RegisterMethod("Editor", "void Cut()", asMETHOD(Editor, Cut), asCALL_THISCALL);
    sdk->RegisterMethod("Editor", "void Paste()", asMETHOD(Editor, Paste), asCALL_THISCALL);
    sdk->RegisterMethod("Editor", "void Redo()", asMETHOD(Editor, Redo), asCALL_THISCALL);
    sdk->RegisterMethod("Editor", "uint RedoSteps()", asMETHOD(Editor, RedoSteps), asCALL_THISCALL);
    sdk->RegisterMethod("Editor", "void Undo()", asMETHOD(Editor, Undo), asCALL_THISCALL);
    sdk->RegisterMethod("Editor", "uint UndoSteps()", asMETHOD(Editor, UndoSteps), asCALL_THISCALL);
    RegisterWidgetMembers<Editor>("Editor");

    // Frame
    sdk->RegisterGlobal("const int QFRAME_NOBORDER", &qFrameNoBorder);
    sdk->RegisterGlobal("const int QFRAME_BOX", &qFrameBox);
    sdk->RegisterGlobal("const int QFRAME_PANEL", &qFramePanel);
    sdk->RegisterGlobal("const int QFRAME_STYLED", &qFrameStyled);
    sdk->RegisterGlobal("const int QFRAME_PLAIN", &qFramePlain);
    sdk->RegisterGlobal("const int QFRAME_RAISED", &qFrameRaised);
    sdk->RegisterGlobal("const int QFRAME_SUNKEN", &qFrameSunken);
    sdk->RegisterClass("Frame", 0, asOBJ_REF);
    sdk->RegisterBehaviour("Frame", asBEHAVE_FACTORY, "Frame@ f(Widget@, int)", asFUNCTION(FrameFactory), asCALL_CDECL);
    sdk->RegisterBehaviour("Frame", asBEHAVE_ADDREF, "void f()", asMETHOD(Frame, AddRef), asCALL_THISCALL);
    sdk->RegisterBehaviour("Frame", asBEHAVE_RELEASE, "void f()", asMETHOD(Frame, Release), asCALL_THISCALL);
    sdk->RegisterBehaviour("Frame", asBEHAVE_IMPLICIT_REF_CAST, "Widget@ f()", asFUNCTION((RefCast<Frame, Widget>)), asCALL_CDECL_OBJFIRST);
    RegisterWidgetMembers<Frame>("Frame");

    // Label
    sdk->RegisterClass("Label", 0, asOBJ_REF);
    sdk->RegisterBehaviour("Label", asBEHAVE_FACTORY, "Label@ f(Widget@, const String& in)", asFUNCTION(LabelFactory), asCALL_CDECL);
    sdk->RegisterBehaviour("Label", asBEHAVE_ADDREF, "void f()", asMETHOD(Label, AddRef), asCALL_THISCALL);
    sdk->RegisterBehaviour("Label", asBEHAVE_RELEASE, "void f()", asMETHOD(Label, Release), asCALL_THISCALL);
    sdk->RegisterBehaviour("Label", asBEHAVE_IMPLICIT_REF_CAST, "Widget@ f()", asFUNCTION((RefCast<Label, Widget>)), asCALL_CDECL_OBJFIRST);
    sdk->RegisterMethod("Label", "String Text() const", asMETHOD(Label, Text), asCALL_THISCALL);
    sdk->RegisterMethod("Label", "void SetText(const String& in)", asMETHOD(Label, SetText), asCALL_THISCALL);
    RegisterWidgetMembers<Label>("Label");

    // LineEdit
    sdk->RegisterClass("LineEdit", 0, asOBJ_REF);
    sdk->RegisterBehaviour("LineEdit", asBEHAVE_FACTORY, "LineEdit@ f(Widget@, const String& in)", asFUNCTION(LineEditFactory), asCALL_CDECL);
    sdk->RegisterBehaviour("LineEdit", asBEHAVE_ADDREF, "void f()", asMETHOD(LineEdit, AddRef), asCALL_THISCALL);
    sdk->RegisterBehaviour("LineEdit", asBEHAVE_RELEASE, "void f()", asMETHOD(LineEdit, Release), asCALL_THISCALL);
    sdk->RegisterBehaviour("LineEdit", asBEHAVE_IMPLICIT_REF_CAST, "Widget@ f()", asFUNCTION((RefCast<LineEdit, Widget>)), asCALL_CDECL_OBJFIRST);
    sdk->RegisterMethod("LineEdit", "String Text() const", asMETHOD(LineEdit, Text), asCALL_THISCALL);
    sdk->RegisterMethod("LineEdit", "void SetText(const String& in)", asMETHOD(LineEdit, SetText), asCALL_THISCALL);
    RegisterWidgetMembers<LineEdit>("LineEdit");

    // Requester
    sdk->RegisterGlobal("const int QCONFIRM_CANCEL", &qConfirmCancel);
    sdk->RegisterGlobal("const int QCONFIRM_NO", &qConfirmNo);
    sdk->RegisterGlobal("const int QCONFIRM_YES", &qConfirmYes);
    sdk->RegisterGlobal("const int QNOTIFY_INFORMATION", &qNotifyInformation);
    sdk->RegisterGlobal("const int QNOTIFY_WARNING", &qNotifyWarning);
    sdk->RegisterGlobal("const int QNOTIFY_ERROR", &qNotifyError);
    sdk->RegisterFunction("int Confirm(Widget@, const String& in, const String& in, bool)", asFUNCTION(Requester::Confirm), asCALL_CDECL);
    sdk->RegisterFunction("void Notify(Widget@, const String& in, const String& in, int)", asFUNCTION(Requester::Notify), asCALL_CDECL);
    sdk->RegisterFunction("String RequestFile(Widget@, const String& in, const String& in, const String& in, bool)", asFUNCTION(Requester::RequestFile), asCALL_CDECL);

    // TabBar
    sdk->RegisterClass("TabBar", 0, asOBJ_REF);
    sdk->RegisterBehaviour("TabBar", asBEHAVE_FACTORY, "TabBar@ f(Widget@)", asFUNCTION(TabBarFactory), asCALL_CDECL);
    sdk->RegisterBehaviour("TabBar", asBEHAVE_ADDREF, "void f()", asMETHOD(TabBar, AddRef), asCALL_THISCALL);
    sdk->RegisterBehaviour("TabBar", asBEHAVE_RELEASE, "void f()", asMETHOD(TabBar, Release), asCALL_THISCALL);
    sdk->RegisterBehaviour("TabBar", asBEHAVE_IMPLICIT_REF_CAST, "Widget@ f()", asFUNCTION((RefCast<TabBar, Widget>)), asCALL_CDECL_OBJFIRST);
    sdk->RegisterMethod("TabBar", "void AddItem(Widget& inout, const String& in)", asMETHOD(TabBar, AddItem), asCALL_THISCALL);
    sdk->RegisterMethod("TabBar", "uint CountItems() const", asMETHOD(TabBar, CountItems), asCALL_THISCALL);
    sdk->RegisterMethod("TabBar", "void RemoveItem(uint)", asMETHOD(TabBar, RemoveItem), asCALL_THISCALL);
    sdk->RegisterMethod("TabBar", "uint Index() const", asMETHOD(TabBar, Index), asCALL_THISCALL);
    sdk->RegisterMethod("TabBar", "void SetIndex(uint)", asMETHOD(TabBar, SetIndex), asCALL_THISCALL);
    sdk->RegisterMethod("TabBar", "String Text(uint) const", asMETHOD(TabBar, Text), asCALL_THISCALL);
    sdk->RegisterMethod("TabBar", "void SetText(uint, const String& in)", asMETHOD(TabBar, SetText), asCALL_THISCALL);
    sdk->RegisterMethod("TabBar", "const Widget& GetWidget(uint) const", asMETHOD(TabBar, GetConstWidget), asCALL_THISCALL);
    sdk->RegisterMethod("TabBar", "Widget& GetWidget(uint)", asMETHOD(TabBar, GetWidget), asCALL_THISCALL);
    RegisterWidgetMembers<TabBar>("TabBar");

    // Window
    sdk->RegisterGlobal("const int QWINDOW_STANDARD", &qWindowStandard);
    sdk->RegisterGlobal("const int QWINDOW_TOOL", &qWindowTool);
    sdk->RegisterGlobal("const int QWINDOW_MODAL", &qWindowModal);
    sdk->RegisterGlobal("const int QWINDOW_SHEET", &qWindowSheet);
    sdk->RegisterGlobal("const int QWINDOW_CENTERED", &qWindowCentered);
    sdk->RegisterClass("Window", 0, asOBJ_REF);
    sdk->RegisterBehaviour("Window", asBEHAVE_FACTORY, "Window@ f(Widget@, int, int, int, int, int)", asFUNCTION(WindowFactory), asCALL_CDECL);
    sdk->RegisterBehaviour("Window", asBEHAVE_ADDREF, "void f()", asMETHOD(Window, AddRef), asCALL_THISCALL);
    sdk->RegisterBehaviour("Window", asBEHAVE_RELEASE, "void f()", asMETHOD(Window, Release), asCALL_THISCALL);
    sdk->RegisterBehaviour("Window", asBEHAVE_IMPLICIT_REF_CAST, "Widget@ f()", asFUNCTION((RefCast<Window, Widget>)), asCALL_CDECL_OBJFIRST);
    sdk->RegisterMethod("Window", "void SetTitle(const String& in)", asMETHOD(Window, SetTitle), asCALL_THISCALL);
    RegisterWidgetMembers<Window>("Window");

    // Menu
    sdk->RegisterClass("Menu", 0, asOBJ_REF | asOBJ_NOCOUNT);
    sdk->RegisterMethod("Menu", "void AddItem(int, const String& in, const String& in)", asMETHOD(Menu, AddItem), asCALL_THISCALL);
    sdk->RegisterMethod("Menu", "void AddSeparator()", asMETHOD(Menu, AddSeparator), asCALL_THISCALL);
    RegisterWidgetMembers<Menu>("Menu");

    // MenuBar (requires Window and Menu)
    sdk->RegisterClass("MenuBar", 0, asOBJ_REF);
    sdk->RegisterBehaviour("MenuBar", asBEHAVE_FACTORY, "MenuBar@ f(Window&)", asFUNCTION(MenuBarFactory), asCALL_CDECL);
    sdk->RegisterBehaviour("MenuBar", asBEHAVE_ADDREF, "void f()", asMETHOD(MenuBar, AddRef), asCALL_THISCALL);
    sdk->RegisterBehaviour("MenuBar", asBEHAVE_RELEASE, "void f()", asMETHOD(MenuBar, Release), asCALL_THISCALL);
    sdk->RegisterBehaviour("MenuBar", asBEHAVE_IMPLICIT_REF_CAST, "Widget@ f()", asFUNCTION((RefCast<MenuBar, Widget>)), asCALL_CDECL_OBJFIRST);
    sdk->RegisterMethod("MenuBar", "Menu& AddTitle(const String& in)", asMETHOD(MenuBar, AddTitle), asCALL_THISCALL);
    RegisterWidgetMembers<MenuBar>("MenuBar");

    // StatusBar (requires Window)
    sdk->RegisterClass("StatusBar", 0, asOBJ_REF);
    sdk->RegisterBehaviour("StatusBar", asBEHAVE_FACTORY, "StatusBar@ f(Window&)", asFUNCTION(StatusBarFactory), asCALL_CDECL);
    sdk->RegisterBehaviour("StatusBar", asBEHAVE_ADDREF, "void f()", asMETHOD(StatusBar, AddRef), asCALL_THISCALL);
    sdk->RegisterBehaviour("StatusBar", asBEHAVE_RELEASE, "void f()", asMETHOD(StatusBar, Release), asCALL_THISCALL);
    sdk->RegisterBehaviour("StatusBar", asBEHAVE_IMPLICIT_REF_CAST, "Widget@ f()", asFUNCTION((RefCast<StatusBar, Widget>)), asCALL_CDECL_OBJFIRST);
    sdk->RegisterMethod("StatusBar", "void SetText(const String& in)", asMETHOD(StatusBar, SetText), asCALL_THISCALL);
    RegisterWidgetMembers<StatusBar>("StatusBar");

    // ToolBar (requires Window and GUIIcon)
    sdk->RegisterClass("ToolBar", 0, asOBJ_REF);
    sdk->RegisterBehaviour("ToolBar", asBEHAVE_FACTORY, "ToolBar@ f(Window&)", asFUNCTION(ToolBarFactory), asCALL_CDECL);
    sdk->RegisterBehaviour("ToolBar", asBEHAVE_ADDREF, "void f()", asMETHOD(ToolBar, AddRef), asCALL_THISCALL);
    sdk->RegisterBehaviour("ToolBar", asBEHAVE_RELEASE, "void f()", asMETHOD(ToolBar, Release), asCALL_THISCALL);
    sdk->RegisterBehaviour("ToolBar", asBEHAVE_IMPLICIT_REF_CAST, "Widget@ f()", asFUNCTION((RefCast<ToolBar, Widget>)), asCALL_CDECL_OBJFIRST);
    sdk->RegisterMethod("ToolBar", "void AddButton(int, GUIIcon&, const String& in)", asMETHOD(ToolBar, AddButton), asCALL_THISCALL);
    sdk->RegisterMethod("ToolBar", "void AddSeparator()", asMETHOD(ToolBar, AddSeparator), asCALL_THISCALL);
    sdk->RegisterMethod("ToolBar", "void AddWidget(Widget& widget)", asMETHOD(ToolBar, AddWidget), asCALL_THISCALL);
    RegisterWidgetMembers<ToolBar>("ToolBar");

    // Process
    sdk->RegisterClass("Process", 0, asOBJ_REF);
    sdk->RegisterBehaviour("Process", asBEHAVE_FACTORY, "Process@ f(const String& in)", asFUNCTION(ProcessFactory), asCALL_CDECL);
    sdk->RegisterBehaviour("Process", asBEHAVE_ADDREF, "void f()", asMETHOD(Process, AddRef), asCALL_THISCALL);
    sdk->RegisterBehaviour("Process", asBEHAVE_RELEASE, "void f()", asMETHOD(Process, Release), asCALL_THISCALL);
    sdk->RegisterMethod("Process", "void Run()", asMETHOD(Process, Run), asCALL_THISCALL);
    sdk->RegisterMethod("Process", "void Terminate()", asMETHOD(Process, Terminate), asCALL_THISCALL);
    sdk->RegisterMethod("Process", "String Output() const", asMETHOD(Process, Output), asCALL_THISCALL);
    sdk->RegisterMethod("Process", "String Error() const", asMETHOD(Process, Error), asCALL_THISCALL);

    // IApplication interface (requires "Window")
    sdk->RegisterInterface("IApplication");
    sdk->RegisterInterfaceMethod("IApplication", "void OnInit()");
    sdk->RegisterInterfaceMethod("IApplication", "void OnCloseWindow(Window@)");
    sdk->RegisterInterfaceMethod("IApplication", "void OnSizeWindow(Window@)");
    sdk->RegisterInterfaceMethod("IApplication", "void OnMenuAction(int)");
    sdk->RegisterInterfaceMethod("IApplication", "void OnWidgetAction(Widget@, int)");
    sdk->RegisterInterfaceMethod("IApplication", "void OnProcessFinish(Process@, int)");
    sdk->RegisterInterfaceMethod("IApplication", "void OnProcessOutput(Process@)");
    sdk->RegisterInterfaceMethod("IApplication", "void OnProcessError(Process@, bool)");

    // App (requires IApplication)
    sdk->RegisterFunction("IApplication& AppInstance()", asFUNCTION(AppInstance), asCALL_CDECL);
}
