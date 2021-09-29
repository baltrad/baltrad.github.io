# *1. Algorithm name*
Calibration difference of two radars CALID

# *2. Basic description*
## *a) Physical basis of the algorithm*
The algorithm compares reflectivity of two radars in overlapping areas. To avoid effects of external factors of distortion (e.g. distance effects, Earth curvature) only points of same distance from both radars are selected. For better performance it is advisable to discriminate screening area and clutters.

![Calid](/images/calid.png)

## *b) Amount of validation performed so far*
The algorithm was implemented in Polish radar network POLRAD. Tests cover whole year 2009 archive data from eight radars. Since 2010 it is in operation use.

## *c) References (names and contact information of all developers during the evolutionary history, scientific papers)*
The algorithm for POLRAD was developed by Stanisław Moszkowicz and Łukasz Wojtas (lukasz@baltrad.eu).

# *3. ODIM metadata requirements for I/O*
## *Input*
where/lon, /lat, /height

datasetx/where/elangle, /nbins, /rscale, /nrays

gain, offset, nodata, and undetect for reflectivity datasets

## *Output*
No ODIM metadata output

# *4. Input data*
Reflectivity data with quality index if available.

# *5. Logical steps, using any of: text, flow charts, graphics, equations (or references to equations), conditional branches in “all possible cases”.*
## *Step 1. Calculating polar coordinates of overlapping points.*
1. Finding geographical coordinates for both radars and every pixel (user can chose an elevation, the lowest are recommended). For calculation the Vincenty direct formula is used, given: start latitude and longitude (radar location), bearing (azimuth) and distance (bin number times rscale)

1. Calculating distance between each point of one radar and every point of the other radar, selecting pairs of points with the distance smaller then given threshold. Vincenty (inverse) formula for distance between two latitude, longitude points is used.

For better performance it is done only once for each radar pair, and the results are stored in a file.

![Calid overlapping points](/images/calid_overlapping_points.png)

<!--	
	#!graphviz
	digraph S {
	"below dist\nthreshold?" [shape=diamond]
	"Loop over\npixels of radar1"->"Loop over\npixels of radar2"
	"Loop over\npixels of radar2"->"Calculating\nlon/lat for radar1"
	"Calculating\nlon/lat for radar1"->"Calculating\nlon/lat for radar2"
	"Calculating\nlon/lat for radar2"->"Calculating dist\nbetween points"
	"Calculating dist\nbetween points"->"below dist\nthreshold?"
	"below dist\nthreshold?"->"Store pair"[label="no"]
	}
-->	
	
## *Step 2 Calculating statistics of two radar data comparison.*
1. Checking for every pixel pair calculated in step 1 if the reflectivity is above given threshold (e.g. 5 dBZ). If quality index is available this gives another restriction for data. Finally there must be at least some (set by user) valid data points available to perform further calculations.

1. Calculating differences between reflectivity measurements for every valid data point.

1. Calculating mean, root mean square and median for one data pair.

![Calid data comparison](/images/calid_data_comparison.png)

<!--	
	#!graphviz
	digraph A {
	"nodata?"[shape=diamond]
	"undetect?"[shape=diamond]
	"below dBZ\nthreshold?"[shape=diamond]
	"below QI\nthreshold?"[shape=diamond]
	"Loop over\npair pixels"->"nodata?"
	"nodata?"->"undetect?"[label="no"]
	"undetect?"->"below dBZ\nthreshold?"[label="no"]
	"below dBZ\nthreshold?"->"below QI\nthreshold?"[label="no"]
	"below QI\nthreshold?"->"Calculate\nstatistics"
	}
-->	
	
# *6. Output*
The output is an information about the difference between two radars. There is a couple of ways of presenting the results:

* differences for every pair pixel
* mean, rms, median of difference for one observation
* mean, rms, median of difference for longer period (e.g. hour, day, week)

# *7. Outline of a test concept exemplifying the algorithm, as a suggestion for checking that an implementation has been successful.*
to-do
