# *1. Algorithm name*
Quality-based Echo Top (ETOP) product generation – Product2D: ETOP

# *2. Basic description*
## *a) Physical basis of the algorithm*
The algorithm generates Echo Top (ETOP) 2-D product from radar reflectivity volume with quality information using product2D_PPI algorithm.

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
The algorithm generates Echo Top (ETOP) 2-D products in Cartesian coordinates from radar reflectivity volume and based on the data quality information.

*Algorithm parameters*

Set of the algorithm parameters:

| **Description** | **Denotation** | **Unit** | **Default value** |
| Lower height limit for ETOP product generation | ETOP_hMin | km | 1 |
| Upper height limit for ETOP product generation | ETOP_hMax | km | 20 |
| Minimum cloud reflectivity | ETOP_ZMin | dBZ | 4 |

*Algorithm description*

Echo Top (ETOP) product represents Cartesian image of height of echo (cloud) tops defining cloud boundary with proper level of radar reflectivity _Z_<sub>0</sub> (in dBZ) (Fig. 1). The _ETOP_ (in km) is detected in a preset range of height (between _h_<sub>min</sub> and _h_<sub>max</sub>) and generally is calculated by interpolation of reflectivity _Z_ between two highest gates for which the reflectivity passes _Z_,,0,, value. If searched height of _Z_<sub>0</sub> value is between two measurements _Z_’ and _Z_” detected at heights _h_’ and _h_” respectively, then in order to find the height _h<sub>int</sub>_ at which echo top occurs (_Z_ = _Z_<sub>0</sub>) the linear interpolation is applied:

<img src="https://render.githubusercontent.com/render/math?math=h_{int} = \frac {(Z_0 - Z_) (h' - h'')} {(Z' - Z'')} + h_" />

<!--	
	#!latex 
	$  h_{int} = \frac {(Z_0 - Z_) (h' - h'')} {(Z' - Z'')} + h_  $ 
-->	
	
In case when both considered measurements are with echo (_Z_ ≥ _Z_<sub>0</sub>) then _h<sub>int<sub>_ = min (<sub>h</sub><sub>max</sub>, max (_h_’, _h_”)).

![Fig 1 ETOP](/images/Fig_1_ET.gif)\
_Fig. 1. Scheme of generation of radar Echo Top product (ETOP)._

There are considered only measurements (Cartesian pixels on PPIs) between _h_,,min,, and _h_,,max,,, and two closest ones (below _h_<sub>min</sub> and above _h_<sub>max</sub>). At first, height _h_ of the highest measurement with echo (_Z_ ≥ _Z_<sub>0</sub>) is found.

The following cases may occur:

* _h_ > _h_<sub>max</sub> and lower measurement exists, then echo top _h<sub>int</sub>_ is interpolated from the two measurements, and:
   * if _h<sub>int</sub>_ > _h_<sub>max</sub> then _ETOP_ = “undetect” and lower echo (_Z_ ≥ _Z_<sub>0</sub>) is analyzed if exists,
   * if _h<sub>int</sub>_ <_h_<sub>max</sub>.

* _h_ > _h_<sub>max</sub> and lower measurement does not exist, then _ETOP_ = “nodata”.

* h <= _h_<sub>max</sub> and higher measurement exists, then echo top _h<sub>int</sub>_ is interpolated from the two measurements, and:
   * if _h<sub>int</sub>_ ≥ _h_<sub>min</sub> then _ETOP_ = min (_h<sub>int</sub>_, _h_<sub>max</sub>),
   * if _h<sub>int</sub>_ < _h_<sub>min</sub> then _ETOP_ = “undetect”.

* _h_ <= _h_<sub>max</sub> and higher measurement does not exist, then:
   * if _h_ ≥ _h_<sub>min</sub> then _ETOP_ = _h_,
   * if _h_ < _h_<sub>min</sub> then _ETOP_ = “nodata”.

Otherwise, i.e. echo (_Z_ ≥ _Z_<sub>0</sub>) is not found, then:

* if there so no measurement between _h_<sub>min</sub> and _h_<sub>max</sub> then _ETOP_ = “nodata”,
* else _ETOP_ = “undetect”.

*Data quality characterization*

Quality of the _ETOP_ depends on the two factors:

* quality of reflectivity data from which _ETOP_ was determined, _QI<sub>source</sub>_,
* how large fraction of investigated heights (between _h_<sub>min</sub> and _h_<sub>max</sub>) was scanned, _QI<sub>scope</sub>_,

and the final quality index _QI_ is taken as a product of the both factors:

<img src="https://render.githubusercontent.com/render/math?math=QI = QI_{source} \cdot QI_{scope}" />

<!--	
	#!latex 
	$  QI = QI_{source} \cdot QI_{scope}  $ 
-->	
	
The value of the first component _QI<sub>source</sub>_ is taken as the quality of the measurement defining echo top, and in case of interpolation from two measurements the minimum quality is chosen. If _ETOP_ “nodata”, and if _ETOP_ 1.

![Fig 2 ETOP](/images/Fig_2_ET.gif)\
_Fig. 2. Quality characterization for Echo Top product in terms of availability._

The second component _QI<sub>scope</sub>_ is determined based on heights of the highest and lowest scans for considered Cartesian pixel (_h<sub>highest</sub>_ and _h<sub>lowest</sub>_ respectively) in relation to _h_<sub>min</sub> and _h_<sub>max</sub> (Fig. 2):

* if _h<sub>highest</sub>_ < _h_<sub>min</sub> then

  _ QI<sub> scope</sub> _  “nodata”.

* if _h<sub>highest</sub>_ ≥ _h_<sub>min</sub> and _h<sub>lowest</sub>_ <= _h_<sub>max</sub> then _QI<sub>scope</sub>_ depends on what part of height range between _h_<sub>min</sub> and _h_<sub>max</sub> was scanned:

<img src="https://render.githubusercontent.com/render/math?math=QI_{scope} = \frac {min(h_{highest},h_{lowest}) - max(h_{lowest},h_{min})} {h_{max} - h_{min}}" />
	
<!--	
	#!latex 
	$      QI_{scope} = \frac {min(h_{highest},h_{lowest}) - max(h_{lowest},h_{min})} {h_{max} - h_{min}}  $ 
-->	
	

  but if (_ h<sub>highest</sub>_  > _h_<sub>max</sub> ) and (_ETOP_  <> “undetect”) then _QI<sub>scope</sub>_  = 1.

* if _h<sub>lowest</sub>_ > _h_<sub>max</sub> then

  _QI<sub>scope</sub>_  “nodata”.

# *6. Output*
## *a) Data type using ODIM notation where possible, e.g. DBZH*
Input quantity as IMAGE object (in Cartesian coordinates) with:

* "how": task - "pl.imgw.product2d.etop",
* "how": task_args
   * parameters inherited from PPI algorithm (interpolation method and selected quality field name),
   * parameters of ETOP algorithm,

## *b) Quality index (QI) field*
Quality index field QIND as IMAGE object with:

* "how": task - "pl.imgw.product2d.etop",
* "how": task_args - parameters inherited from PPI algorithm (interpolation method and selected quality field name).

# *7. Outline of a test concept exemplifying the algorithm, as a suggestion for checking that an implementation has been successful.*
TBD
