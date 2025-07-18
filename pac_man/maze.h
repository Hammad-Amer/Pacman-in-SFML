#pragma once
#include<iostream>
using namespace std;

class Maze
{
public:
char table[31][28];


Maze() : table{}
{
char temp_table[31][28]=
{   {'{','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','}'},//1    
    {'|','o','o','o','o','o','o','o','o','o','o','o','o','}','{','o','o','o','o','o','o','o','o','o','o','o','o','|'},//2 
    {'|','o','{','-','-','}','o','{','-','-','-','}','o','|','|','o','{','-','-','-','}','o','{','-','-','}','o','|'},//3
    {'|','#','|',' ',' ','|','o','|',' ',' ',' ','|','o','|','|','o','|',' ',' ',' ','|','o','|',' ',' ','|','#','|'},//4 
    {'|','o','[','-','-',']','o','[','-','-','-',']','o','[',']','o','[','-','-','-',']','o','[','-','-',']','o','|'},//5 
    {'|','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','|'},//6 
    {'|','o','{','-','-','}','o','{','}','o','{','-','-','-','-','-','-','}','o','{','}','o','{','-','-','}','o','|'},//7 
    {'|','o','[','-','-',']','o','|','|','o','[','-','-','}','{','-','-',']','o','|','|','o','[','-','-',']','o','|'},//8 
    {'|','o','o','o','o','o','o','|','|','o','o','o','o','|','|','o','o','o','o','|','|','o','o','o','o','o','o','|'},//9 
    {'[','-','-','-','-','}','o','|','[','-','-','}',' ','|','|',' ','{','-','-',']','|','o','{','-','-','-','-',']'},//10 
    {' ',' ',' ',' ',' ','|','o','|','{','-','-',']',' ','[',']',' ','[','-','-','}','|','o','|',' ',' ',' ',' ',' '},//11 
    {' ',' ',' ',' ',' ','|','o','|','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|','|','o','|',' ',' ',' ',' ',' '},//12 
    {' ',' ',' ',' ',' ','|','o','|','|',' ','{','-','-','-','-','-','-','}',' ','|','|','o','|',' ',' ',' ',' ',' '},//13 
    {'-','-','-','-','-',']','o','[',']',' ','|',' ',' ',' ',' ',' ',' ','|',' ','[',']','o','[','-','-','-','-','-'},//14 
    {' ',' ',' ',' ',' ',' ','o',' ',' ',' ','|',' ',' ',' ',' ',' ',' ','|',' ',' ',' ','o',' ',' ',' ',' ',' ',' '},//15 
    {'-','-','-','-','-','}','o','{','}',' ','|',' ',' ',' ',' ',' ',' ','|',' ','{','}','o','[','-','-','-','-','-'},//16 
    {' ',' ',' ',' ',' ','|','o','|','|',' ','[','-','-','-','-','-','-',']',' ','|','|','o','|',' ',' ',' ',' ',' '},//17 
    {' ',' ',' ',' ',' ','|','o','|','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|','|','o','|',' ',' ',' ',' ',' '},//18 
    {' ',' ',' ',' ',' ','|','o','|','|',' ','{','-','-','-','-','-','-','}',' ','|','|','o','|',' ',' ',' ',' ',' '},//19 
    {'{','-','-','-','-',']','o','[',']',' ','[','-','-','}','{','-','-',']',' ','[',']','o','[','-','-','-','-','}'},//20 
    {'|','o','o','o','o','o','o','o','o','o','o','o','o','|','|','o','o','o','o','o','o','o','o','o','o','o','o','|'},//21 
    {'|','o','{','-','-','}','o','{','-','-','-','}','o','|','|','o','{','-','-','-','}','o','{','-','-','}','o','|'},//22 
    {'|','o','[','-',']','|','o','[','-','-','-',']','o','[',']','o','[','-','-','-',']','o','|','[','-',']','o','|'},//23 
    {'|','#','o','o','|','|','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','|','|','o','o','#','|'},//24 
    {'[','-','}','o','|','|','o','{','}','o','{','-','-','-','-','-','-','}','o','{','}','o','|','|','o','{','-','|'},//25 
    {'{','-',']','o','[',']','o','|','|','o','[','-','-','}','{','-','-',']','o','|','|','o','[',']','o','[','-','}'},//26 
    {'|','o','o','o','o','o','o','|','|','o','o','o','o','|','|','o','o','o','o','|','|','o','o','o','o','o','o','|'},//27
    {'|','o','{','-','-','-','-',']','[','-','-','}','o','|','|','o','{','-','-',']','[','-','-','-','-','}','o','|'},//28
    {'|','o','[','-','-','-','-','-','-','-','-',']','o','[',']','o','[','-','-','-','-','-','-','-','-',']','o','|'},//29
    {'|','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','o','|'},//30 
    {'[','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-',']'} //31 
    //1   2   3   4   5   6   7   8   9   10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28
};



    for (int i = 0; i < 31; i++) 
    {
        for (int j = 0; j < 28; j++) 
        {
            table[i][j] = temp_table[i][j];
        }
    }

}



};