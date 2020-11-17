#pragma once

#include <string>
#include <memory>
#include <map>
#include <optional>
#include <vector>

namespace Renderer
{
	class ShaderProgram;
	class Texture2D;
	class Sprite;
	class AnimatedSprite;
}

class ResourceManager
{
public:
	ResourceManager( const std::string& executablePath );

	ResourceManager( const ResourceManager& ) = delete;
	ResourceManager( const ResourceManager&& ) = delete;
	ResourceManager operator=( const ResourceManager& ) = delete;
	ResourceManager operator=( const ResourceManager&& ) = delete;

	// Provide relative path from the executable path
	std::shared_ptr<Renderer::ShaderProgram> LoadShaders( const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath );
	std::shared_ptr<Renderer::ShaderProgram> GetShaderProgram( const std::string& shaderName );
	// Provide relative path from the executable path
	std::shared_ptr<Renderer::Texture2D> LoadTexture( const std::string& textureName, const std::string& texturePath );
	std::shared_ptr<Renderer::Texture2D> GetTexture( const std::string& textureName );
	// Provide relative path from the executable path
	std::shared_ptr<Renderer::Sprite> LoadSprite( const std::string& spriteName,
												  const std::string& textureName,
												  const std::string& shaderName,
												  const uint32_t spriteWidth,
												  const uint32_t spriteHeight,
												  const std::string& subTextureName = "default" );
	std::shared_ptr<Renderer::Sprite> GetSprite( const std::string& spriteName );
	// Provide relative path from the executable path
	std::shared_ptr<Renderer::AnimatedSprite> LoadAnimatedSprite( const std::string& spriteName,
												  const std::string& textureName,
												  const std::string& shaderName,
												  const uint32_t spriteWidth,
												  const uint32_t spriteHeight,
												  const std::string& subTextureName = "default" );
	std::shared_ptr<Renderer::AnimatedSprite> GetAnimatedSprite( const std::string& spriteName );
	// Provide relative path from the executable path
	std::shared_ptr<Renderer::Texture2D> LoadTextureAtlas( std::string textureName,
														   std::string texturePath,
														   std::vector<std::string> subTextures,
														   const uint32_t subTextureWidth,
														   const uint32_t subTextureHeight );
private:
	std::optional<std::string> GetFileString( const std::string& relativeFilePath ) const;
	inline std::optional<std::string> GetFileName( const std::string& filePath ) const { return filePath.substr( filePath.find_last_of( "/\\" ) + 1, filePath.length() ); }

private:
	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramsMap;
	typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2D>> TexturesMap;
	typedef std::map<const std::string, std::shared_ptr<Renderer::Sprite>> SpritesMap;
	typedef std::map<const std::string, std::shared_ptr<Renderer::AnimatedSprite>> AnimatedSpritesMap;

	ShaderProgramsMap shaderPrograms;
	TexturesMap textures;
	SpritesMap sprites;
	AnimatedSpritesMap animatedSprites;

	std::string path;
};