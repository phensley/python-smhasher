
import os
import platform
import sys
from distutils.core import setup, Extension

# version number is x.[upstream svn revision].release until upstream
# creates a formal version number.
VERSION = '0.136.1'

# avoid building universal binary (ppc) on osx non-ppc platforms
if sys.platform == 'darwin':
    arch = platform.machine()
    if arch in ('i386', 'x86_64'):
        os.environ['ARCHFLAGS'] = '-arch i386 -arch x86_64'

smhasher_ext = Extension('smhasher',
    sources=[
        'smhasher.cpp',
        'smhasher/MurmurHash3.cpp',
        ],
    include_dirs=['smhasher'],
    define_macros=[('MODULE_VERSION', '"%s"' % VERSION)])


setup(
    name='smhasher',
    version=VERSION,
    description='Python extension for smhasher hash functions',
    ext_modules=[smhasher_ext]
    )

