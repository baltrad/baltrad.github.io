# 1. Algorithm name
Dealiasing of radial velocities in polar space (DEALIAS)

# 2. Basic description
## a) Physical basis of the algorithm
The algorithm detects abrupt velocity changes between neighboring measurements and eliminates (multiple) folding.

## b) Amount of validation performed so far
The dealiasing and wind profile algorithms have been been validated for two Swedish radar sites using radiosonde observations over a 18-month-period.

Haase, G., 2013: Validating Baltrad and Nordrad wind profile retrievals using radiosonde observations, 21 pages.

## c) References (names and contact information of all developers during the evolutionary history, scientific papers)
The software has been developed by Günther Haase and Tomas Landelius (SMHI).

Haase G. and Landelius T., 2004: De-aliasing of Doppler Radar Velocities Using a Torus Mapping. _J. Atmos. Oceanic Technol._, *21*, 1566-1573.

# 3. ODIM metadata requirements for I/O
nbins, nrays, gain, offset, nodata, undetect

# 4. Input data
## a) What kind of radar data (including the list of previous algorithms and quality flags applied)
Polar volume or scan

## b) Other data (optional and mandatory, applying “universally” agreed formats, geometry)
# 5. Logical steps
The polar coordinates _r_ (the radial coordinate) and _φ_ (the angular coordinate) are defined in terms of Cartesian coordinates by

 <img src="https://render.githubusercontent.com/render/math?math=\begin{align*}
x = r \cos \phi\\
y = r \sin \phi
\end{align*}" />

<!--	
	#!latex
	\begin{eqnarray*}
	 x & = & r \cos \phi \\
	 y & = & r \sin \phi \;.
	\end{eqnarray*}
-->	
	
Thus the unambiguous wind velocity _V<sub>u</sub>_ can be mapped onto the circumference of a cylinder with radius _r_:

<img src="https://render.githubusercontent.com/render/math?math=\begin{equation*}
2 \pi r \frac{V_u}{\pi} \:.
\end{equation*}" />

<!--	
	#!latex
	\begin{equation*}
	  2 \pi r \frac{V_u}{\pi} \;.
	\end{equation*}
-->	
	
Assuming that _φ_ equals π for _V<sub>o</sub>_=_V<sub>u</sub>_ results in

<img src="https://render.githubusercontent.com/render/math?math=\begin{equation*}
	  \phi = V_o \: \frac{\pi}{V_u}
	\end{equation*}" />
	
<!--	
	#!latex
	\begin{equation*}
	  \phi = V_o \; \frac{\pi}{V_u}
	\end{equation*}
-->	
	
where _V<sub>o</sub>_ is the observed radial wind. Hence, the corresponding Cartesian coordinates are given by

<img src="https://render.githubusercontent.com/render/math?math=\begin{align*}
x_o = \frac{V_u}{\pi} \cos \left( V_o \: \frac{\pi}{V_u} \right)\\
y_o = \frac{V_u}{\pi} \sin \left( V_o \: \frac{\pi}{V_u} \right)
\end{align*}" />

<!--	
	#!latex
	\begin{eqnarray*}
	  x_o & = & \frac{V_u}{\pi} \cos \left( V_o \; \frac{\pi}{V_u} \right) \\
	  y_o & = & \frac{V_u}{\pi} \sin \left( V_o \; \frac{\pi}{V_u} \right) \;.
	\end{eqnarray*}
-->	
	
Next, a set of _M_ x _N_ radial wind test functions (_V<sub>t</sub>_) with _M_ different wind speeds (_f_) and _N_ different wind directions (_d_) is created. The zonal (_u_) and meridional wind components (_v_) are defined as:

<img src="https://render.githubusercontent.com/render/math?math=\begin{align*}
u_{ij} = f_i \: \sin d_j \:\:\: i=1, ..., M \mbox{ and } j=1, ..., N\\
v_{ij} = f_i \: \cos d_j \:\:\: i=1, ..., M \mbox{ and } j=1, ..., N
\end{align*}" />


<!--	
	#!latex
	\begin{eqnarray*}
	  u_{ij} & = & f_i \; \sin d_j \;\;\; i=1, ..., M \mbox{ and } j=1, ..., N \\
	  v_{ij} & = & f_i \; \cos d_j \;\;\; i=1, ..., M \mbox{ and } j=1, ..., N \;.
	  \end{eqnarray*}
-->	  
	
Assuming a uniform wind the most elementary equation for the radial velocity is

<img src="https://render.githubusercontent.com/render/math?math=\begin{equation*}
(V_t)_{ij} = (w_{ij} %2B W_f) \sin \theta %2B u_{ij} \cos \theta \sin \phi %2B v_{ij} \cos \theta \cos \phi \hspace{10mm} (1)
\end{equation*}" />

<!--	
	#!latex
	\begin{equation*}
	  (V_t)_{ij} = (w_{ij} + W_f) \sin \theta + u_{ij} \cos \theta \sin \phi + v_{ij} \cos \theta \cos \phi \hspace{10mm} (1)
	\end{equation*}
-->	
	
where _W<sub>f</sub>_ is the terminal fall velocity of the hydrometeors, _w_ is the vertical wind component, and _θ_ is the elevation angle of the radar scan. For small elevation angles Eq. (1) becomes

<img src="https://render.githubusercontent.com/render/math?math=\begin{equation*}
(V_t)_{ij} = u_{ij} \sin\phi %2B v_{ij} \cos\phi
\end{equation*}" />

<!--	
	#!latex
	\begin{equation*}
	  (V_t)_{ij} = u_{ij} \sin\phi + v_{ij} \cos\phi \;.
	\end{equation*}
-->	
	
Hence, the Cartesian coordinates of the test functions are given by

<img src="https://render.githubusercontent.com/render/math?math=\begin{align*}
(x_t)_{ij} = \frac{V_u}{\pi} \cos \left( (V_t)_{ij} \: \frac{\pi}{V_u} \right)\\
(y_t)_{ij} = \frac{V_u}{\pi} \sin \left( (V_t)_{ij} \: \frac{\pi}{V_u} \right)
\end{align*}" />

<!--	
	#!latex
	\begin{eqnarray*}
	  (x_t)_{ij} & = & \frac{V_u}{\pi} \cos \left( (V_t)_{ij} \; \frac{\pi}{V_u} \right) \\
	  (y_t)_{ij} & = & \frac{V_u}{\pi} \sin \left( (V_t)_{ij} \; \frac{\pi}{V_u} \right) \;.
	\end{eqnarray*}
-->	
	
Then the radial wind test function _V<sup>*</sup><sub>t</sub>_ closest to the observed radial winds is derived using the minimum distance approach:

<img src="https://render.githubusercontent.com/render/math?math=x_t^*, y_t^* = \min\limits_{ij} \left\{ \left|(x_t)_{ij}-x_o\right| %2B \left|(y_t)_{ij}-y_o\right| \right\}" />

<img src="https://render.githubusercontent.com/render/math?math=V_t^* = u^* \sin\phi %2B v^* \cos\phi" />

<!--
	#!latex
	\begin{eqnarray*}
	  x_t^*, y_t^* & = & \min\limits_{ij} \left\{ \left|(x_t)_{ij}-x_o\right| + \left|(y_t)_{ij}-y_o\right| \right\} \\
	  V_t^* & = & u^* \sin\phi + v^* \cos\phi \;.
	\end{eqnarray*}
-->	
	
Finally, the dealiased radial winds (_V<sub>d</sub>_) are calculated by adding multiples of the unambiguous velocity interval to the observed radial winds:

<img src="https://render.githubusercontent.com/render/math?math=k^* = \min\limits_{k} \left\{ \left|2\,k\,V_u - (V_t^* -V_o)\right| \right\} \:\:\: k \in \{..., -2, -1, 0, 1, 2, ...\}" />

<img src="https://render.githubusercontent.com/render/math?math=V_d = V_o + 2\,k^*\,V_u" />
	
<!--	
	#!latex
	\begin{eqnarray*}
	  k^* & = & \min\limits_{k} \left\{ \left|2\,k\,V_u - (V_t^* -V_o)\right| \right\} \;\;\; k \in \{..., -2, -1, 0, 1, 2, ...\} \\
	  V_d & = & V_o + 2\,k^*\,V_u \;.
	\end{eqnarray*}
-->	
	
For each scan radial winds with constant range are dealiased at the same time. Generally, dealiasing should not be performed on data with large gaps.

# 6. Output.
## a) Data type using ODIM notation where possible, e.g. DBZH
VRAD

## b) Added quality indicators
If no output file is specified data, gain, and offset will be overwritten.

# 7. Outline of a test concept exemplifying the algorithm, as a suggestion for checking that an implementation has been successful.
