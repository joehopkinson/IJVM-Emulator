#include <ijvm.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

struct Stack stack;

void init_stack(){
    stack.stack_pointer = 0;
    stack.stack_max_size = 100;
    stack.stack_array = (word_t *) malloc(stack.stack_max_size * sizeof(word_t));
}

word_t tos(){
    assert(stack_size() >= 0);
    return stack.stack_array[stack_size()];
}

word_t *get_stack(){
    assert(stack_size() > 0);
    return stack.stack_array;
}

int stack_size(){
    assert(stack.stack_pointer >= 0);
    return stack.stack_pointer;
}

void push(signed long push_argument){
    if(stack.stack_pointer == stack.stack_max_size){                            // Allocate additional memory for pushed word
        stack.stack_max_size += 100;
        stack.stack_array = (word_t *) realloc(stack.stack_array, (stack.stack_max_size) * sizeof(word_t*));
    }
    stack.stack_array[++stack.stack_pointer] = push_argument;
}

word_t pop(){
    assert(stack_size() >= 0);
    word_t pop_temp = stack.stack_array[stack.stack_pointer--];                 // Reduce memory allocation as stack size is decremented
    if(stack.stack_pointer < stack.stack_max_size / 4 && stack.stack_max_size > 100){
        stack.stack_max_size -= 100;
        stack.stack_array = (word_t *) realloc(stack.stack_array, (stack.stack_max_size) * sizeof(word_t*));
    }
    return pop_temp;
}

void destroy_stack(){
    free(stack.stack_array);
    stack.stack_pointer = 0;
}
