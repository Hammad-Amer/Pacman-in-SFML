#pragma once

#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <sstream>
#include <string>
using namespace sf;

#include "Shared.h"

pthread_mutex_t MUTEX_UE = PTHREAD_MUTEX_INITIALIZER;

void *User_interface(void *arg)
{
    Global_varibale *Shared;
    Shared = (Global_varibale *)(arg);
    while (1)
    {


        if(Shared->game_end==true)
        {
            break;
        }
        
        if (Keyboard::isKeyPressed(Keyboard::W))
        {

            pthread_mutex_lock(&MUTEX_UE);
            Shared->next_movement = 'W';
            pthread_mutex_unlock(&MUTEX_UE);
        }
        else if (Keyboard::isKeyPressed(Keyboard::A))
        {
            pthread_mutex_lock(&MUTEX_UE);
            Shared->next_movement = 'A';
            pthread_mutex_unlock(&MUTEX_UE);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Enter))
        {
            pthread_mutex_lock(&MUTEX_UE);
            Shared->next_movement = 'P';
            pthread_mutex_unlock(&MUTEX_UE);
        }
        else if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            pthread_mutex_lock(&MUTEX_UE);
            Shared->next_movement = 'V';
            pthread_mutex_unlock(&MUTEX_UE);
        }
        else if (Keyboard::isKeyPressed(Keyboard::S))
        {
            pthread_mutex_lock(&MUTEX_UE);
            Shared->next_movement = 'S';
            pthread_mutex_unlock(&MUTEX_UE);
        }
        else if (Keyboard::isKeyPressed(Keyboard::D))
        {
            pthread_mutex_lock(&MUTEX_UE);
            Shared->next_movement = 'D';
            pthread_mutex_unlock(&MUTEX_UE);
        }
        sf::sleep(sf::milliseconds(20));
    }
    pthread_mutex_destroy(&MUTEX_UE);
}