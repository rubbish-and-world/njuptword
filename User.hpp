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


};

bool User::check_password(){
    string input ;
    cout << "enter your password:" << endl;
    cin >> input ;
    return (input == password);
}
