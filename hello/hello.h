/* --------------------------------------------------------------------
Copyright (C) 2013 Swedish Meteorological and Hydrological Institute, SMHI

This is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This software is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with RAVE.  If not, see <http://www.gnu.org/licenses/>.
------------------------------------------------------------------------*/

/** Header file for tutorial purposes
 * @file
 * @author Daniel Michelson, SMHI
 * @date 2013-11-15
 */
#ifndef HELLO_H
#define HELLO_H
#include <stdio.h>

#include "rave_io.h"
#include "rave_types.h"
#include "rave_attribute.h"
#include "polarscan.h"
#include "polarvolume.h"
#include "cartesian.h"
#include "vertical_profile.h"

/**
 * Queries the ODIM object type for a given file and adds a greeting metadata 
 * attribute to the top-level /how group.
 * @param[in] raveio - the input RaveIO_t object
 * @returns object type, defaulting to Rave_ObjectType_UNDEFINED (-1)
 */
int hello(RaveIO_t* raveio);

#endif
