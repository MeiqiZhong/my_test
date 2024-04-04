#ifndef TESTPROECT_CARTE_H
#define TESTPROECT_CARTE_H
#include <vector>
#include <iostream>

class Carte {
private:
    std::string name;
    int price;
    std::string form;
    std::string range;
    int count1;
    int count2;
public:
    Carte(const std::string &name, int price, const std::string &form, const std::string &range, int count1,
          int count2) : name(name), price(price), form(form), range(range), count1(count1), count2(count2) {}
    ~Carte() = default;

    const std::string &getName() const;
    int getPrice() const;
    const std::string &getForm() const;
    const std::string &getRange() const;
    int getCount1() const;
    int getCount2() const;
};

std::ostream& operator<<(std::ostream& f,const Carte& c);

#endif //TESTPROECT_CARTE_H
