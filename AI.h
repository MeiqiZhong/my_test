//
// Created by zhongmeiqi on 2022/11/21.
//

#ifndef TESTPROECT_AI_H
#define TESTPROECT_AI_H

#endif //TESTPROECT_AI_H

#include"Jeueur.h"
class AI:public Jeueur{
private:

public:
    AI(const string& name="AI",int bir=20000809);
    ~AI()=default;
    bool dice();
    char y_or_n();
    int tossNum();
    int get_n(int i,int JeueurNum);
    string get_change_carte(AI& J);
    string self_change_carte();
    string bandstand_get_money_from(int ,vector<AI*>J);
    char buy_carte_y_or_n();
    string achete_carte(BankCarte& bank);
};