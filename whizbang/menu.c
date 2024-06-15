#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include "menu.h"
#include "option.h"

int afficher_menu(SDL_Surface *screen)
{
int volume= get_volume();
    int hb = 100, //3olw boutton
        lb = 300, //3orth boutton
        bs = 30;  // espace bin les bouttons

    int f = 0;
    int tmp = 0, m = 0;
    int x,y;

//init click souris music
    Mix_Chunk  *music1;
    Mix_AllocateChannels(1);
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        printf("%s", Mix_GetError());
    }
    music1 = Mix_LoadWAV("select2.wav");

//init back music
Mix_Music *music;
music= Mix_LoadMUS("his1.mp3");
Mix_VolumeMusic(volume);
Mix_PlayMusic(music,-1);



    //creation background
    SDL_Surface *background = NULL;
    background = IMG_Load("bckflou.png");
    // detreminerr pos de back
    SDL_Rect background_pos;
    background_pos.x = 0;
    background_pos.y = 0;
    
    //creation bouton start
    SDL_Surface *start[3];
    start[0] = IMG_Load("PLAY0.png");
    start[1] = IMG_Load("PLAY1.png");
    start[2] = IMG_Load("PLAYC.png");
    int ng = 0;
    //pos buton start
    SDL_Rect start_pos;
    start_pos.x = 325;
    start_pos.y = 150;
    
    //creation bouton option
    SDL_Surface *setting[3];
    setting[0] = IMG_Load("OPTIONS0.png");
    setting[1] = IMG_Load("OPTIONS1.png");
    setting[2] = IMG_Load("OPTIONSC.png");
    int op = 0;
    //pos buton option
    SDL_Rect setting_pos;
    setting_pos.x = 325;
    setting_pos.y = start_pos.y + hb + bs;

    
    
    /*
     //creation bouton credits
    SDL_Surface *credits[3];
    credits[0] = IMG_Load("CREDITS0.png");
    credits[1] = IMG_Load("CREDITS1.png");
    credits[2] = IMG_Load("CREDITSC.png");
    int cr = 0;
    //pos buton credits
    SDL_Rect credits_pos;
    credits_pos.x = 100;
    credits_pos.y = setting_pos.y + hb + bs;*/
    
    
    
    //creation bouton quit
    SDL_Surface *quit[3];
    quit[0] = IMG_Load("quit0.png");
    quit[1] = IMG_Load("quit1.png");
    quit[2] = IMG_Load("quitc.png");
    int ex = 0;
    //pos buton quit
    SDL_Rect quit_pos;
    quit_pos.x = 325;
    quit_pos.y = setting_pos.y + hb + bs;
    
    
    
    
     int t1 = 0, t2 = 0, r = 0;



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
            ////////////////////////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////////////////
            case SDL_QUIT: //nenzel 3al (X) el 7amra
                done = 0;
                break;
            ////////////////////////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////////////////
            //avec clavier
            case SDL_KEYDOWN:                 // ay haja fil clav

                switch (event.key.keysym.sym) // taref type l haja l nzalt alaha fil clav
                {
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                case SDLK_q: //q
                    done = 0;
                    break;
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                case SDLK_UP: //flech fou9ani
                    if (ng == 0 && op == 0 && ex == 0 )
                    {
                        ng = 1;
                    }
                    else if (ng == 1 && t == 0)
                    {
                        ex = 1;
                        ng = 0;
                        op = 0;
                        
                        t = 1;
                    }

                    else if (op == 1 && t == 0)
                    {
                        ng = 1;
                        op = 0;
                        ex = 0;
                        
                        t = 1;
                    }
                    else if (ex == 1 && t == 0)
                    {
                        op = 1;
                        ex = 0;
                        ng = 0;
                        
                        t = 1;
                    }
                    
                    break;
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                case SDLK_DOWN: //flech loutani
                    if (ng == 0 && op == 0 && ex == 0 )
                    {
                        ng = 1;
                    }
                    else if (ng == 1 && t == 0)
                    {
                        ex = 0;
                        ng = 0;
                        op = 1;
                        
                        t = 1;
                    }

                    else if (op == 1 && t == 0)
                    {
                        ng = 0;
                        op = 0;
                        ex = 1;
                        
                        t = 1;
                    }
                    
                    break;
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                case SDLK_RETURN: //entree
                    if (ng == 1)
                    {

                        Mix_PlayChannel(1, music1, 0);
                        SDL_Delay(100);
                        return 1;
                    }

                    else if (op == 1)
                    {

                        Mix_PlayChannel(1, music1, 0);
                        SDL_Delay(100);
                        return 2;
                    }
                    
                    
                    
                    else if (ex == 1)
                    {

                        Mix_PlayChannel(1, music1, 0);
                        SDL_Delay(100);
                       return 0;
                    }
                    break;
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                case SDLK_F8: //t9awi music
                  if (volume < 99 )
                    {
                        volume += 33;

                       Mix_VolumeMusic(volume);
                        save_volume(volume);
                    }
                    break;
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                case SDLK_F7: //tna9s music
                    if (volume > 0 )
                    {
                        volume -= 33;
                       Mix_VolumeMusic(volume);
                        save_volume(volume);
                    }
                    break;
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                case SDLK_F1: //mute//
                    if (m == 0)
                    {
                        tmp = volume;
                        volume = 0;
                        m = 1;
                    }
                    else if (m == 1)
                    {
                        volume = tmp;
                        m = 0;
                    }
                   Mix_VolumeMusic(volume);
                    save_volume(volume);
                    break;
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                ////////////////////////////////////////////////////////////////////////////////////////////////////////
                case SDLK_F4: //full screen
                    if (f == 0)
                    {
                        screen = SDL_SetVideoMode(1000, 600, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
                        f = 1;
                    }
                    else if (f == 1)
                    {
                        screen = SDL_SetVideoMode(1100, 700, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                        f = 0;
                    }
                    break;
                }
                break;
            ////////////////////////////////////////////////////////////////////////////////////////////////////////
            ////////////////////////////////////////////////////////////////////////////////////////////////////////
            //avec souris
            case SDL_MOUSEMOTION:
           x = event.motion.x;
y = event.motion.y;
                ex = 0;
                ng = 0;
                op = 0;
                
               // SDL_GetMouseState(&xmouse,&ymouse);

                if (x>start_pos.x && x<start_pos.x+start_pos.w && y>start_pos.y && y<start_pos.y+start_pos.h)
                {
                    ng = 1;
                }
                else if 
                (x>setting_pos.x && x<setting_pos.x+setting_pos.w && y>setting_pos.y && y<setting_pos.y+setting_pos.h)
                {
                    op = 1;
                }
                else if
                (x>quit_pos.x && x<quit_pos.x+quit_pos.w && y>quit_pos.y && y<quit_pos.y+quit_pos.h)
                {
                    ex = 1;
                }
                
                
                
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    if (ng == 1)
                    {

                        Mix_PlayChannel(1, music1, 0);
                        SDL_Delay(500);
                        return 1;
                    }

                    else if (op == 1)
                    {

                        Mix_PlayChannel(1, music1, 0);
                        SDL_Delay(500);
                        return 2;
                    }
                    
                    
                    
                    else if (ex == 1)
                    {
                        SDL_Delay(600);
                        return 0;
                    }
                }
                break;

            } //fin switch event
        }     //fin pollevent

        //afficher back
        SDL_BlitSurface(background, NULL, screen, &background_pos);
        SDL_BlitSurface(quit[ex], NULL, screen, &quit_pos);
        SDL_BlitSurface(start[ng], NULL, screen, &start_pos);
        SDL_BlitSurface(setting[op], NULL, screen, &setting_pos);
        


      SDL_Flip(screen);

    } //fin while

Mix_FreeChunk(music1);
    SDL_FreeSurface(background);

    SDL_FreeSurface(start[0]);
    SDL_FreeSurface(start[1]);
      SDL_FreeSurface(start[2]);
      
    SDL_FreeSurface(setting[0]);
    SDL_FreeSurface(setting[1]);
    SDL_FreeSurface(setting[2]);

    SDL_FreeSurface(quit[0]);
    SDL_FreeSurface(quit[1]);
    SDL_FreeSurface(quit[2]);
    
    
}

    
