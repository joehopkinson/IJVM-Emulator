#include <ijvm.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stack.h"
#include "operations.h"
#include "frame.h"

uint32_t size_text;
byte_t *buf_text;
uint32_t *constant_vals;
int program_counter = 0;
int frame_counter = 0;
int frame_max = 10;
FILE *output;
FILE *input;

static int32_t swap_endian(int32_t num){                                        // Function to swap endianess of a 32 bit integer
    return((num >> 24) &0xff) | ((num << 8) &0xff0000) | ((num >> 8) &0xff00) | ((num << 24) &0xff000000);
}

bool check_magic(int32_t magic_num){
    return(magic_num == MAGIC_NUMBER);
}

int32_t read_32bin(FILE *fp){
    int32_t temp;
    fread(&temp, sizeof(int32_t), 1, fp);
    return swap_endian(temp);
}

uint16_t read_short(){
    uint16_t branch_temp = (buf_text[program_counter] << 8 | buf_text[program_counter + 1]);
    return branch_temp;
}

void read_block(FILE *fp){
    read_32bin(fp);                                                             // Constant origin, storage not necessary
    uint32_t const_size = read_32bin(fp);

    constant_vals = (uint32_t *) malloc(const_size);

    for(int i = 0; i < const_size / 4; i++){                                    // Constant data
        constant_vals[i] = read_32bin(fp);
    }

    read_32bin(fp);                                                             // Data origin, storage not necassary
    size_text = read_32bin(fp);

    buf_text = (byte_t *) malloc(size_text);

    fread(buf_text, sizeof(uint8_t), text_size(), fp);

    fclose(fp);
}

int init_ijvm(char *binary_file){
    FILE *fp;
    fp = fopen(binary_file, "rb");

    uint32_t magic_num = read_32bin(fp);

    if(!check_magic(magic_num)){
        return -1;
    }

    read_block(fp);
    init_stack();

    frame_arr = (Frame *) malloc(frame_max * sizeof(Frame));                    // Allocate memory for frame array
    frame_arr[frame_counter] = new_frame(0,0,0);

    set_output(stdout);                                                         // Set default to stdout/stdin
    set_input(stdin);

    return 0;
}

void destroy_ijvm(){
    program_counter = 0;
    free(buf_text);
    free(constant_vals);
    destroy_stack();
}

bool step(){
    switch (buf_text[program_counter]) {
        case OP_BIPUSH:
                bipush();
                break;
            case OP_DUP:
                dup();
                break;
            case OP_ERR:
                break;
            case OP_GOTO:
                opgoto();
                break;
            case OP_HALT:
                halt();
                break;
            case OP_IADD:
                iadd();
                break;
            case OP_IAND:
                iand();
                break;
            case OP_IFEQ:
                ifeq();
                break;
            case OP_IFLT:
                iflt();
                break;
            case OP_ICMPEQ:
                if_icmpeq();
                break;
            case OP_IINC:
                iinc();
                break;
            case OP_ILOAD:
                iload();
                break;
            case OP_IN:
                in();
                break;
            case OP_INVOKEVIRTUAL:
                invokevirtual();
                break;
            case OP_IOR:
                ior();
                break;
            case OP_IRETURN:
                ireturn();
                break;
            case OP_ISTORE:
                istore();
                break;
            case OP_ISUB:
                isub();
                break;
            case OP_LDC_W:
                ldc_w();
                break;
            case OP_NOP:
                break;
            case OP_OUT:
                out();
                break;
            case OP_POP:
                pop();
                break;
            case OP_SWAP:
                swap();
                break;
            case OP_WIDE:
                wide();
                break;
            default:
                return false;
    }
    program_counter++;
    return true;
}

void run(){
    while(program_counter < text_size()){
      step();
    }
}

void set_input(FILE *fp){
    input = fp;
}

void set_output(FILE *fp){
    output = fp;
}

byte_t *get_text(){
    return buf_text;
}

int text_size(){
    return size_text;
}

int get_program_counter(){
    return program_counter;
}

word_t get_constant(int i){
    return constant_vals[i];
}

word_t get_local_variable(int i){
    return frame_arr[frame_counter].local_variables[i];
}

byte_t get_instruction(){
    return buf_text[program_counter];
}

bool finished(){
    if(program_counter == text_size()){
        return 1;
    }
    return 0;
}
