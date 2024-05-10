#pragma once
#include<iostream>
#include<string>
#include<SFML/Graphics.hpp>

using namespace sf;

class Ghost
{
public:
Sprite SG;
Texture TG;


Ghost(string texture_str)
{
   
    TG.loadFromFile("images/ALLSprites.png");
    SG.setTexture(TG); 
    SG.setScale(25.0f /30, 25.0f /30);

}



};





