# 1. Algorithm name
Retrieval of vertical profiles (reflectivity, wind speed, and wind direction) from polar volume data (WRWP)

# 2. Basic description
## a) Physical basis of the algorithm
The algorithm is based on the VVP method.

## b) Amount of validation performed so far
The dealiasing and wind profile algorithms have been been validated for two Swedish radar sites using radiosonde observations over a 18-month-period.

Haase, G., 2013: Validating Baltrad and Nordrad wind profile retrievals using radiosonde observations, 21 pages.

## c) References (names and contact information of all developers during the evolutionary history, scientific papers)
The software has been developed by Günther Haase and Tomas Landelius (SMHI).

Haase G. and Landelius T., 2004: De-aliasing of Doppler Radar Velocities Using a Torus Mapping. _J. Atmos. Oceanic Technol._, *21*, 1566-1573.

# 3. ODIM metadata requirements for I/O
nbins, nrays, gain, offset, nodata, undetect, rscale, elangle

# 4. Input data
## a) What kind of radar data (including the list of previous algorithms and quality flags applied)
Polar volume or scan 

## b) Other data (optional and mandatory, applying “universally” agreed formats, geometry)
# 5. Logical steps
This algorithm derives vertical profiles of reflectivity, wind speed, and wind direction from polar volume data.

Assuming a uniform wind field the radial wind (_V_) has the form of a sine for constant range and elevation angle:

![Fig 1 WRWP](/images/Fig_WRWP_formula_1.png)

<!--	
	#!latex
	\begin{equation*}
	 V (\phi) = \alpha \sin(k (\phi +\beta)) + \gamma \hspace{10mm} (1)
	\end{equation*}
-->	
	
where _φ_ is the azimuth angle. The four constants are amplitude ( &#124; _α_&#124;  ), period (2π/_k_), phase shift (_β_), and vertical displacement (_γ_). The terminal velocity of the falling hydrometeors is implicitly included in _γ_. For _k_=1 Eq. (1) yields

![Fig 2 WRWP](/images/Fig_WRWP_formula_2.png)

<!--	
	#!latex
	\begin{eqnarray*}
	 V (\phi) & = & \alpha \sin(\phi +\beta) + \gamma \hspace{10mm} (2) \\
	 & = & \alpha \cos\beta \sin\phi + \alpha \sin\beta \cos\phi + \gamma \\
	 & = & w_1 \sin\phi + w_2 \cos\phi + w_3 \\
	 & = & \begin{pmatrix} \sin\phi & \cos\phi & 1 \end{pmatrix} \begin{pmatrix} w_1 \\ w_2 \\ w_3 \end{pmatrix} \hspace{10mm} (3)
	\end{eqnarray*}
-->	
	
with

![Fig 3 WRWP](/images/Fig_WRWP_formula_3.png)

<!--	
	#!latex
	\begin{eqnarray*}
	 w_1 & = & \alpha \cos \beta \hspace{10mm} (4) \\
	 w_2 & = & \alpha \sin \beta \hspace{10mm} (5) \\
	 w_3 & = & \gamma \;. \hspace{10mm} (6)
	\end{eqnarray*}
-->	
	
Equation (3) can be extended to _n_ velocities which results in a nonhomogeneous matrix equation of the form:

![Fig 4 WRWP](/images/Fig_WRWP_formula_4.png)

<!--	
	#!latex
	\begin{equation*}
	 \label{matrix_vn.eq}
	 \underbrace{
	 \begin{pmatrix} 
	  V_1 \\
	  \cdots \\
	  V_n
	 \end{pmatrix}}_{\bf V}
	 =
	 \underbrace{
	 \begin{pmatrix} 
	  \sin\phi_1 & \cos\phi_1 & 1 \\
	  \cdots & \cdots & \cdots \\
	  \sin\phi_n & \cos\phi_n & 1
	 \end{pmatrix}}_{\bf A}
	 \underbrace{
	 \begin{pmatrix}
	  w_1 \\
	  w_2 \\
	  w_3
	 \end{pmatrix}}_{\bf w} \;. \hspace{10mm} (7)
	\end{equation*}
-->
	
For more than three independent measurements, i.e. _n_>3, Eq. (7) is an overdetermined linear system which can be solved using a QR factorization of _A_. The resulting values _w<sub>1</sub>_, _w<sub>2</sub>_, and _w<sub>3</sub>_ are utilized to determine _α_, _β_, and _γ_ in Eq. (2). Squaring and adding Eqs (4) and (5) leads to

![Fig 5 WRWP](/images/Fig_WRWP_formula_5.png)

<!--	
	#!latex
	\begin{equation*}
	 w_1^2 + w_2^2 \sqrt{w_1^2 + w_2^2} \;. \hspace{10mm} (8)
	\end{equation*}
-->	
	
Solving Eq. (4) for _α_ and inserting it into Eq. (5) results in

	
	#!latex
	\begin{equation*}
	 \frac{w_2}{w_1} \frac{w_2}{w_1} \;\; \Leftrightarrow \;\; \beta = \arctan\frac{w_2}{w_1} \;.
	\end{equation*}
	
Finally, Eq. (6) provides an expression for the vertical displacement _γ''. Hence, Eq. (2) describes the radial wind model which is closest to the observations. The real wind velocity is identical with the amplitude ''α_ in Eq. (8) while the wind direction is obtained from the derivative with respect to azimuth angle

	
	#!latex
	\begin{equation*}
	 \frac{\partial V}{\partial \phi} = \alpha \cos(\phi + \beta) \stackrel{!}{=} 0 \;. \hspace{10mm} (9)
	\end{equation*}
	
Hence, Eq. (9) equals zero for

	
	#!latex
	\begin{eqnarray*}
	 \phi_1 + \beta \frac{\pi}{2} - \beta \\
	 \phi_2 + \beta \frac{3}{2}\pi - \beta
	\end{eqnarray*}
	
where _φ,,1 ,,''and ''φ,,2 ,,_are the extreme values of Eq. (2). The second derivative of Eq. (2) with respect to azimuth angle is

	
	#!latex
	\begin{eqnarray*}
	 \frac{\partial^2 V}{\partial \phi^2} & = & -\alpha \sin(\phi + \beta) \\
	 \left. \frac{\partial^2 V}{\partial \phi^2} \right|_{\phi_1} & = & -\alpha \\
	 \left. \frac{\partial^2 V}{\partial \phi^2} \right|_{\phi_2} & = & \alpha \;.
	\end{eqnarray*}
	
From Eq. (8) we know that _α''>0. Thus, the radial velocity in Eq. (2) has a maximum at ''φ,,1,,'' and a minimum at ''φ,,2,,''. Usually the wind direction is expressed in terms of the direction from which the wind originates (for example, a westerly wind blows from the west to the east). Furthermore, radial velocities away from the radar (outbound) are defined as positive while velocities towards the radar (inbound) are defined as negative. Therefore the wind direction in the specified height layer is given by ''φ,,2,,_.

# 6. Output.
## a) Data type using ODIM notation where possible, e.g. DBZH
dbz, dbz_dev, ff, ff_dev, dd, n (DBZH/VRAD)

## b) Added quality indicators
# 7. Outline of a test concept exemplifying the algorithm, as a suggestion for checking that an implementation has been successful.
