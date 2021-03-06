    /*
        Copied from the runjags package.

        Original copyright: Copyright (C) 2013 Matthew Denwood <matthewdenwood@mac.com>
        
        This code creates a JAGS module from the distributions provided

    This file is part of runjags

        This code is based on the source code for JAGS and the following tutorial:
        Wabersich, D., Vandekerckhove, J., 2013. Extending JAGS: A tutorial on 
        adding custom distributions to JAGS (with a diffusion model example). 
        Behavior Research Methods.
        JAGS is Copyright (C) 2002-10 Martyn Plummer, licensed under GPL-2
       
        This version of the module is compatible with JAGS version 3 and 4.
        Some necessary modifications are controlled using the INCLUDERSCALARDIST
        macro which is defined by makevars if JAGS version 3 is detected.
        Once JAGS version 3 becomes obsolete the redundant code will be
        removed from runjags.
        
    runjags is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    runjags is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with runjags  If not, see <http://www.gnu.org/licenses/>.
        
 */

#include <module/Module.h>

#include <function/DFunction.h>
#include <function/PFunction.h>
#include <function/QFunction.h>

//Distributions implemented in geojags
//#include "distributions/DSARError.h"
#include "distributions/DCAR.h"
#include "distributions/DSAR.h"
#include "distributions/DSPATIALEXP.h"


using std::vector;

namespace jags {
namespace geojags {

        class geojagsModule : public Module {
          public:
            geojagsModule();
            ~geojagsModule();

                //void Rinsert(RScalarDist *dist);
        };

geojagsModule::geojagsModule() : Module("geojags")
{
  // insert is the standard way to add a distribution or function
  // insert(new myfun);
  // insert(new mydist);

// Rinsert (copied from jags) adds the distribution, as well as d,f,q functions simultaneously:

  insert(new DCAR);
  insert(new DSAR);
  insert(new DSPATIALEXP);


}


// From jags:

//void geojagsModule::Rinsert(RScalarDist *dist)
//{
//        insert(dist);
//        insert(new DFunction(dist));
//        insert(new PFunction(dist));
//        insert(new QFunction(dist));
//}


geojagsModule::~geojagsModule()
{
  vector<Function*> const &fvec = functions();
  for (unsigned int i = 0; i < fvec.size(); ++i) {
    delete fvec[i];
  }
  vector<Distribution*> const &dvec = distributions();
  for (unsigned int i = 0; i < dvec.size(); ++i) {
    delete dvec[i];
  }
}

}  // namespace geojags
}  // namespace jags

jags::geojags::geojagsModule _geojags_module;

