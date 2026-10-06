#include <iostream>
#include "Material.h"

int main() {
    
    Category g("Mathematics");
    g.addCard(Card("What is 2 + 2?", "4"));
    g.addCard(Card("What is 3 * 3?", "9"));
    g.displayCards();

    return 0;
}