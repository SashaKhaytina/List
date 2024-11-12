#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "header.h"

#include "for_dump.h"
#include "list_commands.h"
#include "tests.h"


// void print_arr(int* arr, size_t size);
// void print_real_list(List* st_list);



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


// void print_arr(int* arr, size_t size)
// {
//     for (size_t i = 0; i < size; i++)
//     {
//         printf("%d ", arr[i]);
//     }
//     printf("\n");
// }


// void print_real_list(List* st_list) // тут можно быстрее. Просто чтоб после каждого шага печатала.
// {
//     for (size_t i = 1; i <= st_list->size; i++)
//     {
//         printf("%d ", st_list->list[who_is_num_ind_now(st_list, i)].data);
//     }
//     printf("\n");
// }

