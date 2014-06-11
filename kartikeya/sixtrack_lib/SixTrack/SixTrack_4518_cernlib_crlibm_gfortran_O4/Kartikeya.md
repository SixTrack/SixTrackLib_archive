For coord Array:            <br>
<br>
Description                    ----------------        SixTrack       ----------------    SixTrackLib            <br>
--------------------------------------------------------------------------           <br>
x-horizontal position [mm]     ----------------        xv(1,j)        ----------------      x                <br>
y-vertical position  [mm]      ----------------        xv(2,j)        ----------------      y                    <br>
x'-horizontal direction        ----------------        yv(1,j)        ----------------      xp                    <br>
y'-vertical direction          ----------------        yv(2,j)        ----------------      yp                     <br>
Path length difference [mm]    ----------------        sigmv(j)       ----------------    PathLengthDiff            <br>
Total energy [MeV]             ----------------        ejv(j)         ----------------    EnergyOfParticle            <br>
Momentum [MeV/c]               ----------------        ejfv(j)        ----------------    MomentumOfParticle            <br>
Delta(p) / p                   ----------------        dpsv(j)        ----------------    RatioDeltaPtoPj              <br>
1000*(Delta(p)/p)/(1+Delta(p)/p)----------------       dpsv1(j)       ----------------    RatioDeltaPtoPj1                   <br>
1+Delta(p)/p                   ----------------        dpd(j)         ----------------    OnePlusRatioDeltaPtoP               <br>
sqrt(1+Delta(p)/p )            ----------------        dpsq(j)        ----------------    SqrtOnePlusRatioDeltaPtoP			<br>
p / p(j)                       ----------------        oidpsv(j)      ----------------    RatioPtoPj				<br>
Beta / Beta(j)                 ----------------        rvv(j)         ----------------    RatioBetaToBetaj			<br>
			<br>
<br>
For argf Array:										<br>
												<br>
Description                    ----------------        SixTrack       ----------------    SixTrackLib				<br>
--------------------------------------------------------------------------			<br>
BLOC : physical length [m]     ----------------      strack(i)        ----------------   PhysicalLengthOfBlock			<br>
strack(i)*tiltc(i)             ----------------      strackc(i)       ----------------   LengthElementTiltCos		<br>
strack(i)*tilts(i)             ----------------      stracks(i)       ----------------   LengthElementTiltSin		<br>
cos(extalign(i,3)*c1m3)        ----------------      tiltc(i)         ----------------   TiltComponentCos			<br>
sin(extalign(i,3)*c1m3)        ----------------      tilts(i)         ----------------   TiltComponentSin		<br>
displacement of current entry  ----------------     								<br>
 in the horizontal direction   ----------------      xsiv(1,i)        ----------------   CurrentEntryDisplacementX		<br>
displacement of current entry  ----------------     								<br>
 in the vertical  direction    ----------------      zsiv(1,i)        ----------------   CurrentEntryDisplacementY			<br>
Frequency Of Crab Cavity       ----------------      crabfreq         ----------------    FrequencyCrabCavity		<br>
Amplitude crab cavity order2   ----------------      crabamp2         ----------------    AmplitudeCrabCavity2			<br>
 Phase of crab Cavity order2   ----------------      crabph2(ix)      ----------------    PhaseCrabCavity4			<br>
First Additional Datum         ----------------        ed(ix)         ----------------     FirstAdditionalDatum			<br>
Second Additional Datum        ----------------        ek(ix)         ----------------     SecondAdditionalDatum			<br>
1.0^3                          ----------------      c1e3             ----------------    OnePoweredTo3			<br>
1.0^-3                         ----------------      c1m3             ----------------    OnePoweredToMinus3				<br>
Speed Of Light                 ----------------     clight            ----------------   SpeedOfLight			<br>
total energy of the reference  ----------------		<br>
 particle [MeV]                ----------------      e0               ----------------   EnergyOfReferenceParticle			<br>
momentum of the reference 									<br>	
particle [MeV/c]               ----------------      e0f              ----------------   MomentumOfReferenceParticle		<br>	
rest mass of the tracked       									<br>
particles [MeV/c^2]            ----------------      pma              ----------------  RestMassOfParticle		<br>
1.0^-38                        ----------------      pieni            ----------------   OnePoweredToMinus38		<br>
Path Length Offset             ----------------     sigmoff(i)        ----------------   PathLengthOff		<br>
second datum in element 								<br>
declaration, interpreted as type----------------    kz(ix)            ----------------   ElementType			<br>
frequency' of the cavity       ----------------    hsyc(ix)           ----------------   FrequencyOfCavity			<br>
lag phase of the cavity        ----------------     phasc(ix)         ----------------   LagPhaseOfCavity			<br>
voltage of each cavity         ----------------     hsy(1)            ----------------   VoltageOfCavity			<br>
RF frequency of the cavity     ----------------     hsy(3)            ----------------   RFFrequencyOfCavity			<br>
horizontal bending kick [rad]									<br>
 of a multipole block          ----------------    dki(ix,1)          ----------------   HorizontalBendingKick			<br>
Switch to turn on linear 									<br>
coupling (0: off, 1: on)       ----------------    ibbc               ----------------    SwitchToLinearCoupling		<br>
Closed Orbit X coordinate      ----------------  clobeam(1,imbb(i))   ----------------    ClosedOrbitBeamX			<br>
Closed Orbit Y coordinate      ----------------  clobeam(2,imbb(i))   ----------------    ClosedOrbitBeamY			<br>
Closed Orbit Sigma coordinate  ----------------  clobeam(3,imbb(i))   ----------------    ClosedOrbitBeamSigma			<br>
Closed Orbit Px coordinate     ----------------  clobeam(4,imbb(i))   ----------------    ClosedOrbitBeamPx		<br>
Closed Orbit Py coordinate     ----------------  clobeam(5,imbb(i))   ----------------    ClosedOrbitBeamPy				<br>
Closed Orbit Delta coordinate  ----------------  clobeam(6,imbb(i))   ----------------    ClosedOrbitBeamDelta		<br>
Square Of SigmaN for X         ----------------  sigman2(1,imbb(i))   ----------------    SquareOfSigmaNX			<br>
Square Of SigmaN for Y         ----------------  sigman2(2,imbb(i))   ----------------    SquareOfSigmaNY			<br>
Beam Offset X                  ----------------   beamoff(1,imbb(i))  ----------------     BeamOffsetX		<br>
Beam Offset Y                  ----------------   beamoff(2,imbb(i))  ----------------     BeamOffsetY		<br>
Beam Offset Sigma              ----------------   beamoff(3,imbb(i))  ----------------     BeamOffsetSigma			<br>
Beam Offset Px                 ----------------   beamoff(4,imbb(i))  ----------------     BeamOffsetPx		<br>
Beam Offset Py                 ----------------   beamoff(5,imbb(i))  ----------------     BeamOffsetPy			<br>
Beam Offset Delta              ----------------   beamoff(6,imbb(i))  ----------------     BeamOffsetDelta		<br>
No Description available in Doc----------------   bbcu(imbb(i),11)    ----------------     bbcu11			<br>
No Description available in Doc----------------   bbcu(imbb(i),12)    ----------------     bbcu12			<br>
		
