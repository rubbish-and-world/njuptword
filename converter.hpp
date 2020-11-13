#include "json.hpp"
using Json = nlohmann::json;
#include "Card.hpp"
#include "Wordlist.hpp"
#include "Deck.hpp"
#include "User.hpp"
using namespace std;
void from_json(const Json & j , Card & c){
    j.at("english").get_to(c.english);
    j.at("chinese").get_to(c.chinese);
    j.at("property").get_to(c.property);
    j.at("info").get_to(c.info);
    j.at("choice_en").get_to(c.choice_en);
    j.at("choice_ch").get_to(c.choice_ch);
}

void to_json(Json & j , const Card & c ){
    j = Json{{"english",c.english},
            {"chinese",c.chinese},
            {"property",c.property},
            {"info",c.info},
            {"choice_en",c.choice_en},
            {"choice_ch",c.choice_ch},
            {"type",c.type}};
}

void from_json(const Json & j , Wordlist & w){
    j.at("name").get_to(w.name);
    j.at("score").get_to(w.score);
    j.at("standard").get_to(w.standard);
    j.at("cards").get_to(w.cards);
    j.at("hidden").get_to(w.hidden);
}

void to_json(Json & j , const Wordlist & w){
    j = Json{
        {"name", w.name},
        {"score",w.score},
        {"standard",w.standard},
        {"cards",w.cards},
        {"hidden",w.hidden},
        {"type",w.type}  
    };
}

void from_json(const Json & j , Deck & d ){
    j.at("name").get_to(d.name);
    j.at("total_score").get_to(d.total_score);
    j.at("standard_score").get_to(d.standard_score);
    j.at("wordlists").get_to(d.wordlists);
}

void to_json(Json & j , const Deck & d){
    j = Json{
        {"name" , d.name},
        {"total_score",d.total_score},
        {"standard_score",d.standard_score},
        {"wordlists",d.wordlists},
        {"type",d.type}
    };
}

void from_json(const Json & j , User & u){
    j.at("name").get_to(u.name);
    j.at("password").get_to(u.password);
    j.at("decks").get_to(u.decks);
    j.at("marks").get_to(u.marks);
}

void to_json(Json & j , const User & u){
    j = Json{
        {"name",u.name},
        {"password",u.password},
        {"decks",u.decks},
        {"type",u.type},
        {"marks",u.marks}
    };
}