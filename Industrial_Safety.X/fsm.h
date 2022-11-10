#ifndef FSM_H
#define FSM_H

#include "fsm_rfid.h"

//#define NEXT_STATE          ((FSM*)p)->func

typedef struct fsmT
{
    void * (* func)(void * p);
    void * arg;
} FSM;


#endif
