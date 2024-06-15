#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>

void save_volume(int volume)
{
    FILE *fichier = NULL;
    fichier = fopen("fichier/volume.txt", "w");
    fprintf(fichier, "%d", volume);
    fclose(fichier);
}

int get_volume()
{
    int volume;
    FILE *fichier = NULL;
    fichier = fopen("fichier/volume.txt", "r");
    while (!feof(fichier))
        fscanf(fichier, "%d", &volume);
    fclose(fichier);
    return volume;
}


int afficher_option(SDL_Surface *screen)
{
    int volum=get_volume();

    int hb = 100,       //3olw boutton
        lb = 300,       //3orth boutton
        bs = 30,        // espace bin les bouttons
        vol_width = 50; // kobr ta3 boutton
        
        int x,y;
        
    TTF_Init();

    Mix_Chunk  *music1;
    Mix_AllocateChannels(2);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        printf("%s", Mix_GetError());
    }
    music1 = Mix_LoadWAV("select2.wav");

Mix_Music *music;
music= Mix_LoadMUS("his1.mp3");
Mix_VolumeMusic(volum);
Mix_PlayMusic(music,-1);

    //creation background
    SDL_Surface *background = NULL;
    background = IMG_Load("sous1.png");
    // detreminerr pos de back
    SDL_Rect background_pos;
    background_pos.x = 250;
    background_pos.y = 50;

    //creation bouton volume
    SDL_Surface *volume[4];
    volume[0] = IMG_Load("v0.png");
    volume[1] = IMG_Load("v2.png");
    volume[2] = IMG_Load("v4.png");
    volume[3] = IMG_Load("v6.png");
    int vl = 0, v = 0;
    if (volum == 0)
        v = 0;
    if (volum == 33)
        v = 1;
    if (volum == 66)
        v = 2;
    if (volum == 99)
        v = 3;
    //pos buton volume
    SDL_Rect volume_pos;
    volume_pos.x = 530;
    volume_pos.y = 350;


    //creation bouton full
    SDL_Surface *full[2];
    full[0] = IMG_Load("full0.png");
    //full[1] = IMG_Load("graphic/button_full2.png");
    full[1] = IMG_Load("full1.png");
    int fl = 0;
    //pos buton full
    SDL_Rect full_pos;
    full_pos.x = 345;
    full_pos.y = volume_pos.y + hb ; 

    //creation bouton back
    SDL_Surface *back[2];
    back[0] = IMG_Load("back0.png");
    back[1] = IMG_Load("backclik.png");
    //back[2] = IMG_Load("graphic/button_back1.png");
    int ba = 0;
    //pos buton back
    SDL_Rect back_pos;
    back_pos.x = 270;
    back_pos.y = /*full_pos.y + hb + bs;*/ 80;

    //CREATION TEXTE

    TTF_Font *police = NULL;
    police = TTF_OpenFont("graphic/font.ttf", 60);
    SDL_Color couleur = {255, 255, 255}, couleur1 = {139, 0, 0};
    SDL_Surface *texte = NULL;
    texte = TTF_RenderText_Solid(police, "volume", couleur);

    //pos texte
    SDL_Rect texte_pos;
    texte_pos.x = 270;
    texte_pos.y = 314 ;

    int t = 0;
    SDL_Event event;
    int done = 1;
    while (done)
    {
        t = 0;
        if (SDL_PollEvent(&event)) // ki ninzel ala ay haja
        {
            switch (event.type) //tal9a type el 7aja
            {
            case SDL_QUIT: //nenzel 3al (X) el 7amra
                done = 0;
                break;
case SDL_MOUSEMOTION:
           x = event.motion.x;
y = event.motion.y;
                ba = 0;
                fl = 0;
                vl = 0;
                  if (x>back_pos.x && x<back_pos.x+back_pos.w && y>back_pos.y && y<back_pos.y+back_pos.h)
                {
                    ba = 1;
                }  
                else if 
                (x>texte_pos.x && x<texte_pos.x+texte_pos.w && y>texte_pos.y && y<texte_pos.y+texte_pos.h)
                {
                  vl = 1;  
                   }
                   else if 
                (x>full_pos.x && x<full_pos.x+full_pos.w && y>full_pos.y && y<full_pos.y+full_pos.h)
                {
                  fl = 1;  
                   }
                   
                   break;
                   
                   
                   
                    case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (ba == 1)
                    {

                        Mix_PlayChannel(1, music1, 0);
                        SDL_Delay(500);
                        return 1;
                    }

                    /*else if (fl == 1)
                    {

                        Mix_PlayChannel(1, music1, 0);
                        SDL_Delay(500);
                        return 2;
                    }*/
                    
                    
                    
                   /* else if ( == 1)
                    {
                        SDL_Delay(600);
                        return 0;
                    }*/
                }
                break;
                   
                   
                   
            //avec clavier
            case SDL_KEYDOWN:                 // ay haja fil clav
                switch (event.key.keysym.sym) // taref type l haja l nzalt alaha fil clav
                {
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                case SDLK_UP: //flech fou9ani
                    if (vl == 0 && fl == 0 && ba == 0)
                    {
                        vl = 1;
                    }
                    else if (vl == 1 && t == 0)
                    {
                        ba = 1;
                        vl = 0;
                        fl = 0;

                        t = 1;
                    }
                    else if (ba == 1 && t == 0)
                    {
                        fl = 1;
                        vl = 0;
                        ba = 0;
                        t = 1;
                    }
                    else if (fl == 1 && t == 0)
                    {
                        fl = 0;
                        vl = 1;
                        ba = 0;
                        t = 1;
                    }

                    break;
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                case SDLK_DOWN: //flech loutani
                    if (vl == 0 && fl == 0 && ba == 0)
                    {
                        ba = 1;
                    }
                    else if (vl == 1 && t == 0)
                    {
                        ba = 0;
                        vl = 0;
                        fl = 1;

                        t = 1;
                    }
                    else if (fl == 1 && t == 0)
                    {
                        fl = 0;
                        vl = 0;
                        ba = 1;

                        t = 1;
                    }
                    else if (ba == 1 && t == 0)
                    {
                        ba = 0;
                        fl = 0;
                        vl = 1;
                        t = 1;
                    }

                    break;
                    
                    
                    
                    
                    
                   
                   
                   
                   
                    
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                case SDLK_RETURN: //entree
                    if (fl == 1)
                    {
                        screen = SDL_SetVideoMode(1920, 900, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
                    }
                    else if (ba == 1)
                    {
                        done = 0;
                    }
                    break;
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                case SDLK_RIGHT: //t9awi music//t9awi music//t9awi music//t9awi music
                    if (volum < 99 && vl == 1)
                    {
                        volum += 33;
                        v++;
                       Mix_VolumeMusic(volum);
                    }
                    break;
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                case SDLK_LEFT: //tna9s music
                    if (volum > 0 && vl == 1)
                    {
                        volum -= 33;
                        v--;
Mix_VolumeMusic(volum);
                    }
                    break;
                   
                }
                break;
            ////////


            } //fin switch event
        }     //fin pollevent

        //couleur text volume
        if (vl == 1)
            texte = TTF_RenderText_Solid(police, "volume", couleur1);
        else
            texte = TTF_RenderText_Solid(police, "volume", couleur);

        //afficher
        SDL_BlitSurface(background, NULL, screen, &background_pos);
        SDL_BlitSurface(volume[v], NULL, screen, &volume_pos);
        SDL_BlitSurface(full[fl], NULL, screen, &full_pos);
        SDL_BlitSurface(back[ba], NULL, screen, &back_pos);
        SDL_BlitSurface(texte, NULL, screen, &texte_pos);


        SDL_Flip(screen);

    } //fin while done

    save_volume(volum);
Mix_FreeChunk(music1);
    SDL_FreeSurface(background);
    TTF_CloseFont(police);
    TTF_Quit();
} //fin focnt
