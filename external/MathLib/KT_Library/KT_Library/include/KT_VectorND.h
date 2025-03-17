#pragma once
/*****************************************************************//**
 * @file   KT_VectorND.h
 * @brief  This file contains the code for KT::VectorND
 *
 * @author Kroktur
 * @date   February 2025
 *********************************************************************/
#include <exception>
#include <initializer_list>
#include <sstream>
#include "KT_Math.h"
#include "KT_Array.h"
 /**
   * @brief Namespace of my library
   */
namespace KT
{
	/**
	 * @brief VectorND
	 * @tparam type 
	 * @tparam size_t 
	 */
	template<typename type , size_t size>
	class VectorND
	{
	public:
        using value_type = type;
        using pointer = type*;
        using const_pointer = const type*;
        using reference = type&;
        using const_reference = const type&;
        struct iterator;
        struct const_iterator;
        struct reverse_iterator;
        struct const_reverse_iterator;
        using reverse_iterator = reverse_iterator;
        using const_reverse_iterator = const_reverse_iterator;
        using iterator = iterator;
        using const_iterator = const_iterator;

        /**
         * @brief Constructor with initializer_list
         * @param initializer_list
         * @throw out_of_range if size not compatible
         */
        VectorND(std::initializer_list<type> list)
        {
            if (list.size() > size)
                throw std::runtime_error("Out of Range");

           KT::Math::Copy(list.begin(), list.end(), m_data.data());
            KT::Math::Fill((m_data.begin() + list.size()), m_data.end(), type());
        }

        /**
         * @brief deault constructor
         */
        VectorND()
        {
           KT::Math::Fill(m_data.begin(), m_data.end(), type());
        }

        /**
         * @brief Copy Constructor
         * @param KT::VectorNd
         * @throw if size not compatible
         */
        VectorND(const VectorND& tab)
        {
            if (tab.m_data.Size() != size)
                throw std::out_of_range("size must be equal");
            KT::Math::Copy(tab.m_data.begin(), tab.m_data.end(), m_data.data());
        }

        /**
         * @brief Copy the VectorND
         * @param KT::VectorND 
         * @return KT::VectorND
         * @throw out_of_range if size not compatible
         */
        VectorND& operator=(const VectorND& tab)
        {
            if (m_data.Size() != tab.m_data.Size())
                throw std::out_of_range("size must be equal");
            if (this != &tab)
               KT::Math::Copy(tab.m_data.begin(), tab.m_data.end(), m_data.data());
            return *this;
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
         * @param size_t
         * @return reference
         * @throw out_of_range size not compatible
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
         * @throw out_of_range size not compatible
         */
        const_reference at(const size_t& idx) const
        {
            if (idx >= size)
                throw std::out_of_range("Out of Range");
            return m_data[idx];
        }

        /**
         * @brief get the size of the container
         * @return size_t
         */
        size_t Size()
        {
            return m_data.Size();
        }

        /**
         * @brief get the size of the container const
         * @return size_t const
         */
        const size_t Size() const
        {
            return m_data.Size();
        }

        /**
         * @brief if container is empty
         * @return bool
         */
        bool Empty()
        {
            return m_data.Empty();
        }

        /**
         * @brief if container is empty const
         * @return boll const
         */
        bool Empty() const
        {
            return  m_data.Empty();
        }

        /**
         * @brief get a pointer of the first element
         * @return pointer
         */
        pointer data()
        {
            return m_data.data();
        }

        /**
         * @brief get a pointer of the first element const 
         * @return pointer const 
         */
        const_pointer data() const
        {
            return m_data.data();
        }

        /**
         * @brief return an iterator of the first element
         * @return iterator
         */
        iterator begin()
        {
            return iterator(data());
        }
        /**
        * @brief return an iterator of the last element
        * @return iterator
        */
        iterator end()
        {
            return iterator(data() + size);
        }
        /**
        * @brief return an Const_iterator of the first element
        * @return Const_iterator
        */
        const_iterator begin() const
        {
            return const_iterator(data());
        }
        /**
        * @brief return an Const_iterator of the first element
        * @return Const_iterator
        */
        const_iterator end() const
        {
            return const_iterator(data() + size);
        }
        /**
        * @brief return an Reverse_iterator of the first element
        * @return Reverse_iterator
        */
        reverse_iterator rbegin()
        {
            return reverse_iterator(data() + size - 1);
        }
        /**
        * @brief return an Reverse_iterator of the last element
        * @return Reverse_iterator
        */
        reverse_iterator rend()
        {
            return reverse_iterator(data() - 1);
        }
        /**
        * @brief return an Const_Reverse_iterator of the first element
        * @return Const_Reverse_iterator
        */
        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(data() + size - 1);
        }
        /**
        * @brief return an Cont_Reverse_iterator of the last element
        * @return Const_Reverse_iterator
        */
        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(data() - 1);
        }

        /**
         * @brief Operator + betwen KT::VectorND
         * @param KT::VectorND 
         * @return KT::VectorND
         */
        KT::VectorND<type, size> operator+(const KT::VectorND<type,size>& data)
        {
            KT::VectorND<type, size> result;
            for (size_t i = 0; i < m_data.Size(); ++i)
            {
                result[i] = data[i] + m_data[i];
            }
            return result;
        }

        /**
         * @brief Operator - betwen KT::VectorND
         * @param KT::VectorND
         * @return KT::VectorND
         */
        KT::VectorND<type, size> operator-(const KT::VectorND<type,size>& data)
        {
            KT::VectorND<type, size> result;
            for (size_t i = 0; i < m_data.Size(); ++i)
            {
                result[i] = data[i] - m_data[i];
            }
            return result;
        }

        /**
         * @brief Operator * betwen KT::VectorND and int
         * @param int
         * @return KT::VectorND
         */
        KT::VectorND<type, size> operator*(const int& idx)
        {
            KT::VectorND<type, size> result;
            for (size_t i = 0; i < m_data.Size(); ++i)
            {
                result[i] =  m_data[i] * idx;
            }
            return result;
        }

        /**
         * @brief Operator / betwen KT::VectorND and int
         * @param int
         * @return KT::VectorND
         */
        KT::VectorND<type, size> operator/(const int& idx)
        {
            if (idx == 0)
                throw std::runtime_error("cannot divide by 0");
            KT::VectorND<type, size> result;
            for (size_t i = 0; i < m_data.Size(); ++i)
            {
                result[i] =  m_data[i] / idx;
            }
            return result;
        }

        /**
         * @brief Operator == betwen KT::VectorND
         * @param KT::VectorND 
         * @return bool
         */
        bool operator ==(const KT::VectorND<type, size>& data)
        {
            for (size_t i = 0; i < m_data.Size(); ++i)
            {
                if (data[i] != m_data[i])
                    return false;
            }
            return true;
        }

        /**
         * @brief Operator != betwen KT::VectorND
         * @param KT::VectorND 
         * @return bool
         */
        bool operator !=(const KT::VectorND<type, size>& data)
        {
            bool result;
            for (size_t i = 0; i < m_data.Size(); ++i)
            {
                if (data[i] == m_data[i])
                    result = false;
                else
                    result = true;
            }
            return result;
        }
        /**
         * @brief Operator == betwen KT::VectorND const
         * @param KT::VectorND
         * @return bool const
         */
        bool operator ==(const KT::VectorND<type, size>& data) const
        {
            for (size_t i = 0; i < m_data.Size(); ++i)
            {
                if (data[i] != m_data[i])
                    return false;
            }
            return true;
        }
        /**
         * @brief Operator != betwen KT::VectorND const
         * @param KT::VectorND
         * @return bool const
         */
        bool operator !=(const KT::VectorND<type, size>& data) const
        {
            bool result;
            for (size_t i = 0; i < m_data.Size(); ++i)
            {
                if (data[i] == m_data[i])
                    result = false;
                else
                    result = true;
            }
            return result;
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
            using reference = const type&;
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
        KT::Array<type, size> m_data;
	};
}

/**
 * @brief display KT::VectorND
 * @tparam type 
 * @tparam size_t 
 * @param output stream 
 * @param KT::VectorND 
 * @return output stream
 */
template<typename type , size_t size>
std::ostream& operator<<(std::ostream& os, const KT::VectorND<type, size>& tab)
{
    if (tab.Size() == 0)
        return os;
    for (auto i = 0; i < tab.Size(); ++i)
        os << "(" << tab[i] << ")" << std::endl;
    return os;
}