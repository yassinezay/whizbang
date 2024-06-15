#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "minimap.h"
void initmap( minimap * m)
{
m->img_map=IMG_Load("minimap2.png");//minimap
m->img_joueur=IMG_Load("miniperso.png");

m->pos_map.x=0;
m->pos_map.y=0;
}
SDL_Rect MAJMinimap (SDL_Rect Posjoueur,int redemensionement,SDL_Rect camera)////////pos absoluee
{
SDL_Rect pos_joueur;
pos_joueur.x= ((camera.x +Posjoueur.x)*redemensionement)/100;
pos_joueur.y= 20+((camera.y +Posjoueur.y)*redemensionement)/100;
return pos_joueur;
}
void afficherminimap (minimap m,SDL_Surface *screen)
{

SDL_BlitSurface(m.img_map,NULL,screen,&m.pos_map);
SDL_BlitSurface(m.img_joueur,NULL,screen,&m.pos_joueur);
}
void affichertemp (Uint32 *temps,SDL_Surface *screen,TTF_Font *police)
{

SDL_Surface *chrono = NULL;
SDL_Rect positionChrono;
SDL_Color couleur = {255,255,255};
int min=0,sec=0;
char texteChrono [40] = "";
positionChrono.x = 840;
positionChrono.y = 10;
(*temps)=SDL_GetTicks();
(*temps)/=1000;
min=((*temps)/60);
sec=(*temps) - (60*min);


sprintf(texteChrono,"%02d:%02d",min,sec);
SDL_FreeSurface(chrono);
chrono = TTF_RenderText_Solid(police,texteChrono,couleur);
SDL_BlitSurface(chrono,NULL,screen,&positionChrono);
//}

}






void init_statjoueur(stat_joueur *sj)
{
strcpy(sj->d1,"BEST PLAYER : ");
strcpy(sj->d2,"");
strcpy(sj->d3,"");

sj->pos1.x=300;
   sj->pos1.y=200;

sj->pos2.x=200;
   sj->pos2.y=300;

sj->pos3.x=200;
   sj->pos3.y=350;
 sj->p1 = TTF_OpenFont("avocado.ttf", 30);
    
 sj->p2 = TTF_OpenFont("Ubuntu-Bold.ttf", 30);
 
}

void sauvegarder_joueur(int score,char nomjoueur[],char nomfichier[])
{


FILE *f=NULL;

f=fopen(nomfichier,"a");

fprintf(f,"%s   %d \n",nomjoueur,score);

fclose(f);

}


void meilleur(char nomfichier[],int *score,char nomjoueur[])
{
int s,sm=0;
char nom [50];

FILE *f=NULL;

f=fopen(nomfichier,"r");

while(!feof(f))
{

fscanf(f,"%s %d",nom,&s);


if (s>sm)
{
sm=s;
*score=s;
strcpy(nomjoueur,nom);

}
}
}


void afficher_meilleur(SDL_Surface *screen,stat_joueur *sj,int score ,char nomjoueur[])
{
SDL_Color rouge={255, 0,0},blue={0,0,255};

sprintf(sj->d2,"  NAME : %s  ",nomjoueur);

sprintf(sj->d3,"  SCORE : %d  ",score);

  sj->t1 = TTF_RenderText_Blended(sj->p1,sj->d1, blue);
sj->t2 = TTF_RenderText_Blended(sj->p2,sj->d2, blue);
sj->t3= TTF_RenderText_Blended(sj->p2,sj->d3, blue);

SDL_BlitSurface(sj->t1, NULL, screen, &(sj->pos1)); 
SDL_BlitSurface(sj->t2, NULL, screen, &(sj->pos2)); 
SDL_BlitSurface(sj->t3, NULL, screen, &(sj->pos3)); 

}

int saisir_nom(char nom[], SDL_Surface *screen)
{
char c[20];
 SDL_Event evnt;
int cnt=1,i=0;
SDL_Color rouge={255, 0,0},blue={0,0,255};
SDL_Surface *text,*t1;
SDL_Rect pos,p1;
 TTF_Font *police ,*pol1;
police = TTF_OpenFont("avocado.ttf", 90);
pol1= TTF_OpenFont("Ubuntu-Bold.ttf", 60);
pos.x=300;
pos.y=350;
p1.x=90;
p1.y=120;
strcpy(nom,"");


t1 = TTF_RenderText_Blended(pol1,"Please write your Name :", rouge);


while(cnt)
{


SDL_BlitSurface(t1, NULL, screen, &p1); 
while(SDL_PollEvent(&evnt))
	{

     switch(evnt.type)
    {
            case SDL_QUIT:
                cnt = 0;
        break ;

 case SDL_KEYDOWN:
                switch (evnt.key.keysym.sym)
                {
case SDLK_a:
c[i]='A';
i++;
break;
case SDLK_b:
c[i]='B';
i++;
break;
case SDLK_c:
c[i]='C';
i++;
break;
case SDLK_d:
c[i]='D';
i++;
break;
case SDLK_e:
c[i]='E';
i++;
break;
case SDLK_f:
c[i]='F';
i++;
break;
case SDLK_g:
c[i]='G';
i++;
break;
case SDLK_h:
c[i]='H';
i++;
break;
case SDLK_i:
c[i]='I';
i++;
break;
case SDLK_j:
c[i]='J';
i++;
break;
case SDLK_k:
c[i]='K';
i++;
break;
case SDLK_l:
c[i]='L';
i++;
break;
case SDLK_m:
c[i]='M';
i++;
break;
case SDLK_n:
c[i]='N';
i++;
break;
case SDLK_o:
c[i]='O';
i++;
break;
case SDLK_p:
c[i]='P';
i++;
break;
case SDLK_q:
c[i]='Q';
i++;
break;
case SDLK_r:
c[i]='R';
i++;
break;
case SDLK_s:
c[i]='S';
i++;
break;
case SDLK_t:
c[i]='T';
i++;
break;
case SDLK_u:
c[i]='U';
i++;
break;
case SDLK_v:
c[i]='V';
i++;
break;
case SDLK_w:
c[i]='W';
i++;
break;
case SDLK_x:
c[i]='X';
i++;
break;
case SDLK_y:
c[i]='Y';
i++;
break;
case SDLK_z:
c[i]='Z';
i++;
break;

case SDLK_RETURN:
cnt=0;
break;
case SDLK_SPACE:
c[i]=' ';
i++;
break;

}
c[i]='\0';

strcpy(nom,c);

text = TTF_RenderText_Blended(police,nom, blue);
SDL_BlitSurface(text, NULL, screen, &pos);





}
}

SDL_Flip(screen);
 

}


return cnt;
}

int goodluck(char nom[], SDL_Surface *screen)
{


char aux[40];
strcpy(aux,"");

 SDL_Event evnt;
int cnt=1;
SDL_Color rouge={255, 0,0};
SDL_Surface *text;
SDL_Rect pos;
 TTF_Font *police ;
police = TTF_OpenFont("avocado.ttf", 90);

pos.x=90;
pos.y=180;


sprintf(aux,"GOOD LUCK  %s ",nom);

text= TTF_RenderText_Blended(police,aux, rouge);


while(cnt)
{


SDL_BlitSurface(text, NULL, screen, &pos); 
while(SDL_PollEvent(&evnt))
	{

     switch(evnt.type)
    {
            case SDL_QUIT:
                cnt = 0;
        break ;  
case SDL_KEYDOWN:
                switch (evnt.key.keysym.sym)
                {
 case SDLK_RETURN:
                cnt = 0;
        break ; 
}
}
}
SDL_Flip(screen);
 
} 
return cnt;
}

void initialiserScore(  score *score )
{

	

	 score->text = NULL;
	strcpy( score->entree,"");
		score->pos.x=815;
	score->pos.y=70;
	(score->police) = TTF_OpenFont("avocado.ttf", 30);
	score->score=0;
	

}


void afficherscore(SDL_Surface *screen, score *score )
{	
SDL_Color rouge={255, 0,0};

	  sprintf(score->entree,"Score : %d",score->score);
        score->text = TTF_RenderText_Blended(score->police,score->entree,rouge);
        
      

SDL_BlitSurface(score->text, NULL, screen, &(score->pos)); 
	
}







void liberer_score(score *s)
{
	SDL_FreeSurface(s->text);
 	TTF_CloseFont(s->police);
}








