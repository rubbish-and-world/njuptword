#include <iostream>
#include "Card.hpp"
#include <algorithm>
#include <vector>
using namespace std;
int main(){
    vector<string> w1 = {"shit" , "fuck" , "die"};
    vector<string> w2 = {"💩" , "草" , "死"};
    Card cardtest(w1, w2 , "milk","牛奶","n","white");
    cardtest.recite_choice_c2e();
    cardtest.recite_choice_e2c();
    return 0;


}