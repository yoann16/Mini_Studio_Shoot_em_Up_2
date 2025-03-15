#pragma once
/*****************************************************************//**
 * @file   KT_Math_Algorithm.h
 * @brief  This file contains the Algorithm for KT::VectorND and KT::Matrix
 *
 * @author Kroktur
 * @date   February 2025
 *********************************************************************/
#include "KT_VectorND.h"
#include "KT_Matrix.h"
#include <exception>
#include <cmath>
 /**
  * @brief Namespace of my library
  */
namespace KT
{
	/**
	 * @brief Node for the IntrusiveList
	 * @tparam type
	 */
	namespace Algorithm
	{
		/**
		 * @brief Vector product 
		 * @tparam value_type
		 * @param KT::VecteurND<value_type, 3> lhs 
		 * @param KT::VecteurND<value_type, 3>  rhs 
		 * @return KT::VecteurND<value_type, 3> 
		 */
		template <typename type >
		KT::VectorND<type, 3>  VectorProduct(const KT::VectorND<type, 3>& lhs, const KT::VectorND<type, 3>& rhs)
		{
			KT::VectorND<type, 3> result;
			result[0] = lhs[1] * rhs[2] - lhs[2] * rhs[1];
			result[1] = lhs[2] * rhs[0] - lhs[0] * rhs[2];
			result[2] = lhs[0] * rhs[1] - lhs[1] * rhs[0];
			return result;
		}

		/**
		 * @brief Norme of a vector
		 * @tparam value_type 
		 * @tparam size_t
		 * @param KT::VecteurND  
		 * @return value_type 
		 */
		template<typename type, size_t size>
		type Norme(const KT::VectorND<type, size>& data)
		{
			type result = type{};
			for (auto it = data.begin(); it != data.end(); ++it)
			{
				result += (*it * *it);
			}
			return std::sqrt(result);
		};

		/**
		 * @brief return the Vector Normalization
		 * @tparam value_type 
		 * @tparam size_t 
		 * @param KT::VectorND 
		 * @return KT::VectorND
		 */
		template<typename type, size_t size>
		KT::VectorND<type, size> VectorNormalization(const KT::VectorND<type, size>& data)
		{
			KT::VectorND<type, size> result;
			type norme = Norme<type, size>(data);
			auto itresult = result.begin();
			for (auto it = data.begin(); it != data.end(); ++it)
			{
				*itresult = (*it / norme);
				++itresult;
			}
			return result;
		};

		/**
		 * @brief return Vector Scalare Product
		 * @tparam value_type 
		 * @tparam size_t 
		 * @param KT::VectorND 
		 * @param KT::VectorND 
		 * @return 
		 */
		template <typename type, size_t size>
		type VectorScalarProduct(const KT::VectorND<type, size>& lhs, const KT::VectorND<type, size>& rhs)
		{
			type result = type{};
			auto it2 = rhs.begin();
			for (auto it = lhs.begin(); it != lhs.end(); ++it)
			{
				result += (*it * *it2);
				++it2;
			}
			return result;
		}

		/**
		 * @brief return Matrix Product
		 * @tparam value_type 
		 * @tparam size_t 
		 * @tparam size_t 
		 * @tparam size_t 
		 * @tparam size_t 
		 * @param KT::Matrix
		 * @param KT::Matrix
		 * @return KT::Matrix
		 */
		template <typename type, size_t height, size_t width, size_t height_, size_t width_   >
		KT::Matrix<type, height, width_>  MatrixProduct(const KT::Matrix<type, height, width>& lhs, const KT::Matrix<type, height_, width_>& rhs)
		{
			if (width != height_)
				throw std::out_of_range("Product Imposible");
			KT::Matrix<type, height, width_> result;
			for (size_t row = 0; row < height; ++row)
			{
				for (size_t col = 0; col < width_; ++col)
				{
					result.getCell(row, col) = type{};
					for (size_t idx = 0; idx < width; ++idx)
					{
						result.getCell(row, col) += lhs.getCell(row, idx) * rhs.getCell(idx, col);
					}
				}
			}
			return result;
		}

		/**
		 * @brief matrix product betwen VectorND and Matrix
		 * @tparam value_type
		 * @tparam size_t
		 * @tparam size_t
		 * @param KT::Matrix
		 * @param KT::VectorND
		 * @return KT::VectorND
		 */
		template <typename type, size_t height, size_t width>
		KT::VectorND<type, height>  MatrixProduct(const KT::Matrix<type, height, width>& lhs, const KT::VectorND<type, width>& rhs)
		{
			KT::VectorND<type, height> result;
			for (size_t i = 0; i < result.Size(); ++i)
			{
				for (size_t col = 0; col < width; ++col)
				{
					result[i] += rhs[col] * lhs.getCell(i, col);
				}
			}
			return result;
		}
	}
}
