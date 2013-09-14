/*! \file   InstrumentationContext.cpp
	\author Naila Farooqui <naila@cc.gatech.edu>
	\date   Sunday October 14, 2012
	\brief  The source file for the InstrumentationContext class.
*/

#ifndef INSTRUMENTATION_CONTEXT_CPP_INCLUDED
#define INSTRUMENTATION_CONTEXT_CPP_INCLUDED

#include <lynx/instrumentation/interface/InstrumentationContext.h>

namespace instrumentation
{
    InstrumentationContext::InstrumentationContext(): toggled(false), 
        _activeInstrumentor(NULL)
    {
    }

    PTXInstrumentor * InstrumentationContext::getActiveInstrumentor()
    {
        return _activeInstrumentor;
    }
    
    void InstrumentationContext::setActiveInstrumentor(PTXInstrumentor * instrumentor)
    {
        _activeInstrumentor = instrumentor;
    }
}

#endif
