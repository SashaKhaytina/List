#include <stdio.h>

#define TEST1    list_append(&st_list, 111, 1);\
    print_arr(st_list.list, LEN_LIST + 1);\
    print_arr(st_list.next, LEN_LIST + 1);\
    print_arr(st_list.prev, LEN_LIST + 1);\
    print_real_list(&st_list);\
\
    list_append(&st_list, 222, 2);\
    print_arr(st_list.list, LEN_LIST + 1);\
    print_arr(st_list.next, LEN_LIST + 1);\
    print_arr(st_list.prev, LEN_LIST + 1);\
    print_real_list(&st_list);\
\
    list_pop(&st_list, 2);\
    print_arr(st_list.list, LEN_LIST + 1);\
    print_arr(st_list.next, LEN_LIST + 1);\
    print_arr(st_list.prev, LEN_LIST + 1);\
    print_real_list(&st_list);

#define TEST2     list_append(&st_list, 111, 1);\
    print_arr(st_list.list, LEN_LIST + 1);\
    print_arr(st_list.next, LEN_LIST + 1);\
    print_arr(st_list.prev, LEN_LIST + 1);\
    print_real_list(&st_list);\
\
    list_append(&st_list, 222, 1);\
    print_arr(st_list.list, LEN_LIST + 1);\
    print_arr(st_list.next, LEN_LIST + 1);\
    print_arr(st_list.prev, LEN_LIST + 1);\
    print_real_list(&st_list);\
\
    list_pop(&st_list, 1);\
    print_arr(st_list.list, LEN_LIST + 1);\
    print_arr(st_list.next, LEN_LIST + 1);\
    print_arr(st_list.prev, LEN_LIST + 1);\
    print_real_list(&st_list);\


const size_t LEN_LIST = 10;


struct List
{
    int list[LEN_LIST + 1]; // Тот мнимый элемент
    int next[LEN_LIST + 1]; // В ячейке i лежит индекс следующего  (в массиве list)
    int prev[LEN_LIST + 1]; // В ячейке i лежит индекс предыдущего (в массиве list)

    size_t size;

    // Зачем они вообще?
    int head; // последний (куда дальше добавляем)
    int tail; // наиболее раншьий добавленный (откуда pop) для очереди. По сути начало списка...  

};
 

void init_list  (List* st_list);
void list_append(List* st_list, int elem, int ind); // ind - на какой индекс ХОТИМ ПОСТАВИТЬ
void list_pop   (List* st_list, int ind);           // ind - с какого индекса ХОТИМ УДАЛИТЬ              

int find_empty_ind(List* st_list);
int who_is_num_ind_now(List* st_list, int ind);

void print_arr(int* arr, size_t size);
void print_real_list(List* st_list);





// Поставить проверку на корректность индекса (то что не превысили ли size своим запросом)


int main()
{
    List st_list;
    init_list(&st_list);


    list_append(&st_list, 111, 1);
    print_arr(st_list.list, LEN_LIST + 1);
    print_arr(st_list.next, LEN_LIST + 1);
    print_arr(st_list.prev, LEN_LIST + 1);
    print_real_list(&st_list);

    list_append(&st_list, 222, 2);
    print_arr(st_list.list, LEN_LIST + 1);
    print_arr(st_list.next, LEN_LIST + 1);
    print_arr(st_list.prev, LEN_LIST + 1);
    print_real_list(&st_list);

    list_pop(&st_list, 1);
    print_arr(st_list.list, LEN_LIST + 1);
    print_arr(st_list.next, LEN_LIST + 1);
    print_arr(st_list.prev, LEN_LIST + 1);
    print_real_list(&st_list);

    list_append(&st_list, 223, 2);
    print_arr(st_list.list, LEN_LIST + 1);
    print_arr(st_list.next, LEN_LIST + 1);
    print_arr(st_list.prev, LEN_LIST + 1);
    print_real_list(&st_list);
    // TEST2

    // TEST1

    // list_append(&st_list, 221, 1);

    // list_append(&st_list, 222, 2);

    // printf("%d - size\n", st_list.size);
    // print_arr(st_list.list, LEN_LIST + 1);
    // print_arr(st_list.next, LEN_LIST + 1);
    // print_arr(st_list.prev, LEN_LIST + 1);
    // print_real_list(&st_list);

    // list_pop(&st_list, 1);
    // print_arr(st_list.list, LEN_LIST + 1);
    // print_arr(st_list.next, LEN_LIST + 1);
    // print_arr(st_list.prev, LEN_LIST + 1);
    // print_real_list(&st_list);

    // list_append(&st_list, 223, 3);
    // print_arr(st_list.list, LEN_LIST + 1);
    // print_arr(st_list.next, LEN_LIST + 1);
    // print_arr(st_list.prev, LEN_LIST + 1);
    // print_real_list(&st_list);

}


void init_list(List* st_list)
{
    for (int i = 1; i <= LEN_LIST; i++)
    {
        st_list->list[i] = -1; // ничего не лежит
        st_list->next[i] = -1;
        st_list->prev[i] = -1;
    }

    st_list->size = 0;
    st_list->head = 0;
    st_list->tail = 0;

    // st_list->list[1] = 111;
    // st_list->list[2] = 222;
    // st_list->prev[1] = 0;
    // st_list->next[1] = 2;
    // st_list->prev[2] = 1;
    // st_list->next[2] = 0;


    // st_list->size = 2;
    // st_list->head = 2;
    // st_list->tail = 1;

}


void list_append(List* st_list, int elem, int ind)
{
    // В list оно добавляется просто на первый свободный элемент!
    // Т.е надо найти свободный индекс и добавить в него. НО ЭТО НЕ ФАКТ, ЧТО БУДЕТ ЕГО МЕСТОМ В САМОМ СПИСКЕ
    int empty_ind = find_empty_ind(st_list); // индекс, на котором он реально лежит в списке. 
    printf("%d - ei\n", empty_ind);

    if (empty_ind == -1)
    {
        printf("Список заполнен. Добавление невозможно\n");
        return; // Это норм?
    }

    // Надо найти, кто СЕЙЧАС (до добавления) под номером ind. Для этого надо сделать ind шагов от TAIL


    // if (st_list->size == 0) // и еще если ind = 1 же надо проверять...
    // {
    //     printf("st_list->size == 0\n");
    //     st_list->list[empty_ind] = elem;
    //     st_list->prev[empty_ind] = 0;
    //     st_list->head = empty_ind;

    // }

    // else
    // {
        printf("st_list->size != 0\n");
        int was_ind = who_is_num_ind_now(st_list, ind);
        printf("%d - was_ind\n", was_ind);
        st_list->list[empty_ind] = elem;
        st_list->next[st_list->prev[was_ind]] = empty_ind;
        st_list->next[empty_ind] = was_ind;

        st_list->prev[empty_ind] = st_list->prev[was_ind];
        st_list->prev[was_ind] = empty_ind;
    // }

    st_list->size++;







}



void list_pop   (List* st_list, int ind)
{
    int was_ind = who_is_num_ind_now(st_list, ind);
    printf("%d - was_ind\n", was_ind);
    // предыдущий от следущего должен стать предыдущим от этого
    st_list->prev[st_list->next[was_ind]] = st_list->prev[was_ind];
    // next от предыдущего должен стать next от этого
    st_list->next[st_list->prev[was_ind]] = st_list->next[was_ind];
    st_list->size--;

    st_list->list[was_ind] = -1;
    st_list->next[was_ind] = -1;
    st_list->prev[was_ind] = -1;

}


int find_empty_ind(List* st_list) // индекс свободной ячейки
{
    for (int i = 1; i <= st_list->size + 1; i++)
    {
        if (st_list->list[i] == -1) return i;
    }
    return -1; // заполнен полностью

}


int who_is_num_ind_now(List* st_list, int ind)
{
    //int now = st_list->tail; // начало!!!!!!!!!!!! (элемент, с которго список начинается)
    int now = st_list->next[0];
    // printf("%d - now\n", now);

    for (int step = 0; step < ind-1; step++)
    {
        // printf("SDFGHHUYTRE\n");
        now = st_list->next[now];
        // printf("%d - now\n", now);
    }

    return now;
}


void print_arr(int* arr, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


void print_real_list(List* st_list)
{
    for (size_t i = 1; i <= st_list->size; i++)
    {
        printf("%d ", st_list->list[who_is_num_ind_now(st_list, i)]);
    }
    printf("\n");
}
