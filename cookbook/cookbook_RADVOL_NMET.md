# *1. Algorithm name*
Removal of non-meteorological echoes and quality characterization (as a part of RADVOL-QC package) – RADVOL-QC: NMET

# *2. Basic description*
## *a) Physical basis of the algorithm*
Investigation of echo location and intensity.

## *b) Amount of validation performed so far*
Works operationally in IMGW since 2013 to correct data before using for Meteo Flight system (for air traffic control).

## *c) References (names and contact information of all developers during the evolutionary history, scientific papers)*
* Operational work: IMGW, Department of  Ground Based Remote Sensing.

# *3. ODIM metadata requirements for I/O*
* Top-level “where”: height.
* Dataset-specific “what”: gain, offset, nodata, undetect.
* Dataset-specific “where”: elangle, nbins, nrays, rscale.

# *4. Input data*
## *a) What kind of radar data (including the list of previous algorithms and quality flags applied)*
object=PVOL or SCAN; quantity=DBZH, otherwise TH.

## *b) Other data (optional and mandatory, applying “universally” agreed formats, geometry)*
None

# *5. Logical steps, using any of: text, flow charts, graphics, equations (or references to equations), conditional branches in “all possible cases”.*
In the detector two stages of non-meteorological echo removal are introduced: for “low” (subalgorithm A), and “high” (subalgorithm B) types of the echoes.

*Set of the algorithm parameters*

| Description | Denotation | Default value |
| _QI,,NMET,,_ value for non-meteorological echoes | NMET_QI | 0.75 |
| _QI,,NMET,,_ value for uncorrected  non-meteorological echoes | NMET_QIUn | 0.3 |
| Minimum value of  reflectivity in NMET echo detector (algorithm A) (dBZ) | NMET_AReflMin | -15.0 |
| Maximum value of  reflectivity in NMET echo detector (algorithm A) (dBZ) | NMET_AReflMax | 5.0 |
| Minimum value of  height in NMET echo detector (algorithm A) (km) | NMET_AAltMin | 1.0 |
| Maximum value of  height in NMET echo detector (algorithm A) (km) | NMET_AAltMax | 3.0 |
| Threshold for  NMET echo detection (algorithm A) | NMET_ADet | 0.2 |
| Threshold for meteorological echo altitude (algorithm B) (km) | NMET_BAlt | 20.0 |

At first the XML file is checked whether there exists group for a considered radar (based on the radar name read from "what"/source(NOD)), which contains the algorithm parameters. If "yes", then parameters are read from that XML group, but if it is impossible for a particular parameter, then default value from source code is taken. If the group does not exist, parameters are read from <default> group in XML file in analogous way.

If the algorithm is run by means of BALTRAD toolbox then all the algorirthm parameters for each specific radar should be placed in relevant XML file by the BALTRAD system admin. Default parameters are placed in the file by admin as well. Moreover, the algorithm default parameters are also included in software.

*“Low” non-meteorological echo removal*

For “low” non-meteorological echo removal a detection scheme is employed, in which the two parameters are investigated: radar reflectivity _Z'' and height of echo above radar level ''H''. Detection function ''D''(''Z'') for parameter ''Z_ is linear in range defined by its minimum and maximum values NMET_AReflMin and NMET_AReflMax:

![RADVOL NMET math 1](/images/RADVOL_NMET_math_1.png)


<!--	
	#!latex 
	$ D(Z) = \begin{cases}
	1    & \textrm{for\ } Z <= \text{NMET}\_\text{AReflMin} \\
	\frac{\text{NMET}\_\text{AReflMax} \ - \ Z}{\text{NMET}\_\text{AReflMax} \ - \ \text{NMET}\_\text{AReflMin}}    & \textrm{for\ } \text{NMET}\_\text{AReflMin} < Z < \text{NMET}\_\text{AReflMax}  \\
	0    & \textrm{for\ } Z >= \text{NMET}\_\text{AReflMax}   
	\end{cases}   $
-->	

and analogically for _D''(''H_) with minimum and maximum values NMET_AAltMin and NMET_AAltMax.

The detector threshold is compared with product of the two functions, and if:

<img src="https://render.githubusercontent.com/render/math?math=D(Z) \cdot D(H)  > \text{NMET}\_\text{ADet}">

<!--	
	#!latex 
	$ D(Z) \cdot D(H)  > \text{NMET}\_\text{ADet}   $
-->	
	
and there is no echo at neighbouring higher elevation then the echo is removed as non-meteorological one.

*“High” non-meteorological echo removal*

In the second subalgorithm “high” spurious echoes are all echoes detected at altitudes higher than NMET_BAlt (km) where any meteorological echo is not possible to exist. All the “high” echoes are removed.

*Quality index*

Quality index _QI,,NMET,,_ due to non-meteorological echoes is defined as follows:

<img src="https://render.githubusercontent.com/render/math?math=$ QI_{NMET} = \begin{cases}
\text{NMET}\_\text{QI}\qquad\text{for gate with non-meteorological echo\ } \\
1\qquad\qquad\qquad         \text{for gate without non-meteorological echo \ } 
\end{cases}" />

<!--	
	#!latex 
	$ QI_{NMET} = \begin{cases}
	\text{NMET}\_\text{QI}  & \textrm{for gate with non-meteorological echo\ } \\
	1                        & \textrm{for gate without non-meteorological echo \ } 
	\end{cases} $
-->	
	
# *6. Output*
## a) Data type using ODIM notation where possible, e.g. DBZH
Corrected DBZH, with "pl.imgw.radvolqc.nmet" added to data-specific "how"/task, and the algorithm parameters added to "how"/task_args.

## b) Quality index (_QI_) field
Quality index (_QI_ 1 for excellent data) with "pl.imgw.radvolqc.nmet" in quality-specific "how"/task, and the algorithm parameters in "how"/task_args.

# *7. Outline of a test concept exemplifying the algorithm, as a suggestion for checking that an implementation has been successful.*
