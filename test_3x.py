
import smhasher
import timeit

print('smhasher version %s' % smhasher.__version__)

# without seed
print(smhasher.murmur3_x86_64('samplebias'))
# with seed value
print(smhasher.murmur3_x86_64('samplebias', 123))

# 128-bit hashes
print('128-bit x64: %s' % smhasher.murmur3_x64_128('samplebias'))
print('128-bit x86: %s' % smhasher.murmur3_x86_128('samplebias'))

# timing comparison with str __hash__
t = timeit.Timer("smhasher.murmur3_x86_64('hello')", "import smhasher")
print('smhasher.murmur3:', t.timeit())

t = timeit.Timer("str.__hash__('hello')")
print('str.__hash__:', t.timeit())

