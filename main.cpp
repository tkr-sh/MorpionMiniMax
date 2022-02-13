////////////////////////////////////
//                                //
//        MiniMax Morpion         //
//  Code Written by Axel DEREPAS  //
/////////////////////////////////////

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int MinMax(string tab[3][3], int depth, int Maximize, char camp){
    int resultat = 10 ,i ,j;
    int win[3][8] = {{0,0,0,2,6,2,1,3} , {1,4,3,4,7,5,4,4} , {2,8,6,6,8,8,7,5}};
    string victory[2] = {"O","X"};
    bool equality;


    // Si la partie est déjà finie
    for (j = 0;j < 2 ; j++ ){ // Pour les deux joueurs
        for (int i = 0; i < 8; i++){ //Victoire
            if (tab[win[0][i]/3][win[0][i]%3] == victory[j] && tab[win[1][i]/3][win[1][i]%3] == victory[j] && tab[win[2][i]/3][win[2][i]%3] == victory[j]){
                resultat = 2 * (std::string(1, camp) != victory[j]) - 1; // resultat = -1 si l'ordinateur perd et 1 s'il gagne
            }
        }
        equality = true;
        for (int i = 0; i < 9; i++){ //Egalité
            if (tab[i/3][i%3]=="-"){
                equality = false;
            }
        }
        if (equality){
            resultat = 0;
        }
    }
    
    if (resultat != 10){ // S'il y a déjà un gagnant ou une égalité, autant directement le retourner
        return resultat;
    }

    int best_score, score;
    if (Maximize){// Si l'on cherche à maximiser
        best_score = -2;
        for (i = 0; i <3; i++){
            for (j = 0; j < sizeof(tab[0])/sizeof(tab[0][0]); j++){
                if (tab[i][j] == "-"){
                    tab[i][j] =  (camp=='O')?'X':'O';
                    score = MinMax(tab, depth+1, false, camp);
                    tab[i][j] = "-";
                    best_score = max(best_score,score);

                }
            }
        }
    } else { // Si l'on cherche à minimiser
        best_score = 2;
        for (i = 0; i < 3; i++){
            for (j = 0; j < sizeof(tab[0])/sizeof(tab[0][0]); j++){
                if (tab[i][j] == "-"){
                    tab[i][j] = camp;
                    score = MinMax(tab, depth+1, true, camp);
                    tab[i][j] = "-";
                    best_score = min(best_score,score);

                }
            }
        }
    }

    return best_score;
}





int BestMove(string tab[3][3], char camp){
    int i = 0, j, score, best_score = -2;
    int move[2] = {0, 0};
    for (; i < 3; i++){
        for (j = 0; j < sizeof(tab[0])/sizeof(tab[0][0]); j++){
            if (tab[i][j] == "-"){
                tab[i][j] = (camp=='O')?'X':'O';
                score = MinMax(tab, 0, false, camp);
                tab[i][j] = "-";
                if (score > best_score){
                    best_score = score;
                    move[0] = i; move[1] = j;
                }
            }
        }
    }
    return move[0]+move[1]*3;
}




int main (){
    bool asking, equality, playing = true, tour = true; // tour == true <=> Joueur 1 && tour == false <=> Joueur 2
    int case_jouee;
    char camp = '-'; // 
    string xo;
    string tableau[3][3] = {{"-","-","-"},{"-","-","-"},{"-","-","-"}};
    int win[3][8] = {{0,0,0,2,6,2,1,3} , {1,4,3,4,7,5,4,4} , {2,8,6,6,8,8,7,5}}; // Positions de victoires

    cout << "Algorithme de MiniMax pour le jeu du Morpion en C++\n\n"; //Titre


    // Détermination de qui joue
    string choice;
    do {
        // Si la variable "choice" contient y ou n, alors la personne a fait son choix, sinon non.
        cout << "Voulez vous commencer à jouer ?[y/n]\n";
        cin >> choice;
        if (choice.find('y') != std::string::npos){
            cout << "Vous commencerez à jouer avec les pion X\n";
            camp = 'X';
        } else if (choice.find('n') != std::string::npos) {
            cout << "L'IA commencera à jouer avec les pion X. Vous allez jouer avec les pions O\n";
            camp = 'O';
        } else {
            cout << "Cette saisie n'est pas valide.\nMettez y pour Yes/Oui et n pour No/Non\n";
        }
    } while (camp=='-');



    // Boucle de jeu
    while (playing){
        xo = (tour)?"X":"O";


        // Si c'est à l'Humain de jouer
        if ((xo == "X" && camp == 'X') || (xo == "O" && camp == 'O')){
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
                cout <<  "\n(1)(2)(3)\n(4)(5)(6)\n(7)(8)(9)\nA votre tour ("<<xo<<"):\n>";
                cin >> case_jouee;

                if (0 > case_jouee || case_jouee > 10) { // Si la case est hors du tableau
                    cout << "Vous devez rentrez un nombre entre 1 et 9. Regardez le tableau numéré pour plus d'infos\n";
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
            cout << "\n-----------------------\n\n";

        } else { // Si c'est à l'IA de jouer
            int best_move = BestMove(tableau,camp);
            tableau[best_move%3][best_move/3] = (camp=='O')?'X':'O';
        }


        for (int i = 0; i < 8; i++){ //Victoire
            if (tableau[win[0][i]/3][win[0][i]%3] == xo && tableau[win[1][i]/3][win[1][i]%3] == xo && tableau[win[2][i]/3][win[2][i]%3] == xo){
                cout << "Le joueur "<< (2-tour) << " a gagné !\n";
                cout << "Tableau final:\n" ;
                for (int i = 0; i < 9; i++){
                    cout << "[" <<tableau[i/3][i%3] << "]";
                    if (i%3 == 2){
                        cout << "\n";
                    }
                }
                playing = false;
            }
        }
        equality = true;
        for (int i = 0; i < 9; i++){ //Egalité
            if (tableau[i/3][i%3] == "-"){
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
