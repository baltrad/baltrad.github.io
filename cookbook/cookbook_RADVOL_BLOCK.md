# *1. Algorithm name*
Correction of partial and total beam blockage and quality characterization including ground clutter (as a part of RADVOL-QC package) – RADVOL-QC: BLOCK

# *2. Basic description*
## *a) Physical basis of the algorithm*
* Analysis of DTM to detect and correct partial and total beam blockage; quality characterization.
* Analysis of DTM to detect ground clutter; quality characterization.

## *b) Amount of validation performed so far*
Works operationally in IMGW since 2011 to correct data before using for Meteo Flight system (for air traffic control).

## *c) References (names and contact information of all developers during the evolutionary history, scientific papers)*
* Operational work: IMGW, Department of  Ground Based Remote Sensing.
* Scientific papers: 
  * Ośródka, K., Szturc, J., and Jurczyk, A., 2012. Chain of data quality algorithms for 3-D single-polarization radar reflectivity (RADVOL-QC system). _Meteorol. Appl._ (Early View).
  * Bech, J., Gjertsen, U., Haase, G., 2007. Modelling weather radar beam propagation and topographical blockage at northern high latitudes. _Quarterly Journal of the Royal Meteorological Society_, *133*, 1191–1204.

# *3. ODIM metadata requirements for I/O*
* Top-level “where”: height. 
* Top-level “how”: beamwidth.
* Dataset-specific “what”: gain, offset, nodata, undetect.
* Dataset-specific “where”: elangle, nbins, nrays, rscale.

# *4. Input data*
## *a) What kind of radar data (including the list of previous algorithms and quality flags applied)*
object=PVOL; quantity=DBZH, otherwise TH.

## *b) Other data (optional and mandatory, applying “universally” agreed formats, geometry)*
Topography maps from GTOPO30.

# *5. Logical steps, using any of: text, flow charts, graphics, equations (or references to equations), conditional branches in “all possible cases”.*
A geometrical approach is applied to calculate the degree of the beam blockage. 

Set of the algorithm parameters:

| Description | Denotation | Default value |
| Maximum of elevation angle to calculate beam blockage (deg) | BLOCK_MaxElev | 5.0 |
| QIGC value for ground clutter | BLOCK_GCQI | 0.5 |
| QIGC value for uncorrected ground clutter | BLOCK_GCQIUn | 0.1 |
| Threshold for PBB increase to detect ground clutter | BLOCK_GCMinPbb | 0.005 |
| Maximum PBB to correct | BLOCK_PBBMax | 0.7 |
| QIPBB value for uncorrected PBB | BLOCK_PBBQIUn | 0.5 |

At first the XML file is checked whether there exists group for a considered radar (based on the radar name read from "what"/source(NOD)), which contains the algorithm parameters. If "yes", then parameters are read from that XML group, but if it is impossible for a particular parameter, then default value from source code is taken. If the group does not exist, parameters are read from <default> group in XML file in analogous way. 

If the algorithm is run by means of BALTRAD toolbox then all the algorirthm parameters for each specific radar should be placed in relevant XML file by the BALTRAD system admin. Default parameters are placed in the file by admin as well. Moreover, the algorithm default parameters are also included in software. 

The algorithm is applied if elevation angle is smaller than BLOCK_MaxElev. A degree of partial beam blocking (_PBB_) is computed from a digital terrain map (DTM) taking into account the highest blocked point in the given beam cross-section (Bech et al., 2007):

<img src="https://render.githubusercontent.com/render/math?math=PBB = \frac{y \sqrt{r_b^2 - y^2}%2B r_b^2 \arcsin \frac{y}{r_b}%2B\frac{\pi r_b^2}{2} }{\pi r_b^2}" />

<!--	
	#!latex 
	$ PBB = \frac{y \sqrt{r_b^2 - y^2}+ r_b^2 \arcsin \frac{y}{r_b}+\frac{\pi r_b^2}{2} }{\pi r_b^2}  $
-->	
	

where _r,,b,,'' is the radius of radar beam cross-section at the given distance from radar, and ''y'' is the difference between the height of the terrain and the height of the radar beam centre. The partial blockage takes place when –''r,,b,,'' < ''y'' < ''r,,b,,_, and varies from 0 to 1.

Quantity _y'' in the equation is calculated as an altitude obtained from DTM for radar gate located in beam centre reduced by quantity ''h'' involving: (i) altitude of radar antenna, ''h,,0,,'', (ii) difference of altitude due to the Earth curvature, (iii) difference of altitude due to antenna elevation, ''ε_:

<img src="https://render.githubusercontent.com/render/math?math=h = \sqrt{l^2%2Br%2Be^2%2B2lr_e \sin \epsilon} - r_e%2Bh_0" />

<!--	
	#!latex 
	$ h = \sqrt{l^2+r+e^2+2lr_e \sin \epsilon} - r_e+h_0  $
-->	
	
where _r,,e,,'' is the effective Earth’s radius (8,493 km), ''l_ is the distance to the radar site.

Correction of partial beam blocking is made by applying a multiplicative correction factor (Bech et al., 2007):

<img src="https://render.githubusercontent.com/render/math?math=Z_{cor} = Z%2B10 \log_{10} (1-PBB)^{-1}" />

<!--	
	#!latex 
	$ Z_{cor} = Z+10 \log_{10} (1-PBB)^{-1}  $
-->	

The correction is introduced if the _PBB'' value is smaller than BLOCK_PBBMax. For higher ''PBB_ reflectivity from neighbouring higher elevation is taken. When such data is not available the “no data” mark is assigned.

The quality index _QI,,PBB,,_ of gates where radar beam is considered as blocked is expressed by the formula:

<img src="https://render.githubusercontent.com/render/math?math=QI_{PBB} = \begin{cases}
1-PBB\qquad\qquad\qquad\qquad\qquad\qquad\qquad\text{for\ } PBB <= \text{BLOCK}\_\text{PBBMax} \\
(1-\text{BLOCK}\_\text{PBBMax})(QI_{PBB}(el%2B1))\qquad \text{for\ } PBB > \text{BLOCK}\_\text{PBBMax} \text{ and } el \text{ is not the number of the highest elevation\ }  \\
0\quad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\qquad\text{for\ } PBB > \text{BLOCK}\_\text{PBBMax} \text{ and } el \text{ is the number of the highest elevation\ } 
\end{cases}" />

<!--	
	#!latex 
	$ QI_{PBB} = \begin{cases}
	1-PBB         & \textrm{for\ } PBB <= \text{BLOCK}\_\text{PBBMax} \\
	(1-\text{BLOCK}\_\text{PBBMax})(QI_{PBB}(el+1))      & \textrm{for\ } PBB > \text{BLOCK}\_\text{PBBMax} \text{ and } el \textrm{ is not the number of the highest elevation\ }  \\
	0             & \textrm{for\ } PBB > \text{BLOCK}\_\text{PBBMax} \text{ and } el \textrm{ is the number of the highest elevation\ } 
	\end{cases} $
-->	

where _QI,,PBB,,''(''el''+1) means the ''QI,,PBB,,'' calculated for the relevant gate in the elevation ''el''+1, ''el_ is the number of elevation (numbered from the lowest to the highest).

In order to determine areas contaminated by ground clutter a diagram of _PBB'' is analysed (Ośródka et al., 2012). A given gate is considered a ground clutter if increase in ''PBB'' along the radar beam exceeds BLOCK_GCMinPbb. Gates where ground clutter was detected should be characterized by lowered quality index. A simple formula for quality index ''QI,,GC,,_ related to the clutter presence can be written as:

<img src="https://render.githubusercontent.com/render/math?math=QI_{GC} = \begin{cases}
\text{BLOCK}\_\text{GCQI}\qquad\text{if ground clutter is detected and\ }PBB < \text{BLOCK}\_\text{PBBMax}   \\
1\qquad\qquad\qquad\qquad\: \text{otherwise\ }   
\end{cases}" />


<!--	
	#!latex 
	$ QI_{GC} = \begin{cases}
	\text{BLOCK}\_\text{GCQI}    & \textrm{if ground clutter is detected and\ }PBB < \text{BLOCK}\_\text{PBBMax}   \\
	1                            & \textrm{otherwise\ }   
	\end{cases} $
-->	

The quality index decreases in each gate in which ground clutter was detected even if it was removed.

<img src="https://render.githubusercontent.com/render/math?math=QI_{BLOCK} = QI_{PBB} \text{ x } QI_{GC}" />


Finally:

<!--	
	#!latex 
	$ QI_{BLOCK} = QI_{PBB} \text{ x } QI_{GC}  $
-->	

# *6. Output*
## a) Data type using ODIM notation where possible, e.g. DBZH
Corrected DBZH, with "pl.imgw.radvolqc.block" added to data-specific "how"/task, and the algorithm parameters added to "how"/task_args. 

## b) Quality index (_QI_) field
Quality index (_QI_ 1 for excellent data) with "pl.imgw.radvolqc.block" in quality-specific "how"/task, and the algorithm parameters in "how"/task_args.

# *7. Outline of a test concept exemplifying the algorithm, as a suggestion for checking that an implementation has been successful.*
