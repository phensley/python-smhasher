
import murmur3
import timeit

print murmur3.murmur3_x86_64('samplebias', 0)
print murmur3.murmur3_x86_64('samplebias', 123)
print murmur3.murmur3_x64_64('samplebias', 0)
print murmur3.murmur3_x64_64('samplebias', 123)

t = timeit.Timer("murmur3.murmur3_x86_64('hello')", "import murmur3")
print t.timeit()

t = timeit.Timer("str.__hash__('hello')")
print t.timeit()

