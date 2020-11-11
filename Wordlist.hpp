#pragma once
#include "Card.hpp"
#include <string>
#include <vector>
using namespace std;
class Wordlist{
    string name ;
    size_t size ;
    vector<Card> cards;
    vector<Card> hidden; //错题本
    
    int score =0;
    int standard=0;

    bool decreaseable(){ return score >= 10 ;}
    bool increaseable(){ return score <= 10000000;}



public:
    Wordlist(vector<Card> cs = vector<Card>(), const string & na = "unamed"  ):name(na),cards(cs){ size = cards.size() ;}
    Wordlist(const string & na = "unamed"  ):name(na){ size = cards.size() ;}
    void add_card(Card & c);
    void show_cards();
    void study_card();
    void set_standard(int num){ standard = num;}

//get value interface
    int get_score(){ return score;}
    string get_name() { return name ; }

};
void Wordlist::add_card(Card & c){
    cards.push_back(c);
    ++size;
}

void Wordlist::show_cards(){
    for (auto card : cards){
        card.show_all();
    }
}
void Wordlist::study_card(){
    Card selected;
    cout << "which word do you want to study ?"<< endl;
    string word;
    cin >> word;
    for (auto i : cards){
        if (i.get_english() == word){
            cout << i.get_english() << " selected!" << endl;
            selected = i;
            break;
        }
    }
    if(selected.get_english() == ""){
        cout << "word not found." << endl;
    }
    else{
    cout <<"which mode ?" << endl;
    cout <<"1. choice_english_to_chinese" << endl;
    cout <<"2. choice_chinese_to_english" << endl;
    cout <<"3. spelling_chinese_to_english" << endl;
    cout <<"4. spelling_english_to_chinese" << endl;
    int c ;
    cin >> c ;
    bool right ;
    switch(c){
        case 1:{
            right = selected.recite_choice_e2c();
            break;
        }
        case 2:{
            right = selected.recite_choice_c2e();
            break;
        }
        case 3:{
            right = selected.recite_spell_c2e();
            break;
        }
        case 4:{
            right = selected.recite_spell_e2c();
            break;
        }
        default:{
            cout << "input error" << endl;
            exit(-1);
        }
    }
    if (!right){
        hidden.push_back(selected);
        if (decreaseable())
        score -= 10;
        else
        {
            score = 0;
            cout << "your score is 0 now *_*" <<endl;
        }
        
    }
    else
    { 
        if (increaseable())
        score += 10;
        else
        cout << "your score cannot be higher!" << endl;
    }

    

    }
}

