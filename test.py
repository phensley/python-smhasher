
import murmur3
import timeit

# without seed
print murmur3.murmur3_x86_64('samplebias')
# with seed value
print murmur3.murmur3_x86_64('samplebias', 123)

# timing comparison with str __hash__
t = timeit.Timer("murmur3.murmur3_x86_64('hello')", "import murmur3")
print 'murmur3:', t.timeit()

t = timeit.Timer("str.__hash__('hello')")
print 'str.__hash__:', t.timeit()

