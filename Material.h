#pragma once
#include <iostream>
#include <string>
#include <vector>
using namespace std;


class Card {
    private:
        string question;
        string answer;
    public:
        Card(string q = "", string a = "") {
            question = q;
            answer = a;
        }
        string getQuestion() const {
            return question;
        }
        string getAnswer() const {
            return answer;
        }
};

class Category {
    private:
        string name;
        vector<Card> cards;
    public:
        Category(string n = "") {
            name = n;
        }
        void addCard(Card c) {
            cards.push_back(c);
        }
        string getName() {
            return name;
        }
        const vector<Card>& getCards() const {
            return cards;
        }

        void addCard(string p, string o) {
            Card k(p, o);
            cards.push_back(k);
        }
        string displayCards() const {
            string result = "Cards for subject: " + name + "\n";
            for (const auto& c : cards) {
                result += "Question: " + c.getQuestion() + ", Answer: " + c.getAnswer() + "\n";
            }
            return result;
        }

        bool checkAnswer(int index, string answer) const {
            if (index < 0 || index >= cards.size()) {
                cout << "Invalid card index." << endl;
                return false;
            }
            return cards[index].getAnswer() == answer;
        }
};