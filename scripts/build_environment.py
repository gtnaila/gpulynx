EnsureSConsVersion(1,2)

import os

import inspect
import platform
import re
import subprocess
from SCons import SConf

def getDebianArchitecture():
	"""Determines the debian architecture
	
	return {deb_arch}
	"""

	# check for supported OS
	if os.name != 'posix':
		raise ValueError, 'Error: unknown OS.  Can only build .deb on linux.'
	
	try:
		dpkg_arch_path = which('dpkg-architecture')
	except:
		raise ValueError, "Failed to find 'dpkg-architecture' needed for .deb" \
			". Try installing dpkg-dev"

	# setup .deb environment variables
	arch = os.popen( \
		'dpkg-architecture -c \'echo $DEB_BUILD_ARCH\'').read().split()

	if len(arch) == 0:
		raise ValueError, 'Failed to get architecture from dpkg-architecture'

	return arch[0]

def getCudaPaths():
	"""Determines CUDA {bin,lib,include} paths
	
	returns (bin_path,lib_path,inc_path)
	"""

	# determine defaults
	if os.name == 'posix':
		bin_path = '/usr/local/cuda/bin'
		lib_path = '/usr/local/cuda/lib'
		inc_path = '/usr/local/cuda/include'
	else:
		raise ValueError, 'Error: unknown OS.  Where is nvcc installed?'
	 
	if platform.machine()[-2:] == '64':
		lib_path += '64'

	# override with environement variables
	if 'CUDA_BIN_PATH' in os.environ:
		bin_path = os.path.abspath(os.environ['CUDA_BIN_PATH'])
	if 'CUDA_LIB_PATH' in os.environ:
		lib_path = os.path.abspath(os.environ['CUDA_LIB_PATH'])
	if 'CUDA_INC_PATH' in os.environ:
		inc_path = os.path.abspath(os.environ['CUDA_INC_PATH'])

	return (bin_path,lib_path,inc_path)

def getBoostPaths():
	"""Determines BOOST {bin,lib,include} paths
	
	returns (bin_path,lib_path,inc_path)
	"""

	# determine defaults
	if os.name == 'posix':
		bin_path = '/usr/bin'
		lib_path = '/usr/lib'
		inc_path = '/usr/include'
	else:
		raise ValueError, 'Error: unknown OS.  Where is boost installed?'

	# override with environement variables
	if 'BOOST_BIN_PATH' in os.environ:
		bin_path = os.path.abspath(os.environ['BOOST_BIN_PATH'])
	if 'BOOST_LIB_PATH' in os.environ:
		lib_path = os.path.abspath(os.environ['BOOST_LIB_PATH'])
	if 'BOOST_INC_PATH' in os.environ:
		inc_path = os.path.abspath(os.environ['BOOST_INC_PATH'])

	return (bin_path,lib_path,inc_path)

def getFlexPaths(env):
	"""Determines Flex {include} paths

	returns (inc_path)
	"""

	# determine defaults
	if os.name == 'posix':
		inc_path = ['/usr/include']
	else:
		raise ValueError, 'Error: unknown OS.  Where is FLEX installed?'

	# override with environement variables
	if 'FLEX_INC_PATH' in os.environ:
		inc_path = os.path.abspath(os.environ['FLEX_INC_PATH'])

	return (inc_path)
	
def getTools():
	result = []
	if os.name == 'posix':
		result = ['default', 'c++', 'g++']
	else:
		result = ['default']

	return result;

OldEnvironment = Environment;


# this dictionary maps the name of a compiler program to a dictionary mapping the name of
# a compiler switch of interest to the specific switch implementing the feature
gCompilerOptions = {
		'gcc' : {'warn_all' : '-Wall',
			'warn_errors' : '-Werror',
			'optimization' : '-O2', 'debug' : '-g',  
			'exception_handling' : '', 'standard': ''},
		'g++' : {'warn_all' : '-Wall',
			'warn_errors' : '-Werror',
			'optimization' : '-O2', 'debug' : '-g', 
			'exception_handling' : '', 'standard': '-std=c++0x'},
		'c++' : {'warn_all' : '-Wall',
			'warn_errors' : '-Werror',
			'optimization' : '-O2', 'debug' : '-g',
			'exception_handling' : '',
			'standard': ['-stdlib=libc++', '-std=c++0x', '-pthread']},
		'cl'  : {'warn_all' : '/Wall',
			'warn_errors' : '/WX',
			'optimization' : ['/Zi', '/Ox', '/DNDEBUG'],
			'debug' : ['/Zi', '/Od', '/D_DEBUG', '/RTC1'],
			'exception_handling': '/EHsc',
			'standard': ['/GS', '/GR', '/Gd', '/fp:precise',
				'/Zc:wchar_t','/Zc:forScope', '/DYY_NO_UNISTD_H',
				'/D_WIN32_WINNT=0x0601', '/wd4482', '/wd4503']}
	}

# this dictionary maps the name of a linker program to a dictionary mapping the name of
# a linker switch of interest to the specific switch implementing the feature
gLinkerOptions = {
		'gcc'  : {'debug' : '-Wl,-soname,libcudart.so'},
		'g++'  : {'debug' : '-Wl,-soname,libcudart.so'},
		'c++'  : {'debug' : ''},
		'link' : {'debug' : '/debug'}
	}


def getCFLAGS(mode, warn, warnings_as_errors, CC):
	result = ['-fPIC']
	if mode == 'release':
		# turn on optimization
		result.append(gCompilerOptions[CC]['optimization'])
	elif mode == 'debug':
		# turn on debug mode
		result.append(gCompilerOptions[CC]['debug'])
		result.append('-DLYNX_DEBUG')

	if warn:
		# turn on all warnings
		result.append(gCompilerOptions[CC]['warn_all'])

	if warnings_as_errors:
		# treat warnings as errors
		result.append(gCompilerOptions[CC]['warn_errors'])

	result.append(gCompilerOptions[CC]['standard'])

	return result

def getLibCXXPaths():
	"""Determines libc++ path

	returns (inc_path, lib_path)
	"""

	# determine defaults
	if os.name == 'posix':
		inc_path = '/usr/include'
		lib_path = '/usr/lib/libc++.so'
	else:
		raise ValueError, 'Error: unknown OS.  Where is libc++ installed?'

	# override with environement variables
	if 'LIBCXX_INC_PATH' in os.environ:
		inc_path = os.path.abspath(os.environ['LIBCXX_INC_PATH'])
	if 'LIBCXX_LIB_PATH' in os.environ:
		lib_path = os.path.abspath(os.environ['LIBCXX_LIB_PATH'])

	return (inc_path, lib_path)

def getCXXFLAGS(mode, warn, warnings_as_errors, CXX):
	result = []
	if mode == 'release':
		# turn on optimization
		result.append(gCompilerOptions[CXX]['optimization'])
	elif mode == 'debug':
		# turn on debug mode
		result.append(gCompilerOptions[CXX]['debug'])
	# enable exception handling
	result.append(gCompilerOptions[CXX]['exception_handling'])

	if warn:
		# turn on all warnings
		result.append(gCompilerOptions[CXX]['warn_all'])

	if warnings_as_errors:
		# treat warnings as errors
		result.append(gCompilerOptions[CXX]['warn_errors'])

	result.append(gCompilerOptions[CXX]['standard'])

	return result

def getLINKFLAGS(mode, LINK):
	result = []
	if mode == 'debug':
		# turn on debug mode
		result.append(gLinkerOptions[LINK]['debug'])

	if LINK == 'c++':
		result.append(getLibCXXPaths()[1]);

	return result

def getExtraLibs():
		return ['-lboost_thread', '-lcuda', '-lcod', '-latl', '-lfm', '-ldill']


def fixPath(path):
		return path
 

def importEnvironment():
	env = {  }
	
	if 'PATH' in os.environ:
		env['PATH'] = os.environ['PATH']
	
	if 'CXX' in os.environ:
		env['CXX'] = os.environ['CXX']
	
	if 'CC' in os.environ:
		env['CC'] = os.environ['CC']
	
	if 'TMP' in os.environ:
		env['TMP'] = os.environ['TMP']
	
	if 'LD_LIBRARY_PATH' in os.environ:
		env['LD_LIBRARY_PATH'] = os.environ['LD_LIBRARY_PATH']

	return env


def Environment():
	vars = Variables()

	# add a variable to handle RELEASE/DEBUG mode
	vars.Add(EnumVariable('mode', 'Release versus debug mode', 'release',
		allowed_values = ('release', 'debug')))

	# add a variable to handle warnings
	vars.Add(BoolVariable('Wall', 'Enable all compilation warnings', 1))
	
	# shared or static libraries
	libraryDefault = 'shared'
	
	vars.Add(EnumVariable('library', 'Build shared or static library',
		libraryDefault, allowed_values = ('shared', 'static')))
	
	# add a variable to treat warnings as errors
	vars.Add(BoolVariable('Werror', 'Treat warnings as errors', 1))
	

	# add a variable to determine the install path
	default_install_path = '/usr/local'
	
	vars.Add(PathVariable('install_path', 'The lynx install path',
		default_install_path))

	# create an Environment
	env = OldEnvironment(ENV = importEnvironment(), \
		tools = getTools(), variables = vars)

	# get the absolute path to the directory containing
	# this source file
	thisFile = inspect.getabsfile(Environment)
	thisDir = os.path.dirname(thisFile)

	# get C compiler switches
	env.AppendUnique(CFLAGS = getCFLAGS(env['mode'], env['Wall'], \
		env['Werror'], env.subst('$CC')))

	# get CXX compiler switches
	env.AppendUnique(CXXFLAGS = getCXXFLAGS(env['mode'], env['Wall'], \
		env['Werror'], env.subst('$CXX')))

	# get linker switches
	env.AppendUnique(LINKFLAGS = getLINKFLAGS(env['mode'], env.subst('$LINK')))

	# get bison switches
	env.AppendUnique(YACCFLAGS = "-d")
	
	# Install paths
	if 'install' in COMMAND_LINE_TARGETS:
		env.Replace(INSTALL_PATH = os.path.abspath(env['install_path']))
	else:
		env.Replace(INSTALL_PATH = os.path.abspath('.'))

	# Set the debian architecture
	if 'debian' in COMMAND_LINE_TARGETS:
		env.Replace(deb_arch = getDebianArchitecture())
	else:
		env.Replace(deb_arch = 'unknown')
		
	# get CUDA paths
	(cuda_exe_path, cuda_lib_path, cuda_inc_path)  = getCudaPaths()
	env.AppendUnique(LIBPATH = [cuda_lib_path, '/usr/lib/nvidia-304'])
	env.AppendUnique(CPPPATH = [cuda_inc_path])

	
	# CUDA builder
	env.Append(BUILDERS = {'Cuda': Builder(
		action=cuda_exe_path + '/nvcc -arch=sm_20 $SOURCE -c -o $TARGET',
		suffix = '.o',
		src_suffix = '.cu'
	)})

  # CUDA builder
	nvccPath = cuda_exe_path + ('/' if cuda_exe_path != '' else '')
	env.Append(BUILDERS = {'Cuda': Builder(
		action= nvccPath + 'nvcc -arch=sm_20 $SOURCE -c -o $TARGET',
		suffix = '.o',
		src_suffix = '.cu'
	)})
	
	# include the build directory in case of generated files
	env.Prepend(CPPPATH = env.Dir('.'))

	# get boost paths
	(boost_exe_path,boost_lib_path,boost_inc_path) = getBoostPaths()
	env.AppendUnique(LIBPATH = [boost_lib_path])
	env.AppendUnique(CPPPATH = [boost_inc_path])
    
	# get Flex paths
	(flex_inc_path) = getFlexPaths(env)
	env.AppendUnique(CPPPATH = [flex_inc_path])

	# get libc++
	if env['CXX'] == 'c++':
		env.AppendUnique(CPPPATH = getLibCXXPaths()[0])


	# set lynx include path
	env.Prepend(CPPPATH = os.path.dirname(thisDir))
	env.AppendUnique(LIBPATH = os.path.abspath('.'))
	
	# set extra libs 
	env.Replace(EXTRA_LIBS=getExtraLibs())
	
	# we need libdl on linux, and librt
	if os.name == 'posix':
		env.AppendUnique(EXTRA_LIBS = ['-ldl', '-lrt']) 
	
	# set lynx libs
	lynx_libs = '-llynx'

	# generate help text
	Help(vars.GenerateHelpText(env))

	return env

