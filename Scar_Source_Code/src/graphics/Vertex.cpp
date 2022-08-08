#include "graphics/Vertex.h"
#include "core/Log.h"
#include "glad/glad.h"
namespace Scar::graphics {

	Vertex::Vertex()
		:m_uploaded(false)
	{
		glGenBuffers(1, &ID);
	}

	Vertex::~Vertex() {
		glDeleteBuffers(1, &ID);
	}

	void Vertex::Bind() {
		glBindBuffer(GL_ARRAY_BUFFER, ID);
	}

	void Vertex::UnBind() {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	template<class T>
	void VertexBuffer<T>::SetLayout(const std::vector<unsigned int>& layout)
	{
		m_layout = layout;
		
	}

	void Vertex::Upload(bool dynamic)
	{
		Bind();
		glBufferData(GL_ARRAY_BUFFER, m_size, m_buffer, dynamic? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
		UnBind();
		m_uploaded = true;
	}

	template<class T>
	void VertexBuffer<T>::PushVertex(const std::vector<T>& vt) {
		m_vertexCount++;
		m_data.insert(m_data.end(), vt.begin(), vt.end());
	}

	template<class T>
	unsigned int VertexBuffer<T>::GetTypeSize() const { return sizeof(T); }

	template<class T>
	void VertexBuffer<T>::Upload(bool dynamic) {
		m_buffer = &m_data[0];
		m_size = m_data.size() * sizeof(T);
		m_stride = 0;
		
		for (auto iter = m_layout.begin(); iter != m_layout.end(); iter++) {
			m_stride += (*iter) * sizeof(T);
		}
		Vertex::Upload(dynamic);
	}
	
	
	VertexArray::VertexArray()
		:ID(0),VEO(0),m_attributeCount(0),m_elementCount(0),m_isUploaded(false)
	{
		glGenVertexArrays(1, &ID);
	}

	VertexArray::~VertexArray()
	{
		for (auto& var : m_VBOs) {
			auto vboId = var->GetID();
			glDeleteBuffers(1, &vboId);
			delete var;
		}
		glDeleteVertexArrays(1, &ID);
		m_VBOs.clear();
	}

	void VertexArray::PushBuffer(Vertex* vbo)
	{
		if (m_VBOs.size() > 0) {
			SCAR_ASSERT(m_VBOs[0]->GetVertexCount() == vbo->GetVertexCount(), "Attempting to push to different VBOs vertex count wise");
		}
		SCAR_ASSERT(vbo->GetLayout().size() > 0, "Vertex Buffer has no layout defined");
		m_VBOs.push_back(vbo);
		//m_vertexCount = m_VBOs[0]->GetVertexCount(); 
	}

	void VertexArray::SetElements(const std::vector<unsigned int>& elements)
	{
		m_elementCount = elements.size();
		glBindVertexArray(ID);
		glGenBuffers(1, &VEO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VEO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_elementCount * sizeof(unsigned int), &elements[0],GL_STATIC_DRAW);
		glBindVertexArray(0);
	}

	void VertexArray::Upload()
	{
		unsigned int attribCount = 0;
		Bind();
		for (auto& vbo: m_VBOs) {
			unsigned int offset = 0;
			if (!vbo->IsUploaded()) {
				vbo->Upload();
			}
			vbo->Bind();
			for (auto& count : vbo->GetLayout()) {
				glVertexAttribPointer(attribCount,count,static_cast<GLenum>(vbo->GetGLType()), GL_FALSE, vbo->GetStride(), (void*)offset);
				glEnableVertexAttribArray(attribCount);
				offset += count * (vbo->GetTypeSize());
				attribCount++;
			}
			vbo->UnBind();
		}
		UnBind();
		m_isUploaded = true;
	}

	void VertexArray::Bind()
	{
		glBindVertexArray(ID);
	}

	void VertexArray::UnBind()
	{
		glBindVertexArray(0);
	}

	//suported vertex buffers

	template SCAR_API class VertexBuffer<float>;
	template SCAR_API class VertexBuffer<double>;
	template SCAR_API class VertexBuffer<int>;
	template SCAR_API class VertexBuffer<unsigned int>;
	template SCAR_API class VertexBuffer<char>;
	template SCAR_API class VertexBuffer<unsigned char>;
	template SCAR_API class VertexBuffer<short>;
	template SCAR_API class VertexBuffer<unsigned short>;
}