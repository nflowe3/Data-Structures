// stack.c

#include <stdlib.h>

#include "list.h"
#include "stack.h"

// stack push

int stack_push(Stack *stack, const void *data){

	// push data onto the stack

	return list_ins_next(stack, NULL, data);
}

// stack pop

int stack_pop(Stack *stack, void **data){

	// pop the data off the stack

	return list_rem_next(stack, NULL, data);
}