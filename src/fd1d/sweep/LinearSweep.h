#ifndef FD1D_LINEAR_SWEEP_H
#define FD1D_LINEAR_SWEEP_H

/*
* PSCF - Polymer Self-Consistent Field Theory
*
* Copyright 2016 - 2019, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include "Sweep.h"                     // base class
#include "SweepParameter.h"            // member 
#include <util/containers/DArray.h>
#include <util/global.h>
#include <iostream>

namespace Pscf {
namespace Fd1d {

   class System;

   using namespace Util;

   /**
   * Base class for a sweep in parameter space where parameters change
   * linearly with the sweep variable. 
   * 
   * \ingroup Fd1d_Sweep_Module
   */
   class LinearSweep : public Sweep
   {
   public:

      /** 
      * Constructor.
      * \param system parent System object
      */
      LinearSweep(System& system);

      /**
      * Read parameters from param file.
      * 
      * \param in Input stream from param file.
      */
      void readParameters(std::istream& in);

      /**
      * Setup operation at the beginning of a sweep. Gets initial 
      * values of individual parameters.
      */
      void setup();

      /**
      * Set the state before an iteration. Called with each new iteration 
      * in SweepTempl::sweep()
      *
      * \param s path length coordinate, in [0,1]
      */    
      void setParameters(double s);

      /**
      * Output data to a running summary.
      *
      * \param out  output file, open for writing
      */
      void outputSummary(std::ostream& out);

   protected:

      using Sweep::system;
   
   private:

      /// Number of parameters being swept. 
      int nParameter_; 

      /// Array of SweepParameter objects.
      DArray< SweepParameter > parameters_;
       
   };

}
}
#endif
