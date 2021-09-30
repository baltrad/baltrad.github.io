Quality-based compositing: QCOMP

# 2. Basic description
Based on existing quality controls in the BALTRAD Toolbox, tools improving and characterizing data quality are selected and chained together to produce a _QI_TOTAL_ quality index that is used as the prioritized compositing criterion.

## a) Physical basis of the algorithm
"The" algorithm is in fact a combination of several. It is not necessarily physical, but rather quality-based which is inherently a combination of both quantitative (_ropo, hac, beamb, radvol-broad'') and qualitative aspects (''radvol-broad, poo_) of QC.

Each polar QC step is performed prior to composite generation. _QI_TOTAL_ is calculated for each site, and then it is used as the prioritized compositing criterion. The composting itself is performed using the toolbox compositing functionality that navigates input polar data directly to the output composite Cartesian surface without any intermediate transformation(s).

## b) Amount of validation performed so far
Several BALTRAD partners are running_ ropo'' operationally, and both ''ropo'' and ''hac'' are running operationally at Odyssey. ''beamb'' was validated in early 2012 as part of the trial of the BALTRAD toolbox for Odyssey. ''RADVOL'' has been validated by IMGW. ''poo'' is being used operationally at FMI. ''QI_TOTAL_ has not yet been validated, alone or in compositing.

## c) References (names and contact information of all developers during the evolutionary history, scientific papers)

| **QC** | **Reference** | **Description**|
| ropo | [BALTRAD Manual](http://git.baltrad.eu/manual/bropo/index.html) | Anomaly detection and removal. Operational at Odyssey. Descriptive and corrective. |
| hac | [BALTRAD Cookbook](cookbook_HAC) | Hit-accumulation clutter filtering. Operational at Odyssey. Descriptive and corrective. |
| beamb | [BALTRAD Cookbook](cookbook_BEAMB) | Beam-blockage analysis and correction. Descriptive and corrective. |
| radvol-att | [BALTRAD Cookbook](cookbook_RADVOL_ATT) | Conventional single-polarization attenuation correction. Descriptive and corrective. |
| radvol-broad | [BALTRAD Cookbook](cookbook_RADVOL_BROAD) | Quality characterization due to distance to radar related effects. Overall analysis of range and pulse volume. Descriptive. |
| poo | [BALTRAD Cookbook](cookbook_BEAM_OVERSHOOT) | Probability of overshooting. Descriptive. |
| QI_TOTAL | [BALTRAD Cookbook](cookbook_QIT) | "Total" quality. Descriptive. |

### Additional references:
Koistinen J. and Hohti H., 2010: Operational diagnosis of precipitation detection range. Proc. ERAD 2010 (short abstract).

Michelson D. and Henja A., 2012: OPERA Work Package 3.6: Odyssey additions. Task 3. Tuning and evaluation of “andre” tool. EUMETNET OPERA Working document WD_2012_02c. 20 pp.

[Henja A. and Michelson D., 2012: Improving the quality of European weather radar composites with the BALTRAD toolbox. Proc. ERAD 2012. Météo France, Toulouse, France](http://www.meteo.fr/cic/meetings/2012/ERAD/extended_abs/DQ_127_ext_abs.pdf)

Michelson D. and Henja A., 2013: OPERA WP3.6, Task #4. Implementation of hit-accumulation clutter filter in BALTRAD toolbox. EUMETNET OPERA Working document WD_2012_02p. 8 pp.

[Ośródka, K., Szturc, J., and Jurczyk, A., 2012. Chain of data quality algorithms for 3-D single-polarization radar reflectivity (RADVOL-QC system). Meteorol. Appl.](http://onlinelibrary.wiley.com/store/10.1002/met.1323/asset/1323_ftp.pdf?v=1&t=hs1w7r1c&s=8bf667d43bc83f23f74850d2c4f45a18a151e418)

Peura M., 2002: Computer vision methods for anomaly removal. Proc. ERAD 2002, 312–317

# 3. ODIM metadata requirements for I/O
Limited optional 'how' metadata are required in processing polar data: RADVOL-BROAD requires the beamwidth and pulsewidth. Otherwise, only mandatory metadata from 'what' and 'where' groups. In generating the composite, metadata and quality fields generated from the polar quality processing chain are used.

# 4. Input data
## a) What kind of radar data (including the list of previous algorithms and quality flags applied)
Horizontally-polarized reflectivity (DBZH) is the basis for the polar QC chain and QCOMP.

## b) Other data (optional and mandatory, applying “universally” agreed formats, geometry)
# 5. Logical steps

![Diagram QCOMP](/images/Fig_1_QCOMP.png)

<!--
	
	#!graphviz
	digraph QCOMP {
	rankdir=TB
	"ropo"[shape=circle,fixedsize=true,width=1.3]
	"hac"[shape=circle,width=1.3]
	"beamb"[shape=circle,width=1.3]
	"radvol-att"[shape=circle,width=1.3]
	"radvol-broad"[shape=circle,fixedsize=true,width=1.3]
	"poo"[shape=circle,width=1.3]
	"QI_TOTAL"[shape=circle]
	"QCOMP"[shape=box]
	"ropo"->"QI_TOTAL"[label="w1"]
	"hac"->"QI_TOTAL"[label="w2"]
	"beamb"->"QI_TOTAL"[label="w3"]
	"radvol-att"->"QI_TOTAL"[label="w4"]
	"radvol-broad"->"QI_TOTAL"[label="w5"]
	"poo"->"QI_TOTAL"[label="w6"]
	"QI_TOTAL"->"QCOMP"[label="w_site"]
	}
-->
	
Chaining the polar QC algorithms together is a simple matter of using a script like `odc_toolbox` on the command line:

`$ odc_toolbox -i input_directory -o output_directory -q hac-increment,ropo,hac-filter,beamb,radvol-att,radvol-broad,poo,qi_total`

In generating _QI_TOTAL _for each site, each of its input quality indicators can be assigned a weight. These can be looked up from XML file; default weights are included.

Composite generation using QCOMP is performed using the output from polar QC. The compositing must be based on a conventional selection criterion, e.g. in cases where all input data have the same quality. This criterion is selectable from among those presently available in the toolbox 'slow compositing' functionality: nearest radar, lowest value to the Earth's surface, PMAX and MAX. Each site's _QI_TOTAL'' may be assigned a weight when generating the composite. This can be looked up from the same XML file as is used to process the single-site polar input data. A multiplicative model is suggested for calculating ''QI_TOTAL_ for these purposes.

Performance of this algorithm can be greatly improved if this composite generator is "tiled" for large composite domains, as was successfully shown in the trial of the toolbox for Odyssey (Michelson and Henja, 2013, Henja and Michelson, 2012). A prerequisite, however, is that there are as many logical CPU cores as there are tiles. For the trial at the European level, six logical CPU cores were required. (A normal quad-core CPU has eight logical cores.)

# 6. Output.
## a) Data type using ODIM notation where possible, e.g. DBZH
## b) Added quality indicators
| **QC** | **how/task** | **Comment** |
| ropo | fi.fmi.ropo.detector.classification | |
| hac | eu.opera.odyssey.hac | |
| beamb | se.smhi.detector.beamblockage | |
| radvol-att | pl.imgw.radvolqc.att | |
| radvol-broad | pl.imgw.radvolqc.broad | |
| poo | se.smhi.detector.poo | |
| qi_total | pl.imgw.detector.qi_total | |
| distance | se.smhi.composite.distance.radar | Optionally added during composite generation |

# 7. Outline of a test concept exemplifying the algorithm, as a suggestion for checking that an implementation has been successful.
The formulation of unit test(s) is TBD.

The trial of this implementation can be carried out on one or several months of data and validated against gauges as was done with the trial of _ropo'' and ''beamb_.
