#include <math.h>

#define make_vecmap(NAME,ND) \
  int  map_vec_##NAME(double dataf[], int datai[], int elem_id, double coord[], int coordi[]) { \
    int iii,exit_code; exit_code=0;  \
    int np,nd;  \
    np=coordi[0]; nd=coordi[1];  \
    for(iii=0;iii<np;iii=iii+1){  \
      exit_code=map_##NAME(dataf,datai,elem_id,&coord[iii*nd]);  \
      if (exit_code<0){ break;};  \
    };  \
    return exit_code;  \
  };  \

#define rot2d_TYPE 1

int map_rot2d(double dataf[], int datai[], int elem_id, double coord[]) {
  double cx,sx,x,y;
  int elem_floatid;
  elem_floatid=datai[elem_id+2];
  cx=dataf[elem_floatid+1]; 
  sx=dataf[elem_floatid+2];
  x=coord[0]; y=coord[1];
  coord[0]= cx*x+sx*y;
  coord[1]=-sx*x+cx*y;
  return 1;
};

int update_rot2d(double dataf[], int datai[], int elem_id) {
  double angle;
  int elem_floatid;
  elem_floatid=datai[elem_id+2];
  angle=datai[elem_floatid];
  dataf[elem_floatid+1]=cos(angle);
  dataf[elem_floatid+2]=sin(angle);
  return 1;
};

make_vecmap(rot2d,2)

#define kick2d_TYPE 2

int map_kick2d(double dataf[], int datai[], int elem_id, double coord[]) {
  double kv;
  int ord, elem_floatid;
  elem_floatid=datai[elem_id+2];
  kv=dataf[elem_floatid]; 
  ord=datai[elem_id+4];
  coord[1]+=kv*pow(coord[0],ord);
  return 1;
};

make_vecmap(kick2d,2);

#define counter_TYPE 3

int map_counter(double dataf[], int datai[], int elem_id, double coord[]) {
  int count,limit,elem_floatid;
  elem_floatid=datai[elem_id+2]; 
  limit=datai[elem_id+4];
  count=datai[elem_id+5]++;
  if (count<limit){
    return 1;
  } else {
    return -1;
  };
};

make_vecmap(counter,2);

int vec_map_block(double dataf[], int datai[], int elem_id, double coord[], int coordi[]){
  int *elem_list,elem_type,retval,elem_next;
  elem_list=&datai[elem_id+3];
  while (*(elem_list++)!=-1){
    elem_id=*elem_list;
       elem_type=datai[elem_id+1]; 
       switch (elem_type) {
      case rot2d_TYPE:
        retval=map_vec_rot2d(dataf, datai, elem_id, coord, coordi);
        break;
      case kick2d_TYPE:
        retval=map_vec_kick2d(dataf, datai, elem_id, coord, coordi);
        break;
      case counter_TYPE:
        retval=map_vec_counter(dataf, datai, elem_id, coord, coordi);
        break;
       };
       if (retval<1) {return retval;}
    };
    elem_next=datai[elem_id+3];
    return -1;    
    //return elem_next;
};

/* datai={elem_id,elem_type,elem_floatid,next_elem,other...}
 */

int vec_map_loop(double dataf[], int datai[], int elem_id, double coord[], int coordi[]) {
  int elem_next,i;  
  for(i=0;i<10;i++)
    printf("%d",datai[i]);
  elem_next=0;
  while(elem_next>=0){
    elem_next= vec_map_block(dataf, datai, elem_next, coord, coordi);
  };
  return 1;
};
