#ifndef LIST_COMMANDS
#define LIST_COMMANDS

#include "header.h"
#include <malloc.h>
#include <string.h>

void init_list  (List* st_list);
void list_append(List* st_list, int elem, int ind, ForDump* st_dump); // ind - на какой индекс ХОТИМ ПОСТАВИТЬ
void list_pop   (List* st_list, int ind, ForDump* st_dump);           // ind - с какого индекса ХОТИМ УДАЛИТЬ    
int who_is_num_ind_now(List* st_list, int ind); 

#endif