#include "hmacro.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "kick2d.c"
#include "rot2d.c"
#include "counter.c"
#include "monitor.c"
#include "drift.c"
#include "drift_exact.c"
#include "multipole.c"
#include "cavity.c"

#define loop_TYPE                                               3
#define loop_int_nelem                                          2
#define loop_int_elems                                          3


INT loop_init(INT elemi[], FLOAT elemf[], INT elemid){
    INT nelem,mapid,id,i;
    nelem=elemi[2];
    for(i=0;i<nelem;i++){
        id=elemi[elemid+3+i];
        mapid=elemi[id];
        switch(mapid){
            case rot2d_TYPE:
                rot2d_init(elemi, elemf, id);
                break;
            case counter_TYPE:
                counter_init(elemi, elemf, id);
                break;
            case monitor_TYPE:
                monitor_init(elemi, elemf, id);
                break;
        }
    }
    return 1;
}

INT loop_map(INT elemi[], FLOAT elemf[], INT elemid, INT parti[], FLOAT partf[], INT partid, INT partn){
    INT nelem,mapid,i,id,retval=1;
    nelem=elemi[2];
    for(;;){
        for(i=0;i<nelem;i++){
            id=elemi[elemid+3+i];
            mapid=elemi[id];
            switch(mapid){
              case rot2d_TYPE:
                retval=rot2d_map(elemi, elemf, id, parti, partf, partid, partn);
                break;
              case kick2d_TYPE:
                retval=kick2d_map(elemi, elemf, id, parti, partf, partid, partn);
                break;
              case counter_TYPE:
                retval=counter_map(elemi, elemf, id, parti, partf, partid, partn);
                break;
              case monitor_TYPE:
                retval=monitor_map(elemi, elemf, id, parti, partf, partid, partn);
                break;
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
            }
            if(retval<0){ return 1; }
        }
    }
}