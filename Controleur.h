#ifndef TESTPROECT_CONTROLEUR_H
#define TESTPROECT_CONTROLEUR_H
#include "Jeueur.h"
#include "BankCarte.h"
#include<stdexcept>
#include<string>
#include"AI.h"

using namespace std;
class ControleurException :public exception{
    string info;
public:
    ControleurException(const string& i)noexcept :info(i){}
    virtual ~ControleurException()noexcept{}
    const char* what()const noexcept{return info.c_str();}

};

class Controleur {
private:
     int JeueurNum;
    std::vector<AI*> J;
    BankCarte bank;
    int modle;

public:
    Controleur();
    ~Controleur();
    Jeueur& getJeueur(std::string name);
    void is_Expansion();
    int choseFirst();
    void rearrange();
    void afficherAll();
    void afficher_allCartes();
    bool win(Jeueur j);
    void process();

};


#endif //TESTPROECT_CONTROLEUR_H
