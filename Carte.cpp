#include "Carte.h"
std::ostream& operator<<(std::ostream& f,const Carte& c) {
    f << "(" << c.getName() << "," << c.getPrice() <<  "," << "," << c.getForm() << ","
      << c.getRange() << "," << c.getCount1() << "," << c.getCount2() << ")"  << ")" ;
    return f;
}

const std::string& Carte::getName() const {
    return name;
}

int Carte::getPrice() const {
    return price;
}

const std::string& Carte::getForm() const {
    return form;
}

const std::string& Carte::getRange() const {
    return range;
}

int Carte::getCount1() const {
    return count1;
}

int Carte::getCount2() const {
    return count2;
}
