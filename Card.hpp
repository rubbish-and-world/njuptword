# pragma once
#include <string>
#include <iostream>
#include <vector>
using namespace std;
class Card{
    string english;
    string chinese;
    string property;
    string info;
    vector<string> choice_en  = {"wrong" , "wrong" ,"wrong"};
    vector<string> choice_ch  = {"wrong" , "wrong" , "wrong"};

// private methods
    void show_en(){ cout << english << endl;}
    void show_ch(){ cout << chinese << endl;}
    string user_input();
    void judge(bool flag);
    char show_choice(vector<string> & vs); // return the right choice




public:
    //Completely constructor
    Card(const string & en = "" ,const string &  ch="" , const string &  pr ="", const string &  in =""):
    english(en) , chinese(ch) , property(pr),info(in) {choice_en.push_back(english);choice_ch.push_back(chinese);}
    //use default wrong choice_vector
    Card(vector<string> we , vector<string> wc ,const string & en = "" ,const string &  ch="" , const string &  pr ="", const string &  in ="" ):
    Card(en , ch , pr , in){
    choice_en = we;
    choice_ch = wc;
    choice_en.push_back(english);choice_ch.push_back(chinese); }

    bool recite_spell_c2e();
    bool recite_spell_e2c();
    bool recite_choice_c2e();
    bool recite_choice_e2c();
    void show_all();

//interface
    string get_english() { return english;}
};
//private methods
string Card::user_input(){
    string res;
    cin >> res;
    return res;
}
void Card::judge(bool flag){
    if (flag){ cout << "correct" << endl; }
    else { cout << "wrong" << endl; }
}


char Card::show_choice(vector<string> & vs){
    int res;
    char index [4] = {'A','B','C','D'};
    random_shuffle(vs.begin() , vs.end());
    for(int i = 0 ; i < vs.size() ; i++){
        if(vs[i] == english || vs[i] == chinese){
            res = i;
            break;
        }
    }
    for(int i = 0 ; i<vs.size() ; i++){
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
    char r = show_choice(choice_ch);
    char c = user_input()[0];
    bool flag = (r == c);
    judge(flag);
    return flag;
    

}
bool Card::recite_choice_e2c(){
    show_en();
    char r = show_choice(choice_en);
    char c = user_input()[0];
    bool flag = (r == c );
    judge(flag);
    return flag;

}

void Card::show_all(){
    cout << "+------------------------------" << endl;
    cout << "|English : " << english << endl;
    cout << "|Chinese : " << chinese  << endl;
    cout << "|Property: " << property << endl;
    cout << "|Info    : " << info << endl;
    cout << "+------------------------------" << endl;
}