# 1. Algorithm name
Hexed ODIM quantities

# 2. Basic description
## a) Physical basis of the algorithm
N/A. This is a helper algorithm used by supporting infrastructure.

## b) Amount of validation performed so far
Implemented in the Beast component. Prototyped in RAVE. This recipe is therefore based on working implementations.

## c) References (names and contact information of all developers during the evolutionary history, scientific papers)
Anders Henja and Daniel Michelson

# 3. ODIM metadata requirements for I/O
No optional 'how' attributes are required. Only the what/quantity attribute(s). 

# 4. Input data
## a) What kind of radar data (including the list of previous algorithms and quality flags applied)
Polar scans (/what/object=SCAN) and volumes (PVOL). This could be applied to products as well.

## b) Other data (optional and mandatory, applying “universally” agreed formats, geometry)
# 5. Logical steps.
A reference lookup file (e.g. XML, see attachment) lists all official ODIM quantities in a specific order, the most commonly used towards the end. This list is 64 positions long, even though fewer official quantities exist.
For each quantity, its position in the list is noted and its equivalent bit in a 64-bit integer is set to 1. This is done for all quantities, whereupon the integer is converted to a hexadecimal string. Default bit shift is from left to right.

This makes it possible to reverse the algorithm to reconstruct a list of quantities from the hex string.

One application of this formatting is to create self-descriptive file names that contain all included quantities without the string becoming ridiculously long and cumbersome.

# 6. Output.
## a) Data type
String.

Example1: a file containing only DBZH will have "0x1".
Example2: the combination of TH, DBZH, VRADH will give "0xb".

Strings will become longer with more quantities, e.g. those from dual-polarization radars.
But the strings cannot become longer than "0x7ffffffffff" with the existing number of quantities, and "0xffffffffffffffff" if ODIM ever has 64 quantities. 

## b) Added quality indicators
None.

# 7. Test concept.

Create a list of strings, each of which is an official ODIM "quantity". The algorithm should return a string that can be input to a reverse algorithm that returns the list of quantities.
