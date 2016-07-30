#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include<new>
#include<cstddef>
#include<limits>
#include<cstdlib>

namespace li
{

    template<class T>
    class allocator
    {
    public:
        typedef size_t                size_type;
        typedef ptrdiff_t             difference_type;
        typedef T*                    pointer;
        typedef const T*              const_pointer;
        typedef T&                    reference;
        typedef const T&              const_reference;
        typedef T                     value_type;

        template<class U>
        struct rebind
        {typedef allocator<U> other;};

        allocator(){}

        allocator(const allocator&){}

        template<class U>
        allocator(const allocator<U>&){}

        ~allocator(){}

         pointer address(reference x)const
        {return &x;}

         const_pointer address(const_reference x)const
        {return &x;}

        static pointer allocate(size_type n, const void* = 0)
        {
           if(n>allocator::max_size())
             throw std::bad_alloc();
            return static_cast<T*>(::operator new(n*sizeof(T)));
        }

        static void deallocate(pointer p)
        {::operator delete(p);}





        static size_type max_size()
        {return size_t(-1)/sizeof(T);}

        static void construct(pointer p, const T& val)
        {::new((void*)p)T(val);}


        static void destroy(pointer p){p->~T();}

    };

    template<class T>
    inline bool
    operator==(const allocator<T>&, const allocator<T>&)
    {return true;}

    template<class T>
    inline bool
    operator!=(const allocator<T>&, const allocator<T>&)
    {return false;}

}

#endif // ALLOCATOR_H


