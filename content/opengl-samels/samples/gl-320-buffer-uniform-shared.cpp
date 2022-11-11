#include "test.hpp"

namespace
{
	char const* VERT_SHADER_SOURCE("gl-320/buffer-uniform-shared.vert");
	char const* FRAG_SHADER_SOURCE("gl-320/buffer-uniform-shared.frag");

	GLsizei const VertexCount(4);
	GLsizeiptr const PositionSize = VertexCount * sizeof(glm::vec2);
	glm::vec2 const PositionData[VertexCount] =
	{
		glm::vec2(-1.0f,-1.0f),
		glm::vec2( 1.0f,-1.0f),
		glm::vec2( 1.0f, 1.0f),
		glm::vec2(-1.0f, 1.0f)
	};

	GLsizei const ElementCount(6);
	GLsizeiptr const ElementSize = ElementCount * sizeof(GLushort);
	GLushort const ElementData[ElementCount] =
	{
		0, 1, 2, 
		2, 3, 0
	};

	namespace buffer
	{
		enum type
		{
			VERTEX,
			ELEMENT,
			UNIFORM,
			MAX
		};
	}//namespace buffer

	namespace shader
	{
		enum type
		{
			VERT,
			FRAG,
			MAX
		};
	}//namespace shader
}//namespace

class sample : public framework
{
public:
	sample(int argc, char* argv[]) :
		framework(argc, argv, "gl-320-buffer-uniform-shared", framework::CORE, 3, 2),
		VertexArrayName(0),
		ProgramName(0),
		UniformTransform(0),
		UniformMaterial(0),
		UniformBlockSizeTransform(0),
		UniformBlockSizeMaterial(0)
	{}

private:
	std::array<GLuint, shader::MAX> ShaderName;
	std::array<GLuint, buffer::MAX> BufferName;
	GLuint ProgramName;
	GLuint VertexArrayName;
	GLint UniformTransform;
	GLint UniformMaterial;
	GLint UniformBlockSizeTransform;
	GLint UniformBlockSizeMaterial;

	bool initProgram()
	{
		bool Validated = true;

		if(Validated)
		{
			compiler Compiler;
			ShaderName[shader::VERT] = Compiler.create(GL_VERTEX_SHADER, getDataDirectory() + VERT_SHADER_SOURCE, "--version 150 --profile core");
			ShaderName[shader::FRAG] = Compiler.create(GL_FRAGMENT_SHADER, getDataDirectory() + FRAG_SHADER_SOURCE, "--version 150 --profile core");

			ProgramName = glCreateProgram();
			glAttachShader(ProgramName, ShaderName[shader::VERT]);
			glAttachShader(ProgramName, ShaderName[shader::FRAG]);

			glBindAttribLocation(ProgramName, semantic::attr::POSITION, "Position");
			glBindFragDataLocation(ProgramName, semantic::frag::COLOR, "Color");
			glLinkProgram(ProgramName);

			Validated = Validated && Compiler.check();
			Validated = Validated && Compiler.check_program(ProgramName);
		}

		if(Validated)
		{
			UniformMaterial = glGetUniformBlockIndex(ProgramName, "material");
			UniformTransform = glGetUniformBlockIndex(ProgramName, "transform");
		}

		return Validated && this->checkError("initProgram");
	}

	bool initVertexArray()
	{
		glGenVertexArrays(1, &VertexArrayName);
		glBindVertexArray(VertexArrayName);
			glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::VERTEX]);
			glVertexAttribPointer(semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, 0, 0);

			glEnableVertexAttribArray(semantic::attr::POSITION);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]);
		glBindVertexArray(0);

		return this->checkError("initVertexArray");
	}

	bool initBuffer()
	{
		glGenBuffers(buffer::MAX, &BufferName[0]);

		GLint UniformBufferOffset(0);
		glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &UniformBufferOffset);

		glGetActiveUniformBlockiv(
			ProgramName, 
			UniformTransform,
			GL_UNIFORM_BLOCK_DATA_SIZE,
			&UniformBlockSizeTransform);
		UniformBlockSizeTransform = ((UniformBlockSizeTransform / UniformBufferOffset) + 1) * UniformBufferOffset;

		glGetActiveUniformBlockiv(
			ProgramName, 
			UniformMaterial,
			GL_UNIFORM_BLOCK_DATA_SIZE,
			&UniformBlockSizeMaterial);
		UniformBlockSizeMaterial = ((UniformBlockSizeMaterial / UniformBufferOffset) + 1) * UniformBufferOffset;

		glBindBuffer(GL_UNIFORM_BUFFER, BufferName[buffer::UNIFORM]);
		glBufferData(GL_UNIFORM_BUFFER, UniformBlockSizeTransform + UniformBlockSizeMaterial, NULL, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, ElementSize, ElementData, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::VERTEX]);
		glBufferData(GL_ARRAY_BUFFER, PositionSize, PositionData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		return this->checkError("initBuffer");
	}

	bool begin()
	{
		bool Validated = true;

		if(Validated)
			Validated = initProgram();
		if(Validated)
			Validated = initBuffer();
		if(Validated)
			Validated = initVertexArray();

		return Validated && this->checkError("begin");
	}

	bool end()
	{
		glDeleteVertexArrays(1, &VertexArrayName);
		glDeleteBuffers(buffer::MAX, &BufferName[0]);
		glDeleteProgram(ProgramName);

		return true;
	}

	bool render()
	{
		glm::vec2 WindowSize(this->getWindowSize());

		{
			// Compute the MVP (Model View Projection matrix)
			glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, WindowSize.x / WindowSize.y, 0.1f, 100.0f);
			glm::mat4 Model = glm::mat4(1.0f);
			glm::mat4 MVP = Projection * this->view() * Model;

			glm::vec4 Diffuse(1.0f, 0.5f, 0.0f, 1.0f);

			glBindBuffer(GL_UNIFORM_BUFFER, BufferName[buffer::UNIFORM]);
			glm::uint8* Pointer = (glm::uint8*)glMapBufferRange(
				GL_UNIFORM_BUFFER, 0,	UniformBlockSizeTransform + sizeof(glm::vec4),
				GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

			*(glm::mat4*)(Pointer + 0) = MVP;
			*(glm::vec4*)(Pointer + UniformBlockSizeTransform) = Diffuse;

			// Make sure the uniform buffer is uploaded
			glUnmapBuffer(GL_UNIFORM_BUFFER);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}

		glViewport(0, 0, static_cast<GLsizei>(WindowSize.x), static_cast<GLsizei>(WindowSize.y));
		glClearBufferfv(GL_COLOR, 0, &glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)[0]);

		glUseProgram(ProgramName);
		glUniformBlockBinding(ProgramName, UniformTransform, semantic::uniform::TRANSFORM0);
		glUniformBlockBinding(ProgramName, UniformMaterial, semantic::uniform::MATERIAL);

		// Attach the buffer to UBO binding point semantic::uniform::TRANSFORM0
		glBindBufferRange(GL_UNIFORM_BUFFER, semantic::uniform::TRANSFORM0, BufferName[buffer::UNIFORM], 0, UniformBlockSizeTransform);
		// Attach the buffer to UBO binding point semantic::uniform::MATERIAL 
		glBindBufferRange(GL_UNIFORM_BUFFER, semantic::uniform::MATERIAL, BufferName[buffer::UNIFORM], UniformBlockSizeTransform, UniformBlockSizeMaterial);

		// Bind vertex array & draw 
		glBindVertexArray(VertexArrayName);
		glDrawElementsInstancedBaseVertex(GL_TRIANGLES, ElementCount, GL_UNSIGNED_SHORT, NULL, 1, 0);

		return true;
	}
};

int main(int argc, char* argv[])
{
	int Error = 0;

	sample Sample(argc, argv);
	Error += Sample();

	return Error;
}

