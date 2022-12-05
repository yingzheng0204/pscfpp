#ifndef PSCF_AMBD_RESIDUAL_H
#define PSCF_AMBD_RESIDUAL_H

/*
* PSCF - Polymer Self-Consistent Field Theory
*
* Copyright 2016 - 2022, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <pscf/inter/Interaction.h>       // base class
#include <util/containers/Array.h>        // argument (template)
#include <util/containers/Matrix.h>       // argument (template)
#include <util/global.h>                  

namespace Pscf {

   using namespace Util;

   /**
   * Quantities required to compute residual defn. of Arora et al.
   *
   * This class computes and provides access to several auxiliary 
   * quantities that are computed from knowledge of the chi matrix, and 
   * that are needed to compute the SCFT residual for multi-component 
   * systems as defined by Arora, Morse, Bates and Dorfman (AMBD) for 
   * use in Anderson-mixing iteration in the following reference:
   * 
   * A. Arora, D.C. Morse, F.S. Bates and K.D Dorfman,
   * J. Chem. Phys vol. 146, 244902 (2017).
   * 
   * \ingroup Pscf_Inter_Module
   */
   class AmbdResidual 
   {

   public:

      /**
      * Constructor.
      */
      AmbdResidual();

      /**
      * Destructor.
      */
      virtual ~AmbdResidual();

      /**
      * Set number of monomers and allocate required memory.
      *
      * \param nMonomer number of different monomer types
      */
      void allocate(int nMonomer);

      /**
      * Update all computed quantities.
      *
      * \param interaction Interaction object with current chi matrix
      */
      void update(Interaction const & interaction);

      /**
      * Return one element of the chi matrix.
      *
      * \param i row index
      * \param j column index
      */
      double chi(int i, int j) const;

      /**
      * Return one element of the inverse chi matrix.
      *
      * \param i row index
      * \param j column index
      */
      double chiInverse(int i, int j) const;

      /** 
      * Return one element of the idempotent matrix.
      *   
      * \param i row index
      * \param j column index
      */  
      double idemp(int i, int j) const; 

      /** 
      * Return sum of elements of chiInverse.
      */  
      double sum_inv() const;

      /**
      * Get number of monomer types.
      */
      int nMonomer() const;

   private:

      // Symmetric matrix of interaction parameters (local copy).
      DMatrix<double> chi_;

      // Inverse of matrix chi_.
      DMatrix<double> chiInverse_;

      // Idempotent matrix P used in residual definition.
      DMatrix<double> idemp_;

      // Sum of elements of matrix chiInverse_
      double sum_inv_;

      /// Number of monomers
      int nMonomer_;

      /// Has private memory been allocated?
      bool isAllocated_;

   };

   // Inline function

   inline int AmbdResidual::nMonomer() const
   {  return nMonomer_; }

   inline double AmbdResidual::chi(int i, int j) const
   {  return chi_(i, j); }

   inline double AmbdResidual::chiInverse(int i, int j) const
   {  return chiInverse_(i, j); }

   inline double AmbdResidual::idemp(int i, int j) const
   {  return idemp_(i, j); }

   inline double AmbdResidual::sum_inv() const
   {  return sum_inv_; }

} // namespace Pscf
#endif
