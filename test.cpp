#include <iostream>
#include "Card.hpp"
#include "Wordlist.hpp"
#include "Deck.hpp"
#include "User.hpp"
#include <algorithm>
#include <vector>
using namespace std;
int main(){
    vector<string> w1 = {"shit" , "sun" , "die"};
    vector<string> w2 = {"💩" , "🌞" , "死"};
    Card cardtest(w1, w2 , "milk","牛奶","n","white");
    Card cd ("cannibal","食人族","n","terrifying");
    Wordlist wls ;
    wls.add_card(cardtest);
    wls.add_card(cd);
    Deck deck ("my");
    deck.add_list(wls);
    deck.show_all();

    vector<User> users; //load from file

    cout << "------   Welcome to WordSystem   ------" << endl;



    return 0;


}