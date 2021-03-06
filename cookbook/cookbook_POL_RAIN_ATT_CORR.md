# *1. Algorithm name*
Rain attenuation correction of reflectivity an differential reflectivity: *PolRainAttCorr*

# *2. Basic description*
A number of methods have been proposed in the literature for correcting Z<sub>HH</sub> for rain attenuation (Bringi el. al., 1990, Carey et al., 2000, Tesud et. al., 2000, Bringi et al., 2001). Describing each one of these is beyond the scope of this report. However, it is suffice to state that from an operational point of view, the so-called “Linear Ф<sub>DP</sub> with a fixed linear α”, by Bringi et. al., (1990) is preferred as it is easy to implement in real-time and is not too demanding computationally. However, its main dis-advantage is that it can over or under-estimate attenuation. In the current version of the software, this method has been implemented to correct for the attenuation suffered by Z<sub>HH</sub> and Z<sub>DR</sub> in rain.

# *3. Computational procedure*
Similar to computing K<sub>DP</sub>, correcting Z<sub>HH</sub> and Z<sub>DR</sub> for rain attenuation is rather challenging as the underlying Ф<sub>DP</sub>(r) are very “noisy” i.e., generally contain many outliers. The current method used at DMI was inspired by Bringi et. al. (2005) and involve the following steps:
1. Compute the texture of Ф<sub>DP</sub>, Tex( Ф<sub>DP</sub>(x,y)), using equation (2).
2. Generate range mask based on thresholds for Tex(Ф<sub>DP(x,y)threshold</sub>), Signal-to-Noise Ratio (SNRthreshold) and ρ,,HVthreshold,, to remove bad Ф<sub>DP</sub> values.
3. Interpolate Ф<sub>DP</sub> across “bad” data segments.
4. Compute the Ф<sub>DP</sub>(0) i.e., offset at the “origin” by averaging the first N range gates FDP containing precipitation.
5. Ф<sub>DP</sub>(r) is then smoothed using a median filter with a window size of ~ 5.0 km - 6.5 km.
6. Correct both Z<sub>HH</sub> and Z<sub>DR</sub> for rain attenuation using equations (13) and (16), respectively.


# *4. Theoretical background*
For an inhomogeneous path, i.e. A<sub>h</sub> varies along the path, the corrected Z<sub>HH</sub> (units of dB) is related to the measured measured Z<sub>HH</sub> at range r from the radar by the following expression

<img src="https://render.githubusercontent.com/render/math?math=\begin{equation*} Z_{HH}(r) = Z^{measured}_{HH}(r) %2B 2\int_{0}^{r} A_h(r) dr  \tag{1}\end{equation*}" />

<!--	
	#!latex
	\begin{equation*} Z_{HH}(r) = Z^{measured}_{HH}(r) + 2\int_{0}^{r} A_h(r) dr  \tag{1}\end{equation*}
-->	 



Substituting equation (10) into the above expression and assuming a is constant we get

<img src="https://render.githubusercontent.com/render/math?math=\begin{equation*} Z_{HH}(r) = Z^{measured}_{HH}(r) %2B 2\alpha\int_{0}^{r} K_{DP}(r) dr \tag{2}\end{equation*}" />

<!--	
	#!latex
	 \begin{equation*} Z_{HH}(r) = Z^{measured}_{HH}(r) + 2\alpha\int_{0}^{r} K_{DP}(r) dr \tag{2}\end{equation*}
-->	 

Now substituting for K<sub>DP</sub> from equation (1), the following expression is obtained for the corrected Z<sub>HH</sub>

<img src="https://render.githubusercontent.com/render/math?math=\begin{equation*} Z_{HH}^{corrected}(r) = Z^{measured}_{HH}(r) %2B \alpha[\phi_{DP}(r)  - \phi_{DP}(0)] \tag{3}\end{equation*}" />

<!--	
	#!latex
	\begin{equation*} Z_{HH}^{corrected}(r) = Z^{measured}_{HH}(r) + \alpha[\phi_{DP}(r)  - \phi_{DP}(0)] \tag{3}\end{equation*}
-->


Thus knowing by how much Ф<sub>DP</sub> increases from its value at the origin Ф<sub>DP</sub>(0) it is possible to correct the radar reflectivity, Z<sub>HH</sub>


## *Radar differential reflectivity rain attenuation correction*

Just like the above radar horizontal reflectivity, Z<sub>HH</sub> , the differential reflectivity also suffer from rain attenuation, especially at C- and X-bands. To estimate the rain attenuation of Z<sub>DR</sub>, we repeat the above procedure for Z<sub>HH</sub>. We get in this case the following expression

<img src="https://render.githubusercontent.com/render/math?math=\begin{equation*} Z_{DR}^{corrected}(r) = Z^{measured}_{DR}(r) %2B 2\int_{0}^{r} A_{DP}(r)dr (4) \tag{4}\end{equation*}" />

<!--	
	#!latex
	\begin{equation*} Z_{DR}^{corrected}(r) = Z^{measured}_{DR}(r) + 2\int_{0}^{r} A_{DP}(r)dr (4) \tag{4}\end{equation*}
-->	

where A<sub>DP</sub> is the difference between the specific attenuations between the horizontally and vertically polarized waves, i.e., A<sub>DP</sub> = A<sub>H</sub> - A<sub>V</sub> , and is normally referred to as the specific differential attenuation. By analogy to equation (10) a linear relationship between A<sub>DP</sub> and K<sub>DP</sub> has been proposed (Bringi et. al., 1990) i.e., 

<img src="https://render.githubusercontent.com/render/math?math=\begin{equation*} A_{DP} = \beta\cdot K_{DP} \tag{5}\end{equation*}" />

<!--	
	#!latex
	\begin{equation*} A_{DP} = \beta\cdot K_{DP} \tag{5}\end{equation*}
-->	

Substituting equation (15) into (14) we get the following expression for the corrected Z<sub>DR</sub>

<img src="https://render.githubusercontent.com/render/math?math=\begin{equation*} Z_{DR}^{corrected}(r) = Z^{measured}_{DR}(r) %2B \beta[\phi_{DP}(r)  - \phi_{DP}(0)] \tag{6}\end{equation*}" />

<!--	
	#!latex
	\begin{equation*} Z_{DR}^{corrected}(r) = Z^{measured}_{DR}(r) + \beta[\phi_{DP}(r)  - \phi_{DP}(0)] \tag{6}\end{equation*}
-->

The coefficient β is typically 0.01-0.003 at C-band (Bringi et. al., 2005).


## *References*


Bringi V. N., Chandrasekar N., Balakrishnan and Zrnic D. S., 1990, _”Anexamination of propagationeffects in rainfall on radar measurements at microwave frequencies”_, J. Atmos. Oceanic Tech.,vol., 7, 829 – 840.[[BR]]

Bringi, V. N., Chandrasekar, V.: 2001, _”Polarimetric Doppler Weather Radar”_, Cambridge Univ.press, Cambridge, UK.[[BR]]

Bringi V. N., Thurai R., and Hannesen R., 2005, _“Dual-Polarization Weather Radar Handbook”_,AMS-Gematronik GmbH.[[BR]]

Carey L. D., Rutledge S. A., Ahijevych D. A., and Keenan T. D., 2000,_ “ Correcting propagationeffects in C-band polarimetric radar observations of tropical convection using differential propagationphase”_, J. Appl. Meteor., vol. 39, 1405 – 1433.
