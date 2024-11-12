#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TEST1    list_append(&st_list, 111, 1, &st_dump);\
    dump_normal_person(&st_list);\
\
    list_append(&st_list, 222, 2, &st_dump);\
    dump_normal_person(&st_list);\
\
    list_pop(&st_list, 2, &st_dump);\
    dump_normal_person(&st_list);


#define TEST2     list_append(&st_list, 111, 1, &st_dump);\
    dump_normal_person(&st_list);\
\
    list_append(&st_list, 222, 1, &st_dump);\
    dump_normal_person(&st_list);\
\
    list_pop(&st_list, 1, &st_dump);\
    dump_normal_person(&st_list);


#define TEST3    list_append(&st_list, 111, 1, &st_dump);\
    dump_normal_person(&st_list);\
\
    list_append(&st_list, 222, 2, &st_dump);\
    dump_normal_person(&st_list);\
\
    list_pop(&st_list, 1, &st_dump);\
    dump_normal_person(&st_list);\
\
    list_append(&st_list, 223, 2, &st_dump);\
    dump_normal_person(&st_list);\
\
    list_append(&st_list, 224, 3, &st_dump);\
    dump_normal_person(&st_list);


#define TEST4    list_append(&st_list, 111, 1, &st_dump);\
    dump_normal_person(&st_list);\
\
    list_append(&st_list, 222, 2, &st_dump);\
    dump_normal_person(&st_list);\
    \
    list_append(&st_list, 333, 3, &st_dump);\
    dump_normal_person(&st_list);\
    \
    list_append(&st_list, 444, 4, &st_dump);\
    dump_normal_person(&st_list);\
\
    list_append(&st_list, 555, 5, &st_dump);\
    dump_normal_person(&st_list);\
    \
    list_append(&st_list, 666, 6, &st_dump);\
    dump_normal_person(&st_list);\
    \
    list_append(&st_list, 777, 7, &st_dump);\
    dump_normal_person(&st_list);\
    \
    list_append(&st_list, 888, 8, &st_dump);\
    dump_normal_person(&st_list);\
    \
    list_append(&st_list, 999, 9, &st_dump);\
    dump_normal_person(&st_list);\
\
    list_pop(&st_list, 1, &st_dump);\
    dump_normal_person(&st_list);\
\
    list_append(&st_list, 223, 2, &st_dump);\
    dump_normal_person(&st_list);\
\
    list_append(&st_list, 224, 3, &st_dump);\
    dump_normal_person(&st_list);



const size_t LEN_LIST = 11;
const char* const DUMP_FILE = "pictures/log.html"; // почему log
const char* const FONT_COLOR = "#191970";
const char* const ELEM_LIST_COLOR = "#AFEEEE";
const char* const NEXT_EDGE_COLOR = "#7FFF00";
const char* const NEXT_FREE_EDGE_COLOR = "#FFFF00";
const char* const PREV_EDGE_COLOR = "#DC143C";
const char* const HEAD_AND_TAIL_COLOR = "#FF8C00";

typedef int list_data_t;

enum Errors
{
    OK, 
    ERROR_OPEN_FILE,
    ERROR_INDEX
};

// struct Node 
// {
//     list_data_t data;
//     int next;
//     int prev;    
// };


struct List
{
    // TODO: Node *list; size can be realloced, ListResize(new_size) (user calls listresize)
    list_data_t list[LEN_LIST]; // Тот мнимый элемент // TODO: wtf +1, list_data_t (not only for int)
    int         next[LEN_LIST]; // В ячейке i лежит индекс следующего  (в массиве list)
    int         prev[LEN_LIST]; // В ячейке i лежит индекс предыдущего (в массиве list)

    size_t size; // TODO: make free index

    int free;    // индекс первой свободной ячейки

    // Зачем они вообще?
    int head; // последний (куда дальше добавляем)
    int tail; // наиболее раншьий добавленный (откуда pop) для очереди. По сути начало списка...  

};

struct ForDump
{
    char commands[100][30];
    int dumps_counter;
};


// можно возвращать коды ошибок

void init_list  (List* st_list);
void list_append(List* st_list, int elem, int ind, ForDump* st_dump); // ind - на какой индекс ХОТИМ ПОСТАВИТЬ
void list_pop   (List* st_list, int ind, ForDump* st_dump);           // ind - с какого индекса ХОТИМ УДАЛИТЬ              

// int find_empty_ind(List* st_list);
int who_is_num_ind_now(List* st_list, int ind);

void print_arr(int* arr, size_t size);
void print_real_list(List* st_list);

void dump(List* st_list, ForDump* st_dump);
void create_png(int num);
void to_do_log_file(ForDump* st_dump); // num - их количесвто

void dump_normal_person(List* st_list);



int main()
{
    List st_list;
    init_list(&st_list);

    ForDump st_dump = {};

    TEST4

    // TEST3

    // TEST2

    // TEST1

    to_do_log_file(&st_dump);

}


void init_list(List* st_list)
{
    st_list->list[0] = 0; // фантомный элемент
    st_list->next[0] = 0;
    st_list->prev[0] = 0;

    for (int i = 1; i < LEN_LIST; i++)
    {
        st_list->list[i] = -1; // ничего не лежит
        // st_list->next[i] = -1;
        st_list->prev[i] = -1;


        // Заполняем пустые ячейки
        if (i != LEN_LIST - 1) st_list->next[i] = i + 1;
        else st_list->next[i] = 0;
    }

    st_list->size = 0;
    st_list->head = 0;
    st_list->tail = 0;

    st_list->free = 1;

}


void list_append(List* st_list, int elem, int ind, ForDump* st_dump)
{
    // int empty_ind = find_empty_ind(st_list); // индекс, на котором он реально лежит в списке. 
    // printf("%d - ei\n", empty_ind);

    if (st_list->free == 0) // ПРОВЕРЬ!!!!!!!!!!!!!
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

    st_list->free = st_list->next[st_list->free]; // Обновляем free
    // printf("%d - was_ind\n", was_ind);

    st_list->list[empty_ind] = elem;
    st_list->next[st_list->prev[was_ind]] = empty_ind;
    st_list->next[empty_ind] = was_ind;

    st_list->prev[empty_ind] = st_list->prev[was_ind];
    st_list->prev[was_ind] = empty_ind;


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
    //st_dump->commands[st_dump->dumps_counter + 1] = new_str2;
    strcpy(st_dump->commands[st_dump->dumps_counter + 1], new_str);






    int was_ind = who_is_num_ind_now(st_list, ind);
    printf("%d - was_ind\n", was_ind);
    // предыдущий от следущего должен стать предыдущим от этого
    st_list->prev[st_list->next[was_ind]] = st_list->prev[was_ind];
    // next от предыдущего должен стать next от этого
    st_list->next[st_list->prev[was_ind]] = st_list->next[was_ind];
    st_list->size--;

    st_list->list[was_ind] = -1;
    st_list->prev[was_ind] = -1;
    // st_list->next[was_ind] = -1;

    // Обновляем free
    st_list->next[was_ind] = st_list->free;
    st_list->free = was_ind;

    dump(st_list, st_dump);

}


// int find_empty_ind(List* st_list) // индекс свободной ячейки
// {
//     for (int i = 1; i <= st_list->size + 1; i++)
//     {
//         if (st_list->list[i] == -1) return i;
//     }
//     return -1; // заполнен полностью
// }


int who_is_num_ind_now(List* st_list, int ind)
{
    int now = st_list->next[0];

    for (int step = 0; step < ind-1; step++)
    {
        now = st_list->next[now];
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


void print_real_list(List* st_list) // тут можно быстрее. Просто чтоб после каждого шага печатала.
{
    for (size_t i = 1; i <= st_list->size; i++)
    {
        printf("%d ", st_list->list[who_is_num_ind_now(st_list, i)]);
    }
    printf("\n");
}











void dump(List* st_list, ForDump* st_dump)
{

    st_dump->dumps_counter++;
    int number_of_dump = st_dump->dumps_counter;

    // printf("%d - st_dump->dumps_counter\n", st_dump->dumps_counter);


    char sample[21] = "pictures/image00.dot";
    sample[14] = (char) ('0' + ((int) number_of_dump / 10));
    sample[15] = (char) ('0' + ((int) number_of_dump % 10));
    // printf("%s - sample\n", sample);
    FILE* file = fopen(sample, "w");

    fprintf(file, "digraph\n{\nbgcolor=\"%s\";\nrankdir = LR;\nedge[style=\"invis\", weight = 1000000];\n", FONT_COLOR);


    for (int i = 0; i < LEN_LIST; i++) // создали все ячейки
    {
        fprintf(file, "IND_%d[shape=Mrecord, label = \"IND = %d | value = %d | next = %d | prev = %d \", style=\"filled\",fillcolor=\"%s\"]\n", i, i, st_list->list[i], st_list->next[i], st_list->prev[i], ELEM_LIST_COLOR);
    }

    for (int i = 0; i < LEN_LIST - 1; i++) // создали все ячейки
    {
        fprintf(file, "IND_%d -> IND_%d\n", i, i + 1);
    }

    fprintf(file, "TAIL[shape=\"rectangle\", width = 0.5, height = 0.4, style=\"filled\", fillcolor=\"%s\"];\n", HEAD_AND_TAIL_COLOR);
    fprintf(file, "HEAD[shape=\"rarrow\", width = 0.5, height = 0.5, style=\"filled\", fillcolor=\"%s\"];\n", HEAD_AND_TAIL_COLOR);
    fprintf(file, "FREE[shape=\"rectangle\", width = 0.5, height = 0.4, style=\"filled\", fillcolor=\"%s\"];\n", HEAD_AND_TAIL_COLOR);

    fprintf(file, "{ rank = same; TAIL; IND_0}\n");
    fprintf(file, "TAIL -> HEAD -> FREE\n");



    // Сделаем связи NEXT зелеными стрелками (и свободные - желтыми стрелками)
    fprintf(file, "edge[color=\"%s\", weight = 1, style=\"\"];\n", NEXT_EDGE_COLOR);

    for (int i = 1; i < LEN_LIST; i++) // если запускать с 0, то на рисунке трешак, который только путает
    {
        // if (st_list->next[i] == -1) continue;
        // fprintf(file, "IND_%d -> IND_%d;\n", i, st_list->next[i]);

        if (st_list->list[i] == -1) fprintf(file, "IND_%d -> IND_%d [color=\"%s\"];\n", i, st_list->next[i], NEXT_FREE_EDGE_COLOR);
        else fprintf(file, "IND_%d -> IND_%d;\n", i, st_list->next[i]);
    }
    fprintf(file, "TAIL -> IND_%d;\n", st_list->next[0]);
    fprintf(file, "FREE -> IND_%d [color=\"%s\"];\n", st_list->free, NEXT_FREE_EDGE_COLOR);


    // Сделаем связи PREV красными стрелками
    fprintf(file, "edge[color=\"%s\", weight = 1, style=\"\"];\n", PREV_EDGE_COLOR);

    for (int i = 1; i < LEN_LIST; i++) // если запускать с 0, то на рисунке трешак, который только путает
    {
        if (st_list->prev[i] == -1) continue; // это возможно?
        fprintf(file, "IND_%d -> IND_%d;\n", i, st_list->prev[i]);
    }
    fprintf(file, "HEAD -> IND_%d;\n", st_list->prev[0]);

    fprintf(file, "}\n");

    fclose(file);

    create_png(number_of_dump);

}

void create_png(int num)
{
    char command_create_png[200] = {};
    sprintf(command_create_png, "dot pictures/image%d%d.dot -Tpng -o pictures/pic%d%d.png", num / 10, num % 10, num / 10, num % 10);
    system(command_create_png);
}




void to_do_log_file(ForDump* st_dump)
{
    FILE* file = fopen(DUMP_FILE, "w");

    fprintf(file, "<pre>\n");
    fprintf(file, "<style>body {background-color:%s}</style>\n\n", FONT_COLOR);

    for (int i = 1; i <= st_dump->dumps_counter; i++)
    {        
        // char sample[] = {'p', 'i', 'c', '0', '0', '.', 'p', 'n', 'g'};
        char sample[] = "pic00.png";
        sample[3] = (char) ('0' + ((int) i / 10));
        sample[4] = (char) ('0' + ((int) i % 10));

        fprintf(file, "<big><big><h style=\"color:#FF8C00\">LIST %s (print %d) &#128578;</h></big></big>\n\n", st_dump->commands[i], i); //  сюда строку!


        fprintf(file, "<img src=\"%s\">\n\n\n", sample);

    }

    fclose(file);
}



void dump_normal_person(List* st_list)
{
    print_arr(st_list->list, LEN_LIST);
    print_arr(st_list->next, LEN_LIST);
    print_arr(st_list->prev, LEN_LIST);
    print_real_list(st_list);
}
