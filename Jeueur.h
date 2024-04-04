#ifndef TESTPROECT_JEUEUR_H
#define TESTPROECT_JEUEUR_H
#include "Carte.h"
#include "Jeu.h"
#include "BankCarte.h"
#include <algorithm>
#include <vector>
#include<iostream>
#include<stdexcept>
#include<string>

using namespace std;
class JeueurException : public exception{
    string info;
public:
    JeueurException(const string& i)noexcept :info(i){}
    virtual ~JeueurException()noexcept{}
    const char* what()const noexcept{return info.c_str();}

};

class Jeueur {
protected:
    std::string name;
    int birthday;
    int money = 3;
    std::vector<Carte*> cartes;
    std::string once;//存储紫卡的名字
    int count = 0;//掷到的点数
    bool flagOther = 0;//有没有红卡
    bool flagOnce = 0;//有没有紫卡
    bool turnHarbor = 0;//有没有建成港口
    bool turnRailway = 0;//有没有建成火车站
    bool turnCenter = 0;//有没有建成购物中心
    bool turnPark = 0;//有没有建成游乐园
    bool turnRadio = 0;//有没有建成广播台
    bool turnAirport = 0;//有没有建成机场
public:
    class iterator:public std::vector<Carte*>::iterator{
    public:
        Carte& operator*() const{
            return *std::vector<Carte*>::iterator::operator*();
        }
    private:
        friend class Jeueur;
        iterator(const std::vector<Carte*>::iterator &it):
                std::vector<Carte*>::iterator(it){}
    };
    iterator begin(){
        return  iterator(cartes.begin());
    }
    iterator end(){
        return  iterator(cartes.end());
    }
    const std::vector<Carte *> &getCartes() const;

    Jeueur(const std::string &name, int birthday);
    ~Jeueur() = default;

    int getNum(std::string name);
    int getCount() const;
    int getBirthday() const;
    int getMoney() const;
    const std::string &getName() const;
    const std::string &getOnce() const;
    Carte& getCarte(std::string name);//得到玩家具有的手牌的一张

    bool isFlagOnce() const;
    bool isTurnRailway() const;
    bool isTurnCenter() const;
    bool isTurnPark() const;
    bool isTurnRadio() const;
    bool isTurnHarbor() const;
    bool isTurnAirport() const;

    void isJHaveCarte(Jeueur& j,Carte &jCname) ;
    void isHaveCarte(Carte &sCname) ;


    void setOnce(const std::string &once);

    void setMoney(int money);

    int addMoney(int i);
    int redMoney(int i);

    bool dice();
    void afficherCarte();

    //controleur如果骰子掷到1，3，7，8，9，10，判断其他玩家有没有红卡，需要调用Pay()   if(count == 1|| count == 3|| count == 7||count == 8||count == 9||count == 10)
    void pay(Jeueur& j);
    //controleur如果骰子掷到1,2,4，5,8，9,10，12，13判断所有玩家有没有蓝，需要调用all()   if(count == 1|| count == 2|| count == 5...)
    void allGet(Jeueur& j);
    //掷到非6，本玩家需要调用self方法
    void selfGet();
    //掷到6，7，8，9，选调一下五个方法的一个
    void getJeueur5(Jeueur& j);
    void getJeueur1(Jeueur& j);
    void getJeueur2(Jeueur& j);
    void getJeueurhalf(Jeueur& j);
    void changeCarte(Jeueur& j,Carte& jCname,Carte& sCname);
    void achete(std::string name,BankCarte& bank);

    };


#endif //TESTPROECT_JEUEUR_H
