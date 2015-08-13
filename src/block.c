#include "hmacro.h"
#include <math.h>
#include <stdio.h>
#include "drift_exact.c"
#include "multipole.c"
#include "cavity.c"
#include "align.c"

#define block_TYPE                                              9
#define loop_int_nelem                                          2
#define loop_int_elems                                          3

void print_var(INT [], FLOAT [], INT [], FLOAT [], INT );

INT block_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    INT nelem,mapid,i,id,retval=1;
    nelem=elemi[2];
    for(;;){
        for(i=0;i<nelem;i++){
            id=elemi[elemid+3+i];
            mapid=elemi[id];
            switch(mapid){
              case drift_exact_TYPE:
                retval=drift_exact_map(elemi, elemf, id, parti, partf, partid, partn);
                break;
              case multipole_TYPE:
                retval=multipole_map(elemi, elemf, id, parti, partf, partid, partn);
                break;
              case cavity_TYPE:
                retval=cavity_map(elemi, elemf, id, parti, partf, partid, partn);
                break;
              case align_TYPE:
                retval=align_map(elemi, elemf, id, parti, partf, partid, partn);
                break;
            }
            if(retval<0){ return 1; }
        }
    }
}