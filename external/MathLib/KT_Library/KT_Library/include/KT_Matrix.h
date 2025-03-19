#pragma once
/*****************************************************************//**
 * @file   KT_Matrix.h
 * @brief  This file contains the code for KT::Matrix
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
	 * @brief Matrix
	 * @tparam value_type
	 * @tparam size_t
	 * @tparam size_t
	 */
	template<typename type, size_t height , size_t width>
    class Matrix
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
         * @brief Constructor with initialisze_list
         * @param initialisze_list 
         */
        Matrix(std::initializer_list<type> list)
        {
            if (list.size() > size)
                throw std::runtime_error("Out of Range");

            KT::Math::Copy(list.begin(), list.end(), m_data.data());
            KT::Math::Fill((m_data.begin() + list.size()), m_data.end(), type());
        }

        /**
         * @brief default constructor
         */
        Matrix()
        {
           KT::Math::Fill(m_data.begin(), m_data.end(), type());
        }

        /**
         * @brief Copy Constructor
         * @param KT::Matrix
         */
        Matrix(const Matrix& tab)
        {
            if (tab.m_data.Size() != size)
                throw std::runtime_error("size must be equal");
            KT::Math::Copy(tab.m_data.begin(), tab.m_data.end(), m_data.data());
        }

        /**
         * @brief Copy KT::Matrix
         * @param KT::Matrix
         * @return KT::Matrix
         */
        Matrix& operator=(const Matrix& tab)
        {
            if (m_data.Size() != tab.m_data.Size())
                throw std::out_of_range("size must be equal");
            if (this != &tab)
                KT::Math::Copy(tab.m_data.begin(), tab.m_data.end(), m_data.data());
            return *this;
        }

        /**
         * @brief return a reference of element 
         * @param size_t row
         * @param size_t col
         * @return reference
         */
        reference getCell(size_t row, size_t col)
        {
            return m_data.at(row * width + col);
        }

        /**
         * @brief return a reference of element const
         * @param size_t row
         * @param size_t col
         * @return reference const
         */
        const_reference getCell(size_t row, size_t col) const
        {
            return m_data.at(row * width + col);
        }

        /**
         * @brief get an element
         * @param size_t 
         * @return reference
         */
        reference operator[](const size_t& idx)
        {
            return m_data[idx];
        }

        /**
         * @brief get an element const
         * @param size_t
         * @return reference const
         */
        const_reference operator[](const size_t& idx) const
        {
            return m_data[idx];
        }

        /**
         * @brief get an element with verification
         * @param size_t
         * @return reference
         * @throw out_of_range if size is not compatible
         */
        reference at(const size_t& idx)
        {
            if (idx >= size)
                throw std::out_of_range("Out of Range");
            return m_data[idx];
        }

        /**
		 * @brief  get an element const with verification
		 * @param size_t
         * @return reference const
         * @throw out_of_range if size is not compatible
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
         * @brief return if the container is empty
         * @return bool
         */
        bool Empty()
        {
            return m_data.Empty();
        }

        /**
         * @brief return if the container is empty const
         * @return bool const
         */
        bool Empty() const
        {
            return  m_data.Empty();
        }
        /**
         * @brief return a pointer of the first element
         * @return pointer
         */
        pointer data()
        {
            return m_data.data();
        }
        /**
         * @brief return a pointer of the first element const
         * @return pointer const
         */
        const_pointer data() const
        {
            return m_data.data();
        }
        /**
         * @brief get an iterator of the first element
         * @return Iterator
         */
        iterator begin()
        {
            return iterator(data());
        }
        /**
         * @brief get an iterator of the last element
         * @return Iterator
         */
        iterator end()
        {
            return iterator(data() + size);
        }
        /**
         * @brief get an Const_iterator of the first element 
         * @return Const_Iterator
         */
        const_iterator begin() const
        {
            return const_iterator(data());
        }
        /**
         * @brief get an Const_iterator of the last element
         * @return Const_Iterator
         */
        const_iterator end() const
        {
            return const_iterator(data() + size);
        }
        /**
         * @brief get an Reverse_iterator of the first element
         * @return Reverse_iterator
         */
        reverse_iterator rbegin()
        {
            return reverse_iterator(data() + size - 1);
        }
        /**
        * @brief get an Reverse_iterator of the last element
        * @return Reverse_iterator
        */
        reverse_iterator rend()
        {
            return reverse_iterator(data() - 1);
        }
        /**
        * @brief get an Const_Reverse_iterator of the first element
        * @return Const_Reverse_iterator
        */
        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(data() + size - 1);
        }
        /**
        * @brief get an Const_Reverse_iterator of the end element
        * @return Const_Reverse_iterator
        */
        const_reverse_iterator rend() const
		{

            return const_reverse_iterator(data() - 1);
        }

        /**
         * @brief Operator + betwen same Matrix size
         * @param KT::Matrix 
         * @return KT::Matrix
         */
        KT::Matrix<type, height, width > operator+(const KT::Matrix<type, height, width >& data)
        {
            KT::Matrix<type, height, width > result;
            for (size_t i = 0; i < m_data.Size(); ++i)
            {
                result[i] = data[i] + m_data[i];
            }
            return result;
        }

        /**
         * @brief Operator - betwen same Matrix size
         * @param KT::Matrix 
         * @return KT::Matrix
         */
        KT::Matrix<type, height, width > operator-(const KT::Matrix<type, height, width >& data)
        {
            KT::Matrix<type, height, width > result;
            for (size_t i = 0; i < m_data.Size(); ++i)
            {
                result[i] = data[i] - m_data[i];
            }
            return result;
        }

        /**
         * @brief Operator * betwen  Matrix and int
         * @param int 
         * @return KT::Matrix
         */
        KT::Matrix<type, height, width > operator*(const int& idx)
        {
            KT::Matrix<type, height, width > result;
            for (size_t i = 0; i < m_data.Size(); ++i)
            {
                result[i] = m_data[i] * idx;
            }
            return result;
        }

        /**
         * @brief Operator / betwen Matrix and int
         * @param idx 
         * @return KT::Matrix
         */
        KT::Matrix<type,height,width > operator/(const int& idx)
        {
            if (idx == 0)
                throw std::runtime_error("cannot divide by 0");
            KT::Matrix<type, height, width > result;
            for (size_t i = 0; i < m_data.Size(); ++i)
            {
                result[i] = m_data[i] / idx;
            }
            return result;
        }

        /**
         * @brief Operator == betwen KT::Matrix of same size
         * @param KT::Matrix 
         * @return bool
         */
        bool operator ==(const KT::Matrix<type, height, width >& data)
        {
            for (size_t i = 0; i < m_data.Size(); ++i)
            {
                if (data[i] != m_data[i])
                    return false;
            }
            return true;
        }

        /**
         * @brief Operator != betwen KT::Matrix of same size
         * @param KT::Matrix 
         * @return bool
         */
        bool operator !=(const KT::Matrix<type, height, width >& data)
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
         * @brief Operator == betwen KT::Matrix of same size const
         * @param KT::Matrix
         * @return bool const 
         */
        bool operator ==(const KT::Matrix<type, height, width >& data) const
        {
            for (size_t i = 0; i < m_data.Size(); ++i)
            {
                if (data[i] != m_data[i])
                    return false;
            }
            return true;
        }
        /**
        * @brief Operator != betwen KT::Matrix of same size const
        * @param KT::Matrix
        * @return bool const
        */
        bool operator !=(const KT::Matrix<type, height, width >& data) const
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
        size_t size = width * height;
        KT::Array<type, height* width > m_data;
    };
}

/**
 * @brief display KT::Matrix
 * @tparam value_type 
 * @tparam size_t 
 * @tparam size_t 
 * @param output stream 
 * @param KT::Matrix 
 * @return output stream
 */
template<typename type, size_t height, size_t width>
std::ostream& operator<<(std::ostream& os, const KT::Matrix<type, height, width >& tab)
{
    if (tab.Size() == 0)
        return os;
    for (auto i = 0; i < height; ++i)
    {
        os << "(";
        for (auto j = 0; j < width; ++j)
        {
            os << tab.getCell(i ,j) ;
            if (j != width - 1)
                os << ",";
        }
        os << ")" << std::endl;
    }
       
    return os;
}