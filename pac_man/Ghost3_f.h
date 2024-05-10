#pragma once
#include <SFML/Graphics.hpp>

#include"Shared.h"
#include<cmath>

//this is for the blue ghost

pthread_mutex_t MUTEX_BG=PTHREAD_MUTEX_INITIALIZER;

void* Ghost3_f(void* arg)
{

Global_varibale* Shared; 
Shared=(Global_varibale*)(arg);

while(1)
{

    pthread_mutex_lock(&MUTEX_BG);

        if(Shared->BG_onblock==true)
        {

        bool flag=false;
        int Py=20,Px=10;

        for(int t1=0;t1<31;t1++)
        {   
            for(int t2=0;t2<28;t2++)
            {
               
                if((t1==14 && t2==0)||(t1==14 && t2==25))
                {
                    Shared->table[t1][t2]=' ';
                }

                if(Shared->table[t1][t2]=='P')
                {
                    Py=t1;  
                    Px=t2;

                    flag=true;
                    break;

                  
                }
            }

            if(flag)
            break;
        }

       if(Shared->movement=='W')
        {
            Py-=2;
        }
        else if(Shared->movement=='A')
        {
            Px-=2;
        }
        else if(Shared->movement=='S')
        {
            Py+=2;
        }
        else if(Shared->movement=='D')
        {
            Px+=2;
        }

       int tempy=Py;
       int tempx=Px;

       if(Shared->RG_xcord>Px)
       {
        tempx=Px-(int)(Shared->RG_xcord);
       }
       else if(Shared->RG_xcord<Px)
       {
        tempx=Px+(int)(Shared->RG_xcord);
       }
            
        if(Shared->RG_ycord>Py)
        {
          tempy=Py-(int)(Shared->RG_ycord);
       }
       else if(Shared->RG_ycord<Py)
       {
        tempy=Py+(int)(Shared->RG_ycord);
       }
          
            Px=tempx;
            Py=tempy;

            int x=Shared->BG_xcord;
            int y=Shared->BG_ycord;



            
             int Wdis=1000000,Adis=1000000,Sdis=1000000,Ddis=1000000;
        
        if(Shared->BG_movement!='S' && (Shared->table[y-1][x]!='-' && Shared->table[y-1][x]!='|' && Shared->table[y-1][x]!='{' && Shared->table[y-1][x]!='}' &&
            Shared->table[y-1][x]!='[' && Shared->table[y-1][x]!=']'))          
        {
            
            Wdis= (pow((Py - (y-1)),2) + pow((Px - x),2));
          
        }

        if(Shared->BG_movement!='W' && (Shared->table[y+1][x]!='-' && Shared->table[y+1][x]!='|' && Shared->table[y+1][x]!='{' && Shared->table[y+1][x]!='}' &&
            Shared->table[y+1][x]!='[' && Shared->table[y+1][x]!=']'))          
        {
            
            Sdis= (pow((Py - (y+1)),2) + pow((Px - x),2));
          
        }

        if(Shared->BG_movement!='A' && (Shared->table[y][x+1]!='-' && Shared->table[y][x+1]!='|' && Shared->table[y][x+1]!='{' && Shared->table[y][x+1]!='}' &&
            Shared->table[y][x+1]!='[' && Shared->table[y][x+1]!=']'))          
        {
            
            Ddis= (pow((Py - y),2) + pow(Px - (x+1),2));
          
        }

        if(Shared->BG_movement!='D' && (Shared->table[y][x-1]!='-' && Shared->table[y][x-1]!='|' && Shared->table[y][x-1]!='{' && Shared->table[y][x-1]!='}' &&
            Shared->table[y][x-1]!='[' && Shared->table[y][x-1]!=']'))          
        {
            
            Adis= (pow((Py - y),2) + pow(Px - (x-1),2));
          
        }
        
      
        int minDis = std::min({Wdis, Adis, Sdis, Ddis});



        if (Wdis == minDis ) 
        {
            Shared->BG_movement = 'W';
        } 
        else if (Adis == minDis) 
        {
            Shared->BG_movement = 'A';
        } 
        else if (Sdis == minDis )
        {
            Shared->BG_movement = 'S';
        } 
        else if (Ddis == minDis ) 
        {

            Shared->BG_movement = 'D';
        }

              Shared->BG_onblock=false;

        }
    pthread_mutex_unlock(&MUTEX_BG);

  

}

pthread_mutex_destroy(&MUTEX_BG);
}