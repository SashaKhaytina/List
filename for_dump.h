#ifndef FOR_DUMP
#define FOR_DUMP

#include "header.h"

const char* const DUMP_FILE             = "pictures/log.html"; // почему log
const char* const FONT_COLOR            = "#191970";
const char* const ELEM_LIST_COLOR       = "#AFEEEE";
const char* const NEXT_EDGE_COLOR       = "#7FFF00";
const char* const NEXT_FREE_EDGE_COLOR  = "#FFFF00";
const char* const PREV_EDGE_COLOR       = "#DC143C";
const char* const HEAD_AND_TAIL_COLOR   = "#FF8C00";


void dump(List* st_list, ForDump* st_dump);
void create_png(int num);
void to_do_log_file(ForDump* st_dump); // num - их количесвто


#endif