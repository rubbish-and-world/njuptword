#pragma once
#include "Wordlist.hpp"
#include "Card.hpp"
#include <string>
#include <vector>
class Deck{
    string name;
    vector<Wordlist> lists;

public:
    Deck(const string & na = "Unamed" , vector<Wordlist> wl = vector<Wordlist>() ) : name(na)  , lists (wl) {}
    void show_all();
    void add_list(Wordlist & wls) { lists.push_back(wls) ; }
};

void Deck::show_all(){
    for (auto i : lists){
        cout << i.get_name() << endl;
    }
}

