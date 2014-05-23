#include <math.h>

#define make_vecmap(NAME,ND) \
  int  map_vec_##NAME(double argf[], int argi[], double coord[],int np) { \
    int iii,exit_code; exit_code=0         \
    for(iii=0;iii<np;iii=iii){   \
      exit_code=map_##NAME(argf,argi,&coord[iii*ND]);  \
      if (exit_code<0){ break;};
    }; \                                      
         return exit_code;       \
  }; \



#define rot2d_TYPE 1

int map_rot2d(double argf[], int argi[], double coord[]) {
  double cx,sx,x,y;
  cx=argf[1]; sx=argf[2];
  x=coord[0]; y=coord[1];
  coord[0]= cx*x+sx*y;
  coord[1]=-sx*x+cx*y;
  return 1;
};

int update_rot2d(double argf[], int argi[]) {
  double angle=argf[0];
  argf[1]=cos(angle);
  argf[2]=sin(angle);
  return 1;
};

make_vecmap(rot2d,2)

#define kick2d_TYPE 2

int map_kick2d(double argf[], int argi[], double coord[]) {
  double kv;
  //double x,y; 
  int ord;
  kv=argf[0]; ord=argi[0];
  //x=coord[0]; y=coord[1];
  coord[1]+=kv*pow(coord[0],ord);
  return 1;
};

make_vecmap(kick2d,2);

#define counter_TYPE 3

int map_counter(double argf[], int argi[], double coord[]) {
  int count,limit;
  limit=argi[0];
  count=argi[1]++;
  if (count<limit){
    return 1;
  } else {
    return -1;
  };
};

make_vecmap(counter,2);

/* datai={elem_id,elem_type,elem_floatid,next_elem,other...}
 */

int vec_map_loop(double dataf[], int datai[], double coord[],
      int np,int nturn,int seq) {
  int retval,elem_id,elem_type,elem_floatid,elem_next;
  int *argi;
  double *argf;
  elem_id=0;
  retval=1;
  while(retval>0){
    elem_id=datai[elem_id];
    elem_type=datai[elem_id+1];
    elem_floatid=datai[elem_id+2];
    elem_next=datai[elem_id+3];
    argf=&dataf[elem_floatid];
    argi=&datai[elem_id+4];
    switch (elem_type) {
      case rot2d_TYPE:
      retval=map_vec_rot2d( argf, argi, coord, np);
      break;
      case kick2d_TYPE:
      retval=map_vec_kick2d( argf, argi, coord, np);
      break;
      case counter_TYPE:
      retval=map_vec_counter( argf, argi, coord, np);
      break;
    };
    elem_id=elem_next;
  };
  return 1;
};















