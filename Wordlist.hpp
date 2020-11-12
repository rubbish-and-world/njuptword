#pragma once
#include "Card.hpp"
#include "color.hpp"
#include <string>
#include <vector>
#include "json.hpp"
using Json = nlohmann::json;
using namespace std;
class Wordlist{
    string type = "wordlist";
    string name ;
    vector<Card> cards;
    vector<Card> hidden; //错题本
    int score =0;
    int standard=0;


    void change_score(bool flag);
    bool decreaseable(){ return score >= 10 ;}
    bool increaseable(){ return score <= 10000000;}
    bool meet(){ return score >= standard;}
    void study_whole_list(int m_num , vector<Card> & list);



public:
    Wordlist(vector<Card> cs = vector<Card>(), const string & na = "unamed"  ):name(na),cards(cs){ }
    Wordlist(const string & na ):name(na){ }
    void add_card(Card & c){ cards.push_back(c);}
    void show_cards();
    void review(int mode);
    void study(int mode);

    void set_standard(int num){ standard = num;}
    Card& select_card(int num ){return cards.at(num);}

    void show_score();
    void remove(int l_index);



//get value interface
    int get_score(){ return score;}
    int get_standard(){ return standard;}
    string get_name() { return name ; }

//work with json
    Wordlist(const Json & jwordlist):name(jwordlist["name"]),score(jwordlist["score"]),standard(jwordlist["standard"])
    ,cards(jwordlist["cards"].get<vector<Card>>()) , hidden(jwordlist["hidden"].get<vector<Card>>()){
    }

//friends
friend void from_json(const Json & j , Wordlist & w);
friend void to_json(Json & j , const Wordlist & w);

};

void Wordlist::study(int mode){
        study_whole_list(mode , cards);
        cout << BLU << "Study finished!" << DEF << endl;
        cout << BLU << hidden.size() << " wrong to be reviewed." << DEF << endl;
    }

void Wordlist::review(int mode){
    int temp = hidden.size();
    study_whole_list(mode , hidden);
    hidden.erase(hidden.begin() , hidden.begin() + temp);
    cout << BLU << temp << " words reviewed. Now " << hidden.size() << " wrong words left" << DEF << endl;
}

void Wordlist::show_cards(){
    cout << "----------- cards -----------" << endl;
    for (int i = 0 ; i < cards.size() ; ++i){
        cards[i].show_all(i);
    }
    cout << "----------- cards -----------" << endl;
}

void Wordlist::change_score(bool flag){
    if(!flag){
        if(decreaseable()){
            score -= 10;
        }
        else{
            score = 0;
        cout <<BLU <<  "your score is 0 now *_*" << DEF <<endl;
        }
    }
    else{
        if(increaseable()){ score += 10;}
        else{
            cout <<BLU <<  "your score cannot be higher!" <<DEF << endl;
        }
    }

}

void Wordlist::study_whole_list(int m_num, vector<Card> & list){
    vector<Card> buffer;
    bool right ;
    switch(m_num){
        case 1:{
            for(auto c :list){
                bool right = c.recite_choice_e2c();
                if(!right) {
                    buffer.push_back(c);
                }
                change_score(right);
            }
            break;
        }
        case 2:{
            for(auto c :list){
                bool right = c.recite_choice_c2e();
                if(!right) {
                    buffer.push_back(c);
                }
                change_score(right);
            }
            break;
        }
        case 3:{
            for(auto c :list){
                bool right = c.recite_spell_c2e();
                if(!right) {
                    buffer.push_back(c);
                }
                change_score(right);
            }
            break;
        }
        case 4:{
            for(auto c :list){
                bool right = c.recite_spell_e2c();
                if(!right) {
                    buffer.push_back(c);
                }
                change_score(right);
            }
            break;
        }
        default:{
            cout << RED << "no such mode" << DEF << endl;
        }
    }

    hidden.insert(hidden.end(),buffer.begin(),buffer.end());

    
}


void Wordlist::show_score(){
    cout << "-> " << name << " : " << score<<"/"<<standard << " ";
    if(meet()){
        cout <<GRN<< "✓" <<DEF<< endl;
    }
    else{
        cout << RED << "✗" << DEF << endl;
    }
}

void Wordlist::remove(int l_index){
    auto bg = cards.begin();
    cards.erase(bg + l_index);

}
