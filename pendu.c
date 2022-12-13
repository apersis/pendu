//gcc -o main pendu.c -lm

#ifndef COULEURS
#define COULEURS

#define clrscr() printf("\033[H\033[2J")
#define couleur(param) printf("\033[%sm",param)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

char lettre;
char nom_joueur[30]; /* */
int deja_utilise=0;
int avancement_lettres_tentes=0;
int tentative=0; // 0 = pas trouvé, 1 = trouvé
int compteur_tentative=0;
int finJeu=0; // 0 = jeu en cours, 1 = perdu, 2 = gagné 
char *mot;
int taille_mot=0;
char a_deviner[50]; // tableau de caractere du mot
char avancement[50]; // tableau avec les "_"
char lettres_tentes[26]; // tableau des lettres de l'alphabet tentés
char chaine[10000] = "";
int alea;
int scrabble[26];
int resultat[5];
int boucleJeu=1;

void demandeLettre();
int initTab();
void initScrabble();
int dessinPendu();
int verrifFinJeu();
void jeu();
void viderBuffer();
char *initWords();
void initClassement();
int score();
void triClassement();
void afficherClassement();
int demandeRejouer();
int verrifLettre();

struct partie
{
	int score;
	char nom[50];
	int erreur;
};

struct partie repertoire[999];

int main()
{
	while (boucleJeu==1)
	{
		int i=0;
		srand(time(NULL));
		alea=rand()%835;//choisi un mot aleatoire
		mot=initWords();
		taille_mot=strlen(mot)-1;
		compteur_tentative=0;
		avancement_lettres_tentes=0;
		initTab();
		initScrabble();
		printf("Entrez votre nom : ");
		scanf("%29s", nom_joueur);
		finJeu=0;
		while (finJeu==0)
		{
			jeu();
			verrifFinJeu();
		}
		if (finJeu==1)
			printf("Defaite\nLe mot était : %s\n",mot);
		if (finJeu==2)
			printf("Victoire, felicitation %s, votre score est de %d\n",nom_joueur,score());
		initClassement();
		afficherClassement();
		boucleJeu=demandeRejouer();
	}
}

int initTab() //initialise les 4 tableau
{
	int i,j;
	for (i=0;i<taille_mot;i++)
	{
		a_deviner[i]=mot[i];  // tableau du mot a deviner
		avancement[i]='_'; // tableau de l'avancement (commence avec que des underscore)
	}
	for (i=0;i<26;i++)
	{
		lettres_tentes[i]='!'; // tableau de toutes les lettres tentés (commence avec que des points d'exclamation)
	}
	for (i=0;i<999;i++)
	{
		repertoire[i].nom[0]='\0';
	}
}

void jeu()
{
	int i;
	tentative=0;
	deja_utilise=0;
	lettre=0;
	demandeLettre(); //demande une lettre et verifie que s'en soit bien une
	deja_utilise=verrifLettre();//verifie que la lettre n'ait pas deja ete demandee
	if (deja_utilise==0) // si la lettre n'a pas deja ete demandee
	{
		lettres_tentes[avancement_lettres_tentes]=lettre; //ajoute la lettre au tableau des lettres deja demandes
		avancement_lettres_tentes++;
		for (i=0;i<taille_mot;i++)
		{
			if (lettre==a_deviner[i])
			{
				avancement[i]=lettre;
				tentative=1;
			}
			printf("%c",avancement[i]);
		}
		printf("\n\n");
		if (tentative==0)// la lettre n'est pas dedans
		{
			compteur_tentative=compteur_tentative+1;
			dessinPendu();
		}
	}
}

void demandeLettre()
{
	while (lettre<97 || lettre>122) // si le caractere est une lettre minuscule
	{
		viderBuffer();
		printf("Entrez une lettre minuscule : ");
		lettre=getchar();
	}
}

int verrifLettre()
{
	int i;
	for (i=0;i<26;i++) // verrif de si la lettre a deja été demandé
	{
		if (lettre==lettres_tentes[i])
		{
			printf("Vous avez deja demandé cette lettre\a\n");
			return(1);
		}
	}
	return(0);
}

int verrifFinJeu()
{
	int i;
	int victoire=0; // en fin de boucle, 0 = gagné, 1 = encore en jeu
	if (compteur_tentative==8) // si le nombre d'echecs est egale a 8, le jeu est perdu
		finJeu=1;
	for (i=0;i<taille_mot;i++)// si le tableau d'avancement n'a pas d'underscore, le jeu est gagné
		if (avancement[i]=='_')
			victoire=1;
	if (victoire==0)
		finJeu=2;
}

int dessinPendu()
{
	if (compteur_tentative==2)
		printf("  --------------\n    |       |\n    |       |\n    |\n    |\n    |\n    |\n    |\n    |\n   /|\\ \n  / | \\ \n /  |  \\ \n~~~~~~~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~~~~~~~\n");
	if (compteur_tentative==1)
		printf("  --------------\n    |\n    |\n    |\n    |\n    |\n    |\n    |\n    |\n   /|\\ \n  / | \\ \n /  |  \\ \n~~~~~~~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~~~~~~~\n");
	if (compteur_tentative==3)
		printf("  --------------\n    |       |\n    |       |\n    |      / \\\n    |      \\_/\n    |\n    |\n    |\n    |\n   /|\\ \n  / | \\ \n /  |  \\ \n~~~~~~~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~~~~~~~\n");
	if (compteur_tentative==4)
		printf("  --------------\n    |       |\n    |       |\n    |      / \\\n    |      \\_/\n    |       |\n    |       |\n    |       |\n    |\n   /|\\ \n  / | \\ \n /  |  \\ \n~~~~~~~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~~~~~~~\n");
	if (compteur_tentative==5)
		printf("  --------------\n    |       |\n    |       |\n    |      / \\\n    |      \\_/\n    |       |\n    |       |__\n    |       |\n    |\n   /|\\ \n  / | \\ \n /  |  \\ \n~~~~~~~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~~~~~~~\n");
	if (compteur_tentative==6)
		printf("  --------------\n    |       |\n    |       |\n    |      / \\\n    |      \\_/\n    |       |\n    |     __|__\n    |       |\n    |\n   /|\\ \n  / | \\ \n /  |  \\ \n~~~~~~~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~~~~~~~\n");
	if (compteur_tentative==8)
		printf("  --------------\n    |       |\n    |       |\n    |      / \\\n    |      \\_/\n    |       |\n    |     __|__\n    |       |\n    |      / \\\n   /|\\    /   \\ \n  / | \\ \n /  |  \\ \n~~~~~~~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~~~~~~~\n");
	if (compteur_tentative==7)
		printf("  --------------\n    |       |\n    |       |\n    |      / \\\n    |      \\_/\n    |       |\n    |     __|__\n    |       |\n    |      / \n   /|\\    /    \n  / | \\ \n /  |  \\ \n~~~~~~~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~~~~~~~\n~~~~~~~~~~~~~~~~~~~~~\n");
	printf("Vous êtes à %d echec(s), il vous reste %d essais\n\n",compteur_tentative,8-compteur_tentative);
}

void viderBuffer()
{
	int c=0;
	while (c != '\n' && c != EOF)
		c=getchar();
}

char *initWords()//va chercher un mot aleatoire dans le fichier words.txt
{
	int i;
    FILE *words = NULL;

    words = fopen("words.txt", "r");

    if (words != NULL)
    {
		for (i=0;i<alea;i++)
			fgets(chaine, 10000, words);
        return(chaine);
    }
}

void initClassement() //initialise et affiche le classement + ajoute le score de chaques parties dans le fichier
{
	char afficheClassement[50]="";
	FILE *classement = NULL;
	char *tab[9];
	int i=0;
	int j;
	int ligne;
	
	classement = fopen("classement.csv","a+");
	
	
	if (classement != NULL)
	{
		fprintf(classement,"%d,%s,%d\n",score(),nom_joueur,compteur_tentative);
		fclose(classement);
	}
}

void afficherClassement() // affiche le classement en fin de partie
{
	char afficheClassement[100];
	char *chaine;
	FILE *classement;
	int i=0;
	int j;

	classement = fopen("classement.csv","r");
	

	if (classement != NULL)
	{
		fgets(afficheClassement,10000,classement);
		while( ! feof(classement))
		{
			chaine=fgets(afficheClassement,10000,classement);
			if (chaine != NULL) // reccupere toutes les lignes du fichier classement, et le met dans ma le tableau de ma structure
			{
				repertoire[i].score = atoi(strtok(chaine,","));
				char *p = strtok(NULL, ",");
				for (j=0;j<strlen(p)+1;j++)
				{
					if (j<strlen(p))
						repertoire[i].nom[j] = p[j];
					else
						repertoire[i].nom[j] = '\0';
				}
				repertoire[i].erreur = atoi(strtok(NULL,"\n"));
			}
			i++;
		}
		triClassement(); //trier tout le tableau
		j=0;
		printf("Classement :\n");
		for (i=0;i<10;i++)
		{
			if (repertoire[i].score==score()) // si le score de la partie actuel se retrouve dans le classement
			{
				couleur("01");
				if (repertoire[i+1].score==score())
					couleur("0");
			}
			printf("%d\t%s\n",repertoire[i].score,repertoire[i].nom);
			couleur("0");
		}
		printf("\n");
		fclose(classement);
	}
}
void triClassement() //tri par selection dans l'ordre decrossant
{  
  int i, j, k, tmp, index;
  char temp[50];
  for (i=0; i < (999-1); i++)
  {
    index = i;
    for (j=i + 1; j < 999; j++)
    {
      if (repertoire[index].score < repertoire[j].score)
        index = j;
    }
    if (index != i)
    {
      tmp = repertoire[i].score;
      repertoire[i].score = repertoire[index].score;
      repertoire[index].score = tmp;
	  for (k=0;k<strlen(repertoire[i].nom)+1;k++)
	  	if (k<strlen(repertoire[i].nom))
	  		temp[k] = repertoire[i].nom[k];
		else
			temp[k] = '\0';
	  for (k=0;k<strlen(repertoire[index].nom)+1;k++)
	  	if (k<strlen(repertoire[index].nom))
			repertoire[i].nom[k] = repertoire[index].nom[k];
		else
			repertoire[i].nom[k] = '\0';
	  for (k=0;k<strlen(temp)+1;k++)
	  	if (k<strlen(temp))
      		repertoire[index].nom[k] = temp[k];
		else
			repertoire[index].nom[k] = '\0';
	  tmp = repertoire[i].erreur;
      repertoire[i].erreur = repertoire[index].erreur;
      repertoire[index].erreur = tmp;
    }
  }
}

void initScrabble()
{
	scrabble[0]=scrabble[4]=scrabble[8]=scrabble[11]=scrabble[13]=scrabble[14]=scrabble[17]=scrabble[18]=scrabble[19]=scrabble[20]=1;
	scrabble[3]=scrabble[6]=scrabble[12]=2;
	scrabble[1]=scrabble[2]=scrabble[15]=3;
	scrabble[5]=scrabble[7]=scrabble[21]=4;
	scrabble[9]=scrabble[16]=8;
	scrabble[10]=scrabble[22]=scrabble[23]=scrabble[24]=scrabble[25]=10;
}

int score()
{
	int i=0;
	int scoreMot=0;
	for (i=0;i<taille_mot;i++)
		scoreMot=scoreMot+scrabble[(int)a_deviner[i]-97];
	return(scoreMot*(8-compteur_tentative));
}

int demandeRejouer()
{
	viderBuffer();
	char rep='a';
	while (rep!='o' && rep!='n')
	{
		printf("Voulez vous rejouer ? (o/n)\n");
		rep=getchar();
		viderBuffer();
	}
	if (rep=='o')
		return 1; //une partie est relancée
	if (rep=='n')
		return 0; //le programme se termine
}