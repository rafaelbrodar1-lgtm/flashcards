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
        QLabel *testQuestion;
        QLabel *testAnswer;
        int testIndex = 0;
        void showCurrentCard();
     

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
    QPushButton *testButton = new QPushButton("Test");
    categoryLayout->addWidget(categoryTitle);
    categoryLayout->addWidget(cardsList);
    categoryLayout->addWidget(testButton);
    categoryLayout->addWidget(addFlashcardButton);
    categoryLayout->addWidget(backButton);

    
    

    QWidget *testPage = new QWidget;
    QVBoxLayout *testLayout = new QVBoxLayout(testPage);
    testQuestion = new QLabel;
    testAnswer = new QLabel;
    testQuestion->setWordWrap(true);
    QPushButton *showAnswerButton = new QPushButton("Show answer");
    QPushButton *nextButton = new QPushButton("Next");
    QPushButton *testBackButton = new QPushButton("Back");
    testLayout->addWidget(testQuestion);
    testLayout->addWidget(testAnswer);
    testLayout->addWidget(showAnswerButton);
    testLayout->addWidget(nextButton);
    testLayout->addWidget(testBackButton);
    

    stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(categoriesPage);
    stackedWidget->addWidget(categoryPage);
    stackedWidget->addWidget(testPage); 
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

    connect(testButton, &QPushButton::clicked, this, [this]() {
        if (currentCategory < 0) return;
        if (categories[currentCategory].getCards().empty()) {
            QMessageBox::warning(this, "Warning", "No cards in this category");
            return;
        }
        testIndex = 0;
        showCurrentCard();
        stackedWidget->setCurrentIndex(2);
    });

    connect(showAnswerButton, &QPushButton::clicked, this, [this]() {
        testAnswer->setText(QString::fromStdString(categories[currentCategory].getCards()[testIndex].getAnswer()));
    });

    connect(nextButton, &QPushButton::clicked, this, [this]() {
        testIndex++;
        if (testIndex >= categories[currentCategory].getCards().size()) {
            QMessageBox::information(this, "Done", "End of cards");
            stackedWidget->setCurrentIndex(1);
            return;
        }
        showCurrentCard();
    });

    connect(testBackButton, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentIndex(1);
    });

    connect(backButton, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentIndex(0);
    });

}

void MainWindow::showCurrentCard() {
    const auto& cards = categories[currentCategory].getCards();
    testQuestion->setText(QString::fromStdString(cards[testIndex].getQuestion()));
    testAnswer->setText("");
}
    


int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    return app.exec();
}