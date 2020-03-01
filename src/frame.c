#include <ijvm.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "frame.h"

Frame init_frame(Frame frame){
    frame.variable_size = 10;
    frame.local_variables = (word_t*) malloc(frame.variable_size * sizeof(word_t));
    frame.prev_frame_pc = 0;
    frame.prev_stack_pointer = 0;
    return frame;
}

Frame new_frame(int program_counter, int num_args, int stack_pointer){
    Frame frame;
    frame = init_frame(frame);

    if(num_args > frame.variable_size){                                         // If no. arguments is larger than capacity, double capacity
        frame.variable_size *= 2;
        frame.local_variables = (word_t*) realloc(frame.local_variables, frame.variable_size * sizeof(word_t));
    }

    frame.prev_stack_pointer = stack_pointer;
    frame.prev_frame_pc = program_counter;

    return frame;
}

void destroy_frame(Frame frame){
    free(frame.local_variables);
}
