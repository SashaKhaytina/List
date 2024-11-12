#define TEST1    list_append(&st_list, 111, 1, &st_dump);\
\
    list_append(&st_list, 222, 2, &st_dump);\
\
    list_pop(&st_list, 2, &st_dump);\




#define TEST2     list_append(&st_list, 111, 1, &st_dump);\
\
    list_append(&st_list, 222, 1, &st_dump);\
\
    list_pop(&st_list, 1, &st_dump);\




#define TEST3    list_append(&st_list, 111, 1, &st_dump);\
\
    list_append(&st_list, 222, 2, &st_dump);\
\
    list_pop(&st_list, 1, &st_dump);\
\
    list_append(&st_list, 223, 2, &st_dump);\
\
    list_append(&st_list, 224, 3, &st_dump);\




#define TEST4    list_append(&st_list, 111, 1, &st_dump);\
\
    list_append(&st_list, 222, 2, &st_dump);\
    \
    list_append(&st_list, 333, 3, &st_dump);\
    \
    list_append(&st_list, 444, 4, &st_dump);\
\
    list_append(&st_list, 555, 5, &st_dump);\
    \
    list_append(&st_list, 666, 6, &st_dump);\
    \
    list_append(&st_list, 777, 7, &st_dump);\
    \
    list_append(&st_list, 888, 8, &st_dump);\
    \
    list_append(&st_list, 999, 9, &st_dump);\
\
    list_pop(&st_list, 1, &st_dump);\
\
    list_append(&st_list, 223, 2, &st_dump);\
\
    list_append(&st_list, 224, 3, &st_dump);\

