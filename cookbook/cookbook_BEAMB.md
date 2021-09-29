# 1. Algorithm name
Beam blockage - BEAMB

# 2. Basic description
Beam blockage on individual reflectivity scans is calculated and the associated power loss is determined and optionally compensated.

## a) Physical basis of the algorithm
Reflectivity measurements behind a partially blocked radar beam is weakened. By assuming a uniform beam filling this loss can be compensated.

## b) Amount of validation performed so far
Indirect validation using one month of European data from Odyssey, documented in Michelson and Henja (2012).

## c) References (names and contact information of all developers during the evolutionary history, scientific papers)
Lars Norin and Anders Henja, Swedish Meteorological and Hydrological Institute, lars.norin@smhi.se, anders.henja@smhi.se

Michelson D. and Henja A., 2012: OPERA Work Package 3.6: Odyssey additions. Task 3. Tuning and evaluation of “andre” tool. EUMETNET OPERA Working document WD_2012_02c. 20 pp.

[Henja A. and Michelson D., 2012: Improving the quality of European weather radar composites with the BALTRAD toolbox. Proc. ERAD 2012. Météo France, Toulouse, France](http://www.meteo.fr/cic/meetings/2012/ERAD/extended_abs/DQ_127_ext_abs.pdf)

# 3. ODIM metadata requirements for I/O
Besides mandatory attributes gain, offset, nodata, undetect, nrays, nbins, lat, lon, height, elangle, and rscale, the optional metadata on beamwidth is also needed.

# 4. Input data
## a) What kind of radar data (including the list of previous algorithms and quality flags applied)
Reflectivity data.

## b) Other data (optional and mandatory, applying “universally” agreed formats, geometry)
The algorithm requires GTOPO30, a global 30 arc second digital elevation data set. This data set is freely available from http://usgs.gov/. Beamb does not alter or reformat the GTOPO30 tiles; they are read and used "as is".

# 5. Logical steps, using any of: text, flow charts, graphics, equations (or references to equations), conditional branches in “all possible cases”.

![BEAMB algorithm](/images/BEAMB_algorithm.png)

<!--	
	#!latex
	The procedure is based on the creation of lookups that match a unique scan geometry. When a scan with a matching lookup is analyzed, it's lookup is read and used, otherwise perform the following:
	
	\begin{enumerate}
	
	\item Find the altitudes at the center of every radar bin by linear interpolation of the digital elevation data set.
	
	\item For every azimuth gate, starting closest to the radar, calculate the angles from the radar to each of the altitudes found in 1). If the angle is higher than the previous, store it, otherwise replace it with the previous angle. This set of angles is denoted $\alpha_\textrm{block}$.
	
	\item Assuming a Gaussian shape of the radar lobe the amount of blockage can be calculated as follows.
	
	The radar lobe power, $P$, as a function of the lobe angle, $\theta$, can be expressed as
	\begin{equation}
	P=P_0 \exp{ \left( -\frac{\theta^2}{c} \right) }
	\end{equation}
	where $P_0$ is a constant and $c$ is given by
	\begin{equation}
	c=\left( \frac{b}{2} \right)^2 /\ln{\left( 2 \right)}.
	\end{equation}
	Here $b$ is the radar lobe beamwidth at $-3$~dB.
	
	To calculate the amount of power blocked the width of the lobe taken into account must be specified. This is given by the parameter $\textrm{dB}_\textrm{lim}$, which specifies the relative power of the beam at the corresponding lobe angle (the default value is $-6$~dB).
	
	From $\textrm{dB}_\textrm{lim}$ the corresponding lobe angle, $\theta_\textrm{lim}$, can be calulated from Eq.~(1).
	\begin{equation}
	\theta_\textrm{lim}=\sqrt{-c \ln{ \left( 10^{\textrm{dB}_\textrm{lim}/10} \right) }}
	\end{equation}
	
	Limiting the Gaussian assumption to the vertical direction of the lobe the total amount of power, $\textrm{P}_\textrm{tot}$, is found by integrating  Eq.~(1) from $-\theta_\textrm{lim}$ to $\theta_\textrm{lim}$.
	\begin{equation}
	\textrm{P}_\textrm{tot}=\int_{-\theta_\textrm{lim}}^{\theta_\textrm{lim}} P_0 \exp{ \left( -\frac{\theta^2}{c} \right) } \textrm{d}\theta = \sqrt{\pi c} ~\textrm{erf}{ \left( \frac{\theta_\textrm{lim\sqrt{c}} \right) }
	\end{equation}
	
	Now, for an radar elevation angle $\alpha$, blockage is zero for $\alpha_\textrm{block} \leq \alpha - \theta_\textrm{lim}$. Similarly blockage is $100\%$ for $\alpha_\textrm{block} \geq \alpha + \theta_\textrm{lim}$. For all other angles, i.e.\ $\alpha - \theta_\textrm{lim} < \alpha_\textrm{block} < \alpha + \theta_\textrm{lim}$, the partial beam blockage, $\textrm{P}_\textrm{BB}$, is calculated as
	\begin{align}
	\textrm{P}_\textrm{BB} &= \int_{-\theta_\textrm{lim}}^{\alpha_\textrm{block}-\alpha} P_0 \exp{ \left( -\frac{\theta^2}{c} \right) } \textrm{d}\theta \\
	&= \frac{1}{2} \sqrt{\pi c} \left\{ \textrm{erf}{ \left[ \frac{\alpha_\textrm{block}-\alpha}{\sqrt{c}} \right] } + \textrm{erf}{ \left[  \frac{\theta_\textrm{lim\sqrt{c}} \right] } \right\} / \textrm{P}_\textrm{tot}
	\end{align}
	where $\textrm{erf}(.)$ is the error function.
	
	\item From the blockage mask a correction matrix can be computed
	\begin{equation}
	Z_\textrm{corr}=-10 \log_{10} \left( 1-\textrm{P}_\textrm{BB} \right).
	\end{equation}
	The correction matrix is saved.
	
	\end{enumerate}
	
	Once the correction matrix exists, for any reflectivity measurements larger
	than undetect, $Z_\textrm{corr}$ is added to compensate for blockage. This
	step is optional. A blockage threshold is used (0-1), e.g. 0.7 (70 \%), above which data are not corrected but instead masked with the "nodata" value.
-->
	
# 6. Output.
The result is an ODIM_H5 file containing a beam blockage corrected reflectivity field.

## a) Data type using ODIM notation where possible, e.g. DBZH
TH, DBZH, DBZV

## b) Added quality indicators
A quality index ranging from 0 (lowest quality) to 1 (highest) is obtained from the blockage mask. This may seem counter-intuitive, as blockage would normally be expressed the other way around, but this is done to create an ODIM-compliant quality indicator field.

# 7. Outline of a test concept exemplifying the algorithm, as a suggestion for checking that an implementation has been successful.
