//optimize : search with Trie

#include <iostream>
#include <algorithm>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
#include <stack>
#include <sstream>
#include "json.hpp"
#include "Card.hpp"
#include "Wordlist.hpp"
#include "Deck.hpp"
#include "User.hpp"
#include "converter.hpp"
#include "color.hpp"

#include "base64.hpp"
using base64::encode;
using base64::decode;

using Json = nlohmann::json;
using namespace std;

Json database;
vector<User> users;
User selected_user;
Deck selected_deck;
Wordlist selected_wordlist;
Card selected_card;
bool logined = false;
bool deck_selected = false;
bool wordlist_selected = false;
bool card_selected = false;
int uid ;
stack<int> s ; //stack used to store the latest index



void load_db(){
    try{
    ifstream in("users.dk");
    string temp ;
    stringstream ss;
    in >> temp ;
    auto plain = decode(temp);
    temp = string(plain.begin() , plain.end());
    ss << temp;
    ss >> database;
    in.close();
    }
    catch(const exception &e ){
        cout << RED << "database not found" << DEF << endl;
        exit(0);
    }
}


void import_deck(User & user){
    string path ;
    cout << "Enter import path :" ;
    cin >> path;
    try{
    if(path.substr(path.size()-4) == "json"){
        std::ifstream in(path);
        Json j;
        in >> j;
        Deck newdk = j;
        user.add_deck(newdk);
        cout << GRN << "deck added successfully!" << DEF  << endl;
    }
    else{
        cout << RED << "import file must be json file !"  << DEF << endl;
    }
    }
    catch (const out_of_range & e){
        cout << RED << "name your file xxx.json, please"  << DEF << endl;
        
    }
    catch (const nlohmann::detail::parse_error & n){
        cout << RED << "file not found."  << DEF << endl;

    }
}

void show_users(){
    for (int i = 0 ; i < users.size() ; ++i){
        cout << i << " : " << users[i].get_name() << endl;
    }
}
bool valid(string input){
    for (auto i : input){
        if (!isalpha(i) && !isdigit(i)) return false;
    }
    return true;
}

string ask_for_input(){
    cout << "WordSystem>";
    string res ;
    while(cin >> res){
    if (valid(res)){
    break;
    }
    else{
        cout << RED << "invalid input, input should not contain non-alphabetic characters" << DEF << endl;
        cout << "WordSystem>";
    }
    }
    return res;
}

int get_mode_num(){
    cout <<"which mode ?" << endl;
    cout <<"1. choice_english_to_chinese" << endl;
    cout <<"2. choice_chinese_to_english" << endl;
    cout <<"3. spelling_chinese_to_english" << endl;
    cout <<"4. spelling_english_to_chinese" << endl;
    try{
       return stoi(ask_for_input());
    }
    catch (const invalid_argument & e){
        cout << RED << "mode not found" << DEF << endl;
        return -100;
    }
}


void help(){
    cout << "The following cmds are available :" << endl;
    cout << "help       - show this help info" << endl;
    cout << "quit       - exit the system" << endl;
    cout << "clear      - clear the screen" << endl;
    cout << "login      - login in an existed account via password" << endl;
    cout << "register   - create a new account" << endl;
    cout << "*----------------*      after login      *----------------*"<< endl;
    cout << "mark       - daily attendence" << endl;
    cout << "marks      - show all your marks" << endl;
    cout << "import     - import deck via a json file" << endl;
    cout << "score      - show current scores and whether them meet the standard" << endl;
    cout << "decks      - show your decks" << endl;
    cout << "wordlists  - show all your wordlists in current deck" << endl;
    cout << "cards      - show all your cards in current wordlist" << endl;
    cout << "select     - select an item" << endl;
    cout << "create     - create a void deck or wordlist or card" << endl;
    cout << "*----------------*  after select an item  *----------------*" << endl;
    cout << "edit       - edit the card you selected" << endl;
    cout << "delete     - delete the selected item" << endl;
    cout << "study      - study the selected card/wordlist" << endl;
    cout << "review     - review all your wrong words in the selected wordlist" << endl;
    cout << "back       - abort the select item and back to the main mode" << endl;
}



void clear(){
    cout << "\033[2J\033[1;1H";
}

void login(){
    cout << "Here we already have :" << endl;
    for(int i = 0 ; i < users.size() ; ++i){
        cout << i << " : " << users.at(i).get_name() << endl;
    }
    cout << "Enter your username/account :" << endl;

    string name = ask_for_input();
    bool exist = false;
    for (int i = 0 ;i<users.size() ; i++){
        if (users[i].get_name() == name){
            uid = i;
            selected_user = users.at(i);
            exist = true;
            break;
        }
    }
    if (!exist){ cout << RED << "user not found, you may want to register a new one." << DEF << endl;}
    else{
        cout << "Enter your password :" << endl;
        string password = ask_for_input();
        if (password == selected_user.get_password()){
            logined = true;
            cout << GRN << "login successfully" << DEF << endl;
        }
        else{
            cout << RED << "wrong password, are you sure this is your account? Try to login again" << DEF << endl;
        }
    }
}

void regist(){
    cout << "now creating a new accout" << endl;
    cout << "Enter the name of your new account :" << endl;
    string name = ask_for_input();
    cout << "Enter the password of your new account :" << endl;
    string password = ask_for_input();
    users.push_back(User(name , password));
    cout << GRN << "account created ! Now you can login." << DEF << endl;
}

void choose_deck(){
    cout << "Enter the index of deck you want to select :" << endl;
    string ind = ask_for_input();
    try{
    // latest_index = stoi(ind);
    s.push(stoi(ind));
    selected_deck = selected_user.select_deck(stoi(ind));
    deck_selected = true;
    cout <<GRN <<  selected_deck.get_name() << " selected." <<DEF << endl;
    }
    catch ( const out_of_range & e){
        cout << RED << "deck not found" << DEF << endl;
    }
    catch (const invalid_argument & in){
        cout << RED << "index should be a number" << DEF << endl;
    }
}
void choose_wordlist(){
    cout << "Enter the index of wordlist you want to select :" << endl;
    string ind = ask_for_input();
    try{
    s.push(stoi(ind));
    selected_wordlist = selected_deck.select_wordlist(stoi(ind));
    wordlist_selected = true;
    cout <<GRN <<  selected_wordlist.get_name() << " selected." <<DEF << endl;
    }
    catch ( const out_of_range & e){
        cout << RED << "wordlist not found" << DEF << endl;
    }
    catch (const invalid_argument & in){
        cout << RED << "index should be a number" << DEF << endl;
    }
}
void choose_card(){
    cout << "Enter the index of card you want to select :"<< endl;
    string ind = ask_for_input();
    try{
        s.push(stoi(ind));
        selected_card = selected_wordlist.select_card(stoi(ind));
        card_selected = true;
        cout << GRN << selected_card.get_english() << " selected." <<DEF<<endl;
    }
    catch (const out_of_range & e){
        cout << RED << "card not found" << DEF << endl;
    }
    catch (const invalid_argument & in){
        cout << RED << "index should be a number" << DEF << endl;
    }
}

void select(){
    if(!deck_selected){
        choose_deck();
    }
    else if(!wordlist_selected){
        choose_wordlist();
    }
    else if(!card_selected){
        choose_card();
    }
}

void back(){
    try{
        if(card_selected){
        
                selected_wordlist.select_card(s.top()) = selected_card;
                s.pop();
                card_selected = false;
                selected_card = Card();
                
            }
            else if(wordlist_selected){
                selected_deck.select_wordlist(s.top()) = selected_wordlist;
                s.pop();
                wordlist_selected = false;
                selected_wordlist = Wordlist();
            }
            else if (deck_selected){
                selected_user.select_deck(s.top()) = selected_deck;
                s.pop();
                deck_selected = false;
                selected_deck = Deck();
            }
    }
    catch (const out_of_range& e){
        cout << RED << "no thing selected now" << DEF << endl;
    }
}
void save(){
    while(!s.empty()){
        back();
    }
    users[uid] = selected_user;
    Json db = users;
    ofstream out("users.dk");
    string temp ;
    stringstream ss;
    ss << db;
    temp = ss.str();
    out <<setw(4) <<  encode(vector<base64::byte>(temp.begin() , temp.end()));
    cout << GRN << "database saved." << DEF  << endl;
    out.close();
    
}
void quit(){
    save();
    cout << "Thank you for using, have a nice day ! 😃" << endl;
    exit(0);
}

int main(){
    cout << BLU << "Loading database ....." << DEF << endl;
    load_db();
    users = database.get<vector<User>>();
    cout << "*----------------* Welcome to Word System *----------------*" << endl;
    help();
    while (true){
    string cmd = ask_for_input();
    bool after_login_cmd = (cmd == "mark" || cmd == "import" || cmd == "score" || cmd == "decks" || cmd == "wordlists" || cmd == "cards" || cmd == "select" || cmd == "marks" || cmd == "create");
    bool after_select_cmd = (cmd == "delete" || cmd == "review" || cmd == "study" || cmd == "back" || cmd == "edit");
    if (cmd == "help"){
        help();
    }
    else if (cmd == "login"){
        login();
    }
    else if(cmd == "quit"){
        quit();
    }
    else if(cmd == "clear"){
        clear();
    }
    else if(cmd == "register"){
        regist();
    }
    else if(after_login_cmd ){

        if(logined){
        if(cmd == "import"){
            import_deck(selected_user);
        }
        else if (cmd == "mark"){
            selected_user.mark();
        }
        else if (cmd == "marks"){
            selected_user.show_marks();
        }
        else if (cmd == "decks"){
            selected_user.show_decks();
        }
        else if(cmd == "create"){
            string name ;
            if(card_selected){
                cout << RED << "please back to wordlist first" << DEF << endl;
            }
            else if(wordlist_selected){
                selected_wordlist.add_card(Card());
            }
            else if(deck_selected){
                cout << "the name of your new wordlist :";
                cin >> name ;
                selected_deck.add_list(Wordlist(name));
            }
            else{
                cout << "the name of your new deck :" ;
                cin >> name ;
                selected_user.add_deck(Deck(name));
            }
            cout << GRN << "item created successfully" << DEF << endl;

        }
        else if (cmd == "wordlists"){
            if(deck_selected){
                selected_deck.show_wordlists();
            }
            else{
                cout << RED << "please select a deck first" << DEF << endl;
            }
        }
        else if (cmd == "score"){
            if(deck_selected){
                selected_deck.show_score();
            }
            else{
                cout << RED << "please select a deck first" << DEF << endl;
            }
        }
        else if(cmd == "cards"){
            if(wordlist_selected && !card_selected){                    
                selected_wordlist.show_cards();
            }
            else if(card_selected){
                cout << RED << "please back to wordlist first" << DEF << endl;
            }
            else{
                cout << RED << "please select a wordlist first" << DEF << endl;
            }
        }
        else if (cmd == "select"){
            select();
        }
        }
        else{
        cout << RED << "please login first" << DEF << endl;
        }
    }
    else if (after_select_cmd){
        if(!(deck_selected || wordlist_selected || card_selected)){
            cout << RED << "please select an item first" << DEF << endl;
        }
        else if (cmd == "back"){
            back();
        }
        else if (cmd == "review"){
            if(!wordlist_selected){
                cout << RED << "please select a wordlist first" << DEF << endl;
            }
            else if (card_selected){
                cout << RED << "please back from card" << DEF << endl;
            }
            else{
                selected_wordlist.review(get_mode_num());
                selected_deck.select_wordlist(s.top()) = selected_wordlist;
            }
        }
        else if (cmd == "study"){
            if(!wordlist_selected){
                cout << RED << "please select a wordlist first" << DEF << endl;
            }
            else if(card_selected){
                cout << RED << "please back from card" << DEF << endl;
            }
            else{
                selected_wordlist.study(get_mode_num());
                selected_deck.select_wordlist(s.top()) = selected_wordlist;
            }

    }
        else if (cmd == "delete"){
            if(card_selected && wordlist_selected){
                selected_wordlist.remove(s.top());
                s.pop();
                cout << GRN << "selected card deleted." << DEF << endl;
                selected_card = Card();
                card_selected = false;
            }
            else if(!card_selected && wordlist_selected && deck_selected){
                selected_deck.remove(s.top());
                s.pop();
                cout << GRN << "selected wordlist deleted." << DEF << endl;
                selected_wordlist = Wordlist();
                wordlist_selected = false;
            }
            else if(!card_selected && !wordlist_selected && deck_selected && logined){
                selected_user.remove(s.top());
                s.pop();
                cout << GRN << "selected deck deleted." << DEF << endl;
                selected_deck = Deck();
                deck_selected = false;

            }
        }
        else if(cmd == "edit"){
            if(!card_selected){
                cout << RED << "no card selected!" << DEF << endl;
            }
            else{
                selected_card.edit(s.top());
            }
        }

    }

    else{
        cout << RED << "unknow command" << DEF << endl;
    }
    }

    return 0;
}
