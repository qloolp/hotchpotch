#ifndef LIST_H
#define LIST_H
#include <cstddef>

namespace li
{
    template <typename T>     //list 节点
    struct list_node
    {
        list_node<T>* prev;
        list_node<T>* next;
        T data;
    };

    //list 迭代器
    template<typename T, typename Ref, typename Ptr>
    struct list_iterator
    {
        typedef list_iterator<T,T&,T*>         iterator;
        typedef list_iterator<T,Ref,Ptr>       self;

        //双向迭代器标识
        typedef bidirectional_iterator_tag iterator_category;

        typedef T                  value_type;
        typedef Ptr                pointer;
        typedef Ref                reference;
        typedef list_node<T>*      link_type;
        typedef size_t             size_type;
        typedef ptrdiff_t          difference_type;

        link_type node;        //指针

        //构造函数
        list_iterator(link_type x):node(x){}
        list_iterator(){}
        list_iterator(const iterator& x):node(x.node){}

        bool operator==(const self& x) const {return node == x.node}
        bool operator!=(const self& x) const {return node != x.node}

        reference operator*()const {return (*node).data;}
        pointer operator->()const {return &(operator*());}

        self& operator++()
        {
            node = node->next;
            return *this;
        }
        self operator++(int)
        {
            self temp = *this;
            ++ *this;
            return temp;
        }

        self& operator--()
        {
            node = node->prev;
            return *this;
        }

        self operator--(int)
        {
            self temp = *this;
            -- *this;
            return temp;
        }

    };


    template<typename T, typename Alloc = alloc>
    class list
    {
        protected:
        public:
            typedef list_node* link_type;
        protected:
            link_type node;
            typedef simple_alloc<list_node,Alloc> list_node_allocator;
            link_type get_node(link_type p){list_node_allocator::allocate();}
            void put_node(link_type p){list_node_allocator::deallocate(p);}
            link_type create_node(const T& x)
            {
                link_type p = get_node();
                construct(&p->data,x);
                return p;
            }
            void destroy_node(link_type p)
            {
                destroy(p->data);
                put_node();
            }

            void empty_initialize()
            {
                node = get_node();
                node->next = node;
                node->prev = node;
            }
        public:
        iterator begin(){return node.next;}
        iterator end(){return node;}
        bool empty()const {return node->next == node;}
        size_type size()const
        {
            size_type result = 0;
            distance(begin(),end(),result);
            return result;
        }
        reference front(){return *begin();}
        reference back(){return *(--end());}


        list(){empty_initialize();}
        void push_back(const T& x){insert(end(),x);}
        iterator insert(iterator position, const T& x)
        {
            link_type temp = create_node(x);
            temp->next = position.node;
            temp->prev = position.node->prev;
            (link_type(position.node->prev))->next = temp;
            position.node->prev = temp;
            return temp;
        }

        void push_front(const T& x){insert(begin(),x);}
        iterator erase(iterator position)
        {
            link_type next_node = link_type(position.node->next);
            link_type prev_node = link_type(position.node->prev);
            prev_node->next = next_node;
            next_node->prev = prev_node;
            destroy_node(position.node);
            return iterator(next_node);
        }
        void pop_front(){erase(begin());}
        void pop_back(){iterator temp = end(); erase(--temp);}

        void clear()
        {
            link_type cur = (link_type)node->next;
            while(cur != node )
            {
                link_type temp = cur;
                cur = (link_type)cur->next;
                destroy_node(temp);
            }
            node->next = node;
            node->prev = node;
        }

        void remove(const T& value)
        {
            iterator first = begin();
            iterator last = end();
            while(first != last )
            {
                iterator next = first;
                ++next;
                if(*first == value)
                    erase(first);
                first = next;
            }


        }

        void unique()
        {
            iterator first = begin();
            iterator last = end();
            if(first == last)
                return;
            iterator next = first;
            while(++next != last)
            {
                if(*first == *next)
                    erase(next);
                else
                    first = next;
                next = first;

            }
        }


        void transfer(iterator position, iterator first, iterator last)
        {
            if(position != last)
            {
                (*(link_type((*last.node).prev))).next = position.node;
                (*(link_type((*first.node).prev))).next = last.node;
                (*(link_type((*position.node).prev))).next = first.node;
                link_type temp = link_type((*position.node).prev);
                (*position.node).prev = (*last.node).prev;
                (*last.node).prev = (*first.node).prev;
                (*first.node).prev = temp;
            }
        }


        void splic(iterator position, list& x)
        {
            if(!x.empty())
                transfer(position,x.begin(),x.end());
        }

        void splice(iterator position, list&, iterator i)
        {
            iterator j= i;
            ++j;
            if(position == i|| position == j)
                return;
            transfer(position,i,j);
        }

        void splic(iterator position, list&, iterator first, iterator last)
        {
            if(first != last)
                transfer(position,first, last);
        }



    }





}

#endif // LIST_H
