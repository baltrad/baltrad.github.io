# *1. Algorithm name*
Baltrad Hydrometer Classifyer BALTRAD-HMC

# *2. Basic description*

Hydrometeor classification at volume level is carried out using the fuzzy logic methodology (Bringi and Chandrasekar, 2001, Zrnic et. al., 2001, Schuur et. al., 2003, Lim et. al., 2005). In the current approach, a given bin of hydrometeor class j has a score Sj given by the relation

<img src="https://render.githubusercontent.com/render/math?math=S_j = \frac{\sum_{i} w_i P_i}{\sum_i w_i}">

<!--	
	#!latex
	$ S_j = \frac{\sum_{i} w_i P_i}{\sum_i w_i} $ (eq. 1)
-->	
	 

where P<sub>i</sub> and W<sub>i</sub> are the value of the parameter i, and the associated weight, for the class j. The radar parameters that have been used in the classifier are: Z<sub>HH</sub>, Z<sub>R</sub>, K<sub>DP</sub>, σ<sub>HV</sub> , plus the texture parameters, associated with Z<sub>HH</sub>, Z<sub>DR</sub>, Ф<sub>DP</sub> (Schuur et. al., 2003, Sugier et. al., 2006). In fuzzy logic the values of the P<sub>i</sub> for the different hydrometeor classes are described by the membership functions (MF).

## *Hydrometeor classes*
In the current version of the algorithm the following 12 hydrometeor classes have been identified:
1. ground clutter,
2. sea clutter,
3. electrical signals from external emitters (EE) that interfere with our radars,
4. clean air echoes (CAE) such as from birds and insects,
5. drizzle,
6. light rain,
7. moderate rain,
8. heavy rain,
9. violent rain,
10. light snow,
11. moderate to heavy snow,
12. rain/hail mixture.
However, internally in the BALTRAD-HMC software there are two classes each of ground and sea clutter, ten classes of external emitters including the signals from the sun and three classes of CAE. Further, the light rain class consists of four sub-classes; light drizzle, moderate drizzle, heavy drizzle and light rain.


# *3. Computational procedure*

The software consists of two main modules:
A. Computation of all the radar parameters that are to be used in the fuzzy logic classifier
B. Using fuzzy logic rules classify each bin of the radar returned echo into one of the predefined hydrometeor classes.

The computational procedure involves the following steps for module A:

1. from the radar volume file read in the following radar parameters: reflectivity Z<sub>HH</sub>, differential reflectivity Z<sub>DR</sub>, cross correlation σ<sub>HV</sub>, differential phase Ф<sub>DP</sub>, radial velocity V<sub>r</sub> and spectral width W

2. by changing the default settings in the metadata file, choose whether to undertake the following operations:\
  a. smooth Z<sub>DR</sub> and σ<sub>HV</sub> parameters, by averaging over N number of range gates,\
  b. correct Z<sub>DR</sub> and σ<sub>HV</sub> at low signal-to-noise (SNR) ratio values,\
  c. correct Z<sub>DR</sub> and Ф<sub>DP</sub> for radome effects,\
  d. correct Z<sub>DR</sub> and Ф<sub>DP</sub> for potential biases,\
  e. compute the specific differential phase, K<sub>DP</sub>, as described in section 4 above,\
  f. correct both Z<sub>HH</sub> and Z<sub>DR</sub> for rain attenuation as described in section 5 above.

3. now compute the following radar parameters in their appropriate units:\
  a. Z<sub>HH</sub> (unit dBZ) and its texture parameter, Tex(Z<sub>HH</sub>),\
  b. Z<sub>DR</sub> (unit dB) and its texture parameter, Tex( Z<sub>DR</sub>),\
  c. σ<sub>HV</sub> and its texture parameter, Tex(σ<sub>HV</sub>),\
  d. Ф<sub>DP</sub> (unit deg.) and its texture parameter, Tex(Ф<sub>DP</sub>),\
  e. K<sub>DP</sub> (unit deg./km) and its texture parameter, Tex(K<sub>DP</sub>),\
  f. V<sub>r</sub> (unit m/s) and its texture parameter, Tex(V<sub>r</sub>),\
  g. W (unit m/s) and its texture parameter, Tex(W ),\
  h. signal-to-noise ratio parameter, SNR (unit dB), and\
  i. the top, centre and bottom heights (unit meters) of the radar beam, HTT, HTC and HTB, respectively.

The computational procedure involves the following steps for module B:
1. read in all the computed radar parameters from module A

2. by changing the default settings in the metadata file, choose which of the above parameters are to be used for level-1 and level-2 hydrometeor classification

3. read-in a , ß and γ indicating the centre, half- width at inflection point and the slope of the curve of the Beta functions (see fig. 1), for each radar parameter including the associated weights

4. for level-1 hydrometeor classification, for each radar echo \
  a. get the “scores “ of each of the parameter\
  b. using fuzzy logic rules compute the final score for each predefined classes (precipitation, clutter, clean air echoes, and external emitters)\
  c. classify the bin by choosing the predefined hydrometeor class with the highest score\
  
5. for level-2 hydrometeor classification\
  a. compute the heights of the melting layers using:\
  &nbsp;&nbsp;i. the radar volume data, and\
  &nbsp;&nbsp;ii. from Numerical Weather Prediction (NWP) models\
  b. get the “scores “ of each of the parameter\
  c. using fuzzy logic rules compute the final score for each predefined classes (see section 2)\
  d. classify the bin by choosing the predefined hydrometeor class with the highest score

# *4. Theoretical background*
In fuzzy logic the values of the P,,i,,, in equation (2), for the different hydrometeor classes are described by the membership functions. In the current version the latter are expressed as Betafunctions of the type shown in fig. 1 with the 3 parameters: a, ß and γ indicating the centre, halfwidth at inflection point and the slope of the curve (Lim et. al., 2005).

![Beta membership function](/images/beta_function.png)\
_Fig. 1 Beta membership function_

As a way of example, fig. 2 shows the membership functions for the parameter Z,,HH,, for the different classes of rain.


![Membership functions](/images/membershift_functions.png)\
_Fig. 2 Membership functions for Z<sub>HH</sub> for different categories of rain._

Similar membership functions exits for other hydrometeor classes for Z<sub>HH</sub> and for all the other parameters used in the classification.

There has been much interest from international colleagues in the radar echo class 3 mentioned in section 2 above, because as far it is know, no hydrometeor classifier has included a class for the external emitters before (Gill et. al., 2012). For this reason the membership functions of Z,,HH,, Z,,DR,, and σ,,HV,, for the different types of external emitters included in the classifier are given below(fig. 3). Also note radar echoes from the sun are also a sub-class of external emitters. Membership function of the sun plus those of external emitters for the parameter Z,,HH,, can be seen in the bottom left part of fig. 3.

![Membership functions](/images/membershift_functions2.png)\
_Fig. 3 Membership functions of Z<sub>HH</sub>, Z<sub>DR</sub> and rho<sub>HV</sub> for the different types of external emitters included in the classifier. Top left MF of a single external emitter of Z<sub>DR</sub>. Top right MF of all 9 external emitters of Z<sub>DR</sub> . Bottom left of all 9 external emitters and of sun of Z<sub>HH</sub>. Bottom right MF of all 9 external emitters of σ<sub>HV</sub>_

## *Examples of output from the hydrometeor classifier*

The current version of the algorithm does the so-called level 1 and level 2 classifications. In the level 1 classification a radar echo is classified into one of four simple classes: precipitation, clutter, clean air echoes, and external emitters. Figure 4 shows an example of the output.

![Radar image](/images/lev1_class_1.png)\
_Fig. 4 shows radar image on the left ( Z<sub>HH</sub> original) and its corresponding level 1 hydrometeor classification into four classes: external emitters (EE), clean air echoes (CAE), clutter and precipitation (prec), colour code: yellow, blue, purple and green, respectively._

In the level 2 classification, the echoes that are classified as precipitation in level 1 are further subclassified into different precipitation classes mentioned above. In this case the heights of the melting layer computed by the local NWP model and/or estimated from the radar parameters [#point2 (see section 3)] are used to strengthen the classification between the different classes of rain and snow. In the current version of the level-2 classification only the parameters Z<sub>HH</sub>, Z<sub>DR</sub>, K<sub>DP</sub>, and σ<sub>HV</sub> are used. In particular, in this case score S<sub>j</sub> is given by the relation

<img src="https://render.githubusercontent.com/render/math?math=S_j = \frac{ P^j_{Zhh} \,\cdot \, P^j_{height}[w_{Zdr} \,\cdot \,P^j_{Zdr} + w_{\rho hv}\,\cdot \,P^j_{\rho{hv}} + w_{Kdp}\,\cdot \,P^j_{Kdp}]}{w^j_{Zdr} + w^j_{\rho_{hv}} + w^j_{Kdp}}" />

<!--	
	#!latex
	$ S_j = \frac{ P^j_{Zhh} \,\cdot \, P^j_{height}[w_{Zdr} \,\cdot \,P^j_{Zdr} + w_{\rho hv}\,\cdot \,P^j_{\rho{hv}} + w_{Kdp}\,\cdot \,P^j_{Kdp}]}{w^j_{Zdr} + w^j_{\rho_{hv}} + w^j_{Kdp}}$ (eq. 2)
-->	

Fig. 5 shows an example of the level 2 classification. Note that the radar data used to illustrate the classifications results are the same in figures 4 and 5.

![Radar image](/images/lev2_class_1.png)\
_Fig. 5 shows radar image on the left (original Z<sub>HH</sub> ) and its corresponding level 2 hydrometeor classifications into eleven classes._


In addition to the above level 1 and 2 classifications, the algorithm can make use of the above classification output to remove the non- meteorological echoes in the original radar reflectivity product, Z<sub>HH</sub>, shown on the left in each of the figures 4 and 5. This is illustrated in figure 6 below. Concerning the latter product, it was the first product that was requested for routine operational use by the DMI end users, namely its meteorologists.

![Radar product](/images/cleaned_1.png)\
_Fig. 6 shows the original radar product on the left and corresponding “cleaned” version on the right which has non-meteorological echoes removed._


## *References*
Bringi, V. N., Chandrasekar, V.: 2001, _Polarimetric Doppler Weather Radar_, Cambridge Univ. press, Cambridge, UK.

Gill R.S., Sørensen M. B., Bøvith T., Koistinen J., Peura M., Michelson D., and Cremonini R., 2012, _BALTRAD dual polarization hydrometeor classifier_, ERAD 2012, 7th European conference on Radar in Meteorology and Hydrology

Lim S., Chandrasekar V., and Bringi V. N., 2005, “_Hydrometeor classification system using dualpolarization radar measurements: Model improvements and in situ verification_”, IEEE transactions of Geosciences and remote sensing, vol. 43, no. 4, 792-801.

Schuur, T., Ryzhkov A., and P. Heinselmann, 2003, _Observations and classification of echoes with the polarimetric WSR-88D radar_, NOAA National Severe Storms laboratory Tech. Report, Norman, Oklahoma, USA.

Sugier, J., Tabary P., and J. Gourley, 2006, _Evaluation of dual polarization technology at C band for operational weather radar network_, report of the EUMETNET OPERA II, work packages 1.4 and 1.5.

Zrnic D. S., Ryzhkov A., Straka J., Liu Y., and Vivekanandan J., _Testing a procedure for automatic classification of hydrometeor types_, J. atmospheric and oceanic technology, vol. 18, 892-913.



