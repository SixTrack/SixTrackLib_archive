#include <math.h>
#include <stdio.h>

#define size 255
#define INT 0
#define FLOAT 1
struct Elem{
   int type;
   union var{int i; double f; } data;
};

struct Elem_stack{
    struct Elem st[size];
    int elem_top;
}el_stack;

void init_elem_stack()
{
    el_stack.elem_top=-1;
}

void elem_pushInt(int item)
{
    el_stack.elem_top++;
    el_stack.st[el_stack.elem_top].type = INT;
    el_stack.st[el_stack.elem_top].data.i = (int)item;
}

void elem_pushFloat(float item)
{
    el_stack.elem_top++;
    el_stack.st[el_stack.elem_top].type = FLOAT;
    el_stack.st[el_stack.elem_top].data.f = (double)item;
}

struct Elem elem_pop()
{
    struct Elem item;
    if(el_stack.elem_top<0)
    {
        item.type = 0;
        item.data.i = 0;
        return item;    
    }
    item.type = el_stack.st[el_stack.elem_top].type;
    item.data = el_stack.st[el_stack.elem_top].data;
    el_stack.elem_top--;
    return(item);
}


void op_POW(){
    struct Elem a,b;
    b = elem_pop();
    a = elem_pop();
    if(a.type==INT && b.type==INT) 
    {elem_pushInt(pow(a.data.i,b.data.i));}
}

void op_MUL(){
    struct Elem a,b;
    b = elem_pop();
    a = elem_pop();
    if(a.type==INT && b.type==INT) 
    {elem_pushInt(a.data.i*b.data.i);}
    if(a.type==FLOAT && b.type==INT) 
    {elem_pushFloat(a.data.f*(double)b.data.i);}
    if(a.type==INT && b.type==FLOAT) 
    {elem_pushFloat((double)a.data.i*b.data.f);}
    if(a.type==FLOAT && b.type==FLOAT) 
    {elem_pushFloat(a.data.f*b.data.f);}
}

void op_DIV(){
    struct Elem a,b;
    b = elem_pop();
    a = elem_pop();
    if(a.type==INT && b.type==INT) 
    {elem_pushInt((double)(a.data.i/b.data.i));}
    if(a.type==FLOAT && b.type==INT) 
    {elem_pushFloat((double)(a.data.f/(double)b.data.i));}
    if(a.type==INT && b.type==FLOAT) 
    {elem_pushFloat((double)((double)a.data.i/b.data.f));}
    if(a.type==FLOAT && b.type==FLOAT) 
    {elem_pushFloat((double)(a.data.f/b.data.f));}
}

void op_ADD(){
    struct Elem a,b;
    b = elem_pop();
    a = elem_pop();
    if(a.type==INT && b.type==INT) 
    {elem_pushInt(a.data.i+b.data.i);}
    if(a.type==FLOAT && b.type==INT) 
    {elem_pushFloat(a.data.f+(double)b.data.i);}
    if(a.type==INT && b.type==FLOAT) 
    {elem_pushFloat((double)a.data.i+b.data.f);}
    if(a.type==FLOAT && b.type==FLOAT) 
    {elem_pushFloat(a.data.f+b.data.f);}
}

void op_SUB(){
    struct Elem a,b;
    b = elem_pop();
    a = elem_pop();
    if(a.type==INT && b.type==INT) 
    {elem_pushInt(a.data.i-b.data.i);}
    if(a.type==FLOAT && b.type==INT) 
    {elem_pushFloat(a.data.f-(double)b.data.i);}
    if(a.type==INT && b.type==FLOAT) 
    {elem_pushFloat((double)a.data.i-b.data.f);}
    if(a.type==FLOAT && b.type==FLOAT) 
    {elem_pushFloat(a.data.f-b.data.f);}
}

void op_LT(){
    struct Elem a,b;
    b = elem_pop();
    a = elem_pop();
    if(a.type==INT && b.type==INT) 
    {elem_pushInt(a.data.i<b.data.i?1:0);}
    if(a.type==FLOAT && b.type==INT) 
    {elem_pushInt(a.data.f<(float)b.data.i?1:0);}
    if(a.type==INT && b.type==FLOAT) 
    {elem_pushInt((float)a.data.i<b.data.f?1:0);}
    if(a.type==FLOAT && b.type==FLOAT) 
    {elem_pushInt(a.data.f<b.data.f?1:0);}
}

void op_GT(){
    struct Elem a,b;
    b = elem_pop();
    a = elem_pop();
    if(a.type==INT && b.type==INT) 
    {elem_pushInt(a.data.i>b.data.i?1:0);}
    if(a.type==FLOAT && b.type==INT) 
    {elem_pushInt(a.data.f>(float)b.data.i?1:0);}
    if(a.type==INT && b.type==FLOAT) 
    {elem_pushInt((float)a.data.i>b.data.f?1:0);}
    if(a.type==FLOAT && b.type==FLOAT) 
    {elem_pushInt(a.data.f>b.data.f?1:0);}
}

void op_LE(){
    struct Elem a,b;
    b = elem_pop();
    a = elem_pop();
    if(a.type==INT && b.type==INT) 
    {elem_pushInt(a.data.i<=b.data.i?1:0);}
    if(a.type==FLOAT && b.type==INT) 
    {elem_pushInt(a.data.f<=(float)b.data.i?1:0);}
    if(a.type==INT && b.type==FLOAT) 
    {elem_pushInt((float)a.data.i<=b.data.f?1:0);}
    if(a.type==FLOAT && b.type==FLOAT) 
    {elem_pushInt(a.data.f<=b.data.f?1:0);}
}

void op_GE(){
    struct Elem a,b;
    b = elem_pop();
    a = elem_pop();
    if(a.type==INT && b.type==INT) 
    {elem_pushInt(a.data.i>=b.data.i?1:0);}
    if(a.type==FLOAT && b.type==INT) 
    {elem_pushInt(a.data.f>=(float)b.data.i?1:0);}
    if(a.type==INT && b.type==FLOAT) 
    {elem_pushInt((float)a.data.i>=b.data.f?1:0);}
    if(a.type==FLOAT && b.type==FLOAT) 
    {elem_pushInt(a.data.f>=b.data.f?1:0);}
}

void op_IF(){
    struct Elem a,b,c;
    c = elem_pop();
    b = elem_pop();
    a = elem_pop();
    if(c.type==INT && b.type==INT)
    (a.data.i!=0)?elem_pushInt(b.data.i):elem_pushInt(c.data.i);
    if(c.type==FLOAT && b.type==INT) 
    (a.data.i!=0)?elem_pushInt(b.data.i):elem_pushFloat(c.data.f);
    if(c.type==INT && b.type==FLOAT) 
    (a.data.i!=0)?elem_pushFloat(b.data.f):elem_pushInt(c.data.i);
    if(c.type==FLOAT && b.type==FLOAT) 
    (a.data.i!=0)?elem_pushFloat(b.data.f):elem_pushFloat(c.data.f);
}

void op_SIN(){
    struct Elem a;
    a = elem_pop();
    if(a.type==INT)
    elem_pushFloat(sin(a.data.i));
    if(a.type==FLOAT)
    elem_pushFloat(sin(a.data.f));
}

void op_COS(){
    struct Elem a;
    a = elem_pop(); 
    if(a.type==INT)
    elem_pushFloat(cos(a.data.i));
    if(a.type==FLOAT)
    elem_pushFloat(cos(a.data.f));
}

void op_SQRT(){
    struct Elem a;
    a = elem_pop();
    if(a.type==INT)
    elem_pushFloat(sqrt(a.data.i));
    if(a.type==FLOAT)
    elem_pushFloat(sqrt(a.data.f));
}

void op_EXP(){
    struct Elem a;
    a = elem_pop();
    if(a.type==INT)
    elem_pushFloat(exp(a.data.i));
    if(a.type==FLOAT)
    elem_pushFloat(exp(a.data.f));
}

void op_CONSTF(double constf[]){
    struct Elem item;    
    int iii;
    item=elem_pop();
    iii=item.data.i;
    elem_pushFloat(constf[iii]);
}

void op_NUMi(int num){
    elem_pushInt(num);
}

void op_NUMf(double num){
    elem_pushFloat(num);
}

int op_add=1, op_sub=2, op_equ=3, op_mul=4, op_div=5, op_pow=6, op_constf=7, op_lt=8, op_gt=9, op_le=10, op_ge=11;

int decode(double dataf[], int datai[], int i)
{
    if(i%3==1)
        return (i-1)/3;
    else
    {
        if(i%3==2)
            return (i-2)/3;
        else
            return i/3;
    }
}

int is_operator(double dataf[],int datai[],int d)
{
    if((d%3==0)&&(decode(dataf,datai,d)!=op_constf))
        return 1;
    else 
        return 0;  
}

int is_variable(int d)
{
    if(d%3==2)
        return 1;
    else 
        return 0;
}

void call_ops(int index)
{
    switch(index)
    {
        case 1: op_ADD(); break;
        case 2: op_SUB(); break;
        case 4: op_MUL(); break;
        case 5: op_DIV(); break;
        case 6: op_POW(); break;
        case 8: op_LT(); break;
        case 9: op_GT(); break;	
        case 10: op_LE(); break;
        case 11: op_GE(); break;
        case 12: op_IF(); break;
        case 13: op_SIN(); break;
        case 14: op_COS(); break;
        case 15: op_SQRT(); break;
        case 16: op_EXP(); break;
    }
}

#define make_vecmap(NAME,ND) \
  int  map_vec_##NAME(double dataf[], int datai[], int elem_id, double coord[], int np) { \
    int iii,exit_code; exit_code=0;         \
    for(iii=0;iii<np;iii=iii+1){   \
      exit_code=map_##NAME(dataf,datai,elem_id,&coord[iii*ND]);  \
      if (exit_code<0){ break;};	\
    }; \
         return exit_code;       \
  }; \

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

int update_rot2d(double dataf[], int datai[], int elem_floatid) {
  double angle;
  angle=dataf[elem_floatid];
  dataf[elem_floatid+1]=cos(angle);
  dataf[elem_floatid+2]=sin(angle);
  return 1;
};

int update_kick2d(double dataf[], int datai[]) {
  return 1;
};

int update_counter(double dataf[], int datai[]) {
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
  int count,limit;
  printf("%lf %lf \n",coord[0],coord[1]);
  limit=datai[elem_id+5];
  count=datai[elem_id+4]++;
  if (count<limit){
    return 1;
  } else {
    return -1;
  };
};

make_vecmap(counter,2);

#define expr_TYPE 4

void update_gen(double dataf[], int datai[], int elem_id,int resi, double resf)
{
    int res_into,temp,type_id,res_type;
    res_into = datai[elem_id+4];
    res_type = datai[elem_id+5];
    temp = (res_into-2)/3;
    if(temp%2==0)
        datai[temp/2]=resi;
    else
        dataf[(temp-1)/2]=resf;
    switch(res_type)
    {
        case rot2d_TYPE: 
            update_rot2d(dataf,datai,(temp-1)/2); break;
        case kick2d_TYPE: 
            update_kick2d(dataf, datai); break;
        case counter_TYPE:
            update_counter(dataf, datai); break;
    }  
}

int map_expr(double dataf[], int datai[], int elem_id, double coord[])
{
    int i,len,temp;
    struct Elem out;
    int *results;
    double *constf;
    results = &datai[elem_id+7];
    constf = &dataf[datai[elem_id+2]];
    len = datai[elem_id+6];
    init_elem_stack();
    for(i=0;i<len;i++)
    {
        if(is_operator(dataf,datai,results[i])||(decode(dataf,datai,results[i])==op_constf))
        {   
            if(decode(dataf,datai,results[i])==op_constf)
            {
                op_CONSTF(constf);
                continue;
            }
            call_ops(decode(dataf,datai,results[i]));
        }
        else
        {
            if(is_variable(results[i]))
            {
                temp = decode(dataf,datai,results[i]);
                if(temp%2==0)
                    op_NUMi(datai[temp/2]);
                else
                    op_NUMf(dataf[(temp-1)/2]);
                continue;
            }
            op_NUMi(decode(dataf,datai,results[i]));
        }
    }
    out = elem_pop();
    if(out.type==INT) 
    {
        update_gen(dataf,datai,elem_id,out.data.i,0);
        //printf("%d\n",datai[(decode(dataf,datai,datai[elem_id+4]))/2]);  
    }  
    if(out.type==FLOAT)
    {
        update_gen(dataf,datai,elem_id,0,out.data.f);
        //printf("%f %f %f\n",dataf[0],dataf[1],dataf[2]);
    }
    return 1;
}

make_vecmap(expr,2);

/*
#define block_TYPE 5

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
    return elem_next;
};

make_vecmap(block,2);

void vec_map_loop(double dataf[], int datai[], int elem_id, double coord[], int coordi[]) {
  int elem_next;  
  elem_next=datai[elem_id+3];
  while(elem_next>=0){
    elem_next= vec_map_block(dataf, datai, elem_next, coord, coordi);
  };
};*/

/* datai={elem_id,elem_type,elem_floatid,next_elem,other...}
 */

int vec_map_loop(double dataf[], int datai[], double coord[], int coordi[]) {
  int retval,elem_id,elem_type,elem_next;
  elem_id=0;
  retval=1;
  while(retval>0){
    elem_id=datai[elem_id];
    elem_type=datai[elem_id+1];
    //elem_floatid=datai[elem_id+2];
    elem_next=datai[elem_id+3];	
    switch (elem_type) {
      case rot2d_TYPE:
        retval=map_vec_rot2d( dataf, datai, elem_id, coord, 1);
        break;
      case kick2d_TYPE:
        retval=map_vec_kick2d( dataf, datai, elem_id, coord, 1);
        break;
      case counter_TYPE:
        retval=map_vec_counter( dataf, datai, elem_id, coord, 1);
        break;
      case expr_TYPE:
        retval=map_vec_expr( dataf, datai, elem_id, coord, 1);
        break;
    };
    elem_id=elem_next;
  };
  return 1;
};














