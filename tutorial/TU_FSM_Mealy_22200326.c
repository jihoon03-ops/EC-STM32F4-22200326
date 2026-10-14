#include <stdio.h>

//State definition
#define S0 0
#define S1 1

#define LOW 0
#define HIGH 1

unsigned char state = S0;
unsigned char nextstate = S0;
unsigned char input = LOW;
unsigned char ledOut = LOW;

// STate table definition
typedef struct {
    unsigned int next[2];       //nextstate = FSM[state].next[input]
    unsigned int out[2];        //output = FSM[state].out[input]
}

State_t FSM[2] = {
    { {S0, S1}, {LOW, HIGH} }, 
    { {S1, S0}, {HIGH, LOW} }
};
