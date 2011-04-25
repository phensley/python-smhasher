
import smhasher
import timeit

print 'smhasher version', smhasher.__version__

# without seed
print smhasher.murmur3_x86_64('samplebias')
# with seed value
print smhasher.murmur3_x86_64('samplebias', 123)

# timing comparison with str __hash__
t = timeit.Timer("smhasher.murmur3_x86_64('hello')", "import smhasher")
print 'smhasher.murmur3:', t.timeit()

t = timeit.Timer("str.__hash__('hello')")
print 'str.__hash__:', t.timeit()

