#ifndef TABLE_H
#define TABLE_H

#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include<sstream>
#include<string>
using namespace sf;

class Grid
{
public:
Sprite wallsS,FrontS,Scoins;
Texture wallsT,FrontT,Tcoins;

Grid()
{
wallsT.loadFromFile("images/bluecolor.png");
wallsS.setTexture(wallsT);
wallsS.setScale(25.0f / wallsT.getSize().x, 25.0f / wallsT.getSize().y);
FrontT.loadFromFile("images/pacman_maze.png");
FrontS.setPosition( 75,50 );
FrontS.setTexture(FrontT);
Tcoins.loadFromFile("images/coins.png");
Scoins.setTexture(Tcoins);
Scoins.setScale(25.0f/Tcoins.getSize().x,25.0f/Tcoins.getSize().y);
}

void drawtable(char table[][28], RenderWindow& window)
{
window.clear();

int i2,j2;
for(int i=0;i<31;i++)
{
    for(int j=0;j<28;j++)
    {
        i2=i+2;
        j2=j+3;
        /*if(table[i][j]=='{' || table[i][j]=='}'||  table[i][j]=='['||  table[i][j]==']'||  table[i][j]=='-'||  table[i][j]=='|' )
        {
            wallsS.setPosition(j2*25  , i2*25 );
            window.draw(wallsS);
        }*/
        if(table[i][j]=='o')
        {
            Scoins.setPosition(j2*25  , i2*25 );
            window.draw(Scoins);
        }

    }

}

}

bool checkCollision(char table[][28],const FloatRect& pacmanRect)
{
        for (int i = 0; i < 31; i++) {
            for (int j = 0; j < 28; j++) {
                if (table[i][j] == '{' || table[i][j] == '}' || table[i][j] == '[' ||
                    table[i][j] == ']' || table[i][j] == '-' || table[i][j] == '|') {
                    FloatRect wallRect((j+3) * 25 , (i+2) * 25 , 25, 25); 
                    if (pacmanRect.intersects(wallRect)) {
                        return true; 
                    }
                }
                if(table[i][j]=='o')
                {
                    float coinCenterX = (j + 3.5f) * 25.0f; 
                    float coinCenterY = (i + 2.5f) * 25.0f;

                    float distanceX = std::abs(pacmanRect.left + pacmanRect.width / 2.0f - coinCenterX);
                    float distanceY = std::abs(pacmanRect.top + pacmanRect.height / 2.0f - coinCenterY);

                    float coinRadius = 12.5f;

                    if (distanceX < coinRadius && distanceY < coinRadius)
                    {
                        table[i][j]=' ';
                    }
                }
            }
        }
        return false; 
}










};

#endif