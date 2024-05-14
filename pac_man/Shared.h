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
bool RG_faster;

float PG_xcord;
float PG_ycord;
bool PG_onblock;
char PG_movement;
string PG_mode;
bool PG_faster;

float BG_xcord;
float BG_ycord;
bool BG_onblock;
char BG_movement;
string BG_mode;
bool BG_faster;

float OG_xcord;
float OG_ycord;
bool OG_onblock;
char OG_movement;
string OG_mode;
bool OG_faster;

float locked_delay;

int key[2][2];


char table[31][28];

Global_varibale()
{
    Maze M;
    next_movement='0';
    movement='0';

    RG_xcord=18*25;
    RG_ycord=16*25;
    RG_onblock=true;
    RG_movement='W';
    RG_mode="Locked1";

    PG_xcord=17*25;
    PG_ycord=16*25;
    PG_onblock=true;
    PG_movement='W';
    PG_mode="Locked1";

    
    BG_xcord=16*25;
    BG_ycord=16*25;
    BG_onblock=true;
    BG_movement='W';
    BG_mode="Locked1";
    
    OG_xcord=15*25;
    OG_ycord=16*25;
    OG_onblock=true;
    OG_movement='A';
    OG_mode="Locked1";

    locked_delay=0;

    key[0][0]=0;
    key[0][1]=0;
    key[1][0]=2;
    key[1][1]=1;

    BG_faster=0;
    OG_faster=0;
    PG_faster=0;
    RG_faster=0;

/*      OG
    1       2
RG              BG
    2          1
        PG
*/      
     for (int i = 0; i < 31; i++) 
     {
            for (int j = 0; j < 28; j++)
             {
                table[i][j]=M.table[i][j];
            }   
    }
 }






};