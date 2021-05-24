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

/** Tutorial purposes
 * @file
 * @author Daniel Michelson, SMHI
 * @date 2013-11-12
 */

#include "hello.h"


int hello(RaveIO_t* raveio) {
   RaveCoreObject* obj = NULL;
   RaveAttribute_t* att = RAVE_OBJECT_NEW(&RaveAttribute_TYPE);
   int retcode = Rave_ObjectType_UNDEFINED;

   obj = (RaveCoreObject*)RaveIO_getObject(raveio);
   retcode = RaveIO_getObjectType(raveio);

   RaveAttribute_setName(att, "how/greeting");
   RaveAttribute_setString(att, "Howzit?");

   if (retcode != Rave_ObjectType_UNDEFINED) {

      if (retcode == Rave_ObjectType_SCAN) {
	 PolarScan_addAttribute((PolarScan_t*)obj, att);
      }
      else if (retcode == Rave_ObjectType_PVOL) {
	 PolarVolume_addAttribute((PolarVolume_t*)obj, att);
      }
      else if (retcode == Rave_ObjectType_IMAGE) {
	 Cartesian_addAttribute((Cartesian_t*)obj, att);
      }
      else if (retcode == Rave_ObjectType_VP) {
	 VerticalProfile_addAttribute((VerticalProfile_t*)obj, att);
      }

   }

   RAVE_OBJECT_RELEASE(att);
   RAVE_OBJECT_RELEASE(obj);
   return retcode;
}
