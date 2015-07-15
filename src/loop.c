#include "hmacro.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "kick2d.c"
#include "rot2d.c"
#include "counter.c"
#include "monitor.c"
#include "drift_exact.c"
#include "rf_cavity.c"
#include "dipole.c"
#include "normal_pole.c"
#include "skew_pole.c"
#include "multipole_hor.c"
#include "multipole_ver.c"

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
              case drift_exact_TYPE:
                retval=drift_exact_map(elemi, elemf, id, parti, partf, partid, partn);
                break;
              case rf_cavity_TYPE:
                retval=rf_cavity_map(elemi, elemf, id, parti, partf, partid, partn);
                break;
              case dipole_TYPE:
                retval=dipole_map(elemi, elemf, id, parti, partf, partid, partn);
                break;
              case normal_quadrupole_TYPE:
              	retval=normal_quadrupole_map(elemi, elemf, id, parti, partf, partid, partn);
              	break;
              case normal_sextupole_TYPE:
              	retval=normal_sextupole_map(elemi, elemf, id, parti, partf, partid, partn);
              	break;
              case normal_octupole_TYPE:
              	retval=normal_octupole_map(elemi, elemf, id, parti, partf, partid, partn);
              	break;
              case normal_decapole_TYPE:
              	retval=normal_decapole_map(elemi, elemf, id, parti, partf, partid, partn);
              	break;
              case normal_dodecapole_TYPE:
              	retval=normal_dodecapole_map(elemi, elemf, id, parti, partf, partid, partn);
              	break;
              case normal_14pole_TYPE:
              	retval=normal_14pole_map(elemi, elemf, id, parti, partf, partid, partn);
              	break;
              case normal_16pole_TYPE:
              	retval=normal_16pole_map(elemi, elemf, id, parti, partf, partid, partn);
              	break;
              case normal_18pole_TYPE:
              	retval=normal_18pole_map(elemi, elemf, id, parti, partf, partid, partn);
              	break;
              case normal_20pole_TYPE:
              	retval=normal_20pole_map(elemi, elemf, id, parti, partf, partid, partn);
              	break;
              case skew_quadrupole_TYPE:
              	retval=skew_quadrupole_map(elemi, elemf, id, parti, partf, partid, partn);
              	break;
              case skew_sextupole_TYPE:
              	retval=skew_sextupole_map(elemi, elemf, id, parti, partf, partid, partn);
              	break;
              case skew_octupole_TYPE:
              	retval=skew_octupole_map(elemi, elemf, id, parti, partf, partid, partn);
              	break;
              case skew_decapole_TYPE:
              	retval=skew_decapole_map(elemi, elemf, id, parti, partf, partid, partn);
              	break;
              case skew_dodecapole_TYPE:
              	retval=skew_dodecapole_map(elemi, elemf, id, parti, partf, partid, partn);
              	break;
              case skew_14pole_TYPE:
              	retval=skew_14pole_map(elemi, elemf, id, parti, partf, partid, partn);
              	break;
              case skew_16pole_TYPE:
              	retval=skew_16pole_map(elemi, elemf, id, parti, partf, partid, partn);
              	break;
              case skew_18pole_TYPE:
              	retval=skew_18pole_map(elemi, elemf, id, parti, partf, partid, partn);
              	break;
              case skew_20pole_TYPE:
              	retval=skew_20pole_map(elemi, elemf, id, parti, partf, partid, partn);
              	break;
              case hor_approx_ho_TYPE:
              	retval=multipole_hor_approx_ho_map(elemi, elemf, id, parti, partf, partid, partn);
              	break;
              case purehor_approx_TYPE:
              	retval=multipole_purehor_approx_map(elemi, elemf, id, parti, partf, partid, partn);
              	break;
              case ver_approx_ho_TYPE:
              	retval=multipole_ver_approx_ho_map(elemi, elemf, id, parti, partf, partid, partn);
              	break;
              case purever_approx_TYPE :
              	retval=multipole_purever_approx_map(elemi, elemf, id, parti, partf, partid, partn);
              	break;
            }
            if(retval<0){ return 1; }
        }
    }
}