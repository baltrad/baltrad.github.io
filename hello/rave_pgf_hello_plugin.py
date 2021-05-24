'''
Copyright (C) 2013- Swedish Meteorological and Hydrological Institute (SMHI)

This file is part of RAVE.

RAVE is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

RAVE is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with RAVE.  If not, see <http://www.gnu.org/licenses/>.

'''
## Plugin for the hello tutorial
## Register in the RAVE PGF with: % pgf_registry -a -H http://<host>:<port>/RAVE --name=eu.baltrad.beast.hello -m rave_pgf_hello_plugin -f generate -d 'Hello tutorial'

## @file
## @author Daniel Michelson, SMHI
## @date 2013-11-15

import os
import _raveio
import _hello


## Say hello.
# @param files list of files to scan. Keep in mind that each file can be
# from a different radar.
# @return nothing
def generate(files, arguments):
    for ifstr in files:        
        rio = _raveio.open(ifstr)
        _hello.hello(rio)

    return None


if __name__ == '__main__':
    pass
  
