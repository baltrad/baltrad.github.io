# *1. Algorithm name*
Total quality index for scans/volumes – QI_TOTAL

# *2. Basic description*
## *a) Physical basis of the algorithm*
Integration of quality indices generated by all or selected quality algorithms. 

## *b) Amount of validation performed so far*
Not developed yet.

## *c) References (names and contact information of all developers during the evolutionary history, scientific papers)*
IMGW, Department of Ground Based Remote Sensing. 

# *3. ODIM metadata requirements for I/O*
* General “what”: source(NOD).
* Dataset-specific “what” for _QI_ data: gain, offset, nodata, undetect.
* Dataset-specific “where” for _QI_ data: nbins, nrays.  

# *4. Input data*
## *a) What kind of radar data (including the list of previous algorithms and quality flags applied)*
object=PVOL or SCAN; quantity=QIND (_QI_ information generated by particular quality algorithms). 

## *b) Other data (optional and mandatory, applying “universally” agreed formats, geometry)*
None.

# *5. Logical steps, using any of: text, flow charts, graphics, equations (or references to equations), conditional branches in “all possible cases”.*

*Quality Index (_QI_) definition*

Quality index _QI'' is a unitless quantity with values in the range from 0 to 1, where: ''QI_ 1 for excellent data. 

*Algorithm parameters*

Set of the algorithm parameters:

| Description | Denotation | Available options | Default value |
| List of _QI_ fields | QIFields | Example: “pl.imgw.radvoqc.att, pl.imgw.radvolqc.spike” NULL means all available QI fields | NULL (all available) |
| Methods of combination of particular _QI''s into total ''QI_ | Method | multi / add / min | multi |
| Overwrite if total _QI_ already exists | Overwrite | 0 (no) / 1 (yes) | 0 |

At first the XML file is checked whether there exists group for a considered radar (based on the radar name read from "what"/source(NOD)), which contains the algorithm parameters. If "yes", then parameters are read from that XML group, but if it is impossible for a particular parameter, then default value from source code is taken. If the group does not exist, parameters are read from <default> group in XML file in analogous way. 

If the algorithm is run by means of BALTRAD toolbox then all the algorirthm parameters for each specific radar should be placed in relevant XML file by the BALTRAD system admin. Default parameters are placed in the file by admin as well. Moreover, the algorithm default parameters are also included in software. 

*Computation*

Total quality index is generated from all or selected quality indices earlier generated by BALTRAD quality algorithms. It constitutes the final stage in data volumes processing.

The total _QI_ is generated:
* from all _QI'' fields available in quality''n_ fields (quantity=QIND),
* from _QI_ fields selected for particular quality algorithms ("how": task).

If there are no available particular _QI'' fields then total ''QI'' is not generated. If a given pixel is marked as "nodata" value at least in one of ''QI'' fields then "nodata" is assigned to total ''QI_ as well.

The following methods for the _QI_s combination are to select:
* *multi* (multiplicative) \
<img src="https://render.githubusercontent.com/render/math?math=QI = \Pi_{i=1}^{n}QI_{i}" />
 	
<!-- 	
	#!latex 
	$ QI = \Pi_{i=1}^{n}QI_{i} $
-->	
	 
* *add* (additive)\
<img src="https://render.githubusercontent.com/render/math?math=QI = \frac{1}{n} \sum_{i=1}^{n}QI_{i}" />
 	
<!--
	#!latex 
	$ QI = \frac{1}{n} \sum_{i=1}^{n}QI_{i}    $
-->	
	
* *min* (minimum value)\
<img src="https://render.githubusercontent.com/render/math?math=QI = \text{min}(QI_{i})" />

<!-- 	
	#!latex 
	$ QI = \text{min}(QI_{i})    $
-->	
	
where _i'' = 1, …, ''n''; ''n_ is the number of particular quality indices.
  
# *6. Output*
## *a) Data type using ODIM notation where possible, e.g. DBZH*
No changes. 

## *b) Quality index (QI) field*
Total quality index _QI_ with:
* "pl.imgw.qi_total" in quality-specific "how": task, 
* combination method and the particular contributing _QI_s listed in "how": task_args. 

# *7. Outline of a test concept exemplifying the algorithm, as a suggestion for checking that an implementation has been successful.*
TBD
