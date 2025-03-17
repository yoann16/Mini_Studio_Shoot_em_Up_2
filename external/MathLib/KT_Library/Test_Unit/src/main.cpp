#include "KT_Algorithm.h"
#include "Test.h"
#include"KT_Container.h"
#include "KT_Math_Algorithm.h"
#include "KT_VectorND.h"


int main()
{
	{
		Test_Units Test("Test_Array_Constructor");
		KT::Array<int, 3> DefaultConstructor;
		Test.testresult(DefaultConstructor[0], 0, "Test_Default value");
		KT::Array<int, 3>InitialiszeListConstructor{1,2,3};
		Test.testresult(InitialiszeListConstructor[0], 1, "Test_First value");
		KT::Array<int, 3>CopyConstructor = InitialiszeListConstructor;
		Test.testresult(CopyConstructor[2], InitialiszeListConstructor[2], "test_Copy value");
	}
	{
		Test_Units Test("Test_Array_Operator");
		KT::Array<int, 3> array{ 1,2,3 };
		KT::Array<int, 3> ArrayCopy{ 5,5,5 };
		Test.testresult(array[2], 3,  "Test_Operator[]");
		Test.testresult(array.at(0), 1, "Test_at()");
		array = ArrayCopy;
		Test.testresult(array[0], ArrayCopy[0], "test_Operator =");
		array = { 1,2,3 };
		ArrayCopy.swap(array);
		Test.testresult(ArrayCopy[0], 1, "test swap");
		ArrayCopy[0] = 100;
		Test.testresult(ArrayCopy[0], 100, "test assignation");
	}
	{
		Test_Units Test("test_Array_Iterator");
		KT::Array<int, 3> IteratorTest{5, 1, 3};
		Test.testresult(*IteratorTest.begin(), 5, "Test_Iterator_begin");
		Test.testresult(*IteratorTest.begin(), *(IteratorTest.rend() - 1), "test_Iterator and reverse Iterator");
		KT::Array<int, 3>::reverse_iterator ri = IteratorTest.rbegin();
		++ri;
		Test.testresult(*ri, IteratorTest[1], "test_++Operator");
		KT::Array<int, 3>::iterator ni = IteratorTest.end();
		--ni;
		Test.testresult(*ni, IteratorTest[2], "test_--Operator");
	}
	{
		Test_Units Test("Test_Array_function");
		KT::Array<int, 3 > array;
		Test.testresult(array.front(), array[0], "test_front");
		Test.testresult(array.back(), array[2],"test_back");
		Test.testresult(array.Size(), 3, "test_size");
		Test.testresult(array.max_size(), 3, "test max_size");
		Test.testresult(*array.data(), 0, "test data");
	}
	{
		Test_Units Test(" Const Test_Array_Constructor");
		const KT::Array<int, 3> DefaultConstructor;
		Test.testresult(DefaultConstructor[0], 0, "Test_Default value");
		const KT::Array<int, 3>InitialiszeListConstructor{ 1,2,3 };
		Test.testresult(InitialiszeListConstructor[0], 1, "Test_First value");
		const KT::Array<int, 3>CopyConstructor = InitialiszeListConstructor;
		Test.testresult(CopyConstructor[2], InitialiszeListConstructor[2], "test_Copy value");
	}
	{
		Test_Units Test(" const Test_Array_Operator");
		const KT::Array<int, 3> array{ 1,2,3 };
		const KT::Array<int, 3> ArrayCopy{ 5,5,5 };
		Test.testresult(array[2], 3, "Test_Operator[]");
		Test.testresult(array.at(0), 1, "Test_at()");
	}
	{
		Test_Units Test(" const test_Array_Iterator");
		const KT::Array<int, 3> IteratorTest{ 5, 1, 3 };
		Test.testresult(*IteratorTest.begin(), 5, "Test_Iterator_begin");
		Test.testresult(*IteratorTest.begin(), *(IteratorTest.rend() - 1), "test_Iterator and reverse Iterator");
		KT::Array<int, 3>::const_reverse_iterator ri = IteratorTest.rbegin();
		++ri;
		Test.testresult(*ri, IteratorTest[1], "test_++Operator");
		KT::Array<int, 3>::const_iterator ni = IteratorTest.end();
		--ni;
		Test.testresult(*ni, IteratorTest[2], "test_--Operator");
	}
	{
		Test_Units Test("const Test_Array_function");
		const KT::Array<int, 3 > array;
		Test.testresult(array.front(), array[0], "test_front");
		Test.testresult(array.back(), array[2], "test_back");
		Test.testresult(array.Size(), 3, "test_size");
		Test.testresult(array.max_size(), 3, "test max_size");
		Test.testresult(*array.data(), 0, "test data");
	}
	{
		Test_Units Test("Algorithme on Array");
		KT::Array<int, 3> array;
		KT::Math::Fill(array.begin(), array.end(), 5);
		Test.testresult(array[0], 5, "test KT::Fill");
		std::fill(array.begin(), array.end(), 10);
		Test.testresult(array[0], 10, "test std::fill");
		KT::Array<int, 3> arraycopy;
		KT::Math::Copy(array.begin(), array.end(), arraycopy.data());
		Test.testresult(arraycopy[0], 10, "test KT::copy");
		array = { 0,0,0 };
		std::copy(array.begin(), array.end(), arraycopy.data());
		Test.testresult(arraycopy[0], 0, "test std::copy");

	}
	{
		Test_Units Test("Sort on Array");
		KT::Array<int, 5> array{5,4,3,2,1};
		KT::Algorithm::Sort<KT::Array<int,5>,KT::Algorithm::BubbleSort>(array);
		Test.testresult(array[0], 1, "test bubblesort");
		array = { 1,2,3,4,5 };
		KT::Algorithm::Sort<KT::Array<int, 5>, KT::Algorithm::FusionSort>(array);
		Test.testresult(array[0], 1, "test fusionsort");
		array = { 1,2,3,4,5 };
		KT::Algorithm::Sort<KT::Array<int, 5>, KT::Algorithm::InsertionSort>(array);
		Test.testresult(array[0], 1, "test insertionsort");
	}
	{
		Test_Units Test("Test_Vector_Constructor");
		KT::Vector<int> DefaultConstructor;
		Test.testresult(DefaultConstructor.Size(), 0, "default size value");
		KT::Vector<int>InitialiszeListConstructor{ 1,2,3 };
		Test.testresult(InitialiszeListConstructor[2], 3, "Test value");
		KT::Vector<int>CopyConstructor = InitialiszeListConstructor;
		Test.testresult(CopyConstructor[2], InitialiszeListConstructor[2], "test_Copy value");
	}
	{
		Test_Units Test("Test_Vector_Operator");
		KT::Vector<int> vector{ 1,2,3 };
		KT::Vector<int > vectorCopy{ 5,5,5 };
		Test.testresult(vector[2], 3, "Test_Operator[]");
		Test.testresult(vector.at(0), 1, "Test_at()");
		vector = vectorCopy;
		Test.testresult(vector[0], vectorCopy[0], "test_Operator =");
		vector = { 1,2,3 };
		vectorCopy.swap(vector);
		Test.testresult(vectorCopy[0], 1, "test swap");
		vectorCopy[0] = 100;
		Test.testresult(vectorCopy[0], 100, "test assignation");
	}
	{
		Test_Units Test("test_Vector_Iterator");
		KT::Vector<int> IteratorTest{ 5, 1, 3 };
		Test.testresult(*IteratorTest.begin(), 5, "Test_Iterator_begin");
		Test.testresult(*IteratorTest.begin(), *(IteratorTest.rend() - 1), "test_Iterator and reverse Iterator");
		KT::Vector<int>::reverse_iterator ri = IteratorTest.rbegin();
		++ri;
		Test.testresult(*ri, IteratorTest[1], "test_++Operator");
		KT::Vector<int>::iterator ni = IteratorTest.end();
		--ni;
		Test.testresult(*ni, IteratorTest[2], "test_--Operator");
	}
	{
		Test_Units Test("Test_Vector_function");
		KT::Vector<int> vector{0,0,0};
		Test.testresult(vector.front(), vector[0], "test_front");
		Test.testresult(vector.back(), vector[2], "test_back");
		Test.testresult(vector.Size(), 3, "test_size");
		Test.testresult(*vector.data(), 0, "test data");
		vector.pushBack(100);
		Test.testresult(vector.back(), 100, "test pushback");
		vector.popBack();
		Test.testresult(vector.back(), 0, "test popback");
		vector.erase(vector.begin());
		Test.testresult(vector.Size(), 2, "test erase");
		KT::Vector<int> vector2{ 5,5,5 };
		vector.reserve(100);
		Test.testresult(vector.Capacity(), 100, "test capacity");
		vector.assign({ 1,1,1 });
		Test.testresult(vector[0], 1, "test Assign initializelist");
		vector.assign(5, 12);
		Test.testresult(vector[4], 12, "test Assign size");
		vector.assign(vector2.begin(), vector2.end());
		Test.testresult(vector[0], 5, "test Assign Iterator");
	}
	{
		Test_Units Test("const Test_Vector_Constructor");
		const KT::Vector<int> DefaultConstructor;
		Test.testresult(DefaultConstructor.Size(), 0, "default size value");
		const KT::Vector<int>InitialiszeListConstructor{ 1,2,3 };
		Test.testresult(InitialiszeListConstructor[2], 3, "Test value");
		const KT::Vector<int>CopyConstructor = InitialiszeListConstructor;
		Test.testresult(CopyConstructor[2], InitialiszeListConstructor[2], "test_Copy value");
	}
	{
		Test_Units Test("const Test_Vector_Operator");
		const KT::Vector<int> vector{ 1,2,3 };
		const KT::Vector<int > vectorCopy{ 5,5,5 };
		Test.testresult(vector[2], 3, "Test_Operator[]");
		Test.testresult(vector.at(0), 1, "Test_at()");
	}
	{
		Test_Units Test("const test_Vector_Iterator");
		const KT::Vector<int> IteratorTest{ 5, 1, 3 };
		Test.testresult(*IteratorTest.begin(), 5, "Test_Iterator_begin");
		Test.testresult(*IteratorTest.begin(), *(IteratorTest.rend() - 1), "test_Iterator and reverse Iterator");
		KT::Vector<int>::const_reverse_iterator ri = IteratorTest.rbegin();
		++ri;
		Test.testresult(*ri, IteratorTest[1], "test_++Operator");
		KT::Vector<int>::const_iterator ni = IteratorTest.end();
		--ni;
		Test.testresult(*ni, IteratorTest[2], "test_--Operator");
	}
	{
		Test_Units Test("const Test_Vector_function");
		const KT::Vector<int> vector{ 0,0,0 };
		Test.testresult(vector.front(), vector[0], "test_front");
		Test.testresult(vector.back(), vector[2], "test_back");
		Test.testresult(vector.Size(), 3, "test_size");
		Test.testresult(*vector.data(), 0, "test data");
	}
	{
		Test_Units Test("Algorithme on Vector");
		KT::Vector<int> vector{0,0,0};
		KT::Math::Fill(vector.begin(), vector.end(), 5);
		Test.testresult(vector[0], 5, "test KT::Fill");
		std::fill(vector.begin(), vector.end(), 10);
		Test.testresult(vector[0], 10, "test std::fill");
		KT::Vector<int> arraycopy{0,0,0};
		KT::Math::Copy(vector.begin(), vector.end(), arraycopy.data());
		Test.testresult(arraycopy[0], 10, "test KT::copy");
		vector = { 0,0,0 };
		std::copy(vector.begin(), vector.end(), arraycopy.data());
		Test.testresult(arraycopy[0], 0, "test std::copy");
	}
	{
		Test_Units Test("Sort on Vector");
		KT::Vector<int> vector{ 5,4,3,2,1 };
		KT::Algorithm::Sort<KT::Vector<int>, KT::Algorithm::BubbleSort>(vector);
		Test.testresult(vector[0], 1, "test bubblesort");
		vector = { 1,2,3,4,5 };
		KT::Algorithm::Sort<KT::Vector<int>, KT::Algorithm::FusionSort>(vector);
		Test.testresult(vector[0], 1, "test fusionsort");
		vector = { 1,2,3,4,5 };
		KT::Algorithm::Sort<KT::Vector<int>, KT::Algorithm::InsertionSort>(vector);
		Test.testresult(vector[0], 1, "test insertionsort");
	}
	{
		Test_Units Test("Test_List_Constructor");
		KT::List<int> DefaultConstructor;
		Test.testresult(DefaultConstructor.Size(), 0, "default size value");
		KT::List<int>InitialiszeListConstructor{ 1,2,3 };
		Test.testresult(InitialiszeListConstructor[2], 3, "Test value");
		KT::List<int>CopyConstructor = InitialiszeListConstructor;
		Test.testresult(CopyConstructor[2], InitialiszeListConstructor[2], "test_Copy value");
	}
	{
		Test_Units Test("Test_List_Operator");
		KT::List<int> list{ 1,2,3 };
		KT::List<int> listcopy{ 5,5,5 };
		Test.testresult(list[2], 3, "Test_Operator[]");
		Test.testresult(list.at(0), 1, "Test_at()");
		list = listcopy;
		Test.testresult(list[0], listcopy[0], "test_Operator =");
		list = { 1,2,3 };
		listcopy.swap(list);
		Test.testresult(listcopy[0], 1, "test swap");
		listcopy[0] = 100;
		Test.testresult(listcopy[0], 100, "test assignation");
	}
	{
		Test_Units Test("test_List_Iterator");
		KT::List<int> IteratorTest{ 5, 1, 3 };
		Test.testresult(*IteratorTest.begin(), 5, "Test_Iterator_begin");
		Test.testresult(*IteratorTest.begin(), *(IteratorTest.rend() - 1), "test_Iterator and reverse Iterator");
		KT::List<int>::reverse_iterator ri = IteratorTest.rbegin();
		++ri;
		Test.testresult(*ri, IteratorTest[1], "test_++Operator");
		KT::List<int>::iterator ni = IteratorTest.end();
		--ni;
		Test.testresult(*ni, IteratorTest[2], "test_--Operator");
	}
	{
		Test_Units Test("Test_List_function");
		KT::List<int> list{ 0,0,0 };
		Test.testresult(list.front(), list[0], "test_front");
		Test.testresult(list.back(), list[2], "test_back");
		Test.testresult(list.Size(), 3, "test_size");
		Test.testresult(*list.begin(), 0, "test data");
		list.pushBack(100);
		Test.testresult(list.back(), 100, "test pushback");
		list.popBack();
		Test.testresult(list.back(), 0, "test popback");
		list.pushFront(100);
		Test.testresult(list.front(), 100, "test pushfront");
		list.popFront();
		Test.testresult(list.front(), 0, "test popfront");
		list.erase(list.begin());
		Test.testresult(list.Size(), 2, "test erase");
		KT::List<int> vector2{ 5,5,5 };
		list.assign({ 1,1,1 });
		Test.testresult(list[0], 1, "test Assign initializelist");
		list.assign(5, 12);
		Test.testresult(list[4], 12, "test Assign size");
		list.assign(vector2.begin(), vector2.end());
		Test.testresult(list[0], 5, "test Assign Iterator");
	}
	{
		Test_Units Test("const Test_List_Constructor");
		const KT::List<int> DefaultConstructor;
		Test.testresult(DefaultConstructor.Size(), 0, "default size value");
		const KT::List<int>InitialiszeListConstructor{ 1,2,3 };
		Test.testresult(InitialiszeListConstructor[2], 3, "Test value");
		const KT::List<int>CopyConstructor = InitialiszeListConstructor;
		Test.testresult(CopyConstructor[2], InitialiszeListConstructor[2], "test_Copy value");
	}
	{
		Test_Units Test("const Test_List_Operator");
		const KT::List<int> list{ 1,2,3 };
		const KT::List<int> listcopy{ 5,5,5 };
		Test.testresult(list[2], 3, "Test_Operator[]");
		Test.testresult(list.at(0), 1, "Test_at()");
	}
	{
		Test_Units Test("const test_List_Iterator");
		const KT::List<int> IteratorTest{ 5, 1, 3 };
		Test.testresult(*IteratorTest.begin(), 5, "Test_Iterator_begin");
		Test.testresult(*IteratorTest.begin(), *(IteratorTest.rend() - 1), "test_Iterator and reverse Iterator");
		KT::List<int>::const_reverse_iterator ri = IteratorTest.rbegin();
		++ri;
		Test.testresult(*ri, IteratorTest[1], "test_++Operator");
		KT::List<int>::const_iterator ni = IteratorTest.end();
		--ni;
		Test.testresult(*ni, IteratorTest[2], "test_--Operator");
	}
	{
		Test_Units Test("const Test_List_function");
		const KT::List<int> list{ 0,0,0 };
		Test.testresult(list.front(), list[0], "test_front");
		Test.testresult(list.back(), list[2], "test_back");
		Test.testresult(list.Size(), 3, "test_size");
		Test.testresult(*list.begin(), 0, "test data");
	}
	{
		Test_Units Test("Algorithme on List");
		KT::List<int> list{ 0,0,0 };
		KT::Math::Fill(list.begin(), list.end(), 5);
		Test.testresult(list[0], 5, "test KT::Fill");
		std::fill(list.begin(), list.end(), 10);
		Test.testresult(list[0], 10, "test std::fill");
		KT::List<int> arraycopy{0,0,0};
		KT::Math::Copy(list.begin(), list.end(), arraycopy.begin());
		Test.testresult(arraycopy[0], 10, "test KT::copy");
		list = { 0,0,0 };
		std::copy(list.begin(), list.end(), arraycopy.begin());
		Test.testresult(arraycopy[0], 0, "test std::copy");
	}
	{
		Test_Units Test("Sort on List");
		KT::List<int> list{ 5,4,3,2,1 };
		KT::Algorithm::Sort<KT::List<int>, KT::Algorithm::BubbleSort>(list);
		Test.testresult(list[0], 1, "test bubblesort");
		list = { 1,2,3,4,5 };
		KT::Algorithm::Sort<KT::List<int>, KT::Algorithm::FusionSort>(list);
		Test.testresult(list[0], 1, "test fusionsort");
		list = { 1,2,3,4,5 };
		KT::Algorithm::Sort<KT::List<int>, KT::Algorithm::InsertionSort>(list);
		Test.testresult(list[0], 1, "test insertionsort");
	}
	{
		Test_Units Test("Test_IntrusiveList_Constructor");
		KT::IntrusiveList<int> DefaultConstructor;
		Test.testresult(DefaultConstructor.Size(), 0, "default size value");
		KT::IntrusiveList<int>InitialiszeListConstructor{ KT::Node<int>(1),KT::Node<int>(2),KT::Node<int>(3) };
		Test.testresult(InitialiszeListConstructor[2], 3, "Test value");
		KT::IntrusiveList<int>CopyConstructor = InitialiszeListConstructor;
		Test.testresult(CopyConstructor[2], InitialiszeListConstructor[2], "test_Copy value");
	}
	{
		Test_Units Test("Test_IntrusiveList_Operator");
		KT::IntrusiveList<int>list{ KT::Node<int>(1),KT::Node<int>(2),KT::Node<int>(3) };
		KT::IntrusiveList<int> listcopy{ KT::Node<int>(5),KT::Node<int>(5),KT::Node<int>(5) };
		Test.testresult(list[2], 3, "Test_Operator[]");
		Test.testresult(list.at(0), 1, "Test_at()");
		list = listcopy;
		Test.testresult(list[0], listcopy[0], "test_Operator =");
		list = { KT::Node<int>(1),KT::Node<int>(2),KT::Node<int>(3) };
		listcopy.swap(list);
		Test.testresult(listcopy[0], 1, "test swap");
		listcopy[0].data = 100;
		Test.testresult(listcopy[0], 100, "test assignation");
	}
	{
		Test_Units Test("test_IntrusiveList_Iterator");
		KT::IntrusiveList<int> IteratorTest{ KT::Node<int>(5),KT::Node<int>(1),KT::Node<int>(3) };
		Test.testresult((*IteratorTest.begin()).data, 5, "Test_Iterator_begin");
		auto it = IteratorTest.rend();
		Test.testresult((*IteratorTest.begin()).data, (*(--it)).data, "test_Iterator and reverse Iterator");
		KT::IntrusiveList<int>::reverse_iterator ri = IteratorTest.rbegin();
		++ri;
		Test.testresult((*ri).data, IteratorTest[1].data, "test_++Operator");
		KT::IntrusiveList<int>::iterator ni = IteratorTest.end();
		--ni;
		Test.testresult((*ni).data, IteratorTest[2].data, "test_--Operator");
	}
	{
		Test_Units Test("Test_IntrusiveList_function");
		KT::IntrusiveList<int> list{ KT::Node<int>(0),KT::Node<int>(0),KT::Node<int>(0) };
		Test.testresult(list.front().data, list[0].data, "test_front");
		Test.testresult(list.back().data, list[2].data, "test_back");
		Test.testresult(list.Size(), 3, "test_size");
		Test.testresult((*list.begin()).data, 0, "test data");
		list.pushBack(100);
		Test.testresult(list.back().data, 100, "test pushback");
		list.popBack();
		Test.testresult(list.back().data, 0, "test popback");
		list.pushFront(100);
		Test.testresult(list.front().data, 100, "test pushfront");
		list.popFront();
		Test.testresult(list.front().data, 0, "test popfront");
		list.erase(list.begin());
		Test.testresult(list.Size(), 2, "test erase");
		KT::IntrusiveList<int> vector2{ 5,5,5 };
		list.assign({ KT::Node<int>(1),KT::Node<int>(1),KT::Node<int>(1) });
		Test.testresult(list[0].data, 1, "test Assign initializelist");
		list.assign(5, 12);
		Test.testresult(list[4].data, 12, "test Assign size");
		list.assign(vector2.begin(), vector2.end());
		Test.testresult(list[0].data, 5, "test Assign Iterator");
	}
	{
		Test_Units Test("const Test_IntrusiveList_Constructor");
		const KT::IntrusiveList<int> DefaultConstructor;
		Test.testresult(DefaultConstructor.Size(), 0, "default size value");
		const KT::IntrusiveList<int>InitialiszeListConstructor{ KT::Node<int>(1),KT::Node<int>(2),KT::Node<int>(3) };
		Test.testresult(InitialiszeListConstructor[2], 3, "Test value");
		const KT::IntrusiveList<int>CopyConstructor = InitialiszeListConstructor;
		Test.testresult(CopyConstructor[2], InitialiszeListConstructor[2], "test_Copy value");
	}
	{
		Test_Units Test("const Test_IntrusiveList_Operator");
		const KT::IntrusiveList<int>list{ KT::Node<int>(1),KT::Node<int>(2),KT::Node<int>(3) };
		const KT::IntrusiveList<int> listcopy{ KT::Node<int>(5),KT::Node<int>(5),KT::Node<int>(5) };
		Test.testresult(list[2], 3, "Test_Operator[]");
		Test.testresult(list.at(0), 1, "Test_at()");
	}
	{
		Test_Units Test("const test_IntrusiveList_Iterator");
		const KT::IntrusiveList<int> IteratorTest{ KT::Node<int>(5),KT::Node<int>(1),KT::Node<int>(3) };
		Test.testresult((*IteratorTest.begin()).data, 5, "Test_Iterator_begin");
		auto it = IteratorTest.rend();
		Test.testresult((*IteratorTest.begin()).data, (*(--it)).data, "test_Iterator and reverse Iterator");
		KT::IntrusiveList<int>::const_reverse_iterator ri = IteratorTest.rbegin();
		++ri;
		Test.testresult((*ri).data, IteratorTest[1].data, "test_++Operator");
		KT::IntrusiveList<int>::const_iterator ni = IteratorTest.end();
		--ni;
		Test.testresult((*ni).data, IteratorTest[2].data, "test_--Operator");
	}
	{
		Test_Units Test("const Test_IntrusiveList_function");
		const KT::IntrusiveList<int> list{ KT::Node<int>(0),KT::Node<int>(0),KT::Node<int>(0) };
		Test.testresult(list.front().data, list[0].data, "test_front");
		Test.testresult(list.back().data, list[2].data, "test_back");
		Test.testresult(list.Size(), 3, "test_size");
		Test.testresult((*list.begin()).data, 0, "test data");
	}
	{
		Test_Units Test("Algorithme on IntrusiveList");
		KT::IntrusiveList<int> list{ KT::Node<int>(0),KT::Node<int>(0),KT::Node<int>(0) };
		KT::Math::Fill(list.begin(), list.end(), KT::Node<int>(5));
		Test.testresult(list[0].data, 5, "test KT::Fill");
		std::fill(list.begin(), list.end(), KT::Node<int>(10));
		Test.testresult(list[0], 10, "test std::fill");
		KT::IntrusiveList<int> arraycopy{ KT::Node<int>(0),KT::Node<int>(0),KT::Node<int>(0) };
		KT::Math::Copy(list.begin(), list.end(), arraycopy.begin());
		Test.testresult(arraycopy[0].data, 10, "test KT::copy");
		list = { KT::Node<int>(0),KT::Node<int>(0),KT::Node<int>(0) };
		std::copy(list.begin(), list.end(), arraycopy.begin());
		Test.testresult(arraycopy[0].data, 0, "test std::copy");
	}
	{
		Test_Units Test("Sort on IntrusiveList");
		KT::IntrusiveList<int> list{ KT::Node<int>(5),KT::Node<int>(4),KT::Node<int>(3), KT::Node<int>(2),KT::Node<int>(1) };
		KT::Algorithm::Sort<KT::IntrusiveList<int>, KT::Algorithm::BubbleSort>(list);
		Test.testresult(list[0].data, 1, "test bubblesort");
		list = { KT::Node<int>(5),KT::Node<int>(4),KT::Node<int>(3), KT::Node<int>(2),KT::Node<int>(1) };
		KT::Algorithm::Sort<KT::IntrusiveList<int>, KT::Algorithm::FusionSort>(list);
		Test.testresult(list[0].data, 1, "test fusionsort");
		list = { KT::Node<int>(5),KT::Node<int>(4),KT::Node<int>(3), KT::Node<int>(2),KT::Node<int>(1) };
		KT::Algorithm::Sort<KT::IntrusiveList<int>, KT::Algorithm::InsertionSort>(list);
		Test.testresult(list[0].data, 1, "test insertionsort");
	}
	{
		Test_Units Test("Test_VectorND_Constructor");
		KT::Array<int, 3> DefaultConstructor;
		Test.testresult(DefaultConstructor[0], 0, "Test_Default value");
		KT::Array<int, 3>InitialiszeListConstructor{ 1,2,3 };
		Test.testresult(InitialiszeListConstructor[0], 1, "Test_First value");
		KT::Array<int, 3>CopyConstructor = InitialiszeListConstructor;
		Test.testresult(CopyConstructor[2], InitialiszeListConstructor[2], "test_Copy value");
	}
	{
		Test_Units Test("Test_VectorND_Operator");
		KT::VectorND<int, 3> vectornd{ 1,2,3 };
		KT::VectorND<int, 3> VectorNdcopy{ 5,5,5 };
		Test.testresult(vectornd[2], 3, "Test_Operator[]");
		Test.testresult(vectornd.at(0), 1, "Test_at()");
		vectornd = VectorNdcopy;
		Test.testresult(vectornd[0], VectorNdcopy[0], "test_Operator =");
		vectornd = { 1,2,3 };
		VectorNdcopy[0] = 100;
		Test.testresult(VectorNdcopy[0], 100, "test assignation");
		vectornd = vectornd + VectorNdcopy;
		Test.testresult(vectornd[0], 101, "test Addition");
		vectornd = vectornd * 2;
		Test.testresult(vectornd[0], 202, "test Multiplication");
	}
	{
		Test_Units Test("test_VectorND_Iterator");
		KT::VectorND<int, 3> IteratorTest{ 5, 1, 3 };
		Test.testresult(*IteratorTest.begin(), 5, "Test_Iterator_begin");
		Test.testresult(*IteratorTest.begin(), *(IteratorTest.rend() - 1), "test_Iterator and reverse Iterator");
		KT::VectorND<int, 3>::reverse_iterator ri = IteratorTest.rbegin();
		++ri;
		Test.testresult(*ri, IteratorTest[1], "test_++Operator");
		KT::VectorND<int, 3>::iterator ni = IteratorTest.end();
		--ni;
		Test.testresult(*ni, IteratorTest[2], "test_--Operator");
	}
	{
		Test_Units Test("Test_VectorND_function");
		KT::VectorND<int, 3> vectornd;
		Test.testresult(vectornd.Size(), 3, "test_size");
		Test.testresult(*vectornd.data(), 0, "test data");
	}
	{
		Test_Units Test("Test_VectorND_Algorithm");
		KT::VectorND<float, 3> vector1{ 1,2,3 };
		KT::VectorND<float, 3>vector2{ 4,5,6 };
		auto VectorProduct = KT::Algorithm::VectorProduct(vector1, vector2);
		Test.testresult(VectorProduct[0], -3, "test vectorProduct");
		vector1 = { 3,4,12 };
		auto norme = KT::Algorithm::Norme(vector1);
		Test.testresult(norme, 13, "test Norme");
		vector1 = { 6,8,0 };
		auto normalisation = KT::Algorithm::VectorNormalization(vector1);
		Test.testresult(normalisation[0], 0.6f, "test Normalisation");
	}








	{
		Test_Units Test("Test_Matrix_Constructor");
		KT::Matrix<int,3,3> DefaultConstructor;
		Test.testresult(DefaultConstructor[0], 0, "Test_Default value");
		KT::Matrix<int, 3, 3> InitialiszeListConstructor{ 1,2,3,4,5,6,7,8,9 };
		Test.testresult(InitialiszeListConstructor[0], 1, "Test_First value");
		KT::Matrix<int, 3, 3>CopyConstructor = InitialiszeListConstructor;
		Test.testresult(CopyConstructor[2], InitialiszeListConstructor[2], "test_Copy value");
	}
	{
		Test_Units Test("Test_Matrix_Operator");
		KT::Matrix<int, 3, 3> matrix{ 1,2,3,4,5,6,7,8,9 };
		KT::Matrix<int, 3, 3> matrixcopy{ 5,5,5,5,5,5,5,5,5 };
		Test.testresult(matrix[2], 3, "Test_Operator[]");
		Test.testresult(matrix.at(0), 1, "Test_at()");
		matrix = matrixcopy;
		Test.testresult(matrix[0], matrixcopy[0], "test_Operator =");
		matrix = { 1,2,3,4,5,6,7,8,9 };
		matrixcopy[0] = 100;
		Test.testresult(matrixcopy[0], 100, "test assignation");
		matrix = matrix + matrixcopy;
		Test.testresult(matrix[0], 101, "test Addition");
		matrix = matrix * 2;
		Test.testresult(matrix[0], 202, "test Multiplication");
	}
	{
		Test_Units Test("test_Matrix_Iterator");
		KT::Matrix<int, 3, 3>  IteratorTest{ 5, 1, 3 ,4,5,6,7,8,9};
		Test.testresult(*IteratorTest.begin(), 5, "Test_Iterator_begin");
		Test.testresult(*IteratorTest.begin(), *(IteratorTest.rend() - 1), "test_Iterator and reverse Iterator");
		KT::Matrix<int, 3, 3> ::reverse_iterator ri = IteratorTest.rbegin();
		++ri;
		Test.testresult(*ri, IteratorTest[7], "test_++Operator");
		KT::Matrix<int, 3, 3> ::iterator ni = IteratorTest.end();
		--ni;
		Test.testresult(*ni, IteratorTest[8], "test_--Operator");
	}
	{
		Test_Units Test("Test_Matrix_function");
		KT::Matrix<int, 3, 3>  matrix{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		Test.testresult(matrix.Size(), 9, "test_size");
		Test.testresult(*matrix.data(), 1, "test data");
	}
	{
		Test_Units Test("Test_Matrix_Algorithm");
		KT::Matrix<int, 3, 3> matrix1{ 1,2,3,4,5,6,7,8,9 };
		KT::Matrix<int, 3, 2> matrix2{ 5,5,5,5,5,5 };
		auto matrixproduct = KT::Algorithm::MatrixProduct(matrix1, matrix2);
		Test.testresult(matrixproduct[0], 30, "test MatrixProduct");
		KT::VectorND<int, 3> vectorNd{ 5,5,5 };
		auto vectocmatrix = KT::Algorithm::MatrixProduct(matrix1, vectorNd);
		Test.testresult(vectocmatrix[0], 30, "test Matrix vector product");
	}
	return 0;
}
