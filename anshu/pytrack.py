#compiling with PIC: 		$ gcc -c -Wall -Werror -fpic track.c
#creating shared library: 	$ gcc -shared -o libtrack.so track.o
#or simply use the makefile instead of the above two commands (which ignores the warning)
 
import ctypes, math
from ctypes import *

ctypes.cdll.LoadLibrary("/home/aviral/Desktop/SixTrack/Start/track.so") #or path of the shared object
libc = ctypes.CDLL("/home/aviral/Desktop/SixTrack/Start/track.so") 	#or path of the shared object

class RPNparser(object):
  parser = []
  constf = []

  op_add = "+"
  op_sub = "-"
  op_equ = "="
  op_mul = "*"
  op_div = "/"
  op_left = "("
  op_right = ")"
  op_pow = "^"
  op_lt = "<"
  op_gt = ">"
  op_ge = "GE"
  op_le = "LE"
  op_if = "IF"
  op_sin = "SIN"
  op_cos = "COS"
  op_sqrt = "SQRT"
  op_exp = "EXP"

  encode_opr={'+':3,'-':6,'=':9,'*':12,'/':15,'^':18,'<':24,'>':27,'LE':30,'GE':33, 'IF':36, 'SIN':39, 'COS':42, 'SQRT':45, 'EXP':48}

  op_associativity = {op_pow: "right", op_mul: "left", op_div: "left", op_add: "left", op_sub: "left", op_equ: "left", op_lt: "left", op_gt: "left", op_le: "left", op_ge: "left", op_if:"left", op_sin: "left", op_cos: "left", op_sqrt: "left", op_exp: "left"}

  op_precedence = {op_pow: 5, op_mul: 4, op_div: 4, op_add: 3, op_sub: 3, op_lt:2, op_gt:2, op_le:2, op_ge:2, op_sin: 1, op_cos: 1, op_sqrt: 1, op_exp: 4, op_equ: 1, op_if:0, op_left: -1, op_right: -1}

  def precedence(self,op):
    return self.op_precedence[op]

  def associativity(self,op):
    return self.op_associativity[op]

  def is_operator(self,c):
    return self.op_precedence.has_key(c) and not (self.is_left(c) or self.is_right(c))

  def is_left(self,c):
    return c == self.op_left

  def is_right(self,c):
    return c == self.op_right

  def append_token(self,token, l):
    if token != "":
        l.append(token)
    return ""

  def gen_token(self,expr):
    tokens = []
    last_token = ""
    in_token = False
    for c in expr:
        if c == " ":
            in_token = False
            last_token = self.append_token(last_token, tokens)
            continue
        elif self.is_operator(c) or self.is_right(c) or self.is_left(c):
            in_token = False
            last_token = self.append_token(last_token, tokens)
            tokens.append(c)
        else:
            in_token = True
            last_token += c
        if not in_token and last_token != "":
            last_token = self.append_token(last_token, tokens)
    if in_token:
        self.append_token(last_token, tokens)
    return tokens

  def __init__(self,seq,expr):
    ops = []
    results = []
    for token in self.gen_token(expr):
        #print ops, results
        if self.is_operator(token):
            while len(ops) > 0 and self.is_operator(ops[-1]) and \
                    ( (self.associativity(token) == 'left' and self.precedence(token) <= self.precedence(ops[-1])) \
                 or   (self.associativity(token) == 'right' and self.precedence(token) < self.precedence(ops[-1])) ):
                results.append(ops.pop())
            ops.append(token)
        elif self.is_left(token):
            ops.append(token)
        elif self.is_right(token):
            while len(ops) > 0 and not self.is_left(ops[-1]):
                results.append(ops.pop())
            if len(ops) == 0:
                print "error: mismatched parentheses"
                exit()
            if self.is_left(ops[-1]):
                ops.pop()
        else:
            results.append(token)
    while len(ops) > 0:
        if self.is_right(ops[-1]) or self.is_left(ops[-1]):
            print "error: mismatched parentheses"
            exit()
        results.append(ops.pop())
    self.parser,self.constf = self.encode(seq,results)  

  def encode(self,seq,expr):
    enc_res=[]
    constf=[]
    for tok in expr:
        if tok.isdigit()==True:
            enc_res.append(3*eval(tok)+1)
        elif tok.replace('.','',1).isdigit():
            enc_res.extend([3*len(constf)+1,21])
            constf.append(eval(tok))
        elif self.encode_opr.has_key(tok):
            enc_res.append(self.encode_opr[tok])
        else:
            to_append, neglect = seq.search(tok)
            enc_res.append(to_append)
    seq.datai.extend([len(enc_res)])
    seq.datai.extend(enc_res)
    seq.dataf.extend(constf)
    return enc_res, constf

class Rot2d(object):
  _typeid=1
  def __init__(self,Element,**argsv):
    self._parameters={'angle':(0.0,1,0),'cx':(1.0,1,1),'sx':(0.0,1,2)}
    self.name = Element
    keys = sorted(argsv.keys())
    self._parameters[keys[0]]=(argsv[keys[0]],1,0)
    self._parameters['cx'] = (math.cos(argsv[keys[0]]),1,1)
    self._parameters['sx'] = (math.sin(argsv[keys[0]]),1,2)

class Kick2d(object):
  _typeid=2
  def __init__(self,Element,**argsv):
    self._parameters={'kv':(0.0,1,0),'order':(0,0,0)}
    self.name = Element
    keys = sorted(argsv.keys())
    self._parameters[keys[0]]=(argsv[keys[0]],1,0)
    self._parameters[keys[1]]=(argsv[keys[1]],0,0)

class Counter(object):
  _typeid=3
  def __init__(self,Element,**argsv):
    self._parameters={'limit':(0,0,0),'count':(0,0,1)}
    self.name = Element
    keys = sorted(argsv.keys())
    self._parameters[keys[0]]=(argsv[keys[0]],0,0)
    self._parameters[keys[1]]=(argsv[keys[1]],0,1)

class Expression(object):
  _typeid=4
  def __init__(self,Element,**argsv):
    self.name = Element

class Sequence(object):
  datai=[]
  dataf=[]
  coord=[]
  coordi=[]

  def __init__(self):
    self.elems={}
    self.lst=[]  

  def add_rot(self,label,angle):
    newid=len(self.datai)
    newfid=len(self.dataf)
    self.lst.extend([newid])
    self.datai.extend([newid,1,newfid,None])
    self.dataf.extend([angle,math.cos(angle),math.sin(angle)])
    self.add_elem(label,Rot2d,newid,angle=angle)

  def add_kick(self,label,kv,order):
    newid=len(self.datai)
    newfid=len(self.dataf)
    self.lst.extend([newid])
    self.datai.extend([newid,2,newfid,None,order])
    self.dataf.extend([kv])
    self.add_elem(label,Kick2d,newid,kv=kv,order=order)

  def add_count(self,label,limit,count):
    newid=len(self.datai)
    newfid=len(self.dataf)
    self.lst.extend([newid])
    self.datai.extend([newid,3,newfid,None,limit,count])
    self.dataf.extend([])
    self.add_elem(label,Counter,newid,limit=limit,count=count)

  def add_expr(self,label,var_into,expr):
    newid=len(self.datai)
    newfid=len(self.dataf)
    self.lst.extend([newid])
    res_into, res_into_type = self.search(var_into)
    self.datai.extend([newid,4,newfid,None,res_into,res_into_type])
    RPNparser(self,expr)
    self.add_elem(label,Expression,newid)   

  def add_elem(self,name,eltype,elem_id,**argsv):
    el=eltype(name,**argsv)
    self.elems[name]=(el,elem_id)

  def search(self,label):
    tag=label.split('.')  
    if self.elems[tag[0]][0]._parameters.has_key(tag[1])==True:
        main = self.elems[tag[0]][1]
        choice = self.elems[tag[0]][0]._parameters[tag[1]][1]
        offset = self.elems[tag[0]][0]._parameters[tag[1]][2]
    if choice==0:
      ret = 2*(main+offset+4)
    if choice==1:
      ret = 2*(self.datai[main+2]+offset)+1
    return 3*ret+2, self.elems[tag[0]][0]._typeid 

  def join(self):
    self.lst.extend([None])		
    i=1
    for index, value in enumerate(self.datai): 
      if value==None:
        if self.lst[i]==None:
          self.datai[index]=self.datai[0]
        else:
          self.datai[index]=self.lst[i]
          i = i+1
    return self

  def track(self,coord,coordi):
    self.join()
    self.coord = coord
    self.coordi = coordi
    arg_coordi=(ctypes.c_int *len(self.coordi))()
    arg_datai=(ctypes.c_int *len(self.datai))()
    arg_dataf=(ctypes.c_double *len(self.dataf))()
    arg_coord=(ctypes.c_double * len(self.coord))()
    arg_coordi=(ctypes.c_int * len(self.coordi))()
    for index, value in enumerate(self.datai):	
      arg_datai[index] = int(value) 
    for index, value in enumerate(self.dataf):
      arg_dataf[index] = float(value)
    for index, value in enumerate(self.coord):
      arg_coord[index] = float(value)
    for index, value in enumerate(self.coordi):
      arg_coordi[index] = int(value)
    val = libc.vec_map_loop(arg_dataf,arg_datai,arg_coord,arg_coordi)
    return self

seq = Sequence()
seq.add_rot("rot1",0.245)
seq.add_rot("rot2",0.3*math.pi) 
seq.add_kick("kick1",0.1,3)
seq.add_count("cnt",1,250)
#seq.add_expr("exp1","rot1.angle","IF (cnt.count<100) (0.245) (IF (cnt.count<200) (0.245+(cnt.count-100)*0.00001) 0.246)")
seq.add_expr("exp1","rot1.angle","0.33*2*3.14+0.01*SIN (2*3.14*0.1*cnt.count)")
seq.track([1.0,1.0],[1,2])
#rpn=RPNparser(seq,"IF (1 GE 0.9) 9 10")
#print rpn.parser
#seq.search("cnt.count")
#rpn = RPNparser("3.2+2.1")
#seq.join()
#print seq.datai
#print seq.dataf
#print rpn.parser, rpn.constf
