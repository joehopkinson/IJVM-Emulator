#ifndef FRAME_H
#define FRAME_H

typedef uint8_t byte_t;
typedef int32_t word_t;

extern int frame_counter;

typedef struct Frame{
    word_t *local_variables;
    int variable_size;
    int prev_frame_pc;
    int prev_stack_pointer;
}Frame;

/**
 * Array of type Frame, which stores the frames
 **/
Frame *frame_arr;

/**
 * Create frame, assigns its attributes
 **/
Frame new_frame(int program_counter, int num_args, int stack_pointer);
/**
 * Initialises frame with default values
 **/
Frame init_frame(Frame frame);
/**
 * Frees memory after frames life
 **/
void destroy_frame(Frame frame);

#endif
