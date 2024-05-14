#pragma once

#include"table.h"
#include"maze.h"
#include"pacman.h"
#include"user_interface.h"
#include"Shared.h"
#include"ghost.h"
#include<thread>
#include<time.h>





void* game_engine_function(void* arg)
{
    
  Global_varibale* Shared=(Global_varibale*)(arg);



Ghost* RG=new Ghost("images/ALLSprites.png"); 
RG->SG.setTextureRect(IntRect(0,30,30,30));  

Ghost* PG=new Ghost("images/ALLSprites.png"); 
PG->SG.setTextureRect(IntRect(0,60,30,30));  

Ghost* BG=new Ghost("images/ALLSprites.png"); 
BG->SG.setTextureRect(IntRect(0,90,30,30)); 

Ghost* OG=new Ghost("images/ALLSprites.png"); 
OG->SG.setTextureRect(IntRect(0,120,30,30)); 

Grid* grid=new Grid();

pthread_mutex_lock(&MUTEX_GE);  
RG->SG.setPosition(Shared->RG_xcord,Shared->RG_ycord);
PG->SG.setPosition(Shared->PG_xcord,Shared->PG_ycord);
BG->SG.setPosition(Shared->BG_xcord,Shared->BG_ycord);
OG->SG.setPosition(Shared->OG_xcord,Shared->OG_ycord);
pthread_mutex_unlock(&MUTEX_GE);  

Pacman pacman;
RenderWindow window(VideoMode(34 * 25, 33 * 25), "PACMAN");
 Clock clock;

float F_timer=7;
float RG_key_timer=0;
float PG_key_timer=0;
float BG_key_timer=0;
float OG_key_timer=0;

int faster_count=2;

bool pallete_appear=0; 
int pallete_count=4;
float pallette_timer=0;

while(window.isOpen())
{
    Event event;


 float time = clock.getElapsedTime().asSeconds(); 
    clock.restart();
       
RG_key_timer+=time;
BG_key_timer+=time;
PG_key_timer+=time;
OG_key_timer+=time;

if(pallete_count==0 && pallete_appear==0)
{
    pallette_timer=0;
    pallete_appear=1;
}
pallette_timer+=time;


pthread_mutex_lock(&MUTEX_GE);

if(pallette_timer>=4 && pallete_count==0 && pallete_appear==1)
{
    Shared->table[3][1]='#';
    pallete_count++;
}
if(pallette_timer>=5 && pallete_count==1 && pallete_appear==1)
{
    Shared->table[3][26]='#';
    pallete_count++;
}
if(pallette_timer>=6 && pallete_count==2 && pallete_appear==1)
{
    Shared->table[23][1]='#';
    pallete_count++;
}
if(pallette_timer>=7 && pallete_count==3 && pallete_appear==1)
{
    Shared->table[23][26]='#';
    pallete_count=4;
    pallete_appear=0;
}

if(Shared->OG_mode!="Locked1"&&faster_count>0&&Shared->OG_faster!=1)
{
    Shared->OG_faster=1;
    faster_count--;
    cout<<"Orange "<<endl;
}
if(Shared->BG_mode!="Locked1"&&faster_count>0&&Shared->BG_faster!=1)
{
    Shared->BG_faster=1;
    faster_count--;
    cout<<"Blue "<<endl;
}
if(Shared->PG_mode!="Locked1"&&faster_count>0&&Shared->PG_faster!=1)
{
    Shared->PG_faster=1;
    faster_count--;
    cout<<"Pink "<<endl;
}
if(Shared->RG_mode!="Locked1"&&faster_count>0&&Shared->RG_faster!=1)
{
    Shared->RG_faster=1;
    faster_count--;
    cout<<"Red "<<endl;
}

Shared->locked_delay+=time;

if (Shared->BG_mode=="Frightened"||Shared->OG_mode=="Frightened"||Shared->PG_mode=="Frightened"||Shared->RG_mode=="Frightened")
{
     F_timer-=time;
}

if(RG_key_timer>=5)
{
    Shared->key[0][0]=1;
    Shared->key[1][0]=2;

}

if(PG_key_timer>=5)
{
    Shared->key[1][0]=2;
    Shared->key[1][1]=1;

}

if(BG_key_timer>=5)
{
    Shared->key[0][1]=2;
    Shared->key[1][1]=1;

}

if(OG_key_timer>=5)
{
    Shared->key[0][0]=1;
    Shared->key[0][1]=2;

}

if(F_timer<=0)
{
    F_timer=7;
    if(Shared->BG_mode!="Locked"&&Shared->BG_mode!="Locked1")
    {
        Shared->BG_mode="Target";
    }
     if(Shared->RG_mode!="Locked"&&Shared->RG_mode!="Locked1")
    {
        Shared->RG_mode="Target";
    }
     if(Shared->OG_mode!="Locked"&&Shared->OG_mode!="Locked1")
    {
        Shared->OG_mode="Target";
    }
     if(Shared->PG_mode!="Locked"&&Shared->PG_mode!="Locked1")
    {
        Shared->PG_mode="Target";
    }
}

pthread_mutex_unlock(&MUTEX_GE);

    while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                std::cout << "Window closed" << std::endl;
                window.close();
            }
        }










FloatRect pacman_box = pacman.SP.getGlobalBounds();
Vector2f NextPos = pacman.SP.getPosition();




//  CURRENT MOVEMENT

NextPos = pacman.SP.getPosition();

pthread_mutex_lock(&MUTEX_GE);
char CM=Shared->movement;



if(CM=='W')
{

    NextPos.y -= 1.25;      
    FloatRect targetBox(NextPos.x, NextPos.y, pacman_box.width, pacman_box.height);
    if(grid->checkCollision(Shared->table,targetBox)==0)
    {  
    pacman.SP.setPosition(pacman.SP.getPosition().x,pacman.SP.getPosition().y-1.25);  
    }  
    
    
}
else if(CM=='A')
{
    NextPos.x -= 1.25; 
    FloatRect targetBox(NextPos.x, NextPos.y, pacman_box.width, pacman_box.height);
    if(grid->checkCollision(Shared->table,targetBox)==0)
    {  
   pacman.SP.setPosition(pacman.SP.getPosition().x-1.25,pacman.SP.getPosition().y);  
    }        
        
}
else if(CM=='S')
{
    NextPos.y += 1.25;
    FloatRect targetBox(NextPos.x, NextPos.y, pacman_box.width, pacman_box.height);
    if(grid->checkCollision(Shared->table,targetBox)==0)
    {  
      pacman.SP.setPosition(pacman.SP.getPosition().x,pacman.SP.getPosition().y+1.25);   
    }  
      
         
}
else if(CM=='D')
{
    NextPos.x += 1.25;    
    FloatRect targetBox(NextPos.x, NextPos.y, pacman_box.width, pacman_box.height);
    if(grid->checkCollision(Shared->table,targetBox)==0)
    {  
      pacman.SP.setPosition(pacman.SP.getPosition().x+1.25,pacman.SP.getPosition().y);   
    }   
  

           
}

FloatRect targetBox(pacman.SP.getPosition().x, pacman.SP.getPosition().y, pacman_box.width, pacman_box.height);
if(grid->PacmanPallete(Shared->table,targetBox))
{
    pallete_count--;

    if(Shared->BG_mode=="Frightened" || Shared->RG_mode=="Frightened" || Shared->OG_mode=="Frightened" || Shared->PG_mode=="Frightened")
    {
        F_timer+=7;
    }
    

    if(Shared->RG_mode!="Locked" && Shared->RG_mode!="Locked1")
    {
        Shared->RG_mode="Frightened";
    }
    if(Shared->PG_mode!="Locked" &&Shared->PG_mode!="Locked1")
    {
        Shared->PG_mode="Frightened";
    }
    if(Shared->BG_mode!="Locked" &&Shared->BG_mode!="Locked1")
    {
        Shared->BG_mode="Frightened";
    }
    if(Shared->OG_mode!="Locked" &&Shared->OG_mode!="Locked1")
    {
        Shared->OG_mode="Frightened";
    }
}

pthread_mutex_unlock(&MUTEX_GE);  

///////////////////
// Ghost colloision
///////////////////

pthread_mutex_lock(&MUTEX_GE);  
FloatRect pacman1 = pacman.SP.getGlobalBounds();
FloatRect RghostRectC = RG->SG.getGlobalBounds();
if(grid->Ghost_coll(pacman1,RghostRectC)&&Shared->RG_mode=="Frightened")
{
    Shared->RG_mode="Locked";
}
else if(grid->Ghost_coll(pacman1,RghostRectC)&&Shared->RG_mode=="Target")
{
     //Pacman Dies
}
FloatRect BghostRectC = BG->SG.getGlobalBounds();
if(grid->Ghost_coll(pacman1,BghostRectC)&&Shared->BG_mode=="Frightened")
{
    Shared->BG_mode="Locked";
}
else if(grid->Ghost_coll(pacman1,BghostRectC)&&Shared->BG_mode=="Target")
{
     //Pacman Dies
}
FloatRect PghostRectC = PG->SG.getGlobalBounds();
if(grid->Ghost_coll(pacman1,PghostRectC)&&Shared->PG_mode=="Frightened")
{
    Shared->PG_mode="Locked";
}
else if(grid->Ghost_coll(pacman1,PghostRectC)&&Shared->PG_mode=="Target")
{
     //Pacman Dies
}
FloatRect OghostRectC = OG->SG.getGlobalBounds();
if(grid->Ghost_coll(pacman1,OghostRectC)&&Shared->OG_mode=="Frightened")
{
    Shared->OG_mode="Locked";
}
else if(grid->Ghost_coll(pacman1,OghostRectC)&&Shared->OG_mode=="Target")
{
     //Pacman Dies
}

pthread_mutex_unlock(&MUTEX_GE);  




//////////////////
//Ghost movement
/////////////////

//RED

FloatRect ghostRect;
pthread_mutex_lock(&MUTEX_GE);

if(Shared->RG_mode=="Locked_out")
{
    RG->SG.setPosition(17*25,13*25);
    Shared->RG_mode="Target";
    Shared->RG_onblock=true;
    RG_key_timer=0;
}

ghostRect.width=25;
ghostRect.height=25;
if(Shared->RG_onblock==false && Shared->RG_mode!="Locked1")
{
    float Speed;
    if(Shared->RG_faster==1)
    {
        Speed=1.25;
    }
    else
    {
        Speed=1;
    }
    
    if(Shared->RG_movement=='W')
    {
        
        RG->SG.setPosition(RG->SG.getPosition().x,RG->SG.getPosition().y-Speed);
        ghostRect.left = RG->SG.getPosition().x;  
        ghostRect.top = RG->SG.getPosition().y;   

        if(grid->isGhostOnBlock(Shared->table,ghostRect)==true)
        {

            Shared->RG_xcord=RG->SG.getPosition().x/25-3;
            Shared->RG_ycord=RG->SG.getPosition().y/25-2;
            Shared->RG_onblock=true;
        }

    }

    else if(Shared->RG_movement=='D')
    {
   
        RG->SG.setPosition(RG->SG.getPosition().x+Speed,RG->SG.getPosition().y);
        ghostRect.left = RG->SG.getPosition().x;  
        ghostRect.top = RG->SG.getPosition().y;   

        if(grid->isGhostOnBlock(Shared->table,ghostRect)==true)
        {
            Shared->RG_xcord=RG->SG.getPosition().x/25-3;
            Shared->RG_ycord=RG->SG.getPosition().y/25-2;

            Shared->RG_onblock=true;
        }

    }
    else if(Shared->RG_movement=='S')
    {
  
        RG->SG.setPosition(RG->SG.getPosition().x,RG->SG.getPosition().y+Speed);
        ghostRect.left = RG->SG.getPosition().x;  
        ghostRect.top = RG->SG.getPosition().y;   

        if(grid->isGhostOnBlock(Shared->table,ghostRect)==true)
        {
            Shared->RG_xcord=RG->SG.getPosition().x/25-3;
            Shared->RG_ycord=RG->SG.getPosition().y/25-2;
            Shared->RG_onblock=true;
        }

    }
    else if (Shared->RG_movement=='A')
    {
   
        RG->SG.setPosition(RG->SG.getPosition().x-Speed,RG->SG.getPosition().y);
        ghostRect.left = RG->SG.getPosition().x;  
        ghostRect.top = RG->SG.getPosition().y;   

        if(grid->isGhostOnBlock(Shared->table,ghostRect)==true)
        {
            Shared->RG_xcord=RG->SG.getPosition().x/25-3;
            Shared->RG_ycord=RG->SG.getPosition().y/25-2;
            Shared->RG_onblock=true;
        }

    }
   
}

pthread_mutex_unlock(&MUTEX_GE);  


//PINK

FloatRect PghostRect;
pthread_mutex_lock(&MUTEX_GE);

if(Shared->PG_mode=="Locked_out")
{
    PG->SG.setPosition(17*25,13*25);
    Shared->PG_mode="Target";
    Shared->PG_onblock=true;
    PG_key_timer=0;
}

PghostRect.width=25;
PghostRect.height=25;
if(Shared->PG_onblock==false && Shared->PG_mode!="Locked1")
{
    float Speed;
    if(Shared->PG_faster==1)
    {
        Speed=1.25;
    }
    else
    {
        Speed=1;
    }
    

    if(Shared->PG_movement=='W')
    {

        PG->SG.setPosition(PG->SG.getPosition().x,PG->SG.getPosition().y-Speed);
        PghostRect.left = PG->SG.getPosition().x;  
        PghostRect.top = PG->SG.getPosition().y;   

        if(grid->isGhostOnBlock(Shared->table,PghostRect)==true)
        {

            Shared->PG_xcord=PG->SG.getPosition().x/25-3;
            Shared->PG_ycord=PG->SG.getPosition().y/25-2;
            Shared->PG_onblock=true;
        }

    }

    else if(Shared->PG_movement=='D')
    {
   
        PG->SG.setPosition(PG->SG.getPosition().x+Speed,PG->SG.getPosition().y);
        PghostRect.left = PG->SG.getPosition().x;  
        PghostRect.top = PG->SG.getPosition().y;   

        if(grid->isGhostOnBlock(Shared->table,PghostRect)==true)
        {
            Shared->PG_xcord=PG->SG.getPosition().x/25-3;
            Shared->PG_ycord=PG->SG.getPosition().y/25-2;

            Shared->PG_onblock=true;
        }

    }
    else if(Shared->PG_movement=='S')
    {
  
        PG->SG.setPosition(PG->SG.getPosition().x,PG->SG.getPosition().y+Speed);
        PghostRect.left = PG->SG.getPosition().x;  
        PghostRect.top = PG->SG.getPosition().y;   

        if(grid->isGhostOnBlock(Shared->table,PghostRect)==true)
        {
            Shared->PG_xcord=PG->SG.getPosition().x/25-3;
            Shared->PG_ycord=PG->SG.getPosition().y/25-2;
            Shared->PG_onblock=true;
        }

    }
    else if (Shared->PG_movement=='A')
    {
   
        PG->SG.setPosition(PG->SG.getPosition().x-Speed,PG->SG.getPosition().y);
        PghostRect.left = PG->SG.getPosition().x;  
        PghostRect.top = PG->SG.getPosition().y;   

        if(grid->isGhostOnBlock(Shared->table,PghostRect)==true)
        {
            Shared->PG_xcord=PG->SG.getPosition().x/25-3;
            Shared->PG_ycord=PG->SG.getPosition().y/25-2;
            Shared->PG_onblock=true;
        }

    }
   
}
pthread_mutex_unlock(&MUTEX_GE);  

//BLUE
FloatRect BghostRect;
pthread_mutex_lock(&MUTEX_GE);

if(Shared->BG_mode=="Locked_out")
{
    BG->SG.setPosition(17*25,13*25);
    Shared->BG_mode="Target";
    Shared->BG_onblock=true;
    BG_key_timer=0;
}

BghostRect.width=25;
BghostRect.height=25;
if(Shared->BG_onblock==false && Shared->BG_mode!="Locked1")
{
    float Speed;
    if(Shared->BG_faster==1)
    {
        Speed=1.25;
    }
    else
    {
        Speed=1;
    }
    
    if(Shared->BG_movement=='W')
    {

        BG->SG.setPosition(BG->SG.getPosition().x,BG->SG.getPosition().y-Speed);
        BghostRect.left = BG->SG.getPosition().x;  
        BghostRect.top = BG->SG.getPosition().y;   

        if(grid->isGhostOnBlock(Shared->table,BghostRect)==true)
        {

            Shared->BG_xcord=BG->SG.getPosition().x/25-3;
            Shared->BG_ycord=BG->SG.getPosition().y/25-2;
            Shared->BG_onblock=true;
        }

    }

    else if(Shared->BG_movement=='D')
    {
   
        BG->SG.setPosition(BG->SG.getPosition().x+Speed,BG->SG.getPosition().y);
        BghostRect.left = BG->SG.getPosition().x;  
        BghostRect.top = BG->SG.getPosition().y;   

        if(grid->isGhostOnBlock(Shared->table,BghostRect)==true)
        {
            Shared->BG_xcord=BG->SG.getPosition().x/25-3;
            Shared->BG_ycord=BG->SG.getPosition().y/25-2;

            Shared->BG_onblock=true;
        }

    }
    else if(Shared->BG_movement=='S')
    {
  
        BG->SG.setPosition(BG->SG.getPosition().x,BG->SG.getPosition().y+Speed);
        BghostRect.left = BG->SG.getPosition().x;  
        BghostRect.top = BG->SG.getPosition().y;   

        if(grid->isGhostOnBlock(Shared->table,BghostRect)==true)
        {
            Shared->BG_xcord=BG->SG.getPosition().x/25-3;
            Shared->BG_ycord=BG->SG.getPosition().y/25-2;
            Shared->BG_onblock=true;
        }

    }
    else if (Shared->BG_movement=='A')
    {
   
        BG->SG.setPosition(BG->SG.getPosition().x-Speed,BG->SG.getPosition().y);
        BghostRect.left = BG->SG.getPosition().x;  
        BghostRect.top = BG->SG.getPosition().y;   

        if(grid->isGhostOnBlock(Shared->table,BghostRect)==true)
        {
            Shared->BG_xcord=BG->SG.getPosition().x/25-3;
            Shared->BG_ycord=BG->SG.getPosition().y/25-2;
            Shared->BG_onblock=true;
        }

    }
   
}
pthread_mutex_unlock(&MUTEX_GE);  

//Orange

FloatRect OghostRect;
pthread_mutex_lock(&MUTEX_GE);

if(Shared->OG_mode=="Locked_out")
{
    OG->SG.setPosition(17*25,13*25);
    Shared->OG_mode="Target";
    Shared->OG_onblock=true;
    OG_key_timer=0;
}

OghostRect.width=25;
OghostRect.height=25;
if(Shared->OG_onblock==false && Shared->OG_mode!="Locked1")
{
    float Speed;
    if(Shared->OG_faster==1)
    {
        Speed=1.25;
    }
    else
    {
        Speed=1;
    }
    

    if(Shared->OG_movement=='W')
    {

        OG->SG.setPosition(OG->SG.getPosition().x,OG->SG.getPosition().y-Speed);
        OghostRect.left = OG->SG.getPosition().x;  
        OghostRect.top = OG->SG.getPosition().y;   

        if(grid->isGhostOnBlock(Shared->table,OghostRect)==true)
        {

            Shared->OG_xcord=OG->SG.getPosition().x/25-3;
            Shared->OG_ycord=OG->SG.getPosition().y/25-2;
            Shared->OG_onblock=true;
        }

    }

    else if(Shared->OG_movement=='D')
    {
   
        OG->SG.setPosition(OG->SG.getPosition().x+Speed,OG->SG.getPosition().y);
        OghostRect.left = OG->SG.getPosition().x;  
        OghostRect.top = OG->SG.getPosition().y;   

        if(grid->isGhostOnBlock(Shared->table,OghostRect)==true)
        {
            Shared->OG_xcord=OG->SG.getPosition().x/25-3;
            Shared->OG_ycord=OG->SG.getPosition().y/25-2;

            Shared->OG_onblock=true;
        }

    }
    else if(Shared->OG_movement=='S')
    {
  
        OG->SG.setPosition(OG->SG.getPosition().x,OG->SG.getPosition().y+Speed);
        OghostRect.left = OG->SG.getPosition().x;  
        OghostRect.top = OG->SG.getPosition().y;   

        if(grid->isGhostOnBlock(Shared->table,OghostRect)==true)
        {
            Shared->OG_xcord=OG->SG.getPosition().x/25-3;
            Shared->OG_ycord=OG->SG.getPosition().y/25-2;
            Shared->OG_onblock=true;
        }

    }
    else if (Shared->OG_movement=='A')
    {
   
        OG->SG.setPosition(OG->SG.getPosition().x-Speed,OG->SG.getPosition().y);
        OghostRect.left = OG->SG.getPosition().x;  
        OghostRect.top = OG->SG.getPosition().y;   

        if(grid->isGhostOnBlock(Shared->table,OghostRect)==true)
        {
            Shared->OG_xcord=OG->SG.getPosition().x/25-3;
            Shared->OG_ycord=OG->SG.getPosition().y/25-2;
            Shared->OG_onblock=true;
        }

    }
   
}
pthread_mutex_unlock(&MUTEX_GE);  


pthread_mutex_lock(&MUTEX_GE);  
//getting into the lcoked area
FloatRect GHOST_LOCKED=RG->SG.getGlobalBounds();
if(Shared->RG_mode=="Locked")
{
    if(grid->Get_locked(GHOST_LOCKED))
    {
       if(Shared->RG_faster==1)
       {
        Shared->RG_faster=0;
        faster_count++;
       } 
       Shared->RG_mode="Locked1";
        RG_key_timer=0;
       RG->SG.setPosition((16+3)*25,(14+2)*25);
    }
}
GHOST_LOCKED=OG->SG.getGlobalBounds();
if(Shared->OG_mode=="Locked")
{
    if(grid->Get_locked(GHOST_LOCKED))
    {
        if(Shared->OG_faster==1)
       {
        Shared->OG_faster=0;
        faster_count++;
       } 
       Shared->OG_mode="Locked1";
        OG_key_timer=0;
       OG->SG.setPosition((15+3)*25,(14+2)*25);
    }
}
GHOST_LOCKED=BG->SG.getGlobalBounds();
if(Shared->BG_mode=="Locked")
{
    if(grid->Get_locked(GHOST_LOCKED))
    {
        if(Shared->BG_faster==1)
       {
        Shared->BG_faster=0;
        faster_count++;
       } 
       Shared->BG_mode="Locked1";
        BG_key_timer=0;
       BG->SG.setPosition((14+3)*25,(14+2)*25);
    }
}
GHOST_LOCKED=PG->SG.getGlobalBounds();
if(Shared->PG_mode=="Locked")
{
    if(grid->Get_locked(GHOST_LOCKED))
    {
        if(Shared->PG_faster==1)
       {
        Shared->PG_faster=0;
        faster_count++;
       } 
       Shared->PG_mode="Locked1";
       PG_key_timer=0;
       PG->SG.setPosition((13+3)*25,(14+2)*25);
    }
}
pthread_mutex_unlock(&MUTEX_GE);  

//teleportaion through tunnel

if(pacman.SP.getPosition().x >= 710 && pacman.SP.getPosition().x < 720 && pacman.SP.getPosition().y==400)
{

    pacman.SP.setPosition(90,400);
}
else if(pacman.SP.getPosition().x >= 70 && pacman.SP.getPosition().x < 80 && pacman.SP.getPosition().y==400)
{

    pacman.SP.setPosition(690,400);
}

if(RG->SG.getPosition().x >= 710 && RG->SG.getPosition().x < 720 && RG->SG.getPosition().y==400)
{
    RG->SG.setPosition(90,400);


}
else if(RG->SG.getPosition().x >= 70  && RG->SG.getPosition().x < 80  && RG->SG.getPosition().y==400)
{

   RG->SG.setPosition(690,400);
}

if(PG->SG.getPosition().x >= 710 && PG->SG.getPosition().x < 720 && PG->SG.getPosition().y==400)
{
    PG->SG.setPosition(90,400);


}
else if(PG->SG.getPosition().x >= 70  && PG->SG.getPosition().x < 80  && PG->SG.getPosition().y==400)
{

   PG->SG.setPosition(690,400);
}

if(BG->SG.getPosition().x >= 710 && BG->SG.getPosition().x < 720 && BG->SG.getPosition().y==400)
{
    BG->SG.setPosition(90,400);


}
else if(BG->SG.getPosition().x >= 70  && BG->SG.getPosition().x < 80  && BG->SG.getPosition().y==400)
{

   BG->SG.setPosition(690,400);
}

if(OG->SG.getPosition().x >= 710 && OG->SG.getPosition().x < 720 && OG->SG.getPosition().y==400)
{
    OG->SG.setPosition(90,400);


}
else if(OG->SG.getPosition().x >= 70  && OG->SG.getPosition().x < 80  && OG->SG.getPosition().y==400)
{

   OG->SG.setPosition(690,400);
}



//  NEXT MOVEMENT



NextPos = pacman.SP.getPosition();
pthread_mutex_lock(&MUTEX_GE);
if(Shared->next_movement=='W')
{

    NextPos.y -= 1.25;      
    FloatRect targetBox(NextPos.x, NextPos.y, pacman_box.width, pacman_box.height);
    if(grid->checkCollision(Shared->table,targetBox)==0)
    {  
    Shared->movement=Shared->next_movement;  
    }  
    
    
}
else if(Shared->next_movement=='A')
{
    NextPos.x -= 1.25; 
    FloatRect targetBox(NextPos.x, NextPos.y, pacman_box.width, pacman_box.height);
    if(grid->checkCollision(Shared->table,targetBox)==0)
    {  
    Shared->movement=Shared->next_movement;
    }        
        
}
else if(Shared->next_movement=='S')
{
    NextPos.y += 1.25;
    FloatRect targetBox(NextPos.x, NextPos.y, pacman_box.width, pacman_box.height);
    if(grid->checkCollision(Shared->table,targetBox)==0)
    {  
     Shared->movement=Shared->next_movement; 
    }  
      
         
}
else if(Shared->next_movement=='D')
{
    NextPos.x += 1.25;    
    FloatRect targetBox(NextPos.x, NextPos.y, pacman_box.width, pacman_box.height);
    if(grid->checkCollision(Shared->table,targetBox)==0)
    {  
     Shared->movement=Shared->next_movement;
    }   
  
}




pthread_mutex_unlock(&MUTEX_GE); 



//////////////////////////////////////

//      Animations


pthread_mutex_lock(&MUTEX_GE); 

if(Shared->OG_mode=="Target"||Shared->OG_mode=="Locked")
{
if(Shared->OG_movement=='W')
{  
    OG->SG.setTextureRect(IntRect(120,120,30,30)); 
}
else if(Shared->OG_movement=='A')
{  
    OG->SG.setTextureRect(IntRect(180,120,30,30)); 
}
else if(Shared->OG_movement=='S')
{  
    OG->SG.setTextureRect(IntRect(60,120,30,30)); 
}
else if(Shared->OG_movement=='D')
{  
    OG->SG.setTextureRect(IntRect(0,120,30,30)); 
}
}
else if(Shared->OG_mode=="Frightened")
{
     OG->SG.setTextureRect(IntRect(0,150,30,30)); 
}

if(Shared->RG_mode=="Target"||Shared->RG_mode=="Locked")
{
if(Shared->RG_movement=='W')
{  
    RG->SG.setTextureRect(IntRect(120,30,30,30)); 
}
else if(Shared->RG_movement=='A')
{  
    RG->SG.setTextureRect(IntRect(180,30,30,30)); 
}
else if(Shared->RG_movement=='S')
{  
    RG->SG.setTextureRect(IntRect(60,30,30,30)); 
}
else if(Shared->RG_movement=='D')
{  
    RG->SG.setTextureRect(IntRect(0,30,30,30)); 
}
}
else if(Shared->RG_mode=="Frightened")
{
     RG->SG.setTextureRect(IntRect(0,150,30,30)); 
}

if(Shared->PG_mode=="Target"||Shared->PG_mode=="Locked")
{
if(Shared->PG_movement=='W')
{  
    PG->SG.setTextureRect(IntRect(120,60,30,30)); 
}
else if(Shared->PG_movement=='A')
{  
    PG->SG.setTextureRect(IntRect(180,60,30,30)); 
}
else if(Shared->PG_movement=='S')
{  
    PG->SG.setTextureRect(IntRect(60,60,30,30)); 
}
else if(Shared->PG_movement=='D')
{  
    PG->SG.setTextureRect(IntRect(0,60,30,30)); 
}
}
else if(Shared->PG_mode=="Frightened")
{
     PG->SG.setTextureRect(IntRect(0,150,30,30)); 
}

if(Shared->BG_mode=="Target"||Shared->BG_mode=="Locked")
{
if(Shared->BG_movement=='W')
{  
    BG->SG.setTextureRect(IntRect(120,90,30,30)); 
}
else if(Shared->BG_movement=='A')
{  
    BG->SG.setTextureRect(IntRect(180,90,30,30)); 
}
else if(Shared->BG_movement=='S')
{  
    BG->SG.setTextureRect(IntRect(60,90,30,30)); 
}
else if(Shared->BG_movement=='D')
{  
    BG->SG.setTextureRect(IntRect(0,90,30,30)); 
}
}
else if(Shared->BG_mode=="Frightened")
{
     BG->SG.setTextureRect(IntRect(0,150,30,30)); 
}

pthread_mutex_unlock(&MUTEX_GE); 
///////////////////////////////////


window.clear();

pthread_mutex_lock(&MUTEX_GE);
grid->drawtable(Shared->table,window);

pthread_mutex_unlock(&MUTEX_GE); 

window.draw(grid->FrontS);
window.draw(pacman.SP);
window.draw(RG->SG);
window.draw(PG->SG);
window.draw(BG->SG);
window.draw(OG->SG);
window.display();

}




pthread_mutex_destroy(&MUTEX_GE);

}
