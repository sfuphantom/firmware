
// #include "../TestUtils/TestUtils.h"
#include <stdio.h>
/* Functions Under Test */
// uint8_t actor_logic(AgentMessage_t data, uint8_t agent1_state, uint8_t agent2_state){

//     switch(data.id){

//         case AGENT_ONE:
//             agent1_state = data.msg;
//             gioSetBit(gioPORTB, 1, agent1_state);
//             break;

//         case AGENT_TWO:
//             agent2_state =  data.msg;
//             gioSetBit(gioPORTB, 2, agent2_state);
//             break;
//     } // switchcase
//     return agent2_state && agent1_state;
// }



int main(){

    // printf("Hello\r\n");


    // Actor_t test = {
    //     .agent1_state = 0,
    //     .agent2_state = 0,
    //     .data = {
    //         .id = AGENT_TWO,
    //         .msg = 1
    //     },
    // };
    // Actor_t expected = {
    //     .tx_data = 1
    // };

    // int TEST_LUT[] ={ 
    //        0,      
    //        0,
    //        0,
    //        0,
    //        0,
    //        1,
    //        0,
    //        0,
    //        0,
    //        0,
    //        0,
    //        1,
    //        0,
    //        1,     
    //        0, 
    //        1,
    // }; 

    
    // // a1 a2 id msg | tx_data
    // // 0   0  0  0       0      
    // // 0   0  0  1
    // // 0   0  1  0  
    // // 0   0  1  1       0
    // // 0   1  0  0       0
    // // 0   1  0  1       1
    // // 0   1  1  0       0
    // // 0   1  1  1       0
    // // 1   0  0  0       0
    // // 1   0  0  1       0
    // // 1   0  1  0       0
    // // 1   0  1  1       1
    // // 1   1  0  0       0
    // // 1   1  0  1       1     
    // // 1   1  1  0       0 
    // // 1   1  1  1       1
    



    // int i = 0;
    // for(i = 0; i < 16; i++){

    //     bool a1  = i & (1 << 3);
    //     bool a2  = i & (1 << 2);
    //     bool id  = i & (1 << 1);
    //     bool msg = i & (1 << 0);

    //     Actor_t test = {
    //         .agent1_state = a1,
    //         .agent2_state = a2,
    //         .data = {
    //             .id = id,
    //             .msg = msg
    //         },
    //     };

    //     Actor_t expected = {
    //         .tx_data = TEST_LUT[i],

    //     };

    //     // validate(compare_actor_ou   t,&test, &expected,  "Test");
    //     validate(1);


    // }

    // return 0;
#include <stdio.h>



  printf("%d",sizeof(char));

}

