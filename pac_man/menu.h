#pragma once
#include "user_interface.h"
#include "Shared.h"
#include "ghost.h"
#include <thread>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
using namespace std;
using namespace sf;
class Menu
{
public:
    Menu()
    {
    }

    int display_menu(void *arg)

    {

        Global_varibale *Shared = (Global_varibale *)(arg);

        int val = -1;
        Sprite menu_background, pellet;
        Texture menu_texture, pellettex;
        menu_texture.loadFromFile("images/menu.png");
        menu_background.setTexture(menu_texture);
        menu_background.setScale(1, 1);
        RenderWindow window(VideoMode(780, 780), "Main Menu");

        Music music;
        music.openFromFile("audio/intro.wav");
        music.play();
        music.setVolume(20.f);

        SoundBuffer menuclickbuffer;
        menuclickbuffer.loadFromFile("audio/menuclick.wav");
        Sound menuclicksound;
        menuclicksound.setBuffer(menuclickbuffer);
        menuclicksound.setVolume(20.f);

        pellettex.loadFromFile("images/pellet.png");
        pellet.setTexture(pellettex);
        pellet.setScale(0.09, 0.09);
        float x1 = 200, y1 = 275;
        float x2 = 80, y2 = 370;
        float x3 = 150, y3 = 465;
        float x4 = 200, y4 = 620;
        pellet.setPosition(x4, y4);

        Clock clock2;
        float menutimer=0.0;

        int m = 0;

        if (Shared->next_movement == 'P')
            Shared->next_movement = 'O';

        int c = 0;
        
        while (m != 1)
        {   
            float time = clock2.getElapsedTime().asSeconds(); 
    clock2.restart();
            menutimer+=time;

            if(c%4==0)
            {
                pellet.setPosition(x1, y1);
            window.draw(menu_background);
						window.draw(pellet);
						window.display();
            }

             if(c%4==1)
            {
                pellet.setPosition(x2, y2);
            window.draw(menu_background);
						window.draw(pellet);
						window.display();
            }
            
             if(c%4==2)
            {
                pellet.setPosition(x3, y3);
                window.draw(menu_background);
						window.draw(pellet);
						window.display();
            }
            
             if(c%4==3)
            {
                pellet.setPosition(x4, y4);
                 window.draw(menu_background);
						window.draw(pellet);
						window.display();
            }

            if (Shared->next_movement == 'V' && menutimer>0.1)
            {
                menutimer=0;
                menuclicksound.play();
                val=-1;
                break;
            }

            if (Shared->next_movement == 'W' && menutimer>0.1)
            {
                menutimer=0;
                 menuclicksound.play();
                c--;
            }
            else if (Shared->next_movement == 'S' && menutimer>0.1)
            {
                menutimer=0;
                 menuclicksound.play();
                c++;
            }
            else if (Shared->next_movement == 'P' && menutimer>0.1)
            {
                menutimer=0;
                 menuclicksound.play();
                if (c % 4 == 0)
                {
                     menuclicksound.play();
                 break;
                }
                else if (c % 4 == 1)
                {
                    menuclicksound.play();
                    m = 0;
                    while (m != 2)
                    {

                        window.draw(menu_background);
                        menu_texture.loadFromFile("images/menu2.png");
                        window.display();

                        if (Shared->next_movement == 'A')
                        {

                            menuclicksound.play();
                            m = 2;
                            menu_texture.loadFromFile("images/menu.png");
                        }
                        if (Shared->next_movement == 'V')
                        {
                            menuclicksound.play();
                            break;
                        }
                    }
                }
                else if (c % 4 == 2)
                {
                    menuclicksound.play();
                    m = 0;
                    while (m != 3)
                    {

                        window.draw(menu_background);
                        menu_texture.loadFromFile("images/menu3.png");
                        window.display();

                        if (Shared->next_movement == 'A')
                        {
                            menuclicksound.play();
                            m = 3;
                            menu_texture.loadFromFile("images/menu.png");
                        }
                        if (Shared->next_movement == 'V')
                        {
                            menuclicksound.play();
                            break;
                        }
                    }
                }
                else if (c % 4 == 3)
                {
                    menuclicksound.play();
                    val=-1;
                    break;
                }
            }
            Shared->next_movement = 'O';
        }

        return val;
    }
};