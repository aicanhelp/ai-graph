#include "test.hpp"

namespace
{
	char const* VERT_SHADER_SOURCE_TEXTURE("gl-320/fbo-srgb-blend.vert");
	char const* FRAG_SHADER_SOURCE_TEXTURE("gl-320/fbo-srgb-blend.frag");
	char const* VERT_SHADER_SOURCE_SPLASH("gl-320/fbo-srgb-blit-blend.vert");
	char const* FRAG_SHADER_SOURCE_SPLASH("gl-320/fbo-srgb-blit-blend.frag");
	char const* TEXTURE_DIFFUSE("kueken7_rgba8_srgb.dds");

	namespace buffer
	{
		enum type
		{
			TRANSFORM,
			MAX
		};
	}//namespace buffer

	namespace texture
	{
		enum type
		{
			DIFFUSE,
			COLORBUFFER,
			RENDERBUFFER,
			MAX
		};
	}//namespace texture
	
	namespace program
	{
		enum type
		{
			TEXTURE,
			SPLASH,
			MAX
		};
	}//namespace program

	namespace shader
	{
		enum type
		{
			VERT_TEXTURE,
			FRAG_TEXTURE,
			VERT_SPLASH,
			FRAG_SPLASH,
			MAX
		};
	}//namespace shader
}//namespace

class sample : public framework
{
public:
	sample(int argc, char* argv[]) :
		framework(argc, argv, "gl-320-fbo-srgb-blend", framework::CORE, 3, 2, HEURISTIC_MIPMAPS_ABSOLUTE_DIFFERENCE_MAX_CHANNEL_BIT),
		FramebufferName(0),
		FramebufferScale(2),
		UniformTransform(-1)
	{}

private:
	std::array<GLuint, program::MAX> ProgramName;
	std::array<GLuint, program::MAX> VertexArrayName;
	std::array<GLuint, buffer::MAX> BufferName;
	std::array<GLuint, texture::MAX> TextureName;
	std::array<GLint, program::MAX> UniformDiffuse;
	GLuint FramebufferName;
	glm::uint FramebufferScale;
	GLint UniformTransform;

	bool initProgram()
	{
		bool Validated(true);

		compiler Compiler;

		std::array<GLuint, shader::MAX> ShaderName;

		if(Validated)
		{
			ShaderName[shader::VERT_TEXTURE] = Compiler.create(GL_VERTEX_SHADER, getDataDirectory() + VERT_SHADER_SOURCE_TEXTURE, "--version 150 --profile core");
			ShaderName[shader::FRAG_TEXTURE] = Compiler.create(GL_FRAGMENT_SHADER, getDataDirectory() + FRAG_SHADER_SOURCE_TEXTURE, "--version 150 --profile core");

			ProgramName[program::TEXTURE] = glCreateProgram();
			glAttachShader(ProgramName[program::TEXTURE], ShaderName[shader::VERT_TEXTURE]);
			glAttachShader(ProgramName[program::TEXTURE], ShaderName[shader::FRAG_TEXTURE]);

			glBindAttribLocation(ProgramName[program::TEXTURE], semantic::attr::POSITION, "Position");
			glBindAttribLocation(ProgramName[program::TEXTURE], semantic::attr::TEXCOORD, "Texcoord");
			glBindFragDataLocation(ProgramName[program::TEXTURE], semantic::frag::COLOR, "Color");
			glLinkProgram(ProgramName[program::TEXTURE]);
		}

		if(Validated)
		{
			ShaderName[shader::VERT_SPLASH] = Compiler.create(GL_VERTEX_SHADER, getDataDirectory() + VERT_SHADER_SOURCE_SPLASH, "--version 150 --profile core");
			ShaderName[shader::FRAG_SPLASH] = Compiler.create(GL_FRAGMENT_SHADER, getDataDirectory() + FRAG_SHADER_SOURCE_SPLASH, "--version 150 --profile core");

			ProgramName[program::SPLASH] = glCreateProgram();
			glAttachShader(ProgramName[program::SPLASH], ShaderName[shader::VERT_SPLASH]);
			glAttachShader(ProgramName[program::SPLASH], ShaderName[shader::FRAG_SPLASH]);

			glBindFragDataLocation(ProgramName[program::SPLASH], semantic::frag::COLOR, "Color");
			glLinkProgram(ProgramName[program::SPLASH]);
		}
	
		if(Validated)
		{
			Validated = Validated && Compiler.check();
			Validated = Validated && Compiler.check_program(ProgramName[program::TEXTURE]);
			Validated = Validated && Compiler.check_program(ProgramName[program::SPLASH]);
		}

		if(Validated)
		{
			UniformTransform = glGetUniformBlockIndex(ProgramName[program::TEXTURE], "transform");
			UniformDiffuse[program::TEXTURE] = glGetUniformLocation(ProgramName[program::TEXTURE], "Diffuse");
			UniformDiffuse[program::SPLASH] = glGetUniformLocation(ProgramName[program::SPLASH], "Diffuse");

			glUseProgram(ProgramName[program::TEXTURE]);
			glUniform1i(UniformDiffuse[program::TEXTURE], 0);
			glUniformBlockBinding(ProgramName[program::TEXTURE], UniformTransform, semantic::uniform::TRANSFORM0);

			glUseProgram(ProgramName[program::SPLASH]);
			glUniform1i(UniformDiffuse[program::SPLASH], 0);
		}

		return Validated && this->checkError("initProgram");
	}

	bool initBuffer()
	{
		glGenBuffers(buffer::MAX, &BufferName[0]);

		GLint UniformBufferOffset(0);
		glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &UniformBufferOffset);
		GLint UniformBlockSize = glm::max(GLint(sizeof(glm::mat4)), UniformBufferOffset);

		glBindBuffer(GL_UNIFORM_BUFFER, BufferName[buffer::TRANSFORM]);
		glBufferData(GL_UNIFORM_BUFFER, UniformBlockSize * 2, nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		return true;
	}

	bool initTexture()
	{
		bool Validated(true);

		gli::gl GL(gli::gl::PROFILE_GL32);
		gli::texture2d Texture(gli::load_dds((getDataDirectory() + TEXTURE_DIFFUSE).c_str()));
		assert(!Texture.empty());

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glGenTextures(texture::MAX, &TextureName[0]);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureName[texture::DIFFUSE]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(Texture.levels() - 1));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		gli::gl::format const Format = GL.translate(Texture.format(), Texture.swizzles());
		for (gli::texture2d::size_type Level = 0; Level < Texture.levels(); ++Level)
		{
			glTexImage2D(GL_TEXTURE_2D, static_cast<GLint>(Level),
				Format.Internal,
				static_cast<GLsizei>(Texture[Level].extent().x), static_cast<GLsizei>(Texture[Level].extent().y),
				0,
				Format.External, Format.Type,
				Texture[Level].data());
		}
	
		glm::ivec2 WindowSize(this->getWindowSize() * this->FramebufferScale);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureName[texture::COLORBUFFER]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, GLint(0), GL_SRGB8_ALPHA8, GLsizei(WindowSize.x), GLsizei(WindowSize.y), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

		return Validated;
	}

	bool initVertexArray()
	{
		glGenVertexArrays(program::MAX, &VertexArrayName[0]);

		glBindVertexArray(VertexArrayName[program::TEXTURE]);
		glBindVertexArray(0);

		glBindVertexArray(VertexArrayName[program::SPLASH]);
		glBindVertexArray(0);

		return true;
	}

	bool initFramebuffer()
	{
		glGenFramebuffers(1, &FramebufferName);
		glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, TextureName[texture::COLORBUFFER], 0);

		if(!this->checkFramebuffer(FramebufferName))
			return false;

		GLint const EncodingLinear = GL_LINEAR;
		GLint const EncodingSRGB = GL_SRGB;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		GLint Encoding = 0;
		glGetFramebufferAttachmentParameteriv(GL_DRAW_FRAMEBUFFER, GL_BACK_LEFT, GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING, &Encoding);
		return true;
	}

	bool begin()
	{
		bool Validated(true);

		// Explicitly convert linear pixel color to sRGB color space, as FramebufferName is a sRGB FBO
		// Shader execution is done with linear color to get correct linear algebra working.
		glEnable(GL_FRAMEBUFFER_SRGB);
		glEnable(GL_PROGRAM_POINT_SIZE);

		if(Validated)
			Validated = initProgram();
		if(Validated)
			Validated = initBuffer();
		if(Validated)
			Validated = initVertexArray();
		if(Validated)
			Validated = initTexture();
		if(Validated)
			Validated = initFramebuffer();

		return Validated;
	}

	bool end()
	{
		glDeleteFramebuffers(1, &FramebufferName);
		glDeleteProgram(ProgramName[program::SPLASH]);
		glDeleteProgram(ProgramName[program::TEXTURE]);
		
		glDeleteBuffers(buffer::MAX, &BufferName[0]);
		glDeleteTextures(texture::MAX, &TextureName[0]);
		glDeleteVertexArrays(program::MAX, &VertexArrayName[0]);

		return true;
	}

	bool render()
	{
		glm::vec2 WindowSize(this->getWindowSize());

		{
			glBindBuffer(GL_UNIFORM_BUFFER, BufferName[buffer::TRANSFORM]);
			glm::mat4* Pointer = reinterpret_cast<glm::mat4*>(glMapBufferRange(GL_UNIFORM_BUFFER,
				0, sizeof(glm::mat4) * 2, GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT));

			glm::mat4 const Projection = glm::perspective(glm::pi<float>() * 0.25f, WindowSize.x / WindowSize.y, 0.1f, 100.0f);
			glm::mat4 const View = this->view();
			glm::mat4 const Model = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));


			*(Pointer + 0) = Projection * View * Model;
			*(Pointer + 1) = View * Model;

			// Make sure the uniform buffer is uploaded
			glUnmapBuffer(GL_UNIFORM_BUFFER);
		}

		// Render a textured quad to a sRGB framebuffer object.
		{
			glViewport(0, 0, static_cast<GLsizei>(WindowSize.x) * this->FramebufferScale, static_cast<GLsizei>(WindowSize.y) * this->FramebufferScale);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
			glEnable(GL_FRAMEBUFFER_SRGB);

			glClearBufferfv(GL_COLOR, 0, &glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)[0]);

			glUseProgram(ProgramName[program::TEXTURE]);

			glBindVertexArray(VertexArrayName[program::TEXTURE]);
			glBindBufferBase(GL_UNIFORM_BUFFER, semantic::uniform::TRANSFORM0, BufferName[buffer::TRANSFORM]);

			glDrawArraysInstanced(GL_POINTS, 0, 360, 3);

			glDisable(GL_BLEND);
		}

		// Blit the sRGB framebuffer to the default framebuffer back buffer.
		{
			glViewport(0, 0, static_cast<GLsizei>(WindowSize.x), static_cast<GLsizei>(WindowSize.y));

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			glEnable(GL_FRAMEBUFFER_SRGB);

			glUseProgram(ProgramName[program::SPLASH]);

			glActiveTexture(GL_TEXTURE0);
			glBindVertexArray(VertexArrayName[program::SPLASH]);
			glBindTexture(GL_TEXTURE_2D, TextureName[texture::COLORBUFFER]);

			glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 1);
		}

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

