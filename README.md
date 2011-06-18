
`python-smhasher` is a Python 2.x/3.x wrapper for the 
[SMHasher](http://code.google.com/p/smhasher/) non-cryptographic hashing
library.  It currently supports the MurmurHash3 64-/128-bit and x86/x64
variants.

License: MIT License

Usage
-----

    >>> import smhasher
    >>> [k for k in dir(smhasher) if k[0] == 'm']
    ['murmur3_x64_128', 'murmur3_x64_64', 'murmur3_x86_128', 'murmur3_x86_64']

    >>> smhasher.murmur3_x86_128('hello')
    213030289162235495270783145757721615258L

    >>> seed = 1138
    >>> smhasher.murmur3_x86_128('hello', seed)
    94758481705480737162820094006203962724L

