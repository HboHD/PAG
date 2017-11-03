#include "Mesh.h"

Mesh::Mesh(unsigned int *VBO, unsigned int *VAO, unsigned int *EBO)
{
	//VBO = VBO;
	//VAO = VAO;
	//EBO = EBO;

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// Pozycje          // Kolory           // Wsp�rz�dne tekstury
		-0.5f, -0.5f, 0.0f,	1.0f, 0.0f, 0.0f,   0.0f, 0.0f,   // Lewy
		0.5f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // Prawy
		0.0f, 0.5f, 0.0f,	0.0f, 0.0f, 1.0f,   0.5f, 1.0f   // G�ra
	};

	glGenVertexArrays(1, VAO);
	glGenBuffers(1, VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(*VAO);

	glBindBuffer(GL_ARRAY_BUFFER, *VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// texture coord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
}


Mesh::~Mesh()
{
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	//glDeleteVertexArrays(1, &VAO);
	//glDeleteBuffers(1, &VBO);
}