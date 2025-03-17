#pragma once
/*****************************************************************//**
 * @file   KT_Array.h
 * @brief  This file contains the code for KT::Vector
 *
 * @author Kroktur
 * @date   February 2025
 *********************************************************************/

//include
 #include <exception>
#include <initializer_list>
#include <sstream>
#include "KT_Math.h"
/**
  * @brief Namespace of my library
  */
namespace KT
{
	/**
	 * @brief Vector
	 * @tparam type 
	 */
	template<typename type>
    class Vector
    {
    public:
        using value_type = type;
        struct iterator;
        struct reverse_iterator;
        struct const_iterator;
        struct const_reverse_iterator;
        using reverse_iterator = reverse_iterator;
        using const_reverse_iterator = const_reverse_iterator;
        using iterator = iterator;
        using const_iterator = const_iterator;
        using value_type = type;
        using pointer = type*;
        using const_pointer = const type*;
        using reference = type&;
        using const_reference = const type&;
        /**
         * @brief destructor 
         */
        ~Vector() { delete[] m_data; }
        /**
         * @brief default constructor
         */
        Vector() :capacity(0), size(0), m_data(nullptr) {}
        /**
         * @brief constructor with size
         * @param size_t 
         */
        Vector(size_t newcapacity) :capacity(newcapacity), size(0), m_data(nullptr) { reserve(newcapacity); }

        /**
         * @brief Copy constructor
         * @param KT::Vector 
         */
        Vector(const Vector& tab) :capacity(0), size(0), m_data(nullptr)
        {
            reserve(tab.Capacity());
            resize(tab.Size());
            KT::Math::Copy(tab.begin(), tab.end(), m_data);
        }

        /**
         * @brief constructor with Initialize_List
         * @param Initialize_List 
         */
        Vector(std::initializer_list<type> list):capacity(0), size(0), m_data(nullptr)
        {
            reserve(list.size() * 2);
            resize(list.size());
            KT::Math::Copy(list.begin(), list.end(), m_data);
        }

        /**
         * @brief reserve the size of the vector
         * @param size_t
         * @throw out_of_range compatible size
         */
        void reserve(const size_t& newcapacity)
        {
            if (capacity > newcapacity)
                throw std::out_of_range("New capacity too small");
            type* newdata = new type[newcapacity];
          KT::Math::Copy(m_data, m_data + size, newdata);
            KT::Math::Fill(newdata + size, newdata + newcapacity, type());
            delete[] m_data;
            m_data = newdata;
            capacity = newcapacity;
        }

        /**
         * @brief add an element to the container
         * @param value 
         */
        void pushBack(const_reference value)
        {
            resize(size + 1);
            m_data[size - 1] = value;
        }

        /**
         * @brief pop the last element
         */
        void popBack()
        {
            if (!Empty())
                resize(size - 1);
        }

        /**
         * @brief resize the container 
         * @param size_t 
         */
        void resize(const size_t& newsize)
        {
            if (size == newsize)
                return;
            if (newsize > capacity)
                reserve(newsize * 2);
            size = newsize;
        }

        /**
         * @brief get an element of the container
         * @param size_t 
         * @return reference
         */
        reference operator[](const size_t& idx)
        {
            return m_data[idx];
        }

        /**
         * @brief get an element of the container const 
         * @param size_t 
         * @return reference const
         */
        const_reference operator[](const size_t& idx) const
        {
            return m_data[idx];
        }

        /**
         * @brief get an element of the container with verification
         * @param idx 
         * @return reference
         */
        reference at(const size_t& idx)
        {
            if (idx >= size)
                throw std::out_of_range("Out of Range");
            return m_data[idx];
        }

        /**
         * @brief get an element of the container with verification const
         * @param size_t 
         * @return reference const
         */
        const_reference at(const size_t& idx) const
        {
            if (idx >= size)
                throw std::out_of_range("Out of Range");
            return m_data[idx];
        }

        /**
         * @brief get the Iterator of the first element
         * @return iterator
         */
        iterator begin()
        {
            return iterator(m_data);
        }

        /**
         * @brief get the iterator of the last element
         * @return iterator
         */
        iterator end()
        {
            return iterator(m_data + size);
        }

        /**
         * @brief get the Const_Iterator of the first element
         * @return Const_Iterator
         */
        const_iterator begin() const
        {
            return const_iterator(m_data);
        }

        /**
         * @brief get the Const_Iterator of the last element
         * @return Const_Iterator
         */
        const_iterator end() const
        {
            return const_iterator(m_data + size);
        }

        /**
         * @brief get the Reverse_Iterator of the first element
         * @return Reverse_Iterator
         */
        reverse_iterator rbegin()
        {
            return reverse_iterator(m_data + size - 1);
        }

        /**
         * @brief get the Const_Reverse_Iterator of the first element 
         * @return Const_Reverse_Iterator
         */
        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(m_data + size - 1);
        }

        /**
         * @brief get the Reverse_Iterator of the last element
         * @return Reverse_Iterator
         */
        reverse_iterator rend()
        {
            if (Empty())
                throw std::out_of_range("Array is empty");
            return reverse_iterator(m_data - 1);
        }

        /**
         * @brief get the Const_Reverse_Iterator of the last element
         * @return Const_Reverse_Iterator
         */
        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(m_data - 1);
        }

        /**
         * @brief get the first element
         * @return reference
         */
        reference front()
        {
            if (Empty())
                throw std::out_of_range("Array is empty");
            return m_data[0];
        }

        /**
         * @brief get the first element const
         * @return reference const
         */
        const_reference front() const
        {
            if (Empty())
                throw std::out_of_range("Array is empty");
            return m_data[0];
        }

        /**
         * @brief get the last element
         * @return reference
         */
        reference back()
        {
            if (Empty())
                throw std::out_of_range("Array is empty");
            return m_data[size - 1];
        }

        /**
         * @brief get the last element const
         * @return reference const
         */
        const_reference back() const
        {
            if (Empty())
                throw std::out_of_range("Array is empty");
            return m_data[size - 1];
        }

        /**
         * @brief return if the container is empty
         * @return bool
         */
        bool Empty()
        {
            return size == 0;
        }
        /**
         * @brief return if the container is empty const
         * @return bool const
         */
        bool Empty() const
        {
            return size == 0;
        }
        /**
         * @brief get the Capacity of the container
         * @return size_t
         */
        size_t Capacity()
        {
            return capacity;
        }
        /**
         * @brief get the Capacity of the container const
         * @return size_t const
         */
        size_t Capacity() const
        {
            return capacity;
        }
        /**
         * @brief get the size of the container
         * @return size_t
         */
        size_t Size()
        {
            return size;
        }
        /**
         * @brief get the size of the container const
         * @return size_t const
         */
        size_t Size() const
        {
            return size;
        }

        /**
         * @brief get the max_size of the container
         * @return size_t
         */
        size_t max_size()
        {
            return std::numeric_limits<size_t>::max() / sizeof(type);
        }

        /**
         * @brief get the max_size of the container const
         * @return size_t const
         */
        size_t max_size() const
        {
            return std::numeric_limits<size_t>::max() / sizeof(type);
        }

        /**
         * @brief get a pointer of the first element
         * @return pointer
         */
        pointer data()
        {
            return m_data;
        }

        /**
         * @brief get a pointer of the first element const
         * @return pointer const
         */
        const_pointer data() const
        {
            return m_data;
        }

        /**
         * @brief clear the container
         */
        void clear()
        {
            resize(0);
            reserve(capacity);
        }

        /**
         * @brief insert a element in the container
         * @param iterator dest 
         * @param reference
         * @throw out_of_range of the container
         */
        void insert(iterator dest, const_reference value )
        {
            if (dest > m_data + size || dest < m_data)
                throw std::out_of_range("dest out of range");
            resize(size + 1);
            for (auto ptr = m_data + size - 1; ptr != dest.m_ptr; --ptr)
            {
                *ptr = *(ptr - 1);
            }
            *dest = value;
        }

        /**
         * @brief erase an element of the container
         * @param iterator 
         */
        void erase(iterator supr)
        {
            if (find(supr) == end())
                throw std::out_of_range("supr out of range");
            for (auto ptr = supr; ptr != m_data + size - 1; ++ptr)
            {
                *ptr = *(ptr + 1);
            }
            resize(size - 1);
        }

        /**
         * @brief assign value to the container 
         * @param iterator begin 
         * @param iterator end 
         */
        void assign(iterator begin, iterator end)
        {
            clear();
            size_t sizeofvec = end - begin;
            resize(sizeofvec);

            KT::Math::Copy(begin, end, m_data);
        }

        /**
         * @brief assign data in a range
         * @param sizeofvec 
         * @param value_type 
         */
        void assign(size_t sizeofvec, value_type data)
        {
            clear();
            resize(sizeofvec);
            KT::Math::Fill(m_data, m_data + sizeofvec, data);
        }

        /**
         * @brief assign with initializer_list
         * @param list 
         */
        void assign(std::initializer_list<type> list)
        {
            clear();
            resize(list.size());
            KT::Math::Copy(list.begin(), list.end(), m_data);
        }

        /**
         * @brief Copy a the container
         * @param KT::Vector 
         * @return KT::Vector
         */
        Vector& operator=(const Vector& tab)
        {
            resize(tab.Size());
         KT::Math::Copy(tab.begin(), tab.end(), m_data);
            return *this;
        }

        /**
         * @brief swap Vector
         * @param KT::Vector 
         */
        void swap(Vector<type>& NewVector)
        {
            Vector<type> tmp = *this;
            *this = NewVector;
            NewVector = tmp;
        }

        /**
         * @brief find if an element is on the list
         * @param Iterator 
         * @return Iterator
         */
        iterator find(const iterator& ptr)
        {
            for (auto it = begin(); it != end(); ++it)
            {
                if (it == ptr)
                    return it;
            }
            return end();
        }

        /**
         * @brief find if an element is on the list const
         * @param Const_iterator 
         * @return Const_iterator
         */
        const_iterator find(const const_iterator& ptr) const
        {
            for (auto it = begin(); it != end(); ++it)
            {
                if (it == ptr)
                    return it;
            }
            return end();
        }

    private:
        struct iterator
        {
            //this iterator compatible with stl
            using iterator_category = std::random_access_iterator_tag;
            using value_type = type;
            using difference_type = std::ptrdiff_t;
            using pointer = type*;
            using reference = type&;
            friend Vector;
            iterator(pointer ptr) : m_ptr(ptr) {}
            reference operator*()
            {
                return *m_ptr;
            }
          const reference operator*()const
            {
                return *m_ptr;
            }
            pointer operator->()
            {
                return m_ptr;
            }
           const pointer operator->()const
            {
                return m_ptr;
            }
            iterator& operator++()
            {
                ++m_ptr;
                return *this;
            }
            iterator& operator--()
            {
                --m_ptr;
                return *this;
            }
            iterator operator+(difference_type n) const
            {
                return iterator(m_ptr + n);
            }
            iterator operator-(difference_type n) const
            {
                return iterator(m_ptr - n);
            }
            difference_type operator-(const iterator& other) const
            {
                return m_ptr - other.m_ptr;
            }
            difference_type operator+(const iterator& other) const
            {
                return m_ptr + other.m_ptr;
            }
            bool operator==(const iterator& other) const
            {
                return m_ptr == other.m_ptr;
            }
            bool operator!=(const iterator& other) const
            {
                return m_ptr != other.m_ptr;
            }
            bool operator<(const iterator& other) const
            {
                return m_ptr < other.m_ptr;
            }
            bool operator>(const iterator& other) const
            {
                return m_ptr > other.m_ptr;
            }
            bool operator<=(const iterator& other) const
            {
                return m_ptr <= other.m_ptr;
            }
            bool operator>=(const iterator& other) const
            {
                return m_ptr >= other.m_ptr;
            }
        private:
            pointer m_ptr;
        };
        struct const_iterator
        {
            //this iterator compatible with stl
            using iterator_category = std::random_access_iterator_tag;
            using value_type = const type;
            using difference_type = std::ptrdiff_t;
            using pointer = const type*;
            using reference = const type&;
            friend Vector;
            const_iterator(pointer ptr) : m_ptr(ptr) {}
            reference operator*()
            {
                return *m_ptr;
            }
            const reference operator*() const
            {
                return *m_ptr;
            }
            pointer operator->()
            {
                return m_ptr;
            }
            const pointer operator->() const
            {
                return m_ptr;
            }
            const_iterator& operator++()
            {
                ++m_ptr;
                return *this;
            }
            const_iterator& operator--()
            {
                --m_ptr;
                return *this;
            }
            const_iterator operator+(difference_type n) const
            {
                return iterator(m_ptr + n);
            }
            const_iterator operator-(difference_type n) const
            {
                return const_iterator(m_ptr - n);
            }
            difference_type operator-(const const_iterator& other) const
            {
                return m_ptr - other.m_ptr;
            }
            difference_type operator+(const const_iterator& other) const
            {
                return m_ptr + other.m_ptr;
            }
            bool operator==(const const_iterator& other) const
            {
                return m_ptr == other.m_ptr;
            }
            bool operator!=(const const_iterator& other) const
            {
                return m_ptr != other.m_ptr;
            }
            bool operator<(const const_iterator& other) const
            {
                return m_ptr < other.m_ptr;
            }
            bool operator>(const const_iterator& other) const
            {
                return m_ptr > other.m_ptr;
            }
            bool operator<=(const const_iterator& other) const
            {
                return m_ptr <= other.m_ptr;
            }
            bool operator>=(const const_iterator& other) const
            {
                return m_ptr >= other.m_ptr;
            }
        private:
            pointer m_ptr;
        };
        struct reverse_iterator {
            //this iterator compatible with stl
            using iterator_category = std::random_access_iterator_tag;
            using value_type = type;
            using difference_type = std::ptrdiff_t;
            using pointer = type*;
            using reference = type&;
            friend Vector;
            reverse_iterator(pointer ptr) : m_ptr(ptr) {}
            reference operator*()
            {
                return *m_ptr;
            }
            const reference operator*() const
            {
                return *m_ptr;
            }
            pointer operator->()
            {
                return m_ptr;
            }
            const pointer operator->() const
            {
                return m_ptr;
            }
            reverse_iterator& operator++()
            {
                --m_ptr;
                return *this;
            }
            reverse_iterator& operator--()
            {
                ++m_ptr;
                return *this;
            }
            reverse_iterator operator+(difference_type n) const
            {
                return reverse_iterator(m_ptr - n);
            }
            reverse_iterator operator-(difference_type n) const
            {
                return reverse_iterator(m_ptr + n);
            }
            difference_type operator-(const reverse_iterator& other) const
            {
                return m_ptr + other.m_ptr;
            }
            difference_type operator+(const reverse_iterator& other) const
            {
                return m_ptr - other.m_ptr;
            }
            bool operator==(const reverse_iterator& other) const
            {
                return m_ptr == other.m_ptr;
            }
            bool operator!=(const reverse_iterator& other) const
            {
                return m_ptr != other.m_ptr;
            }
            bool operator<(const reverse_iterator& other) const
            {
                return m_ptr > other.m_ptr;
            }
            bool operator>(const reverse_iterator& other) const
            {
                return m_ptr < other.m_ptr;
            }
            bool operator<=(const reverse_iterator& other) const
            {
                return m_ptr >= other.m_ptr;
            }
            bool operator>=(const reverse_iterator& other) const
            {
                return m_ptr <= other.m_ptr;
            }
        private:
            pointer m_ptr;
        };
        struct const_reverse_iterator {
            //this iterator compatible with stl
            using iterator_category = std::random_access_iterator_tag;
            using value_type = const type;
            using difference_type = std::ptrdiff_t;
            using pointer = const type*;
            using reference = const type&;
            friend Vector;
            const_reverse_iterator(pointer ptr) : m_ptr(ptr) {}
            reference operator*()
            {
                return *m_ptr;
            }
            const reference operator*() const 
            {
                return *m_ptr;
            }
            pointer operator->()
            {
                return m_ptr;
            }
            const pointer operator->() const 
            {
                return m_ptr;
            }
            const_reverse_iterator& operator++()
            {
                --m_ptr;
                return *this;
            }
            const_reverse_iterator& operator--()
            {
                ++m_ptr;
                return *this;
            }
            const_reverse_iterator operator+(difference_type n) const
            {
                return const_reverse_iterator(m_ptr - n);
            }
            const_reverse_iterator operator-(difference_type n) const
            {
                return const_reverse_iterator(m_ptr + n);
            }
            difference_type operator-(const const_reverse_iterator& other) const
            {
                return m_ptr + other.m_ptr;
            }
            difference_type operator+(const const_reverse_iterator& other) const
            {
                return m_ptr - other.m_ptr;
            }
            bool operator==(const const_reverse_iterator& other) const
            {
                return m_ptr == other.m_ptr;
            }
            bool operator!=(const const_reverse_iterator& other) const
            {
                return m_ptr != other.m_ptr;
            }
            bool operator<(const const_reverse_iterator& other) const
            {
                return m_ptr < other.m_ptr;
            }
            bool operator>(const const_reverse_iterator& other) const
            {
                return m_ptr < other.m_ptr;
            }
            bool operator<=(const const_reverse_iterator& other) const
            {
                return m_ptr <= other.m_ptr;
            }
            bool operator>=(const const_reverse_iterator& other) const
            {
                return m_ptr <= other.m_ptr;
            }
        private:
            pointer m_ptr;
        };
        size_t capacity;
        size_t size;
        type* m_data;
    };
}

/**
 * @brief display the Vector
 * @tparam type 
 * @param output stream 
 * @param KT::Vector 
 * @return output stream
 */
template<typename type>
std::ostream& operator<<(std::ostream& os, const KT::Vector<type>& tab)
{
    if (tab.Size() == 0)
        return os;
    os << "(";
    for (auto i = 0; i < tab.Size() - 1; ++i)
        os << tab[i] << ", ";
    os << tab[tab.Size() - 1] << ")";
    return os;
}