#pragma once 
#include "Deck.hpp"
#include <string>
#include <vector>
class User{
    string account;
    string password;
    vector<Deck> decks;
    int score = 0;


    bool check_password();


public:
    User(const string & ac = "undefined" , const string & ps = "undefined" , vector<Deck> dk = vector<Deck>()):
    account(ac) , password(ps) , decks(dk){}
    void add_deck(Deck & dk) {decks.push_back(dk);}
    Deck& select_deck(int index){ decks.at(index).show_all(); return decks.at(index);}

//interface
    string get_account() { return account ;}
    string get_password() { return password ;}
    void show_decks();


};

bool User::check_password(){
    string input ;
    cout << "enter your password:" << endl;
    cin >> input ;
    return (input == password);
}

void User::show_decks(){
    cout << "----------- decks -----------" << endl;
    for (int i =0 ; i < decks.size() ; ++i){
        cout << i << " : " << decks[i].get_name() << endl;
    }
    cout << "----------- decks -----------" << endl;
}
