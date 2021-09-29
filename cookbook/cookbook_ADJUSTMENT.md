# *1. Algorithm name*
Combination of radar-based ground precipitation rate and raingauge network data – COMBINATION

# *2. Basic description*
## *a) Physical basis of the algorithm*
Final precipitation estimate is generated as combination of corrected radar-based precipitation rate with data from raingauge. Three options/techniques are available: 
* simple mean field bias (MFB),
* local-oriented MFB,
* conditional merging of the two kinds of precipitation information.

## *b) Amount of validation performed so far*
Prototype was developed and tested in the frame of RISK-AWARE Project (2003-2007).

## *c) References (names and contact information of all developers during the evolutionary history, scientific papers)*
* IMGW, Department of Ground Based Remote Sensing. 
* Scientific papers: 

 Jurczyk, A., Ośródka, K., and Szturc, J., 2008. Research studies on improvement in real-time estimation of radar-based precipitation in Poland. _Meteorol. Atmos. Phys._, *101*, 159-173.

 Sinclair, S. and Pegram, G., 2005. Combining radar and rain gauge rainfall estimates using conditional merging. _Atmos. Sci. Lett._, *6*, 19-22.

# *3. ODIM metadata requirements for I/O*
* Top-level “what”: object, data, time.
* Top-level “where”: lon, lat, projdef, xsize, ysize, xscale, yscale, LL_lon, LL_lat, UL_lon, UL_lat, UR_lon, UR_lat, LR_lon, LR_lat.
* Dataset-specific “what”: product, gain, offset, nodata, undetect.

# *4. Input data*
## *a) What kind of radar data (including the list of previous algorithms and quality flags applied)*
One of weather radar products that reflects ground precipitation rate RATE or accumulation ACRR as IMAGE or COMP files: PPI, CAPPI, PCAPPI, MAX, etc.

## *b) Other data (optional and mandatory, applying “universally” agreed formats, geometry)*
Data from raingauge telemetric network.

# *5. Logical steps, using any of: text, flow charts, graphics, equations (or references to equations), conditional branches in “all possible cases”.*
Radar data is considered to be better then raingauge network in reproduction of spatial distribution, whereas raingauges measure precipitation accurately in their locations. This observation was a starting point of conditional merging (Sinclair and Pegram 2005). In this approach the information from radar is used to obtain the correct spatial structure of the precipitation field, while the field values are fitted to the raingauge observations. The method consists of the following steps: 

1. Spatial interpolation of raingauge-derived precipitation data is performed using one of known methods (here IDW or ordinary Kriging). Resulting field is denoted as _R<sub>G</sub>_.
2. Next deviations between observed and interpolated radar values are calculted (_R<sub>R</sub>_) in the following way:
* spatial interpolation of radar data only from pixels with raingauge locations (field _R<sub>R’</sub>_),
* calculation of differences between the two maps (_R<sub>R</sub>'' – ''R<sub>R’</sub>_),
3. Finally spatially interpolated raingauge data is corrected using the differences (errors of interpolation) according to the following formula:


<img src="https://render.githubusercontent.com/render/math?math=R'=R_G+(R_R-R_{R'})" />

<!--	
	#!latex 
	$  R’ = R_G + (R_R - R_{R’})  $ 
-->	
	
 
where _R’_ is the merged precipitation estimate.

Gauge and radar spatial interpolation should be performed by the means of the same method. 

Two simplified techniques are available as well: simple mean field bias (MFB) and local-oriented MFB.

# *6. Output*
* Field of adjusted precipitation rate RATE or accumulation ACRR as IMAGE or COMP object.
* Quality index field QIND as IMAGE or COMP object.

# *7. Outline of a test concept exemplifying the algorithm, as a suggestion for checking that an implementation has been successful.*
Quality of merging method was evaluated applying data from May to September 2006. The two methods of spatial interpolation, IDW and ordinary Kriging, implemented in combination were tested. Radar data as 1-hour accumulations were employed. Raingauge set was divided into two subsets: 1-hour accumulation data from the first one were used in combination and from the second one for verification (10% of the whole number). Characteristics obtained using IDW method are slightly better than using Kriging (e.g., RMSE equals 0.56 for IDW whereas 0.61 for Kriging, and correlation coefficient equals 0.70 and 0.68, respectively).

In Fig. 1 an example of the coditional merging algorithm performance is shown. It illustrates one of effects of using the technique: the combined field maintains the spatial pattern of the radar field. Correlation coefficient between the combined field and radar one equals 0.86 whereas between the combined field and interpolated raingauges (using IDW method) only 0.59. On the other hand final combined rainfall field follows the mean field of raingauge interpolation. For the whole period May–September 2006 the mean values are 0.130 mm for combined field and 0.126 mm for raingauges against 0.157 mm for radar. The results are obtained for point data (in raingauge locations) using IDW method in combination. 

![Fig 1 ADJUSTMENT](/images/Fig_1_ADJUSTMENT.gif)\
_Fig. 1. Example of the algorithm running: a) radar field, b) spatially interpolated raingauge measurements, c) spatially interpolated radar measurements from raingauge locations, d) merged field._

