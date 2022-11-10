#ifndef FSM_REFID_H
#define FSM_REFID_H

void * rfid_read (void * p);
void * rfid_read_wait (void * p); 
void * rfid_display (void * p);
void * rfid_display_wait (void * p);

#endif
