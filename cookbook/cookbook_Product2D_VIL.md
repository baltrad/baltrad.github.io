# *1. Algorithm name*
Quality-based vertically integrated liquid water (VIL) product generation – Product2D: VIL

# *2. Basic description*
## *a) Physical basis of the algorithm*
The algorithm generates vertically integrated liquid water (VIL) 2-D product from radar reflectivity volume with quality information using product2D_PPI algorithm.

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
The algorithm generates vertically integrated liquid water (VIL) 2-D products in Cartesian coordinates from radar reflectivity volume and based on the data quality information.

*Algorithm parameters*

Set of the algorithm parameters:

| **Description** | **Denotation** | **Unit** | **Default value** |
| Lower height limit for VIL product generation (a.s.l.) | VIL_hMin | km | 1 |
| Upper height limit for VIL product generation (a.s.l.) | VIL_hMax | km | 10 |
| Coefficient _c'' in ''Z-M_ formula | VIL_ZMc | - | 24000 |
| Coefficient _d'' in ''Z-M_ formula | VIL_ZMd | - | 1.82 |

*Algorithm description*

Vertically integrated liquid water (VIL) product represents Cartesian image of the water content residing in a user-defined layer in the atmosphere (in dBA) (Fig. 1). Generally, in the first step a vertical profile of liquid water content _M_ (based on _Z-M_ relationship) is determined by interpolation between all pairs of neighbouring measurements. Then the _VIL_ in a preset range of height (between _h_<sub>min</sub> and _h_<sub>max</sub>) is calculated by integration of the profile. In order to find the vertical profile of _M_(_h_), values between two measurements _M’_ and _M”_ detected at heights _h’_ and _h”_ respectively, the linear interpolation is applied:

<img src="https://render.githubusercontent.com/render/math?math=M(h) = \frac {(h-h'')(M'-M'')} {h'-h''} %2B M''" />

<!--	
	#!latex 
	$  M(h) = \frac {(h-h_)(M'-M'')} {h'-h''} + M_  $ 
-->	
	
![Fig 1 VIL](/images/Fig_1_VIL.gif)\
_Fig. 1. Scheme of generation of vertically integrated liquid water product (VIL)._

Radar reflectivity _Z_ is related to liquid water content _M_ (in cm^3^ m^-3^) according to so called _Z-M_ relationship:

<img src="https://render.githubusercontent.com/render/math?math=M(h) = \frac {(h-h'')(M'-M'')} {h'-h''} %2B M''" />

<!--	
	#!latex 
	$  Z({\text{mm}^6 \text{m}^{-3}}) (\frac {Z}{c})^{\frac{1}{d}}    $ 
-->	
	
where constants: _c_ 1.82 (as proposed by Selex, 2010).

The _VIL_ (vertically integrated liquid water content) is defined as:

<img src="https://render.githubusercontent.com/render/math?math=VIL(\text{dBA}) = 10 \cdot \text{log}_{10} \int_{h_{min}}^{h_{max}} M(h) \text{d}h" />

<!--	
	#!latex 
	$  VIL(\text{dBA}) = 10 \cdot \text{log}_{10} \int_{h_{min}}^{h_{max}} M(h) \text{d}h    $ 
-->	
	
In the VIL algorithm there are considered only measurements (Cartesian pixels on PPIs) between _h_<sub>min</sub> and _h_<sub>max</sub>, and two closest ones (below _h_<sub>min</sub> and above _h_<sub>max</sub>).

The following ranges of integration are considered:

* If the highest measurement is higher than _h_<sub>max</sub>, then the two measurements above and below _h_<sub>max</sub> are interpolated and values of _M_ below _h_<sub>max</sub> are taken for integration, else the integration is performed up to height of the highest measurement.

* If the lowest measurement is lower than _h_<sub>min</sub>, then the two measurements above and below _h_<sub>min</sub> are interpolated and values of _M_ above _h_<sub>min</sub> are taken for integration, else the integration is performed with the assumption that the lowest measurement was also at _h_<sub>min</sub>.

*Data quality characterization*

Quality of the _VIL_ depends on the two factors:

* quality of reflectivity data from which _VIL_ was determined, _QI<sub>source</sub>_,
* how large fraction of investigated heights (between _h_<sub>min</sub> and _h_<sub>max</sub>) was scanned, _QI<sub>scope</sub>_,

and the final quality index _QI_ is taken as a product of the both factors:

<img src="https://render.githubusercontent.com/render/math?math=QI = QI_{source} \cdot QI_{scope}" />

<!--
	#!latex 
	$  QI = QI_{source} \cdot QI_{scope}  $ 
-->	
	
The value of the first component _QI<sub>source</sub>_ is taken as an average quality of all measurements defining _VIL_. If _VIL_ “nodata”, and if VIL 1.

![Fig 2 VIL](/images/Fig_2_VIL.gif)\
_Fig. 2. Quality characterization for vertically integrated liquid water product in terms of scope._

The second component _QI<sub>scope</sub>_ is determined based on heights of the lowest and highest scans for considered Cartesian pixel (_h<sub>lowest</sub>_ and _h<sub>highest</sub>_ respectively) in relation to _h_<sub>min</sub> and _h_<sub>max</sub> (Fig. 2):

* if _h<sub>highest</sub>_ < _h_<sub>min</sub> then

  _QI<sub>scope</sub>_  “nodata”.

* if _h<sub>highest</sub>_ ≥ _h_<sub>min</sub> and _h<sub>lowest</sub>_ <= _h_<sub>max</sub> then _QI<sub>scope</sub>_ depends on what part of height range between _h_<sub>min</sub> and _h_<sub>max</sub> was scanned:

<img src="https://render.githubusercontent.com/render/math?math=QI_{scope} = \frac {min(h_{highest},h_{max}) - max(h_{lowest},h_{min})} {h_{max} - h_{min}}" />
	
<!--	
	#!latex 
	$  QI_{scope} = \frac {min(h_{highest},h_{max}) - max(h_{lowest},h_{min})} {h_{max} - h_{min}}  $ 
-->	
	

* if _h<sub>lowest</sub>_ > _h_<sub>max</sub> then

  _QI<sub>scope</sub>_  “nodata”.

# *6. Output*
## *a) Data type using ODIM notation where possible, e.g. DBZH*
Input quantity as IMAGE object (in Cartesian coordinates) with:

* "how": task - "pl.imgw.product2d.vil",
* "how": task_args
   * parameters inherited from PPI algorithm (interpolation method and selected quality field name),
   * parameters of VIL algorithm,

## *b) Quality index (QI) field*
Quality index field QIND as IMAGE object with:

* "how": task - "pl.imgw.product2d.vil",
* "how": task_args - parameters inherited from PPI algorithm (interpolation method and selected quality field name).

# *7. Outline of a test concept exemplifying the algorithm, as a suggestion for checking that an implementation has been successful.*
TBD
