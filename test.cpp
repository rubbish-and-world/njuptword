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
    Wordlist wls("mywordlist") ;
    wls.add_card(cardtest);
    wls.add_card(cd);
    Deck deck ("my");
    deck.add_list(wls);
    // deck.show_all();

    vector<User> users; //load from file
    users.push_back(User("user1","pass"));
    users[0].add_deck(deck);


    cout << "------   Welcome to WordSystem   ------" << endl;
    User current;
    cout << "enter your account :";
    string enter ;
    int option;
    cin >> enter ;
    for (auto i : users){
        if (enter == i.get_account()){
            current = i;
            break;
        }
    }
    if(current.get_account() == "undefined"){
        cout << "account not found" << endl;
        exit(0);
    }
    else{
        cout << "your passowrd :";
        while(cin >> enter){
            if (enter == current.get_password()){
                break;
            }
            cout << "wrong password, again" << endl;
        }
    }
    current.show_decks();
    cout << "select deck :";
    cin >> option;
    Deck c_deck = current.select_deck(option);
    cout << "select wordlist :";
    cin >> option;
    Wordlist c_wordlist = c_deck.select_wordlist(option);
    c_wordlist.study_card();
    



    return 0;


}