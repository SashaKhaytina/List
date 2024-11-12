#ifndef HEADER
#define HEADER


#include <stdio.h>

const size_t LEN_LIST = 11;


typedef int list_data_t;

enum Errors
{
    OK, 
    ERROR_OPEN_FILE,
    ERROR_INDEX
};

struct Node 
{
    list_data_t data;
    int next;
    int prev;    
};


struct List
{
    Node* list;

    size_t size;

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


#endif