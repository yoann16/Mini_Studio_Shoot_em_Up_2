#pragma once 
/*****************************************************************//**
 * @file   KT_Array.h
 * @brief  This file contains the code for KT::IntrusiveList
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
	 * @brief Node for the IntrusiveList
	 * @tparam type
	 */
	template <typename type>
	struct Node
	{
			/**
			 * @brief default constructor
			 * 
			 */
			Node() :Next(nullptr), Previous(nullptr)
			{
			}
			/**
			 * @brief constructor
			 * 
			 * @param type
			 */
			Node(type val) :data(val), Next(nullptr), Previous(nullptr)
			{
			}
			type data;
			Node<type>* Next;
			Node<type>* Previous;
			void operator=(const Node& other)
			{
				data = other.data;
			}
			bool operator==(const Node& other) const
			{
				return data == other.data;
			}
			bool operator!=(const Node& other) const
			{
				return data != other.data;
			}
			bool operator<(const Node& other) const
			{
				return data < other.data;
			}
			bool operator>(const Node& other) const
			{
				return data > other.data;
			}
			bool operator<=(const Node& other) const
			{
				return data <= other.data;
			}
			bool operator>=(const Node& other) const
			{
				return data >= other.data;
			}
	};
	/**
     * @brief operator overload << for display
	 *
	 * @tparam type
	 * @param output stream
	 * @param KT::IntrusiveList
	 * @return output stream
	 */
	template <typename type>
	std::ostream& operator<<(std::ostream& os, const Node<type>& node)
	{
		return os << node.data;
	}
	/**
	 * @brief IntrusiveList
	 * @tparam type
	 */
	template<typename type>
	class IntrusiveList
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
		using value_type = KT::Node<type>;
		using pointer = KT::Node<type>*;
		using const_pointer = const KT::Node<type>*;
		using reference = KT::Node<type>&;
		using const_reference = const KT::Node<type>&;
		/**
		 * @brief default destructor
		 * 
		 */
		~IntrusiveList() { clear(); }
		/**
		 * @brief default constructor
		 * 
		 */
		IntrusiveList() :size(0) { Head.Next = &Tail;  Tail.Previous = &Head; }
		/**
		 * @brief Copy Constructor
		 * 
		 * @param KT::IntrusiveList
		 */
		IntrusiveList(const IntrusiveList& tab) :size(0)
		{
			Head.Next = &Tail;
			Tail.Previous = &Head;
			for (auto it = tab.begin(); it != tab.end(); ++it)
			{
				pushBack(*it);
			}
		}
		/**
		 * @brief Constructor with Initialize_list
		 *
		 * @param Initialize_list
		 */
		IntrusiveList(const std::initializer_list<KT::Node<type>>& list) :size(0)
		{
			Head.Next = &Tail;  Tail.Previous = &Head;
			for (const auto& element : list)
			{
				pushBack(element);
			}
		}
		/**
		 * @brief resize The container
		 * 
		 * @param Size_t 
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
		 * @brief Swaps the content of this IntrusiveList with another IntrusiveList of the same type.
		 *
		 * @param IntrusiveList
		 */
		void swap(IntrusiveList<type>& Newlist)
		{
			IntrusiveList<type> tmp = *this;
			*this = Newlist;
			Newlist = tmp;
		}
		/**
		 * @brief PushBack
		 * 
		 * @param Node
		 */
		void pushBack(const value_type& val)
		{
			pointer NewVal = new KT::Node(val.data);
			Tail.Previous->Next = NewVal;
			NewVal->Next = &Tail;
			NewVal->Previous = Tail.Previous;
			Tail.Previous = NewVal;
			++size;
		}
		/**
		 * @brief PopBack
		 * 
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
		 * @brief PushFront
		 *
		 * @param Node
		 */
		void pushFront(const value_type& val)
		{
			pointer NewVal = new KT::Node(val.data);
			Head.Next->Previous = NewVal;
			NewVal->Previous = &Head;
			NewVal->Next = Head.Next;
			Head.Next = NewVal;
			++size;
		}
		/**
		 * @brief PopFront
		 * 
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
		 * @return Node reference
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
		 * @return Node reference const 
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
		* @brief get an element with verification
		*
		* @param size_t idx
		* @return Node reference
		* @throw out_of_range if idx out of range
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
		* @brief get an element const with verification
		*
		* @param size_t idx
		* @return Node reference const 
		* @throw out_of_range if idx out of range
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
		* @brief empty verification
		*
		* @return bool
		*/
		bool Empty()
		{
			return size == 0;
		}
		/**
		* @brief empty verification
		*
		* @return bool const
		*/
		bool Empty() const
		{
			return size == 0;
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
		* @brief get Iterator on the first element
		*
		* @return Iterator

		*/
		iterator end()
		{
			return iterator(&Tail);
		}
		/**
		* @brief get Const_Iterator on the first element
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
			return *Head.Next;
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
			return *Head.Next;
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
			return *Tail.Previous;
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
			return *Tail.Previous;
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
		 * @brief overloading the equals operator
		 *
		 * @param KT::IntrusiveList
		 * @return reference KT::IntrusiveList
		 */
		IntrusiveList& operator=(const IntrusiveList& tab)
		{
			clear();
			for (auto it = tab.begin(); it != tab.end(); ++it)
			{
				pushBack(*it);
			}
			return *this;
		}
		/**
		 * @brief Assign with another IntrusiveList
		 * 
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
		 * @brief Assign with a size and a data
		 * 
		 * @param size_t 
		 * @param Node 
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
		 * @brief Assign with initialize_list
		 * 
		 * @param initialize_list
		 */
		void assign(const std::initializer_list<KT::Node<type>>& list)
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
		* @brief get Const_Reverse_Iterator on the first element
		*
		* @return Const_Reverse_Iterator
		*/
		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(&Head);
		}
		/**
		 * @brief get the max size 
		 * @return size_t
		 */
		size_t max_size()
		{
			return std::numeric_limits<size_t>::max() / sizeof(type);
		}
		/**
		 * @brief get the max size const
		 * @return size_t const
		 */
		size_t max_size() const
		{
			return std::numeric_limits<size_t>::max() / sizeof(type);
		}
		/**
		 * @brief Insert an element to a place 
		 * @param Iterator 
		 * @param Node 
		 */
		void insert(const iterator& newit, const value_type& value)
		{
			if (find(newit) == end())
				throw std::out_of_range("Out of range");
			auto oldnode = newit.m_node;
			pointer nodetoadd = new KT::Node<type>(value.data);
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

		

		struct iterator {
			//this iterator compatible with stl
			using iterator_category = std::random_access_iterator_tag;
			using value_type = KT::Node<type>;
			using difference_type = std::ptrdiff_t;
			using pointer = KT::Node<type>*;
			using reference = KT::Node<type>&;
			friend IntrusiveList;
			iterator(pointer ptr) : m_node(ptr) {}
			reference operator*()
			{
				return *m_node;
			}
			const reference  operator*() const
			{
				return *m_node;
			}
			pointer operator->()
			{
				return m_node;
			}
			const pointer operator->() const
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
				for (auto it = *this; it != other; --it)
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
			pointer m_node;
		};
		struct const_iterator {
			//this iterator compatible with stl
			using iterator_category = std::random_access_iterator_tag;
			using value_type = const KT::Node<type>;
			using difference_type = std::ptrdiff_t;
			using pointer = const KT::Node<type>*;
			using reference = const KT::Node<type>&;
			friend IntrusiveList;
			const_iterator(pointer ptr) : m_node(ptr) {}
			reference operator*()
			{
				return *m_node;
			}
			reference operator*() const
			{
				return *m_node;
			}
			pointer operator->()
			{
				return m_node;
			}
			pointer operator->() const
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
			pointer m_node;
		};
		struct reverse_iterator {
			//this iterator compatible with stl
			using iterator_category = std::random_access_iterator_tag;
			using value_type = KT::Node<type>;
			using difference_type = std::ptrdiff_t;
			using pointer = KT::Node<type>*;
			using reference = KT::Node<type>&;
			friend IntrusiveList;
			reverse_iterator(pointer ptr) : m_node(ptr) {}
			reference operator*()
			{
				return *m_node;
			}
			const reference  operator*() const
			{
				return *m_node;
			}
			pointer operator->()
			{
				return m_node;
			}
			const pointer operator->() const
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
			pointer m_node;
		};
		struct const_reverse_iterator {
			//this iterator compatible with stl
			using iterator_category = std::random_access_iterator_tag;
			using value_type = const KT::Node<type>;
			using difference_type = std::ptrdiff_t;
			using pointer = const KT::Node<type>*;
			using reference = const KT::Node<type>&;
			friend IntrusiveList;
			const_reverse_iterator(pointer ptr) : m_node(ptr) {}
			reference operator*()
			{
				return *m_node;
			}
			const reference  operator*() const
			{
				return *m_node;
			}
			pointer operator->()
			{
				return m_node;
			}
			const pointer operator->() const
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
			pointer m_node;
		};
		KT::Node<type> Head;
		KT::Node<type> Tail;
		size_t size;
	};
}
/**
 * @brief operator overload << for display
 *
 * @tparam value_type
 * @param output stream
 * @param KT::IntrusiveList
 * @return output stream
 */
template< typename type>
std::ostream& operator<<(std::ostream& os, const KT::IntrusiveList<type>& tab)
{
	if (tab.Empty())
		return os;
	os << "(";
	for (auto i = 0; i < tab.Size() - 1; ++i)
		os << tab[i] << ", ";
	os << tab[tab.Size() - 1] << ")";
	return os;
}