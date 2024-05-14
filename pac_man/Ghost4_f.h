#pragma once
#include <SFML/Graphics.hpp>

#include"Shared.h"
#include<cmath>

//this is for the blue ghost



void* Ghost4_f(void* arg)
{

Global_varibale* Shared; 
Shared=(Global_varibale*)(arg);

while(1)
{

    pthread_mutex_lock(&MUTEX_GE);


        if(Shared->game_end==true)
        {
            break;
        }
        
        if(Shared->OG_onblock==true)
        {

        bool flag=false;
        int Py=20,Px=10;
        
        if(Shared->OG_mode=="Target")
        {

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


        if(Shared->OG_xcord<Px+8 && Shared->OG_xcord>Px-8 && Shared->OG_ycord < Py+8 && Shared->BG_ycord>Py-8)
        {
            Py=32;
            Px=0;
        }
}
else if(Shared->OG_mode=="Frightened")
        {
            Py=rand()%31;
            Px=rand()%28;
            srand(time(0));
            
        }    
else if(Shared->OG_mode=="Locked")
        {
            Py=11;
            Px=14;
        }
        else if(Shared->OG_mode=="Scatter")
        {
            Py=31;
            Px=28;
        }
            int x=Shared->OG_xcord;
            int y=Shared->OG_ycord;

            

            
             int Wdis=1000000,Adis=1000000,Sdis=1000000,Ddis=1000000;
        
        if(Shared->OG_movement!='S' && (Shared->table[y-1][x]!='-' && Shared->table[y-1][x]!='|' && Shared->table[y-1][x]!='{' && Shared->table[y-1][x]!='}' &&
            Shared->table[y-1][x]!='[' && Shared->table[y-1][x]!=']'))          
        {
            
            Wdis= (pow((Py - (y-1)),2) + pow((Px - x),2));
          
        }

        if(Shared->OG_movement!='W' && (Shared->table[y+1][x]!='-' && Shared->table[y+1][x]!='|' && Shared->table[y+1][x]!='{' && Shared->table[y+1][x]!='}' &&
            Shared->table[y+1][x]!='[' && Shared->table[y+1][x]!=']'))          
        {
            
            Sdis= (pow((Py - (y+1)),2) + pow((Px - x),2));
          
        }

        if(Shared->OG_movement!='A' && (Shared->table[y][x+1]!='-' && Shared->table[y][x+1]!='|' && Shared->table[y][x+1]!='{' && Shared->table[y][x+1]!='}' &&
            Shared->table[y][x+1]!='[' && Shared->table[y][x+1]!=']'))          
        {
            
            Ddis= (pow((Py - y),2) + pow(Px - (x+1),2));
          
        }

        if(Shared->OG_movement!='D' && (Shared->table[y][x-1]!='-' && Shared->table[y][x-1]!='|' && Shared->table[y][x-1]!='{' && Shared->table[y][x-1]!='}' &&
            Shared->table[y][x-1]!='[' && Shared->table[y][x-1]!=']'))          
        {
            
            Adis= (pow((Py - y),2) + pow(Px - (x-1),2));
          
        }
        
      
        int minDis = std::min({Wdis, Adis, Sdis, Ddis});



        if (Wdis == minDis ) 
        {
            Shared->OG_movement = 'W';
        } 
        else if (Adis == minDis) 
        {
            Shared->OG_movement = 'A';
        } 
        else if (Sdis == minDis )
        {
            Shared->OG_movement = 'S';
        } 
        else if (Ddis == minDis ) 
        {

            Shared->OG_movement = 'D';
        }

              Shared->OG_onblock=false;

        }
        else if(Shared->OG_mode=="Locked1")
        {
            if(Shared->key[0][0]==1 && Shared->key[0][1]==2  && Shared->locked_delay>=8)
            {
                Shared->OG_mode="Locked_out";
                Shared->key[0][0]=0;
                Shared->key[0][1]=0;
                Shared->locked_delay=0;
            }
        }
    pthread_mutex_unlock(&MUTEX_GE);

  

}


}