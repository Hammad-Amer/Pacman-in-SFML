
#include <X11/Xlib.h>

#undef Drawable
#undef Window
#undef Font
#undef Status
#undef None
#undef Default

#include <iostream>
#include <pthread.h>
#include <unistd.h>

using namespace std;

pthread_mutex_t MUTEX_GE = PTHREAD_MUTEX_INITIALIZER;

#include "Shared.h"
#include "game_engine.h"
#include "user_interface.h"
#include "Ghost1_f.h"
#include "Ghost2_f.h"
#include "Ghost3_f.h"
#include "Ghost4_f.h"
#include "maze.h"

//  thread for each one of the requirement

pthread_t game_engine;
pthread_t user_int;
pthread_t ghost1;
pthread_t ghost2;
pthread_t ghost3;
pthread_t ghost4;

int main()
{

    Global_varibale *Shared = new Global_varibale();

    XInitThreads();
    pthread_create(&game_engine, NULL, game_engine_function, (void *)Shared);
    pthread_create(&user_int, NULL, User_interface, (void *)Shared);
    pthread_create(&ghost1, NULL, Ghost1_f, (void *)Shared);
    pthread_create(&ghost2, NULL, Ghost2_f, (void *)Shared);
    pthread_create(&ghost3, NULL, Ghost3_f, (void *)Shared);
    pthread_create(&ghost4, NULL, Ghost4_f, (void *)Shared);

    while (1)
    {
        sleep(10);
        if (Shared->game_closed == true)
            break;
    }

    return 0;
}