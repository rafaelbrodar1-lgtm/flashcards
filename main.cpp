#include <iostream>
#include "Material.h"
#include <QApplication>
#include <QWidget>
#include <QLabel>

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    QLabel label("");
    
    Category g("Mathematics");
    g.addCard(Card("What is 2 + 2?", "4"));
    g.addCard(Card("What is 3 * 3?", "9"));
    QString text = QString::fromStdString(g.displayCards());
    label.setText(text);
    label.show();
    return app.exec();
}