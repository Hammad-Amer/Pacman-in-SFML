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
    ycord=19;
    xcord=24;
    TP.loadFromFile("images/ALLSprites.png");
    SP.setTexture(TP);
    SP.setTextureRect(IntRect(0,0,30,30));   
    SP.setPosition(xcord*25,ycord*25); 
    SP.setScale(25.0f /30, 25.0f /30);
}
};