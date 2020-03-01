#ifndef STACK_H
#define STACK_H

typedef uint8_t byte_t;
typedef int32_t word_t;

extern byte_t *buf_text;
extern uint32_t *constant_vals;

struct Stack{
    int stack_pointer;
    int stack_max_size;
    word_t *stack_array;
}stack;

/**
 * Destroys stack
 **/
void destroy_stack(void);
/**
 * Pushes argument to stack
 **/
void push(signed long push_argument);
/**
 * Pops method from stack
 **/
word_t pop(void);
/**
 * Initialise stack with default values
 **/
void init_stack(void);

#endif
