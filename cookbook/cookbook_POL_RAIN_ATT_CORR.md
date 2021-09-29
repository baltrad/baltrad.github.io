# *1. Algorithm name*
Rain attenuation correction of reflectivity an differential reflectivity: *PolRainAttCorr*

# *2. Basic description*
A number of methods have been proposed in the literature for correcting Z,,HH,, for rain attenuation (Bringi el. al., 1990, Carey et al., 2000, Tesud et. al., 2000, Bringi et al., 2001). Describing each one of these is beyond the scope of this report. However, it is suffice to state that from an operational point of view, the so-called “Linear Ф<sub>DP</sub> with a fixed linear α”, by Bringi et. al., (1990) is preferred as it is easy to implement in real-time and is not too demanding computationally. However, its main dis-advantage is that it can over or under-estimate attenuation. In the current version of the software, this method has been implemented to correct for the attenuation suffered by Z<sub>HH</sub> and Z<sub>DR</sub> in rain.

# *3. Computational procedure*
Similar to computing K<sub>DP</sub>, correcting Z<sub>HH</sub> and Z<sub>DR</sub> for rain attenuation is rather challenging as the underlying Ф<sub>DP</sub>(r) are very “noisy” i.e., generally contain many outliers. The current method used at DMI was inspired by Bringi et. al. (2005) and involve the following steps:
1. Compute the texture of Ф<sub>DP</sub>, Tex( Ф<sub>DP</sub>(x,y)), using equation (2).
2. Generate range mask based on thresholds for Tex(Ф,,DP(x,y)threshold,,), Signal-to-Noise Ratio (SNRthreshold) and ρ,,HVthreshold,, to remove bad Ф,,DP,, values.
3. Interpolate Ф--DP-- across “bad” data segments.
4. Compute the Ф,,DP,,(0) i.e., offset at the “origin” by averaging the first N range gates FDP containing precipitation.
5. Ф,,DP,,(r) is then smoothed using a median filter with a window size of ~ 5.0 km - 6.5 km.
6. Correct both Z,,HH,, and Z,,DR,, for rain attenuation using equations (13) and (16), respectively.


# *[=#point1] 4. Theoretical background*
For an inhomogeneous path, i.e. A,,h,, varies along the path, the corrected Z,,HH,, (units of dB) is related to the measured measured Z,,HH,, at range r from the radar by the following expression[[BR]]


	
	#!latex
	\begin{equation*} Z_{HH}(r) = Z^{measured}_{HH}(r) + 2\int_{0}^{r} A_h(r) dr  \tag{1}\end{equation*}
	 



Substituting equation (10) into the above expression and assuming a is constant we get
[[BR]]
	
	#!latex
	 \begin{equation*} Z_{HH}(r) = Z^{measured}_{HH}(r) + 2\alpha\int_{0}^{r} K_{DP}(r) dr \tag{2}\end{equation*}
	 
[[BR]]

Now substituting for K,,DP,, from equation (1), the following expression is obtained for the corrected Z,,HH,,
[[BR]][[BR]]
	
	#!latex
	\begin{equation*} Z_{HH}^{corrected}(r) = Z^{measured}_{HH}(r) + \alpha[\phi_{DP}(r)  - \phi_{DP}(0)] \tag{3}\end{equation*}
	 

[[BR]]


Thus knowing by how much Ф,,DP,, increases from its value at the origin Ф,,DP,,(0) it is possible to correct the radar reflectivity, Z,,HH,[[BR]]

[[BR]]

## *Radar differential reflectivity rain attenuation correction*

Just like the above radar horizontal reflectivity, Z,,HH,, , the differential reflectivity also suffer from rain attenuation, especially at C- and X-bands. To estimate the rain attenuation of Z,,DR,,, we repeat the above procedure for Z,,HH,,. We get in this case the following expression
[[BR]]

	
	#!latex
	\begin{equation*} Z_{DR}^{corrected}(r) = Z^{measured}_{DR}(r) + 2\int_{0}^{r} A_{DP}(r)dr (4) \tag{4}\end{equation*}
	
[[BR]]

where A,,DP,, is the difference between the specific attenuations between the horizontally and vertically polarized waves, i.e., A,,DP,, = A,,H,, - A,,V,, , and is normally referred to as the specific differential attenuation. By analogy to equation (10) a linear relationship between A,,DP,, and K,,DP,, has been proposed (Bringi et. al., 1990) i.e., 
[[BR]][[BR]]
	
	#!latex
	\begin{equation*} A_{DP} = \beta\cdot K_{DP} \tag{5}\end{equation*}
	
[[BR]]

Substituting equation (15) into (14) we get the following expression for the corrected Z,,DR,,
[[BR]][[BR]]
	
	#!latex
	\begin{equation*} Z_{DR}^{corrected}(r) = Z^{measured}_{DR}(r) + \beta[\phi_{DP}(r)  - \phi_{DP}(0)] \tag{6}\end{equation*}
	 
[[BR]]

The coefficient β is typically 0.01-0.003 at C-band (Bringi et. al., 2005).


## *References*


Bringi V. N., Chandrasekar N., Balakrishnan and Zrnic D. S., 1990, _”Anexamination of propagationeffects in rainfall on radar measurements at microwave frequencies”_, J. Atmos. Oceanic Tech.,vol., 7, 829 – 840.[[BR]]

Bringi, V. N., Chandrasekar, V.: 2001, _”Polarimetric Doppler Weather Radar”_, Cambridge Univ.press, Cambridge, UK.[[BR]]

Bringi V. N., Thurai R., and Hannesen R., 2005, _“Dual-Polarization Weather Radar Handbook”_,AMS-Gematronik GmbH.[[BR]]

Carey L. D., Rutledge S. A., Ahijevych D. A., and Keenan T. D., 2000,_ “ Correcting propagationeffects in C-band polarimetric radar observations of tropical convection using differential propagationphase”_, J. Appl. Meteor., vol. 39, 1405 – 1433.
