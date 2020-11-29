#pragma once

#include <string>
#include <memory>
#include <map>
#include <optional>
#include <vector>

namespace RenderEngine
{
	class ShaderProgram;
	class Texture2D;
	class Sprite;
}

class ResourceManager
{
public:	
	ResourceManager() = delete;
	ResourceManager( const ResourceManager& ) = delete;
	ResourceManager( const ResourceManager&& ) = delete;
	ResourceManager operator=( const ResourceManager& ) = delete;
	ResourceManager operator=( const ResourceManager&& ) = delete;
	~ResourceManager() = delete;

	static void SetExecutablePath( const std::string& executablePath );
	static void UnloadAllResources();

	// Provide relative path from the executable path
	static std::shared_ptr<RenderEngine::ShaderProgram> LoadShaders( const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath );
	static std::shared_ptr<RenderEngine::ShaderProgram> GetShaderProgram( const std::string& shaderName );
	// Provide relative path from the executable path
	static std::shared_ptr<RenderEngine::Texture2D> LoadTexture( const std::string& textureName, const std::string& texturePath );
	static std::shared_ptr<RenderEngine::Texture2D> GetTexture( const std::string& textureName );
	// Provide relative path from the executable path
	static std::shared_ptr<RenderEngine::Sprite> LoadSprite( const std::string& spriteName,
												  const std::string& textureName,
												  const std::string& shaderName,
												  const std::string& subTextureName = "default" );
	static std::shared_ptr<RenderEngine::Sprite> GetSprite( const std::string& spriteName );
	// Provide relative path from the executable path
	static std::shared_ptr<RenderEngine::Texture2D> LoadTextureAtlas( std::string textureName,
														   std::string texturePath,
														   std::vector<std::string> subTextures,
														   const uint32_t subTextureWidth,
														   const uint32_t subTextureHeight );
	// Provide relative path from the executable path
	static bool loadJSONResources(const std::string& relativeFilePath); 
	static const std::vector<std::vector<std::string>>& GetLevels() { return levels; } 

private:
	static std::optional<std::string> GetFileString( const std::string& relativeFilePath );
	static inline std::optional<std::string> GetFileName( const std::string& filePath ) { return filePath.substr( filePath.find_last_of( "/\\" ) + 1, filePath.length() ); }

private:
	typedef std::map<const std::string, std::shared_ptr<RenderEngine::ShaderProgram>> ShaderProgramsMap;
	typedef std::map<const std::string, std::shared_ptr<RenderEngine::Texture2D>> TexturesMap;
	typedef std::map<const std::string, std::shared_ptr<RenderEngine::Sprite>> SpritesMap;

	static ShaderProgramsMap shaderPrograms;
	static TexturesMap textures;
	static SpritesMap sprites;

	static std::vector<std::vector<std::string>> levels; 

	static std::string path;
};