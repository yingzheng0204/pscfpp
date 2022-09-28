/*
* PSCF - Polymer Self-Consistent Field Theory 
*
* Copyright 2016 - 2022, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "System.tpp"

namespace Pscf {
namespace Pspg {

   using namespace Util;

   // Explicit instantiation of relevant class instances
   template class System<1>;
   template class System<2>;
   template class System<3>;

}
}
