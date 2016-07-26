#pragma once
#include <cstddef>
#include <new>
#include <iostream>



namespace li
{

	template<class T>
	class allocator
	{
	public:
		typedef T            value_type;
		typedef T*           pointer;
		typedef const T*     const_pointer;
		typedef T&           reference;
		typedef const T&     const_reference;
		typedef size_t       size_type;
		typedef ptrdiff_t    difference_type;
		template<class U>
		struct rebind
		{
			typedef allocator<U> other;
		};



		//默认构造函数
		allocator();

		//复制构造函数
		allocator(const allocator&);

		//从类型U对象的分配器中构造T类型对象的分配器
		template<class U>allocator(const allocator<U>&);

		//析构函数
		~allocator();

		//返回指向引用对象x的指针。特别的，它返回&x
		pointer address(reference x)const
		{
			return (pointer)&x;
		}
		const_pointer address(const_reference x)const
		{
			return (const_pointer)&x;
		}

		//为类型value_type的n个对象分配内存，但不构造对象,hint指示引用位置
		pointer allocate(size_type n, typename allocator<void>::const_pointer hint = 0)
		{
			pointer temp = (pointer)(::operator new ((size_t)(n*sizeof(value_type))));
			if (temp == 0)
			{
				throw std::bad_alloc();
			}
			return temp;
		}


		//使用全局delete运算符释放指针p所指向的所有内存空间，在此之前应销毁该区域所有的对象
		void deallocate(pointer p, size_type n)
		{
			::operator delete(p);
		}

		//返回allocate(N)可能成功的最大的正N值
		size_type max_size()
		{
			return size_type(UINT_MAX / sizeof(T));
		}

		//通过执行new((void*)p)T(val)来构造P所指示内存中val的副本
		void construct(pointer p, const T& val)
		{
			new (p) value_type(val);
		}

		//通过执行((T*)p)->~T()来销毁p指示的对象
		void destroy(pointer p)
		{
			p->~value_type();
		}

		//allocator没有内部数据，总具有相同功能，故总为true
		template<class T>
		bool operator==(const allocator<T>&) { return true; };

		template<class T>
		bool operator!=(const allocator<T>&) { return false; };


	};



	template<class T>
	inline allocator<T>::allocator()
	{
	}

	template<class T>
	inline allocator<T>::allocator(const allocator &)
	{
	}

	template<class T>
	inline allocator<T>::~allocator()
	{
	}



	//       void 的特化版本

	template<>
	class allocator<void>
	{
	public:
		typedef void*                    pointer;
		typedef const void*              const_pointer;
		typedef void                     value_type;
		template<typename U>
		struct rebind
		{
			typedef allocator<U> other;
		};
	};

}