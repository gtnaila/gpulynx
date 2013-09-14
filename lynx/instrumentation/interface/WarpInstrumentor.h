/*! \file WarpInstrumentor.h
	\date Saturday July 30, 2011
	\author Naila Farooqui <naila@cc.gatech.edu>
	\brief The header file for WarpReductionInstrumentor
*/

#ifndef WARP_INSTRUMENTOR_H_INCLUDED
#define WARP_INSTRUMENTOR_H_INCLUDED

#include <string>

#include <lynx/instrumentation/interface/PTXInstrumentor.h>

#include <ocelot/transforms/interface/Pass.h>
#include <ocelot/ir/interface/Module.h>

namespace instrumentation
{
    /*! \brief Able to run the warp-level instrumentation passes over PTX modules */
	class WarpInstrumentor : public PTXInstrumentor
	{
		public:
            
            enum InstrumentationType {
		        memoryEfficiency,
		        branchDivergence,
		        activityFactor,
                instructionCount,
                barrierCount
		    };		

            InstrumentationType type;

            /*! \brief The counter */
            size_t *counter;        

            unsigned int warpCount;
            
            unsigned int entries;
        	
		public:
			/*! \brief The default constructor */
			WarpInstrumentor();
			WarpInstrumentor(InstrumentationType type);

            /*! \brief The validate method verifies that the defined conditions 
                are met for this instrumentation */
            bool validate();

            /*! \brief The analyze method performs any necessary static analyses */
            void analyze(ir::Module &module);

            /*! \brief The initialize method performs any necessary CUDA 
                runtime initialization prior to instrumentation */
            void initialize();

            /*! \brief The specificationPath method specifies the 
                C code instrumentation specification file path */
            std::string specificationPath();

            /*! \brief extracts results for the instrumentation */
            void extractResults(std::ostream *out);
	};

}

#endif
