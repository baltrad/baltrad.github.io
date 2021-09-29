# *1. Algorithm name*
Quality characterization due to distance to radar related effects (as a part of RADVOL-QC package) – RADVOL-QC: BROAD

# *2. Basic description*
## *a) Physical basis of the algorithm*
Evaluation of data quality related to radar beam broadening

## *b) Amount of validation performed so far*
Works operationally in IMGW since 2011 to correct data before using for Meteo Flight system (for air traffic control).

## *c) References (names and contact information of all developers during the evolutionary history, scientific papers)*
* Operational work: IMGW, Department of  Ground Based Remote Sensing.
* Scientific paper: Ośródka, K., Szturc, J., and Jurczyk, A., 2012. Chain of data quality algorithms for 3-D single-polarization radar reflectivity (RADVOL-QC system). _Meteorol. Appl._ (Early View).

# *3. ODIM metadata requirements for I/O*
* Top-level “how”: beamwidth, pulsewidth.
* Dataset-specific “what”: gain, offset, nodata, undetect.
* Dataset-specific “where”: elangle, nbins, nrays, rscale.

# *4. Input data*
## *a) What kind of radar data (including the list of previous algorithms and quality flags applied)*
object=PVOL or SCAN; quantity=DBZH, otherwise TH.

## *b) Other data (optional and mandatory, applying “universally” agreed formats, geometry)*
None

# *5. Logical steps, using any of: text, flow charts, graphics, equations (or references to equations), conditional branches in “all possible cases”.*
The horizontal and vertical broadening of radar beam for each gate can be computed when its polar coordinates are known: _ε'' (elevation angle), ''α'' (azimuth angle), and ''l'' (radial distance to radar site in km), and two parameters of radar beam: ''φ'' (beam width) and ''P<sub>L</sub>_ (measurement gate length in km) calculated from radar pulse length.

![Fig BROAD.gif](/images/Fig_1_BROAD.gif)

Set of the algorithm parameters:

| Description | Denotation | Default value |
| Maximum _L<sub>H</sub>'' for which ''QI<sub>LH</sub>_ = 1 | BROAD_LhQI1 | 1.1 |
| Minimum _L<sub>H</sub>'' for which ''QI<sub>LH</sub>_ = 0 | BROAD_LhQI0 | 2.5 |
| Maximum _L<sub>V</sub>'' for which ''QI<sub>LV</sub>_ = 1 | BROAD_LvQI1 | 1.6 |
| Minimum _L<sub>V</sub>'' for which ''QI<sub>LV</sub>_ = 0 | BROAD_LvQI0 | 4.3 |
| Pulse length (km) - radar parameter | BROAD_Pulse | 0.3 |

At first the XML file is checked whether there exists group for a considered radar (based on the radar name read from "what"/source(NOD)), which contains the algorithm parameters. If "yes", then parameters are read from that XML group, but if it is impossible for a particular parameter, then default value from source code is taken. If the group does not exist, parameters are read from <default> group in XML file in analogous way.

If the algorithm is run by means of BALTRAD toolbox then all the algorirthm parameters for each specific radar should be placed in relevant XML file by the BALTRAD system admin. Parameters included in HDF5 file are used in cases they are not found in XML file. Default parameters are placed in the XML file by admin as well. Moreover, the algorithm default parameters are also included in software.

The horizontal and vertical broadenings _L<sub>H</sub>'' and ''L<sub>V</sub>_ are described by the following formulae calculated from vertical cross-section through radar beam:

<img src="https://render.githubusercontent.com/render/math?math={L_{H}} = ({l}+\frac{P_L}{2}) \cos(\epsilon-\frac{\phi}{2}) - ({l}-\frac{P_L}{2}) \cos(\epsilon+\frac{\phi}{2})" />

<img src="https://render.githubusercontent.com/render/math?math={L_{V}} = ({l}+\frac{P_L}{2}) \sin(\epsilon+\frac{\phi}{2}) - ({l}-\frac{P_L}{2}) \sin(\epsilon-\frac{\phi}{2})" />

<!--	
	#!latex 
	$ {L_{H}} = ({l}+\frac{P_L}{2}) \cos(\epsilon-\frac{\phi}{2}) - ({l}-\frac{P_L}{2}) \cos(\epsilon+\frac{\phi}{2})  $,
	
	$ {L_{V}} = ({l}+\frac{P_L}{2}) \sin(\epsilon+\frac{\phi}{2}) - ({l}-\frac{P_L}{2}) \sin(\epsilon-\frac{\phi}{2})  $.
-->	
	
Assuming linear relationships _L<sub>H</sub>'' => ''QI<sub>LH</sub>'' and ''L<sub>V</sub>'' => ''QI<sub>LV</sub>_, the following formulas can be applied:

<img src="https://render.githubusercontent.com/render/math?math=QI_{LH} = \begin{cases}
1\qquad\qquad\qquad \text{for\ } L_H<\text{BROAD}\_\text{LhQI1} \\
\frac {\text{BROAD}\_\text{LhQI0 }-\text{ }L_H}{\text{BROAD}\_\text{LhQI0 }-\text{ BROAD}\_\text{LhQI1}}\qquad \text{for\ } \text{BROAD}\_\text{LhQI1}<=L_{LH}<=\text{BROAD}\_\text{LhQI0} \\
0\qquad\qquad\qquad \text{for\ } L_H>\text{BROAD}\_\text{LhQI1}\end{cases}" />

<img src="https://render.githubusercontent.com/render/math?math=QI_{LV} = \begin{cases}
1\qquad\qquad\qquad \text{for\ } L_V<\text{BROAD}\_\text{LvQI1} \\
\frac {\text{BROAD}\_\text{LvQI0 }-\text{ }L_V}{\text{BROAD}\_\text{LvQI0 }-\text{ BROAD}\_\text{LvQI1}}\qquad \text{for\ } \text{BROAD}\_\text{LvQI1}<=L_{LV}<=\text{BROAD}\_\text{LvQI0} \\
0\qquad\qquad\qquad \text{for\ } L_V>\text{BROAD}\_\text{LvQI1}\end{cases}" />

<!--	
	#!latex 
	$ QI_{LH} = \begin{cases}
	1                                 & \textrm{for\ } L_H<\text{BROAD}\_\text{LhQI1} \\
	\frac {\text{BROAD}\_\text{LhQI0 }-\text{ }L_H}{\text{BROAD}\_\text{LhQI0 }-\text{ BROAD}\_\text{LhQI1}} & \textrm{for\ } \text{BROAD}\_\text{LhQI1}<=L_{LH}<=\text{BROAD}\_\text{LhQI0} \\
	0                                 & \textrm{for\ } L_H>\text{BROAD}\_\text{LhQI1}
	\end{cases} $,
	
	$ QI_{LV} = \begin{cases}
	1                                 & \textrm{for\ } L_V<\text{BROAD}\_\text{LvQI1} \\
	\frac {\text{BROAD}\_\text{LvQI0 }-\text{ }L_V}{\text{BROAD}\_\text{LvQI0 }-\text{ BROAD}\_\text{LvQI1}} & \textrm{for\ } \text{BROAD}\_\text{LvQI1}<=L_{LV}<=\text{BROAD}\_\text{LvQI0} \\
	0                                 & \textrm{for\ } L_V>\text{BROAD}\_\text{LvQI1}\end{cases} $.
-->	
	
where boundary values can be estimated empirically.

Finally:

<img src="https://render.githubusercontent.com/render/math?math=QI_{BROAD} = QI_{LH} \cdot QI_{LV}" />

<!--	
	#!latex 
	$ QI_{BROAD} = QI_{LH} \cdot QI_{LV}  $
-->	
	
# *6. Output*
## a) Quality index (_QI_) field
Quality index (_QI_ 1 for excellent data) with "pl.imgw.radvolqc.broad" in quality-specific "how"/task, and the algorithm parameters in "how"/task_args.

# *7. Outline of a test concept exemplifying the algorithm, as a suggestion for checking that an implementation has been successful.*
