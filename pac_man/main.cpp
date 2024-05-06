
 #include <X11/Xlib.h>

#undef Drawable
#undef Window
#undef Font
#undef Status
#undef None
#undef Default

#include<iostream>
#include<pthread.h>
#include<unistd.h>

using namespace std;

#include"Shared.h"
#include"game_engine.h"
#include"user_interface.h"

//  thread for each one of the requirement

pthread_t game_engine;
pthread_t user_int;
/*pthread_t ghost;
*/
int main()
{
Global_varibale* Shared=new Global_varibale();

XInitThreads();  
pthread_create(&game_engine,NULL,game_engine_function,(void*)&Shared);
pthread_create(&user_int,NULL,User_interface,(void*)&Shared);
 
 while(1)
 {


 }

return 0;
}