#ifndef FONCTIONS_H_
#define FONCTIONS_H_
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h> 


typedef struct {
        
	
	char entree[100];
	SDL_Surface* text;
	TTF_Font *police;
	SDL_Rect pos;
	int score;
	
}score;







typedef struct
{

char d1[20],d2[50],d3[50];
SDL_Surface *t1,*t2,*t3;
SDL_Rect pos1,pos2,pos3;
 TTF_Font *p1,*p2 ;

}stat_joueur;




typedef struct
{
SDL_Surface *img_map;
SDL_Rect pos_map;
SDL_Surface *img_joueur;
SDL_Rect pos_joueur;
}minimap;


void affichertemp (Uint32 *temps,SDL_Surface *screen,TTF_Font *police);
void initmap(minimap *m); 
void afficherminimap(minimap m,SDL_Surface *screen); 
SDL_Rect MAJMinimap (SDL_Rect posJoueur,int redemensionement,SDL_Rect camera);
void afficherminimap (minimap m,SDL_Surface *screen);




void sauvegarder_joueur(int score,char nomjoueur[],char nomfichier[]);
void meilleur(char nomfichier[],int *score,char nomjoueur[]);
void init_statjoueur(stat_joueur *sj);
void afficher_meilleur(SDL_Surface *screen,stat_joueur *sj,int score ,char nomjoueur[]);
int saisir_nom(char nom[], SDL_Surface *screen);
int goodluck(char nom[], SDL_Surface *screen);


void initialiserScore(score *score );
void afficherscore(SDL_Surface *screen, score *score );
void liberer_score(score *s);
#endif
