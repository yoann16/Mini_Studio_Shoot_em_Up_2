#pragma once
#include <iostream>
struct Test_Units
{
	Test_Units(const char* name) :m_name(name) { std::cout << "Test :"; Write_in_green(std::cout, m_name) << std::endl; std::cout << std::endl;}
	~Test_Units() { std::cout << std::endl; }
	template<typename type1 , typename type2>
	void testresult(type1 lhs, type2 rhs, const char* text)
	{
		std::cout << "Test :" << text << std::endl;
		std::cout << "Result : ";

		if (lhs == rhs)
		{
			Write_in_green(std::cout, "OK") << std::endl;
			return;
		}
		 Write_in_red(std::cout,"KO") << std:: endl;
		std::cout << "Value Needed : " << rhs << std::endl;	
		std::cout << "Value Get : " << lhs << std::endl;

	}
private:
	std::ostream& Write_in_red(std::ostream& os ,const char* text)
	{
		os << "\033[31m" << text <<"\033[0m";
		return os;
	}
	std::ostream& Write_in_green(std::ostream& os, const char* text)
	{
		os << "\033[32m" << text <<"\033[0m";
		return os;
	}
	const char* m_name;
};