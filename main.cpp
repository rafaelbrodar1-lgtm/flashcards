#include <iostream>
#include "Material.h"
#include <vector>
#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QFont>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QInputDialog>
#include <QMessageBox>
#include <QStackedWidget>

class MainWindow : public QWidget {
    private:
        vector<Category> categories;
        QListWidget *categoryList;

    public : 
        MainWindow(QWidget *parent = nullptr); 
};


MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Flashcards");
    categoryList = new QListWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(categoryList);
    QPushButton *addCategoryButton = new QPushButton("Add Category", this);
    layout->addWidget(addCategoryButton);

    connect(addCategoryButton, &QPushButton::clicked, this, [this]() {
        bool ok;
        QString categoryName = QInputDialog::getText(this, "Add Category", "Category Name:", QLineEdit::Normal, "", &ok);
        if (ok && !categoryName.isEmpty()) {
            Category newCategory(categoryName.toStdString());
            categories.push_back(newCategory);
            categoryList->addItem(categoryName);
        }
    });

    connect (categoryList, &QListWidget::itemDoubleClicked, this, [this]() {
        int i = categoryList->currentRow();
        if (i >= 0 && i < categories.size()) {
            Category &selectedCategory = categories[i];
            QString cardsInfo = QString::fromStdString(selectedCategory.displayCards());
            QMessageBox::information(this, "Cards in " + categoryList->currentItem()->text(), cardsInfo);
        }
    });
    
}


int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    return app.exec();
}