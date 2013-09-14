/*! \file PTXInstrumentor.h
	\date Saturday November 13, 2010
	\author Naila Farooqui <naila@cc.gatech.edu>
	\brief The header file for the Ocelot PTX Instrumentor
*/

#ifndef PTX_INSTRUMENTOR_H_INCLUDED
#define PTX_INSTRUMENTOR_H_INCLUDED

#include <string>
#include <vector>
#include <map>

#include <lynx/translator/interface/CToPTXTranslator.h>
#include <lynx/instrumentation/interface/kernel_profile.h>

#include <ocelot/transforms/interface/Pass.h>
#include <ocelot/ir/interface/Module.h>

#include <hydrazine/interface/json.h>

#include <ostream>

#include <mqueue.h>

namespace instrumentation
{
	/*! \brief Able to run various instrumentation passes over PTX modules */
	class PTXInstrumentor
	{
		
        public:

            enum FormatType {
                json,
                text
            };
        
            typedef std::map<int, transforms::Pass *> PassMap;
            typedef std::map<std::string, int> KernelDataMap;
            typedef std::map<std::string, std::vector<std::string>> KernelLabelsMap;
            typedef std::vector<std::string> KernelVector;
            typedef std::map<std::string, std::vector<size_t>> KernelBasicBlockSizeMap;
            typedef std::vector<size_t> BasicBlockInstructionVector;

            std::string description;

			/*! \brief device name for JSON output */
			std::string deviceName;
			
			/*! \brief The input file being instrumented */
			std::string input;
			
			/*! \brief The output file being generated */
			std::string output;

            /*! \brief The output stream for writing instrumentation results */
            std::ostream *out;
            
            /*! \brief The PTX module being instrumented */
            ir::Module *module;
            
            /*! \brief The name of kernel being instrumented */
			std::string kernelName;        

            /*! \brief The instrumentation passes */
            PassMap passes;
            
            /*! \brief The symbol name for data structure storing instrumentation results */
            std::string symbol;
            
            /*! \brief The number of thread blocks or CTAs specified for this execution */
            unsigned int threadBlocks;

            /*! \brief The number of threads specified for this execution */
            unsigned int threads;

            /*! \brief The strings representing the basic block labels */
            KernelLabelsMap kernelLabelsMap;
            
            /*! \brief is the instrumentation being applied (is it 'on')? */
            bool on;
    
             /*! \brief format for display */
            FormatType fmt;

            /*! \brief check if device info has already been written */
            bool deviceInfoWritten;
            
            unsigned int sharedMemSize;
            
            KernelDataMap kernelDataMap;
            KernelBasicBlockSizeMap kernelBasicBlocks;
            KernelVector kernelsToInstrument;

            int iterations;

        protected:

            kernel_profile _profile;

		public:
		
		    PTXInstrumentor();
            ~PTXInstrumentor();
            
            /* !\brief Ensures conditions are met to perform this instrumentation */		    
            bool conditionsMet();

            /*! \brief Performs the instrumentation */
			void instrument();		

            /*! \brief Performs the instrumentation */
            void instrument(ir::Module& module);	

            /*! \brief The finalize method performs any necessary CUDA runtime actions after instrumentation */
            void finalize();

            /*! \brief The createPasses method instantiates the instrumentation passes */
            void createPasses(std::string resource);

            /*! \brief Output device info */
            void deviceInfo(std::ostream *out);

            /*! \brief The jsonEmitter method creates a JSON emitter to display JSON */
            void jsonEmitter(std::string metric, hydrazine::json::Object *stats);
			
			/*! \brief send kernel profile data */
            int sendKernelProfile(mqd_t messageQueue);
			
        public:			
			
			/*! \brief The instrumentationSpecificationPath method returns 
			    the path for the C instrumentation code specification */
		    virtual std::string specificationPath() = 0;	    
			
			/*! \brief The validate method checks to make sure that all the 
                defined conditions are met for this instrumentation */
            virtual bool validate() = 0;

            /*! \brief The analyze method performs any necessary static analyses */
            virtual void analyze(ir::Module &module) = 0;
			
			/*! \brief The initialize method performs any necessary CUDA 
			    runtime initialization prior to instrumentation */
            virtual void initialize() = 0;
			
            /*! \brief Extracts instrumentation-specific data */
            virtual void extractResults(std::ostream *out) = 0;
	};

    typedef std::vector< PTXInstrumentor *> PTXInstrumentorVector;
}

#endif
