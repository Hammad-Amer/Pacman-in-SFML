#ifndef TABLE_H
#define TABLE_H

#include "Shared.h"
#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <sstream>
#include <string>
#include <pthread.h>
#include <unistd.h>
using namespace sf;

class Grid
{
public:
    Sprite wallsS, FrontS, Scoins, Spellets;
    Texture wallsT, FrontT, Tcoins, Tpellets;
    SoundBuffer eats,eats1;
    Sound eat,eat1;

    Grid()
    {
        wallsT.loadFromFile("images/bluecolor.png");
        wallsS.setTexture(wallsT);
        wallsS.setScale(25.0f / wallsT.getSize().x, 25.0f / wallsT.getSize().y);
        FrontT.loadFromFile("images/pacman_maze.png");
        FrontS.setPosition(75, 50);
        FrontS.setTexture(FrontT);
        Tcoins.loadFromFile("images/coins.png");
        Scoins.setTexture(Tcoins);
        Scoins.setScale(25.0f / Tcoins.getSize().x, 25.0f / Tcoins.getSize().y);
        Tpellets.loadFromFile("images/pellet.png");
        Spellets.setTexture(Tpellets);
        Spellets.setScale(25.0f / Tpellets.getSize().x, 25.0f / Tpellets.getSize().y);

        eats.loadFromFile("audio/eat.wav");
        eat.setBuffer(eats);
        eat.setVolume(20.f);

        eats1.loadFromFile("audio/eatFruit.wav");
        eat1.setBuffer(eats);
        eat1.setVolume(50.f);


    }

    void drawtable(char table[][28], RenderWindow &window)
    {
        window.clear();

        int i2, j2;
        for (int i = 0; i < 31; i++)
        {
            for (int j = 0; j < 28; j++)
            {
                i2 = i + 2;
                j2 = j + 3;

                if (table[i][j] == 'o')
                {
                    Scoins.setPosition(j2 * 25, i2 * 25);
                    window.draw(Scoins);
                }

                if (table[i][j] == '#')
                {

                    Spellets.setPosition(j2 * 25, i2 * 25);
                    window.draw(Spellets);
                }
            }
        }
    }

    bool checkCollision(char table[][28], const FloatRect &pacmanRect, int &score, int &count)
    {

        for (int i = 0; i < 31; i++)
        {
            for (int j = 0; j < 28; j++)
            {
                if (table[i][j] == '{' || table[i][j] == '}' || table[i][j] == '[' ||
                    table[i][j] == ']' || table[i][j] == '-' || table[i][j] == '|')
                {
                    FloatRect wallRect((j + 3) * 25, (i + 2) * 25, 25, 25);
                    if (pacmanRect.intersects(wallRect))
                    {
                        return true;
                    }
                }
                if (table[i][j] == 'o')
                {
                    float coinCenterX = (j + 3.5f) * 25.0f;
                    float coinCenterY = (i + 2.5f) * 25.0f;

                    float distanceX = std::abs(pacmanRect.left + pacmanRect.width / 2.0f - coinCenterX);
                    float distanceY = std::abs(pacmanRect.top + pacmanRect.height / 2.0f - coinCenterY);

                    float coinRadius = 12.5f;

                    if (distanceX < coinRadius && distanceY < coinRadius)
                    {
                        eat.play();
                        score += 10;
                        count--;
                        table[i][j] = 'P';
                        if (table[i - 1][j] == 'P')
                            table[i - 1][j] = ' ';
                        if (table[i + 1][j] == 'P')
                            table[i + 1][j] = ' ';
                        if (table[i][j - 1] == 'P')
                            table[i][j - 1] = ' ';
                        if (table[i][j + 1] == 'P')
                            table[i][j + 1] = ' ';
                    }
                }
                else if (table[i][j] == ' ')
                {
                    float BCX = (j + 3.5f) * 25.0f;
                    float BCY = (i + 2.5f) * 25.0f;

                    float distanceX = std::abs(pacmanRect.left + pacmanRect.width / 2.0f - BCX);
                    float distanceY = std::abs(pacmanRect.top + pacmanRect.height / 2.0f - BCY);

                    float blockHalfWidth = 25.0f / 2.0f;
                    float blockHalfHeight = 25.0f / 2.0f;
                    if (distanceX <= blockHalfWidth && distanceY <= blockHalfHeight)
                    {
                        table[i][j] = 'P';
                        if (table[i - 1][j] == 'P')
                            table[i - 1][j] = ' ';
                        if (table[i + 1][j] == 'P')
                            table[i + 1][j] = ' ';
                        if (table[i][j - 1] == 'P')
                            table[i][j - 1] = ' ';
                        if (table[i][j + 1] == 'P')
                            table[i][j + 1] = ' ';
                    }
                }
            }
        }

        return false;
    }

    bool isGhostOnBlock(char table[][28], const FloatRect &ghostRect)
    {

        int ghostLeft = static_cast<int>(ghostRect.left);
        int ghostTop = static_cast<int>(ghostRect.top);
        int ghostRight = ghostLeft + static_cast<int>(ghostRect.width) - 1;
        int ghostBottom = ghostTop + static_cast<int>(ghostRect.height) - 1;

        for (int i = 0; i < 31; ++i)
        {
            for (int j = 0; j < 28; ++j)
            {

                int blockLeft = (j + 3) * 25;
                int blockTop = (i + 2) * 25;
                int blockRight = blockLeft + 24; // Assuming 25x25 blocks
                int blockBottom = blockTop + 24;

                if (ghostLeft >= blockLeft && ghostRight <= blockRight &&
                    ghostTop >= blockTop && ghostBottom <= blockBottom)
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool PacmanPallete(char table[][28], const FloatRect &pacmanRect)
    {
        for (int i = 0; i < 31; i++)
        {
            for (int j = 0; j < 28; j++)
            {
                if (table[i][j] == '#')
                {
                    FloatRect wallRect((j + 3) * 25, (i + 2) * 25, 25, 25);
                    if (pacmanRect.intersects(wallRect))
                    {
                        eat1.play();
                        table[i][j] = ' ';
                        return true;
                    }
                }
            }
        }
        return false;
    }

    bool Ghost_coll(const FloatRect &pacman, const FloatRect &Ghost)
    {

        if (pacman.intersects(Ghost))
        {
            return true;
        }
        return false;
    }

    bool Get_locked(const FloatRect &GhostRect)
    {
        float cellX = (14 + 3) * 25;
        float cellY = (11 + 2) * 25;
        float cellRight = cellX + 25;
        float cellBottom = cellY + 25;

        return (GhostRect.left >= cellX &&
                GhostRect.left + GhostRect.width <= cellRight &&
                GhostRect.top >= cellY &&
                GhostRect.top + GhostRect.height <= cellBottom);
    }

    void Ghost_eats_pacman(Global_varibale *Shared)
    {
        for (int i = 0; i < 31; i++)
        {
            for (int j = 0; j < 28; j++)
            {
                if (Shared->table[i][j] == 'P')
                {
                    Shared->table[i][j] == ' ';
                }
            }
        }

        if (Shared->PG_mode != "Locked1")
            Shared->PG_mode = "Locked";
        if (Shared->RG_mode != "Locked1")
            Shared->RG_mode = "Locked";
        if (Shared->OG_mode != "Locked1")
            Shared->OG_mode = "Locked";
        if (Shared->BG_mode != "Locked1")
            Shared->BG_mode = "Locked";

        Shared->movement = '0';
        Shared->next_movement = '0';
        Shared->locked_delay = 0;
    }
};

#endif