#include "tabbar.h"
#include "event.h"
#include <QTabWidget>

TabBar::TabBar(Widget* parent) {
    // Fix parent
    QWidget* qtParent = NULL;
    if ( parent ) qtParent = parent->QtWidget();

    // Create TabBar
    QTabWidget* tabbar = new QTabWidget(qtParent);
    QObject::connect(tabbar, SIGNAL(currentChanged(int)), &GetEventDispatcher(), SLOT(TabBarChangedIndex(int)));

    // Set Qt widget
    SetQtWidget(tabbar);
}

TabBar::~TabBar() {
    for ( int i = 0; i < widgets.Size(); i++ ) {
        widgets[i]->Release();
    }
}

void TabBar::AddItem(Widget* item, const String& text) {
    ((QTabWidget*)QtWidget())->addTab(item->QtWidget(), text.ToCString());
}

unsigned int TabBar::CountItems() const {
    return ((QTabWidget*)QtWidget())->count();
}

void TabBar::RemoveItem(unsigned int index) {
    ((QTabWidget*)QtWidget())->removeTab(index);
    widgets[index]->Release();
    widgets.RemoveAt(index);
}

unsigned int TabBar::Index() const {
    return ((QTabWidget*)QtWidget())->currentIndex();
}

void TabBar::SetIndex(unsigned int index) {
    ((QTabWidget*)QtWidget())->setCurrentIndex(index);
}

String TabBar::Text(unsigned int index) const {
    return ((QTabWidget*)QtWidget())->tabText(index).toStdString().c_str();
}

void TabBar::SetText(unsigned int index, const String& text) {
    ((QTabWidget*)QtWidget())->setTabText(index, text.ToCString());
}

const Widget* TabBar::GetConstWidget(unsigned int index) const {
    return widgets[index];
}

Widget* TabBar::GetWidget(unsigned int index) {
    return widgets[index];
}
