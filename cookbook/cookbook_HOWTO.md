![BALTRAD doxlogo](/images/BALTRAD-doxlogo.png)

Algorithms included in the cookbook shall be documented by writing a wiki page for each algorithm, under the [cookbook](https://github.com:baltrad/baltrad.github.io/cookbook) directory. A recipe shall be written before a new algorithm is implemented technically.

A “recipe” in the cookbook shall contain the following sections, in order:

# 1. Algorithm name
# 2. Basic description
## a) Physical basis of the algorithm
## b) Amount of validation performed so far
## c) References (names and contact information of all developers during the evolutionary history, scientific papers)
# 3. ODIM metadata requirements for I/O
# 4. Input data
## a) What kind of radar data (including the list of previous algorithms and quality flags applied)
## b) Other data (optional and mandatory, applying “universally” agreed formats, geometry)
# 5. Logical steps, using any of: text, flow charts, graphics, equations (or references to equations), conditional branches in “all possible cases”.
Besides normal text, we can add "interactive" diagrams using Graphviz markup,
	
	```dot
	digraph G {Hello->World->BALTRAD->Cookbook}
	```
<!--![Example diagram](https://g.gravizo.com/svg?digraph G {Hello->World->BALTRAD->Cookbook})-->
	
Equations can be added using LaTeX notation, e.g.
	
	<img src="https://render.githubusercontent.com/render/math?math=\overline{P_r} = \frac{P_t G^2 \lambda^2 \theta \phi h L}{512(2 \ln 2) \pi^2 r^2} \frac{1}{\Delta v} \sum_{vol} \sigma_i" />
	```math
	\overline{P_r} = \frac{P_t G^2 \lambda^2 \theta \phi h L}
	{512(2 \ln 2) \pi^2 r^2} \frac{1}{\Delta v} \sum_{vol} \sigma_i $
	```
	
Tables can be created using the WYSIWYG functionality, e.g.

|| _Column 1'' || ''Col 2'' || ''Col 3_ ||
|| Content 1 || Content 2 || Content 3 ||

# 6. Output.
## a) Data type using ODIM notation where possible, e.g. DBZH
## b) Added quality indicators
# 7. Outline of a test concept exemplifying the algorithm, as a suggestion for checking that an implementation has been successful.
