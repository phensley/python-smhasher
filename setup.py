
import os
import platform
import sys
from distutils.core import setup, Extension

# version number is x.[upstream svn revision].release until upstream
# creates a formal version number.
VERSION = '0.150.1'

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


if __name__ == '__main__':
    # load README.txt for the long description
    cwd = os.path.dirname(os.path.abspath(__file__))
    path = os.path.join(cwd, 'README.txt')
    short_desc = 'Python extension for smhasher hash functions'
    long_desc = short_desc
    if os.path.exists(path):
        long_desc = open(path, 'r').read()

    # call setup
    setup(
        name = 'smhasher',
        version = VERSION,
        description = short_desc,
        author = 'Patrick Hensley',
        author_email = 'spaceboy@indirect.com',
        keywords = ['hash', 'hashing', 'smhasher'],
        url = "http://github.com/phensley/python-smhasher",
        ext_modules = [smhasher_ext],
        classifiers = [
            "Development Status :: 4 - Beta",
            "Intended Audience :: Developers",
            "License :: OSI Approved :: MIT License",
            "Operating System :: MacOS :: MacOS X",
            "Operating System :: POSIX :: Linux",
            "Operating System :: Unix",
            "Programming Language :: Python",
            "Programming Language :: Python :: 2.4",
            "Programming Language :: Python :: 2.5",
            "Programming Language :: Python :: 2.6",
            "Programming Language :: Python :: 2.7",
            "Programming Language :: Python :: 3",
            "Programming Language :: Python :: 3.1",
            "Topic :: Software Development :: Libraries :: Python Modules",
            ],
        long_description = long_desc
        )

