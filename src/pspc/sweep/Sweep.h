#ifndef PSPC_SWEEP_H
#define PSPC_SWEEP_H

/*
* PSCF - Polymer Self-Consistent Field Theory
*
* Copyright 2016 - 2019, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <pscf/sweep/SweepTmpl.h>          // base class template
#include <pspc/sweep/BasisFieldState.h>    // base class template parameter
//#include <util/param/ParamComposite.h>     // base class
#include <util/global.h>

namespace Pscf {
namespace Pspc {

   using namespace Util;

   /**
   * Solve a sequence of problems along a line in parameter space.
   */
   template <int D>
   class Sweep : public SweepTmpl< BasisFieldState<D> >
   {

   public:

      /**
      * Default Constructor.
      */
      Sweep();

      /**
      * Destructor.
      */
      ~Sweep();

      /**
      * Set association with parent System.
      */
      void setSystem(System<D>& system);

   protected:

      /**
      * Setup operation at beginning sweep.
      *
      * Must call initializeHistory.
      */
      virtual void setup();

      /**
      * Set non-adjustable system parameters to new values.
      *
      * \param s path length coordinate, in range [0,1]
      */
      virtual void setParameters(double s) = 0;

      /**
      * Create guess for adjustable variables by continuation.
      */
      virtual void setGuess(double sNew);

      /**
      * Call current iterator to solve SCFT problem.
      *
      * Return 0 for sucessful solution, 1 on failure to converge.
      */
      virtual int solve(bool isContinuation);

      /**
      * Reset system to previous solution after iterature failure.
      *
      * The implementation of this function should reset the system state
      * to correspond to that stored in state(0).
      */
      virtual void reset();

      /**
      * Update state(0) and output data after successful convergence
      *
      * The implementation of this function should copy the current 
      * system state into state(0) and output any desired information
      * about the current converged solution.
      */
      virtual void getSolution();

      using SweepTmpl<BasisFieldState<D>>::nHistory;
      using SweepTmpl<BasisFieldState<D>>::ns_;
      using SweepTmpl<BasisFieldState<D>>::baseFileName_;
      using SweepTmpl<BasisFieldState<D>>::state;
      using SweepTmpl<BasisFieldState<D>>::s;
      using SweepTmpl<BasisFieldState<D>>::historySize;
      using SweepTmpl<BasisFieldState<D>>::nAccept;
      using SweepTmpl<BasisFieldState<D>>::initializeHistory;

   protected:

      System<D>& system()
      {  return *systemPtr_; }

   private:

      // Trial state (produced by continuation)
      BasisFieldState<D> trial_;

      // Pointer to parent system.
      System<D>* systemPtr_;

   };

} // namespace Pspc
} // namespace Pscf
#endif
