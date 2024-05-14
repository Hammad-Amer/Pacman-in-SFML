#pragma once

#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include<sstream>
#include<string>
using namespace sf;



class Pacman
{
public:
Sprite SP;
Texture TP;
float xcord;
float ycord;


Pacman()
{
    ycord=25;
    xcord=16;
    TP.loadFromFile("images/L_C.png");
    SP.setTexture(TP);
   
    SP.setPosition(xcord*25,ycord*25); 
    SP.setScale(25.0f /16.0f, 25.0f /16.f);
  
}
};