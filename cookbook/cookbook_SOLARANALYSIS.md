# *1. Algorithm name*
Detection and analysis of solar signals in the volume data to determine solar flux, antenna pointing bias and image width in elevation 
and azimuth  – SOLAR_ANALYSIS

# *2. Basic description*
## *a) Physical basis of the algorithm*
* Sun provides a reference pointing by which the antenna pointing biases can be calculated
* Solar flux provides a means for monitoring the stability of the radar receiver system (and may provide means for absolute calibration)
* Solar radiation in non-polarized. Hence it is a source to monitor the receiver part of the ZDR calibration.

## *b) Amount of validation performed so far*
Has been used operationally at FMI since 2007 and in the present form since 2011

## *c) References (names and contact information of all developers during the evolutionary history, scientific papers)*
* Operational work: FMI, Observation services
* Scientific papers: 
  * [1] Huuskonen, A., and I. Holleman, 2007. Determining weather radar antenna pointing using signals detected from the sun at low antenna elevations, _J. Atmos. Oceanic Technol._, *24*, 476–483.
  * [2] Holleman, I., A. Huuskonen, M. Kurri, and H. Beekhuis, 2010. Operational monitoring of weather radar receiving chain using the sun, _J. Atmos. Oceanic Technol._, *27*, 159–166.
  * [3] Holleman, I., A. Huuskonen, R. Gill, and P. Tabary, 2010. Operational monitoring of radar differential reflectivity using the sun, _J. Atmos. Oceanic Technol._, *27*, 881–887.
  * [4] Holleman, I., and A. Huuskonen, 2013. Analytical Formulas for Refraction of Radiowaves from Exoatmospheric sources,  _Radio Science_, *48*, 226–231.
  * [5] Huuskonen, A., M. Kurri, H. Hohti, H. Beekhuis, H. Leijnse, and I. Holleman, 2014. Radar performance monitoring using the angular width of the solar image, _J. Atmos. Oceanic Technol._, *31*, 1704-1712.
 
# *3. ODIM metadata requirements for I/O*
* Top-level “where”: latitude, longitude 
* Top-level “how”: beamwidth, wavelength, antgain
* Dataset-specific “what”: startdate, starttime, enddate, endtime 
* Dataset-specific “where”: elangle, rstart, nbins, nrays, rscale, a1gate
* Dataset-specific “how”: radconstH, radconstHV, polarization, pulsewidth
* Data-specific "what" : quantity, gain, offset, nodata, undetect

# *4. Input data*
## *a) What kind of radar data (including the list of previous algorithms and quality flags applied)*
quantity=TH (preferably), or DBZH. In addition ZDR if available.

## *b) Solar flux data from observatory*

Dominion Radio Astrophysical Observatory offer solar flux data measured at 10.7 cm wavelength. A formula to calculate the solar flux at C-band is given e.g. in Ref.[2] (Eq. 17).
The observatory fluxes can be used as a reference in the receive monitoring. The data can be ftp'd from www.drao-ofr.hia-iha.nrc-cnrc.gc.ca, file /pub/solar/FLUX_DATA/fluxtable.txt


# *5. Logical steps, using any of: text, flow charts, graphics, equations (or references to equations), conditional branches in “all possible cases”.*

Set of the algorithm parameters:
| Description | Denotation | Default value |
| Minimum elevation to use | min_el | 1.0  deg|
| Maximum elevation to use | max_el | 10.0  deg|
| Minimum height to use  | min_height | 2.0 km|
| Maximum elevation difference between antenna and sun  | max_eldiff | 1.5 deg|
| Maximum azimuth difference between antenna and sun  | max_azdiff | 5.0 deg|
| Maximum angular range from sun center | max_r | 1.5 deg|
| Maximum standard deviation of the solar hit | max_sd | 3.0 dB|
| Maximum deviation from the first fit  | max_fitdiff | 1.0 dB|
| Maximum angular range from sun center for ZDR | max_r_ZDR | 0.5 deg|


## *a) The first phase of the analysis is the detection of all sun hits in the data.*


The following analysis is done for all radar PPI's collected during the analysis period, which is typically one calendar day

Solar pointing is calculated, including the refraction (Ref.[4]. Eq. 13 , using k=5/4 recommended). If the PPI start azimuth (a1gate) is not known, mean of start and end times can be used.

The PPI is processed if antenna elevation is close enough to solar elevation, refraction taken into account (max_eldiff)

Process all azimuth bins which are close enough to solar azimuth (max_azdiff)

Calculate received power in dBm (Ref.[2], Eq.1). 

Calculate first bin which is above the minimum accepted height (min_height)

After the previous procssing steps the data should have a Gaussian distribution with standard deviation less than 1 dB. Occasional rain or ground clutter may corrupt the data. Data can be cleaned with an optional filtering section.

Filtering can base on mean or median values. Median is recommended. In the median fitlering median [m] is calculated, and 1st and 3rd quartal values. Difference of quartals [x] determines the filtering width. Data within [m-x, m+x] is accepted.

The above step may be repeated for the filtered data set.

After filtering calculate the mean power and standard deviation (provided that sufficient number of points (>50%) pass the filtering)

Add the overlay loss (Ref.[2], Eq. 14)

Calculate the solar flux (Ref.[2], Eq. 15). Remember to take into account the receiver bandwidth.

Please note that the above does not guarantee absolute calibration. Depending on the system, receiver losses need of must not be added. This depends on whether they are included in the
system constant or not. The finite bandwidth loss may also be needed. Monitoring of the receiver system does not require that all losses are included.

Output results (date, time, solar pointing, refraction, antenna pointing, power, standard deviation, number of points) to a (temporaray) file containg all analyzed sun hits.

In case you have access to the ZDR data, just use the same range bins that passed the filtering stages of TH, and calculate the mean and standard deviation and store in file. 

## *b) The second step of analysis is the determination of the solar flux, antenna biases, and image widths. *



Read in all solar hits. Calculate deviations in elevation and azimuth (Ref.[1], Eqs. 14 and 15), taking refraction into account.

Add atmospheric attenuation from ground to the edge of atmosphere to the solar flux (Ref.[2], Eq. 2). The attenuation depends on the solar elevation.

Select those within the specified elevation range (min_el, max_el), and with standard deviation below the limit (max_sd), and close enough to sun (max_r)

If at least 5 points exist, do a linear fit to the model (Ref.[1], Eq. 16), using standard deviations to calculate weights

Calculate fit curve based on fit results, remove data points far from the fit curve (max_fitdiff)

If at least 5 point exist, do a second fit

Calculate flux, biases and widths (Ref.[1], Eq. 17-21)

Output results (flux, biases, widths, # of points, residual variance)

The ZDR analysis is possible along the same guidelines.  Please note that the surface may have different sign of curvature in the two directions (saddle surface). It is advisable to use the center point determined in the TH analysis, and only fit for the power and the widths.  The ZDR as a function of elevation and azimuth is often constant close the sun center. Hence a simple estimate is obtained by averaging all sun hits around the center points determined by the TH analysis up to a range (max_r_ZDR). 

## *c) A note on pulse widths*

If the data contains measurement done using several pulse widths, some caution is needed. It is advisable to first analyze the data sets separately (whether analysing TH or DBZ),
and to combine all data into a single fit only after it is guaranteed that the levels agree. The levels should agree in a properly calibrated system. The solar analysis thus
provides another way to check that the system calibration is done correctly.


# *6. Output*
## a) Data type using ODIM notation where possible, e.g. DBZH
Solar flux (absolute, or relative), elevation bias, azimuth bias, image width in elevation, image width in azimuth, ZDR offset of the receiver chain

## b) Quality index (_QI_) field
Number of solar hits, residual variance (sum of squared data-model differences divided by data variances)

# *7. Outline of a test concept exemplifying the algorithm, as a suggestion for checking that an implementation has been successful.*
Comparison against an existing implementation recommeded.

For well calibrated and maintained radar systems the biases are less than 0.2 deg and width close to the antenna beam width. 
