#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <memory>
#include <string>
#include <vector>

#include "../System/Utils/IndexBuffer.h"
#include "../System/Utils/VertexBuffer.h"
#include "../System/Utils/VertexArray.h"

namespace RenderEngine
{
	class Texture2D;
	class ShaderProgram;

	class Sprite
	{
	public:
		struct FrameDesc
		{
			FrameDesc( const glm::vec2& leftBottomUV, const glm::vec2& rightTopUV, double duration ) :
				leftBottomUV( leftBottomUV ),
				rightTopUV( rightTopUV ),
				duration( duration )
			{}
			glm::vec2 leftBottomUV;
			glm::vec2 rightTopUV;
			double duration;
		};

	public:
		Sprite( std::shared_ptr<Texture2D> pTexture,
				std::string initialSubTexture,
				std::shared_ptr<ShaderProgram> pShaderProgram );

		void Render( const glm::vec2& position, const glm::vec2& size, float rotation, float depthLayer, size_t frameId = 0 ) const;

		inline void InsertFrames( std::vector<FrameDesc> framesDescriptions ) { descFrames = std::move( framesDescriptions ); }
		inline double GetFrameDuration( size_t frameId ) const { return descFrames[frameId].duration; }
		inline size_t GetFramesCount() const { return descFrames.size(); }

	protected:
		std::vector<GLfloat> GetSubTextureCoordinates( std::string initialSubTexture ) const;

		std::shared_ptr<Texture2D> pTexture;
		Utils::VertexBuffer textureCoordsBuffer;

	private:
		std::shared_ptr<ShaderProgram> pShaderProgram;

		Utils::VertexArray vertexArray;
		Utils::VertexBuffer vertexCoordsBuffer;	
		Utils::IndexBuffer indicesBuffer;	

		std::vector<FrameDesc> descFrames;
		mutable size_t lastFrameId = 0;
	};
}