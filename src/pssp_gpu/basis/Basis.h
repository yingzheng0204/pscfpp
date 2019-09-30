#ifndef PSSP_GPU_BASIS_H
#define PSSP_GPU_BASIS_H
/*
* PSCF - Polymer Self-Consistent Field Theory
*
* Copyright 2016, The Regents of the University of Minnesota
* Distributed under the terms of the GNU General Public License.
*/

#include <pscf/math/IntVec.h>
#include <pssp_gpu/field/RDFieldDft.h>
#include <pssp_gpu/field/RDField.h>
#include <pscf/mesh/MeshIterator.h>
#include <pscf/mesh/Mesh.h>
#include <pssp_gpu/crystal/shiftToMinimum.h>
#include <pssp_gpu/crystal/UnitCell.h>
#include <util/containers/DArray.h>
#include <util/containers/GArray.h>
#include <util/containers/DMatrix.h>

namespace Pscf { 

   //since we are using member function of all of these forward declare is not
   //enough

   //template <int D> class Mesh;
   //template <int D> class UnitCell;
   //template <int D> class RFieldDft; //needs definition of fftw_complex
   //template <int D> class meshIterator;

namespace Pssp_gpu
{ 

   using namespace Util;

   /**
   * Basis function for pseudo-spectral scft.
   *
   * \ingroup Pssp_gpu_Basis_Module
   */
   template <int D>
   class Basis {
   
   public:
      
      /**
      * A wavevector used in the construction of symmetry adapted basis functions.
      */ 
      class Wave {
      public:
         // Coefficient of this wave within associated star basis function
         std::complex<double> coeff;

         // Square magnitude of associated wavevector
         double sqNorm;

         // Integer indices of this wavevector
         IntVec<D> indicesDft;

         // Index of star containing this wavevector
         int starId;

         // Is this wave represented implicitly in DFT of real field?
         bool implicit;
         
      //friends:
         friend class Basis;

      };
  
      /**
      * A list of wavevectors that are related by space-group symmetry operations.
      *
      * The indices of the wavevectors in a star form a continuous block. Within
      * this block, waves are listed in descending lexigraphical order of their 
      * integer (ijk) indices, with more signficant indices listed first.
      */ 
      class Star 
      {
      public:
         /**
         * Number of wavevectors in the star.
         */
         int size; 

         /**
         * Wave index of first wavevector in star.
         */
         int beginId; 

         /**
         * Wave index of last wavevector in star.
         */
         int endId;  

         /**
         * Index for symmetry of star under inversion.
         *
         * A star is said to be closed under inversion iff, for each vector G
         * in the start, -G is also in the star. If a star S is not closed 
         * under inversion, then there is another star S that is related to 
         * S by inversion, i.e., such that for each G in S, -G is in S'. Stars
         * that are related by inversion are always listed consecutively.
         * 
         * If a star is closed under inversion, invertFlag = 0.
         *
         * If a start is not closed under inversion, then invertFlag = +1 or -1,
         * with inverFlag = +1 for the first star in the pair of stars related 
         * by inversion and invertFlag = -1 for the second.
         *
         * In a centro-symmetric group, all stars are closed under inversion.
         * In a non-centro-symmetric group, some stars may still be closed under
         * inversion.
         */
         int invertFlag; 

         /**
         * Index for symmetry of associated basis function under inversion.
         *
         * If basis function is even under inversion signFlag = 1.
         * If basis function is odd under inversion signFlag = -1.
         */
         int signFlag; 

         /**
         * Integer indices of characteristic wave of this star.
         *
         * For invertFlag = 0 or 1, this is the first wave in the star.
         * For invertFlag = -1, this is the last wave in the star.
         * Container removed to facilitate GPU calculation stress is done by basis
         * waveBz is now an object in Basis class of size (mesh,D)
         * This will break for symmetry other than I
         */
         //IntVec<D> waveBz;
         

         /**
         * Is this star cancelled, i.e., associated with a zero function?
         *
         * The cancel flag is true iff there is not a nonzero basis function
         * associated with this star.
         */
         bool cancel;

      //friends:
         friend class Basis;

      };

      /**
      * Default constructor.
      */
      Basis();
 
      /**
      * Construct basis for a specific grid and space group.
      *
      * Proposal: Initially implementation functions correctly only if groupName == 'I'. 
      */
      void makeBasis(const Mesh<D>& mesh, const UnitCell<D>& unitCell, std::string groupName);
     
      /**
      * Convert field from symmetry-adapted representation to complex DFT.
      *
      * \param components coefficients of symmetry-adapted basis functions.
      * \param dft complex DFT representation of a field.
      */
	  void convertFieldComponentsToDft(RDField<D>& components, RDFieldDft<D>& dft);

      /**
      * Convert DFT of real field to symmetry-adapted representation.
      *
      * \param dft complex DFT representation of a field.
      * \param components coefficients of symmetry-adapted basis functions.
      */
      void convertFieldDftToComponents(RDFieldDft<D>& dft, RDField<D>& components);

      void convertFieldDftToComponents(cufftComplex* dft, cufftReal* components);

      /* 
      * Calculates dksq_ assuming ksq are in non increasing order of ksq 
      * and pairs of stars related by inversion are listed consecutively
      */
      void makeDksq(const UnitCell<D>& unitCell);

      void update (const UnitCell<D>& unitCell);

      /**
      * Total number of wavevectors.
      */
      int nWave() const;

      /**
      * Total number of stars.
      */
      int nStar() const;
   
      /**
      * Total number of nonzero symmetry-adapted basis functions.
      */
      int nBasis() const;
  
      /** 
      * Get a specific Wave, access by integer array index.
      */
      Wave& wave(int i);
  
      /** 
      * Get a Wave, access wave by IntVec of indices.
      */
      Wave& wave(IntVec<D> vector);
  
      /** 
      * Get a Star, access by integer index.
      */
      Star& star(int i);
      
      // Derivatives of dksq with respect to each 
      // of the parameters (rows)
      //public for now cause im lazy
      cufftReal* dksq; 

   private:


  

      ///cuda device side memory of lookup table
      int* rankTable_;
      int* partnerIdTable_;
      bool* implicitTable_;
      cufftComplex* coeffTable_;
      int* starIdTable_;
      int* invertFlagTable_;
      int* star2rank_;

      /// Array of all Wave objects (all wavevectors)
      DArray<Wave> waves_;

      /// Array of Star objects (all stars of wavevectors).
      GArray<Star> stars_;
   
      /// Indexing that allows identification by IntVec
      DArray<int> waveId_;
     
      int* waveBz_;
      int* waveBz_d;

      /// Total number of wavevectors
      int nWave_;

      /// Total number of stars.
      int nStar_;

      /// Pointer to associated UnitCell<D>
      const UnitCell<D>* unitCellPtr_;

      /// Dimensions of associated spatial grid.
      //IntVec<D> meshDimensions_;
      const Mesh<D>* mesh_;

   };

   template <int D>
   inline int Basis<D>::nWave() const
   { return nWave_; }

   template <int D>
   inline int Basis<D>::nStar() const
   { return nStar_; }

   template <int D>
   inline 
   typename Basis<D>::Wave& Basis<D>::wave(int i)
   { return waves_[i]; }

   template <int D>
   inline 
   typename Basis<D>::Star& Basis<D>::star(int i)
   { return stars_[i]; }

}
}
#include "Basis.tpp"
#endif