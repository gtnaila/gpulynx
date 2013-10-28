/*! \file   AnalysisFactory.cpp
        \date   Saturday September 14, 2013
        \author Naila Farooqui <naila@cc.gatech.edu>
        \brief  The source file for the AnalysisFactory class.
       
*/

// Ocelot Includes
#include <ocelot/analysis/interface/AnalysisFactory.h>

#include <ocelot/analysis/interface/DataflowGraph.h>
#include <ocelot/analysis/interface/DivergenceAnalysis.h>
#include <ocelot/analysis/interface/ControlTree.h>
#include <ocelot/analysis/interface/DominatorTree.h>
#include <ocelot/analysis/interface/PostdominatorTree.h>

namespace analysis
{

Analysis* AnalysisFactory::createAnalysis(const std::string& name,
        const StringVector& options)
{
        Analysis* analysis = NULL;

        if(name == "ControlTreeAnalysis")
        {
                analysis = new ControlTree;
        }
        else if(name == "DominatorTreeAnalysis")
        {
                analysis = new DominatorTree;
        }
        else if(name == "PostDominatorTreeAnalysis")
        {
                analysis = new PostdominatorTree;
        }
        else if(name == "DataflowGraphAnalysis")
        {
                auto dfg = new DataflowGraph;
               
                dfg->setPreferredSSAType(analysis::DataflowGraph::None);
                               
                analysis = dfg;
        }
        else if(name == "DivergenceAnalysis")
        {
                analysis = new DivergenceAnalysis;
        }

        if(analysis != NULL)
        {
                analysis->configure(options);
        }
       
        return analysis;
}

}


