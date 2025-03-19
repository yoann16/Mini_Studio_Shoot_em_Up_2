#pragma once
/*****************************************************************//**
 * @file   KT_Array.h
 * @brief  This file contains the code for KT::Array
 * 
 * @author Kroktur
 * @date   February 2025
 *********************************************************************/
#include <exception>
#include <initializer_list>
#include "KT_Math.h"
#include <sstream>
/**
 * @brief Namespace of my library
 */
namespace KT
{
     /**
      * @brief Array
      * @tparam type
      * @tparam size_t size 
      */
    template<typename type, size_t size>
    class Array
    {
    public:

        
        using value_type = type;
        struct iterator;
        struct const_iterator;
        struct reverse_iterator;
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
         * @brief constructor with initializer_list
         * 
         * @param initializer_list
         * @throw out_of_range if incompatible size
         */
        Array(std::initializer_list<type> list)
        {
            if (list.size() > size)
                throw std::out_of_range("Out of Range");

            KT::Math::Copy(list.begin(), list.end(), m_data);
            KT::Math::Fill(m_data + list.size(), m_data + size, type());
        }
        /**
         * @brief default constructor
         * 
         */
        Array()
        {
            KT::Math::Fill(m_data, m_data + size, type());
        }
        /**
         * @brief overloading the equals operator
         * 
         * @param KT::Array
         * @return reference KT::Array
         */
        Array& operator=(const Array<type, size>& tab)
        {
            if (this != &tab)
               KT::Math::Copy(tab.begin(), tab.end(), m_data);
            return *this;
        }
        /**
         * @brief Copy constructor 
         * 
         * @param tab
         * @throw out_of_range if incompatible size
         */
        Array(const Array& tab)
        {
            if (tab.Size() != size)
                throw std::out_of_range("size must be equal");
            KT::Math::Copy(tab.begin(), tab.end(), m_data);
        }
        /**
         * @brief get an element
         * 
         * @param size_t idx
         * @return reference 
         */
        reference operator[](const size_t& Idx)
        {
            return m_data[Idx];
        }
        /**
       * @brief get an element const
       *
       * @param size_t idx
       * @return reference const
       */
        const_reference operator[](const size_t& Idx) const
        {
            return m_data[Idx];
        }
        /**
       * @brief get an element with verification 
       *
       * @param size_t idx
       * @return reference 
       * @throw out_of_range if idx out of range
       */
        reference at(const size_t& Idx)
        {
            if (Idx >= size)
                throw std::out_of_range("Out of Range");
            return m_data[Idx];
        }
        /**
       * @brief get an element const with verification
       *
       * @param size_t idx
       * @return reference const
       * @throw out_of_range if idx out of range
       */
        const_reference at(const size_t& Idx) const
        {
            if (Idx >= size)
                throw std::runtime_error("Out of Range");
            return m_data[Idx];
        }
        /**
         * @brief get first element
         * 
         * @return reference 
         * @throw out_of_range if empty
         */
        reference front()
        {
            if (Empty())
                throw std::out_of_range("Array is empty");
            return m_data[0];
        }
        /**
         * @brief get first element const
         *
         * @return reference const
         * @throw out_of_range if empty
         */
        const_reference front() const
        {
            if (Empty())
                throw std::out_of_range("Array is empty");
            return m_data[0];
        }
        /**
         * @brief get last element 
         *
         * @return reference 
         * @throw out_of_range if empty
         */
        reference back()
        {
            if (Empty())
                throw std::out_of_range("Array is empty");
            return m_data[size - 1];
        }
        /**
         * @brief get last element const 
         *
         * @return reference 
         * @throw out_of_range if empty
         */
        const_reference back() const
        {
            if (Empty())
                throw std::out_of_range("Array is empty");
            return m_data[size - 1];
        }
        /**
         * @brief pointer to first element
         * 
         * @return pointer 
         */
        pointer data()
        {
            return m_data;
        }
        /**
         * @brief pointer const to the first element
         *
         * @return pointer const 
         */
        const_pointer data() const
        {
            return m_data;
        }
        /**
         * @brief empty verification
         * 
         * @return bool  
         */
        bool Empty()
        {
            return size == 0;
        }
        /**
        * @brief empty verification const
        *
        * @return bool const
        */
        bool Empty() const
        {
            return size == 0;
        }
        /**
         * @brief return the maximum size of the container
         * 
         * @return size_t
         */
        size_t max_size()
        {
            return size;
        }
        /**
         * @brief return the maximum size const of the container
         *
         * @return size_t const 
         */
        size_t max_size() const
        {
            return size;
        }
        /**
         * @brief return the size of the container
         * 
         * @return size_t   
         */
        size_t Size()
        {
            return size;
        }
        /**
        * @brief return the size of the container const
        *
        * @return size_t const
        */
        size_t Size() const
        {
            return size;
        }
        /**
         * @brief get Iterator on the first element
         * 
         * @return Iterator
         */
        iterator begin()
        {
            return iterator(m_data);
        }
        /**
         * @brief get Iterator on the last element
         *
         * @return Iterator
         */
        iterator end()
        {
            return iterator(m_data + size);
        }
        /**
         * @brief get Iterator on the first element const
         *
         * @return Const_Iterator 
         */
        const_iterator begin() const
        {
            return const_iterator(m_data);
        }
        /**
         * @brief get Iterator on the last element const
         *
         * @return Const_Iterator
         */
        const_iterator end() const
        {
            return const_iterator(m_data + size);
        }
        /**
         * @brief get Iterator on the first element upside down
         *
         * @return Reverse_Iterator
         */
        reverse_iterator rbegin()
        {
            return reverse_iterator(m_data + size - 1);
        }
        /**
         * @brief get Iterator on the last element upside down
         *
         * @return Reverse_Iterator
         */
        reverse_iterator rend()
        {
            return reverse_iterator(m_data - 1);
        }
        /**
         * @brief get Iterator on the first element upside down const
         *
         * @return Const_Reverse_Iterator
         */
        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(m_data + size - 1);
        }
        /**
        * @brief get Iterator on the last element upside down const
        *
        * @return Const_Reverse_Iterator
        */
        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(m_data - 1);
        }
        /**
         * @brief Swaps the content of this array with another array of the same type and size. 
         * 
         * @param Array
         */
        void swap(Array<type, size>& NewArray)
        {
            Array<type, size> tmp = *this;
            *this = NewArray;
            NewArray = tmp;
        }
    private:
        struct iterator {
            //this iterator compatible with stl
            using iterator_category = std::random_access_iterator_tag;
            using value_type = type;
            using difference_type = std::ptrdiff_t;
            using pointer = type*;
            using reference = type&;
            friend Array;
            iterator(pointer ptr) : m_ptr(ptr) {}
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
        struct const_iterator {
            //this iterator compatible with stl
            using iterator_category = std::random_access_iterator_tag;
            using value_type = const type;
            using difference_type = std::ptrdiff_t;
            using pointer = const type*;
            using reference =  const type&;
            friend Array;
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
            friend Array;
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
            friend Array;
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
                return m_ptr > other.m_ptr;
            }
            bool operator>(const const_reverse_iterator& other) const
            {
                return m_ptr < other.m_ptr;
            }
            bool operator<=(const const_reverse_iterator& other) const
            {
                return m_ptr >= other.m_ptr;
            }
            bool operator>=(const const_reverse_iterator& other) const
            {
                return m_ptr <= other.m_ptr;
            }
        private:
            pointer m_ptr;
        };
        type m_data[size];
    };
}
/**
 * @brief operator overload << for display
 *
 * @tparam type
 * @tparam size_t
 * @param output stream
 * @param KT::Array
 * @return output stream
 */
template<typename type, size_t size>
std::ostream& operator<<(std::ostream& os, const KT::Array<type, size>& tab)
{
    if (tab.Size() == 0)
        return os;
    os << "(";
    for (auto i = 0; i < tab.Size() - 1; ++i)
        os << tab[i] << ", ";
    os << tab[tab.Size() - 1] << ")";
    return os;
}