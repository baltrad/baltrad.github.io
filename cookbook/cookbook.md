![BALTRAD doxlogo](/images/BALTRAD-doxlogo.png)

Welcome to this "cookbook", where "recipes" are collected. This is intended to constitute a documentation reference collection of data processing algorithms. Each algorithm recipe is documented in a standardized way, enabling them to be coded as part of the BALTRAD code base or an external system. The important thing is that the community can focus this effort in a harmonized way.

# Documentation
[How to write a cookbook recipe](cookbook_HOWTO)

<!--
[Cookbook roadmap](http://git.baltrad.eu/trac/wiki/cookbook/roadmap)

[Development and maintenance](http://git.baltrad.eu/trac/wiki/cookbook/dev-maint)

[wiki:cookbook/meetings Meeting minutes]
-->

# Recipes
Add the new recipe under an appropriate category

## Anomalies
[Removal of geometrically-shaped non-meteorological echoes and quality characterization – RADVOL-QC: SPIKE](cookbook_RADVOL_SPIKE)

[Removal of non-meteorological echoes and quality characterization – RADVOL-QC: NMET](cookbook_RADVOL_NMET)

[Removal of measurement noise and quality characterization – RADVOL-QC: SPECK](cookbook_RADVOL_SPECK)

[Hit-accumulation clutter filter: HAC](cookbook_HAC)

[Identification and removal of residual non-precipitation echoes using the Meteosat Second Generation Cloud Type product: CTFILTER](cookbook_CTFILTER)

## Biological Targets
## Solar monitoring
[Determination and analysis of solar signatures in volume data](cookbook_SOLARANALYSIS)

## Hail
## Volcanic Ash Plumes
## Beam Blockage
[Correction of partial and total beam blockage and quality characterization including ground clutter – RADVOL-QC: BLOCK](cookbook_RADVOL_BLOCK)

[Analysis and correction of beam blockage due to topography: BEAMB](cookbook_BEAMB)

[Probability of beam overshoot / detection range analysis : BEAM_OVERSHOOT](cookbook_BEAM_OVERSHOOT)
## Classifiers
[Baltrad Hydrometeor Classifier : BALTRAD-HMC](http://git.baltrad.eu/trac/wiki/cookbook/BALTRAD-HMC)

## Path attenuation correction
[Polarimetric Rain Attenuation Correction : rainATTENcorrect](http://git.baltrad.eu/trac/wiki/cookbook/PolRainAttCorr:)

[Correction and quality characterization for attenuation in rain – RADVOL-QC: ATT](http://git.baltrad.eu/trac/wiki/cookbook/RADVOL-QC_ATT)

[Non-polarimetric integrated path attenuation estimate for melting layer at C-band: BBAND_ATTN_DIAG_SPOL_fmi](http://git.baltrad.eu/trac/wiki/cookbook/BBAND_PIA_EST_NP:)

## Quality characterization
[Calibration difference of two radars - CALID](http://git.baltrad.eu/trac/wiki/cookbook/CALID)

[Quality characterization due to distance to radar related effects – RADVOL-QC: BROAD](http://git.baltrad.eu/trac/wiki/cookbook/RADVOL-QC_BROAD)

[Total quality index (QI) for scans/volumes – QI_TOTAL](http://git.baltrad.eu/trac/wiki/cookbook/QIT)

## QPE
[Precipitation accumulation - ACRR](http://git.baltrad.eu/trac/wiki/cookbook/ACRR)

[Separation of convective and stratiform precipitation – CONVECTION](http://git.baltrad.eu/trac/wiki/cookbook/CONV)

[Combination of radar-based ground precipitation rate and raingauge network data – COMBINATION](http://git.baltrad.eu/trac/wiki/cookbook/ADJUSTMENT)

[Dynamical downscaling of ground precipitation rate – DOWNSCALE](http://git.baltrad.eu/trac/wiki/cookbook/DOWNSCALE)

[Networked VPR correction](http://git.baltrad.eu/trac/wiki/cookbook/Networked-VPR-correction)

[Dynamic R(Z) using single-polarisation data and ground observations – RZ_DYN_OBS](http://git.baltrad.eu/trac/wiki/cookbook/RZ_DYN_OBS)

## 2-D products
[Quality-based PPI product generation – Product2D: PPI](http://git.baltrad.eu/trac/wiki/cookbook/Product2D_PPI)

[Quality-based maximum of reflectivity (MAX) product generation – Product2D: MAX](http://git.baltrad.eu/trac/wiki/cookbook/Product2D_MAX)

[Quality-based echo top (ETOP) product generation – Product2D: ETOP](http://git.baltrad.eu/trac/wiki/cookbook/Product2D_ET)

[Quality-based vertically integrated liquid water (VIL) product generation – Product2D: VIL](http://git.baltrad.eu/trac/wiki/cookbook/Product2D_VIL)

## Compositing
[Quality-based compositing based on QI_TOTAL: QCOMP](http://git.baltrad.eu/trac/wiki/cookbook/QCOMP)

## Dealiasing and wind profiles
[wiki:cookbook/DEALIAS Dealiasing]

[wiki:cookbook/WRWP Wind profiles]

## Data visualization
[wiki:cookbook/BALTRAD-WMS BALTRAD-WMS]

## Miscellaneous
[wiki:cookbook/HEXED-QUANTITIES Representation of ODIM quantities as a compact string signature]

[[Image(cooks.jpg, 432px, nolink)]]
