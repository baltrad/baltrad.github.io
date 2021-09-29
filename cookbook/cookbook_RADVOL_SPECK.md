# *1. Algorithm name*
Removal of measurement noise and quality characterization (as a part of RADVOL-QC package) – RADVOL-QC: SPECK

# *2. Basic description*
## *a) Physical basis of the algorithm*
Investigation of echo patterns to detect non-meteorological echoes such as specks and reverse specks.

## *b) Amount of validation performed so far*
Works operationally in IMGW since 2011 to correct data before using for Meteo Flight system (for air traffic control).

## *c) References (names and contact information of all developers during the evolutionary history, scientific papers)*
* Operational work: IMGW, Department of  Ground Based Remote Sensing.
* Scientific paper: Ośródka, K., Szturc, J., and Jurczyk, A., 2012. Chain of data quality algorithms for 3-D single-polarization radar reflectivity (RADVOL-QC system). _Meteorol. Appl._ (Early View).

# *3. ODIM metadata requirements for I/O*
* Dataset-specific “what”: gain, offset, nodata, undetect.
* Dataset-specific “where”: elangle, nbins, nrays, rscale.

# *4. Input data*
## *a) What kind of radar data (including the list of previous algorithms and quality flags applied)*
object=PVOL or SCAN; quantity=DBZH, otherwise TH.

## *b) Other data (optional and mandatory, applying “universally” agreed formats, geometry)*
None

# *5. Logical steps, using any of: text, flow charts, graphics, equations (or references to equations), conditional branches in “all possible cases”.*
Generally, the specks are isolated radar gates with or without echo.

*Set of the algorithm parameters*

| Description | Denotation | Default value |
| QI,,SPECK,, value for speck | SPECK_QI | 0.9 |
| QI,,SPECK,, value for uncorrected speck | SPECK_QIUn | 0.5 |
| A. Reverse speck vicinity | SPECK_AGrid | 1 |
| A. Maximum of non-rainy gates | SPECK_ANum | 2 |
| A. Number of reverse speck removal subalgorithm cycles | SPECK_AStep | 1 |
| B. Speck vicinity | SPECK_BGrid | 1 |
| B. Maximum of rainy gates | SPECK_BNum | 2 |
| B. Number of speck removal subalgorithm cycles | SPECK_BStep | 2 |

At first the XML file is checked whether there exists group for a considered radar (based on the radar name read from "what"/source(NOD)), which contains the algorithm parameters. If "yes", then parameters are read from that XML group, but if it is impossible for a particular parameter, then default value from source code is taken. If the group does not exist, parameters are read from <default> group in XML file in analogous way. 

If the algorithm is run by means of BALTRAD toolbox then all the algorirthm parameters for each specific radar should be placed in relevant XML file by the BALTRAD system admin. Default parameters are placed in the file by admin as well. Moreover, the algorithm default parameters are also included in software. 

*Reverse specks removal*

So called reverse specks are isolated gates without radar echo (_Z'' = –32 dBZ) surrounded by precipitation field. The introduced subalgorithm is employed to each elevation scan separately. A vicinity of a given gate (''α'', ''l'') ±SPECK_AGrid gates is considered. Number of non-echo gates ''s,,rspeck,,''(''α'', ''l_) in the grid is calculated from:

<img src="https://render.githubusercontent.com/render/math?math=s_{rspeck}(\alpha ,l) = \sum_{m=\alpha -\text{SPECK}\_\text{AGrid}}^{\alpha %2B\text{SPECK}\_\text{AGrid}}  \sum_{n=l-\text{SPECK}\_\text{AGrid}}^{l%2B\text{SPECK}\_\text{AGrid}}  {f_{rspeck}(m,n)}">

<!--	
	#!latex 
	$  s_{rspeck}(\alpha ,l) = \sum_{m=\alpha -\text{SPECK}\_\text{AGrid}}^{\alpha +\text{SPECK}\_\text{AGrid}}  \sum_{n=l-\text{SPECK}\_\text{AGrid}}^{l+\text{SPECK}\_\text{AGrid}}  {f_{rspeck}(m,n)}  $
-->	

where:

<img src="https://render.githubusercontent.com/render/math?math=f_{rspeck}(m,n) = \begin{cases}
1\qquad\qquad \text{for\ } Z(m,n) = -32 \text{dBZ\ }  \\
0\qquad\qquad \text{for\ } Z(m,n) > -32 \text{dBZ\ }  
\end{cases}">

<!--	
	#!latex 
	$ f_{rspeck}(m,n) = \begin{cases}
	1                                 & \textrm{for\ } Z(m,n) = -32 \textrm{dBZ\ }  \\
	0                                 & \textrm{for\ } Z(m,n) > -32 \textrm{dBZ\ }  
	\end{cases} $
-->	

where _m'', ''n'' are the polar coordinates of gates inside the considered vicinity; ''Z''(''m'', ''n'') is the radar reflectivity in the gate (''m'', ''n_) (in dBZ).

Parameter of the algorithm is threshold SPECK_ANum for _s,,rspeck,,''(''α'', ''l'') value. If the threshold for (''α'', ''l_) gate is not exceeded then the gate is classified as a reverse speck and its reflectivity is set to average from all precipitation gates inside the grid. This subalgorithm is launched SPECK_AStep times.

*Specks removal*

As opposed to reverse specks, the ordinary ones are gates in which isolated echoes are observed that can be considered as measurement noise. Subalgorithm of the speck removal is analogous to the one used for reverse specks. A vicinity of a given gate (_α'', ''l'') ±SPECK_BGrid gates is considered.  Number of echo gates ''s,,speck,,''(''α'', ''l_) in the grid can be calculated from (Jurczyk et al., 2008):

<img src="https://render.githubusercontent.com/render/math?math=s_{speck}(\alpha ,l) = \sum_{m=\alpha -\text{SPECK}\_\text{BGrid}}^{\alpha %2B\text{SPECK}\_\text{BGrid}}  \sum_{n=l-\text{SPECK}\_\text{BGrid}}^{l%2B\text{SPECK}\_\text{BGrid}}  {f_{speck}(m,n)}" />

<!--	
	#!latex 
	$  s_{speck}(\alpha ,l) = \sum_{m=\alpha -\text{SPECK}\_\text{BGrid}}^{\alpha +\text{SPECK}\_\text{BGrid}}  \sum_{n=l-\text{SPECK}\_\text{BGrid}}^{l+\text{SPECK}\_\text{BGrid}}  {f_{speck}(m,n)}  $
-->	

where:

<img src="https://render.githubusercontent.com/render/math?math=f_{speck}(m,n) = \begin{cases}
1\qquad\qquad\text{for\ } Z(m,n) > -32 \text{dBZ\ }  \\
0\qquad\qquad\text{for\ } Z(m,n) = -32 \text{dBZ\ }  
\end{cases}" />

<!--
	#!latex 
	$ f_{speck}(m,n) = \begin{cases}
	1                                 & \textrm{for\ } Z(m,n) > -32 \textrm{dBZ\ }  \\
	0                                 & \textrm{for\ } Z(m,n) = -32 \textrm{dBZ\ }  
	\end{cases} $
-->	

where denotation is the same as for Equation above.

If threshold SPECK_BNum for number of surrounding precipitation gates _s,,speck,,''(''α'', ''l'') is not exceeded then (''α'', ''l'') gate is classified as speck echo and the echo is removed, i.e. reflectivity ''Z_ = –32 dBZ is set for the gate. This subalgorithm is launched SPECK_BStep times to clean the data more thoroughly.

*Quality index*

Related quality index _QI,,SPECK,,_ depends on presence of removed speck or reverse speck in the given gate:

<img src="https://render.githubusercontent.com/render/math?math=I_{SPECK} = \begin{cases}
\text{SPECK}\_\text{QI}\qquad \text{for gate with speck\ } \\
1\qquad\qquad\qquad\:\:\text{for gate without speck\ } 
\end{cases}" />

<!--	
	#!latex 
	$ QI_{SPECK} = \begin{cases}
	\text{SPECK}\_\text{QI}         & \textrm{for gate with speck\ } \\
	1                               & \textrm{for gate without speck\ } 
	\end{cases} $
-->	

# *6. Output*
## a) Data type using ODIM notation where possible, e.g. DBZH
Corrected DBZH, with "pl.imgw.radvolqc.speck" added to data-specific "how"/task, and the algorithm parameters added to "how"/task_args. 

## b) Quality index (_QI_) field
Quality index (_QI_ 1 for excellent data) with "pl.imgw.radvolqc.speck" in quality-specific "how"/task, and the algorithm parameters in "how"/task_args. 

# *7. Outline of a test concept exemplifying the algorithm, as a suggestion for checking that an implementation has been successful.*
