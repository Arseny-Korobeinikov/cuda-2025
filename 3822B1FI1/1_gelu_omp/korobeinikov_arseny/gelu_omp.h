#ifndef __GELU_OMP_H
#define __GELU_OMP_H

#include <cstdlib>
#include <vector>

#ifdef _WIN32
#define aligned_alloc(ALIGN, SIZE) _aligned_malloc(SIZE, ALIGN)
#define aligned_free(PTR) _aligned_free(PTR)
#else
#define aligned_alloc(ALIGN, SIZE) std::aligned_alloc(ALIGN, SIZE)
#define aligned_free(PTR) std::free(PTR)
#endif

template <typename T, std::size_t N = 16>
class AlignedAllocator {
  public:
    typedef T value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    typedef T * pointer;
    typedef const T * const_pointer;

    typedef T & reference;
    typedef const T & const_reference;

    inline AlignedAllocator() throw () { }

    template <typename T2>
    inline AlignedAllocator(const AlignedAllocator<T2, N> &) throw () { }

    inline ~AlignedAllocator() throw () { }

    inline pointer adress(reference r) {
        return &r;
    }

    inline const_pointer adress(const_reference r) const {
        return &r;
    }

    inline pointer allocate(size_type n) {
        return (pointer)aligned_alloc(N, n * sizeof(value_type));
    }

    inline void deallocate(pointer p, size_type) {
        aligned_free(p);
    }

    inline void construct(pointer p, const value_type & wert) {
        new (p) value_type(wert);
    }

    inline void destroy(pointer p) {
        p->~value_type();
    }

    inline size_type max_size () const throw () {
        return size_type(-1) / sizeof(value_type);
    }

    template <typename T2>
    struct rebind {
        typedef AlignedAllocator<T2, N> other;
    };

    bool operator!=(const AlignedAllocator<T,N>& other) const  {
        return !(*this == other);
    }

    bool operator==(const AlignedAllocator<T,N>& other) const {
        return true;
    }
};

using AlignedVector = std::vector<float, AlignedAllocator<float, 128>>;

AlignedVector GeluOMP(const AlignedVector& input);

#endif // __GELU_OMP_H