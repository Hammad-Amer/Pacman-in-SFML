#pragma once

#include"table.h"
#include"maze.h"
#include"pacman.h"
#include"user_interface.h"
#include"Shared.h"

pthread_mutex_t MUTEX_GE=PTHREAD_MUTEX_INITIALIZER;

void* game_engine_function(void* arg)
{
  Global_varibale* Shared; 
 Shared=(Global_varibale*)(arg);

  Maze* maze=new Maze();

Grid* grid=new Grid();
Pacman pacman;
RenderWindow window(VideoMode(34 * 25, 33 * 25), "PACMAN");
cout<<"o"<<endl;
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
pthread_mutex_unlock(&MUTEX_GE);  

if(CM=='W')
{

    NextPos.y -= 0.5;      
    FloatRect targetBox(NextPos.x, NextPos.y, pacman_box.width, pacman_box.height);
    if(grid->checkCollision(maze->table,targetBox)==0)
    {  
    pacman.SP.setPosition(pacman.SP.getPosition().x,pacman.SP.getPosition().y-1);  
    }  
    
    
}
else if(CM=='A')
{
    NextPos.x -= 0.5; 
    FloatRect targetBox(NextPos.x, NextPos.y, pacman_box.width, pacman_box.height);
    if(grid->checkCollision(maze->table,targetBox)==0)
    {  
   pacman.SP.setPosition(pacman.SP.getPosition().x-1,pacman.SP.getPosition().y);  
    }        
        
}
else if(CM=='S')
{
    NextPos.y += 0.5;
    FloatRect targetBox(NextPos.x, NextPos.y, pacman_box.width, pacman_box.height);
    if(grid->checkCollision(maze->table,targetBox)==0)
    {  
      pacman.SP.setPosition(pacman.SP.getPosition().x,pacman.SP.getPosition().y+1);   
    }  
      
         
}
else if(CM=='D')
{
    NextPos.x += 0.5;    
    FloatRect targetBox(NextPos.x, NextPos.y, pacman_box.width, pacman_box.height);
    if(grid->checkCollision(maze->table,targetBox)==0)
    {  
      pacman.SP.setPosition(pacman.SP.getPosition().x+1,pacman.SP.getPosition().y);   
    }   
  
           
}


//  NEXT MOVEMENT





NextPos = pacman.SP.getPosition();
pthread_mutex_lock(&MUTEX_GE);
if(Shared->next_movement=='W')
{

    NextPos.y -= 0.5;      
    FloatRect targetBox(NextPos.x, NextPos.y, pacman_box.width, pacman_box.height);
    if(grid->checkCollision(maze->table,targetBox)==0)
    {  
    Shared->movement=Shared->next_movement;  
    }  
    
    
}
else if(Shared->next_movement=='A')
{
    NextPos.x -= 0.5; 
    FloatRect targetBox(NextPos.x, NextPos.y, pacman_box.width, pacman_box.height);
    if(grid->checkCollision(maze->table,targetBox)==0)
    {  
    Shared->movement=Shared->next_movement;
    }        
        
}
else if(Shared->next_movement=='S')
{
    NextPos.y += 0.5;
    FloatRect targetBox(NextPos.x, NextPos.y, pacman_box.width, pacman_box.height);
    if(grid->checkCollision(maze->table,targetBox)==0)
    {  
     Shared->movement=Shared->next_movement; 
    }  
      
         
}
else if(Shared->next_movement=='D')
{
    NextPos.x += 0.5;    
    FloatRect targetBox(NextPos.x, NextPos.y, pacman_box.width, pacman_box.height);
    if(grid->checkCollision(maze->table,targetBox)==0)
    {  
     Shared->movement=Shared->next_movement;
    }   
  
}       
pthread_mutex_unlock(&MUTEX_GE);  
window.clear();
grid->drawtable(maze->table,window);
window.draw(grid->FrontS);
window.draw(pacman.SP);

window.display();
}





}
