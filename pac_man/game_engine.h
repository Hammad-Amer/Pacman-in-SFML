#pragma once

#include"table.h"
#include"maze.h"
#include"pacman.h"
#include"user_interface.h"
#include"Shared.h"
#include"ghost.h"
#include<thread>

pthread_mutex_t MUTEX_GE=PTHREAD_MUTEX_INITIALIZER;

void* game_engine_function(void* arg)
{
    
  Global_varibale* Shared=(Global_varibale*)(arg);



Ghost* RG=new Ghost("images/ALLSprites.png"); 
RG->SG.setTextureRect(IntRect(30,30,30,30));  
Grid* grid=new Grid();

pthread_mutex_unlock(&MUTEX_GE);  
RG->SG.setPosition(Shared->RG_xcord,Shared->RG_ycord);
pthread_mutex_unlock(&MUTEX_GE);  

Pacman pacman;
RenderWindow window(VideoMode(34 * 25, 33 * 25), "PACMAN");




while(window.isOpen())
{
    Event event;
    while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                std::cout << "Window closed" << std::endl;
                window.close();
            }
        }
//window.clear();

FloatRect pacman_box = pacman.SP.getGlobalBounds();
Vector2f NextPos = pacman.SP.getPosition();




//  CURRENT MOVEMENT

NextPos = pacman.SP.getPosition();

pthread_mutex_lock(&MUTEX_GE);
char CM=Shared->movement;



if(CM=='W')
{

    NextPos.y -= 1;      
    FloatRect targetBox(NextPos.x, NextPos.y, pacman_box.width, pacman_box.height);
    if(grid->checkCollision(Shared->table,targetBox)==0)
    {  
    pacman.SP.setPosition(pacman.SP.getPosition().x,pacman.SP.getPosition().y-1);  
    }  
    
    
}
else if(CM=='A')
{
    NextPos.x -= 1; 
    FloatRect targetBox(NextPos.x, NextPos.y, pacman_box.width, pacman_box.height);
    if(grid->checkCollision(Shared->table,targetBox)==0)
    {  
   pacman.SP.setPosition(pacman.SP.getPosition().x-1,pacman.SP.getPosition().y);  
    }        
        
}
else if(CM=='S')
{
    NextPos.y += 1;
    FloatRect targetBox(NextPos.x, NextPos.y, pacman_box.width, pacman_box.height);
    if(grid->checkCollision(Shared->table,targetBox)==0)
    {  
      pacman.SP.setPosition(pacman.SP.getPosition().x,pacman.SP.getPosition().y+1);   
    }  
      
         
}
else if(CM=='D')
{
    NextPos.x += 1;    
    FloatRect targetBox(NextPos.x, NextPos.y, pacman_box.width, pacman_box.height);
    if(grid->checkCollision(Shared->table,targetBox)==0)
    {  
      pacman.SP.setPosition(pacman.SP.getPosition().x+1,pacman.SP.getPosition().y);   
    }   
  
           
}
pthread_mutex_unlock(&MUTEX_GE);  

//Ghost movement

FloatRect ghostRect;
pthread_mutex_lock(&MUTEX_GE);

ghostRect.width=25;
ghostRect.height=25;
if(Shared->RG_onblock==false)
{
    
    if(Shared->RG_movement=='W')
    {

        RG->SG.setPosition(RG->SG.getPosition().x,RG->SG.getPosition().y-1);
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
   
        RG->SG.setPosition(RG->SG.getPosition().x+1,RG->SG.getPosition().y);
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
  
        RG->SG.setPosition(RG->SG.getPosition().x,RG->SG.getPosition().y+1);
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
   
        RG->SG.setPosition(RG->SG.getPosition().x-1,RG->SG.getPosition().y);
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



//  NEXT MOVEMENT



NextPos = pacman.SP.getPosition();
pthread_mutex_lock(&MUTEX_GE);
if(Shared->next_movement=='W')
{

    NextPos.y -= 1;      
    FloatRect targetBox(NextPos.x, NextPos.y, pacman_box.width, pacman_box.height);
    if(grid->checkCollision(Shared->table,targetBox)==0)
    {  
    Shared->movement=Shared->next_movement;  
    }  
    
    
}
else if(Shared->next_movement=='A')
{
    NextPos.x -= 1; 
    FloatRect targetBox(NextPos.x, NextPos.y, pacman_box.width, pacman_box.height);
    if(grid->checkCollision(Shared->table,targetBox)==0)
    {  
    Shared->movement=Shared->next_movement;
    }        
        
}
else if(Shared->next_movement=='S')
{
    NextPos.y += 1;
    FloatRect targetBox(NextPos.x, NextPos.y, pacman_box.width, pacman_box.height);
    if(grid->checkCollision(Shared->table,targetBox)==0)
    {  
     Shared->movement=Shared->next_movement; 
    }  
      
         
}
else if(Shared->next_movement=='D')
{
    NextPos.x += 1;    
    FloatRect targetBox(NextPos.x, NextPos.y, pacman_box.width, pacman_box.height);
    if(grid->checkCollision(Shared->table,targetBox)==0)
    {  
     Shared->movement=Shared->next_movement;
    }   
  
}




pthread_mutex_unlock(&MUTEX_GE); 



window.clear();

pthread_mutex_lock(&MUTEX_GE);
grid->drawtable(Shared->table,window);

pthread_mutex_unlock(&MUTEX_GE); 

window.draw(grid->FrontS);
window.draw(pacman.SP);
window.draw(RG->SG);
window.display();
}




pthread_mutex_destroy(&MUTEX_GE);

}
