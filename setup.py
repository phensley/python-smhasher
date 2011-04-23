
from distutils.core import setup, Extension

murmur_ext = Extension('murmur3', sources=[
    'murmur3.cpp',
    'smhasher/MurmurHash3.cpp',
    'smhasher/Platform.cpp'
    ], include_dirs=['smhasher'])

setup(
    name='murmur3',
    version=0.1,
    description='Python extension for murmur3 hash',
    ext_modules=[murmur_ext]
    )

