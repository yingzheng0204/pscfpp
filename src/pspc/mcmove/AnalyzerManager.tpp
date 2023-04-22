#ifndef PSPC_ANALYZER_MANAGER_TPP
#define PSPC_ANALYZER_MANAGER_TPP

#include "AnalyzerManager.h" 
#include "Analyzer.h" 
#include <util/archives/Serializable_includes.h>

namespace Pscf {
namespace Pspc {

   using namespace Util;

   /*
   * Constructor.
   */
   template <int D>
   AnalyzerManager<D>::AnalyzerManager()
   : Manager< Analyzer<D> >()
   {  setClassName("AnalyzerManager"); }

   /*
   * Destructor.
   */
   template <int D>
   AnalyzerManager<D>::~AnalyzerManager()
   {} 

   /*
   * Read parameter file. 
   *
   * \param in input parameter file stream.
   */
   template <int D>
   void AnalyzerManager<D>::readParameters(std::istream &in)
   {
      read<long>(in,"baseInterval", Analyzer<D>::baseInterval);
      Manager< Analyzer<D> >::readParameters(in);
   }

   /*
   * Call initialize method of each analyzer.
   */
   template <int D>
   void AnalyzerManager<D>::setup() 
   {
      for (int i = 0; i < size(); ++i) {
         (*this)[i].setup();
      }
   }
 
   /*
   * Call sample method of each analyzer.
   */
   template <int D>
   void AnalyzerManager<D>::sample(long iStep) 
   {
      UTIL_CHECK(Analyzer<D>::baseInterval > 0);
      UTIL_CHECK(iStep % Analyzer<D>::baseInterval == 0);
      for (int i = 0; i < size(); ++i) {
         (*this)[i].sample(iStep);
      }
   }
 
   /*
   * Call output method of each analyzer.
   */
   template <int D>
   void AnalyzerManager<D>::output() 
   {
      for (int i = 0; i < size(); ++i) {
         (*this)[i].output();
      }
   }

   #if 0
   /*
   * Read instructions for creating objects from file.
   */
   template <int D>
   void AnalyzerManager<D>::loadParameters(Serializable::IArchive &ar)
   {
      loadParameter<long>(ar, "baseInterval", Analyzer<D>::baseInterval);
      Manager< Analyzer<D> >::loadParameters(ar);
   }

   /*
   * Read instructions for creating objects from file.
   */
   void AnalyzerManager<D>::save(Serializable::OArchive &ar)
   {
      ar << Analyzer<D>::baseInterval;
      Manager< Analyzer<D> >::save(ar);
   }
   #endif

}
}
#endif
