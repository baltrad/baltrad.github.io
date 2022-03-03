# RELEASE NOTES

We are changing the install procedure to use pre-built RPMs and in the future Deb-packages as well **This is the recommended installation process**. If you aren't able to use the prebuilt packages we are offering here or if you have some other reason for not wanting to install from pre-built packages, then you will have to rely on the node-installer which is not actively maintained.

The latest official release is *3.1.0* and this is the one you will get if you install the RPM:s. The node installer also uses the 3.1.0 software but the dependencies are different.

## Releases
Latest RPM builds for [CentOS Stream 8/RedHat 8](https://rpm.baltrad.eu/CentOS/8/latest/). These RPMs are updated daily with newest features.

Official [CentOS Stream 8/RedHat 8 release](https://rpm.baltrad.eu/CentOS/8/3.1/). This is the official latest release with the release notes below.

## Installation of RPMs
The install procedure for installing the software on RedHat 8 / CentOS Stream 8 is quite simple and you are strongly encouraged to consider this approach.

The procedure for installing from RPM:s can be found [here](https://baltrad.github.io/install.html#in_rpm). You can either use the latest repo which is updated continously. Obviously, something might break using this repo
but if that occurs the correction is usually not far behind. We appreciate if you are able to use this repository, at least in a test-situation, since this will help us out finding issues fast.

If you on the other hand want to use a release that not is updated frequently you can instead use the 3.1 repo.

To install from the latest repo, refer to [https://baltrad.github.io/install.html#in_rpm](https://baltrad.github.io/install.html#in_rpm).

## To install using the node installer
See [Node-installer instructions](https://baltrad.github.io/install.html#in_prep_node_installer). Since the node-installer is going to be phased out in the future we are only keeping the installer alive but we are not improving it continously. If you experience any problems, there are a couple of work-arounds that you can read about in the NOTICE section of the previously mentioned page.

\verbatim

%> git clone https://github.com/baltrad/node-installer.git or

%> cd node-installer 

%> git checkout 3.1.0

\endverbatim

or if you already have a source repository that you have built from scratch, you can speed up the process by doing:

\verbatim
%> cd node-installer
\endverbatim

# If you haven't previously fetched software from github you will change repository to fetch software from by
\verbatim
%> sed -i -e "s#http://git.baltrad.eu/node-installer.git#https://github.com/baltrad/node-installer.git#g"
\endverbatim


\verbatim
%> git checkout master

%> git pull

%> git checkout 3.1.0
\endverbatim

## Release date 2022-03-02  --- 3.1.0
This is a major release with new features and bug corrections. 

*Please note that the database will be upgraded. This means that if the database upgrade is performed separately, post config upgrade database has to be called.*

The number of changes are wast and not all will be described in this description. Some interesting things is that we now only supports Python 3. Lazy loading has been introduced in rave to keep memory foot print down when processing large files. ODIM 2.3 has been added as well as most of the functionality to support ODIM 2.4. We have introduced a new modules for configuring the system when it has been installed from RPMs called baltrad-config.

The first version is the tag, the second version is the actual version number of the package of the RPM. For example, since hlhdf has version 0.9.1-8. The RPMs will be named: hlhdf-0.9.1-8.el8.x86_64.rpm, hlhdf-devel-0.9.1-8.el8.x86_64.rpm and so on.

Changes from 2.2.1 to 3.1.0

### High Level Interface to the HDF5 File Format (HLHDF)  - hlhdf-build-11 - 0.9.1-8
- Ticket #1: Add support to build with HDF5 >= 1.12
- Ticket 688: Enable python 3 support
- Ticket 704: Allow hlhdf to be built against hdf5 where hid_t is defined as long
- Ticket 706: HLHDF fails to read variable strings after upgrade to hdf5 1.10.1
- Ticket 736: Tests does not use python libraries for specified python binary
- Ticket 743: Create packaging support for RPM and DEB
- Ticket 768: Add possibility to choose python3 binary name
- Ticket 875: Add some more metadata loading features
- Ticket 884: Migrate pyhl to be compilable against python 3.8

### Radar Analysis and Visualization Environment (RAVE)  - rave-build-28 - 3.1.0-127
- Ticket #1: Scans rstart attribute not taken into account for height computations
- Ticket 14: Add support for proj >= 5
- Ticket 15: Support for ODIM 2.4 added. Strict mode added to rave. Also possiblity to read error_message to see what caused the problem saving a file
- Ticket 16: shiftData not applied when a file has been lazy loaded. Ticket 17: Add possibility to enforce old-style lon/lat coordinates when running legacy proj
- Ticket 619: VRADDH/V
- Ticket 631: Distance field for ACRR product is 'masked' where no rain is measured
- Ticket 633: Add attribute to site2d products
- Ticket 636: Chaining QC algorithms in odc_polarQC
- Ticket 639: When generating site2d images, CMT should contain area name.
- Ticket 642: Update odim_source.xml (new names for sevar and seosu)
- Ticket 646: Error in gra-adjustment of composites
- Ticket 648: Add functionality for merging polar scans and volumes
- Ticket 650: Quality field attributes
- Ticket 651: "Propagate" radar process in to products
- Ticket 655: Baltrad BRDR-field
- Ticket 656: height quality plugin
- Ticket 665: Update odim_source.xml with new name for sehud
- Ticket 672: rave-overshooting crash issue
- Ticket 674: Add support for removing malfunc scans in ApplyQc-plugin
- Ticket 676: Add functionality for choosing to only perform qc or if qc also should be applied
- Ticket 682: Dealiased radial velocities to separate sets of data
- Ticket 686: WRWP
- Ticket 688: Enable python 3 support for hlhdf
- Ticket 689: Add python 3 support.
- Ticket 693: detection range: enable processing of TH
- Ticket 697: Conversion from one set of gain+offset to another results in loss of data values
- Ticket 698: Truncation of data values could be replaced by rounding
- Ticket 699: Add possibility to control 'reprocess_qualityfields' for composite plugin via generate args
- Ticket 702: ODIM_H5 v.2.2. Converts ODIM v2.1 into ODIM v2.2 when reading files
- Ticket 711: scansun readout times and refraction
- Ticket 712: Add possibility to write cartesian products in CF-convention format.
- Ticket 721: scansun. Changed from localtime, localtime_r to gmtime, gmtime_r in function readOutTiming.
- Ticket 727: Volume with unsorted elangles gives faulty CAPPI/PCAPPI composites
- Ticket 731: Remove NR code in scansun
- Ticket 732: Add compression to CF Convention export
- Ticket 744: Create packaging support for RPM and DEB
- Ticket 747: Configurable log format for Rave
- Ticket 750: Support for additional interpolation methods in composites
- Ticket 751: Dealias improvements
- Ticket 754: Tiled compositing fails
- Ticket 764: Added support for an alternative output path (RAVESCANSUN_OUT) in rave_pgf_scansun_plugin.py. The path must be defined in rave_defines.py
- Ticket 767: Some corrupt files causes scansun to crash
- Ticket 769: Antenna gain and rxloss not correctly read in scansun for ODIM 2.1 files Ticket 771: Correct usage of astart in scansun Ticket 772: Allow scansun to work for files containing startazA but not stopazA
- Ticket 773: Add possibility to perform various matrix operations in RaveData2D
- Ticket 774: QiTotal mimimum with one field produces empty quality field
- Ticket 776: autogenerated proj names does not work in compositing
- Ticket 777: Modernized swedish radars should be added to odim_source.xml
- Ticket 778: Add melting_layer to rave database handling
- Ticket 780: scansun_main does not use full compiler flags
- Ticket 781: scansun memory pointer problem
- Ticket 783: scansun memory pointer problem
- Ticket 784: area_registry error
- Ticket 786: Update python files for python3
- Ticket 788: def.mk.in LDFLAGS does not use correct PROJ-flag
- Ticket 793: projection_registry uses invalid string join
- Ticket 794: Several programs has not been converted to Python3
- Ticket 798: Move QITOTAL_METHOD to rave_defines
- Ticket 800: Area extent should not be adjusted in x and y direction when reading writing
- Ticket 805: area_registry --list does not work after --add
- Ticket 808: Add new radar source finur
- Ticket 809: rave_tempfile creates tmp folder without full write access
- Ticket 813: A new peojection, laea15e60n, added to projection_registry.xml
- Ticket 816: Some changes to the vertical profile part of rave to be able to accomodate some new parameters and attributes
- Ticket 819: Update python objects with documentation
- Ticket 821: Support possibility that startazA / stopazA resides in parameters howgroup
- Ticket 831: Add how subgroups as part of ODIM H5 2.3 support
- Ticket 832: Add prodname as part of ODIM H5 2.3 support
- Ticket 833: Add possibility to store files in ODIM H5 2.2 and 2.3 format. Added support for zscale/zstart and zsize for cartesian volumes
- Ticket 834: Add ProductType EBASE as part of ODIM H5 2.3
- Ticket 835: Add support for astart/startazA/stopazA when calculating ray indexes.
- Ticket 841: tiled_compositing and preprocess qc doesn't work
- Ticket 850: Combine tiles might cause an empty lines between various tiles.
- Ticket 852: Increase hexquant/odim_quantities.xml to allow for 128 bits and add new ODIM 2.3 quantities
- Ticket 857: Add H5rad 2.3 to rave_defines.py
- Ticket 859: Change WMO code for nosmn
- Ticket 860: Change so that RAVESCANSUN_OUT is configurable in rave_defines.py
- Ticket 863: Add configurable RAVEIO version when writing files.
- Ticket 870: Improve performance when using rotation correction in the azimuthal calculations
- Ticket 874: Add Lazy Loading to RaveIO
- Ticket 876: Scansun crashes on erroneous H5-files
- Ticket 885: Add ray-shifting for scans and also identification of northmost ray
- Ticket 886: Avoid unessecary loading when fetching files from bdb
- Ticket 893: Add filtering to remove all quantities but wanted
- Ticket 896: Remove vpr module

### The Baltrad exchange and scheduling tools (BEAST)  - beast-build-18 - 3.1.0-54
- Ticket 627: Check alive
- Ticket 629: Upload test for distribution rules always returns OK
- Ticket 637: Update of site2d route
- Ticket 641: Supervisor bdb.object.status does not search according to UTC
- Ticket 644: Error for some hexcodes
- Ticket 653: Enable sorting of routes in GUI.
- Ticket 658: Deficiency in ACRR plugin
- Ticket 659: GRA: Add possibility to isolate specific composites for generation
- Ticket 663: ACRR gets wrong accumulation time when node load is excessive
- Ticket 668: Compositing route filter possibility
- Ticket 670: Filtering in ACRR-rule sometimes cause rule execution to crash
- Ticket 679: Add option to choose between analyse only and analyse and apply for composite, volume and site2d
- Ticket 685: Filter possibility needed in Google Maps route and in WRWP route
- Ticket 700: Add possibility in compositing rules to select whether or not quality controls shall be reprocessed
- Ticket 701: Improve bdb.object.status supervisor query
- Ticket 703: Add possibility to select what fields that should be included in the wrwp product
- Ticket 714: Update postgres jdbc version to support prepareThreshold
- Ticket 717: Max-age-limit in composite rules
- Ticket 758: Use of temporary file during FTP file upload
- Ticket 811: Add support for keyhandling / security handling and exchange
- Ticket 824: Add support for maxelevationangle, maxvelocitythreshold, minsamplesizereflectivity, minsamplesizewind to wrwp
- Ticket 826: Add NZ to available fields. Change dbzh and dbzh_dev to DBZH and DBZH_dev.
- Ticket 848: If same redirect address already stored for beast_authorization file is not delivered
- Ticket 849: Update beast & dex to propagate post_file redirect to dex for dex_users storage
- Ticket 853: Add support for 128 different quantities in hexquant namer
- Ticket 865: Add more logging to be able to follow what happens to a file that is injected.
- Ticket 867: Add distribution name creator for mapping between double and string
- Ticket 868: Update with new postgresql driver
- Ticket 869: PooledFileRequestPublisher creates new factory each time a new thread is created
- Ticket 891: Added handling of groovy script routes
- Ticket 894: Add possibility to enable/disable admin mailer

### Baltrad Config Tool (baltrad-config)  - baltrad-config-build-3 - 3.1.0-37
New module for configuring a baltrad node

### Baltrad Database (baltrad-db)  - baltrad-db-build-13 - 3.1.0-45
- Ticket #11: Allow for WSGIServer from both cherrypy and cheroot
- Ticket 664: Not possible to create two products only differing on area ID name
- Ticket 666: Decrease execution time of composite rules in Beast in loaded situations
- Ticket 673: Migrate from DB to FS storage
- Ticket 692: Syslog output from bdb-server
- Ticket 717: Max-age-limit in composite rules
- Ticket 718: Update to use newer version of virtualenv
- Ticket 733: Fixed some more encoding things
- Ticket 748: Handling of incomplete /what/source key-value pairs
- Ticket 749: Handling non-unique identifiers in /what/source
- Ticket 766: Merge attribute_values and nodes tables into one
- Ticket 795: baltrad-bdb-client --help causes exception
- Ticket 838: Add strategy storage so that it is possible to configure which storage variant that should be used
- Ticket 851: Add log information for debug purpose as well as performance monitoring
- Ticket 865: Add more logging to be able to follow what happens to a file that is injected.
- Ticket 866: CacheDirStorage should not fail when finding non-uuid filenames, they should be ignored.
- Ticket 878: Change metadata storage when inserting files.
- Ticket 883: sqla.pool_size not used when creating backend
- Ticket 887: Change to use WatchedFileHandler for file logging in bdbserver
- Ticket 888: Update bdb to use werkzeug 1.0.1

### Baltrad Data Exchange (baltrad-dex)  - baltrad-dex-build-11 - 3.1.0-78
- Ticket 465: Added try/catch around factory method
- Ticket 627: Check alive
- Ticket 629: Upload test for distribution rules always returns OK
- Ticket 637: Update of site2d route
- Ticket 653: Enable sorting of routes in GUI
- Ticket 654: Add possiblity to duplicate Site2dRules
- Ticket 658: Deficiency in ACRR plugin
- Ticket 659: GRA: Add possibility to isolate specific composites for generation
- Ticket 660: Volume route: If opening a volume route with a null filter route itself fails.
- Ticket 661: Site2D route: If opening a Site2D route with a null filter route itself fails.
- Ticket 668: Compositing route filter possibility
- Ticket 679: Add option to choose between analyse only and analyse and apply for composite, volume and site2d
- Ticket 685: Filter possibility needed in Google Maps route and in WRWP route
- Ticket 694: Transmitting side drops data without log information
- Ticket 700: Add possibility in compositing rules to select whether or not quality controls shall be reprocessed
- Ticket 701: Improve bdb.object.status supervisor query
- Ticket 703: Add possibility to select what fields that should be included in the wrwp product
- Ticket 714: Update postgres jdbc version to support prepareThreshold
- Ticket 717: Max-age-limit in composite rules
- Ticket 765: Add individual peer-check to peer.status reporter
- Ticket 792: tld files are not allowed to reside under tags
- Ticket 812: Change key exchange / authorization / file sending to the one provided by beast
- Ticket 825: Add support for maxelevationangle, maxvelocitythreshold, minsamplesizereflectivity, minsamplesizewind to wrwp
- Ticket 826: Add NZ to available fields. Change dbzh and dbzh_dev to DBZH and DBZH_dev.
- Ticket 839: Use bdb strategy storage for selecting correct storage
- Ticket 847: web.xml order of filter causes login problems
- Ticket 849: Update beast & dex to propagate post_file redirect to dex for dex_users storage
- Ticket 865: Add more logging to be able to follow what happens to a file that is injected.
- Ticket 867: Add distribution name creator for mapping between double and string
- Ticket 868: Update with HikariCP as DB connection pool
- Ticket 873: Maintenance of dex_messages and dex_delivery_registry causes performance issues
- Ticket 877: Stacktrace when trying to show details about a file containing 16bit data
- Ticket 880: Add configuration items in dex.fc.properties for setting up client bdb properly
- Ticket 881: Add possibility to configure db.pool.size and blt manager executor size
- Ticket 891: Add support for GUI-less configuration of rules, schedules, adaptors and detectors
- Ticket 894: Add possibility to enable/disable admin mailer
- Ticket 895: When updating node settings the beast local user should also be updated

### Baltrad Tomcat Node instance (baltrad-node-tomcat)  - N/A - 8.5.56-10
New module that is available for prebuilt packages. Is a customized tomcat-server.

### Baltrad Polarimetric Processing Chain (baltrad-ppc)  - baltrad-ppc-build-13 - 3.1.0-76
New module for processing

### Baltrad Viewer (baltrad-viewer)  - baltrad-viewer-build-1 - 3.1.0-6
Old google maps plugin that has a more suitable name since open street map support has been added.

- Ticket 734: Add python3 support
- Ticket 755: Add support for OpenStreetMap-based maps
- Ticket 757: Full screen support in leaflet-based map

### Baltrad Weather Radar Wind and Reflectivity Profiles (baltrad-wrwp)  - baltrad-wrwp-build-15 - 3.1.0-76
- Ticket #1: wrwp_main always writes log file to default folder
- Ticket 686: WRWP
- Ticket 702: ODIM_H5 v.2.2. Converts ODIM v2.1 into ODIM v2.2 when reading files
- Ticket 703: Add possibility to select what fields that should be included in the wrwp product
- Ticket 720: WRWP, adjustement to be able to cope with volumes only having scans with lower elangles than set in the GUI route
- Ticket 725: add license statement
- Ticket 726: Enable standalone binary
- Ticket 728: Gain & offset not used for products.
- Ticket 729:WRWP
- Ticket 738: Add python3 support
- Ticket 741: PI
- Ticket 752: Add support for quantities to wrwp binary
- Ticket 816: Some changes to the vertical profile part of rave to be able to accomodate some new parameters and attributes
- Ticket 817: Some parameters added (EMAX, FF_MAX and NZ). The command-line c-code had been replaced with a python-version which permits converting to ver2.1. Two extra how-attributes have been added (task, angles)
- Ticket 823: Add support for maxelevationangle, maxvelocitythreshold, minsamplesizereflectivity, minsamplesizewind in pgf plugin
- Ticket 827: Update pydocumentation for wrwp
- Ticket 864: Add configurable RAVEIO version when writing files.

### Baltrad BUFR module (bbufr)  - bbufr-build-6 - 3.1.0-3
- Ticket 745: Create packaging support for RPM and DEB

### Baltrad Beam Blockage module (beamb)  - beamb-build-14 - 3.1.0-65
- Ticket 672: rave-overshooting crash issue
- Ticket 678: Add functionality for choosing to only perform qc or if qc also should be applied
- Ticket 723: add license statement
- Ticket 737: Add python3 support
- Ticket 779: Correction of some issues, see trac for more info
- Ticket 791: Need to fix shebang on beamb script

### Baltrad ROPO module (bropo)  - bropo-build-22 - 3.1.0-75
- Ticket 1: Encoding problems when processing file that doesn't contain NOD in what/source
- Ticket #3: Compilation problems on gcc >= 9
- Ticket 677: Add functionality for choosing to only perform qc or if qc also should be applied
- Ticket 684: "Analyze only" with bropo creates invalid DBZH datafield
- Ticket 724: add license statement
- Ticket 735: Add python3 support
- Ticket 746: Create packaging support for RPM and DEB. Fixed DESTDIR
- Ticket 782: Changed so that classification is returned as 8-bit uchar
- Ticket 787: Handle format-security compile error
- Ticket 789: Erroneous usage of gain/offset when processing data != UCHAR/CHAR
- Ticket 790: Need to fix shebang on ropo script

## Release date: 2016-08-26

This is minor release containing both new features and bug corrections.

*Please note that the database will be upgraded. This means that if the database upgrade is performed separately, post config upgrade database has to be called.*

For more information on changes and improvements, please refer to the ticket list below.

Changes from 2.2 to 2.2.1 

node-installer:
- Ticket 549: Https communication problem between JDK 1.6 and Tomcat 7
- Ticket 572: Increase cache size to 5000

HLHDF:
- Ticket 603: Add possibility to read variable length strings

BALTRAD-DB:
- Ticket 551: Frequent exception in java client api
- Ticket 557: Feature request: Wildcard in filter strings
- Ticket 562: Add possibility to get all metadata from a file without storing it.
- Ticket 571: Add debug logs to help troubleshooting of file storage functionality
- Ticket 589: Baltrad-db log does not contain timestamps
- Ticket 601: Upgrade to use later version of setuptools
- Ticket 604: Database exception when two equal files input at the same time
- Ticket 617: Running vacuumlo on database removes los that are not actually orphaned
- Ticket 625: Problem installing with newer version of setuptools

BEAST:
- Ticket 27: allow testing the destination of a distribution rule
- Ticket 546: scponly does not work as distribution route
- Ticket 494: Make sure that jobs are processed in prioritized order
- Ticket 557: Feature request: Wildcard in filter strings
- Ticket 575: Scan PPI does not use scans closest to nominal time
- Ticket 579: Timeout to start at nominal time
- Ticket 586: ConcurrentModificationException when editing route
- Ticket 591: Improve observability on route executions
- Ticket 595: Possibility to filter directly in the volume route
- Ticket 602: Add protection against parallel distributions to same target
- Ticket 607: Add possibility to create time intervals in the distribution routes
- Ticket 608: Concurrency issue for FTP distributions

BALTRAD-DEX:
- Ticket 27: allow testing the destination of a distribution rule
- Ticket 28: allow testing the filter of a distribution rule
- Ticket 465: succesful authentication but failed authorization gives NullPointerException
- Ticket 521: Ensure that correct node address is set in settings
- Ticket 543: Can not handle HTTP 301 Moved Permantently
- Ticket 545: Order of quality controls in volume route
- Ticket 546: scponly does not work as distribution route
- Ticket 552: DEX login via Firefox: Session expired
- Ticket 553: This webpage has a redirect loop
- Ticket 557: Feature request: Wildcard in filter strings
- Ticket 565: GUI exception
- Ticket 566: GUI enhancement 2
- Ticket 569: Add protection against routes without recipient
- Ticket 570: Multiple selected adaptors if similar names
- Ticket 572: Increase cache size to 5000
- Ticket 579: Timeout to start at nominal time
- Ticket 582: Clear/reset button on the 'Browse files' page does not clear form
- Ticket 583: Route name handling deficiency
- Ticket 592: Distribution route Test distribution has secret limitation
- Ticket 593: redirectedAddress passed in the user json object
- Ticket 594: Add more descriptive error handling in DataSourceListServlet
- Ticket 595: Possibility to filter directly in the volume route.
- Ticket 608: Concurrency issue for FTP distributions
- Ticket 609: Volume route bug

RAVE:
- Ticket 494: Make sure that jobs are processed in prioritized order
- Ticket 539: Replace start/stopelA with elangles in scansun
- Ticket 541: Quality chains example in the config directory is erroneous
- Ticket 542: Quality chain field names
- Ticket 547: wrong zr_b value for acrr plugin
- Ticket 548: rave_pgf crashes randomly
- Ticket 554: Accumulation period needed as primary key in Rave DB
- Ticket 556: Generation of volumes in rave_pgf_volume_plugin.py fails
- Ticket 558: Messages in the rave-log
- Ticket 561: FM12 importer sometimes adjusts pressure incorrectly
- Ticket 564: Migrate files not installed
- Ticket 568: acrr quality field gets 1 as offset instead of 0
- Ticket 573: Nodata missing if to few files in ACRR
- Ticket 574: rave_IO DeprecationWarning
- Ticket 576: Memory usage constantly grows when running fm12_importer
- Ticket 577: Kill command to running FM12 daemon has no effect
- Ticket 578: Allow FM12-importer to only trigger on certain suffix:es
- Ticket 584: Add PGF plugin for adding QCs to PVOL
- Ticket 585: Add VPR correction
- Ticket 587: Debug log on files used in composite generation
- Ticket 588: def.mk.in missing reference to libravetnc.so
- Ticket 590: Change plc in odim_source.xml
- Ticket 597: migrate folder conflicts with sqlalchemy-migrate
- Ticket 598: Add possibility to fetch most recently generated gra coefficients since date/time
- Ticket 599: GRA coefficient generation should use fallbacks
- Ticket 600: ACRR & composite generation should use climatological gra coefficients if none exists in database
- Ticket 606: If db connection reset at server side, the gra coefficient generation might be postponed a long time
- Ticket 610: Add possiblity to delete stations and observations in rave_dom_db
- Ticket 611: Change NOD in odim_source.xml
- Ticket 614: ACRR & composite generation should use climatological gra coefficients if none exists in database
- Ticket 615: Type still set as primary key in dom-object
- Ticket 618: Error in compositing when applying gra.
- Ticket 620: Add VRADH/V to dealias.c
- Ticket 621: ODIM_H5 violation (LT)
- Ticket 622: Change quantity index in odim_quantities.xml
- Ticket 623: Add possibility to specify elevation threshold to dealias
- Ticket 624: Make a PolarScanParamCore object clonable in Python
- Ticket 626: compositing does not handle if prodpar already is float/int

RAVE-GMAP:
- No changes

BROPO:
- Ticket 544: Ignore failed bropo.pth installation

BBUFR:
- No changes

BEAMB:
- No changes

BWRWP:
- No changes


## Release date: 2015-12-30

This is a major release. Several bug fixes have been performed. We have upgraded so that the node can run with java 1.8 and other miscellaneous fixes and enhancements.

*Please note that the database will be upgraded. This means that if the database upgrade is performed separately, post config upgrade database has to be called.*

For more information on changes and improvements, please refer to the ticket list below.

Happy New Year from the BALTRAD team!

Changes from 2.1-ec1 to 2.2

node-installer:
* Ticket 478: Upgrade system to install tomcat 7
* Ticket 479: Add support for java 1.8 to tomcat options
* Ticket 480: Node-installer does not reckognize openjdk 1.8 during jdk validation
* Ticket 486: Can not find java version with openjdk-7 and ubuntu 15.04
* Ticket 487: Upgrade pycurl to 7.19.5.3
* Ticket 488: Upgrade pip to 7.1.2
* Ticket 490: Add possibility to retrieve all configuration settings
* Ticket 495: bltnode --all status does not show tomcat node as started even though it is started
* Ticket 496: PIP 7.1.2 did not work with python 2.6 on Redhat 7
* Ticket 529: Add so that rave.pgf.uri added to post_config properties
* Ticket 530: baltrad_post_config sets erroneous bdb_storage root
* Ticket 531: DEX servlet-context should use bdb.xml instead of instantiating beans.
* Ticket 536: Add possibility to retrieve quality controls from PGF

HLHDF:
* Ticket 347: Handle too short STRSIZE
* Ticket 473: When writing file, some times it doesn't get flushed directly

BALTRAD-DB:
* Ticket 506: Can not inject data If source contains ORG and one of WMO, NOD, RAD or PLC
* Ticket 519: Add source information so that it is possible to know what ORG a source belongs to
* Ticket 520: Add possibility to retrieve information about one single source
* Ticket 527: Node start issues due to existing pid-file

BEAST:
* Ticket 447: Add possibility to choose elevations to include in a volume
* Ticket 472: Add applygra to configuration details for ACRR route.
* Ticket 476: Upgrade system to use spring framework 4
* Ticket 492: Add SFTP support to distribution route
* Ticket 509: Site2D generates more files than ordered in the route definition
* Ticket 522: Add possibility to retrieve all available areas from the PGFs
* Ticket 534: Add possibility to determine what quantity to use in the composite generator
* Ticket 535: Empty qitotal argument passed to the pgf
* Ticket 536: Add possibility to retrieve quality controls from PGF
* Ticket 538: Add possibility to retrieve all available pcs definitions from the PGFs

BALTRAD-DEX:
* Ticket 447: Add possibility to choose elevations to include in a volume
* Ticket 472: Add applygra to configuration details for ACRR route.
* Ticket 474: Route distribution filter does not show in some cases
* Ticket 476: Upgrade system to use spring framework 4
* Ticket 477: When viewing composite file details an exception is thrown
* Ticket 514: Improved user-friendliness when adding radarsites
* Ticket 522: Add possibility to retrieve all available areas from the PGFs
* Ticket 531: DEX servlet-context should use bdb.xml instead of instantiating beans.
* Ticket 534: Add possibility to determine what quantity to use in the composite generator
* Ticket 536: Add possibility to retrieve quality controls from PGF
* Ticket 537: Add possibility to set order of anomaly detectors for volume rule
* Ticket 538: Add possibility to retrieve all available pcs definitions from the PGFs

RAVE:
* Ticket 344: rave_scansun_quality_plugin.py
* Ticket 399: Support ODIM 2.2
* Ticket 419: add zdiff quality
* Ticket 442: grapoint not removed properly
* Ticket 443: Add possibility to specify ranges when deleting grapoints
* Ticket 444: Add interval matching to obsmatcher
* Ticket 445: Not possible to dump processed volume in odc_toolbox
* Ticket 446: Add grib reading capabilities
* Ticket 448: tiled_compositing can not handle if there are tiles that gets 0 files
* Ticket 449: odc_toolbox does not toggle between compositing and QC on polar data
* Ticket 451: Can not build system without expat enabled
* Ticket 456: nodata, undetect, gain and offset not set when using tiled_compositing
* Ticket 457: Add script for batching ACRR generation
* Ticket 458: create_acrr_composites does not set start/end datetime interval
* Ticket 459: hex strings for representing quantities
* Ticket 460: Update scansun
* Ticket 461: Add gra coefficient usage in create_acrr_composites script
* Ticket 462: Toolbox does not support USHORT in data
* Ticket 463: Toolbox does not support UINT in data
* Ticket 464: Toolbox does not support ULONG in data
* Ticket 467: GRA correction error in algorithm
* Ticket 469: Missing H5Rad constants in _rave
* Ticket 470: GRA should add coefficients to how/task_args
* Ticket 471: Add script for fetching files from bdb
* Ticket 475: VerticalProfiles should be able to contain other quantities than specified in ODIM
* Ticket 481: Add hasAttribute to pycartesian
* Ticket 482: ACRR sets /dataset1//what/product to origin product instead of RR
* Ticket 483: scansun crashes when reflectivity is missing
* Ticket 484: Add fipet to odim_sources.xml
* Ticket 485: odim_source enhancements
* Ticket 489: rename n2b to odim_injector
* Ticket 498: n2b crashes if a file not can be removed
* Ticket 500: pcsid, xscale and yscale missing in registry definitions for site2d
* Ticket 501: pyarea can not handle if xscale and yscale are integer
* Ticket 502: Single Site 2D area names should identify radar source
* Ticket 503: VerticalProfile does not provide python api for add/get of attributes
* Ticket 507: Badly formatted ODIM files should result in IOError
* Ticket 511: fm12_importer --conf will not start
* Ticket 513: fikes has got wrong wmo-number in odim_sources.
* Ticket 516: bin/wmo_station does not print help when providing erroneous arguments
* Ticket 518: FM12 parser should handle several blocks
* Ticket 522: Add possibility to retrieve all available areas from the PGFs
* Ticket 528: Compositing does not apply gra
* Ticket 532: ACRR pgf plugin should set startdate/time in the past
* Ticket 533: remove_nul in rave_IO expects all string to have nullterm
* Ticket 536: Add possibility to retrieve quality controls from PGF
* Ticket 538: Add possibility to retrieve all available pcs definitions from the PGFs

RAVE-GMAP:
* Ticket 491: mktime error in list_data.php

BROPO:
* No changes

BBUFR:
* Ticket 399: Support ODIM 2.2
* Ticket 468: Remove debug printouts

BEAMB:
* Ticket 515: add North American tiles

BWRWP:
* Ticket 504: How attributes should be copied from volume to profile

## Release date: 2015-01-23

Emergency correction. Corrects a problem that occurs when the python 2.6 is installed. See Release 2.1 for proper release note.

Changes from 2.1 to 2.1-ec1 

node-installer:
   Ticket 441: dexinstaller fails when python 2.6 is used by installer

Release date: 2014-12-30

This is a major release. Major changes are that the DEX exchange protocol can handle ghost subscriptions provided that the nodes it communicates with are also of 2.1 version. Otherwise, it will fall back to the 2.0 protocol. In order to get handle ghost subscriptions, new subscriptions must be made so that the required information is exchanged. However, to get a smooth transition we have enabled the 2.0 protocol as default in this release and when all sites has been upgraded we will create a maintenance release that activates the 2.1 protocol since it will be backward compatible with 2.0. Besides the updated DEX exchange protocol, RAVE has been enhanced with gauge adjustment and first versions of the quality-based compositing and filtering of residual non-precipitation echoes using the Meteosat Second Generation cloud-type product available operationally through EUMETCAST. We have added a couple of more product generators, site2D which will create a cartesian product from a single radar source with an area that is determined on the fly. Then we have added scan sun which is used for creating calibration information for the site.

The distribution rules has got a number of improvements when it comes to creating file names from the metadata, please refer to the documentation for more information regarding this.

Besides all new and upgraded features, we have put a lot of effort into improving performance and reliability of the system. We have added the possibility to use multiprocessing when generating composites. This also affects how the quality controls are performed.

For more information on changes and improvements, please refer to the ticket list below.

*NOTE! When upgrading the release it might take a long time (several hours) to update the database tables since the datatype on some IDs has been changed for bdb_nodes and bdb_attribute_values. If you want to speed up the process, you might want to consider doing some cleanup of these tables first.*

Happy New Year from the BALTRAD team!

Changes from 2.0 to 2.1 

node-installer:
* Ticket 168: INSTALL.centos61
* Ticket 257: Override default Tomcat memory settings
* Ticket 258: Rotate catalina.out
* Ticket 270: apply file protection on files containing passwords etc
* Ticket 341: beamb build 53: make clean_cache
* Ticket 353: start and stop rave_pgf_logger
* Ticket 359: Add configure option for RAVE LOG Port
* Ticket 366: Route for site2D product generation
* Ticket 392: Update documentation
* Ticket 420: bbufr compiler flag error
* Ticket 428: freetype/fterrors.h not found when building libImaging
* Ticket 432: Documentation not installed for dex
* Ticket 433: Remove references to --with-bdbfs
* Ticket 440: Remove printouts from unpacking the dex jar in the deploy phase

HLHDF:
* No changes

BALTRAD-DB:
* Ticket 195: In field Name template not works {/_bdb/source_name}
* Ticket 335: Distribution route in beast stops working after 2-3 days
* Ticket 371: Limit reached on autogenerated ids
* Ticket 376: Add possibility to count number of files stored in database
* Ticket 378: Add possibility to remove several files by count at once
* Ticket 379: Add removeFilesByAge
* Ticket 382: Change rest database client to be configurable to use more than 2 connections
* Ticket 416: FileCache might become inconsistant

BEAST:
* Ticket 322: Add rule for GRA coefficient generation
* Ticket 325: Message manager manage should not try to handle new messages after shutdown
* Ticket 357: Add gra-attributes to CompositeRule and manager
* Ticket 362: Improve performance on loading filters from CoreFilterManager
* Ticket 365: Option to CTFilter when generating Cartesian products
* Ticket 366: Route for site2D product generation
* Ticket 370: Groovy script for scansun
* Ticket 377: exclude scans where how/malfunc=True
* Ticket 380: Beast should use removeFilesByCount and removeFilesByAge for cleanup rules
* Ticket 395: Hex strings to represent quantities in distribution route
* Ticket 397: Add QCOMP to composite route
* Ticket 421: Add formatting possibilities for what/date and what/time
* Ticket 427: Add tolower, toupper and substring possibilities to distribution rules
* Ticket 430: Add trim/ltrim/rtrim to distribution rule namer
* Ticket 436: SCPFileUploadHandler problems for distribution routes, Ticket 437: SCP upload slow in distribution rule
* Ticket 438: Intermittent scp upload problem during high load
* Ticket 439: FormattableDateTimeNameCreator can not handle concurrent calls properly

BALTRAD-DEX:
* Ticket 189: fix ghost subscriptions
* Ticket 258: Rotate catalina.out
* Ticket 273: Node settings - time zone: enhance or remove
* Ticket 323: Add rule for GRA coefficient generation
* Ticket 324: swap odim_source.xml
* Ticket 326: Enhance node status page so it loads faster and contains additional information
* Ticket 334: Add so that dex nodes can support multiple protocol versions
* Ticket 350: Add possibility to choose order of the quality plugins in the GUI
* Ticket 358: Add attributes for gra correction to the composite route
* Ticket 364: Add route name to the schedule overview list
* Ticket 365: Option to CTFilter when generating Cartesian products
* Ticket 366: Route for site2D product generation
* Ticket 367: Schedule handling for jobs are behaving strange
* Ticket 370: Add rule for SCANSUN production
* Ticket 377: exclude scans where how/malfunc=True
* Ticket 384: Increate restful connections to baltrad-db
* Ticket 393: Browsing more than 1000 pages of system messages difficult
* Ticket 394: Not possible to edit or insert date in text boxes in browse system messages
* Ticket 395: Hex strings to represent quantities in distribution route
* Ticket 397: Add QCOMP to composite route
* Ticket 421: Add formatting possibilities for what/date and what/time
* Ticket 431: Not possible to generate javadoc without doxygen installed
* Ticket 438: Intermittent scp upload problem during high load

RAVE:
* Ticket 220: minor odds and ends
* Ticket 265: n2b janitor seems to ignore file
* Ticket 266: n2b only works properly with default values
* Ticket 328: add single-site Cartesian product generator
* Ticket 331: Revert quality fields
* Ticket 337: PGF registry entry incorrent for composite generation
* Ticket 338: Acrr plugin does not support reading of COMP products
* Ticket 339: Clarify PROJ.4 string for Google Maps
* Ticket 340: Add QI total algorithm to rave
* Ticket 342: more robust n2b
* Ticket 343: update RADVOL
* Ticket 345: Support ODIM 2.2
* Ticket 346: Add QCOMP to composite generation
* Ticket 348: Add possibility to apply GRA coefficients to cartesian parameters
* Ticket 349: Implement CTFILTER
* Ticket 351: rave dom db runs out of connections
* Ticket 352: fm12_importer fails to import certain files
* Ticket 354: resiliant job queue
* Ticket 355: Add GRA usage on composites in rave_pgf_composite_plugin
* Ticket 356: fm12_importer can not identify when monitored directory get file renames
* Ticket 360: handle RADVOL algorithm-specific parameters in memory
* Ticket 363: poo not used properly when creating composites
* Ticket 366: Route for site2D product generation
* Ticket 368: grapoint and gra coefficients queried incorrect
* Ticket 369: MAX composite - carrying over quality
* Ticket 372: log server - open connections
* Ticket 373: consistent log levels in PGF
* Ticket 374: move CT-filter config to rave_defines
* Ticket 375: add MSG CT file name to product
* Ticket 377: exclude scans where how/malfunc=True
* Ticket 381: Add support for bdb in scansun plugin
* Ticket 383: Migrate logging to syslog
* Ticket 385: qitotal selection don't work when product type = MAX
* Ticket 386: qi-total compositing does not work with MAX
* Ticket 387: Consolidate compositing scripts
* Ticket 388: Gra observations are not found
* Ticket 389: Consistent root tag in PGF_quality_registry lookup
* Ticket 390: Remove sys.exit from rave_ql
* Ticket 391: Update odim_source.xml
* Ticket 396: Update rave_doxygen.cfg
* Ticket 397: Add QCOMP to composite route
* Ticket 403: add hasAttribute to PolarScan and PolarScanParam
* Ticket 404: Rave have some configure problems in later versions of ubuntu
* Ticket 405: add Russian entries to odim_source.xml
* Ticket 406: Add fallback date and time management to compositing
* Ticket 407: DB issues
* Ticket 408: add dealiasing quality plugin
* Ticket 409: delete tempfiles
* Ticket 410: add ability to generate 'tiled' composites
* Ticket 411: Quality plugin for processing chains
* Ticket 413: job queue initiation
* Ticket 414: Add possibility to clone volumes and scans
* Ticket 415: Move tempfiles to /dev/shm
* Ticket 417: Not possible to both have multiprocessing on PGF level and tiling level
* Ticket 418: modules need installing
* Ticket 419: add zdiff quality (partly implemented)
* Ticket 422: dealias.c does not add how/task to dealiased field
* Ticket 423: Add possibility for quality plugins to identify if reprocessing should be done or not
* Ticket 426: Add possibility to run the qc steps before running the tiles
* Ticket 429: Add Kesälahti radar to odim source
* Ticket 434: tiled_compositing creates composite with objectType=IMAGE
* Ticket 435: fm12 importer crashed due to missing file

RAVE-GMAP:
* Ticket 176: cannot initiate properly with no images
* Ticket 194: clear unused background field
* Ticket 327: length of array in Apache log and forward button to switch to next time
* Ticket 361: More general handling of quantity and QC layer settings
* Ticket 402: Enable image generation from single-site IMAGE objects

BROPO:
* Ticket 330: Add gain and offset to quality indicators
* Ticket 411: Quality plugin for processing chains
* Ticket 424: Add possibility for quality plugins to identify if reprocessing should be done or not

BBUFR:
* No changes

BEAMB:
* Ticket 329: Revert quality field
* Ticket 333: add default restore to quality plugin
* Ticket 411: Quality plugin for processing chains
* Ticket 425: Add possibility for quality plugins to identify if reprocessing should be done or not

BWRWP:
* Ticket 400: remove logger from PGF plugin


## Release date: 2013-12-30

This is a major release that is part of the BALTRAD+ project. If upgrading from a node earlier than version 1.6, it is essential that you follow the instructions described in the "Release 1.6" and "Release 1.7" tag.  Most of the changes that have occurred since 1.0 can be found in the different release tags below, but here are some headlines of changes since 1.0:

* node-installer can install individual parts of the system

* node-installer provides the ability to perform post-installation steps in order to configure and add features to the system after an installation

* baltrad-db is able to manage more than one request at a time (configurable by setting baltrad.bdb.server.type=cherrypy in bltnode.properties)

* BaltradDex has received more stable and reliable data exchange and, consequently, the communication protocol has been completely changed. This means that there is no possibility for a node with version 1.7 or lower to communicate with this release.

* BaltradDex gui has been changed to provide a more easy-to-use user interaction. It also provides https support for parts of the GUI.

* BaltradDex provides a supervisor feature that can be queried from an external monitoring system (see documentation).

* RAVE has received a number of new product generators, like PMAX, ACRR, RADVOL, Cartesian compositing and more. There is also a daemon for importing WMO FM-12 formatted SYNOP files to a local database.

We will follow up with more information about the plans and coming features for release 3.0.

Happy New Year!

And as usual, if you experience problems or need help, write a ticket or send an email to support @ baltrad.eu.

Release date: 2013-11-29

This is a major (beta) release. Rave has got a gisc fm12 synop importer that can be run as a daemon monitoring a folder. Some critical bugs has been corrected as well.

Changes from 1.9 to 2.0-beta1.

node-installer:

* Ticket 311: Add rave.db.uri to bltnode.properties

BALTRAD-DEX:

* Ticket 271: Subscribing to some nodes shows error
* Ticket 314: Modification of data source access rights breaks existing subscriptions
* Ticket 315: Data sources with underscores produce errors when trying to subscribe

RAVE:

* Ticket 310: Add gisc fm12 synop import
* Ticket 316: SURF
* Ticket 317: Polar navigator returns int values to python for equatorradius, dndh and lat0

Release date: 2013-11-01

This is a major release containing bugfixes and some added functionality.

Changes from 1.9-beta1-ec1 to 1.9

node-installer:

* Ticket 181: don't overwrite newer rave_pgf_quality_registry.xml

BALTRAD-DB:

* Ticket 238: Request: resetting bdb-server after an uncontrolled shutdown

BALTRAD-DEX:

* Ticket 305: Handle ArithmeticException in NodeStatusController
* Ticket 50: In Home -> Browse files generated PVOL files shows error: HTTP Status 500,
* Ticket 303: remove double index from dex_messages table

RAVE:

* Ticket 181: don't overwrite newer rave_pgf_quality_registry.xml
* Ticket 309: Add support for modifying the rave_pgf_quality_registry,xml
* Ticket 304: Newest areas lost from area_registry when upgrading to 1.9-beta1-ec1
* Ticket 308: Add cartesian composite generator to rave
* Ticket 307: pycomposite time and date is not possible to read

## Release date: 2013-09-30

Quick emergency correction due to a mistake during delivery to the source repository. The deployer was disabled. See release information for 1.9-beta1 for release information.

## Release date: 2013-09-30

This is a major (beta) release with new product generation functionality and also updated with more functionality for stability and usability. We have also added product generators for generating both WRWP and ACRR products. The WRWP product generator requires fortran and lapack so if you want to install this generator you will have to read the help and INSTALL notes.

The upgrade might take quite a long time, that is due to some triggers that might cause the upgrade to take quite a long time in a production environment with a lot of deliveries. If you experience problems upgrading due to database timeouts or that it just hangs during the dex db upgrade. You could truncate the dex_delivery tables (truncate table dex_delivery_registry,dex_delivery_registry_users;)

Changes from 1.7 to 1.9-beta1

node-installer:

* Ticket 302: Add installation of baltrad wrwp package to the installer
* Ticket 292: Add functionality for performing site-specific post-operations during installation

BEAST:

* Ticket 299: Add rule for WRWP product generation
* Ticket 294: Add rule for ACRR product generation

BALTRAD-DEX:

* Ticket 300: Add support for creating WRWP routes
* Ticket 259: When adding data source it resets all selected values if missing field
* Ticket 297: After connecting to remote node, local data sources are shown
* Ticket 268: key approval - add message and guidance in the web UI
* Ticket 295: Add rule for ACRR product generation
* Ticket 291: Add possibility to authenticate with LDAP
* Ticket 290: node status page takes too long time to load
* Ticket 289: Incorrect Cartesian images in DEX data preview page
* Ticket 285: Redirect user and show message when session expires
* Ticket 279: Adapt documentation to DEX build 449
* Ticket 284: logout.htm page redirects to insecure protocol
* Ticket 283: Too many open files

RAVE:

* Ticket 301: scansun fails to bulid due to missing libm
* Ticket 299: Add WRWP product generation
* Ticket 296: Add plugin for ACRR product generation

BWRWP:

* Added

## Release date: 2013-06-30

This is a major release with new functionallity. The most noticeable change is that the GUI has been completely changed. The other major feature is that https-support has been added for a number of links. Due to the https-addition, you will have to modify the tomcat configration.

If you are using the delivered tomcat without any modifications, you only have to specify  --rebuild=TOMCAT in the install command. Otherwise you have to manually add:

<Connector port="8443" protocol="HTTP/1.1" SSLEnabled="true" maxThreads="150" scheme="https" secure="true" clientAuth="false" sslProtocol="TLS"  keystoreFile="<keystorepth>/keystore.jks" keystorePass="<pwd>" />

to <tprefix>/tomcat/conf/server.xml.

<pwd> should be the keystore password (and if that has not been specified,  the same pwd as is used for tomcat)

<keystorepth> should most likely be .../baltrad/etc/bltnode-keys but if you have specified --keystore=<pth>, then it is pth.

A couple of new optional arguments has been added to the installer:

* keystoredn=<dn>
* keystorepwd=<pwd>
* tomcatsecureport=<port>
* tomcatfwdports=<httpport>,<httpsport>

It is recommended that you read and understand the usage of these attributes. A file called setup_apache_for_redirect.txt has also been added to the installer and atempts to explain how to configure apache for beeing able to use proxying.

Changes from 1.6.1-ec1 to 1.7

node-installer:

* Ticket 282: Adapt node-installer to BaltradDex build !#451

BALTRAD-DEX:

* Ticket 281: Implement HTTPS support,
* Ticket 278: Stack-trace when clicking on Home->Browse files->details
* Ticket 280: Incorrect input stream processing in PostKeyServlet
* Ticket 277: Authenticate key in post key request
* Ticket 269: IP from user logins should be logged, preferably in a security log,
* Ticket 274: Radar Berlevag is missing
* Ticket 276: Adjust DEX db upgrade script
* Ticket 275: Upgrade DEX GUI

## Release date: 2013-04-17

The 1.6.1 release contains a number of debug messages that have got a too high presentation level which causes a lot of unnecessary messages being shown in the DEX-system messages log.

Changes from 1.6.1 to 1.6.1-ec1

BALTRAD-DEX:

* Changed

## Release date: 2013-04-15

This is a maintenance release with a number of bug corrections.

Changes from 1.6 to 1.6.1

BEAST:

* Ticket 256: When an exception occurs in a timeout it might terminate timeout scheduler

BALTRAD-DEX:

* Ticket 49: lvrix files in dex preview seems rotated by ~90 deg.
* Ticket 251: Automate key exchange - add missing test cases
* Ticket 255: Broken "file details" page
* Ticket 262: Don't validate node name length
* Ticket 263: User admin can't change password
* Ticket 264: Rename private/public key folders when node name is modified

## Release date: 2013-03-12

This is a major release that will affect the nodes quite heavily. This release requires a fresh database installation *(use --reinstalldb)* which will cause all your previous settings to disappear. These database changes are due to the revamp of DEX and the communication protocol between the nodes. As you can imagine, this will effectively render this release unable to communicate with earlier releases of the baltrad software. We are sorry for the inconvenience this will cause you but it will hopefully make the data exchange more robust..

Another thing that has been included in this software release is a supervisor. Please refer to the dex user documentation for more information about this feature.

Changes from 1.5 to 1.6

node-installer:

* Ticket 173: Don't use log4j.properties file.
* Ticket 199: Local node settings changed to default.
* Ticket 242: Add possibility to do a post installation configuration
* Ticket 235: Adapt node-installer to renamed DEX properties file

HLHDF:

* No changes

BALTRAD-DB:

* No changes

BEAST:

* Ticket 191: enable PMAX composite generation from composite route
* Ticket 221: Add supervising features
* Ticket 226: Add possibility to use supervisor for querying for product in bdb
* Ticket 228: Add MAX algorithm to the composite route

BALTRAD-DEX:

* Ticket 111: configure data sources - removal of a recipient user does not stop data from being sent,
* Ticket 185: Normalize DEX db schema
* Ticket 188: Simplify configuration of new radars
* Ticket 191: enable PMAX composite generation from composite route, Ticket 228: Add MAX algorithm to the composite route
* Ticket 201: Status 500 when trying to view a volume route
* Ticket 215: Adapt documentation to build #391
* Ticket 217: Implement proper equals() and hashCode() methods for compared objects
* Ticket 218: Implement proper equals() and hashCode() methods for compared objects
* Ticket 221: Add supervising features, Ticket 184: In 'List of routes' error, when try to view route
* Ticket 222: Inject files into DEX does not work
* Ticket 226: Add possibility to use supervisor for querying for product in bdb
* Ticket 234: Set charset explicitly while parsing string entity
* Ticket 236: Node settings changed in 3 pages, but 4 page remained polish
* Ticket 239: Http element charset not set in HttpClient
* Ticket 240: Local peer account not created
* Ticket 241: Peer data sources not stored locally
* Ticket 243: No information on upload status
* Ticket 244: Local and peer data sources not distinguished
* Ticket 245: Delete peer data sources when removing downloads
* Ticket 249: Simplify subscription object, remove dex_nodes table, add transactions
* Ticket 250: ignore object id fields while converting to JSON
* Ticket 251: Automate key exchange
* Ticket 253: Not possible to start DEX

RAVE:

* Ticket 216: acrr never sets undetect value
* Ticket 191: enable PMAX composite generation from composite route
* Ticket 220: minor odds and ends
* Ticket 224: Adapt rave to use new way to communicate with DEX
* Ticket 227: Add MAX algorithm to the composite
* Ticket 246: Improvements to dealiasing
* Ticket 254: Add hit-accumulation clutter management

RAVE-GMAP:

* No changes

BROPO:

* No changes

BBUFR:

* No changes

BEAMB:

* No changes

This release is identical to 1.5-beta except for a tidied-up INSTALL file.

## Release date: 2012-12-31

Please note the advisory on ODIM sources from the previous release (see below).

## Release date: 2012-12-21

Changes from 1.5-alpha1 to 1.5-beta:

node-installer:

  Changed but no tickets resolved

HLHDF:

  No changes

BALTRAD-DB:

  No changes

BEAST:

  No changes

BALTRAD-DEX:

  No changes

RAVE:

* Ticket 208: radvol Makefile issues
* Ticket 153: command-line binary for PoO
* Ticket 207: add Odyssey QC routines
* Ticket 206: Add RADVOL
* Ticket 196: add dealiased wind algorithm

RAVE-GMAP:

* Ticket 210: copy-paste error with pover in radar.js

BROPO:

  No changes

BBUFR:

  No changes

BEAMB:

* Ticket 186: add two-way correction
* Ticket 209: add E140S10 tile config
* Ticket 150: write a command-line binary

*Important*: the ODIM source definitions have been updated, and updating your node with them must be done manually according to http://git.baltrad.eu/config.html#con_os . This is not mandatory, but it is advisable.

News: the RAVE product generation framework server has now been made much more efficient and scalable with the help of Python's multiprocessing module. It now processes jobs with a pool of asynchronous worker processes. The default number of workers in the pool (4) can be changed with the PGFs variable in the Lib/rave_defines.py file.

Release date: 2012-11-15

Changes from 1.2.1-ec2 to 1.5-alpha1

node-installer:

  Changed but no tickets resolved

HLHDF:

  No changes

BALTRAD-DB:

  No changes

BEAST:

  No changes

BALTRAD-DEX:

* Ticket 183: Upgrade trimmer functions
* Ticket 182: DEX should handle database connection errors and BDB service outages
* Ticket 179: Server should answer with 401 status (unauthorized) in case when client's public key is missing
* Ticket 177: make "doc" ant target independent from other targets in the build script
* Ticket 33: user can't change his password
* Ticket 52: Add possibility to search the system messages

RAVE:

* Ticket 2: multiple server instances
* Ticket 193: one-liner in pgf composite generator
* Ticket 190: pooscan == NULL (temporary)
* Ticket 175: update odim_source.xml
* Ticket 174: rename transform to toolbox
* Ticket 158: VerticalProfile: Prevent levels to be set when fields already have been added
* Ticket 157: Add Vertical Profile support

RAVE-GMAP:

* Ticket 180: add display of more quality-indicator fields

BROPO:

  No changes

BBUFR:

  No changes

BEAMB:

  No changes

This is an emergency correction.

## Release date: 2012-10-02

Changes from 1.2.1-ec1 to 1.2.1-ec2

BALTRAD-DEX:

* Ticket 167: No system messages
* Ticket 166: Temp files never removed
* Ticket 170: Upload status page displays only one peer user
* Ticket 163: Update documentation to cover default admin password issue
* Ticket 165: Wrong entry condition to data delivery loop
* Ticket 159: Caught exception in HandleFrameTask
* Ticket 164: DEX db upgrade script fails when installing with node-installer
* Ticket 160: Settings are changed to Poland node
* Ticket 162: Registry manager fails to store registry entry
* Ticket 156: Use JDBCTemplate in FileObjectManager
* Ticket 155: Use JDBCTemplate in NodeConnectionManager

This is an emergency correction.

## Release date: 2012-09-03

Changes from 1.2.1 to 1.2.1-ec1

BALTRAD-DEX:

* Ticket 151: Use JDBCTemplate in LogManager
* Ticket 152: Data sources configuration page unavailable

This is a bug fix release.

## Release date: 2012-08-30

Changes from 1.2

node-installer:

* Ticket 143: Add install howtos to installation package
* Ticket 142: beast pgf should use the generated bltnode.properties file
* Ticket 137: baltrad-bdb-server fails to start due to missing http.cookies
* Ticket 133: adapt node-installer to DEX build #339

BEAST:

* Ticket 139: beast pgf should be able to communicate with dex

BALTRAD-DEX:

* Ticket 110: configure data sources - select users pane is not intuitive and user friendly.
* Ticket 131: Create documentation for BaltradDex
* Ticket 130: Incorrect encoding of diacritic signs

RAVE:

* Ticket 140: Convert polar scan parameter from float64 to uint8

BROPO:

* Ticket 13: Wrap-around issues at 360-0°
* Ticket 132: ropo --lookup=True doesn't work

## Release date: 2012-06-29

Planned release

## Release date: 2012-06-21

Changes from 1.2-beta1

BALTRAD-DEX:

* Ticket 120: Enable password encoding for spring-security form login
* Ticket 117: Error when in Home i press Browse files and next press on Details
* Ticket 113: Use spring security package

RAVE:

* Ticket 122: Use of def.mk not possible without setting some build flags manually
* Ticket 121: Add possibility to configure rave with java-support

One major change is that you now have a hopefully more efficient bdb server. It is based on cherrypy and can be  activated / configured in the bltnode.properties configuration file. Upon upgrade / installation the server type  will be changed to cherrypy so no extra  work should be necessary.

If you want to use the old server variant, just change bltnode.properties and set server type to werkzeug again.

* baltrad.bdb.server.type = werkzeug

Release date: 2012-06-04

Changes from 1.1.3

node-installer:

* Ticket 37: can't find lockfile when installing from scratch
* Ticket 45: server: serve more efficiently

HLHDF:

* No changes

BALTRAD-DB:

* Ticket 9: allow specifying more than two node levels for attributes
* Ticket 45: server: serve more efficiently

BEAST:

* No changes

BALTRAD-DEX:

* Ticket 107: Improve error diagnostics and message logging

RAVE:

* Ticket 109: Implement accumulation ACRR

RAVE-GMAP:

* No changes

BROPO:

* No changes

BBUFR:

* No changes

BEAMB:

* No changes

This is a maintenance release.

## Release date: 2012-05-23

Changes from 1.1.2

node-installer:

* Ticket 104: user .pydistutils.cfg may interfere with the installation
* Ticket 106: Unsupported machine type: i686
* Ticket 102: error with node-installer (STANDALONE_RAVE -> BDB_URI)
* Ticket 29: rotate logs

HLHDF:

* No changes

BALTRAD-DB:

* No changes

BEAST:

* No changes

BALTRAD-DEX:

* Ticket 98: In 'Distribution route' 'Name template' do not work

RAVE:

* Ticket 103: Add support for BltCommandMessage

RAVE-GMAP:

* No changes

BROPO:

* No changes

BBUFR:

* No changes

BEAMB:

* No changes

We have added so that you now should be able to install parts of the system separately. This can be specified as

  --subsystems=<subsystem>[,<subsystem>]*

where <subsystem> can be one of:

* RAVE = RAVE PGF
* STANDALONE_RAVE = RAVE without BDB-connection
* BDB = Standalone BDB
* DEX = Standalone DEX

If you specify --subsystems=RAVE or --subsystems=DEX without also specifying BDB, then you will have to specify --bdb-uri=... as well.

The other thing that has been changed and needs to be tested a bit more careful is that we now are sending UUIDs instead of absolute file paths when generating volumes, composites and google map images. If you still are using the google map scripts they should be backward compatible.

It might be a good idea to test that everything works properly before deploying it to the production environment since it only has been tested locally without any major load. Also, if you experience any drastic changes in performance please let us know.

## Release date: 2012-04-25

Changes from 1.1.1

node-installer:

* Ticket 15: option to install stand-alone RAVE with its deps
* Ticket 80: Add libpq-dev as pre requirement package for ubuntu.
* Ticket 81: Add freetype2 as optional requirement for installation
* Ticket 82: Change BltGenerateMessage from composite rule to send uuids instead of files
* Ticket 83: Change BltGenerateMessage from volume rule to send uuids instead of file
* Ticket 84: bdb installs bdbclient and bdbcommon in a virtual environment
* Ticket 88: Change BltGenerateMessage from google map rule to send uuids instead of file
* Ticket 89: Add possibility to install DEX separately
* Ticket 94: Add description about ubuntu 11.10 encryption problems
* Ticket 93: baltrad-bdb-client installed at wrong place

HLHDF:

* No changes

BALTRAD-DB:

* Ticket 18: enable configuring logging for bdb-server

BEAST:

* Ticket 38: use special attributes from _bdb group in BDB queries
* Ticket 82: Change BltGenerateMessage from composite rule to send uuids instead of files
* Ticket 83: Change BltGenerateMessage from volume rule to send uuids instead of file
* Ticket 86: RuleUtilities uses deprecated method call getSources
* Ticket 88: Change BltGenerateMessage from google map rule to send uuids instead of file

BALTRAD-DEX:

* Ticket 85: Change volume rule timeout description from milliseconds to seconds
* Ticket 95: use special attributes from _bdb group in BDB queries

RAVE:

* Ticket 82: Change BltGenerateMessage from composite rule to send uuids instead of files
* Ticket 83: Change BltGenerateMessage from volume rule to send uuids instead of file
* Ticket 87: Add possibility to get a stored file from bdb

RAVE-GMAP:

* Ticket 88: Change BltGenerateMessage from google map rule to send uuids instead of file

BROPO:

* No changes

BBUFR:

* No changes

BEAMB:

* No changes

This release contains a predefined rule for generating google map images from composites so please verify that it is doing the same thing that the previous groovy rule. Other than that, this is a maintenance release.

## Release date: 2012-04-11

Changes from 1.1.0

node-installer:

* Ticket 60: Incorrect information...
* Ticket 68: node name mess
* Ticket 30: make google map rule a proper rule

HLHDF:

* No changes

BALTRAD-DB:

* Ticket 79: Add integration tests for python-client to server communication
* Ticket 78: python client api update source not working
* Ticket 301: Update & Add Source not working properly
* Ticket 42: java-client: deprecate source management through Database interface
* Ticket 56: what/source:PLC identifier invalid when contains diacritics
* Ticket 57: Request to introduce q.setDistinct() functionality

BEAST:

* Ticket 30: make google map rule a proper rule
* Ticket 59: Convert to easymock 3 usage for testing

BALTRAD-DEX:

* Ticket 74: Composite timeout help invalid
* Ticket 30: make google map rule a proper rule
* Ticket 880: user can't download files
* Ticket 819: data sources with no users
* Ticket 915: Save settings with empty address gives jsp error
* Ticket 63: Empty rows before data sorce description
* Ticket 66: Certificates option disappear after Connections option is used
* Ticket 292: data download link exposes full path
* Ticket 722: don't issue direct statements against bdb db

RAVE:

* No changes

RAVE-GMAP:

* Ticket 73: GmapCreator uses erroneous default whatgroup
* Ticket 30: make google map rule a proper rule

BROPO:

* No changes

BBUFR:

* No changes

BEAMB:

* No changes

## Release date:  2012-03-21

Changes from 1.0.7

node-installer:

* Ticket 55: add 1.1.0 to releases.dox
* Ticket 54: Not possible to specify --warfile
* Ticket 825: Conflicting pgsql-devel packages
* Ticket 913: add python progressbar as dependency
* Ticket 946: setup script does not print argument causing failure
* Ticket 910: add sqlalchemy-migrate as a dependency
* Ticket 863: Can download a tarball, but also need git.
* Ticket 874: make generated private keys only readable by owning user
* Ticket 943: tomcatpwd argument handled improperly
* Ticket 940: v1.0.7 fails on deploy
* Ticket 941: cosmetic glitches in ./setup --help
* Ticket 918: allow specifying database host by name

HLHDF:

* Ticket 917: Make configuration script not enforcing static libz

BALTRAD-DB:

* Ticket 948: FileCache does not seem to remove files properly
* Ticket 916: server: enable storing/retrieving filters
* Ticket 921: server: split source management from Database interface
* Ticket 922: server: always access source attributes through the same column
* Ticket 920: python-client: enable specifying source attribute for da_stats command
* Ticket 907: server: store /what/source elements in a separate table
* Ticket 919: server: index bdb_nodes(path, name)
* Ticket 909: server: store path in bdb_nodes
* Ticket 908: server: rename bdb_attribute_value columns
* Ticket 906: server: use sqlalchemy-migrate to manage sqlalchemy backend schema
* Ticket 376: python-client: add command to print data availability statistics

BEAST:

* Ticket 939: Problems encountered in Groovy script /opt/baltrad/beast/examples/GenerateGmapPng.groovy
* Ticket 856: BltAdaptorManager tries to send null messages

BALTRAD-DEX:

* No changes

RAVE:

* Ticket 48: n2b: ERROR elangle
* Ticket 53: make expects that hlhdf.mk is available during clean/distclean
* Ticket 937: Defining a Cartesian area - area created, but composites not generated
* Ticket 947: etc directory not created during installation
* Ticket 942: rave_defines not updated during install
* Ticket 6: Use std configure/make/make install
* Ticket 6: Use std configure/make/make install
* Ticket 932: detection_range should get the gain/undetect updated to correspond to 0-1
* Ticket 931: fillGap only working for default parameter in cartesian
* Ticket 928: add pseudo-MAX polar-to-cartesian selection
* Ticket 651: double how/nodes entry
* Ticket 891: composite several parameters at once

RAVE-GMAP:

* No changes

BROPO:

* No changes

BBUFR:

* No changes

BEAMB:

* No changes

BALTRAD-DB:

* Ticket 901: java-client: enable fine-grained matching for /_bdb/source in Oh5MetadataMatcher
* Ticket 905: server: properly map plain attributes to their value columns
* Ticket 903: server: properly store boolean values
* Ticket 904: java-client: update defaultAttributes.xml to contain attributes from _bdb group
* Ticket 896: server: add interval expression (and handling)
* Ticket 898: python-common: exclude high value from between expression
* Ticket 897: server: enable using special attributes from _bdb group in queries
* Ticket 894: python-client: enable executing attribute queries
* Ticket 869: server: enable determining supported authentication types

BEAST:

* Ticket 899: use special attributes from _bdb group in BDB queries

RAVE:

* Ticket 892: add distance as quality field in composite

BEAMB:

* Ticket 879: add default radar height

We are heading for 1.2 to be released in 30th of june 2012 and will come back with further information about release plan and contents. You can find the latest software here [The baltrad git repository](http://git.baltrad.eu/git) - Baltrad git repository
