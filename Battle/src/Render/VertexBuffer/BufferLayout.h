#pragma once
#include "Utils/Utils.h"
#include <cstdint>
#include <iostream>
#include <cassert>
#include <vector>
namespace JF
{
	

	struct BufferElement
	{
	public:
		BufferElement(const ShaderDataType& type, bool isNormalized = false)
		{
			dataType = type;
			dataSize = Utils::get_data_size(dataType);
			dataCount = Utils::get_data_count(dataType);
			this->isNormalized = isNormalized;
		}

		ShaderDataType dataType;
		uint32_t offset = 0;
		uint32_t dataSize;
		uint32_t dataCount;
		bool isNormalized;
	};

	class BufferLayout
	{
	public:
		BufferLayout(){}
		BufferLayout(const std::initializer_list<BufferElement>& elements) :m_Elements(elements)
		{
			calculate_offset_stride();
		}

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }

		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

		inline uint32_t get_stride() const { return m_Stride; }

	private:
		void calculate_offset_stride()
		{
			uint32_t offset = 0;
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.offset = offset;
				offset += element.dataSize;
				m_Stride += element.dataSize;
			}
		}
	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};
}