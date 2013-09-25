#! /bin/python

################################################################################
#	\file   SConscript
#	\author Naila Farooqui <naila@cc.gatech.edu>
#   \date   Monday June 25, 2012
#	\brief  The SCons master build script for Lynx (modified the one from Ocelot)
################################################################################

import os
import inspect
from subprocess import call

#
#
## The script begins here
# try to import an environment first
try:
	Import('env')
except:
	try:
		exec open("../scripts/which.py")
		prefix = '../'
	except:
		exec open("scripts/which.py")
		prefix = './'
	exec open(prefix + "scripts/build_environment.py")
	env = Environment()

# find all source files in the source tree
sources = []                 
intermediate_headers = []
directories = [ 'lynx/analysis/implementation',
                'lynx/api/implementation',
                'lynx/cuda/implementation',
                'lynx/instrumentation/implementation',
                'lynx/transforms/implementation',
                'lynx/translator/implementation', 
                'lynx/trace/implementation',
                'hydrazine/interface',
                'hydrazine/implementation']

# Ocelot dependencies
ocelot_dep = [  'ocelot/analysis/implementation/Analysis.cpp',
                'ocelot/analysis/implementation/BranchInfo.cpp',
                'ocelot/analysis/implementation/ControlTree.cpp',
                'ocelot/analysis/implementation/DataflowGraph.cpp',
                'ocelot/analysis/implementation/DirectionalGraph.cpp',
                'ocelot/analysis/implementation/DivergenceAnalysis.cpp',
                'ocelot/analysis/implementation/DivergenceGraph.cpp',
                'ocelot/analysis/implementation/DominatorTree.cpp',
                'ocelot/analysis/implementation/PostdominatorTree.cpp',
                'ocelot/analysis/implementation/SSAGraph.cpp',
                'ocelot/cuda/implementation/FatBinaryContext.cpp',
                'ocelot/ir/implementation/ControlFlowGraph.cpp',
                'ocelot/ir/implementation/Dim3.cpp',
                'ocelot/ir/implementation/Global.cpp',
                'ocelot/ir/implementation/Instruction.cpp',
                'ocelot/ir/implementation/IRKernel.cpp',
                'ocelot/ir/implementation/Kernel.cpp',
                'ocelot/ir/implementation/Local.cpp',
                'ocelot/ir/implementation/Module.cpp',
                'ocelot/ir/implementation/Parameter.cpp',
                'ocelot/ir/implementation/PTXInstruction.cpp',
                'ocelot/ir/implementation/PTXKernel.cpp',
                'ocelot/ir/implementation/PTXOperand.cpp',
                'ocelot/ir/implementation/PTXStatement.cpp',
                'ocelot/ir/implementation/Texture.cpp',
                'ocelot/parser/implementation/PTXLexer.cpp',
                'ocelot/parser/implementation/PTXParser.cpp',
                'ocelot/transforms/implementation/Pass.cpp',
                'ocelot/transforms/implementation/PassManager.cpp',
                'ocelot/transforms/implementation/ReadableLayoutPass.cpp' ]
                
ocelot_dep_headers = [  'ocelot/analysis/interface/Analysis.h',
                        'ocelot/analysis/interface/AnalysisFactory.h',
                        'ocelot/analysis/interface/BranchInfo.h',
                        'ocelot/analysis/interface/ControlTree.h',
                        'ocelot/analysis/interface/DataflowGraph.h',
                        'ocelot/analysis/interface/DirectionalGraph.h',
                        'ocelot/analysis/interface/DivergenceAnalysis.h',
                        'ocelot/analysis/interface/DivergenceGraph.h',
                        'ocelot/analysis/interface/DominatorTree.h',
                        'ocelot/analysis/interface/PostdominatorTree.h',
                        'ocelot/analysis/interface/SSAGraph.h',
                        'ocelot/cuda/interface/FatBinaryContext.h',
                        'ocelot/cuda/interface/cudaFatBinary.h',
                        'ocelot/ir/interface/ControlFlowGraph.h',
                        'ocelot/ir/interface/Dim3.h',
                        'ocelot/ir/interface/Global.h',
                        'ocelot/ir/interface/Instruction.h',
                        'ocelot/ir/interface/IRKernel.h',
                        'ocelot/ir/interface/Kernel.h',
                        'ocelot/ir/interface/Local.h',
                        'ocelot/ir/interface/Module.h',
                        'ocelot/ir/interface/Parameter.h',
                        'ocelot/ir/interface/PTXEmitter.h',   
                        'ocelot/ir/interface/PTXInstruction.h',
                        'ocelot/ir/interface/PTXKernel.h',
                        'ocelot/ir/interface/PTXOperand.h',
                        'ocelot/ir/interface/PTXStatement.h',
                        'ocelot/ir/interface/Texture.h',
                        'ocelot/parser/interface/Parser.h',
                        'ocelot/parser/interface/PTXLexer.h',
                        'ocelot/parser/interface/PTXParser.h',
                        'ocelot/transforms/interface/Pass.h',
                        'ocelot/transforms/interface/PassFactory.h',
                        'ocelot/transforms/interface/PassManager.h',
                        'ocelot/transforms/interface/ReadableLayoutPass.h' ]
                
ocelot_dir = ['ocelot/analysis/implementation', 'ocelot/analysis/interface',
                'ocelot/cuda/implementation', 'ocelot/cuda/interface',
                'ocelot/ir/implementation', 'ocelot/ir/interface',
                'ocelot/parser/implementation', 'ocelot/parser/interface',
                'ocelot/transforms/implementation', 'ocelot/transforms/interface']
   
   
# find all flex/bison sources
flex_sources  = ['ocelot/parser/implementation/ptx.ll']
bison_sources = ['ocelot/parser/implementation/ptxgrammar.yy']   
                
                
def buildCJIT():

    #Create variables out of shell commands
    cercs_env = "cd c-jit/cercs_env; ./configure && make && sudo make install"
    atl = "cd c-jit/atl; ./configure && make && sudo make install"
    fm = "cd c-jit/ffs/fm; ./configure && make && sudo make install"
    dill = "cd c-jit/dill; ./configure && make && sudo make install"
    cod = "cd c-jit/ffs/cod; ./configure && make && sudo make install"

    #Places variables into a list/array
    cmds = [cercs_env, atl, fm, dill, cod]
    libs = ["/usr/local/lib/libcercs_env.so", "/usr/local/lib/libatl.so", "/usr/local/lib/libfm.so", "/usr/local/lib/libdill.so", "/usr/local/lib/libcod.so"]

    #Iterates over list, running statements for each item in the list
    i = 0
    while (i < 5):
        if not os.path.exists(libs[i]):
            call(cmds[i], shell=True)    
        i = i + 1               
                
# obtain ocelot/hydrazine dependencies from svn
def ocelotDependencies():

    print "[OCELOT DEPENDENCIES] begin ..."
    
    svn_ocelot = 'svn export http://gpuocelot.googlecode.com/svn/trunk/ocelot/'
    svn_hydrazine = 'svn export http://hydrazine.googlecode.com/svn/trunk/hydrazine'
    
    if not os.path.exists("ocelot"):   
        for dir in ocelot_dir:
            Execute(Mkdir(dir))
            
        for file in ocelot_dep_headers:
            cmd = svn_ocelot + file + ' ' + file;
            call(cmd, shell=True)
        for file in ocelot_dep:
            cmd = svn_ocelot + file + ' ' + file;
            call(cmd, shell=True)
        for file in flex_sources:
            cmd = svn_ocelot + file + ' ' + file;
            call(cmd, shell=True)
        for file in bison_sources:
            cmd = svn_ocelot + file + ' ' + file;
            call(cmd, shell=True)

    if not os.path.exists("hydrazine"):
        call(svn_hydrazine + ' hydrazine',
        shell=True)

    print "[OCELOT DEPENDENCIES] done."
    
    
# build C-JIT and ocelot dependencies
buildCJIT()    
ocelotDependencies()
   

# Generate the flex/bison .c/.cpp files
for source in flex_sources:
	lex = env.CXXFile(os.path.splitext(os.path.basename(str(source)))[0] \
		+ '.cpp', str(source))
	sources.append(lex[0])

for source in bison_sources:
	bison = env.CXXFile(os.path.splitext(os.path.basename(str(source)))[0] \
		+ '.cpp', str(source))
	sources.append(bison[0])
	bison_header = bison[1]
	intermediate_headers.append(os.path.basename(str(bison_header)))

extensions = ['*.cpp']

for dir in directories:
	for ext in extensions:
		regexp = os.path.join(dir, ext)
		sources.extend(env.Glob(regexp))


for file in ocelot_dep:
    sources.append(file)

# Create the lynx library
lynx_dep_libs = env['EXTRA_LIBS']


if env['library'] == 'shared':
    liblynxruntime = env.SharedLibrary('lynx_runtime', sources, LIBS=lynx_dep_libs)
else:
    liblynxruntime = env.StaticLibrary('lynx_runtime', sources, LIBS=lynx_dep_libs)

# find all header files in the source tree
headers = []
directories = [ 'lynx/api/interface',
                'lynx/cuda/interface',
                'lynx/instrumentation/interface',   
                'lynx/transforms/interface',
                'lynx/translator/interface', 
                'lynx/trace/interface',

                'hydrazine/interface' ]
extensions = ['*.h', '*.hpp']

for dir in directories:
	for ext in extensions:
		regexp = os.path.join(dir, ext)
		headers.extend(env.Glob(regexp))

for file in ocelot_dep_headers:
    headers.extend(env.Glob(file))


lib_objs = []
lib_source_dir = [ 'lynx/api/implementation',
                    'lynx/instrumentation/implementation',   
                    'lynx/transforms/implementation',
                    'lynx/translator/implementation',
                    'lynx/trace/implementation']
                    
extensions = ['*.os']

for dir in lib_source_dir:
	for ext in extensions:
		regexp = os.path.join(dir, ext)
		lib_objs.extend(env.Glob(regexp))

liblynx = env.SharedLibrary('lynx', lib_objs, LIBS=[lib for lib in lynx_dep_libs if lib != '-lcuda'])

if 'install' in COMMAND_LINE_TARGETS:
	liblynxruntime = env.Install(os.path.join(env['install_path'], "lib"), liblynxruntime)
	liblynx = env.Install(os.path.join(env['install_path'], "lib"), liblynx)

# Install rules
if 'install' in COMMAND_LINE_TARGETS:
	print 'Installing lynx (library and runtime)...'
	installed = []
	installed.append(liblynxruntime)
	installed.append(liblynx)
	
	for header in headers:
		(directoryPath, headerName) = os.path.split( \
			os.path.relpath(str(header), prefix))
		installed.append(env.Install(os.path.join( \
			env['install_path'], "include", directoryPath), header))

	for header in intermediate_headers:
		(directoryPath, headerName) = os.path.split( \
			os.path.relpath(str(header), '.'))
		installed.append(env.Install(os.path.join( \
			env['install_path'], "include", directoryPath), header))

	for i in installed:
		env.AddPostAction(str(i), Chmod(str(i), 0644))
	
	env.Alias('install', env['install_path'])

	env.Replace(installed_files = installed)

	Export('env')

