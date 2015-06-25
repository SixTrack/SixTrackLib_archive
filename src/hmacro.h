#define ELEMINIT \
 INT elem_floatid; \
 elem_floatid=elemi[elemid+1];

#define GETATTRF(type,name) \
 FLOAT name;                     \
 name=elemf[elem_floatid+type##_float_##name];

#define SETATTRF(type,name,value)     \
 elemf[elem_floatid+type##_float_##name]=value;

#define GETATTRI(type,name)   \
 INT name ; \
 name=elemi[elemid+2+type##_int_##name];

#define SETATTRI(type,name,value)   \
 elemi[elemid+2+type##_int_##name]=value;
 
#define rot2d_TYPE 0
#define kick2d_TYPE 1
#define counter_TYPE 2
#define loop_TYPE 3
#define monitor_TYPE 4
#define drift_exact_TYPE 5

#define rot2d_float_angle  0
#define rot2d_float_cx  1
#define rot2d_float_sx  2
#define rot2d_int_i   0
#define rot2d_int_j   1

#define kick2d_float_k   0 
#define kick2d_int_i   0
#define kick2d_int_j   1
#define kick2d_int_o   2

#define counter_int_count_max 0
#define counter_int_count 1

#define monitor_float_dataf 0+ndf*last+i
#define monitor_int_count 0
#define monitor_int_nrec 1
#define monitor_int_skip 2
#define monitor_int_last 3
#define monitor_int_index 4+last
#define monitor_int_datai 4+nrec+ndf*last+i

#define drift_exact_float_L 0

#define INITPARTF \
 INT ndf, stf, pfstart; \
 ndf=parti[1]; \
 stf=parti[3]; \
 pfstart=stf+ndf*partid; 

#define INITPARTI \
 INT ndi, sti, pistart; \
 ndi=parti[2]; \
 sti=parti[4]; \
 pistart=sti+ndi*partid; 

#define GETPARTF(partid) \
 &partf[stf+ndf*partid]

#define GETPARTI(partid) \
 &parti[sti+ndi*partid]

#define GETCOORDF(type,name) \
 FLOAT name; \
 name=partf[pfstart+type##_##name];

#define SETCOORDF(type,name,value) \
 partf[pfstart+type##_##name]=value;

#define GETCOORDI(type,name) \
 INT name; \
 name=parti[pistart+type##_##name];

#define SETCOORDI(type,name,value) \
 parti[pistart+type##_##name]=value;


#define partf_p0 0
#define partf_beta0 1
#define partf_gamma0 2
#define partf_m0 3
#define partf_E0 4
#define partf_x 5
#define partf_px 6
#define partf_y 7
#define partf_py 8
#define partf_ds 9
#define partf_ps 10
#define partf_s 11
#define partf_m 12
#define partf_q 13