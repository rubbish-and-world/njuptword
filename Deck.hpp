#pragma once
#include "json.hpp"
using Json = nlohmann::json;
#include "Wordlist.hpp"
#include "Card.hpp"
#include <string>
#include <vector>
#include "color.hpp"
class Deck{
    string type = "deck";
    string name;
    vector<Wordlist> wordlists;
    int total_score = 0;
    int standard_score = 0;


    void update_t_score();
    bool meet(){ return total_score >= standard_score;}

public:
    Deck(const string & na = "Unamed" , vector<Wordlist> wl = vector<Wordlist>() ) : name(na)  , wordlists (wl) {}
    void set_standard_score(int num){ standard_score = num;}
    void add_list(Wordlist & wls) { wordlists.push_back(wls) ; }
    Wordlist& select_wordlist(int index){  return wordlists.at(index);}    

    void show_wordlists();
    void show_score();
    void remove(int i);

//interface
    string get_name() { return name ;}


//work with json
    Deck(const Json & jdeck):name(jdeck["name"]),wordlists(jdeck["wordlists"].get<vector<Wordlist>>()),
    total_score(jdeck["total_score"]),standard_score(jdeck["standard_score"]){
    }

//friend
friend void from_json(const Json & j , Deck & d );
friend void to_json(Json & j , const Deck & d);



};

void Deck::update_t_score(){
    int sum = 0;
    for (auto i : wordlists){
        sum += i.get_score();
    }
    total_score = sum;
}


void Deck::show_wordlists(){
    cout << "----------- wordlist -----------" << endl;
    for (int i = 0 ; i < wordlists.size() ; ++i){
        cout << i << ". " << wordlists[i].get_name() << endl;
    }
    cout << "----------- wordlist -----------" << endl;
}


void Deck::show_score(){
    update_t_score();
    cout << "----------- score -----------" << endl;
    cout << "total score of current deck : " << total_score << endl;
    cout << "standard score of current deck : " << standard_score << endl;
    if(meet()){
    cout << GRN << "requirement satisfied!" << DEF << endl;
    }
    else{
    cout << RED << "standard not met, please wrok harderrrrr!" << DEF << endl;
    }
    cout << "Details ->"<<endl;
    for (int i = 0 ; i < wordlists.size() ; ++i){
        wordlists[i].show_score();
    }
    cout << "----------- score -----------" << endl;

}

void Deck::remove(int index){
    auto bg = wordlists.begin();
    wordlists.erase(bg + index);
    
}