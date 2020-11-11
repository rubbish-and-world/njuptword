#pragma once
#include "Wordlist.hpp"
#include "Card.hpp"
#include <string>
#include <vector>
class Deck{
    string name;
    vector<Wordlist> lists;
    int total_score = 0;
    int standard_score = 0;

    void update_t_score();

public:
    Deck(const string & na = "Unamed" , vector<Wordlist> wl = vector<Wordlist>() ) : name(na)  , lists (wl) {}
    void show_all();
    void set_standard_score(int num){ standard_score = num;}
    void add_list(Wordlist & wls) { lists.push_back(wls) ; }
    Wordlist& select_wordlist(int index){ lists.at(index).show_cards() ; return lists.at(index);}    


//interface
    string get_name() { return name ;}
};

void Deck::update_t_score(){
    int sum = 0;
    for (auto i : lists){
        sum += i.get_score();
    }
    total_score = sum;
}


void Deck::show_all(){
    update_t_score();
    cout << "total score of current deck is : " << total_score << endl;
    cout << "----------- wordlists -----------" << endl;
    for (int i = 0 ; i < lists.size() ; ++i){
        cout << i << ". " << lists[i].get_name() << endl;
    }
    cout << "----------- wordlists -----------" << endl;
}



