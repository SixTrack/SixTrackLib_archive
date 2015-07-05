#define OnePoweredToMinus38       1.0e-38
#define OnePoweredTo3             1.0e3
#define Pi                        4.0*atan(1.0)

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
 
#define rot2d_TYPE                                              0
#define kick2d_TYPE                                             1
#define counter_TYPE                                            2
#define loop_TYPE                                               3
#define monitor_TYPE                                            4
#define drift_exact_TYPE                                        5
#define rf_cavity_TYPE                                          6
#define horizontal_dipole_TYPE                                  7
#define vertical_dipole_TYPE                                    8 

#define rot2d_float_angle                                       0
#define rot2d_float_cx                                          1
#define rot2d_float_sx                                          2
#define rot2d_int_i                                             0
#define rot2d_int_j                                             1

#define kick2d_float_k                                          0 
#define kick2d_int_i                                            0
#define kick2d_int_j                                            1
#define kick2d_int_o                                            2

#define counter_int_count_max                                   0
#define counter_int_count                                       1

#define monitor_float_dataf                                     0+ndf*last+i
#define monitor_int_count                                       0
#define monitor_int_nrec                                        1
#define monitor_int_skip                                        2
#define monitor_int_last                                        3
#define monitor_int_index                                       4+last
#define monitor_int_datai                                       4+nrec+ndf*last+i

#define drift_exact_float_L                                     0

#define rf_cavity_float_dppoff                                  0
#define rf_cavity_float_ElementType                             1
#define rf_cavity_float_FirstAdditionalDatum                    2
#define rf_cavity_float_FrequencyOfCavity                       3
#define rf_cavity_float_LagPhaseOfCavity                        4
#define rf_cavity_float_VoltageOfCavity                         5
#define rf_cavity_float_RFFrequencyOfCavity                     6
#define rf_cavity_float_PathLengthOffset                        7

#define vertical_dipole_float_L                                 0
#define vertical_dipole_float_TiltComponentCos                  1
#define vertical_dipole_float_TiltComponentSin                  2

#define horizontal_dipole_float_L                               0
#define horizontal_dipole_float_TiltComponentCos                1
#define horizontal_dipole_float_TiltComponentSin                2

#define normal_pole_float_L                                     0
#define normal_pole_float_TiltComponentCos                      1
#define normal_pole_float_TiltComponentSin                      2
#define normal_pole_float_CurrentEntryDisplacementX             3
#define normal_pole_float_CurrentEntryDisplacementY             4

#define skew_pole_float_L                                       0
#define skew_pole_float_TiltComponentCos                        1
#define skew_pole_float_TiltComponentSin                        2
#define skew_pole_float_CurrentEntryDisplacementX               3
#define skew_pole_float_CurrentEntryDisplacementY               4

#define beambeam_float_HorBeamBeamSeparation              		0
#define beambeam_float_VerBeamBeamSeparation              		1
#define beambeam_float_L						            	2
#define beambeam_float_ClosedOrbitBeamX                  		3
#define beambeam_float_ClosedOrbitBeamY                			4
#define beambeam_float_ClosedOrbitBeamSigma               		5
#define beambeam_float_ClosedOrbitBeamPx                  		6
#define beambeam_float_ClosedOrbitBeamPy                  		7
#define beambeam_float_ClosedOrbitBeamDelta              		8
#define beambeam_float_BeamOffsetX                       		9
#define beambeam_float_BeamOffsetY                        		10
#define beambeam_float_BeamOffsetSigma                    		11
#define beambeam_float_BeamOffsetPx                       		12
#define beambeam_float_BeamOffsetPy                       		13
#define beambeam_float_BeamOffsetDelta                    		14
#define beambeam_float_bbcu11                             		15
#define beambeam_float_bbcu12                             		16
#define beambeam_float_SigmaNqX                           		17
#define beambeam_float_SigmaNqY                     		    18
#define beambeam_float_SquareOfSigmaNX                    		19
#define beambeam_float_SquareOfSigmaNY                    		20
#define beambeam_int_SwitchToLinearCoupling               		0
#define beambeam_int_NoOfParticles               				1
#define beambeam_int_SwitchToFastBeamBeamAlgo               	2
#define beambeam_int_BeambeamType               				3

#define multipole_ver_float_L                                   0
#define multipole_ver_float_TiltComponentCos                    1
#define multipole_ver_float_TiltComponentSin                    2
#define multipole_ver_float_CurrentEntryDisplacementX           3
#define multipole_ver_float_CurrentEntryDisplacementY           4
#define multipole_ver_float_VerticalBendingKick                 5
#define multipole_ver_int_ApproxType                            0

#define multipole_hor_float_L                                   0
#define multipole_hor_float_TiltComponentCos                    1
#define multipole_hor_float_TiltComponentSin                    2
#define multipole_hor_float_CurrentEntryDisplacementX           3
#define multipole_hor_float_CurrentEntryDisplacementY           4
#define multipole_hor_float_HorizontalBendingKick               5
#define multipole_hor_int_ApproxType                            0

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


#define partf_p0                                                0
#define partf_beta0                                             1
#define partf_gamma0                                            2
#define partf_m0                                                3
#define partf_E0                                                4
#define partf_x                                                 5
#define partf_px                                                6
#define partf_y                                                 7
#define partf_py                                                8
#define partf_ds                                                9
#define partf_ps                                                10
#define partf_s                                                 11
#define partf_m                                                 12
#define partf_q                                                 13
//following are not mentioned in the wiki
#define partf_RatioPtoPj 4
#define partf_EnergyOfParticle 6
#define partf_MomentumOfParticle 7
#define partf_RatioDeltaPtoPj 8
#define partf_RatioDeltaPtoPj1 9
#define partf_RatioBetaToBetaj 12
#define partf_MomentumOfParticle0 13
#define partf_crxbj 10
#define partf_crzbj 11
#define partf_cbxbj 3
#define partf_cbzbj 2