################################################################################
#	\file   SConstruct
#	\author Naila Farooqui naila@cc.gatech.edu>
#   \date   Monday June 25, 2012
#	\brief  The SCons master build script for Lynx (borrowed from Ocelot)
################################################################################

if ARGUMENTS.get('mode', 'release') == 'debug':
	SConscript('SConscript', variant_dir='.debug_build',   duplicate=0, 
		exports={'mode':'debug'})
else:
	SConscript('SConscript', variant_dir='.release_build', duplicate=0,
		exports={'mode':'release'})


