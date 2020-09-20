#pragma once

#include <string>
#include <memory>
#include <map>
#include <optional>

namespace Renderer
{
	class ShaderProgram;
	class Texture2D;
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

private:
	std::optional<std::string> GetFileString( const std::string& relativeFilePath ) const;
	inline std::optional<std::string> GetFileName( const std::string& filePath ) const { return filePath.substr( filePath.find_last_of( "/\\" ) + 1, filePath.length() ); }

private:
	typedef std::map<const std::string, std::shared_ptr<Renderer::ShaderProgram>> ShaderProgramMap;
	typedef std::map<const std::string, std::shared_ptr<Renderer::Texture2D>> TextureMap;
	ShaderProgramMap shaderPrograms;
	TextureMap textures;

	std::string path;
};