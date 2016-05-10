// list.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

// list_init

void list_init(List *list, void (*destroy)(void *data)){
	
	// initialize the list

	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;	

	return;
}

// list_destroy

void list_destroy(List *list){

	void *data;

	// remove each element

	while(list_size(list) > 0){

		// If we can successfully remove the next element and the destroy function
		// defined inside the list object is not null, we will delete the element
		if(list_rem_next(list, NULL, (void **)&data) == 0 && list->destroy != NULL){
			list->destroy(data);
		}
	}

	// Clear the structure as a precaution

	memset(list, 0, sizeof(list));

	return;
}

// list_ins_next

int list_ins_next(List *list, ListElmt *element, const void *data){

	ListElmt *new_element;

	// Allocate storage for the element

	if((new_element = (ListElmt *)malloc(sizeof(ListElmt))) == NULL)
		return -1;

	// insert the element into the list

	new_element->data = (void *)data;

	if(element == NULL){

		// Handle insertion at the head of the list

		if(list_size(list) == 0)
			list->tail = new_element;

		new_element->next = list->head;
		list->head = new_element;

	}
	else {

		// handle insertion somewhere other than at the head

		if(element->next == NULL)
			list->tail = new_element;

		new_element->next = element->next;
		element->next = new_element;
	}

	list->size++;
}

// list_rem_next

int list_rem_next(List *list, ListElmt *element, void **data){

	ListElmt *old_element;

	// Do not allow removal from an empty list

	if(list_size(list) == 0)
		return -1;

	// Remove the current element from the list

	if(element == NULL){

		// Handle removal from the head of the list

		*data = list->head->data;
		old_element = list->head;
		list->head = list->head->next;

		if(list_size(list) == 1)
			list->tail = NULL;

	}
	else {

		// Handle removal from elsewhere other than the head

		if(element->next == NULL)
			return -1;

		*data = element->next->data;
		old_element = element->next;
		element->next = element->next->next;

		if(element->next == NULL)
			list->tail = element;
	}

	// Free the storage allocated by the abstract datatype

	free(old_element);

	// Adjust the size of the list to account for the removed element

	list->size--;

	return 0;

}
