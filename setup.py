
from distutils.core import setup, Extension

# version number is x.[upstream svn revision].release until upstream
# creates a formal version number.
VERSION = '0.135.4'


import os
import platform
if platform.machine() == 'i386':
  os.environ['ARCHFLAGS']='-arch i386 -arch x86_64'
# python in os x will use -arch flags that will attempt to make a universal ppc
# binary. explicitly set the archflags here.


smhasher_ext = Extension('smhasher',
    sources=[
        'smhasher.cpp',
        'smhasher/MurmurHash3.cpp',
        'smhasher/Platform.cpp'
    ],
    include_dirs=['smhasher'],
    define_macros=[('MODULE_VERSION', '"%s"' % VERSION)])

setup(
    name='smhasher',
    version='0.1',
    description='Python extension for smhasher hash functions',
    ext_modules=[smhasher_ext]
    )

