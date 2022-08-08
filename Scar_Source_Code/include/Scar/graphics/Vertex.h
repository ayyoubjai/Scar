#pragma once
#include "core/core.h"
#include <vector>
#include <type_traits>
#include <cstdint>
namespace Scar::graphics {
	class SCAR_API Vertex {
	protected:
		unsigned int ID;
		void* m_buffer;
		unsigned int m_size,m_stride;
		bool m_uploaded;
		std::vector<unsigned int> m_layout;
		uint32_t m_glType;
		enum class Types :uint32_t {
			GLTypeByte=0x1400,
			GLTypeUByte=0x1401, 
			GLTypeShort=0x1402,
			GLTypeUShort=0x1403,
			GLTypeInt=0x1404,
			GLTypeUInt=0x1405,
			GLTypeFloat=0x1406,
			GLTypeDouble=0x140A
		};
	public:
		Vertex();
		~Vertex();
		inline unsigned int GetID() const { return ID; }
		inline unsigned int GetSize() const { return m_size; }
		inline unsigned int GetStride() const { return m_stride; }
		inline uint32_t GetGLType() const { return m_glType; }
		inline bool IsUploaded() const { return m_uploaded; }
		void Bind();
		void UnBind();
		virtual void Upload(bool dynamic = false);
		virtual unsigned int GetVertexCount() const = 0;
		virtual unsigned int GetTypeSize() const = 0;
		virtual const std::vector<unsigned int>& GetLayout() const =0;
	};
	template<class T>
	class SCAR_API VertexBuffer:public Vertex {
		static_assert(	std::is_same<T, char>() ||
						std::is_same<T, unsigned char>() ||
						std::is_same<T, short>() ||
						std::is_same<T, unsigned short>() ||
						std::is_same<T,int>() ||
						std::is_same<T,unsigned int>() ||
						std::is_same<T,float>() ||
						std::is_same<T,double>(),
						"Unsuported type for Vertex Buffer");
		
		std::vector<T> m_data;
		unsigned int m_vertexCount;
		
	public:
		VertexBuffer()
			:m_vertexCount(0) 
		{
			if constexpr (std::is_same<T, char>()) { m_glType = /*(uint32_t)*/ static_cast<uint32_t>(Vertex::Types::GLTypeByte); }
			if constexpr (std::is_same<T, unsigned char>()) { m_glType = static_cast<uint32_t>(Vertex::Types::GLTypeUByte); }
			if constexpr (std::is_same<T, short>()) { m_glType = static_cast<uint32_t>(Vertex::Types::GLTypeShort); }
			if constexpr (std::is_same<T, unsigned short>()) { m_glType = static_cast<uint32_t>(Vertex::Types::GLTypeUShort); }
			if constexpr (std::is_same<T, int>()) { m_glType = static_cast<uint32_t>(Vertex::Types::GLTypeInt); }
			if constexpr (std::is_same<T, unsigned int>()) { m_glType = static_cast<uint32_t>(Vertex::Types::GLTypeUInt); }
			if constexpr (std::is_same<T, float>()) { m_glType = static_cast<uint32_t>(Vertex::Types::GLTypeFloat); }
			if constexpr (std::is_same<T, double>()) { m_glType = static_cast<uint32_t>(Vertex::Types::GLTypeDouble); }
		}
		
		using Type = T;
		inline unsigned int GetVertexCount() const { return m_vertexCount; }
		inline const std::vector<unsigned int>& GetLayout() const { return m_layout; }

		void SetLayout(const std::vector<unsigned int>& layout);

		
		void PushVertex(const std::vector<T>&);

		void Upload(bool dynamic = false) override;
		unsigned int GetTypeSize() const override;
	};

	class SCAR_API VertexArray {
		unsigned int m_elementCount, m_attributeCount;
		bool m_isUploaded;
		unsigned int VEO, ID;
		std::vector<Vertex*> m_VBOs;
	public:
		VertexArray();
		~VertexArray();

		inline unsigned int GetElementCount() const { return m_elementCount; }
		inline bool IsUploaded() const { return m_isUploaded; }

		void PushBuffer(Vertex* vbo);
		void SetElements(const std::vector<unsigned int>& elements);

		void Upload();

		void Bind();
		void UnBind();
	};
	


}