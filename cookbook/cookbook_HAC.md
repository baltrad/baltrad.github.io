# 1. Algorithm name
Hit-accumulation clutter filter: HAC

# 2. Basic description
## a) Physical basis of the algorithm
By summing all polar bins in a scan with a uniquely-defined geoometry, the frequency of detection can be used as a criterion for determining whether a given bin is contaminated by clutter. Frequency of detection is thresholded hit accumulation, which is used to remove clutter and store it in a separate quality indicator field.

## b) Amount of validation performed so far
See references below.

## c) References (names and contact information of all developers during the evolutionary history, scientific papers)
Michelson D. and Henja A., 2013: OPERA WP3.6, Task #4. Implementation of hit-accumulation clutter filter in BALTRAD toolbox. EUMETNET OPERA Working document WD_2012_02p. 8 pp.

Scovell R., 2012: OPERA WP 3.6 Task #2 Evaluation of the Odyssey Clutter Removal Technique Using Radar vs. Gauge Comparisons Over the UK. EUMETNET OPERA Working document WD_2012_02f. 53 pp.

# 3. ODIM metadata requirements for I/O
No optional 'how' attributes are required.

# 4. Input data
## a) What kind of radar data (including the list of previous algorithms and quality flags applied)
Polar scans (/what/object=SCAN) containing horizontal reflectivity (DBZH) are the basis for this algorithm, although other quantities can also be used. Polar volumes are also input; their scans are treated individually. No previous QC step need have been applied. 

## b) Other data (optional and mandatory, applying “universally” agreed formats, geometry)
# 5. Logical steps.
The algorithm has two steps:

1. *Increment*. For each input scan, increment a hit counter for each bin that is not NODATA or UNDETECT. The files containing the hit counters are generated each month and used to filter data during the subsequent month.
1. *Filter*. For each input scan to be processed, read the previous month’s hit-counter file and use it to filter clutter. The filter criterion is: data where the hit counter is higher than a specified frequency threshold are replaced with the NODATA value. Filtered reflectivity data are moved to a _quality indicator _field that is associated with the input reflectivity, thus making it possible to reverse the QC step. No in-filling is performed; this is saved for the composite generator to do.

# 6. Output.
## a) Data type
The output reflectivities are the same data type as the input. 

## b) Added quality indicators
A quality field containing the filtered reflectivities is written. This field has the same data type as the original quantity.

The identifier for this algorithm, written to the quality indicator's how/task attribute is "eu.opera.odyssey.hac".

# 7. Test concept.
