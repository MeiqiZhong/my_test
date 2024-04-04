#include "Controleur.h"

Jeueur& Controleur::getJeueur(std::string name) {
    for(int i = 0; i < JeueurNum ; i++){
        if(J[i]->getName() == name)
            return *J[i];
    }
}

int Controleur::choseFirst(){//得到第一个玩家的下标
    int i=0;
    int max = J[0]->getBirthday();
    for(int k = 1; k < JeueurNum;k++){
        i = max >= J[k]->getBirthday()? i:i+1;
        max = max >= J[k]->getBirthday()? max:J[k]->getBirthday();
    }
    return i;
}

void Controleur::rearrange(){//重新分配向量空间，让被选为第一的人作为向量空间的第一位
    int i = choseFirst();
    std::cout<<"The first player is "<<J[i]->getName()<<std::endl;
    for(int k = 0 ; k < i ; k++){
        J.push_back(J[0]);
        J.erase(J.begin());
    }
}

void Controleur::afficherAll(){
    for(int i = 0; i < JeueurNum ;i++)
        J[i]->afficherCarte();
}

bool Controleur::win(Jeueur j){
    return (j.isTurnRailway() && j.isTurnCenter() && j.isTurnPark() && j.isTurnRadio() && j.isTurnHarbor() && j.isTurnAirport());//短路与，判断是否都建成
}

void Controleur::process() {
    bool flag = 0;
    for (int i = 0; i < JeueurNum || !flag; i++) {//经过所有玩家回合
        bank.afficher();
        bool equal;
        std::cout << "\n    *************************** Turn of " << J[i]->getName() << " ***************************"
                  << std::endl;
        if (J[i]->getName() == "AI")//判断是否是AI
            equal = J[i]->AI::dice();//掷骰子,并得到两个骰子是否相同
        else equal = J[i]->Jeueur::dice();
        if (J[i]->getCount() == 1 || J[i]->getCount() == 3 || J[i]->getCount() == 7 || J[i]->getCount() == 8
            || J[i]->getCount() == 9 || J[i]->getCount() == 10) { //进行红卡的判定
            int n = i;//n得到当前玩家的下标
            for (int k = 0; k < JeueurNum - 1; k++) {//循环玩家数减1次
                if (!J[i]->getMoney())
                    break;//当前玩家没有钱了，退出循环
                if (n - 1 >= 0) {//如果当前玩家在vector容器中有前继
                    J[i]->pay(*J[n - 1]);
                    n--;
                } else {//没有前继
                    J[i]->pay(*J[n - 1 + JeueurNum]);
                    n--;
                }
            }
        }
        if (J[i]->getCount() == 1 || J[i]->getCount() == 2 || J[i]->getCount() == 4 || J[i]->getCount() == 5
            || J[i]->getCount() == 8 || J[i]->getCount() == 9 || J[i]->getCount() == 10 || J[i]->getCount() == 12 ||
            J[i]->getCount() == 13) { //进行蓝卡的判定
            int n = i; //n得到当前玩家的下标
            for (int k = 0; k < JeueurNum - 1; k++) {//循环玩家数减1次
                if (n - 1 >= 0) { //如果当前玩家在vector容器中有前继
                    J[i]->allGet(*J[n - 1]);
                    n--;
                } else {//没有前继
                    J[i]->allGet(*J[n - 1 + JeueurNum]);
                    n--;
                }
            }
        }
        if (J[i]->getCount() != 6) {//进行绿卡的判定
            J[i]->selfGet();
        }
        afficherAll();

        if (J[i]->getCount() == 6 || J[i]->getCount() == 7 || J[i]->getCount() == 8 ||
            J[i]->getCount() == 9) { //进行紫卡的判断
            if (J[i]->isFlagOnce()) {//有紫卡
                for (auto it = J[i]->getCartes().begin(); it != J[i]->getCartes().end(); it++) {//遍历手牌
                    if (J[i]->getOnce() == "businessCenter") {//如果是商业中心
                        std::string Jname;
                        std::string jCname;
                        std::string sCname;
                        int n = 0;
                        char s;
                        std::cout << "Do you want to change the card?(y/n):" << std::endl;
                        while (1) {
                            try {
                                if (J[i]->getName() == "AI") {
                                    s = J[i]->AI::y_or_n();
                                    cout << s << endl;
                                } else cin >> s;
                                if (s != 'y' && s != 'n')
                                    throw ControleurException("erreur:Enter a wrong answer");
                                else
                                    break;
                            } catch (exception &e) {
                                std::cout << e.what() << std::endl;
                                std::cout << "Do you want to change the card again(y/n)?:\n";
                            }
                        }
                        if (s == 'n')
                            break;
                        char a;
                        std::cout << "Do you want to look at the introduction for all the cards(y/n)?" << std::endl;
                        while (1) {
                            try {
                                if (J[i]->getName() == "AI") {
                                    a = J[i]->AI::y_or_n();
                                    cout << a << endl;
                                } else cin >> a;
                                if (a != 'y' && a != 'n')
                                    throw ControleurException("erreur:Enter a wrong answer");
                                else
                                    break;
                            } catch (exception &e) {
                                std::cout << e.what() << "\n";
                                std::cout << "Do you want to look at the introduction for all the cards(y/n) again?"
                                          << std::endl;
                            }
                        }
                        if (a == 'y')
                            afficher_allCartes();
                        std::cout << "Please enter the player you want to change with(name):" << std::endl;
                        int j = 1;
                        while (j) {
                            try {
                                j = 0;
                                if (J[i]->getName() == "AI") {
                                    n = J[i]->get_n(i, JeueurNum);
                                    Jname = J[n]->getName();
                                    cout << Jname << endl;
                                } else cin >> Jname;
                                int k = 0;
                                for (k = 0; k < JeueurNum; k++) {
                                    if (Jname == J[k]->getName())
                                        break;
                                }
                                if (k == JeueurNum)
                                    throw ControleurException("erreur:This player does not exist");
                                else {
                                    std::cout << "Please enter the name of card you want to get:" << std::endl;
                                    if (J[i]->getName() == "AI") {
                                        jCname = J[i]->get_change_carte(*J[n]);
                                        cout << jCname << endl;
                                    } else std::cin >> jCname;
                                    if (jCname == "gym" || jCname == "businessCenter" || jCname == "bandstand"|| jCname == "press"|| jCname == "taxoffice")
                                        throw ControleurException(
                                                "erreur:You can't get the card whose form is building from the other player");
                                    J[i]->isJHaveCarte(getJeueur(Jname), getJeueur(Jname).getCarte(jCname));
                                    std::cout << "Please enter the name of card you want to give:" << std::endl;
                                    if (J[i]->getName() == "AI") {
                                        sCname = J[i]->self_change_carte();
                                        cout << sCname << endl;
                                    } else std::cin >> sCname;
                                    if (sCname == "gym" || sCname == "businessCenter" || sCname == "bandstand"|| sCname == "press"|| sCname == "taxoffice")
                                        throw ControleurException(
                                                "erreur:You can't give a the card whose form is building to the other player");
                                    J[i]->isHaveCarte(J[i]->getCarte(sCname));
                                }
                            }
                            catch (exception &e) {
                                std::cout << e.what() << std::endl;
                                std::cout << "Please enter the player you want to change with(name) again:"
                                          << std::endl;
                                j = 1;
                            }
                        }
                        J[i]->changeCarte(getJeueur(Jname), getJeueur(Jname).getCarte(jCname),
                                          J[i]->getCarte(sCname));
                        int q = 0;
                        break;
                    } else if (J[i]->getOnce() == "gym") {//如果是体育馆
                        int n = i;//n得到当前玩家的下标
                        for (int k = 0; k < JeueurNum - 1; k++) {//循环玩家数减1次
                            if (n - 1 >= 0) {//如果当前玩家在vector容器中有前继
                                J[i]->getJeueur2(*J[n - 1]);
                                n--;
                            } else {//没有前继
                                J[i]->getJeueur2(*J[n - 1 + JeueurNum]);
                                n--;
                            }
                        }
                        break;
                    } else if (J[i]->getOnce() == "bandstand") {//如果是音乐台
                        std::string Jname;
                        std::cout << "Please enter the player you want to get money from(name):" << std::endl;
                        while (1) {
                            try {
                                if (J[i]->getName() == "AI") {
                                    Jname = J[i]->bandstand_get_money_from(i, J);
                                    cout << Jname << endl;
                                } else std::cin >> Jname;
                                int k = 0;
                                for (k = 0; k < JeueurNum; k++) {
                                    if (Jname == J[k]->getName())
                                        break;
                                }
                                if (k == JeueurNum)
                                    throw ControleurException("erreur:This player does not exist");
                                else
                                    break;
                            }
                            catch (exception &e) {
                                std::cout << e.what() << std::endl;
                                std::cout << "Please enter the player you want to get money from(name) again:"
                                          << std::endl;
                            }
                        }
                        J[i]->getJeueur5(getJeueur(Jname));
                        break;

                    } else if (J[i]->getOnce() == "press") {//如果是出版社
                        int n = i;//n得到当前玩家的下标
                        for (int k = 0; k < JeueurNum - 1; k++) {//循环玩家数减1次
                            if (n - 1 >= 0) {//如果当前玩家在vector容器中有前继
                                J[i]->getJeueur1(*J[n - 1]);
                                n--;
                            } else {//没有前继
                                J[i]->getJeueur1(*J[n - 1 + JeueurNum]);
                                n--;
                            }
                        }
                        break;
                    } else if (J[i]->getOnce() == "taxoffice") {//如果是税务局
                        int n = i;//n得到当前玩家的下标
                        for (int k = 0; k < JeueurNum - 1; k++) {//循环玩家数减1次
                            if (n - 1 >= 0) {//如果当前玩家在vector容器中有前继
                                J[i]->getJeueurhalf(*J[n - 1]);
                                n--;
                            } else {//没有前继
                                J[i]->getJeueurhalf(*J[n - 1 + JeueurNum]);
                                n--;
                            }
                        }
                    }
                }
            }
        }


        //买卡
        std::cout << "Do you want to look at the introduction for all the cards(y/n)?" << std::endl;
        char a;
        int k = 1;
        while (k) {
            try {
                k = 0;
                if (J[i]->getName() == "AI") {
                    a = J[i]->y_or_n();
                    cout << a << endl;
                } else std::cin >> a;
                if (std::cin.fail())//抛出输入类型异常情况
                    throw ControleurException("erreur:Enter a wrong answer");
                else if (a != 'y' && a != 'n')
                    throw ControleurException("erreur:Enter a wrong answer");
                else if (a == 'y')
                    afficher_allCartes();
                else if (a == 'n')
                    break;
            } catch (exception &e) {
                std::cout << e.what() << "\n";
                std::cout << "Do you want to look at the introduction for all the cards(y/n) again?"
                << std::endl;
                k = 1;
                std::cin.clear();
                std::cin.sync();
            }
        }
        std::cout << "Do you want to buy a card(y/n)?" << std::endl;
        char c;
        std::string s;
        int l = 1;
        while (l) {
            try {
                l = 0;
                if (J[i]->getName() == "AI") { c = J[i]->buy_carte_y_or_n(); }
                else std::cin >> c;
                if (std::cin.fail())//抛出输入类型异常情况
                    throw ControleurException("erreur:Enter a wrong answer");
                else if (c != 'y' && c != 'n')
                    throw ControleurException("erreur:Enter a wrong answer");
                else if (c == 'y') {
                    std::cout << "Please enter the card you want to buy(name):" << std::endl;
                    if (J[i]->getName() == "AI") { s = J[i]->achete_carte(bank); }
                    else cin >> s;
                    J[i]->achete(s, bank);
                } else if (c == 'n')
                    break;
            } catch (exception &e) {
                std::cout << e.what() << "\n";
                std::cout << "Do you want to buy a card(y/n) again?" << std::endl;
                l = 1;
                std::cin.clear();
                std::cin.sync();
            }
        }
        if (win(*J[i])) {//判断是否获胜
            std::cout << "Game over !" << std::endl;
            std::cout << "Congratulations to " << J[i]->getName() << "!!!" << std::endl;
            flag = 1;
        }
        if (equal) //如果两个骰子掷到相同点数，该玩家再来一次
            if (J[i]->isTurnPark())
                i--;
        if (i == JeueurNum - 1)
            i = -1;
        if (flag)
            return;
    }
}

void Controleur::is_Expansion() {
    char a;
    cout<<"Do you want to chose the Expansion Pack?(y/n)"<<endl;
    cin>>a;
    if(a=='n') modle=0;
    else modle=1;
}

Controleur::Controleur():bank(modle){
    std::cout<<"Please enter the number of players(2-6):"<<std::endl;
    int i=1;
    while(i){
        try{i=0;
            std::cin>>JeueurNum;
            if(JeueurNum=1){cout<<"you will play with an AI"<<endl;}
            if(JeueurNum<=0||JeueurNum>6)//抛出人数异常情况
                throw ControleurException("erreur:The number of peoples is wrong");
        }
        catch(exception& e){//捕获异常并要求玩家重新输入
            std::cout<<e.what()<<"\n";
            std::cout<<"Please enter the number of players(2-6) again:"<<std::endl;
            i=1;
        }
    }
    for(int i = 0; i < JeueurNum; i++){
        std::string name = "";
        int bir;
        std::cout<<"Please enter the name of player"<<i+1<<":"<<std::endl;
        std::cin>>name;
        std::cout<<"Please enter the birthday of player(8 digits)"<<i+1<<":"<<std::endl;
        int j=1;
        while(j) {
            try {
                j = 0;
                std::cin >> bir;
                if (std::cin.fail())//抛出输入类型异常情况
                    throw ControleurException("erreur:Enter an inconsistent type");
            }
            catch (exception &e) {//捕获异常并要求玩家重新输入
                std::cout << e.what() << "\n";
                std::cout << "Please enter the birthday of player(8 digits) again" << i + 1 << ":" << std::endl;
                j = 1;
                std::cin.clear();
                std::cin.sync();
            }
        }
        J.push_back(new AI(name,bir));

    }
    if(JeueurNum==1) {J.push_back(new AI);JeueurNum=2;}
}

Controleur::~Controleur() {
    AI* item = nullptr;
    for(int i = 0;i < J.size();i++){
        item= J[i];
        delete item;
    }
    std::vector<AI*> temp;
    J.swap(temp);
}

void Controleur::afficher_allCartes(){
    std::cout<<"-------------------------------------------------------Building--------------------------------------------------------\n";
    std::cout<<"|| *** cornfiled *** ||    *** farm ***   ||    *** bakery ***    ||     *** coffeeCar ***   ||     *** store ***    ||\n";
    std::cout<<"||price: 1           ||price: 1           ||price: 1              ||price: 2                 ||price: 2              ||\n";
    std::cout<<"||count: 1           ||count: 2           ||count: 2 or 3         ||count: 3                 ||count: 4              ||\n";
    std::cout<<"||range: all         ||range: all         ||range: self           ||range: other             ||range: self           ||\n";
    std::cout<<"||form: wheat        ||form: cow          ||form: house           ||form: cup                ||form: house           ||\n";
    std::cout<<"||All players get one||All players get one||The current player get||Other players can get one||The current player get||\n";
    std::cout<<"||money from the bank||money from the bank||one money from the    ||money from the player who||three moneys from the ||\n";
    std::cout<<"||for each cornfield.||for each farm.     ||bank for each bakery. ||get count 3 for each     ||bank for each store.  ||\n";
    std::cout<<"||                   ||                   ||                      ||coffeeCar.               ||                      ||\n";
    std::cout<<"                      --------------------------Important Building-------------------------                            \n";
    std::cout<<"||   *** forest ***  || *** businessCenter *** ||     *** gym ***    || *** bandstand *** ||  *** cheeseFactory ***  ||\n";
    std::cout<<"||price: 3           ||price: 8                ||price: 6            ||price: 7           ||price: 5                 ||\n";
    std::cout<<"||count: 5           ||count: 6                ||count: 6            ||count: 6           ||count: 7                 ||\n";
    std::cout<<"||range: all         ||range: once             ||range: once         ||range: once        ||range: self              ||\n";
    std::cout<<"||form: gear         ||form: building          ||form: building      ||form: building     ||form: factory            ||\n";
    std::cout<<"||All players get one||The current player can  ||The current player  ||The current player ||The current player get   ||\n";
    std::cout<<"||money from the bank||exchange the card whose ||get two moneys from ||get five moneys    ||three moneys from the    ||\n";
    std::cout<<"||for each forest.   ||form isn't building with||the each player.    ||from any one payer.||bank for each card whose ||\n";
    std::cout<<"||                   ||any one player.         ||                    ||                   ||form is cow.             ||\n";
    std::cout<<"                      ---------------------------------------------------------------------                            \n";
    std::cout<<"||** furnitureFactory **||  *** mineField ***  ||    *** restaurant ***   || *** orchard *** ||    *** market ***    ||\n";
    std::cout<<"||price: 3              ||price: 6             ||price: 3                 ||price: 3         ||price: 2              ||\n";
    std::cout<<"||count: 8              ||count: 9             ||count: 9 or 10           ||count: 10        ||count: 11 or 12       ||\n";
    std::cout<<"||range: self           ||range: all           ||range: other             ||range: all       ||range: self           ||\n";
    std::cout<<"||form: factory         ||form: gear           ||form: cup                ||form: wheat      ||form: factory         ||\n";
    std::cout<<"||The current player get||All players get five ||Other players can get two||All players get  ||The current player get||\n";
    std::cout<<"||three moneys from the ||moneys from the bank ||moneys from the player   ||three moneys from||three moneys from the ||\n";
    std::cout<<"||bank for each card    ||for each mineField.  ||who get count 9 or 10    ||the bank for each||bank for each card    ||\n";
    std::cout<<"||whose form is gear.   ||                     ||for each restaurant.     ||orchard.         ||whose form is wheat.  ||\n";
    std::cout<<"------------------------------------------------building---------------------------------------------------------------\n";
    std::cout<<"||    ** sushibar **    || *** flowerfield *** || *** florist *** ||  *** press ***   ||      *** pizzashop ***      ||\n";
    std::cout<<"||price: 2              ||price: 2             ||price: 1         ||price: 5          ||price: 1                     ||\n";
    std::cout<<"||count: 1              ||count: 4             ||count: 6         ||count: 7          ||count: 7                     ||\n";
    std::cout<<"||range: other          ||range: all           ||range: self      ||range: once       ||range: other                 ||\n";
    std::cout<<"||form: cup             ||form: cheat          ||form: house      ||form: building    ||form: cup                    ||\n";
    std::cout<<"||players who have habor||All players get one  ||The current play ||The current pla   ||Other players who get count 3||\n";
    std::cout<<"||can get 3 money from t||money from the bank f||er get one money ||yer get 1 money e ||must give you 1 money each pi||\n";
    std::cout<<"||he player who get coun||or each card         ||from the bank fo ||ach from those ha ||zzashop you have             ||\n";
    std::cout<<"||t 1 for each sushi bar||                     ||each card        ||ve cup and house  ||                             ||\n";
    std::cout<<"------------------------------------------------building---------------------------------------------------------------\n";
    std::cout<<"|| ** hamburgershop **  || *** fishingboat *** || *** taxoffice *** || *** sightseeingship *** || *** foodmarket *** ||\n";
    std::cout<<"||price: 1              ||price: 2             ||price: 4           ||price: 5                 ||price: 2            ||\n";
    std::cout<<"||count: 8              ||count: 8             ||count: 8 or 9      ||count: 12 or 13          ||count: 12 or 13     ||\n";
    std::cout<<"||range: other          ||range: all           ||range: once        ||range: all               ||range: self         ||\n";
    std::cout<<"||form: cup             ||form: ship           ||form: building     ||form: ship               ||form: factory       ||\n";
    std::cout<<"||Other players can get ||All players who have ||The current player ||The current player get 1 ||The current player g||\n";
    std::cout<<"||1 money from the playe||build harbor get 3 mo||get the half money ||chance to reroll the dice||et 2 moneys from the||\n";
    std::cout<<"||r who get count 8 for ||neys from the bank   ||from the player who||and get the money equal t||bank each cup you ha||\n";
    std::cout<<"||each hamburgershop    ||for each fishingboat ||have >=10 money    ||he sum of the count      ||ve                  ||\n";
    std::cout<<std::endl;
    std::cout<<"--------------------------------------------------------Landmark Building (all get can win)--------------------------------------------------------\n";
    std::cout<<"|| ~ railwayStation ~  ||  ~ shoppingCenter ~  ||      ~ amusementPark ~       ||   ~ radioStation ~   ||     ~ airport ~     ||    ~ harbor ~   ||\n";
    std::cout<<"||price: 4             ||price: 10             ||price: 16                     ||price: 22             ||price: 30            ||price: 2         ||\n";
    std::cout<<"||range: self          ||range: self           ||range: self                   ||range: self           ||range: self          ||range: self      ||\n";
    std::cout<<"||The player can choose||The player can add one||When two dice are rolled at   ||The current player can||If the dice player do||When the points r||\n";
    std::cout<<"||to toss one or two   ||money for each card   ||the same counts,The player can||choose toss the dice  ||es not build any buil||olled is greater ||\n";
    std::cout<<"||dice.                ||whose form is cup or  ||play again after completing   ||once again.           ||ding cards in this ro||than 10,you can c||\n";
    std::cout<<"||                     ||house.                ||the current game process.     ||                      ||und,add ten monry    ||hoose add 2      ||\n";
}