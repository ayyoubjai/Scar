#pragma once
#include "core/core.h"

namespace Scar::graphics {
	class SCAR_API Mesh {
	private:
		unsigned int VAO;
		unsigned int VBO;
		unsigned int EBO;
		unsigned int m_vertexcount;
		unsigned int m_elementcount;
		unsigned int* m_elementbuffer;
	public:
		Mesh(float* VertexBuffer,unsigned int VertexCount ,unsigned int VertexDim, unsigned int* ElementBuffer,unsigned int ElementCount);
		Mesh(float* VertexBuffer, unsigned int VertexCount, unsigned int VertexDim);
		Mesh()
			:VAO(0), VBO(0), EBO(0), m_vertexcount(0),m_elementcount(0),m_elementbuffer(nullptr)
		{
		
		}
		~Mesh();
		void Bind();
		void UnBind();
		inline unsigned int GetVertexCount() {
			return m_vertexcount;
		}
		inline unsigned int GetElementCount() {
			return m_elementcount;
		}
		inline unsigned int* GetElementBuffer() {
			return m_elementbuffer;
		}
	};
}