#include <ijvm.h>
#include <stdlib.h>
#include "operations.h"
#include "stack.h"
#include "frame.h"

void bipush(){
    program_counter++;
    push((signed char) buf_text[program_counter]);
}

void out(){
    word_t temp = pop();
    fprintf(output, "%c", temp);
}

void in(){
    word_t in = fgetc(input);
    if(in == -1){
        in = 0;
    }
    push(in);
}

void iadd(){
    word_t temp1 = pop();
    word_t temp2 = pop();
    push(temp1 + temp2);
}

void isub(){
    word_t temp1 = pop();
    word_t temp2 = pop();
    push(temp2 - temp1);
}

void iand(){
    word_t temp1 = pop();
    word_t temp2 = pop();
    push(temp1 & temp2);
}

void ior(){
    word_t temp1 = pop();
    word_t temp2 = pop();
    push(temp1 | temp2);
}

void swap(){
    word_t temp1 = pop();
    word_t temp2 = pop();
    push(temp1);
    push(temp2);
}

void halt(){
    program_counter = text_size();
}

void dup(){
    push(tos());
}

void opgoto(){
    program_counter++;
    int16_t offset = read_short();
    program_counter += offset - 2;
}

void ifeq(){
    if(pop() == 0){
        opgoto();
    }
    else{
        program_counter += 2;
    }
}

void iflt(){
    if(pop() < 0){
        opgoto();
    }
    else{
        program_counter += 2;
    }
}

void if_icmpeq(){
    word_t temp1 = pop();
    word_t temp2 = pop();
    if(temp1 == temp2){
        opgoto();
    }
    else{
        program_counter += 2;
    }
}

void ldc_w(){
    program_counter++;
    uint16_t temp_index = read_short();
    push(get_constant(temp_index));
    program_counter++;
}

void istore(){
    word_t temp;
    program_counter++;
    temp = pop();
    if(buf_text[program_counter - 2] == OP_WIDE){                               // Check WIDE prefix (istore, iload, iinc)
        frame_arr[frame_counter].local_variables[read_short()] = temp;
    }
    else{
        frame_arr[frame_counter].local_variables[buf_text[program_counter]] = temp;
    }
}

void iload(){
    word_t temp;
    program_counter++;
    if(buf_text[program_counter - 2] == OP_WIDE){
        temp = get_local_variable(read_short());
    }
    else{
        temp = get_local_variable(buf_text[program_counter]);
    }

    push(temp);
}

void iinc(){
    program_counter++;
    if(buf_text[program_counter - 2] == OP_WIDE){
        frame_arr[frame_counter].local_variables[read_short()] += (signed char)buf_text[program_counter + 1];
    }
    else{
        frame_arr[frame_counter].local_variables[buf_text[program_counter]] += (signed char)buf_text[program_counter + 1];
    }
    program_counter++;
}

void invokevirtual(){
    program_counter++;
    frame_counter++;

    int temp_pc = program_counter + 1;
    program_counter = get_constant(read_short());
    int num_args = read_short();

    program_counter += 3;

    if(frame_counter == frame_max){                                             // In case no. frames exeeds array size, double size
        frame_max *= 2;
        frame_arr = (Frame *) realloc(frame_arr, frame_max * sizeof(Frame));
    }

    frame_arr[frame_counter] = new_frame(temp_pc, num_args, stack.stack_pointer - num_args);

    for(int i = num_args - 1; i > 0; i--){
        frame_arr[frame_counter].local_variables[i] = pop();
    }
}

void ireturn(){
    word_t temp_return = pop();

    // Pop redundant frame args from stack
    while(stack.stack_pointer - frame_arr[frame_counter].prev_stack_pointer != 0){
        pop();
    }

    program_counter = frame_arr[frame_counter].prev_frame_pc;
    push(temp_return);

    destroy_frame(frame_arr[frame_counter]);

    frame_counter--;
}

void wide(){
    program_counter++;
    step();
}
