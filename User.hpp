#pragma once 
#include "Deck.hpp"
#include <string>
#include <vector>
#include "json.hpp"
using Json = nlohmann::json;
class User{
    string type = "user";
    string name;
    string password;
    vector<Deck> decks;


public:
    User(const string & ac = "undefined" , const string & ps = "undefined" , vector<Deck> dk = vector<Deck>()):
    name(ac) , password(ps) , decks(dk){}
    void add_deck(Deck & dk) {decks.push_back(dk);}
    Deck& select_deck(int index){  return decks.at(index);}
    void remove(int i);
//interface
    string get_name() { return name ;}
    string get_password() { return password ;}
    void show_decks();

//work with json
    User(const Json& juser):name(juser["name"]),password(juser["password"]),decks(juser["decks"].get<vector<Deck>>()){
        // cout << "user" << endl;
    }

//friend
friend void from_json(const Json & j , User & u);
friend void to_json(Json & j , const User & u);
};


void User::show_decks(){
    cout << "----------- decks -----------" << endl;
    for (int i =0 ; i < decks.size() ; ++i){
        cout << i << " : " << decks[i].get_name() << endl;
    }
    cout << "----------- decks -----------" << endl;
}

void User::remove(int i){
    auto bg = decks.begin();
    decks.erase(bg +i);
    
}