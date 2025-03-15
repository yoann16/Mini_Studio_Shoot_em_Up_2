#pragma once 
/*****************************************************************//**
 * @file   KT_Array.h
 * @brief  This file contains the code for KT::List
 *
 * @author Kroktur
 * @date   February 2025
 *********************************************************************/
//include 
#include <exception>
#include <initializer_list>
#include <sstream>
/**
 * @brief Namespace of my library
 */
namespace KT
{
	/**
	 * @brief List
	 * @tparam type 
	 */
	template<typename type>
	class List
	{
	public:
	
		struct Node;
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
		 * @brief Destructor who Clear the List
		 */
		~List() { clear(); }

		/**
		 * @brief default Constructor
		 */
		List() :size(0) { Head.Next = &Tail;  Tail.Previous = &Head; }

		/**
		 * @brief Copy Constructor
		 * @param KT::List 
		 */
		List(const List& tab) :size(0)
		{
			Head.Next = &Tail;  
			Tail.Previous = &Head;
			for (auto it = tab.begin(); it != tab.end(); ++it)
			{
				pushBack(*it);
			}
		}

		/**
		 * @brief Constructor with initializer_list
		 * @param initializer_list 
		 */
		List(const std::initializer_list<type>& list) :size(0)
		{
			Head.Next = &Tail;  Tail.Previous = &Head;
			for (const auto& element : list)
			{
				pushBack(element);
			}
		}

		/**
		 * @brief resize the List
		 * @param size_t
		 */
		void resize(const size_t& idx)
		{
			if (idx < size)
			{
				for (size_t i = size; i > idx; --i)
				{
					popBack();
				}

			}
			if (idx > size)
			{
				for (size_t i = size; i < idx; ++i)
				{
					pushBack(type{});
				}
			}

		}
		/**
		 * @brief
		 * @param KT::List 
		 */
		void swap(List<type>& Newlist)
		{
			List<type> tmp = *this;
			*this = Newlist;
			Newlist = tmp;
		}
		/**
		 * @brief Add an element to the back
		 * @param value_type 
		 */
		void pushBack(const value_type& val)
		{
			Node* NewVal = new Node(val);
			Tail.Previous->Next = NewVal;
			NewVal->Next = &Tail;
			NewVal->Previous = Tail.Previous;
			Tail.Previous = NewVal;
			++size;
		}
		/**
		 * @brief pop the last element 
		 */
		void popBack()
		{
			if (Empty())
				throw std::out_of_range("List is Empty");
			auto todelete = Tail.Previous;
			Tail.Previous = todelete->Previous;
			todelete->Previous->Next = &Tail;

			todelete->Next = nullptr;
			todelete->Previous = nullptr;
			delete todelete;

			--size;
		}
		/**
		 * @brief Add an element to the front
		 * @param value_type 
		 */
		void pushFront(const value_type& val)
		{
			Node* NewVal = new Node(val);
			Head.Next->Previous = NewVal;
			NewVal->Previous = &Head;
			NewVal->Next = Head.Next;
			Head.Next = NewVal;
			++size;
		}
		/**
		 * @brief pop the first element
		 */
		void popFront()
		{
			if (Empty())
				throw std::out_of_range("List is Empty");
			auto todelete = Head.Next;
			Head.Next = todelete->Next;
			todelete->Next->Previous = &Head;

			todelete->Next = nullptr;
			todelete->Previous = nullptr;
			delete todelete;

			--size;
		}
		/**
		 * @brief get an element
		 *
		 * @param size_t idx
		 * @return value_type 
		 */
		reference operator[](const size_t& idx)
		{
			auto it = begin();
			for (auto i = 0; i < idx; ++i)
			{
				++it;
			}
			return *it;

		}
		/**
		 * @brief get an element const 
		 *
		 * @param size_t idx
		 * @return value_type const
		 */
		const_reference operator[](const size_t& idx) const
		{
			auto it = begin();
			for (auto i = 0; i < idx; ++i)
			{
				++it;
			}
			return *it;
		}
		/**
		 * @brief get an element
		 *
		 * @param size_t idx
		 * @return value_type
		 * @throw incompatible size
		 */
		reference at(const size_t& idx)
		{
			if (Empty())
				throw std::out_of_range("vector is empty");
			if (idx >= size)
				throw std::out_of_range("idx out of vector range");
			auto it = begin();
			for (auto i = 0; i < idx; ++i)
			{
				++it;
			}
			return *it;
		}
		/**
		 * @brief get an element const
		 *
		 * @param size_t idx
		 * @return value_type const 
		 * @throw incompatible size
		 */
		const_reference at(const size_t& idx) const
		{
			if (Empty())
				throw std::out_of_range("vector is empty");
			if (idx >= size)
				throw std::out_of_range("idx out of vector range");
			auto it = begin();
			for (auto i = 0; i < idx; ++i)
			{
				++it;
			}
			return *it;
		}

		/**
		 * @brief return if Empty
		 * @return bool
		 */
		bool Empty()
		{
			return size == 0;
		}
		/**
		 * @brief return if Empty const
		 * @return bool const
		 */
		bool Empty() const
		{
			return size == 0;
		}

		/**
		 * @brief Get The size of the container
		 * @return size_t 
		 */
		size_t Size()
		{
			return size;
		}
		/**
		 * @brief Get The size of the container const
		 * @return size_t const 
		 */
		size_t Size() const
		{
			return size;
		}
		/**
		 * @brief erase an element
		 *
		 * @param Iterator
		 */
		void erase(const iterator& it)
		{
			if (find(it) == end())
				throw std::out_of_range("out of range");
			auto supr = it.m_node;
			supr->Previous->Next = supr->Next;
			supr->Next->Previous = supr->Previous;

			delete supr;

			--size;
		}
		/**
		* @brief get Iterator on the first element
		*
		* @return Iterator
		*/
		iterator begin()
		{
			return iterator(Head.Next);
		}
		/**
		* @brief get Const_Iterator on the first element
		*
		* @return Const_Iterator
		*/
		const_iterator begin() const
		{
			return const_iterator(Head.Next);
		}
		/**
		* @brief get Iterator on the last element
		*
		* @return Iterator
		*/
		iterator end()
		{
			return iterator(&Tail);
		}
		/**
		* @brief get Const_Iterator on the last element
		*
		* @return Const_Iterator
		*/
		const_iterator end() const
		{
			return const_iterator(&Tail);
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
			return Head.Next->data;
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
			return Head.Next->data;
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
			return Tail.Previous->data;
		}
		/**
		* @brief get last element const 
		*
		* @return reference const
		* @throw out_of_range if empty
		*/
		const_reference back() const
		{
			if (Empty())
				throw std::out_of_range("Array is empty");
			return Tail.Previous->data;
		}
		/**
		 * @brief Clear the Container
		 *
		 */
		void clear()
		{
			while (!Empty())
				popFront();
			resize(0);
		}

		/**
		 * @brief Assign new value to the container
		 * @param KT::List 
		 * @return KT::List reference
		 */
		List& operator=(const List& tab)
		{
			clear();
			for (auto it = tab.begin(); it != tab.end(); ++it)
			{
				pushBack(*it);
			}
			return *this;
		}

		/**
		 * @brief Assign new value betwen Iterator
		 * @param Iterator begin 
		 * @param Iterator end 
		 */
		void assign(const iterator& begin, const iterator& end)
		{
			clear();
			for (auto it = begin; it != end; ++it)
			{
				pushBack(*it);
			}
		}

		/**
		 * @brief Assign new value in range of size
		 * @param size_t size 
		 * @param value_type
		 */
		void assign(const size_t& sizeofvec, const value_type& data)
		{
			clear();
			for (size_t i = 0; i < sizeofvec; ++i)
			{
				pushBack(data);
			}
		}

		/**
		 * @brief Assign new KT::List
		 * @param KT::List 
		 */
		void assign(const std::initializer_list<type>& list)
		{
			clear();
			for (const auto& element : list)
			{
				pushBack(element);
			}
		}
		/**
		* @brief get Reverse_Iterator on the first element
		*
		* @return Reverse_Iterator
		*/
		reverse_iterator rbegin()
		{
			return reverse_iterator(Tail.Previous);
		}
		/**
		* @brief get Const_Reverse_Iterator on the first element
		*
		* @return Const_Reverse_Iterator
		*/
		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(Tail.Previous);
		}
		/**
		* @brief get Reverse_Iterator on the last element
		*
		* @return Reverse_Iterator
		*/
		reverse_iterator rend()
		{
			return reverse_iterator(&Head);
		}
		/**
		* @brief get Const_Reverse_Iterator on the last element
		*
		* @return Const_Reverse_Iterator
		*/
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(&Head);
		}

		/**
		 * @brief return the max size
		 * @return size_t 
		 */
		size_t max_size()
		{
			return std::numeric_limits<size_t>::max() / sizeof(type);
		}
		/**
		 * @brief return the max size const
		 * @return size_t const
		 */
		size_t max_size() const
		{
			return std::numeric_limits<size_t>::max() / sizeof(type);
		}

		/**
		 * @brief Insert an element
		 * @param Iterator position
		 * @param value_type 
		 */
		void insert(const iterator&  newit, const value_type& value)
		{
			if (find(newit) == end())
				throw std::out_of_range("Out of range");
			auto oldnode = newit.m_node;
			Node* nodetoadd = new Node(value);
			nodetoadd->Next = oldnode;
			nodetoadd->Previous = oldnode->Previous;
			oldnode->Previous->Next = nodetoadd;
			oldnode->Previous = nodetoadd;
			++size;
		}

		/**
		 * @brief find an element in the Container 
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
		 * @brief find an element in the Container const 
		 * @param Const_itrator
		 * @return Const_itrator
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

		struct Node
		{
			Node() :Next(nullptr), Previous(nullptr)
			{
			}
			Node( type val) :data(val), Next(nullptr), Previous(nullptr)
			{
			}
			type data;
			Node* Next;
			Node* Previous;
		};

		struct iterator {
			//this iterator compatible with stl
			using iterator_category = std::random_access_iterator_tag;
			using value_type = type;
			using difference_type = std::ptrdiff_t;
			using pointer = type*;
			using reference = type&;
			friend List;
			iterator(Node* ptr) : m_node(ptr) {}
			reference operator*()
			{
				return m_node->data;
			}
			const reference operator*() const
			{
				return m_node->data;
			}
			Node* operator->()
			{
				return m_node;
			}
			const Node* operator->() const
			{
				return m_node;
			}
			iterator& operator++()
			{
				m_node = m_node->Next;
				return *this;
			}
			iterator& operator--()
			{
				m_node = m_node->Previous;
				return *this;
			}
			iterator operator+(difference_type n) const
			{
				auto curentnode = m_node;
				for (size_t i = 0; i < n; ++i)
				{
					curentnode = curentnode->Next;
				}
				return iterator(curentnode);
			}
			iterator operator-(difference_type n) const
			{
				auto curentnode = m_node;
				for (size_t i = 0; i < n; ++i)
				{
					curentnode = curentnode->Previous;
				}
				return iterator(curentnode);
			}
			difference_type operator-(const iterator& other) const
			{
				difference_type diff = 0;
				for(auto it = *this; it != other ; --it)
				{
					++diff;
				}
				return diff;
			}
			difference_type operator+(const iterator& other) const
			{
				difference_type diff = 0;
				for (auto it = *this; it != other; ++it)
				{
					++diff;
				}
				return diff;
			}
			bool operator==(const iterator& other) const
			{
				return m_node == other.m_node;
			}
			bool operator!=(const iterator& other) const
			{
				return m_node != other.m_node;
			}
			bool operator<(const iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					curent = curent->Next;
					if (curent == other.m_node)
						return true;
					
				}
				return false;
			}
			bool operator>(const iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					curent = curent->Previous;
					if (curent == other.m_node)
						return true;

				}
				return false;
			}
			bool operator<=(const iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					if (curent == other.m_node)
						return true;
					curent = curent->Next;
				}
				return false;
			}
			bool operator>=(const iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					if (curent == other.m_node)
						return true;
					curent = curent->Previous;
				}
				return false;
			}
		private:
			Node* m_node;
		};
		struct const_iterator {
			//this iterator compatible with stl
			using iterator_category = std::random_access_iterator_tag;
			using value_type = const type;
			using difference_type = std::ptrdiff_t;
			using pointer = const type*;
			using reference = const type&;
			friend List;
			const_iterator(const Node* ptr) : m_node(ptr) {}
			reference operator*()
			{
				return m_node->data;
			}
			reference operator*() const
			{
				return m_node->data;
			}
			Node* operator->()
			{
				return m_node;
			}
			const Node* operator->() const
			{
				return m_node;
			}
			const_iterator& operator++()
			{
				m_node = m_node->Next;
				return *this;
			}
			const_iterator& operator--()
			{
				m_node = m_node->Previous;
				return *this;
			}
			const_iterator operator+(difference_type n) const
			{
				auto curentnode = m_node;
				for (size_t i = 0; i < n; ++i)
				{
					curentnode = curentnode->Next;
				}
				return const_iterator(curentnode);
			}
			const_iterator operator-(difference_type n) const
			{
				auto curentnode = m_node;
				for (size_t i = 0; i < n; ++i)
				{
					curentnode = curentnode->Previous;
				}
				return const_iterator(curentnode);
			}
			difference_type operator-(const const_iterator& other) const
			{
				difference_type diff = 0;
				for (auto it = *this; it != other; --it)
				{
					++diff;
				}
				return diff;
			}
			difference_type operator+(const const_iterator& other) const
			{
				difference_type diff = 0;
				for (auto it = *this; it != other; ++it)
				{
					++diff;
				}
				return diff;
			}
			bool operator==(const const_iterator& other) const
			{
				return m_node == other.m_node;
			}
			bool operator!=(const const_iterator& other) const
			{
				return m_node != other.m_node;
			}
			bool operator<(const const_iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					curent = curent->Next;
					if (curent == other.m_node)
						return true;

				}
				return false;
			}
			bool operator>(const const_iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					curent = curent->Previous;
					if (curent == other.m_node)
						return true;

				}
				return false;
			}
			bool operator<=(const const_iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					if (curent == other.m_node)
						return true;
					curent = curent->Next;
				}
				return false;
			}
			bool operator>=(const const_iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					if (curent == other.m_node)
						return true;
					curent = curent->Previous;
				}
				return false;
			}
		private:
			const Node* m_node;
		};
		struct reverse_iterator {
			//this iterator compatible with stl
			using iterator_category = std::random_access_iterator_tag;
			using value_type = type;
			using difference_type = std::ptrdiff_t;
			using pointer = type*;
			using reference = type&;
			friend List;
			reverse_iterator(Node* ptr) : m_node(ptr) {}
			reference operator*()
			{
				return m_node->data;
			}
			const reference operator*() const
			{
				return m_node->data;
			}
			Node* operator->()
			{
				return m_node;
			}
			const Node* operator->() const
			{
				return m_node;
			}
			reverse_iterator& operator++()
			{
				m_node = m_node->Previous;
				return *this;
			}
			reverse_iterator& operator--()
			{
				m_node = m_node->Next;
				return *this;
			}
			reverse_iterator operator+(difference_type n) const
			{
				auto curentnode = m_node;
				for (size_t i = 0; i < n; ++i)
				{
					curentnode = curentnode->Previous;
				}
				return reverse_iterator(curentnode);
			}
			reverse_iterator operator-(difference_type n) const
			{
				auto curentnode = m_node;
				for (size_t i = 0; i < n; ++i)
				{
					curentnode = curentnode->Next;
				}
				return reverse_iterator(curentnode);
			}
			difference_type operator-(const reverse_iterator& other) const
			{
				difference_type diff = 0;
				for (auto it = *this; it != other; --it)
				{
					++diff;
				}
				return diff;
			}
			difference_type operator+(const reverse_iterator& other) const
			{
				difference_type diff = 0;
				for (auto it = *this; it != other; ++it)
				{
					++diff;
				}
				return diff;
			}
			bool operator==(const reverse_iterator& other) const
			{
				return m_node == other.m_node;
			}
			bool operator!=(const reverse_iterator& other) const
			{
				return m_node != other.m_node;
			}
			bool operator<(const reverse_iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					curent = curent->Previous;
					if (curent == other.m_node)
						return true;

				}
				return false;
			}
			bool operator>(const reverse_iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					curent = curent->Next;
					if (curent == other.m_node)
						return true;

				}
				return false;
			}
			bool operator<=(const reverse_iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					if (curent == other.m_node)
						return true;
					curent = curent->Previous;
				}
				return false;
			}
			bool operator>=(const reverse_iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					if (curent == other.m_node)
						return true;
					curent = curent->Next;
				}
				return false;
			}
		private:
			Node* m_node;
		};
		struct const_reverse_iterator {
			//this iterator compatible with stl
			using iterator_category = std::random_access_iterator_tag;
			using value_type = const type;
			using difference_type = std::ptrdiff_t;
			using pointer = const type*;
			using reference = const type&;
			friend List;
			const_reverse_iterator(const Node* ptr) : m_node(ptr) {}
			reference operator*()
			{
				return m_node->data;
			}
			const reference operator*() const
			{
				return m_node->data;
			}
			Node* operator->()
			{
				return m_node;
			}
			const Node* operator->() const
			{
				return m_node;
			}
			const_reverse_iterator& operator++()
			{
				m_node = m_node->Previous;
				return *this;
			}
			const_reverse_iterator& operator--()
			{
				m_node = m_node->Next;
				return *this;
			}
			const_reverse_iterator operator+(difference_type n) const
			{
				auto curentnode = m_node;
				for (size_t i = 0; i < n; ++i)
				{
					curentnode = curentnode->Previous;
				}
				return const_reverse_iterator(curentnode);
			}
			const_reverse_iterator operator-(difference_type n) const
			{
				auto curentnode = m_node;
				for (size_t i = 0; i < n; ++i)
				{
					curentnode = curentnode->Next;
				}
				return const_reverse_iterator(curentnode);
			}
			difference_type operator-(const const_reverse_iterator& other) const
			{
				difference_type diff = 0;
				for (auto it = *this; it != other; --it)
				{
					++diff;
				}
				return diff;
			}
			difference_type operator+(const const_reverse_iterator& other) const
			{
				difference_type diff = 0;
				for (auto it = *this; it != other; ++it)
				{
					++diff;
				}
				return diff;
			}
			bool operator==(const const_reverse_iterator& other) const
			{
				return m_node == other.m_node;
			}
			bool operator!=(const const_reverse_iterator& other) const
			{
				return m_node != other.m_node;
			}
			bool operator<(const const_reverse_iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					curent = curent->Previous;
					if (curent == other.m_node)
						return true;

				}
				return false;
			}
			bool operator>(const const_reverse_iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					curent = curent->Next;
					if (curent == other.m_node)
						return true;

				}
				return false;
			}
			bool operator<=(const const_reverse_iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					if (curent == other.m_node)
						return true;
					curent = curent->Previous;
				}
				return false;
			}
			bool operator>=(const const_reverse_iterator& other) const
			{
				auto curent = m_node;
				while (curent != nullptr)
				{
					if (curent == other.m_node)
						return true;
					curent = curent->Next;
				}
				return false;
			}

		private:
			const Node* m_node;
		};
		Node Head;
		Node Tail;
		size_t size;
	};

}

/**
 * @brief display KT::List
 * @tparam type 
 * @param output stream 
 * @param KT::List 
 * @return output stream
 */
template<typename type>
std::ostream& operator<<(std::ostream& os,  KT::List<type> tab)
{
	if (tab.Empty())
		return os;
	os << "(";
	for (auto i = 0; i < tab.Size() - 1; ++i)
		os << tab[i] << ", ";
	os << tab[tab.Size() - 1] << ")";
	return os;
}