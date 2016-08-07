#ifndef VECTOR_H
#define VECTOR_H
#include "allocator.h"
#include <memory>
#include <cstddef>
#include <bits/stl_iterator_base_funcs.h>


namespace li
{
    template<class T, class Allocator = li::allocator<T> >
    class vector
    {
    public:                            //STL标准规定
        typedef T*            iterator;                   //因为是基于数组的，所以传统指针即具有迭代器功能                   
        typedef const T*      const_iterator;
        typedef T&            reference;
        typedef const T&      const_reference;
        typedef T*            pointer;
        typedef const T*      const_pointer;
        typedef size_t        size_type;
        typedef ptrdiff_t     difference_type;
        typedef T             value_type;

    protected:
        typedef Allocator     allocator_type;
        iterator start;
        iterator finish;
        iterator end_of_storage;
        void insert_aux(iterator position, const T& x)            //插入，若空间不够则申请新的空间，并拷贝原有内容
        {
            if(finish != end_of_storage)
            {
                allocator<T>::construct(finish,*(finish-1));
                ++finish;
                T x_copy = x;
                std::copy_backward(position,finish-2,finish-1);
                *position = x_copy;
            }
            else
            {
                const size_type old_size = size();
                const size_type len = old_size!=0?2*old_size:1;
                iterator new_start = allocator<T>::allocate(len);
                iterator new_finish = new_start;
                try
                {
                    new_finish = std::uninitialized_copy(start,position,new_start);
                    allocator<T>::construct(new_finish,x);
                    ++new_finish;
                    new_finish = std::uninitialized_copy(position,finish,new_finish);
                }
                catch(...)
                {
                    destroy(new_start,new_finish);
                    allocator<T>::deallocate(new_start);
                    throw;
                }

                destroy(begin(),end());
                allocator<T>::deallocate(begin());
                start = new_start;
                finish = new_finish;
                end_of_storage = new_start+len;

            }
        }


        pointer allocate_and_copy(const_iterator first, const_iterator last)   //申请空间并拷贝区间内容
        {
            difference_type len = last-first;
            pointer temp = allocator<T>::allocate(size_type(len));
            for(int i=0; i<len; i++,first++)
                (temp+i)->T(*first);
            return temp;
        }

        pointer allocate_and_fill(size_type n, const T val = T())                //申请空间，并填充指定内容
        {
            pointer temp = allocator<T>::allocate(n);
            for(int i=0; i<n; i++)
                (temp+i)->T(val);
            return temp;
         }

         void destroy(iterator first, iterator last)              //析构区间内对象
         {
            while(first!=last)
            {
                first->~T();
                first++;
            }
         }
    public:




        vector(const Allocator& a=Allocator()):start(0),finish(0),end_of_storage(0){}

        explicit vector(size_type n, const T& value=T())
        {
            start = allocate_and_fill(n,value);
            finish = start+n;
            end_of_storage = finish;
        }

        vector(const vector<T,Allocator>& x)
        {
            start = allocate_and_copy(x.begin(),x.end());
            finish = start+(x.end()-x.begin());
            end_of_storage = finish;
        }

        template<class InputIterator>
        vector(const InputIterator first, const InputIterator last)
        {
            start = allocate_and_copy(first,last);
            finish = start+(last-first);
            end_of_storage = finish;
        }



        vector<T,Allocator>& operator=(const vector<T,Allocator>& x)
        {
            if( this != &x){

                if(x.size()>capacity())
                {
                    pointer temp = allocate_and_copy(x.begin(),x.end());
                    destroy(start,finish);
                    allocator<T>::deallocate(start);
                    start = temp;
                    finish = start+(x.end()-x.begin());
                    end_of_storage = finish;
                }
                else if(size()>=x.size())
                {
                    iterator index = std::copy(x.begin(),x.end(),begin());
                    destroy(index,finish);
                }
                else
                {
                    std::copy(x.begin(),x.begin()+size(),start);
                    uninitialized_copy(x.begin() + size(), x.end(), finish);
                }

                finish = start + x.size();
            }
            return *this;
        }

        template<class InputIterator>
        void assign(InputIterator first, InputIterator last);

        void assign(size_type n, const T& u);

        void reserve(size_type n);

        ~vector(){destroy(start,finish); allocator<T>::deallocate(start);}

        void swap(vector<T,Allocator>& x)
        {
            std::swap(start,x.start);
            std::swap(finish,x.finish);
            std::swap(end_of_storage,x.end_of_storage);
        }


        //比较操作

        bool operator<(const vector<T>& x)
        {
            size_type len = max(x.size(),this.size());

        }


        //向量元素访问成员函数
        iterator begin(){return start;}
        const_iterator begin()const{return start;}

        iterator end(){return finish;}
        const_iterator end()const{return finish;}

        size_type size()const{return size_type(end()-begin());}
        size_type max_size()const{return size_type(-1)/sizeof(T);}

        void resize(size_type sz,T c = T())
        {
            if(sz<size())
                erase(begin()+sz,end());
            else
                insert(end(),sz-size(),c);
        }

        size_type capacity()const{return size_type(end_of_storage-begin());}
        bool empty()const{return begin()==end();}
        reference operator[](size_type n){return reference(*(start+n));}
        const_reference operator[](size_type n)const{return const_reference(*start+n);}
        reference at(size_type n){return reference(*start+n);}
        const_reference at(size_type n)const{return const_reference(*start+n);}
        reference front(){return reference(*start);}
        const_reference front()const{return const_reference(*start);}
        reference back(){return reference(*(end()-1));}
        const_reference back()const{return reference(*(end()-1));}


        //向量插入成员函数

        void push_back(const T& x)
        {
            if(finish != end_of_storage)        //内存充足
            {
                allocator<T>::construct(finish,x);
                ++finish;
            }
            else
                insert_aux(end(),x);
        }

        iterator insert(iterator position, const T& x)
        {
            size_type n=position-begin();
            if(finish != end_of_storage && position == end())
            {
                allocator<T>::construct(finish,x);
                ++finish;
            }
            else
                insert_aux(position,x);
            return begin()+n;
        }

        void insert(iterator position, size_type n, const T& x)
        {
            if(n != 0)
            {
                if(size_type(end_of_storage-finish)>=n)
                {
                    T x_copy = x;
                    const size_type elems_after = finish-position;
                    iterator old_finish = finish;
                    if(elems_after>n)
                    {
                        uninitialized_copy(finish-n,finish,finish);
                        finish+=n;
                        copy_backward(position,old_finish-n,old_finish);
                        fill(position,position+n,x_copy);
                    }
                    else
                    {
                        uninitialized_fill_n(finish,n-elems_after,x_copy);
                        finish+=n-elems_after;
                        uninitialized_copy(position,old_finish,finish);
                        finish+=elems_after;
                        fill(position,old_finish,x_copy);
                    }
                }
                else
                {
                    const size_type old_size = size();
                    const size_type len = old_size+ old_size>n?old_size:n;
                    iterator new_start = allocator<T>::allocate(len);
                    iterator new_finish = new_start;
                    try
                    {
                        new_finish = uninitialized_copy(start,finish,n,x);
                        new_finish = uninitialized_fill_n(new_finish,n,x);
                        new_finish = uninitialized_copy(position,finish,new_finish);
                    }
                    catch(...)
                    {
                        destroy(new_start,new_finish);
                        allocator<T>::deallocate(new_start);
                        throw;
                    }
                    destroy(start,finish);
                    allocator<T>::deallocate(start);
                    start = new_start;
                    finish = new_finish;
                    end_of_storage = new_start+len;
                    }
                }

        }



        template<class InputIerator>
        void insert(iterator position, InputIerator first, InputIerator last)
        {
            if (first != last) {
                size_type n = 0;
                distance(first, last, n);
                if (size_type(end_of_storage - finish) >= n) {
                    const size_type elems_after = finish - position;
                    iterator old_finish = finish;
                    if (elems_after > n) {
                        uninitialized_copy(finish - n, finish, finish);
                        finish += n;
                        copy_backward(position, old_finish - n, old_finish);
                        copy(first, last, position);
                    }
                    else {
                    uninitialized_copy(first + elems_after, last, finish);
                    finish += n - elems_after;
                    uninitialized_copy(position, old_finish, finish);
                    finish += elems_after;
                    copy(first, first + elems_after, position);
                    }
                }
                else {
                    const size_type old_size = size();
                    const size_type len = old_size + old_size>n?old_size:n;
                    iterator new_start = allocator<T>::allocate(len);
                    iterator new_finish = new_start;
                    try {
                        new_finish = uninitialized_copy(start, position, new_start);
                        new_finish = uninitialized_copy(first, last, new_finish);
                        new_finish = uninitialized_copy(position, finish, new_finish);
                        }

                    catch(...) {
                        destroy(new_start, new_finish);
                        allocator<T>::deallocate(new_start, len);
                        throw;
                    }

                    destroy(start, finish);
                    deallocate(start);
                    start = new_start;
                    finish = new_finish;
                    end_of_storage = new_start + len;
                }
            }
        }

        //向量删除成员函数

        void pop_back(){--finish; allocator<T>::destroy(finish);}
        iterator erase(iterator position)
        {
            if(position+1!=end())
                copy(position+1,finish,position);
            --finish;
            allocator<T>::destroy(finish);
            return position;

        }
        iterator erase(iterator first, iterator last)
        {
            iterator it = copy(last,finish,first);
            destroy(it,finish);
            finish = finish-(last-first);
            return first;
        }
        void clear()
        {
            erase(begin(),end());
        }
    };
}

#endif






























