#include "BankCarte.h"

BankCarte::BankCarte(int i){//得到银行的25*6张卡牌
    if(i==0) {
        for (auto it = Jeu::getInstance().getCartes().begin(); it != Jeu::getInstance().getCartes().begin() + 150; it++)
            cartes.push_back(*it);
    }
    else{
        for (auto it = ExpansionJeu::getInstance().getCartes().begin(); it != ExpansionJeu::getInstance().getCartes().begin() + 150; it++)
            cartes.push_back(*it);
    }
    count = 0;
}

BankCarte::~BankCarte(){
    std::vector<Carte*> temp;
    cartes.swap(temp);
}

void BankCarte::afficher(){
    std::cout<<"          ----------------------------BankCarte------------------------------\n";
    for(iterator it = end()-15+count;it != end();++it){
        int i = it - (end()-15+count);
        if(i%5 == 0 && i != 0)
            std::cout<<"\n";
        std::string str;
        str = (*it).getName();
        str.append("*");
        str = str + std::to_string(getNum((*it).getName()));
        std::cout<<std::left<<std::setw(20)<<str;
    }
    std::cout<<"\n";
}

void BankCarte::redCarte(const std::string name){//银行减牌
    for(auto it = begin();it != end();++it)//遍历
        if((*it).getName() == name){//还有这张牌
            cartes.erase(it);;//牌减1
            break;
            int i = 0;
        }
    if(!getNum(name))//减完牌之后没有这种牌了
        count++;
}

int BankCarte::getNum(std::string name){
    int num = 0;
    for(auto it = begin();it != end();++it){
        if((*it).getName() == name)
            num++;
    }
    return num;
}

Carte* BankCarte::getCarte(std::string name){
    for(auto it = begin();it != end();++it)
        if((*it).getName() == name)
            return &(*it);
}

int BankCarte::getPrice(std::string name) {
    for(auto it = begin();it != end();++it)
        if((*it).getName() == name)
            return (*it).getPrice();
}

const std::vector<Carte *> &BankCarte::getCartes() const {
    return cartes;
}
