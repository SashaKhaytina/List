#include "list_commands.h"

#include "for_dump.h"

void init_list(List* st_list)
{
    st_list->list = (Node*) calloc(LEN_LIST, sizeof(Node));
    
    
    st_list->list[0] = {0, 0, 0}; // фантомный элемент


    for (int i = 1; i < LEN_LIST; i++)
    {

        if (i != LEN_LIST - 1) st_list->list[i] = {-1, i + 1, -1};
        else                   st_list->list[i] = {-1, 0, -1};
    }

    st_list->size = 0;
    st_list->head = 0;
    st_list->tail = 0;

    st_list->free = 1;

}


void list_append(List* st_list, int elem, int ind, ForDump* st_dump)
{
    if (st_list->free == 0)
    {
        printf("Список заполнен. Добавление невозможно\n");
        return; // Это норм?
    }

    if (ind > st_list->size + 1) // добавляет на индекс, который больше чем длина + 1
    {
        printf("Превышение максимального на данный момент индекса\n"); // переделать надпись
        return;
    }

    char new_str[30] = {};
    sprintf(new_str, "append to ind %d elem %d", ind, elem);

    strcpy(st_dump->commands[st_dump->dumps_counter + 1], new_str);

    int was_ind = who_is_num_ind_now(st_list, ind);
    int empty_ind = st_list->free;

    // Обновляем free
    st_list->free = st_list->list[st_list->free].next;

    // Как вставить хоть какие-то объяснения?
    st_list->list[empty_ind].data = elem;
    st_list->list[st_list->list[was_ind].prev].next = empty_ind;
    st_list->list[empty_ind].next = was_ind;

    st_list->list[empty_ind].prev = st_list->list[was_ind].prev;
    st_list->list[was_ind].prev = empty_ind;


    st_list->size++;

    dump(st_list, st_dump);


}



void list_pop   (List* st_list, int ind, ForDump* st_dump)
{
    if (st_list->size == 0)
    {
        printf("Попытка удаления из пустого списка\n");
        return;
    }

    char new_str[30] = {};
    sprintf(new_str, "pop elem on ind %d", ind);
    strcpy(st_dump->commands[st_dump->dumps_counter + 1], new_str);






    int was_ind = who_is_num_ind_now(st_list, ind);
    // предыдущий от следущего должен стать предыдущим от этого
    st_list->list[st_list->list[was_ind].next].prev = st_list->list[was_ind].prev;
    // next от предыдущего должен стать next от этого
    st_list->list[st_list->list[was_ind].prev].next = st_list->list[was_ind].next;
    st_list->size--;

    st_list->list[was_ind].data = -1;
    st_list->list[was_ind].prev = -1;
    // st_list->next[was_ind] = -1;

    // Обновляем free
    st_list->list[was_ind].next = st_list->free;
    st_list->free = was_ind;

    dump(st_list, st_dump);

}



int who_is_num_ind_now(List* st_list, int ind)
{
    int now = st_list->list[0].next; // TAIL

    for (int step = 0; step < ind-1; step++)
    {
        now = st_list->list[now].next;
    }

    return now;
}
