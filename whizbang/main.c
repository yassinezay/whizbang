#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <ctype.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include <SDL/SDL_mixer.h>
#include <time.h>
#include "Personne.h"
#include "background.h"
#include "enemie.h"
#include "minimap.h"
#include "enigme_IA.h"
#include "enigme.h"//aleatoire sans fichier
#include "menu.h"
#include "option.h"
#include "enig_fichier.h"
#include "sauvegarde.h"

#define mono_joueur 1
#define multijoueur 2
#define new_game 0
#define save_game 3

int main()
{
vie  v;    
minimap m;
enemie e;
Background b;  
Personne p,p1;
SDL_Surface *screen;
SDL_Surface *back;
int continuer=1,up=0;
SDL_Event event,event2;
int acceleration=0;
int deceleration=0;
int up1=0;
int acceleration1=0;
int deceleration1=0;
TTF_Font *police=NULL;
Uint32 t_prev,t_fin , dt ,temps;
SDL_Surface *mask;
int resultat_ia,resultat_alea,stage=1;
SDL_Color Color={255,255,255};
enig_fichier en;
int resultat_fichier;
SDL_Surface *sous_menu_1[2],*menu[2];

SDL_Surface *image2 = NULL, *sous = NULL ;
SDL_Rect positionEcran,possousplay;
image2=IMG_Load("backflou.png");
positionEcran.x=0;
positionEcran.y=0;

int mode=new_game;

SDL_Init(SDL_INIT_VIDEO);
TTF_Init();
screen=SDL_SetVideoMode (1000,600,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
initPerso(&p);
initPerso2(&p1);
initBack(&b);
initennemi(&e);
initmap(&m);
initialiser_score(&v);
back=IMG_Load("background.png");
police=TTF_OpenFont("DS-DIGI.TTF",70);
//mask=IMG_Load("mask.png");
mask=IMG_Load("stage3msk.png");
init_enig_fichier(&en,Color);
int choix=1;
sous_menu_1[0]=IMG_Load("bck1.png");
sous_menu_1[1]=IMG_Load("bck2.png");
menu[0]=IMG_Load("11.png");
menu[1]=IMG_Load("12.png");


sous=IMG_Load("sous1.png");
possousplay.x=250;
possousplay.y=50;

score s;
 
int ok=1,sc;
stat_joueur sj;
SDL_Surface *imageDeFond=NULL;

char nj[100],nom[100];
SDL_Rect position_BG ;


position_BG.x=0;
position_BG.y=0;

meilleur("players.txt",&sc,nj);


imageDeFond = IMG_Load("1.jpg");
initialiserScore(&s );

init_statjoueur(&sj);




//////////menu 
    int Menu=-1;


while(ok)
{
 SDL_BlitSurface(imageDeFond, NULL, screen, &position_BG);

ok=saisir_nom(nom,screen);
SDL_Flip(screen);
}
ok=1;

while(ok)
{
SDL_FreeSurface(screen);
 SDL_BlitSurface(imageDeFond, NULL, screen, &position_BG);

ok=goodluck(nom,screen);
SDL_Flip(screen);
}
ok=1;

  




    do
    {
Menu=afficher_menu(screen);
if (Menu==2)
{ 

while(ok)
{
SDL_FreeSurface(screen);
SDL_BlitSurface(image2,NULL,screen,&positionEcran);
SDL_BlitSurface(sous,NULL,screen,&possousplay);





afficher_meilleur(screen,&sj,sc,nj);

SDL_Flip(screen);
while(SDL_PollEvent(&event2))
{
switch(event2.type)
{
case SDL_QUIT:
ok=0;

break;
}
}
}






SDL_FreeSurface(screen);
SDL_BlitSurface(image2,NULL,screen,&positionEcran);
SDL_Flip(screen);
afficher_option( screen);

}
}
while (Menu==2);

if (Menu ==0) return 0;
while (continuer)
{
t_prev = SDL_GetTicks();

while(SDL_PollEvent(&event))
{
    if (mode==new_game)
    {
        switch (event.type)
      		 {
   		    case SDL_QUIT://pour quitter le program
        	   continuer=0;
          	 break;
       
     		  case SDL_KEYDOWN:
    			   if (event.key.keysym.sym== SDLK_RETURN) 
   			    {
                        printf("%d",choix);
          		 switch (choix)
        	   {
           			case 0:
					mode=multijoueur;
              		 break;
           			 case 1:
           		     mode=mono_joueur;
          			  break;              
         			  }
         			  SDL_Delay(1000);
          	
    			   }
       else
       choix=(choix+1)%2;//si choix =1 , devient 0 ,,, si choix =0 ,, devient 1
       break;
      
       }
    }   
    if (mode==mono_joueur){
switch (event.type)
{
case SDL_QUIT:
    continuer=0;
    break;

case SDL_KEYDOWN:
    switch (event.key.keysym.sym)
    {
    case  SDLK_RIGHT:
        p.direction=0;
        p.vitesse=5;
        break;
    case  SDLK_LEFT:
        p.direction=1;
        p.vitesse=5;
        break; 
    case SDLK_UP:
        up=1;
        break;  
    case SDLK_p:
        acceleration=1;
    break;
    case SDLK_o:
        deceleration=1;
        break;
    case SDLK_ESCAPE:
    mode=save_game;
    break;    

        
    
    
    }
break;

case SDL_KEYUP:
switch (event.key.keysym.sym)//lbouton appuyé?
    {
    case  SDLK_RIGHT:
              p.vitesse=0;
        break;

    case  SDLK_LEFT:        
        p.vitesse=0;
        break; 

    case SDLK_UP:
        up=0;
        break; 

    case SDLK_p:
        acceleration=0;
    break;

    case SDLK_o:
        deceleration=0;
        break; 


      
    
    }

break;
}

}
    if (mode==multijoueur)
    {
       switch (event.type)
{
case SDL_QUIT:
    continuer=0;
    break;

case SDL_KEYDOWN:
    switch (event.key.keysym.sym)
    {
    case  SDLK_RIGHT:
        p.direction=0;
        p.vitesse=5;
        break;
    case  SDLK_LEFT:
        p.direction=1;
        p.vitesse=5;
        break; 
    case SDLK_UP:
        up=1;
        break;  
    case SDLK_p:
        acceleration=1;
    break;
    case SDLK_o:
        deceleration=1;
        break;

        
    case  SDLK_d:
        p1.direction=0;
        p1.vitesse=5;
        break;
    case  SDLK_q:
        p1.direction=1;
        p1.vitesse=5;
        break; 
    case SDLK_z:
        up1=1;
        break;  
    case SDLK_f:
        acceleration1=1;
    break;
    case SDLK_g:
        deceleration1=1;
        break;
    
    }
break;

case SDL_KEYUP:
switch (event.key.keysym.sym)//lbouton appuyé?
    {
    case  SDLK_RIGHT:
              p.vitesse=0;
        break;

    case  SDLK_LEFT:        
        p.vitesse=0;
        break; 

    case SDLK_UP:
        up=0;
        break; 

    case SDLK_p:
        acceleration=0;
    break;

    case SDLK_o:
        deceleration=0;
        break; 



        case  SDLK_d:
              p1.vitesse=0;
        break;

    case  SDLK_q:        
        p1.vitesse=0;
        break; 

    case SDLK_z:
        up1=0;
        break; 

    case SDLK_f:
        acceleration1=0;
    break;

    case SDLK_g:
        deceleration1=0;
        break;             
    
    }

break;
}
    }
    if (mode==save_game)
			{
				switch (event.type)
      		 {
   		    case SDL_QUIT://pour quitter le program
        	   continuer=0;
          	 break;
       
     		  case SDL_KEYDOWN:
    			   if (event.key.keysym.sym== SDLK_RETURN) 
   			    {
           
          		 switch (choix)
        	   {
           			case 0:
						sauvegarder(p,b);
              		 break;
           			 case 1:
           		     charger(&p,&b);
           			     printf("\nperso %d -- %d\n",p.position.x,p.position.y);
            			printf("\nback %d -- %d\n",b.camera.x,b.camera.y);
          			  break;              
         			  }
         			  SDL_Delay(1000);
					   mode=mono_joueur;
          	
    			   }
       else
       choix=(choix+1)%2;//si choix =1 , devient 0 ,,, si choix =0 ,, devient 1
       break;
      
       }
			}

}

//partie update
if (mode==mono_joueur){
if (acceleration==1) p.acceleration = p.acceleration + 0.005 ;
if (deceleration==1) p.acceleration = p.acceleration - 0.01;

p.acceleration = p.acceleration - 0.001;
if (p.acceleration<0) p.acceleration =0;


SDL_Delay(3);
t_fin=SDL_GetTicks();
dt=t_fin - t_prev ;
switch (p.direction)
{
case 0:
    if (collisionbb_droite(p.position,mask,b.camera)==0){
    scrolling(&b.camera,p.direction,p.dx);
    scrolling_enemie(&e,p.direction,p.dx);
    deplacerPerso(&p,dt);
    }
    break;

case 1:
    if (collisionbb_gauche(p.position,mask,b.camera)==0){
    scrolling(&b.camera,p.direction,p.dx);
    scrolling_enemie(&e,p.direction,p.dx);
    deplacerPerso(&p,dt);
    }
    break;
}
s.score+=1;
update_score(&v);
deplacerIA(&e,p.position);
m.pos_joueur=MAJMinimap(p.position,20,b.camera);
animerennemi(&e);
animerPerso(&p);
if (p.up==0 && collisionbb_down(p.position,mask,b.camera)==0)
{
   // p.vitesse_saut+=15;
    p.ground+=15;
}
if (collisionbb_down(p.position,mask,b.camera)==1){
    p.ground=p.position.y;
  //  printf("co\n");
} 


if (up==1) saut(&p);
//printf("%f\n",p.vitesse_saut);
p.position.y = p.position.y   + p.vitesse_saut ;
p.vitesse_saut = p.vitesse_saut + 10 ;
if (p.position.y>=p.ground)
{   
    p.position.y=p.ground;
    p.vitesse_saut=0;
    p.up=0;
}

//jeu puissance quand le perso atteint la fin
if (b.camera.x>b.backgroundImg->w - screen->w)
{switch (stage)
{
case 2:
    resultat_ia=enigme_IA();
    if (resultat_ia==1)
    {
    	
        initPerso(&p);
        initBack(&b);
        initialiser_score(&v);
        //SDL_FreeSurface(mask);
        //mask=IMG_Load("maskstage22.png");
        //continuer=0;
        printf("you win \n");
        stage=1;
        SDL_FreeSurface(screen);
        screen=SDL_SetVideoMode (1000,600,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
    }else
    {
        printf("you lose \n");
        continuer=0;
    }
    break;
case 1:
    resultat_fichier=quiz1(&en,screen);
    if (resultat_fichier==1)
    {
    SDL_FreeSurface(screen);
        initPerso(&p);
        initBack(&b);
        initialiser_score(&v);
        //continuer=0;
        printf("you winn \n");
        stage=2;
    }else
    {
        printf("you lostt \n");
        continuer=0;
    }
    
    
break;

}

}

//cas de collision bb
if (collision(e.pos,p.position)==1)
{
    if (v.valeur_vie>0) v.valeur_vie--;
    else if (v.valeur_vie==0)
    {
        resultat_alea=enigme_alea();
        if (resultat_alea==1)
        {
        //SDL_FreeSurface(screen);
            printf("revived\n");
            p.position.x+=500;
            p.dx=0;
            b.backgroundPos.x+=500;
            v.valeur_vie=100;
            SDL_FreeSurface(screen);
            screen=SDL_SetVideoMode (1000,600,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
        }else
        {
            printf("dead\n");
            continuer=0;
        }
        
        
    }
    
}
}
if (mode==multijoueur)
{
    if (acceleration==1) p.acceleration = p.acceleration + 0.005 ;
if (deceleration==1) p.acceleration = p.acceleration - 0.01;

if (acceleration1==1) p1.acceleration = p1.acceleration + 0.005 ;
if (deceleration1==1) p1.acceleration = p1.acceleration - 0.01;

p.acceleration = p.acceleration - 0.001;
if (p.acceleration<0) p.acceleration =0;


p1.acceleration = p1.acceleration - 0.001;
if (p1.acceleration<0) p1.acceleration =0;


SDL_Delay(3);
t_fin=SDL_GetTicks();
dt=t_fin - t_prev ;
switch (p.direction)
{
case 0:
   if (collisionbb_droite(p.position,mask,b.backgroundPos)==0){
    scrolling(&b.backgroundPos,p.direction,p.dx);
    //scrolling_enemie(&e,p.direction,p.dx);
    deplacerPerso(&p,dt);
    
    }
    break;

case 1:
    if (collisionbb_gauche(p.position,mask,b.backgroundPos)==0){
    scrolling(&b.backgroundPos,p.direction,p.dx);
    //scrolling_enemie(&e,p.direction,p.dx);
    deplacerPerso(&p,dt);
    
    }
    break;
}


switch (p1.direction)
{
case 0:
    if (collisionbb_droite(p1.position,mask,b.backgroundPos2)==0){
    scrolling(&b.backgroundPos2,p1.direction,p1.dx);
    //scrolling_enemie(&e,p.direction,p.dx);
    deplacerPerso2(&p1,dt);
    }
    break;

case 1:
    if (collisionbb_gauche(p1.position,mask,b.backgroundPos2)==0){
    scrolling(&b.backgroundPos2,p1.direction,p1.dx);
    //scrolling_enemie(&e,p.direction,p.dx);
    deplacerPerso2(&p1,dt);
    }
    break;
}
s.score+=1;
//update_score(&v);
//deplacerIA(&e,p.position);
//m.pos_joueur=MAJMinimap(p.position,20,b.backgroundPos);
animerennemi(&e);
animerPerso(&p);
animerPerso(&p1);

if (p.up==0 && collisionbb_down(p.position,mask,b.backgroundPos)==0)
{
    //p.vitesse_saut+=15;
    p.ground+=15;
}
if (collisionbb_down(p.position,mask,b.backgroundPos)==1){
    p.ground=p.position.y;
  //  printf("co\n");
} 

if (p1.up==0 && collisionbb_down(p1.position,mask,b.backgroundPos2)==0)
{
    //p.vitesse_saut+=15;
    p1.ground+=15;
}
if (collisionbb_down(p1.position,mask,b.backgroundPos2)==1){
    p1.ground=p1.position.y;
  //  printf("co\n");
} 

if (up1==1) saut(&p1);

if (up==1) saut(&p);
//printf("%f\n",p.vitesse_saut);
p.position.y = p.position.y   + p.vitesse_saut ;
p.vitesse_saut = p.vitesse_saut + 10 ;
if (p.position.y>=p.ground)
{   
    p.position.y=p.ground;
    p.vitesse_saut=0;
    p.up=0;
}

p1.position.y = p1.position.y   + p1.vitesse_saut ;
p1.vitesse_saut = p1.vitesse_saut + 10 ;
if (p1.position.y>=p1.ground)
{   
    p1.position.y=p1.ground;
    p1.vitesse_saut=0;
    p1.up=0;
}

}



/*----------partie affichage---------*/
//SDL_BlitSurface(back,NULL,screen,NULL);
if (mode==mono_joueur)
{
    afficherBack(b,screen);
    afficherPerso(p,screen);
    afficherennemi(&e,screen);
    affichertemp(&temps,screen,police);
    afficherminimap(m,screen);
    afficher_vie(&v,screen);
    afficherscore(screen, &s);
}
if (mode==new_game){
		SDL_BlitSurface(sous_menu_1[choix],NULL,screen,NULL);
	}	
if (mode==multijoueur)
{
    afficherBack_partage(b,screen);
    afficherPerso(p,screen);
    afficherPerso(p1,screen);
    afficherscore(screen, &s);
    afficherennemi(&e,screen);
}
if (mode==save_game)
	{
		SDL_BlitSurface(menu[choix],NULL,screen,NULL);
	}

SDL_Flip(screen);

SDL_Delay(30);
}


    return 0;
}



