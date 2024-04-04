#include "Jeueur.h"



Jeueur::Jeueur(const std::string &name, int birthday) : name(name), birthday(birthday) {
    cartes.push_back(&Jeu::getInstance().getCarte(156));
    cartes.push_back(&Jeu::getInstance().getCarte(157));
}

int Jeueur::getNum(std::string name) {
    int num = 0;
    for(auto it = begin();it != end();it++){
        if((*it).getName() == name)
            num++;
    }
    return num;
}

int Jeueur::getCount() const{
    return count;
}

int Jeueur::getMoney() const {
    return money;
}

int Jeueur::getBirthday() const {
    return birthday;
}

int Jeueur::addMoney(int i){
    money = money + i;
    return money;
}

int Jeueur::redMoney(int i) {
    money = money - i;
    return money;
}

const std::string &Jeueur::getOnce() const {
    return once;
}

const std::string &Jeueur::getName() const {
    return name;
}
void Jeueur::setMoney(int money) {
    Jeueur::money = money;
}

void Jeueur::afficherCarte(){
    std::cout<<"          ----------------------------"<<getName()<<"------------------------------\n";
    int n = 0;
    for(auto it = begin();it != end();it++){
        auto im = begin();
        for(;im != it;im++)
            if((*im).getName() == (*it).getName())
                break;
        if(im == it){
            std::string str;
            str = (*it).getName();
            str.append("*");
            str = str + std::to_string(getNum((*it).getName()));
            std::cout<<std::left<<std::setw(20)<<str;
            n++;
            if(n % 5 == 0 && n != 0)
                std::cout<<"\n";
        }
    }
    std::cout<<"\nmoney: "<<getMoney()<<"\n";
}

bool Jeueur::dice(){
    bool flagEqual= 0;
    if(!turnRailway){//没有翻转火车站
        int _count = (rand() % 6) + 1;
        std::cout<<"the count is: "<<_count<<"\n";
        if(!turnRadio) {//没有翻转广播台
            count = _count;
            return flagEqual;
        }else{//翻转了广播台
            std::cout<<"Do you want to toss again(y/n)?\n";
            char s;
            int l=1;
            while(l){
                try {
                    l = 0;
                    std::cin >> s;
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
        int n;
        std::cout << "Choose one dice or tow dices(1/2):" << std::endl;
        while (1) {
            try {
                std::cin >> n;
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
                char s;
                while (1) {
                    try {
                        std::cin >> s;
                        if (s != 'y' && s != 'n')
                            throw JeueurException("erreur:Enter a wrong answer");
                        else if (std::cin.fail())
                            throw JeueurException("erreur:Enter a wrong answer");
                        else
                            break;
                    } catch (exception &e) {
                        std::cout << e.what() << std::endl;
                        std::cout << "Do you want to toss again(y/n)?\n";
                        std::cin.clear();
                        std::cin.sync();
                    }
                }
                if (s == 'y') {//要求重掷
                    std::cout << "Choose one dice or tow dices(1/2):" << std::endl;
                    int m;
                    while (1) {
                        try {
                            std::cin >> m;
                            if (std::cin.fail())
                                throw JeueurException("erreur:Enter a wrong answer");
                            else if (m != 1 && m != 2)
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
                } else {
                    count = _count;
                    return flagEqual;
                }
            }
        } else {//选择2个骰子
            int _count1 = (rand() % 6) + 1;
            int _count2 = (rand() % 6) + 1;
            if (!turnHarbor) {//没有翻转港口
                count = _count1 + _count2;
                return flagEqual;
            } else {//翻转了港口
                if (_count1 + _count2 >= 10) {//点数大于10
                    char q;
                    while (1) {
                        try {
                            std::cin >> q;
                            if (q != 'y' && q != 'n')
                                throw JeueurException("erreur:Enter a wrong answer");
                            else if (std::cin.fail())
                                throw JeueurException("erreur:Enter a wrong answer");
                            else
                                break;
                        } catch (exception &e) {
                            std::cout << e.what() << std::endl;
                            std::cout << "Do you want to toss again(y/n)?\n";
                            std::cin.clear();
                            std::cin.sync();
                        }
                    }
                    if (q == 'y') {
                        int _countadd2 = _count1 + _count2 + 2;
                        count = _countadd2;
                        return flagEqual;
                    } else if (q == 's') {
                        int _countnoadd = _count1 + _count2;
                        count = _countnoadd;
                        return flagEqual;
                    }
                } else {//点数不大于10
                    count = _count1 + _count2;
                    return flagEqual;
                }
            }
            std::cout << "the count is: " << _count1 << " and " << _count2 << "\n";
            if (!turnRadio) {//没有翻转广播台
                if (_count1 == _count2)
                    flagEqual = 1;
                count = _count1 + _count2;
                return flagEqual;
            } else {//翻转了广播台
                std::cout << "Do you want to toss again(y/n)?\n";
                char s;
                while (1) {
                    try {
                        std::cin >> s;
                        if (s != 'y' && s != 'n')
                            throw JeueurException("erreur:Enter a wrong answer");
                        else if (std::cin.fail())
                            throw JeueurException("erreur:Enter a wrong answer");
                        else
                            break;
                    } catch (exception &e) {
                        std::cout << e.what() << std::endl;
                        std::cout << "Do you want to toss again(y/n)?\n";
                        std::cin.clear();
                        std::cin.sync();
                    }

                    if (s == 'y') {//要求重掷
                        std::cout << "Choose one dice or tow dices(1/2):" << std::endl;
                        int m;
                        while (1) {
                            try {
                                std::cin >> m;
                                if (std::cin.fail())
                                    throw JeueurException("erreur:Enter a wrong answer");
                                else if (m != 1 && m != 2)
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
                    } else {
                        count = _count1 + _count2;
                        return flagEqual;
                    }
                }
            }
        }
    }
}

void Jeueur::pay(Jeueur& j) {//给其他玩家钱，传入其他玩家
    if (!flagOther)//如果其他玩家没有红卡，退出pay()
        return;
    if (count == 1) {//如果是1->寿司店
        for (auto it = j.begin(); it != j.end(); it++) {//遍历其他玩家的手牌
            if ((*it).getCount1() == count) {//如果其他玩家有对应点数的红卡
                if (!turnCenter) {//没有建造购物中心
                    if (money >= 3 * j.getNum((*it).getName())) {//钱数大于卡牌数
                        money -= 3 * j.getNum((*it).getName());
                        j.addMoney(3 * j.getNum((*it).getName()));
                    } else { //钱数小于卡牌数，全给
                        j.addMoney(money);
                        money = 0;
                    }
                } else {//建造了购物中心
                    if (money >= 6 * j.getNum((*it).getName())) {//钱数大于卡牌数*2
                        money -= 6 * j.getNum((*it).getName());
                        j.addMoney(6 * j.getNum((*it).getName()));
                    } else {//钱数小于卡牌数*2，全给
                        j.addMoney(money);
                        money = 0;
                    }
                }
                break;
            } else if (count == 3) {//如果是3—>咖啡车
                for (auto it = j.begin(); it != j.end(); it++) {//遍历其他玩家的手牌
                    if ((*it).getCount1() == count && turnHarbor) {//如果其他玩家有对应点数的红卡
                        if (!turnCenter) {//没有建造购物中心
                            if (money >= j.getNum((*it).getName())) {//钱数大于卡牌数
                                money -= j.getNum((*it).getName());
                                j.addMoney(j.getNum((*it).getName()));
                            } else { //钱数小于卡牌数，全给
                                j.addMoney(money);
                                money = 0;
                            }
                        } else {//建造了购物中心
                            if (money >= 2 * j.getNum((*it).getName())) {//钱数大于卡牌数*2
                                money -= 2 * j.getNum((*it).getName());
                                j.addMoney(2 * j.getNum((*it).getName()));
                            } else {//钱数小于卡牌数*2，全给
                                j.addMoney(money);
                                money = 0;
                            }
                        }
                        break;
                    }
                }
            } else if (count == 7) {//如果是7->披萨店
                for (auto it = j.begin(); it != j.end(); it++) {//遍历其他玩家的手牌
                    if ((*it).getCount1() == count) {//如果其他玩家有对应点数的红卡
                        if (!turnCenter) {//没有建造购物中心
                            if (money >= j.getNum((*it).getName())) {//钱数大于卡牌数
                                money -= j.getNum((*it).getName());
                                j.addMoney(j.getNum((*it).getName()));
                            } else { //钱数小于卡牌数，全给
                                j.addMoney(money);
                                money = 0;
                            }
                        } else {//建造了购物中心
                            if (money >= 2 * j.getNum((*it).getName())) {//钱数大于卡牌数*4
                                money -= 2 * j.getNum((*it).getName());
                                j.addMoney(2 * j.getNum((*it).getName()));
                            } else {//钱数小于卡牌数*4，全给
                                j.addMoney(money);
                                money = 0;
                            }
                        }
                        break;
                    }
                }
            } else if (count == 8) {//如果是8->汉堡店
                for (auto it = j.begin(); it != j.end(); it++) {//遍历其他玩家的手牌
                    if ((*it).getCount1() == count) {//如果其他玩家有对应点数的红卡
                        if (!turnCenter) {//没有建造购物中心
                            if (money >= j.getNum((*it).getName())) {//钱数大于卡牌数
                                money -= j.getNum((*it).getName());
                                j.addMoney(j.getNum((*it).getName()));
                            } else {//钱数小于卡牌数，全给
                                j.addMoney(money);
                                money = 0;
                            }
                        } else {//建造了购物中心
                            if (money >= 2 * j.getNum((*it).getName())) {//钱数大于卡牌数*4
                                money -= 2 * j.getNum((*it).getName());
                                j.addMoney(2 * j.getNum((*it).getName()));
                            } else {//钱数小于卡牌数*4，全给
                                j.addMoney(money);
                                money = 0;
                            }
                        }
                        break;
                    }
                }
            } else if (count == 9 || count == 10) {//其他（9，10）->餐厅
                for (auto it = j.begin(); it != j.end(); it++) {//遍历其他玩家的手牌
                    if ((*it).getCount1() == count) {//如果其他玩家有对应点数的红卡
                        if (!turnCenter) {//没有建造购物中心
                            if (money >= 2 * j.getNum((*it).getName())) {//钱数大于卡牌数*2
                                money -= 2 * j.getNum((*it).getName());
                                j.addMoney(2 * j.getNum((*it).getName()));
                            } else { //钱数小于卡牌数，全给
                                j.addMoney(money);
                                money = 0;
                            }
                        } else {//建造了购物中心
                            if (money >= 4 * j.getNum((*it).getName())) {//钱数大于卡牌数*4
                                money -= 4 * j.getNum((*it).getName());
                                j.addMoney(4 * j.getNum((*it).getName()));
                            } else {//钱数小于卡牌数*4，全给
                                j.addMoney(money);
                                money = 0;
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
}
void Jeueur::allGet(Jeueur& j) {
    if(count == 9) {//如果是9->矿场
        for (auto it = j.begin(); it != j.end();it++) {//遍历其他玩家的手牌
            if ((*it).getCount1() == count) //如果其他玩家有对应点数的蓝卡
                j.addMoney(3);
        }
    }else if(count == 10){//10->果园
        for (auto it = j.begin(); it != j.end();it++) {//遍历其他玩家的手牌
            if ((*it).getCount1() == count) //如果其他玩家有对应点数的蓝卡
                j.addMoney(3);
        }
    }else if(count == 1 || count == 2 || count == 4 || count == 5){//其他(1,2,4,5)->麦田，农场，林场
        for (auto it = j.begin(); it != j.end();it++) {//遍历其他玩家的手牌
            if ((*it).getCount1() == count && (*it).getCount2() == 0) //如果其他玩家有对应点数的蓝卡(排除蛋糕房)
                j.addMoney(1);//加1
        }
    }else if(count == 8){//如果是8->渔船
        for (auto it = j.begin(); it != j.end();it++) {//遍历其他玩家手牌
            if ((*it).getCount1() == count || turnHarbor)
                j.addMoney(3);//加1
        }
    }else if(count == 12 || count == 13 ){//12~13->观光船
        int _count1 = (rand() % 6) + 1;
        int _count2 = (rand() % 6) + 1;
        int _count;
        for (auto it = j.begin(); it != j.end();it++) {
            if ((*it).getCount1() == count)
                _count = _count1 + _count2;
                j.addMoney(_count);
        }
    }
}

void Jeueur::selfGet(){
    if (count == 1){
        for(auto it = begin(); it !=end();it++) {//遍历本玩家的手牌
            if ((*it).getName() == "cornfield")//如果有麦田
                money += 1;//加1
        }
    }else if(count == 2){//2->农场
        for(auto it = begin(); it != end();it++){//遍历本玩家的手牌
            if((*it).getName() == "farm")//如果有农场
                money += 1;//加1
            if((*it).getName() == "bakery"){//如果有蛋糕房
                if(!turnCenter)//如果没有建成购物中心
                    money += 1;//加1
                else//如果建成了购物中心
                    money += 2;//加2
            }
        }
    }else if(count == 3){
        for(auto it = begin(); it != end();it++){//遍历本玩家的手牌
            if((*it).getName() == "bakery"){//如果有蛋糕房
                if(!turnCenter)//如果没有建成购物中心
                    money += 1;//加1
                else//如果建成了购物中心
                    money += 2;//加2
            }
        }
    }else if(count == 4){
        for(auto it = begin(); it != end();it++) {//遍历本玩家的手牌
            if ((*it).getName() == "store") {//如果有便利店
                if (!turnCenter)//如果没有建成购物中心
                    money += 3;//加3
                else//如果建成了购物中心
                    money += 6;//加6*牌数
            }
        }
    }else if(count == 5) {
        for (auto it = begin(); it != end(); it++) {//遍历本玩家的手牌
            if ((*it).getName() == "forest")//如果有林场
                money += 1;//加1
        }
    }else if(count == 6) {
        for (auto it = begin(); it != end(); it++) {//遍历本玩家的手牌
            if ((*it).getName() == "florist")//如果有花店
                money += 1;//加1
        }
    }else if(count == 7){
        for(auto it = begin(); it != end();it++) {//遍历本玩家的手牌
            if ((*it).getName() == "cheeseFactory") {//如果有奶酪工厂
                int n = 0;//用于存储农场卡牌数
                for(auto im = begin(); im != end();it++){
                    if((*im).getName() == "farm")
                        n += 1;
                }
                money += 3*n;//加3*农场卡牌数
            }
        }
    }else if(count == 8){
        for(auto it = begin(); it != end();it++) {//遍历本玩家的手牌
            if ((*it).getName() == "furnitureFactory") {//如果有家具工厂
                int n = 0,m = 0;//用于存储林场，矿场卡牌数
                for(auto im = begin(); im != end();it++){
                    if((*im).getName() == "forest")
                        n += 1;
                    if((*im).getName() == "mineField")
                        m += 1;
                }
                money += 3*(n+m);//加3*(林场+矿场卡牌数)
            }
        }
    }else if(count == 9){
        for(auto it = begin(); it != end();it++){//遍历本玩家的手牌
            if((*it).getName() == "mineField")//如果有矿场
                money += 5;//加5
        }
    }
    else if(count == 10){
        for(auto it = begin(); it != end();it++){//遍历本玩家的手牌
            if((*it).getName() == "orchard")//如果有果园
                money += 3;//加3
        }
    }else if(count == 11 || count == 12){
        for(auto it = begin(); it != end();it++) {//遍历本玩家的手牌
            if ((*it).getName() == "market") {//如果有果蔬超市
                int n = 0,m = 0;//用于存储麦田，果园卡牌数
                for(auto im = begin(); im != end();it++){
                    if((*im).getName() == "cornfield")
                        n += 1;
                    if((*im).getName() == "market")
                        m += 1;
                }
                money += 3*(n+m);//加3*(麦田+果园卡牌数)
            }
        }
    }else if(count == 12 || count == 13){
        for(auto it = begin(); it != end();it++) {//遍历本玩家的手牌
            if ((*it).getName() == "foodmarket") {//如果有食品市场
                int n = 0,m = 0,j = 0,k = 0,l = 0;//用于存储cup类型卡牌数
                for(auto im = begin(); im != end();it++){
                    if((*im).getName() == "coffeeCar")
                        n += 1;
                    if((*im).getName() == "restaurant")
                        m += 1;
                    if((*im).getName() == "sushi bar")
                        j += 1;
                    if((*im).getName() == "pizzashop")
                        k += 1;
                    if((*im).getName() == "hamburgershop")
                        l += 1;
                }
                money += 2*(n+m+j+k+l);//加2*cup类型数
                }
            }
    }
}

void Jeueur::changeCarte(Jeueur& j,Carte& jCname,Carte& sCname) {
    for (auto it = j.begin(); it != j.end(); it++) {
        if ((*it).getName() == jCname.getName()) {//被选中的玩家减牌
            j.cartes.erase(it);
            break;
        }
    }
    j.cartes.push_back(&sCname);
    for (auto it = begin(); it !=end(); it++) {
        if ((*it).getName() == sCname.getName()) {//玩家减牌
            cartes.erase(it);
            break;
        }
    }
    cartes.push_back(&jCname);
}

void Jeueur::getJeueur1(Jeueur& j){
    for (auto it = j.begin(); it != j.end();it++)
        if(j.getMoney() >= 1) {
            int n = 0, m = 0, j = 0, k = 0, l = 0, o = 0, p = 0, q = 0,s = 0;
            for (auto im = begin(); im != end(); it++) {
                if ((*im).getName() == "coffeeCar") {
                    n += 1;
                }
                if ((*im).getName() == "restaurant"){
                    m += 1;}
                if ((*im).getName() == "pizzashop"){
                    j += 1;}
                if ((*im).getName() == "sushi bar"){
                    k += 1;}
                if ((*im).getName() == "hamburgershop"){
                    l += 1;}
                if ((*im).getName() == "bakery"){
                    o += 1;}
                if ((*im).getName() == "store"){
                    p += 1;}
                if ((*im).getName() == "florist"){
                    q += 1;}
            }
            s = n + m + j + k + l + o + p + q;
            money += s;
        }
    else{
                money += j.getMoney();
                j.setMoney(0);
            }

    }

void Jeueur::getJeueur5(Jeueur& j){
    if(j.getMoney() >= 5){
        money += 5;
        j.redMoney(5);
    }else{
        money += j.getMoney();
        j.setMoney(0);
    }
}

void Jeueur::getJeueur2(Jeueur& j){
    if(j.getMoney() >= 2){
        money += 2;
        j.redMoney(2);
    }else{
        money += j.getMoney();
        j.setMoney(0);
    }
}

void Jeueur::getJeueurhalf(Jeueur& j) {
    if (j.getMoney() >= 10) {
        int m;
        if(j.getMoney()%2 == 0){
            money += 0.5 * j.getMoney();
            m = 0.5 * j.getMoney();
        }else{
            money += 0.5 * (j.getMoney() - 1);
            m = 0.5 * (j.getMoney() - 1);
        }
        j.redMoney(m);
    }
}



bool Jeueur::isFlagOnce() const {
    return flagOnce;
}

bool Jeueur::isTurnHarbor() const {
    return turnHarbor;
}

bool Jeueur::isTurnRailway() const {
    return turnRailway;
}

bool Jeueur::isTurnCenter() const {
    return turnCenter;
}

bool Jeueur::isTurnPark() const {
    return turnPark;
}

bool Jeueur::isTurnRadio() const {
    return turnRadio;
}

bool Jeueur::isTurnAirport() const {
    return turnAirport;
}



void Jeueur::isJHaveCarte(Jeueur& j, Carte& jCname) {
    auto it = std::find(j.cartes.begin(), j.cartes.end(), &jCname);
    if (it == j.end())
        throw JeueurException("erreur:The player don't have this card");
}

void Jeueur::isHaveCarte( Carte& sCname){
    auto im = std::find( cartes.begin(), cartes.end(), &sCname);
    if (im == end())
        throw JeueurException("erreur:You don't have this card");
}

Carte& Jeueur::getCarte(std::string name){
    for(auto it = begin(); it != end();it++){
        if((*it).getName() == name)
            return (*it);
    }
}

void Jeueur::achete(std::string name,BankCarte& bank){
    if(name == "harbor" && money>=2){
        if( turnHarbor )
            throw JeueurException("erreur:You have purchased the card 'railwayStation'");
        turnHarbor = 1;
        money -= 2;
        if(money == 0){
            money += 1;
        }
        cartes.push_back(&Jeu::getInstance().getCarte(150));
    }else if(name == "harbor" && money<2)
        throw JeueurException("erreur:You don't have enough money to buy this card");
    else if(name == "railwayStation" && money>=4){
        if( turnRailway )
            throw JeueurException("erreur:You have purchased the card 'railwayStation'");
        turnRailway = 1;
        money -= 4;
        if(money == 0){
            money += 1;
        }
        cartes.push_back(&Jeu::getInstance().getCarte(151));
    }else if(name == "railwayStation" && money<4)
        throw JeueurException("erreur:You don't have enough money to buy this card");
    else if(name == "shoppingCenter" && money>=10) {
        if( turnCenter )
            throw JeueurException("erreur:You have purchased the card 'shoppingCenter'");
        turnCenter = 1;
        money -= 10;
        if(money == 0){
            money += 1;
        }
        cartes.push_back(&Jeu::getInstance().getCarte(152));
    }else if(name == "shoppingCenter" && money<10)
        throw JeueurException("erreur:You don't have enough money to buy this card");
    else if(name == "amusementPark" && money>=16) {
        if( turnPark )
            throw JeueurException("erreur:You have purchased the card 'amusementPark'");
        turnPark = 1;
        money -= 16;
        if(money == 0){
            money += 1;
        }
        cartes.push_back(&Jeu::getInstance().getCarte(153));
    }else if(name == "amusementPark" && money<16)
        throw JeueurException("erreur:You don't have enough money to buy this card");
    else if(name == "radioStation" && money>=22) {
        if( turnRadio )
            throw JeueurException("erreur:You have purchased the card 'radioStation'");
        turnRadio = 1;
        money -= 22;
        if(money == 0){
            money += 1;
        }
        cartes.push_back(&Jeu::getInstance().getCarte(154));
    }
    else if(name == "airport" && money>=30) {
        if( turnAirport )
            throw JeueurException("erreur:You have purchased the card 'airport'");
        turnAirport = 1;
        money -= 30;
        if(money == 0){
            money += 1;
        }
        cartes.push_back(&Jeu::getInstance().getCarte(155));
    }else if(name == "airport" && money<30)
        throw JeueurException("erreur:You don't have enough money to buy this card");
    else if(name == "businessCenter"|| name == "gym" || name == "bandstand"|| name == "press"|| name == "taxoffice") {
        if(flagOnce)
            throw JeueurException("erreur:You have purchased the purple card");
        if(money<bank.getPrice(name))
            throw JeueurException("erreur:You don't have enough money to buy this card");
        flagOnce = 1;
        cartes.push_back(bank.getCarte(name));
        setOnce(name);
        money = money - bank.getPrice(name);
        if(money == 0){
            money += 1;
        }
        bank.redCarte(name);
    }else{
        int i;
        for (i = 0;i < 25; i++) {
           if (Jeu::getInstance().getCartes()[i]->getName() == name)break;
        }
       if(i == 25)
        throw JeueurException("erreur:This card doesn't exist");
        else if(bank.getNum(name)==0)
            throw JeueurException("erreur:This card was bought out");
        else if(money<bank.getPrice(name))
            throw JeueurException("erreur:You don't have enough money to buy this card");
        else{
            cartes.push_back(bank.getCarte(name));
            money = money - bank.getPrice(name);
            if(money == 0){
                money += 1;
            }
            bank.redCarte(name);
        }
    }
}

const std::vector<Carte *> &Jeueur::getCartes() const {
    return cartes;
}

void Jeueur::setOnce(const std::string &once) {
    Jeueur::once = once;
}


