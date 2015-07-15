#include "hmacro.h"
#include <math.h>
#include <stdio.h>

#define counter_TYPE 2
#define counter_int_count_max 0
#define counter_int_count 1


INT counter_init(INT elemi[], FLOAT elemf[], INT elemid){
    return 1;
}

INT counter_map(INT elemi[], FLOAT elemf[], INT elemid,
                INT parti[], FLOAT partf[], INT partid, INT partn){
    GETATTRI(counter,count_max);
    GETATTRI(counter,count);
    SETATTRI(counter,count,count+1);
    if (count<count_max){
        return 1;
    } else {
      SETATTRI(counter,count,0);
      return -1;
    }
}
