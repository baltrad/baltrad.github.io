# *1. Algorithm name*
Quality-based PPI (Plan Position Indicator) product generation – Product2D: PPI

# *2. Basic description*
## *a) Physical basis of the algorithm*
The algorithm interpolates polar data into Cartesian coordinates employing quality information (quality index e.g. from QI_TOTAL processing). It can be applied e.g. to radar reflectivity _Z_ after VPR-based extrapolation down to ground.

The product is the basis for generating other 2-D products.

## *b) Amount of validation performed so far*
Not performed yet.

## *c) References (names and contact information of all developers during the evolutionary history, scientific papers)*
IMGW, Department of Ground Based Remote Sensing. 

# *3. ODIM metadata requirements for I/O*
Input data: SCAN
* General “what”: source(NOD).
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
* Radar-based quantity, e.g. reflectivity data after corrections DBZH as SCAN object.
* Optionally QI information QIND (generated e.g. by QI_TOTAL algorithm) included in the same SCAN object.

## *b) Other data (optional and mandatory, applying “universally” agreed formats, geometry)*
Defined projection and domain of Cartesian output.

# *5. Logical steps, using any of: text, flow charts, graphics, equations (or references to equations), conditional branches in “all possible cases”.*
The algorithm transforms values for measurement gates of polar coordinates (_α'', ''l''), where ''α'' is the azimuth, ''l'' is the distance from the radar site, into values interpolated for Cartesian pixels defined by coordinates: (''x'', ''y_).

[[Image(Fig_1_PPI.gif)]]

_Fig. 1. Scheme of interpolation of gate values into Cartesian pixel._

*Algorithm parameters*

Set of the algorithm parameters:

| **Description** | **Denotation** | **Available options** | **Default value** |
| Interpolation method | Method | nearest / uniform / inverse1 / inverse2 / bilinear / cressman | bilinear |
| Input quantity identifier | Quantity | TH / DBZH / ... | DBZH |
| If to employ quality information QI for interpolation | IncludeQuality | 0 (no) / 1 (yes) | 1 |
| Input quality field name | QIField | pl.imgw.qi_total / se.smhi.detector.poo / ... | pl.imgw.qi_total |
| If to interpolate values in mm^6^ m^-3^ (for Quantity = TH / TV/ DBZH / DBZV / ZDR) | dBZtoZ | 0 (no) / 1 (yes) | 1 |

*Separation of pixels due to distance to radar*

The algorithm interpolates data in different ways for pixels close to radar site, where there is dense pattern of gates, and farther from radar site (so called inside and outside method). The border in distance to radar (_D'') is defined by empirically determined function of measurement parameters: step in azimuth d''Az'' (°), step in distance from radar d''bin_ (km), and Cartesian spatial resolution dx (km):

<img src="https://render.githubusercontent.com/render/math?math=D = \sqrt{ \frac{9500(\frac {1.3}{\text{d}Az} + \frac{2.3}{\text{d}bin} + 1.6 \text{d}x) - 39000} {\pi} }" />
	
<!--	
	#!latex 
	$  D = \sqrt{ \frac{9500(\frac {1.3}{\text{d}Az} + \frac{2.3}{\text{d}bin} + 1.6 \text{d}x) - 39000} {\pi} }   $ 
-->	
	
For instance, for d_Az'' 1 km, and d''x_ 57,5 km.

*Inside method*

For the centre of Cartesian pixel its four corners are considered, which coordinates are transformed into polar coordinates defining investigation area in polar data. Then the number of gates inside this area is determined. If it is higher than 2 the inside method based on quality weighted interpolation is employed:

<img src="https://render.githubusercontent.com/render/math?math=Z(x,y) = \frac {\sum_{i=1}^{n}(Z_i QI_i)} {\sum_{i=1}^{n}QI_i}" />

<!--	
	#!latex 
	$  Z(x,y) = \frac {\sum_{i=1}^{n}(Z_i QI_i)} {\sum_{i=1}^{n}QI_i}  $ 
-->	
	
where _n_ is the number of gates inside the investigation area.

Otherwise (if the number of gates inside the investigation area is not higher than 2) the outside method is applied.

*Outside method*

In outside method the closest gates are determined in the following way. The coordinates of the Cartesian pixel centre are transformed into polar coordinates and four surrounding gates are taken into account. In case when difference between the considered pixel centre and one or two the investigated gates is lower than the preset limit (5% of "rscale" or azimuth step in terms of distance to radar or azimuth respectively) then only the closest gates are taken into calculations. 

Then quantity in given pixel of coordinates (_x'', ''y'') is estimated as weighing average value ''Z''(''x'', ''y'') from the ''n'' selected gates ''Z<sub>i</sub>_, taking both distances to the gates and data quality information in the gates into account:

<img src="https://render.githubusercontent.com/render/math?math=Z(x,y) = \frac{\sum_{i=1}^{n} (Z_i W_{Di} W_{QIi})}{\sum_{i=1}^{n} (W_{Di} W_{QIi})}" />

<!--	
	#!latex 
	$  Z(x,y) = \frac{\sum_{i=1}^{n} (Z_i W_{Di} W_{QIi})}{\sum_{i=1}^{n} (W_{Di} W_{QIi})}    $ 
-->	
		
where: _W<sub>Di</sub>'' is the weight related to distance of ''i''-gate to pixel (''x'', ''y''); ''W<sub>QIi</sub>'' is the quality index ''QI'' of the ''i''-gate; ''n_ is the number of the closest gates taken into account. 

*Determination of weigths in outside method*

The polar coordinates of selected _i''-gate are transformed into Cartesian coordinates (''x,,i,,'', ''y,,i,,'') in order to determine its distance to the considered pixel (''x'', ''y_):

<img src="https://render.githubusercontent.com/render/math?math=D_i = \sqrt{ (x - x_i)^2 + (y - y_i)^2 }" />

<!--	
	#!latex 
	$  D_i = \sqrt{ (x - x_i)^2 + (y - y_i)^2 }   $ 
-->	
	

Weights due to distances to gates _D<sub>i</sub>_ are determined by means of the following methods:

* nearest:\
<img src="https://render.githubusercontent.com/render/math?math=\quad\quad W_{Di} = \begin{cases}
1\qquad\qquad\text{}D_i = min(D_j, j=1,..., n)  \\
0\qquad\qquad\text{otherwise:\ }D_i > min(D_j, j=1,..., n)   
\end{cases}" />

<!--	
	#!latex 
	$ \quad \quad W_{Di} = \begin{cases}
	1  & \textrm{}D_i = min(D_j, j=1,..., n)  \\
	0  & \textrm{otherwise:\ }D_i > min(D_j, j=1,..., n)   
	\end{cases} $
-->	
	

* uniform: \
<img src="https://render.githubusercontent.com/render/math?math=\quad \quad W_{Di} = 1" />

<!--	
	#!latex 
	$ \quad \quad W_{Di} = 1   $ 
-->	
	

* inverse1:\
<img src="https://render.githubusercontent.com/render/math?math=\quad \quad W_{Di} = \frac{1}{D_i}" />

<!--	
	#!latex 
	$ \quad \quad W_{Di} = \frac{1}{D_i}   $ 
-->	
	

* inverse2:\
<img src="https://render.githubusercontent.com/render/math?math=\quad \quad W_{Di} = \frac{1}{D_i^2}" />

<!--	
	#!latex 
	$ \quad \quad W_{Di} = \frac{1}{D_i^2}   $ 
-->	
	

* bilinear:

![Fig 2 PPI](/images/Fig_2_PPI.gif)\
_Fig. 2. Scheme of bilinerar interpolation._

<img src="https://render.githubusercontent.com/render/math?math=\quad \quad  W_{Di} = \frac{1}{A_i}" />

<!--	
	#!latex 
	$ \quad \quad  W_{Di} = \frac{1}{A_i}  $ 
-->	
	
   where _A<sub>i</sub>_ is the area of annulus sector.

* cressman:\
<img src="https://render.githubusercontent.com/render/math?math=\quad \quad W_{Di} = \frac{a^2-D_i^2}{a^2+D_i^2}" />

<!--	
	#!latex 
	$ \quad \quad W_{Di} = \frac{a^2-D_i^2}{a^2+D_i^2}   $ 
-->	
	 
   where _a'' is the influence radius, ''a_ 0. 
   If for the considered pixel there are no gates with _D<sub>i</sub>'' < ''a'' then the calculation is repeated with longer ''a_ = 20 km.

Weights due to data quality for 1, .., _n_ pixels are determined as:
	
<img src="https://render.githubusercontent.com/render/math?math=W_{QIi} = QI_i" />

<!--	
	#!latex 
	$  W_{QIi} = QI_i   $ 
-->	
	

*Data quality characterization*

Quality index for interpolated pixel (_x'', ''y_) is calculated in dependence on method applied to data interpolation:

* for inside method\
<img src="https://render.githubusercontent.com/render/math?math=QI(x,y) = \frac {\sum_{i=1}^{n}QI_i} {n}" />

<!--	
	#!latex 
	$  QI(x,y) = \frac {\sum_{i=1}^{n}QI_i} {n}  $ 
-->	
	

* for outside method \
<img src="https://render.githubusercontent.com/render/math?math=QI(x,y) = \frac{\sum_{i=1}^{n} (QI_i W_{Di})}{\sum_{i=1}^{n} W_{Di}}" />

<!--
	#!latex 
	$ QI(x,y) = \frac{\sum_{i=1}^{n} (QI_i W_{Di})}{\sum_{i=1}^{n} W_{Di}}    $ 
-->	
	

 where: _W<sub>Di</sub>'' are the distance-related weights for ''n_ selected gates.

# *6. Output*
## *a) Data type using ODIM notation where possible, e.g. DBZH*
* Input quantity as IMAGE or COMP objects (in Cartesian coordinates) with
  * "pl.imgw.product2d.ppi" in quality-specific "how": task, 
  * interpolation method, selected quality field name, and whether values were interpolated in mm^6^ m^-3^, listed in "how": task_args. 

## *b) Quality index (QI) field*
* Quality index field QIND as IMAGE or COMP objects with:
  * "pl.imgw.product2d.ppi" in quality-specific "how": task, 
  * interpolation method and selected quality field name listed in "how": task_args. 

# *7. Outline of a test concept exemplifying the algorithm, as a suggestion for checking that an implementation has been successful.*
TBD
