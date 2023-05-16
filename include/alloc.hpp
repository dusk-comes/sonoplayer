#include <cstdlib>
#include <limits>
#include <new>
#include <fftw3.h>
 
namespace fft
{
    template <class T>
    struct alloc_real
    {
        using size_type = std::size_t;
        using value_type = T;
     
        alloc_real() = default;
        ~alloc_real() = default;
     
        template <class U>
        constexpr alloc_real (const alloc_real <U>&) noexcept {}
    
        template <typename U>
        struct rebind { using other = alloc_real<U>; };
     
        [[nodiscard]] T* allocate(size_type n)
        {
            if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
                throw std::bad_array_new_length();
     
            if (auto p = static_cast<T*>(fftw_alloc_real(n * sizeof(T))))
            {
                return p;
            }
     
            throw std::bad_alloc();
        }
     
        void deallocate(T* p, [[maybe_unused]] size_type n) noexcept
        {
            fftw_free(p);
        }
    };

    template <class T>
    struct alloc_complex
    {
        using size_type = std::size_t;
        using value_type = T;
     
        alloc_complex() = default;
        ~alloc_complex() = default;
     
        template <class U>
        constexpr alloc_complex (const alloc_complex <U>&) noexcept {}
    
        template <typename U>
        struct rebind { using other = alloc_complex<U>; };
     
        [[nodiscard]] T* allocate(size_type n)
        {
            if (n > std::numeric_limits<std::size_t>::max() / sizeof(T))
                throw std::bad_array_new_length();
     
            if (auto p = reinterpret_cast<T*>(fftw_alloc_complex(n * sizeof(T))))
            {
                return p;
            }
     
            throw std::bad_alloc();
        }
     
        void deallocate(T* p, [[maybe_unused]] size_type n) noexcept
        {
            fftw_free(p);
        }
    };
}
 
template<class T, class U>
bool operator==(const fft::alloc_real <T>&, const fft::alloc_real <U>&) { return true; }
 
template<class T, class U>
bool operator!=(const fft::alloc_real <T>&, const fft::alloc_real <U>&) { return false; }

template<class T, class U>
bool operator==(const fft::alloc_complex <T>&, const fft::alloc_complex <U>&) { return true; }
 
template<class T, class U>
bool operator!=(const fft::alloc_complex <T>&, const fft::alloc_complex <U>&) { return false; }
