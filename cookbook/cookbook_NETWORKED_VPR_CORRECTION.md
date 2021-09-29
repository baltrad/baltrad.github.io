# 2. Basic description
## a) Physical basis of the algorithm
The vertical profile of radar reflectivity factor (VPR) and the measurement geometry of weather radar introduce a vertical sampling difference between the actual precipitation at ground level and the radar estimate of it. VPR correction is used to modify the measured values so that they represent the precipitation conditions at ground level more accurately. The networked VPR correction described here denotes that the correction is calculated in radar networks so that the adjustment factor field will be continuous, not introducing additional steps at the seam lines where measured data from neighboring radars meet.
## b) Amount of validation performed so far
Algorithm is implemented and used operationally at FMI since the year 2004. Validation has been performed applying gauge-radar and radar-radar comparisons.
## c) References (names and contact information of all developers during the evolutionary history, scientific papers)
Operational estimation of ground level reflectivity in radar networks applying ensembles of VPR corrections.
Jarmo Koistinen and Heikki Pohjola
Article isn't published yet.
# 3. ODIM metadata requirements for I/O
/dataset/what: gain, offset, nodata
# 4. Input data
## a) What kind of radar data (including the list of previous algorithms and quality flags applied)
Full volume scan reflectivity data(for each radar). At FMI the VPR correction for a 500 m PseudoCAPPI composite is performed presently applying the 4 lowest elevation angles from each radar. Other number of elevations can be applied according to the user selections.
## b) Other data (optional and mandatory, applying “universally” agreed formats, geometry)
The classification scheme of VPRs embedded into the correction algorithm and used in real time requires that the height of the freezing level is known at each radar site at each volume scan moment. At FMI that is estimated from NWP nowcasting data applying the HIRLAM model fields of temperature.
# 5. Logical steps

![VPR Correction](/images/VPRCorrection20120910.png)

## Equations

![VPR Equations](/images/VPR_equations.png)
	
<!--	
	#!latex
	Measured radar reflectivity factor along a slant radial at distance $r$ and height $h$ (height of the beam center) above the antenna can be calculated with equation
	\[
	Z_e(h,r) = \int_{h_s(r)}^{H(r)} f^2[h(r)-y]Z_e(y)dy,\qquad(1)
	\]
	where $h_s$ is the upper edge of the shielding, $f$ the one way normalized power density pattern in the beam, $H$ is an arbitrary height $(H \gg h)$, where $f$ becomes insignificantly small to contribute to the measured reflectivity factor, $Z_e(y)$ is the true verticalprofile of reflectivity and $y$ is the vertical co-ordinate.
	
	
	Vertical sampling differencebetween the ground level reflectivity and that at the measurement aloft is given by the equation
	\[
	S(h,r) = 10\log\frac{Z_e(0,r)}{Z_e(h,r)},\qquad(2)
	\]
	where $Z_e(0,r)$ is radar reflectivity factor at ground level and $Z_e>0$ at both heights.
	
	Ground level reflectivity factor estimate is obtained from the equation
	\[
	dBZ(0,r) = dBZ(h,r) + S^0(h,r),\qquad(3)
	\]
	where $dBZ(h,r)$ is the measured reflectivity aloft and $dBZ(0,r)$ the estimated reflectivity at ground, vertically below the measurement.
	
	Quantitative Precipitation Estimate (QPE) quality of the entire measured VPR, $q_p$ can be calculated with equation
	\[
	q_p = \frac{\sum_{y_0}^{y_{top}}N(y_i)\sigma(y_i)}{\sum_{y_0}^{y_{top}}N_{max}\sigma(y_i)}\qquad(4)
	\]
	where $y_0$ is the height of the radar antenna, $y_{top}$ is the height of the top of the profile and $N(y_i)$ is the bin count in each layer $y_i$. $\sigma(y_i) = 0$ when $N(y_i) < 30$
	and $\sigma(y_i) = 1$ when $30\leq N(y_i)\leq N_{max}$
	
	
	Member in the time ensemble of virtual VPR corrections at single radar is calculated from the equation
	\[
	S_{pc} \frac{S_p^0(h,r,t)q_p(t) + S_c(h,r,t)q_c(t)}{q_p(t)+q_c(t)},\qquad(5)
	\]
	where $S_p^0(h,r,t)$ is the VPR correction based on the measured precipitation profile and $S_c(h,r,t)$ is the correction based on the climatological profile at time moment $t$
	and height $h$ at distance $r$ from the radar. $q_p(t)$ and $q_c(t)$ are quality weights given for the measured and climatological profiles.
	
	
	Time ensemble member corrections can be calculated with equation
	\[
	\overline{S}_{pc}(h,r,t_0) = \frac{\sum_{t=t_0-6h}^{t_0}[q_t(t)S_{pc}(h,r,t)]}{\sum_{t=t_0-6h}^{t_0}[q_t(t)]}\qquad(6)
	\]
	where time weights $q_t$ of the individual ensemble members can be calculated with equation
	\[
	q_t(t)=1-\frac{t_0-t}{360 min},\qquad(7)
	\]
	where the age of the profile $t_0-t$ is located between $0$ and $360$ minutes. Collections older than $6$ h obtain weight $0$.
	
	Spatial weight coefficient $q_{r_j}$ can be calculated from the equation
	\[
	q_{r_j} = \frac{(r_{max} - r_j)^2}{r_{max}^2}\qquad(8)
	\]
	
	where $r_j$ is the range of a grid point in the network composite from radar j and $r_{max} = 300$ is the maximum range allowed. If $r_j\>r_{max}$ then $q_{r_j}=0$. 
	
	Magnitude of the contributing operational VPR correction can be calculated with equation
	\[
	\overline{S_{pcn}}(h,r,t_0)=\frac{\sum_{j=1}^{j=n}(q_{r_j}\overline{S_{{pc}_j}}(h,r,t_0))}{\sum_{j=1}{j=n}q_{r_j}},\qquad(9)
	\]
	where $n$ is the number of radars within the radius of $300$ km from a network composite pixel, $q_{r_j}$ is range weight for radar $j$ (Eq.8) and $\overline{S_{pc_j}}(h,r,t_0)$ is the $6$-hourly time ensemble correction for radar $j$ (Eq.6).
-->	

# 6. Output.
## a) Data type using ODIM notation where possible, e.g. DBZH
## b) Added quality indicators
# 7. Outline of a test concept exemplifying the algorithm, as a suggestion for checking that an implementation has been successful.
