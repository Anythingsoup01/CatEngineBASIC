#pragma once

#include <glad/glad.h>
#include "Buffers/VertexArray.h"
#include "Buffers/IndexBuffer.h"
#include "Shader/Shader.h"

class Renderer
{
public:
	void Clear();
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};

