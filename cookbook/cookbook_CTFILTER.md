# 1. Algorithm name
Identification and removal of residual non-precipitation echoes using the Meteosat Second Generation Cloud-Type product: CTFILTER

# 2. Basic description
## a) Physical basis of the algorithm
The EUMETSAT Nowcasting Satellite Application (SAF-NWC) generates cloud-type (CT) products every 15 minutes using full-disc data at roughly three km horizontal resolution. These products contain information on cloud-free areas. If a radar echo exists in an area void of clouds, according to the CT product, then such echoes are removed.

## b) Amount of validation performed so far
The method has been running operationally in Sweden in the NORDRAD2 system for over 10 years. The CT product itself has been validated in the SAF-NWC activities.

## c) References (names and contact information of all developers during the evolutionary history, scientific papers)
Michelson D., 2006: The Swedish weather radar production chain. Proc. ERAD 2006. GRAHI. Barcelona, Spain

based on

Michelson D. B. and Sunhede D., 2004: Spurious weather radar echo identification and removal using multisource temperature information. Meteorological Applications 11, 1-14

Dybbroe et al. 2005: NWCSAF AVHRR Cloud Detection and Analysis Using Dynamic Thresholds and Radiative Transfer Modelling. Part II. Tuning and Validation. _J. Appl. Meteor._ *44*. p. 55-71. (Addresses AVHRR, but is also relevant for MSG.)

# 3. ODIM metadata requirements for I/O
No non-mandatory metadata required.

# 4. Input data
## a) What kind of radar data (including the list of previous algorithms and quality flags applied)
Cartesian data: either IMAGE or COMP. No explicit QC or quality flags need to be applied or generated previously, although doing so is generally a good idea, as this method is only intended to be used at the end of a processing chain to remove residual non-precipitation echoes.

## b) Other data (optional and mandatory, applying “universally” agreed formats, geometry)
MSG CT product, available in HDF5 format operationally through EUMETCAST. This product is not corrected for parallax errors, but it can be using openly-available software.

# 5. Logical steps, using any of: text, flow charts, graphics, equations (or references to equations), conditional branches in “all possible cases”.
When the Cartesian image has been generated, it contains date and time attributes for the image's nominal time (also known as "product time", in contrast to "data time"). These attributes are used to try to find a matching MSG CT file in a directory specified by this application. It is up to you to subscribe to such files, put them in the directory, and maintain the directory. This application uses the official EUMETSAT file naming template, which can be changed if the file names change for whatever reason.

Because the MSG CT file arrives several minutes after product time, this application will try to find the file that matches the product time of the radar image. If it fails, then it will try to find the most recent file. The application can be configured to search backwards in time a user-defined number of time steps, although going more than 30 min back in time is probably not advisable.

The selected MSG CT file is read and navigated "as is"; this is possible because it contains a PROJ.4 string and projection coordinates for the corners.

Looping through the radar image, if the pixel value is not "nodata" or "undetect", navigate to the corresponding CT pixel. If this pixel belongs to any of the four cloud-free classes, then save the radar pixel value to a new quality-indicator field, and set the pixel in the radar quantity to "undetect".

Such classes are:

| Value | Class |
| 1 | Cloud-free land |
| 2 | Cloud-free sea |
| 3 | Snow/ice contaminated land |
| 4 | Snow/ice contaminated sea |

# 6. Output.
## a) Data type using ODIM notation where possible
Default=DBZH, but this is changeable as an argument.

## b) Added quality indicators
A new quality indicator field is added, with how/task=se.smhi.quality.ctfilter

# 7. Outline of a test concept exemplifying the algorithm, as a suggestion for checking that an implementation has been successful.
