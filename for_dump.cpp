#include <stdlib.h>

#include "for_dump.h"


void dump(List* st_list, ForDump* st_dump)
{

    st_dump->dumps_counter++;
    int number_of_dump = st_dump->dumps_counter;



    char sample[21] = "pictures/image00.dot";
    sample[14] = (char) ('0' + ((int) number_of_dump / 10));
    sample[15] = (char) ('0' + ((int) number_of_dump % 10));
    FILE* file = fopen(sample, "w");

    fprintf(file, "digraph\n{\nbgcolor=\"%s\";\nrankdir = LR;\nedge[style=\"invis\", weight = 1000000];\n", FONT_COLOR);


    for (int i = 0; i < LEN_LIST; i++) // создали все ячейки
    {
        fprintf(file, "IND_%d[shape=Mrecord, label = \"IND = %d | value = %d | next = %d | prev = %d \", style=\"filled\",fillcolor=\"%s\"]\n", i, i, st_list->list[i].data, st_list->list[i].next, st_list->list[i].prev, ELEM_LIST_COLOR);
    }

    for (int i = 0; i < LEN_LIST - 1; i++)
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

    for (int i = 1; i < LEN_LIST; i++) // Запускаем с 1 для удобства дебага (если запускать с 0, то на рисунке неудобно читать)
    {
        if (st_list->list[i].data == -1) fprintf(file, "IND_%d -> IND_%d [color=\"%s\"];\n", i, st_list->list[i].next, NEXT_FREE_EDGE_COLOR);
        else fprintf(file, "IND_%d -> IND_%d;\n", i, st_list->list[i].next);
    }
    fprintf(file, "TAIL -> IND_%d;\n", st_list->list[0].next);
    fprintf(file, "FREE -> IND_%d [color=\"%s\"];\n", st_list->free, NEXT_FREE_EDGE_COLOR);


    // Сделаем связи PREV красными стрелками
    fprintf(file, "edge[color=\"%s\", weight = 1, style=\"\"];\n", PREV_EDGE_COLOR);

    for (int i = 1; i < LEN_LIST; i++) 
    {
        if (st_list->list[i].prev == -1) continue;
        fprintf(file, "IND_%d -> IND_%d;\n", i, st_list->list[i].prev);
    }
    fprintf(file, "HEAD -> IND_%d;\n", st_list->list[0].prev);

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
        char sample[] = "pic00.png";
        sample[3] = (char) ('0' + ((int) i / 10));
        sample[4] = (char) ('0' + ((int) i % 10));

        fprintf(file, "<big><big><h style=\"color:#FF8C00\">LIST %s (print %d) &#128578;</h></big></big>\n\n", st_dump->commands[i], i);


        fprintf(file, "<img src=\"%s\">\n\n\n", sample);

    }

    fclose(file);
}

