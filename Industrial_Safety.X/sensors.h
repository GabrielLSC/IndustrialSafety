#ifndef SENSORS_H
#define SENSORS_H

#define AVISO          PORTCbits.RC0
#define PRS_IN         PORTAbits.RA3
#define UTS_TRIGGER    PORTAbits.RA2
#define PERIGO         PORTCbits.RC1

extern long time;
extern long dist;

void sensors_init (void);
unsigned char prs_detect( void );
void uts_trigger (void);
void interrupt_init( void );

#endif