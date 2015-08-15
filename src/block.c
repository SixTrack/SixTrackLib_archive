#include "hmacro.h"
#include <math.h>
#include <stdio.h>
// #include "drift.c"
// #include "drift_exact.c"
// #include "multipole.c"
// #include "cavity.c"
// #include "align.c"
// #include "results.c"

INT drift_map(INT [], FLOAT[], INT, INT [], FLOAT [], INT, INT);
INT drift_exact_map(INT [], FLOAT[], INT, INT [], FLOAT [], INT, INT);
INT multipole_map(INT [], FLOAT[], INT, INT [], FLOAT [], INT, INT);
INT cavity_map(INT [], FLOAT[], INT, INT [], FLOAT [], INT, INT);
INT align_map(INT [], FLOAT[], INT, INT [], FLOAT [], INT, INT);
void print_var(INT [], FLOAT [], INT [], FLOAT [], INT );

#define drift_TYPE                                              5
#define drift_exact_TYPE                                        6
#define multipole_TYPE                                          7
#define cavity_TYPE                                             8
#define align_TYPE                                              9
#define block_TYPE                                              10
#define loop_int_nelem                                          2
#define loop_int_elems                                          3

INT block_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    INT nelem,mapid,i,id,retval=1;
    nelem=elemi[2];
    for(i=0;i<nelem;i++){
        id=elemi[elemid+3+i];
        mapid=elemi[id];
        // printf("%d\n", mapid);
        switch(mapid){
          case drift_TYPE:
            retval=drift_map(elemi, elemf, id, parti, partf, partid, partn);
            break;  
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
    }
    // print_var(elemi,elemf,parti,partf,block_TYPE);
    return 1;
}