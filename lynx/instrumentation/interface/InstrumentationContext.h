/*! \file   InstrumentationContext.h
	\author Naila Farooqui <naila@cc.gatech.edu>
	\date   Sunday October 14, 2012
	\brief  The header file for the InstrumentationContext class.
*/

#ifndef INSTRUMENTATION_CONTEXT_H_INCLUDED
#define INSTRUMENTATION_CONTEXT_H_INCLUDED

#include <lynx/instrumentation/interface/PTXInstrumentor.h>

namespace instrumentation
{
    class InstrumentationContext
    {
        public:

            InstrumentationContext();
            
            bool toggled;            

            PTXInstrumentor * getActiveInstrumentor();
            void setActiveInstrumentor(PTXInstrumentor * instrumentor);

        private:
            //! currently active instrumentor
            PTXInstrumentor * _activeInstrumentor;    
             

    };
}

#endif
