
#include "stdlib.h"
#include "stdint.h"
#include <stdio.h>
#include <stdbool.h>

/* Dummy definitions */
#define gioPORTB "gioPORTB"
#define gioSetBit(gioPORTB, num, agent1_state)
enum{
    AGENT_ONE,
    AGENT_TWO
};

typedef struct AgentMessage{
    uint8_t id; // agent identifier
    uint8_t msg; // data from agent
}AgentMessage_t;


typedef struct Actor_t
{
    /* Queue Handles */
    // QueueHandle_t tx_q;
    // QueueHandle_t rx_q;

    /* Input Data */ 
    AgentMessage_t data;
    uint8_t agent1_state;
    uint8_t agent2_state;
    
    /* Output Data */
    uint8_t tx_data;
    uint8_t output;

}Actor_t;

/* Helpful Functions */
bool compare_agent(void* o1, void* o2){
    AgentMessage_t* agent1 = (AgentMessage_t*) o1;
    AgentMessage_t* agent2 = (AgentMessage_t*) o2;
    return (agent1->id == agent2->id && agent1->msg == agent2->msg);
}
bool compare_actor_out(void* o1, void* o2){
    Actor_t* actor1 = (Actor_t*) o1;
    Actor_t* actor2 = (Actor_t*) o2;
    return (actor1->tx_data == actor2->tx_data && actor1->output == actor2->output);
}

typedef bool (*f_expression )(void*, void*);    

// void validate(f_expression,  void*, void*, char[]);

int validate(int);


