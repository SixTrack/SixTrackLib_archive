#include "hmacro.h"
#include <math.h>
#include <stdio.h>

#ifndef FLOAT
#define FLOAT double
#endif

#ifndef INT
#define INT int
#endif

void print_var(INT [], FLOAT [], INT [], FLOAT [], INT);

INT counter_init(INT elemi[], FLOAT elemf[], INT elemid){
    return 1;
}

INT counter_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    INT retval=-1;
    GETATTRI(counter,count_max);
    GETATTRI(counter,count);
    SETATTRI(counter,count,count+1);
    if (count<count_max){
        retval=1;
    }
    print_var(elemi, elemf, parti, partf, counter_TYPE);
    return retval;
}