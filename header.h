#define END_GAME 3 // STATO DI FINE GIOCO
#define YEL   "\x1B[33m" 
#define GRN   "\x1B[32m"
#define RESET "\x1B[0m"   // Costanti per i colori dei printf.
#define RED   "\x1B[31m"
#define TESTING_MODE 0 // Costante per il printf del campo in testing mode,(visulizzazione dei numeri delle carte per vedere quante volte mischia)

int field[40] = {1,2,3,4,5,6,7,8,9,10,
                 1,2,3,4,5,6,7,8,9,10,    // CAMPO DA GIOCO 0-39 CARTE
                 1,2,3,4,5,6,7,8,9,10,
                 1,2,3,4,5,6,7,8,9,10};

typedef struct giocatore{
    char *name;
    unsigned int point;             //Struttura per la gestione dei giocatori,nome_giocatore,puntenggio_giocatore,avversario per lo switch.
    unsigned short opponent;
}player;

player player1 = {"Giocatore1",0,2};
player player2 = {"Giocatore2",0,1};

player *ptr;  // puntantore per la gestione dei player

extern unsigned short ATT_PLAYER = 0;  // Variabile esterna per controllare il turno di ogni giocatore.


// Funzioni gestionali
void stampCamp(int[],int);
int getRandom(int,int);
int sameCard(int card1, int card2);
void mescola(int array[], int len);
void getPlayerName(player *ptr);
int getPlayerPoint(player *ptr);
void addPlayerPoint(player *ptr);
void getWinner(player *ptr1, player *ptr2);
void playGame(int player);
void scopriCarte(int card1, int card2);
int isEndGame(player *ptr1,player *ptr2);
void setName(char *player_name,player *ptr);
void testMode(int array[], int len);
// End Funzioni.