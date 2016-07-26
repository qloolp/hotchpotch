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



		//Ĭ�Ϲ��캯��
		allocator();

		//���ƹ��캯��
		allocator(const allocator&);

		//������U����ķ������й���T���Ͷ���ķ�����
		template<class U>allocator(const allocator<U>&);

		//��������
		~allocator();

		//����ָ�����ö���x��ָ�롣�ر�ģ�������&x
		pointer address(reference x)const
		{
			return (pointer)&x;
		}
		const_pointer address(const_reference x)const
		{
			return (const_pointer)&x;
		}

		//Ϊ����value_type��n����������ڴ棬�����������,hintָʾ����λ��
		pointer allocate(size_type n, typename allocator<void>::const_pointer hint = 0)
		{
			pointer temp = (pointer)(::operator new ((size_t)(n*sizeof(value_type))));
			if (temp == 0)
			{
				throw std::bad_alloc();
			}
			return temp;
		}


		//ʹ��ȫ��delete������ͷ�ָ��p��ָ��������ڴ�ռ䣬�ڴ�֮ǰӦ���ٸ��������еĶ���
		void deallocate(pointer p, size_type n)
		{
			::operator delete(p);
		}

		//����allocate(N)���ܳɹ���������Nֵ
		size_type max_size()
		{
			return size_type(UINT_MAX / sizeof(T));
		}

		//ͨ��ִ��new((void*)p)T(val)������P��ָʾ�ڴ���val�ĸ���
		void construct(pointer p, const T& val)
		{
			new (p) value_type(val);
		}

		//ͨ��ִ��((T*)p)->~T()������pָʾ�Ķ���
		void destroy(pointer p)
		{
			p->~value_type();
		}

		//allocatorû���ڲ����ݣ��ܾ�����ͬ���ܣ�����Ϊtrue
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



	//       void ���ػ��汾

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