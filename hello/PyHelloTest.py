'''
Copyright (C) 2013 Swedish Meteorological and Hydrological Institute, SMHI,

This file is part of RAVE.

RAVE is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

RAVE is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with RAVE.  If not, see <http://www.gnu.org/licenses/>.
------------------------------------------------------------------------*/

Tests the hello tutorial

@file
@author Daniel Michelson (Swedish Meteorological and Hydrological Institute, SMHI)
@date 2013-11-15
'''
import unittest
import _raveio
import _hello

class PyHelloTest(unittest.TestCase):
    FIXTURE = "fixtures/rix_volume.h5"
    BADINPUT = "fixtures/vp_fixture.h5"
  
    def setUp(self):
        pass

    def tearDown(self):
        pass

    def testHello(self):
        rio = _raveio.open(self.FIXTURE)
        self.assertEquals(_hello.hello(rio), _raveio.Rave_ObjectType_PVOL) 

    def testGoodbye(self):
        rio = _raveio.open(self.BADINPUT)
        self.assertNotEquals(_hello.hello(rio), _raveio.Rave_ObjectType_VP) 
