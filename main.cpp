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
        QStackedWidget *stackedWidget;
        QListWidget *cardsList;
        QLabel *categoryTitle;
        int currentCategory = -1;
     

    public : 
        MainWindow(QWidget *parent = nullptr); 
};


MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Flashcards");



    QWidget *categoriesPage = new QWidget(this);
    QVBoxLayout *categoriesLayout = new QVBoxLayout(categoriesPage);
    categoryList = new QListWidget;
    QPushButton *addCategoryButton = new QPushButton("Add Category");
    categoriesLayout->addWidget(categoryList);
    categoriesLayout->addWidget(addCategoryButton);

    QWidget *categoryPage = new QWidget;
    QVBoxLayout *categoryLayout = new QVBoxLayout(categoryPage);
    categoryTitle = new QLabel("Category: ");
    cardsList = new QListWidget;
    QPushButton *addFlashcardButton = new QPushButton("Add Flashcard");
    QPushButton *backButton = new QPushButton("Back");
    categoryLayout->addWidget(categoryTitle);
    categoryLayout->addWidget(cardsList);
    categoryLayout->addWidget(addFlashcardButton);
    categoryLayout->addWidget(backButton);



    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(categoriesPage);
    stackedWidget->addWidget(categoryPage);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stackedWidget);


    connect(addCategoryButton, &QPushButton::clicked, this, [this]() {
        bool ok;
        QString categoryName = QInputDialog::getText(this, "Add Category", "Category Name:", QLineEdit::Normal, "", &ok);
        if (ok && !categoryName.isEmpty()) {
            Category newCategory(categoryName.toStdString());
            categories.push_back(newCategory);
            categoryList->addItem(categoryName);
        }
    });

    connect(categoryList, &QListWidget::itemDoubleClicked, this, [this]() {
        int i = categoryList->currentRow();
        if (i<0) return;
        currentCategory = i;
        categoryTitle->setText("Category: " + QString::fromStdString(categories[i].getName()));
        cardsList->clear();
        for (const auto& card : categories[i].getCards()) {
            cardsList->addItem(QString::fromStdString("Q: " + card.getQuestion() + " | A: " + card.getAnswer()));
        }
        stackedWidget->setCurrentIndex(1);
    });

    connect(addFlashcardButton, &QPushButton::clicked, this, [this]() {
        if (currentCategory < 0) return;
        bool ok;
        QString q = QInputDialog::getText(this, "Add Flashcard", "Question:", QLineEdit::Normal, "", &ok);
        if (!ok || q.isEmpty()) return;
        QString a = QInputDialog::getText(this, "Add Flashcard", "Answer:", QLineEdit::Normal, "", &ok);
        if (!ok || a.isEmpty()) return;

        categories[currentCategory].addCard(q.toStdString(), a.toStdString());
        cardsList->addItem(q);

    });

    connect(backButton, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentIndex(0);
    });


    

    
}


int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    return app.exec();
}