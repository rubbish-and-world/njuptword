#pragma once 
#include "Deck.hpp"
#include <string>
#include <vector>
#include "json.hpp"
#include <ctime>
using Json = nlohmann::json;
using namespace std;
class User{
    string type = "user";
    string name;
    string password;
    vector<Deck> decks;
    vector<string> marks;


public:
    User(const string & ac = "undefined" , const string & ps = "undefined" , vector<Deck> dk = vector<Deck>()):
    name(ac) , password(ps) , decks(dk){}
    void add_deck(Deck  dk) {decks.push_back(dk);}
    Deck& select_deck(int index){  return decks.at(index);}
    void remove(int i);
    void mark();
    void show_marks();

//interface
    string get_name() { return name ;}
    string get_password() { return password ;}
    void show_decks();

//work with json
    User(const Json& juser):name(juser["name"]),password(juser["password"]),decks(juser["decks"].get<vector<Deck>>()),marks(juser["marks"].get<vector<string>>()){
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

void User::mark(){
    bool make_mark = true;
    time_t rawtime  = time(nullptr);
    tm * now_ptr = localtime(&rawtime);
    tm now = *now_ptr;
    if(!marks.empty()){
        tm last ;
        strptime(marks.back().c_str(), "%c", &last);
        if(last.tm_year == now.tm_year &&
            last.tm_mon == now.tm_mon && 
            last.tm_mday==now.tm_mday ){
                cout << RED << "you have already marked today, see you tomorrow!" << DEF << endl;
                make_mark = false;
            }
    }

    if(make_mark){
        string mark (asctime(now_ptr));
        cout << GRN << "marked successfully, marking at : " << mark << DEF ;
        marks.push_back(mark);
    }
}

void User::show_marks(){
    cout << "now you have " << GRN << marks.size() << DEF << " marks, keep going !" << endl;
    cout << "----------- marks -----------" << endl;
    for(auto i : marks){
        cout << i << endl;
    }
    cout << "----------- marks -----------" << endl;

}