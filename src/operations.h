#ifndef OPERATIONS_H
#define OPERATIONS_H

typedef uint8_t byte_t;
typedef int32_t word_t;

extern int program_counter;
extern FILE *output;
extern FILE *input;
extern int frame_counter;
extern int frame_max;


/**
 * Method to read a short from buffer
 **/
uint16_t read_short(void);
/**
 * Push a byte onto stack
 **/
void bipush(void);
/**
 * Pop word off stack and print to stdout
 **/
void out(void);
/**
 * Pop two words from stack; push their sum
 **/
void iadd(void);
/**
 * Pop two words from stack; subtract the top word from the second, push the answer
 **/
void isub(void);
/**
 * Pop two words from stack; push bit-wise AND
 **/
void iand(void);
/**
 * Pop two words from stack; push bit-wise OR.
 **/
void ior(void);
/**
 * Swap the two top words on the stack
 **/
void swap(void);
/**
 * Halt the simulator
 **/
void halt(void);
/**
 * Reads a character from the input and pushes it onto the stack. If no character is available, 0 is pushed
 **/
void in(void);
/**
 * Pop word off stack and print it to standard out
 **/
void out(void);
/**
 * Copy top word on stack and push onto stack
 **/
void dup(void);
/**
 * Unconditional jump
 **/
void opgoto(void);
/**
 * Pop word from stack and branch if it is zero
 **/
void ifeq(void);
/**
 * Pop word from stack and branch if it is less than zero
 **/
void iflt(void);
/**
 * Pop two words from stack and branch if they are equal
 **/
void if_icmpeq(void);
/**
 * Push constant from constant pool onto stack
 **/
void ldc_w(void);
/**
 * Pop word from stack and store in local variable
 **/
void istore(void);
/**
 * Push local variable onto stack
 **/
void iload(void);
/**
 * Add a constant value to a local variable. The first byte is the variable index. The second byte is the constant.
 **/
void iinc(void);
/**
 * Invoke a method, pops object reference and pops arguments from stack.
 **/
void invokevirtual(void);
/**
 * Return from method with a word value
 **/
void ireturn(void);
/**
 * Prefix instruction; next instruction has a 16-bit index
 **/
void wide(void);


#endif
