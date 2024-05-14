#pragma once
#include <SFML/Graphics.hpp>

#include"Shared.h"
#include<cmath>
#include<cstdlib>

//this is for the red ghost



void* Ghost1_f(void* arg)
{

Global_varibale* Shared; 
Shared=(Global_varibale*)(arg);

while(1)
{
    

    pthread_mutex_lock(&MUTEX_GE);

        if(Shared->RG_onblock==true)
        {


        bool flag=false;
        int Py=10,Px=10;

        if(Shared->RG_mode=="Target")
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
        }
        else if(Shared->RG_mode=="Frightened")
        {
            Py=rand()%31;
            Px=rand()%28;
            srand(time(0));
            
        }
        else if(Shared->RG_mode=="Locked")
        {
            Py=11;
            Px=14;
        }
       

            //xcord for horizonatal  //so columns
            //ycord for vertical    //so rows
            
            int x=Shared->RG_xcord;
            int y=Shared->RG_ycord;



            
             int Wdis=1000000,Adis=1000000,Sdis=1000000,Ddis=1000000;
        
        if(Shared->RG_movement!='S' && (Shared->table[y-1][x]!='-' && Shared->table[y-1][x]!='|' && Shared->table[y-1][x]!='{' && Shared->table[y-1][x]!='}' &&
            Shared->table[y-1][x]!='[' && Shared->table[y-1][x]!=']'))          
        {
            
            Wdis= (pow((Py - (y-1)),2) + pow((Px - x),2));
          
        }

        if(Shared->RG_movement!='W' && (Shared->table[y+1][x]!='-' && Shared->table[y+1][x]!='|' && Shared->table[y+1][x]!='{' && Shared->table[y+1][x]!='}' &&
            Shared->table[y+1][x]!='[' && Shared->table[y+1][x]!=']'))          
        {
            
            Sdis= (pow((Py - (y+1)),2) + pow((Px - x),2));
          
        }

        if(Shared->RG_movement!='A' && (Shared->table[y][x+1]!='-' && Shared->table[y][x+1]!='|' && Shared->table[y][x+1]!='{' && Shared->table[y][x+1]!='}' &&
            Shared->table[y][x+1]!='[' && Shared->table[y][x+1]!=']'))          
        {
            
            Ddis= (pow((Py - y),2) + pow(Px - (x+1),2));
          
        }

        if(Shared->RG_movement!='D' && (Shared->table[y][x-1]!='-' && Shared->table[y][x-1]!='|' && Shared->table[y][x-1]!='{' && Shared->table[y][x-1]!='}' &&
            Shared->table[y][x-1]!='[' && Shared->table[y][x-1]!=']'))          
        {
            
            Adis= (pow((Py - y),2) + pow(Px - (x-1),2));
          
        }
        
      
        int minDis = std::min({Wdis, Adis, Sdis, Ddis});



        if (Wdis == minDis ) 
        {
            Shared->RG_movement = 'W';
        } 
        else if (Adis == minDis) 
        {
            Shared->RG_movement = 'A';
        } 
        else if (Sdis == minDis )
        {
            Shared->RG_movement = 'S';
        } 
        else if (Ddis == minDis ) 
        {

            Shared->RG_movement = 'D';
        }
        
        
              Shared->RG_onblock=false;

        }
        else if(Shared->RG_mode=="Locked1")
        {
            if(Shared->key[0][0]==1 && Shared->key[1][0]==2  && Shared->locked_delay>=8)
            {
                Shared->RG_mode="Locked_out";
                Shared->key[0][0]=0;
                Shared->key[1][0]=0;
                Shared->locked_delay=0;
            }
        }
    pthread_mutex_unlock(&MUTEX_GE);

  

}


}