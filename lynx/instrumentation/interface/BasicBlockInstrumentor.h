/*! \file BasicBlockInstrumentor.h
	\date Monday November 15, 2010
	\author Naila Farooqui <naila@cc.gatech.edu>
	\brief The header file for BasicBlockInstrumentor
*/

#ifndef BASIC_BLOCK_INSTRUMENTOR_H_INCLUDED
#define BASIC_BLOCK_INSTRUMENTOR_H_INCLUDED

#include <string>

#include <lynx/instrumentation/interface/PTXInstrumentor.h>

#include <ocelot/transforms/interface/Pass.h>
#include <ocelot/ir/interface/Module.h>

namespace instrumentation
{
    /*! \brief Able to run the basic block instrumentation passes over PTX modules */
	class BasicBlockInstrumentor : public PTXInstrumentor
	{
		public:
		
		    enum BasicBlockInstrumentationType {
		        instructionCount,
		        executionCount,
                memoryIntensity
		    };

            /*! \brief The basic block counter */
            size_t *counter;        

            /*! \brief Number of entries per basic block */
            size_t entries;
            
            /*! \brief type of basic block instrumentation */
            BasicBlockInstrumentationType type;
			
		public:
			/*! \brief The default constructor */
			BasicBlockInstrumentor();
			BasicBlockInstrumentor(BasicBlockInstrumentationType type);

            /*! \brief The validate method verifies that the defined 
                conditions are met for this instrumentation */
            bool validate();

            /*! \brief The analyze method performs any necessary static analysis */
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
