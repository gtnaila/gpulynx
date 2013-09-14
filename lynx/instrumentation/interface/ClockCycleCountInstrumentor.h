/*! \file ClockCycleCountInstrumentor.h
	\date Monday November 15, 2010
	\author Naila Farooqui <naila@cc.gatech.edu>
	\brief The header file for ClockCycleCountInstrumentor
*/

#ifndef CLOCK_CYCLE_COUNT_INSTRUMENTOR_H_INCLUDED
#define CLOCK_CYCLE_COUNT_INSTRUMENTOR_H_INCLUDED

#include <string>
#include <map>
#include <algorithm>

#include <lynx/instrumentation/interface/PTXInstrumentor.h>

#include <ocelot/ir/interface/Module.h>
#include <ocelot/transforms/interface/Pass.h>

namespace instrumentation
{
	/*! \brief Able to run the clock cycle count instrumentation pass over PTX modules */
	class ClockCycleCountInstrumentor : public PTXInstrumentor
	{
		public:             
            size_t *clock_sm_info;
			
		public:
			/*! \brief The default constructor */
			ClockCycleCountInstrumentor();

            /*! \brief The validate method verifies that the defined conditions are met for this instrumentation */
            bool validate();

            /*! \brief The analyze method performs any necessary static analysis */
            virtual void analyze(ir::Module &module);

            /*! \brief The initialize method performs any necessary CUDA runtime initialization prior to instrumentation */
            void initialize();

            /*! \brief The specificationPath method specifies the instrumentation specification file path */
            std::string specificationPath();

            /*! \brief extracts results for the basic block execution count instrumentation */
            void extractResults(std::ostream *out);

        private:
            bool pred(const std::pair<size_t, size_t>& lhs, const std::pair<size_t, size_t>& rhs);
	};
}

#endif
