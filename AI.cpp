//
// Created by zhongmeiqi on 2022/11/21.
//

#include "AI.h"
AI::AI(const string &name, int bir) :Jeueur(name,bir){}

char AI::y_or_n() {
    int n=rand()%1;
    if(n=0) return 'y';
    else return 'n';
}

int AI::tossNum(){
    int n=1+rand()%1;
    return n;
}

int AI::get_n(int i,int JeueurNum){
    int n=rand()%JeueurNum-1;
    while(n==i)
        n=rand()%JeueurNum-1;
    return n;
}

string AI::get_change_carte(AI& J){
    int m=0;
    m=rand()%(J.getCartes().size()-1);
    string j;
    j=J.getCartes()[m]->getName();
    while(j=="gym"||j=="businessCenter"||j=="bandstand"||j=="press"||j=="taxoffice")
    {m=rand()%(J.getCartes().size()-1);j=J.getCartes()[m]->getName(); }
    return j;
}

string AI::self_change_carte(){
    int a;
    string sCname;
    a=rand()%cartes.size()-1;
    sCname=cartes[a]->getName();
    while(sCname=="gym"||sCname=="businessCenter"||sCname=="bandstand"||sCname=="press"||sCname=="taxoffice")
    {a=rand()%cartes.size()-1;
        sCname=cartes[a]->getName();}
    return sCname;
}

string AI:: bandstand_get_money_from(int i,vector<AI*>J){
    int max=0;
    string Jname;
    for(int j=i+1;j!=i;j++)
    {
        if(J[j]->getMoney()>=max) {max=J[j]->getMoney();Jname=J[j]->getName();}
        if(i!=0){
            if(j==J.size()-1) j=0;}
        else{if(j==J.size()-1) j=-1;}
    }
    return Jname;
}

char AI::buy_carte_y_or_n() {
    char s;
    if(money>0) {
        s='y';
        cout << "y" << endl;}
    else {s='n';cout<<"n"<<endl;}
    return s;
}

string AI::achete_carte(BankCarte& bank){
    std::string s;
    int m=0;
    if (!(isTurnRailway()) &&money >= 4) {s = "railwayStation";m = 1;}
    if (!isTurnHarbor() && money >= 2) {s = "harbor";m = 1;}
    if (!isTurnCenter() && money >= 10) {s = "shoppingCenter";m = 1;}
    if (!isTurnPark() && money >= 16) {s = "amusementPark";m = 1;}
    if (!isTurnRadio() && money >= 22) {s = "radioStation";m = 1;}
    if (!isTurnAirport() && money >= 30) {s = "airport";m = 1;}

    while(m==0) {
        int n;
        n = rand() % (bank.getCartes().size());
        while (money < bank.getCartes()[n]->getPrice()) {
            n = rand() % (bank.getCartes().size());
        }
        s = bank.getCartes()[n]->getName();
        if(s== "businessCenter"|| s == "gym" || s == "bandstand" || s == "press" || s == "taxoffice")
        {if(flagOnce)m=0;else m+=1;}
        else m+=1;
    }
    cout<<s<<endl;
    return s;
}


bool AI::dice(){
    bool flagEqual= 0;
    if(!turnRailway){//没有翻转火车站
        int _count = (rand() % 6) + 1;
        std::cout<<"the count is: "<<_count<<"\n";
        if(!turnRadio) {//没有翻转广播台
            count = _count;
            return flagEqual;
        }else{//翻转了广播台
            std::cout<<"Do you want to toss again(y/n)?\n";
            char s=y_or_n();
            int l=1;
            while(l){
                try {
                    l = 0;
                    cout<<s<<endl;
                    if (std::cin.fail())
                        throw JeueurException("erreur:Enter a wrong answer");
                    else if (s != 'y' && s != 'n')
                        throw JeueurException("erreur:Enter a wrong answer");
                    else if (s == 'y') {//要求重掷
                        int _countAgain = (rand() % 6) + 1;
                        std::cout << "the count is: " << _countAgain << "\n";
                        count = _countAgain;
                        return flagEqual;
                    } else {
                        count = _count;
                        return flagEqual;
                    }
                }catch(exception& e){
                    std::cout<<e.what()<<std::endl;
                    std::cout<<"Do you want to toss again(y/n)?"<<std::endl;
                    l=1;
                    std::cin.clear();
                    std::cin.sync();}
            }
        }
    }else {//翻转了火车站
        int n=tossNum();
        std::cout << "Choose one dice or tow dices(1/2):" << std::endl;
        while (1) {
            try {
                cout<<n<<endl;
                if (std::cin.fail())
                    throw JeueurException("erreur:Enter a wrong answer");
                else if (n != 1 && n != 2)
                    throw JeueurException("erreur:Enter a wrong answer");
                else
                    break;
            } catch (exception &e) {
                std::cout << e.what() << std::endl;
                std::cout << "Choose one dice or tow dices(1/2) again:" << std::endl;
                std::cin.clear();
                std::cin.sync();
            }
        }
        if (n == 1) {//选择1个骰子
            int _count = (rand() % 6) + 1;
            std::cout << "the count is: " << _count << "\n";
            if (!turnRadio) {//没有翻转广播台
                count = _count;
                return flagEqual;
            } else {//翻转了广播台
                std::cout << "Do you want to toss again(y/n)?\n";
                char s=y_or_n();
                while(1) {
                    try {
                        cout<<s<<endl;
                        if (s != 'y' && s != 'n')
                            throw JeueurException("erreur:Enter a wrong answer");
                        else if (std::cin.fail())
                            throw JeueurException("erreur:Enter a wrong answer");
                        else
                            break;
                    }catch(exception& e){
                        std::cout<<e.what()<<std::endl;
                        std::cout << "Do you want to toss again(y/n)?\n";
                        std::cin.clear();
                        std::cin.sync();
                    }
                }
                if (s == 'y') {//要求重掷
                    std::cout << "Choose one dice or tow dices(1/2):" << std::endl;
                    int m=tossNum();
                    while(1){
                        try{
                            cout<<m<<endl;
                            if (std::cin.fail())
                                throw JeueurException("erreur:Enter a wrong answer");
                            else if (m != 1 && m != 2)
                                throw JeueurException("erreur:Enter a wrong answer");
                            else
                                break;
                        }catch (exception &e) {
                            std::cout << e.what() << std::endl;
                            std::cout << "Choose one dice or tow dices(1/2) again:" << std::endl;
                            std::cin.clear();
                            std::cin.sync();
                        }
                    }
                    if (m == 1) {//选择1个骰子
                        int _countAgain = (rand() % 6) + 1;
                        std::cout << "the count is: " << _countAgain << "\n";
                        count = _countAgain;
                        return flagEqual;
                    } else {//选择2个骰子
                        int _countAgain1 = (rand() % 6) + 1;
                        int _countAgain2 = (rand() % 6) + 1;
                        if (_countAgain1 == _countAgain2)
                            flagEqual = 1;
                        std::cout << "the count is: " << _countAgain1 << " and " << _countAgain2 << "\n";
                        count = _countAgain1 + _countAgain2;
                        return flagEqual;
                    }
                }else{
                    count = _count;
                    return flagEqual;
                }
            }
        } else {//选择2个骰子
            int _count1 = (rand() % 6) + 1;
            int _count2 = (rand() % 6) + 1;
            std::cout << "the count is: " << _count1 << " and " << _count2 << "\n";
            if (!turnRadio) {//没有翻转广播台
                if (_count1 == _count2)
                    flagEqual = 1;
                count = _count1 + _count2;
                return flagEqual;
            } else {//翻转了广播台
                std::cout << "Do you want to toss again(y/n)?\n";
                char s=y_or_n();
                while(1){
                    try{
                        cout<<s<<endl;
                        if (s != 'y' && s != 'n')
                            throw JeueurException("erreur:Enter a wrong answer");
                        else if (std::cin.fail())
                            throw JeueurException("erreur:Enter a wrong answer");
                        else
                            break;
                    }catch(exception& e){
                        std::cout<<e.what()<<std::endl;
                        std::cout << "Do you want to toss again(y/n)?\n";
                        std::cin.clear();
                        std::cin.sync();
                    }
                }
                if (s == 'y') {//要求重掷
                    std::cout << "Choose one dice or tow dices(1/2):" << std::endl;
                    int m=tossNum();
                    while(1){
                        try{
                            cout<<m<<endl;
                            if (std::cin.fail())
                                throw JeueurException("erreur:Enter a wrong answer");
                            else if (m != 1 && m != 2)
                                throw JeueurException("erreur:Enter a wrong answer");
                            else
                                break;

                        }catch (exception &e) {
                            std::cout << e.what() << std::endl;
                            std::cout << "Choose one dice or tow dices(1/2) again:" << std::endl;
                            std::cin.clear();
                            std::cin.sync();
                        }
                    }
                    if (m == 1) {//选择1个骰子
                        int _countAgain = (rand() % 6) + 1;
                        std::cout << "the count is: " << _countAgain << "\n";
                        count = _countAgain;
                        return flagEqual;
                    } else {//选择2个骰子
                        int _count3 = (rand() % 6) + 1;
                        int _count4 = (rand() % 6) + 1;
                        if (_count3 == _count4)
                            flagEqual = 1;
                        std::cout << "the count is: " << _count3 << " and " << _count4 << "\n";
                        count = _count3 + _count4;
                        return flagEqual;
                    }
                }else{
                    count = _count1 + _count2;
                    return flagEqual;
                }
            }
        }
    }
}