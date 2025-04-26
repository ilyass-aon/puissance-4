#include <stdio.h>
#include <stdlib.h>
#define NC 7
#define NL 6
#define EMPTY ' '
#define T 1
#define F 0

char m1='X',m2='O';
int g_id;

typedef struct
{
    int dg;
    int vert;
    int dd;
    int horz;
}Case ;

typedef struct element{
    int id;
    char name1[10];
    char name2[10];
    int score1,score2;
    int role;
    char grille[7][6];
    char m1;
    char m2;
} Element;

int P1(int player, char grille[NC][NL])
{
    int col=1;
    printf("- quelle colonne voulez vous JOUER?\n" );
    scanf("%d", &col);
    return col;

}
int IAF(int player, char grille[NC][NL])
{
    int col;
    col = (rand() % NC) + 1; // donne un nombre entre 1 et NC:
    return col;

}
int IAM(int player, char grille[NC][NL],int s, int nbcoups )
{   int col;
    if((nbcoups%2)==0){
     if(TCHOICE(grille, s)==T){
         col = s;
     }else{
     if(TCHOICE(grille, s+1 )==T){
       col=s+1;
     }else{
         if(TCHOICE(grille, s-1 )==T){
       col=s-1;
     }}}}
 if((nbcoups%2)!=0){
     if(TCHOICE(grille, s+1)==T){
         col = s+1;
     }else{
     if(TCHOICE(grille, s-1 )==T){
       col=s-1;
     }else{
         if(TCHOICE(grille, s)==T){
       col=s-1;
     }}}}}
int P2(int player, char grille[NC][NL])
{
    int col=1;
    printf("PLAYER: %s - quelle colonne voulez vous jouer?\n" , player == F ? "J2" : "J1");
    scanf("%d", &col);
    return col;

}
int TCHOICE(char grille[NC][NL], int colonne) // numero entre 0 et 6 indiquant la colonne jouée
{
    int y;
    int lignefree=-1; // contient le numero de ligne de la case qui est libre pour cette colonne, -1 si la colonne est pleine

    colonne -=1; // pour passer de 1..NC à 0..NC-1

    if (colonne < 0 || colonne >= NC)
    {
        return F; // si le numero de colonne est en dehors des bornes, le coup n'est pas valide
    }

    for ( y = NL-1; y >=0 ; y--)
    {
        if (grille[colonne][y] == EMPTY)
            lignefree = y;
    }

    if (lignefree== -1)
    {
        return F; // si la colonne est pleine, le coup n'est pas valide
    }
    return T;
}

void SHOWINITIALISE(char grille[NC][NL])
{
    int w, h;
    for(w = 0; w < NC; w++)
    {
        for(h = 0; h < NL; h++)
        {
            grille[w][h]=EMPTY; // on SHOWINITIALISEialise la tableau pour qu'il soit EMPTY au debut
        }
    }
}

void SHOW(char tableau[NC][NL])
{  int w, h;
    printf("|");
    for(w = 0; w < NC; w++)
        printf(" %d ", w+1);  // on affiche le numero de la colonne
    printf("|\n");

    printf("|");
    for(w = 0; w < NC; w++)
        printf("___", w+1); // une ligne 'souligné' pour dessiner le cadre
    printf("|\n");

    for(h = NL-1 ; h >= 0; h--) // on affiche la ligne du haut en haut et on descend pour avoir l'afficgage dans le bon sens
    {
        printf("|");
        for(w = 0; w< NC; w++)
        {
            printf(" %c ", tableau[w][h]);
        }
        printf("|\n");
    }
    printf("|");
    for(w = 0; w < NC; w++)
        printf("___", w+1); // une ligne 'souligné' pour dessiner le cadre
    printf("|\n");}

void SHOW3(char tableau[NC][NL])
{
// Affichage de la grille
int i,j;

printf("| 0 | 1 | 2 | 3 | 4 | 5 | 6 |\n");
printf("|---|---|---|---|---|---|---|\n");
for(i=0; i<NL; i++){
printf("|");
for(j=0; j<NC; j++){
printf(" %c |", tableau[j][i]);
}
printf("\n");
printf("|---|---|---|---|---|---|---|\n");
}
printf("| 0 | 1 | 2 | 3 | 4 | 5 | 6 |\n\n\n");
}




int VICTORYCHECK(char grille[NC][NL])
/*
    Principe:
    Additioner le contenu de la case adjacente correcte (->meme couleur)
    au contenu de la case courante.
*/

{
    Case game[NC][NL];
    int ligne, colonne;
    for ( ligne = 0; ligne < NL ; ligne++)
    {
        for ( colonne = 0; colonne < NC; colonne++)
        {
            /*
            Par defaut il y a 1 pion sur 4 d'aligner correctement
            */
            game[colonne][ligne].horz=1;
            game[colonne][ligne].vert=1;
            game[colonne][ligne].dg=1;
            game[colonne][ligne].dd=1;
        }
    }

    // pour le horizontal
    for ( ligne = 0; ligne < NL ; ligne++)
    {
        for ( colonne = 1; colonne < NC; colonne++)
        {
            if ((grille[colonne][ligne]==grille[colonne-1][ligne])&&(grille[colonne][ligne]!=EMPTY))
                // meme couleur
            {
                game[colonne][ligne].horz=game[colonne-1][ligne].horz+1;
                if (game[colonne][ligne].horz==4)
                    return T;
            }
        }
    }
    // pour le vertical
    for ( ligne = 1; ligne < NL ; ligne++)
    {
        for ( colonne = 0; colonne < NC; colonne++)
        {
            if ((grille[colonne][ligne]==grille[colonne][ligne-1])&&(grille[colonne][ligne]!=EMPTY))
                // meme couleur
            {
                game[colonne][ligne].vert=game[colonne][ligne-1].vert+1;
                if (game[colonne][ligne].vert==4)
                    return T;
            }
        }
    }
    // pour le diagonal gauche:de bas à gauche vers haut à droite
    for ( ligne = 1; ligne < NL ; ligne++)
    {
        for ( colonne = 0; colonne < NC-1; colonne++)
        {
            if ((grille[colonne][ligne]==grille[colonne+1][ligne-1])&&(grille[colonne][ligne]!=EMPTY))
                // meme couleur
            {
                game[colonne][ligne].dg=game[colonne+1][ligne-1].dg+1;
                if (game[colonne][ligne].dg==4)
                    return T;
            }
        }
    }
    // pour le diagonal droite:de haut à gauche vers bas à droite
    for ( ligne = 1; ligne < NL ; ligne++)
    {
        for ( colonne = 1; colonne < NC; colonne++)
        {
            if ((grille[colonne][ligne]==grille[colonne-1][ligne-1])&&(grille[colonne][ligne]!=EMPTY))
                // meme couleur
            {
                game[colonne][ligne].dd=game[colonne-1][ligne-1].dd+1;
                if (game[colonne][ligne].dd==4)
                    return T;
            }
        }
    }
    return F;
}


void PLAY(int player, char grille[NC][NL], int colonne ,char J1, char J2  )
/*
  colonne entre 1 et 7 inclus
*/
{
    int lignefree=-1; // contient le numero de ligne de la case qui est libre pour cette colonne, -1 si la colonne est pleine
    int y;
    colonne -=1;

    if (colonne < 0 || colonne >= NC)  // ne devrait pas arriver à ce stade si TCHOICE() a été appelé avant cette fonction
    {
        return ; // si le numero de colonne est en dehors des bornes, le coup n'est pas valide
    }

    for ( y = NL-1; y >=0 ; y--)
    {
        if (grille[colonne][y] == EMPTY)
            lignefree = y;
    }
    if (lignefree== -1) // ne devrait pas arriver a ce stade si TCHOICE() a été appelé avant cette fonction
    {
        return;
    }

    grille[colonne][lignefree]= (player == F) ? J2:J1;

}

int ASK4(int player, char grille[NC][NL],int s,int nbcoups)
{
    int col;
    printf("- A votre tour...\n" );
    switch (player)
    {
        case T:
            col = P1(player, grille);
            break;
        case F:
            col = IAM(player, grille,s,nbcoups);
            break;
    }

    return col;
}
int ASK(int player, char grille[NC][NL])
{
    int col;
    printf("- A votre tour...\n" );
    switch (player)
    {
        case T:
            col = P1(player, grille);
            break;
        case F:
            col = IAF(player, grille);
            break;
    }

    return col;
}
 int ASK2(int player, char grille[NC][NL])
{
    int col;
    printf("PLAYER: %s - A votre tour...\n" , player == F ? "J2" : "J1");

    switch (player)
    {
        case T:
            col = P1(player, grille);
            break;
        case F:
            col = P2(player, grille);
            break;
    }

    return col;
}

void IDGEN(){
    FILE *f = fopen("HISTORY.txt","r");
    if(f){
        Element el;
            while(HISTORYREAD(f,&el)!=EOF){}
            g_id = el.id+1;
    }else{
        g_id = 1;
    }
    fflush(f);
    fclose(f);
}

char *FILENAMEGEN(int id){

        char *nomFichier = malloc(20*sizeof(char));
        char ext[] = ".txt";
        itoa(id,nomFichier,10);
        strcat(nomFichier,ext);
        return nomFichier;


}

void PARTYSAVE(int id,char name1[10],char name2[10],int score1,int score2,int role,char grille[7][6]){
    char *nom = FILENAMEGEN(id);
    FILE* fichier = fopen(nom, "a+");
    fprintf(fichier, "%d %s %d %d %s %d %c %c ",id,name1,score1,score2,name2,role,m1,m2);
    for(int i=0;i<6;i++){
            for(int j=0;j<7;j++){
                fprintf(fichier, "%c", grille[j][i]);
            }
    }
    fprintf(fichier, "\n");
    fflush(fichier);
    fclose(fichier);
}

void HISTORYSAVE(int id,char name1[10],char name2[10],int score1,int score2){
    FILE* fichierHistorique = fopen("HISTORY.txt", "a+");
    fprintf(fichierHistorique, "%d %s %d %d %s\n",id,name1,score1,score2,name2);

    fflush(fichierHistorique);
    fclose(fichierHistorique);
}

void LASTPARTYSAVE(int id,char name1[10],char name2[10],int score1,int score2,int role,char grille[7][6]){
    FILE* fichier = fopen("PLAYEDPARTY.txt", "a+");
    fprintf(fichier, "%d %s %d %d %s %d %c %c ",id,name1,score1,score2,name2,role,m1,m2);
    for(int i=0;i<6;i++){
            for(int j=0;j<7;j++){
                fprintf(fichier, "%c", grille[j][i]);
            }
    }
    fprintf(fichier, "\n");
    fflush(fichier);
    fclose(fichier);
}

int HISTORYREAD(FILE* fichier, Element* el){
  return fscanf(fichier, "%d %s %d %d %s\n",&(el->id),el->name1,&(el->score1),&(el->score2),el->name2);

}

int PARTYREAD(FILE* fichier, Element* el){
  fscanf(fichier, "%d %s %d %d %s %d %c %c ",&(el->id),el->name1,&(el->score1),&(el->score2),el->name2,&(el->role),&(el->m1),&(el->m2));
  for(int i=0;i<6;i++){
            for(int j=0;j<7;j++){
                if(i==5 && j==6)  return fscanf(fichier, "%c\n", &(el->grille[j][i]));
           else  fscanf(fichier, "%c", &(el->grille[j][i]));
            }
    }
}

void HISTORYPRINT(){
    Element el;
    FILE *fichier = fopen("HISTORY.txt","r");
     fseek(fichier,0,SEEK_SET);

    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf(" ---------------------------                       \n");
    printf("|        HISTORIQUE         |                       \n");
    printf(" ---------------------------                        \n");
        while(HISTORYREAD(fichier,&el)!=EOF){
            printf("%d %s %d - %d %s\n",el.id,el.name1,el.score1,el.score2,el.name2);
        }
         fclose(fichier);
}

void READANDSHOWONETOUR(){
    FILE *fichier = fopen("1.txt","r");
    fseek(fichier,0,SEEK_SET);
    Element el;
    PARTYREAD(fichier,&el);


    SHOW(el.grille);

    fclose(fichier);
}

void OBSERVE(int id){
    char *nom = FILENAMEGEN(id);

    FILE *f = fopen(nom,"r");
    fseek(f,0,SEEK_SET);
    Element el;

    while(PARTYREAD(f,&el)!=EOF){
    printf("APPUYER SUR UNE TOUCHE\n");
        getch();
        system("cls");
        SHOW(el.grille);

    }


    fflush(f);
    fclose(f);
}


int main (int argc, char *argv[])
{

    int col;
    int s ;
    int GAMEOVER = F;
    int nbcoups = 0;
    char grille[NC][NL];
    int player = T;
    int c , d , e , f ,pp ,dd , svc1 ,svc2,hh ;
    int sc1 = 0;
    int sc2 = 0;
    char bb[5];
    char ss[5];


    printf("                             ---------------------------------------------------------- \n");
    printf("                            |                       PUISSANCE 4                        |   \n");
    printf("                             ---------------------------------------------------------- \n");
    printf("                             --------------------------MENU----------------------------\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                            |               PARTIE CONTRE PC TAPER 1                   |\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                            |              JOUER CONTRE UN AMI TAPER 2                 |\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                            |                  HISTORIQUE taper 3                      |\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                            |                CHARGER PARTIE taper 4                    |\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                            |                  AIDE DE JEU taper 5                     |\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                            |                    QUITTER taper 0                       |\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                             ----------------------------------------------------------                         \n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                            | realise par :       AIT OUHAMAN  ILYASS                   |\n");
    printf("                             -----------------------------------------------------------                         \n");
    scanf("%d",&c);
    system("cls");
    if (c == 1) {
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                             ----------------------------------------------------------                       \n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                            |        JOUER CONTRE Le PC ( NIVEAU FACILE ) TAPER 1       |\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                            |        JOUER CONTRE Le PC ( NIVEAU MOYEN )  TAPER 1       |\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                            |                   QUITTER TAPER 0                        |\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                             ----------------------------------------------------------                         \n");
    scanf("%d",&hh);
    system("cls");
    if(hh==1) {
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                             ----------------------------------------------------------                       \n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                            |        JOUER CONTRE Le PC ( MODE NORMALE ) TAPER 1        |\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                            |        JOUER CONTRE Le PC ( MODE INVERSE ) TAPER 2        |\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                            |                   QUITTER TAPER 0                        |\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                             ----------------------------------------------------------                         \n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                            | MODE NORMALE : LE JEU COMMENCE DE BAS DE GRILLE VERS HAUT |                       \n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                             ----------------------------------------------------------                         \n");
    printf("                            | MODE INVERSE : LE JEU COMMANCE DE HAUT DE GRILLE VERS BAS |                       \n");
    printf("                             ----------------------------------------------------------                         \n");
    scanf("%d",&d);
    system("cls");


     if ( d == 1){
    IDGEN();
    char name[10] ;
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                            |       TAPER LE NOM QUE VOUS VOULEZ UTILISER AU JEU        |                       \n");
    printf("                             -----------------------------------------------------------                         \n");
    scanf("%s",name);
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                            |     PLAYER 1 TAPER LE PION QUE VOUS VOULEZ UTILISER       |                       \n");
    printf("                             -----------------------------------------------------------                         \n");
    scanf("%s",bb);
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                            |     PLAYER 1 TAPER LE PION QUE VOUS VOULEZ POUR PC        |                       \n");
    printf("                             -----------------------------------------------------------                         \n");
    scanf("%s",ss);
    system("cls");
    m1 = bb[0];
    m2 = ss[0];

    SHOWINITIALISE(grille);
    SHOW(grille);


    while (!GAMEOVER)
    {
        do
        {
            col = ASK4(player, grille ,s ,nbcoups);
            s=col;

        }while(TCHOICE(grille, col)==F );
        // tant qu'il n'est pas possible de JOUER là, on reASK
        PLAY(player, grille, col ,m1, m2 );
        printf("PLAYER %s a PLAY:\n", player == F ? "IA" : name );
        system("cls");
        SHOW(grille);
        printf(" %s (%d-%d) IA\n", name ,sc1 , sc2 );
        nbcoups++;

        if (VICTORYCHECK(grille)==T)
        {

            printf("Victoire de %s au %dieme coups!", player == F ? "IA" : name , nbcoups );
            if( player == F){
                sc2++;
            }else {
            sc1++;}
            HISTORYSAVE(g_id,name,"IA",sc1,sc2);
            PARTYSAVE(g_id,name,"IA",sc1,sc2,player,grille);

            printf("Vouler vous JOUER une autre partie taper 1 sinon taper 2");
            scanf("%d",&pp);
            if(pp==1){
                SHOWINITIALISE(grille);
            }else{
                GAMEOVER = T;}




        }
        else if (nbcoups == NC*NL)
        {
            PARTYSAVE(g_id,name,"IA",sc1,sc2,player,grille);
            HISTORYSAVE(g_id,name,"IA",sc1,sc2);
            GAMEOVER = T;
            printf("Match NUL (%d coups)\n", nbcoups);
        }

        player = !player;

        // au PLAYER suivant de JOUER
        PARTYSAVE(g_id,name,"IA",sc1,sc2,player,grille);
        LASTPARTYSAVE(g_id,name,"IA",sc1,sc2,player,grille);


    }
    }
     if (d==2){
    IDGEN();
    char name[10] ;
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                            |       TAPER LE NOM QUE VOUS VOULEZ UTILISER AU JEU        |                       \n");
    printf("                             -----------------------------------------------------------                         \n");
    scanf("%s",name);
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                            |     PLAYER 1 TAPER LE PION QUE VOUS VOULEZ UTILISER       |                       \n");
    printf("                             -----------------------------------------------------------                         \n");
    scanf("%s",bb);
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                            |     PLAYER 1 TAPER LE PION QUE VOUS VOULEZ POUR PC        |                       \n");
    printf("                             -----------------------------------------------------------                         \n");
    scanf("%s",ss);
    system("cls");
    m1 = bb[0];
    m2 = ss[0];


    SHOWINITIALISE(grille);
    SHOW3(grille);


    while (!GAMEOVER)
    {
        do
        {
            col = ASK(player, grille);
            s=col;

        }while(TCHOICE(grille, col)==F );
        // tant qu'il n'est pas possible de JOUER là, on reASK
        PLAY(player, grille, col ,m1, m2 );
        printf("PLAYER %s a PLAY:\n", player == F ? "IA" : name );
        system("cls");
        SHOW3(grille);
        printf(" %s (%d-%d) IA\n", name ,sc1 , sc2 );
        nbcoups++;

        if (VICTORYCHECK(grille)==T)
        {

            printf("Victoire de %s au %dieme coups!", player == F ? "IA" : name , nbcoups );
            if( player == F){
                sc2++;
            }else {
            sc1++;}
            HISTORYSAVE(g_id,name,"IA",sc1,sc2);
            PARTYSAVE(g_id,name,"IA",sc1,sc2,player,grille);

            printf("Vouler vous JOUER une autre partie taper 1 sinon taper 2");
            scanf("%d",&pp);
            if(pp==1){
                SHOWINITIALISE(grille);
            }else{
                GAMEOVER = T;}




        }
        else if (nbcoups == NC*NL)
        {
            PARTYSAVE(g_id,name,"IA",sc1,sc2,player,grille);
            HISTORYSAVE(g_id,name,"IA",sc1,sc2);
            GAMEOVER = T;
            printf("Match NUL (%d coups)\n", nbcoups);
        }

        player = !player;

        // au PLAYER suivant de JOUER
        PARTYSAVE(g_id,name,"IA",sc1,sc2,player,grille);
        LASTPARTYSAVE(g_id,name,"IA",sc1,sc2,player,grille);


    }


     } }else if (hh==2) {
     printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                             ----------------------------------------------------------                       \n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                            |        JOUER CONTRE Le PC ( MODE NORMALE ) TAPER 1        |\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                            |        JOUER CONTRE Le PC ( MODE INVERSE ) TAPER 2        |\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                            |                   QUITTER TAPER 0                        |\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                             ---------------------------------------------------------- \n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                            | MODE NORMALE : LE JEU COMMENCE DE BAS DE GRILLE VERS HAUT |                       \n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                             ----------------------------------------------------------                         \n");
    printf("                            | MODE INVERSE : LE JEU COMMANCE DE HAUT DE GRILLE VERS BAS |                       \n");
    printf("                             ---------------------------------------------------------- \n");
    scanf("%d",&d);
    system("cls");


     if ( d == 1){
    IDGEN();
    char name[10] ;
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                            |       TAPER LE NOM QUE VOUS VOULEZ UTILISER AU JEU        |                       \n");
    printf("                             -----------------------------------------------------------                         \n");
    scanf("%s",name);
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                            |     PLAYER 1 TAPER LE PION QUE VOUS VOULEZ UTILISER       |                       \n");
    printf("                             -----------------------------------------------------------                         \n");
    scanf("%s",bb);
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                            |     PLAYER 1 TAPER LE PION QUE VOUS VOULEZ POUR PC        |                       \n");
    printf("                             -----------------------------------------------------------                         \n");
    scanf("%s",ss);
    system("cls");
    m1 = bb[0];
    m2 = ss[0];


    SHOWINITIALISE(grille);
    SHOW(grille);


    while (!GAMEOVER)
    {
        do
        {
            col = ASK4(player, grille ,s ,nbcoups);
            s=col;

        }while(TCHOICE(grille, col)==F );
        // tant qu'il n'est pas possible de JOUER là, on reASK
        PLAY(player, grille, col ,m1, m2 );
        printf("PLAYER %s a PLAY:\n", player == F ? "IA" : name );
        system("cls");
        SHOW(grille);
        printf(" %s (%d-%d) IA\n", name ,sc1 , sc2 );
        nbcoups++;

        if (VICTORYCHECK(grille)==T)
        {

            printf("Victoire de %s au %dieme coups!", player == F ? "IA" : name , nbcoups );
            if( player == F){
                sc2++;
            }else {
            sc1++;}
            HISTORYSAVE(g_id,name,"IA",sc1,sc2);
            PARTYSAVE(g_id,name,"IA",sc1,sc2,player,grille);

            printf("Vouler vous JOUER une autre partie taper 1 sinon taper 2");
            scanf("%d",&pp);
            if(pp==1){
                SHOWINITIALISE(grille);
            }else{
                GAMEOVER = T;}




        }
        else if (nbcoups == NC*NL)
        {
            PARTYSAVE(g_id,name,"IA",sc1,sc2,player,grille);
            HISTORYSAVE(g_id,name,"IA",sc1,sc2);
            GAMEOVER = T;
            printf("Match NUL (%d coups)\n", nbcoups);
        }

        player = !player;

        // au PLAYER suivant de JOUER
        PARTYSAVE(g_id,name,"IA",sc1,sc2,player,grille);
        LASTPARTYSAVE(g_id,name,"IA",sc1,sc2,player,grille);


    }
    }
     if (d==2){
    IDGEN();
    char name[10] ;
printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                            |       TAPER LE NOM QUE VOUS VOULEZ UTILISER AU JEU        |                       \n");
    printf("                             -----------------------------------------------------------                         \n");
    scanf("%s",name);
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                            |     PLAYER 1 TAPER LE PION QUE VOUS VOULEZ UTILISER       |                       \n");
    printf("                             -----------------------------------------------------------                         \n");
    scanf("%s",bb);
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                            |     PLAYER 1 TAPER LE PION QUE VOUS VOULEZ POUR PC        |                       \n");
    printf("                             -----------------------------------------------------------                         \n");
    scanf("%s",ss);
    system("cls");
    m1 = bb[0];
    m2 = ss[0];


    SHOWINITIALISE(grille);
    SHOW3(grille);


    while (!GAMEOVER)
    {
        do
        {
            col = ASK4(player, grille ,s ,nbcoups);
            s=col;

        }while(TCHOICE(grille, col)==F );
        // tant qu'il n'est pas possible de JOUER là, on reASK
        PLAY(player, grille, col ,m1, m2 );
        printf("PLAYER %s a PLAY:\n", player == F ? "IA" : name );
        system("cls");
        SHOW3(grille);
        printf(" %s (%d-%d) IA\n", name ,sc1 , sc2 );
        nbcoups++;

        if (VICTORYCHECK(grille)==T)
        {

            printf("Victoire de %s au %dieme coups!", player == F ? "IA" : name , nbcoups );
            if( player == F){
                sc2++;
            }else {
            sc1++;}
            HISTORYSAVE(g_id,name,"IA",sc1,sc2);
            PARTYSAVE(g_id,name,"IA",sc1,sc2,player,grille);

            printf("Vouler vous JOUER une autre partie taper 1 sinon taper 2");
            scanf("%d",&pp);
            if(pp==1){
                SHOWINITIALISE(grille);
            }else{
                GAMEOVER = T;}




        }
        else if (nbcoups == NC*NL)
        {
            PARTYSAVE(g_id,name,"IA",sc1,sc2,player,grille);
            HISTORYSAVE(g_id,name,"IA",sc1,sc2);
            GAMEOVER = T;
            printf("Match NUL (%d coups)\n", nbcoups);
        }

        player = !player;

        // au PLAYER suivant de JOUER
        PARTYSAVE(g_id,name,"IA",sc1,sc2,player,grille);
        LASTPARTYSAVE(g_id,name,"IA",sc1,sc2,player,grille);


    }


     }}
      }else if ( c == 2) {

    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
  printf("                             ----------------------------------------------------------                       \n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                            |        JOUER CONTRE UN AMI ( MODE NORMALE ) TAPER 1      |\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                            |        JOUER CONTRE UN AMI ( MODE INVERSE ) TAPER 2      |\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                            |                   QUITTER TAPER 0                        |\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                            |                                                          |\n");
    printf("                             ---------------------------------------------------------- \n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                            | MODE NORMALE : LE JEU COMMENCE DE BAS DE GRILLE VERS HAUT |                       \n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                             ----------------------------------------------------------                         \n");
    printf("                            | MODE INVERSE : LE JEU COMMANCE DE HAUT DE GRILLE VERS BAS |                       \n");
    printf("                             ---------------------------------------------------------- \n");
    scanf("%d",&dd);
    system("cls");
    if (dd==1) {
    IDGEN();
    char name[10] ;
    char namee[10] ;
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                            |   PLAYER 1 TAPER LE NOM QUE VOUS VOULEZ UTILISER AU JEU   |                       \n");
    printf("                             -----------------------------------------------------------                         \n");
    scanf("%s",name);
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                            |   PLAYER 2 TAPER LE NOM QUE VOUS VOULEZ UTILISER AU JEU   |                       \n");
    printf("                             -----------------------------------------------------------                         \n");
    scanf("%s",&namee);
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                            |     PLAYER 1 TAPER LE PION QUE VOUS VOULEZ UTILISER       |                       \n");
    printf("                             -----------------------------------------------------------                         \n");
    scanf("%s",bb);
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                            |     PLAYER 2 TAPER LE PION QUE VOUS VOULEZ UTILISER       |                       \n");
    printf("                             -----------------------------------------------------------                         \n");
    scanf("%s",ss);
    system("cls");
    m1 = bb[0];
    m2 = ss[0];
    SHOWINITIALISE(grille);
    SHOW(grille);
    while (!GAMEOVER)
    {
        do
        {
            col = ASK2(player, grille);
            s=col;

        }while(TCHOICE(grille, col)==F );
        // tant qu'il n'est pas possible de JOUER là, on reASK
        PLAY(player, grille, col ,m1, m2 );
        printf("PLAYER %s a PLAY:\n", player == F ? namee : name );
        system("cls");
        SHOW(grille);
        printf(" %s (%d-%d) %s\n", name ,sc1 , sc2 , namee );
        nbcoups++;

        if (VICTORYCHECK(grille)==T)
        {

            printf("Victoire de %s au %dieme coups!", player == F ? namee : name , nbcoups );
            if( player == F){
                sc2++;
            }else {
            sc1++;}
            HISTORYSAVE(g_id,name,namee,sc1,sc2);
            PARTYSAVE(g_id,name,namee,sc1,sc2,player,grille);
            GAMEOVER = T;




        }
        else if (nbcoups == NC*NL)
        {
            PARTYSAVE(g_id,name,"IA",sc1,sc2,player,grille);
            HISTORYSAVE(g_id,name,"IA",sc1,sc2);
            GAMEOVER = T;
            printf("Match NUL (%d coups)\n", nbcoups);
        }

        player = !player;

        // au PLAYER suivant de JOUER
        PARTYSAVE(g_id,name,namee,sc1,sc2,player,grille);
        LASTPARTYSAVE(g_id,name,namee,sc1,sc2,player,grille);


    }



     }
        if (dd==2){
    IDGEN();
    char name[10] ;
    char namee[10] ;
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                            |   PLAYER 1 TAPER LE NOM QUE VOUS VOULEZ UTILISER AU JEU   |                       \n");
    printf("                             -----------------------------------------------------------                         \n");
    scanf("%s",name);
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                            |   PLAYER 2 TAPER LE NOM QUE VOUS VOULEZ UTILISER AU JEU   |                       \n");
    printf("                             -----------------------------------------------------------                         \n");
    scanf("%s",&namee);
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                            |     PLAYER 1 TAPER LE PION QUE VOUS VOULEZ UTILISER       |                       \n");
    printf("                             -----------------------------------------------------------                         \n");
    scanf("%s",bb);
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                             -----------------------------------------------------------                         \n");
    printf("                            |     PLAYER 2 TAPER LE PION QUE VOUS VOULEZ UTILISER       |                       \n");
    printf("                             -----------------------------------------------------------                         \n");
    scanf("%s",ss);
    system("cls");
    m1 = bb[0];
    m2 = ss[0];
    SHOWINITIALISE(grille);
    SHOW3(grille);
    while (!GAMEOVER)
    {
        do
        {
            col = ASK2(player, grille);
            s=col;

        }while(TCHOICE(grille, col)==F );
        // tant qu'il n'est pas possible de JOUER là, on reASK
        PLAY(player, grille, col ,m1, m2 );
        printf("PLAYER %s a PLAY:\n", player == F ? namee : name );
        system("cls");
        SHOW3(grille);
        printf(" %s (%d-%d) %s\n", name ,sc1 , sc2 , namee );
        nbcoups++;

        if (VICTORYCHECK(grille)==T)
        {

            printf("Victoire de %s au %dieme coups!", player == F ? namee : name , nbcoups );
            if( player == F){
                sc2++;
            }else {
            sc1++;}
            HISTORYSAVE(g_id,name,namee,sc1,sc2);
            PARTYSAVE(g_id,name,namee,sc1,sc2,player,grille);
            GAMEOVER = T;




        }
        else if (nbcoups == NC*NL)
        {
            PARTYSAVE(g_id,name,"IA",sc1,sc2,player,grille);
            HISTORYSAVE(g_id,name,"IA",sc1,sc2);
            GAMEOVER = T;
            printf("Match NUL (%d coups)\n", nbcoups);
        }

        player = !player;

        // au PLAYER suivant de JOUER
        PARTYSAVE(g_id,name,namee,sc1,sc2,player,grille);
        LASTPARTYSAVE(g_id,name,namee,sc1,sc2,player,grille);


    }






        }


       }
       else if ( c == 3) {
        int ch ;
           HISTORYPRINT();
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf(" -------------------------------------------------------------------------                        \n");
    printf("|        VEUILLEZ CHOISIR LA PARTIE QUE VOUS VOULEZ RE-VISUALISER         |                       \n");
    printf(" -------------------------------------------------------------------------                        \n");
    scanf("%d",&ch);
    system("cls");
           OBSERVE(ch);
       }
       else if ( c == 4) {
            Element el;
            FILE * f = fopen("PLAYEDPARTY.txt","r");
            fseek(f,0,SEEK_SET);
            while(PARTYREAD(f,&el)!=EOF){
            }
            ///we have all infos here
            player=el.role;
            printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                             -------------------------------------------------------------------------                        \n");
    printf("                            | VOULER VOUS CONTINUER LA PARTIE CONTRE IA (TAPER 1) OU UN AMI (TAPER 2) |                       \n");
    printf("                             -------------------------------------------------------------------------                        \n");
    scanf("%d",&svc1);
    system("cls");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("                 ----------------------------------------------------------------------------------------                        \n");
    printf("                | VOULER VOUS CONTINUER LA PARTIE EN MODE NORMALE (TAPER 1) OU EN MODE INVERSE (TAPER 2) |                       \n");
    printf("                 ----------------------------------------------------------------------------------------                        \n");
    scanf("%d",&svc2);
    system("cls");
            if (svc1==1){
                if (svc2==1) {

            SHOW(el.grille);

            while (!GAMEOVER){
        do{
            col = ASK(player, el.grille);
            s=col;

        }while(TCHOICE(el.grille, col)==F );
        // tant qu'il n'est pas possible de JOUER là, on reASK
        PLAY(player,el.grille,col,el.m1,el.m2 );
        printf("PLAYER %s a PLAY:\n", player == F ? "IA" : el.name1 );
        system("cls");
        SHOW(el.grille);
        printf(" %s (%d-%d) IA\n", el.name1 ,el.score1 ,el.score2 );
        nbcoups++;

        if (VICTORYCHECK(el.grille)==T)
        {

            printf("Victoire de %s", player == F ? "IA" : el.name1 );
            if( player == F){
                el.score2++;
            }else {
            el.score1++;}
            HISTORYSAVE(el.id,el.name1,"IA",el.score1,el.score2);
            PARTYSAVE(el.id,el.name1,"IA",el.score1,el.score2,player,el.grille);
            GAMEOVER = T;




        }
        else if (nbcoups == NC*NL)
        {
            PARTYSAVE(el.id,el.name1,"IA",el.score1,el.score2,player,el.grille);
            HISTORYSAVE(el.id,el.name1,"IA",el.score1,el.score2);
            GAMEOVER = T;
            printf("Match NUL \n");
        }

        player = !player;

        // au PLAYER suivant de JOUER
        PARTYSAVE(el.id,el.name1,"IA",el.score1,el.score2,player,el.grille);
        LASTPARTYSAVE(el.id,el.name1,"IA",el.score1,el.score2,player,el.grille);







       }

                }else if(svc2==2){

            SHOW3(el.grille);

            while (!GAMEOVER){
        do{
            col = ASK(player, el.grille);
            s=col;

        }while(TCHOICE(el.grille, col)==F );
        // tant qu'il n'est pas possible de JOUER là, on reASK
        PLAY(player,el.grille,col,el.m1,el.m2 );
        printf("PLAYER %s a PLAY:\n", player == F ? "IA" : el.name1 );
        system("cls");
        SHOW3(el.grille);
        printf(" %s (%d-%d) IA\n", el.name1 ,el.score1 ,el.score2 );
        nbcoups++;

        if (VICTORYCHECK(el.grille)==T)
        {

            printf("Victoire de %s", player == F ? "IA" : el.name1 );
            if( player == F){
                el.score2++;
            }else {
            el.score1++;}
            HISTORYSAVE(el.id,el.name1,"IA",el.score1,el.score2);
            PARTYSAVE(el.id,el.name1,"IA",el.score1,el.score2,player,el.grille);
            GAMEOVER = T;




        }
        else if (nbcoups == NC*NL)
        {
            PARTYSAVE(el.id,el.name1,"IA",el.score1,el.score2,player,el.grille);
            HISTORYSAVE(el.id,el.name1,"IA",el.score1,el.score2);
            GAMEOVER = T;
            printf("Match NUL \n");
        }

        player = !player;

        // au PLAYER suivant de JOUER
        PARTYSAVE(el.id,el.name1,"IA",el.score1,el.score2,player,el.grille);
        LASTPARTYSAVE(el.id,el.name1,"IA",el.score1,el.score2,player,el.grille);







       }
                }
            }else if (svc1==2){


            if (svc2==1) {

            SHOW(el.grille);

            while (!GAMEOVER){
        do{
            col = ASK2(player, el.grille);
            s=col;

        }while(TCHOICE(el.grille, col)==F );
        // tant qu'il n'est pas possible de JOUER là, on reASK
        PLAY(player,el.grille,col,el.m1,el.m2 );
        printf("PLAYER %s a PLAY:\n", player == F ? "IA" : el.name1 );
        system("cls");
        SHOW(el.grille);
        printf(" %s (%d-%d) IA\n", el.name1 ,el.score1 ,el.score2 );
        nbcoups++;

        if (VICTORYCHECK(el.grille)==T)
        {

            printf("Victoire de %s", player == F ? "IA" : el.name1 );
            if( player == F){
                el.score2++;
            }else {
            el.score1++;}
            HISTORYSAVE(el.id,el.name1,"IA",el.score1,el.score2);
            PARTYSAVE(el.id,el.name1,"IA",el.score1,el.score2,player,el.grille);
            GAMEOVER = T;




        }
        else if (nbcoups == NC*NL)
        {
            PARTYSAVE(el.id,el.name1,"IA",el.score1,el.score2,player,el.grille);
            HISTORYSAVE(el.id,el.name1,"IA",el.score1,el.score2);
            GAMEOVER = T;
            printf("Match NUL \n");
        }

        player = !player;

        // au PLAYER suivant de JOUER
        PARTYSAVE(el.id,el.name1,"IA",el.score1,el.score2,player,el.grille);
        LASTPARTYSAVE(el.id,el.name1,"IA",el.score1,el.score2,player,el.grille);







       }

                }else if(svc2==2){

            SHOW3(el.grille);

            while (!GAMEOVER){
        do{
            col = ASK2(player, el.grille);
            s=col;

        }while(TCHOICE(el.grille, col)==F );
        // tant qu'il n'est pas possible de JOUER là, on reASK
        PLAY(player,el.grille,col,el.m1,el.m2 );
        printf("PLAYER %s a PLAY:\n", player == F ? "IA" : el.name1 );
        system("cls");
        SHOW3(el.grille);
        printf(" %s (%d-%d) IA\n", el.name1 ,el.score1 ,el.score2 );
        nbcoups++;

        if (VICTORYCHECK(el.grille)==T)
        {

            printf("Victoire de %s", player == F ? "IA" : el.name1 );
            if( player == F){
                el.score2++;
            }else {
            el.score1++;}
            HISTORYSAVE(el.id,el.name1,"IA",el.score1,el.score2);
            PARTYSAVE(el.id,el.name1,"IA",el.score1,el.score2,player,el.grille);
            GAMEOVER = T;




        }
        else if (nbcoups == NC*NL)
        {
            PARTYSAVE(el.id,el.name1,"IA",el.score1,el.score2,player,el.grille);
            HISTORYSAVE(el.id,el.name1,"IA",el.score1,el.score2);
            GAMEOVER = T;
            printf("Match NUL \n");
        }

        player = !player;

        // au PLAYER suivant de JOUER
        PARTYSAVE(el.id,el.name1,"IA",el.score1,el.score2,player,el.grille);
        LASTPARTYSAVE(el.id,el.name1,"IA",el.score1,el.score2,player,el.grille);







       }
                }
            }

  }
  if (c==5){
    printf("\n");
    printf("                     L'aide de jeu sera sous forme d'un guide des instructions , \n");
    printf("\n");
    printf("                     pour passer d'une a l'autre il faut cliquer a n'importe quelle touche au clavier. \n");
    printf("\n");
    printf("                     Alors en commence , (cliquer sur une touche au clavier)    \n");
    getch();
    printf("\n");
    printf("                     1.    D'abord on choisi l'adversaire de jeu (contre un ami ou contre IA) \n");
    getch();
    printf("\n");
    printf("                     1.2    Si on a choisi l'IA comme adversaire , il faut choisir aussi le niveau (facile ou moyen) \n");
    getch();
    printf("\n");
    printf("                     2.    Puis on choisi le mode de jeu (grille normale ou inverse) \n");
    getch();
    printf("\n");
    printf("Example de grille normale :\n");
    printf("\n");
    SHOWINITIALISE(grille);
    grille[0][0]='X';
    grille[0][1]='0';
    grille[0][2]='X';
    grille[1][0]='0';
    grille[2][0]='X';
    grille[2][1]='0';
    grille[2][2]='X';
    grille[3][0]='0';
    SHOW(grille);
    getch();
    printf("Example de grille inverse :\n");
    printf("\n");
    SHOW3(grille);
    getch();
    printf("\n");
    printf("                      3.    Puis on tape (nos ou notre) nom(s) pour la partie   \n");
    getch();
    printf("\n");
    printf("                      4.    Puis on choisi les pions   \n");
    getch();
    printf("\n");
    printf("                      5.    Le PLAYER qui commence met un premier pion dans l'une des colonnes de son choix   \n");
    printf("\n");
    printf("                            puis l'autre fais la meme chose jusqu'on arrive a aligner 4 pions (verticale ou horizontale\n");
    printf("\n");
    printf("                            ou digonale ) sinon le partie sera nulle \n");
    getch();
    printf("\n");
    printf("                      00.   Toute partie termine par victoire ou nulle sera lister en historique , sinon il pourra etre \n");
    printf("\n");
    printf("                            charge ulterieurement pour la terminer ");
    printf("\n");
    getch();
    printf("\n");
    printf("                      00.   Enfin , on vous souhaite de bon temps en jouant notre puissance 4\n");

  }
    return 0;
}
