# BALTRAD WMS

# Basic description

## Web Map Service
WMS (Web Map Service) is a standard protocol for serving georeferenced images over the Internet developed and published by the [Open Geospatial Consortium (OGC)](http://www.opengeospatial.org/). Images are generated on the server side. There are available a lot of software that has support for WMS. Examples include [OpenLayers](http://www.openlayers.org/) for Web browser usage and [Quantum GIS](http://www.qgis.org/) for desktop usage.

## Technical description
Software is independent of BALTRAD node. Only ODIM HDF5 or GeoTIFF files are needed for data input. Software consist of Python scripts based on Mapserver software. The main program is the visualization script which runs via Web server. There is also data converter script that converts from HDF5 files to GeoTIFF raster images. Installation instructions are included in the [GIT repository](http://git.baltrad.eu/git/?p=baltrad-wms.git).

# Metadata requirements
Projection must be defined in ODIM metadata. 

The software has also support for [FMI Open data](http://en.fmi.fi/open-data).

# Output.

## Output for WMS clients
Mapserver supports many different [output formats](http://mapserver.org/mapfile/outputformat.html) that can be requested via WMS client.  

## Georeferenced GeoTIFF images
Geotiff images can also be downloaded using the software. These images can be useful if are viewed or edited in a GIS software.

## KMZ files
Software also has capability to generate KMZ files that can be viewed in Google Earth. It is possible to create a KMZ file with either a single image or time series.

# Usage in [STUK](http://www.stuk.fi)
Software is integrated into the collaborative emergency management software "TIUKU" and dose-rate monitoring network web interface "USVA". The integration allows viewing of radar images together with dispersion model or measurement results. 


![TIUKU radar screenshot](/images/tiuku_radar_screenshot.png)
