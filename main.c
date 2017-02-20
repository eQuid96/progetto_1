#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include <time.h>

int main(){
  int n;
  char *name1,*name2;
  srand((unsigned)time(NULL));
  printf("Benvenuto,scegli quante volte mischiare il mazzo di carte: ");
  scanf("%d",&n);
  printf("Hai deciso di mischiare il mazzo %d volte.\n",n);
  if (TESTING_MODE){
    printf("Campo da gioco non mischiato:\n");
    testMode(field,40);
    mescola(field,n);
    printf("-------------------------------\n");
    printf("Campo da gioco mischiato %d volte:\n",n);
    testMode(field,40);
  }
  mescola(field,n);
  printf("Giocatore1 scegli il tuo nome: ");
  scanf("%s",&name1);
  setName(&name1,&player1);
  printf("Giocatore2 scegli il tuo nome: ");
  scanf("%s",&name2);
  setName(&name2,&player2);
  printf("Viene scelto a caso il giocatore che inizierà a giocare . . .\n");
  ATT_PLAYER = getRandom(1,2);
  if(ATT_PLAYER == 2){
    getPlayerName(&player2);
    printf("Inizierà a giocare per primo\n");
  }else{
    getPlayerName(&player1);
    printf("Inizierà a giocare per primo\n");
  }
  stampCamp(field,40);
  playGame(ATT_PLAYER);
  return 0;
}

void stampCamp(int array[], int len){
  int i;
  for(i=0;i<len;i++){
    if (i == 9 || i == 19 || i == 29 || i == 39){
      if(array[i]!=0){
        printf(YEL" [] \n"RESET);
      }else{
        printf(GRN" ✔ \n"RESET);
      }
    }
    else if(array[i] == 0){
       printf(GRN" ✔ "RESET);
    }else{
      printf(YEL" [] "RESET);
    }
  }
}


void testMode(int array[], int len){
  int i;
  for(i=0;i<len;i++){
    if (i == 9 || i == 19 || i == 29 || i == 39){
      if(array[i]!=0){
        printf(YEL" %d \n"RESET,array[i]);
      }else{
        printf(GRN" ✔ \n"RESET);
      }
    }
    else if(array[i] == 0){
       printf(GRN" ✔ "RESET);
    }else{
      printf(YEL" %d "RESET,array[i]);
    }
  }
}

int sameCard(int card1, int card2){
  if(field[card1] != field[card2]){
    return 0;
  }else{
    return 1;
  }
}

void mescola(int array[], int len){
  int i,card1,card2,temp;
  for(i=0;i<len;i++){
    card1 = (int)getRandom(0,39);
    card2 = (int)getRandom(0,39);
    temp = array[card2];
    array[card2] = array[card1];
    array[card1] = temp;
   }
}

int getRandom(int a,int b){
  int i;
  i = (int) rand() % b + a;
  return i;
}

void getPlayerName(player *ptr){
  printf("[%s]: ",ptr->name);
}

int getPlayerPoint(player *ptr){
  return ptr->point;
}

void addPlayerPoint(player *ptr){
  int att_p = getPlayerPoint(ptr);
  ptr->point = ++att_p;
}

void setName(char *player_name,player *ptr){
  ptr->name = player_name;
}

void scopriCarte(int card1, int card2){
  field[card1] = 0;
  field[card2] = 0;
}

// Function per il controllo del vincitore
// Essendoci 40 carte, il massimo punteggio che si può ottenere è 20 punti
// Controllo quindi se la somma dei punteggi dei due giocatori è == 20.

int isEndGame(player *ptr1,player *ptr2){
  unsigned int sum;
  sum = (unsigned int)ptr1->point + ptr2->point;
  if (sum == 20){
    return 1; // Gioco completato.
  }else{
    return 0; // Gioco non ancora completato.
  }
}

void getWinner(player *ptr1, player *ptr2){
  int player1 = getPlayerPoint(ptr1);
  int player2 = getPlayerPoint(ptr2);
  if (player1 == player2){
    printf(GRN"[Info]: La partita è finita in Preggio! (%s:%d - %s:%d)\n"RESET,ptr1->name,player1,ptr2->name,player2);
    ATT_PLAYER = END_GAME;
    return;
  }
  if(player1>player2){
    printf("[Info]: La partita è finita!,Vince: %s! ("GRN"%s:%d"RESET" - %s:%d)\n",ptr1->name,ptr1->name,player1,ptr2->name,player2);
    ATT_PLAYER = END_GAME;
    return;
  }
  printf("[Info]: La partita è finita!,Vince: %s! ("GRN"%s:%d"RESET" - %s:%d)\n",ptr2->name,ptr2->name,player2,ptr1->name,player1);
  ATT_PLAYER = END_GAME;
  return;
}


void playGame(int player){
  int card1,card2,isSame,isEnd;
  
  // SWITCH DEL PUNTATORE DEL GIOCATORE
  if (player == 1) 
  {
    ptr = &player1;
  }
  else
  {
    ptr = &player2;
  }
   getPlayerName(ptr);
   printf("Scegli le carte da scoprire,inserici il numero delle carte(1,40): ");
   scanf("%d %d",&card1,&card2);
   card1--; 
   card2--; // decremento l'indice delle carte perchè l'array va da 0 a 39;
  
 // CONTROLLI PER LA SICUREZZA DEL GIOCO
   if (card1 == card2){
      printf(RED"[Info]: Non puoi scegliere la stessa carta.\n"RESET);
      playGame(ATT_PLAYER);
    }
    else if(field[card1] == 0 || field[card2] == 0){
     printf(RED"[Info] Non puoi scegliere carte già scoperte.\n"RESET);
     playGame(ATT_PLAYER);
    }
 // END
      isSame = sameCard(card1,card2);
      if(!isSame)
      {
        getPlayerName(ptr);
        printf(RED"Le carte non sono uguali tocca al prossimo giocatore..\n"RESET);
        ATT_PLAYER = ptr->opponent;
        playGame(ATT_PLAYER);
        return;
      }
      addPlayerPoint(ptr);
      printf(GRN"Le carte sono uguali!,hai guadagnato un punto. Punteggio Giocatore: %d\n"RESET,getPlayerPoint(ptr));
      scopriCarte(card1,card2);
      stampCamp(field,40);
      isEnd = isEndGame(&player1,&player2);
      if(!isEnd)
       {
         playGame(ATT_PLAYER);
       }else{
         getWinner(&player1,&player2);
       }
  return;
}
