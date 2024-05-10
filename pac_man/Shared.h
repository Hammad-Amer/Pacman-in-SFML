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



float PG_xcord;
float PG_ycord;
bool PG_onblock;
char PG_movement;
string PG_mode;



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

    PG_xcord=12*25;
    PG_ycord=14*25;
    PG_onblock=false;
    PG_movement='W';
    PG_mode="Target";

     for (int i = 0; i < 31; i++) 
     {
            for (int j = 0; j < 28; j++)
             {
                table[i][j]=M.table[i][j];
            }   
 }
 }






};