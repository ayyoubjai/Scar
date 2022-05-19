#include "graphics/Mesh.h"
#include "glad/glad.h"

namespace Scar::graphics {
	Mesh::Mesh(float* VertexBuffer, unsigned int VertexCount, unsigned int VertexDim, unsigned int* ElementBuffer, unsigned int ElementCount):
		m_vertexcount(VertexCount),m_elementcount(ElementCount),m_elementbuffer(ElementBuffer) {
		//create the VAO, VBO and EBO
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		//bind the VAO, VBO and EBO
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

		glBufferData(GL_ARRAY_BUFFER, VertexCount * VertexDim * sizeof(float) , VertexBuffer, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, ElementCount * sizeof(unsigned int), ElementBuffer, GL_STATIC_DRAW);
		//VBO layout
		//TO DO:provide functionsto automate the process

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,VertexDim * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VertexDim * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, VertexDim * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);
		//unbind the VBO
		glBindBuffer(GL_VERTEX_ARRAY, 0);
		//unbind the VAO
		glBindVertexArray(0);
		//unbind the EBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	Mesh::Mesh(float* VertexBuffer, unsigned int VertexCount, unsigned int VertexDim):
		m_vertexcount(VertexCount),m_elementbuffer(0),m_elementcount(0)
	{
		//create the VAO, VBO and EBO
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		//bind the VAO, VBO and EBO
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, VertexCount * VertexDim * sizeof(float), VertexBuffer, GL_STATIC_DRAW);
		//VBO layout
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VertexDim * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VertexDim * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
		//unbind the VBO
		glBindBuffer(GL_VERTEX_ARRAY, 0);
		//unbind the VAO
		glBindVertexArray(0);
		//unbind the EBO
	}
	void Mesh::Bind()
	{
		glBindVertexArray(VAO);
	}

	void Mesh::UnBind()
	{
		glBindVertexArray(0);
	}

	Mesh::~Mesh() {
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
		glDeleteVertexArrays(1, &VAO);
	}
}

