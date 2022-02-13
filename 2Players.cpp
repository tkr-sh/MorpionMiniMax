////////////////////////////////////
//                                //
//        MiniMax Morpion         //
//  Code Written by Axel DEREPAS  //
/////////////////////////////////////
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main (){
    bool asking, equality, playing = true, tour = true; // tour == true <=> Joueur 1 && tour == false <=> Joueur 2
    int case_jouee;
    string xo;
    string tableau[3][3] = {{"-","-","-"},{"-","-","-"},{"-","-","-"}};
    int win[3][8] = {{0,0,0,2,6,2,1,3} , {1,4,3,4,7,5,4,4} , {2,8,6,6,8,8,7,5}}; // Positions de victoires

    cout << "Jeu du Morpion en C++\n"; //Titre

    while (playing){
        xo = (tour == true)?"X":"O";
        asking = true;
        do {
            // Print du tableau
            for (int i = 0; i < 9; i++){
                cout << "["<<tableau[i/3][i%3]<<"]";
                if (i%3==2){
                    cout << "\n";
                }
            }
            
            //Indiquation de la notation du tableau + Tour du joueur
            cout <<  "\n(1)(2)(3)\n(4)(5)(6)\n(7)(8)(9)\nTour du Joueur "<< 2-tour<<" ("<<xo<<"):\n>";
            cin >> case_jouee;

            if (0 > case_jouee || case_jouee > 10) { // Si la case est hors du tableau
                cout << "Vous devez rentrez un nombre entre 1 et 9. Regarcez le tableau numéré pour plus d'infos\n";
            }
            else if (tableau[(case_jouee-1)/3][(case_jouee-1)%3] != "-"){// Si la case séléctionné est déjà prise
                cout << "Cette case appartient déjà à un joueur. Merci d'en séléctrionner une autre\n";
            }
            else { //Sinon
                asking = false;
            }
        } while (asking);

        case_jouee--;
        tableau[case_jouee/3][case_jouee%3]=xo;

        for (int i = 0; i < 8; i++){ //Victoire
            if (tableau[win[0][i]/3][win[0][i]%3] == xo && tableau[win[1][i]/3][win[1][i]%3] == xo && tableau[win[2][i]/3][win[2][i]%3] == xo){
                cout << "Le joueur "<< (2-tour) << " a gagné !";
                playing = false;
            }
        }
        equality = true;
        for (int i = 0; i < 9; i++){ //Egalité
            if (tableau[i/3][i%3]=="-"){
                equality = false;
            }
        }
        if (equality){
            cout << "Egalité";
            playing = false;
        }

        //Changement de tour
        tour = !tour;
    }
}
