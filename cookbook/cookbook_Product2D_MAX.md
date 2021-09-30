# *1. Algorithm name*
Quality-based maximum of reflectivity (MAX) product generation – Product2D: MAX

# *2. Basic description*
## *a) Physical basis of the algorithm*
The algorithm generates maximum of reflectivity (MAX) 2-D product from radar reflectivity volume with quality information using product2D_PPI algorithm.

## *b) Amount of validation performed so far*
Not performed yet.

## *c) References (names and contact information of all developers during the evolutionary history, scientific papers)*
IMGW, Department of Ground Based Remote Sensing. 

# *3. ODIM metadata requirements for I/O*
Input data: VOL
* General “what”: source(NOD).
* For particular SCANs:
  * Dataset-specific “where” for data and QI: nbins, nrays. 
  * Data-specific “what” for data: gain, offset, nodata, undetect.
  * Data-specific “what” for QI: gain, offset, nodata, undetect.

Output data: Cartesian data
* Top-level “where”: lon, lat, xsize, ysize, xscale, yscale. 
* Dataset-specific “what”: product.
* Data-specific “what” for data: gain, offset, nodata, undetect.
* Data-specific “what” for QI: gain, offset, nodata, undetect.

# *4. Input data*
## *a) What kind of radar data (including the list of previous algorithms and quality flags applied)*
object=PVOL:
* quantity=DBZH, otherwise TH, 
* quantity=QIND (generated e.g. by QI_TOTAL algorithm).

## *b) Other data (optional and mandatory, applying “universally” agreed formats, geometry)*
Defined projection and domain of Cartesian output.

# *5. Logical steps, using any of: text, flow charts, graphics, equations (or references to equations), conditional branches in “all possible cases”.*
The algorithm generates maximum of reflectivity (MAX) 2-D products in Cartesian coordinates from radar reflectivity volume and based on the data quality information.

*Algorithm parameters*

Set of the algorithm parameters:

| **Description** | **Denotation** | **Unit** | **Default value** |
| Lower height limit for MAX product generation | MAX_hMin | km | 1 |
| Upper height limit for MAX product generation | MAX_hMax | km | 20 |

*Algorithm description*

Maximum of reflectivity (MAX) product represents Cartesian image of highest measured value of radar reflectivity _Z'' (in dBZ) for each vertical column. The maximum is detected in a preset range of height (between ''h''<sub>min</sub> and ''h_<sub>max</sub>) and generally is a search for the highest value among reflectivities in pixels in the column for all PPIs (Fig. 1).


![Fig 1 MAX](/images/Fig_1_MAX.gif)\
_Fig. 1. Scheme of generation of maximum of radar reflectivity product (MAX)._

*Data quality characterization*

Quality of the _MAX_ depends on the two factors:
- quality of reflectivity data taken as _MAX'', ''QI,,source,,_,
- how large fraction of investigated heights (between _h'',,min,, and ''h'',,max,,) was scanned, ''QI,,scope,,_,
and the final quality index _QI_ is taken as a product of the both factors: 

<img src="https://render.githubusercontent.com/render/math?math=QI = QI_{source} \cdot QI_{scope}" />

<!--
	#!latex 
	$  QI = QI_{source} \cdot QI_{scope}  $ 
-->	
	

The value of the first component _QI,,source,,'' is taken as the quality of the measurement defining ''MAX''. If ''MAX'' “nodata”, and if ''MAX_ 1.

![Fig 2 MAX](/images/Fig_2_MAX.gif)\
_Fig. 2. Quality characterization for maximum of reflectivity product in terms of availability._

The second component _QI<sub>scope</sub>'' is determined based on heights of the highest and lowest scans for considered Cartesian pixel (''h<sub>highest</sub>'' and ''h<sub>lowest</sub>'' respectively) in relation to ''h''<sub>min</sub> and ''h_<sub>max</sub> (Fig. 2):

- if _h<sub>highest</sub>'' < ''h_<sub>min</sub> then

  _QI<sub>scope</sub>_ “nodata”.

- if _h<sub>highest</sub>'' ≥ ''h''<sub>min</sub> and ''h<sub>lowest</sub>'' <= ''h''<sub>max</sub> then ''QI<sub>scope</sub>'' depends on what part of height range between ''h''<sub>min</sub> and ''h_<sub>max</sub> was scanned:

<img src="https://render.githubusercontent.com/render/math?math=QI_{scope} = \frac {min(h_{highest},h_{lowest}) - max(h_{lowest},h_{min})} {h_{max} - h_{min}}" />
  	
<!--  	
	#!latex 
	$  QI_{scope} = \frac {min(h_{highest},h_{lowest}) - max(h_{lowest},h_{min})} {h_{max} - h_{min}}  $ 
-->	
	

- if _h<sub>lowest</sub>'' > ''h_<sub>max</sub> then

  _QI<sub>scope</sub>_ “nodata”.

# *6. Output*
## *a) Data type using ODIM notation where possible, e.g. DBZH*
Input quantity as IMAGE object (in Cartesian coordinates) with:
* "how": task - "pl.imgw.product2d.max",
* "how": task_args 
  * parameters inherited from PPI algorithm (interpolation method and selected quality field name),
  * parameters of MAX algorithm,

## *b) Quality index (QI) field*
Quality index field QIND as IMAGE object with:
* "how": task - "pl.imgw.product2d.max", 
* "how": task_args - parameters inherited from PPI algorithm (interpolation method and selected quality field name). 

# *7. Outline of a test concept exemplifying the algorithm, as a suggestion for checking that an implementation has been successful.*
TBD
