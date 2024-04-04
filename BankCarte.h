#ifndef TESTPROECT_BANKCARTE_H
#define TESTPROECT_BANKCARTE_H
#include "Carte.h"
#include "Jeu.h"
#include<iomanip>

class BankCarte {
private:
    std::vector<Carte*> cartes;
    int count;//用于记录被拿空的牌的种数
public:
    class iterator:public std::vector<Carte*>::iterator{
    public:
        Carte& operator*() const{
            return *std::vector<Carte*>::iterator::operator*();
        }
    private:
        friend class BankCarte;
        iterator(const std::vector<Carte*>::iterator &it):
                std::vector<Carte*>::iterator(it){}
    };
    iterator begin(){
        return  iterator(cartes.begin());
    }
    iterator end(){
        return  iterator(cartes.end());
    }
    explicit BankCarte(int i);
    ~BankCarte();
    void afficher();
    void redCarte(const std::string name);
    int getNum(std::string name);

    const std::vector<Carte *> &getCartes() const;

    Carte* getCarte(std::string name);
    int getPrice(std::string name);
};

#endif //TESTPROECT_BANKCARTE_H
