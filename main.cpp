#include <iostream>
#include "Carte.h"
#include "Jeu.h"
#include "Jeueur.h"
#include "Controleur.h"
#include "BankCarte.h"

using namespace std;
int main() {
    Controleur con;
    con.is_Expansion();
    con.rearrange();
    con.process();
    //con.afficher_allCartes();

    return 0;
}
