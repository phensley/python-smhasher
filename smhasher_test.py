
import smhasher
import timeit

print('smhasher version: %s\n\n' % smhasher.__version__)

def demo(name, seed=None):
    text = 'samplebias'
    func = getattr(smhasher, name)
    msg = name
    if seed:
        msg += ' seed: %d' % seed
        res = func(text, seed)
    else:
        res = func(text)
    print('%s\n  %d\n  %s\n' % (msg, res, hex(res)))

demo('murmur3_x86_64')
demo('murmur3_x86_64', 123)

demo('murmur3_x86_128')
demo('murmur3_x64_128')
demo('murmur3_x86_128', 123456789)


# timing comparison with str __hash__
t = timeit.Timer("smhasher.murmur3_x86_64('hello')", "import smhasher")
print('smhasher.murmur3:', t.timeit())

t = timeit.Timer("str.__hash__('hello')")
print('    str.__hash__:', t.timeit())

