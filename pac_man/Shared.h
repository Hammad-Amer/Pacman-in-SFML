#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
using namespace std;

#include"maze.h"

class Global_varibale
{
public:
char next_movement;
char movement;

float RG_xcord;
float RG_ycord;
bool RG_onblock;
char RG_movement;
string RG_mode;

char table[31][28];

Global_varibale()
{
    Maze M;
    next_movement='0';
    movement='0';
    RG_xcord=9*25;
    RG_ycord=8*25;
    RG_onblock=false;
    RG_movement='W';

    RG_mode="Target";
     for (int i = 0; i < 31; i++) 
     {
            for (int j = 0; j < 28; j++)
             {
                table[i][j]=M.table[i][j];
            }   
 }
 }






};