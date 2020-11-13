# pragma once
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "json.hpp"
#include "color.hpp"
using Json = nlohmann::json;

using namespace std;
class Card{
    string type = "card";
    string english;
    string chinese;
    string property;
    vector<string> info = {"void"};
    vector<string> choice_en  = {"wrong" , "wrong" ,"wrong"};
    vector<string> choice_ch  = {"wrong" , "wrong" , "wrong"};

// private methods
    void show_en(){ cout << english << endl;}
    void show_ch(){ cout << chinese << endl;}
    string user_input();
    void judge(bool flag);
    char show_choice_ch(vector<string>  vs); // return the right choice
    char show_choice_en(vector<string>  vs); // return the right choice



public:
    //Completely constructor
    Card(const string & en = "" ,const string &  ch="" , const string &  pr ="", const vector<string> &  in =vector<string>()):
    english(en) , chinese(ch) , property(pr),info(in) {}
    //use default wrong choice_vector
    Card(vector<string> we , vector<string> wc ,const string & en = "" ,const string &  ch="" , const string &  pr ="", const vector<string> &  in =vector<string>() ):
    Card(en , ch , pr , in){ choice_en = we; choice_ch = wc; }

    bool recite_spell_c2e();
    bool recite_spell_e2c();
    bool recite_choice_c2e();
    bool recite_choice_e2c();
    void show_all(int index);

//get value interface
    string get_english() { return english;}


//work with json
    Card(const Json & jcard ):english(jcard["english"]),chinese(jcard["chinese"]),property(jcard["property"]),info(jcard["info"].get<vector<string>>()){
    choice_en =  jcard["choice_en"].get<vector<string>>();
    choice_ch =  jcard["choice_ch"].get<vector<string>>();
    // choice_en.push_back(english);
    // choice_ch.push_back(chinese); 

    }


//convertors
friend void from_json(const Json & j , Card & c);
friend void to_json(Json & j , const Card & c );
friend void change(Card & c);


};


//private methods
string Card::user_input(){
    string res;
    cin >> res;
    return res;
}
void Card::judge(bool flag){
    if (flag){ cout << GRN << "correct"<<DEF << endl; }
    else { cout << RED << "wrong" << DEF << endl; }
}


char Card::show_choice_ch(vector<string>  vs){
    vs.push_back(chinese);
    int res;
    char index [4] = {'A','B','C','D'};
    shuffle(vs.begin() , vs.end()  ,mt19937(random_device()()));
    for(int i = 0 ; i < vs.size() ; i++){
        if(vs[i] == chinese){
            res = i;
            break;
        }
    }
    for(int i = 0 ; i<4 ; i++){
        cout << index[i]  << " : "  << vs[i] << endl;
    }
    return index[res];
}

char Card::show_choice_en(vector<string>  vs){
    vs.push_back(english);
    int res;
    char index [4] = {'A','B','C','D'};
    shuffle(vs.begin() , vs.end()  ,mt19937(random_device()()));
    for(int i = 0 ; i < vs.size() ; i++){
        if(vs[i] == english){
            res = i;
            break;
        }
    }
    for(int i = 0 ; i<4 ; i++){
        cout << index[i]  << " : "  << vs[i] << endl;
    }
    return index[res];
}

//public methods

bool Card::recite_spell_c2e(){
    show_ch();
    string input = user_input();
    bool flag = (input == english);
    judge(flag);
    return flag;
}
bool Card::recite_spell_e2c(){
    show_en();
    string input = user_input();
    bool flag = (input == chinese);
    judge(flag);
    return flag;
}
bool Card::recite_choice_c2e(){
    show_ch();
    char r = show_choice_en(choice_en);
    char c = user_input()[0];
    bool flag = (r == c);
    judge(flag);
    return flag;
    

}
bool Card::recite_choice_e2c(){
    show_en();
    char r = show_choice_ch(choice_ch);
    char c = user_input()[0];
    bool flag = (r == c );
    judge(flag);
    return flag;

}

void Card::show_all(int index){
    cout << "+------------------------------" << endl;
    cout << "|index   : " << index << endl;
    cout << "|English : " << english << endl;
    cout << "|Chinese : " << chinese  << endl;
    cout << "|Property: " << property << endl;
    for (auto i : info)
    cout << "|Info    : " << i << endl;
    cout << "+------------------------------" << endl;
}
