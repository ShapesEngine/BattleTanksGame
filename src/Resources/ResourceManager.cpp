#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"

#define STB_IMAGE_IMPLEMENTATION
// if you'd like to use other texture image extensions
// make sure that you define appropriate key
#define STBI_ONLY_PNG
#include "stb_image.h"

#include <sstream>
#include <fstream>
#include <iostream>

ResourceManager::ResourceManager( const std::string& executablePath )
{
	// Finding and getting substr without slash
	// ----------------------------------------
	size_t foundSlash = executablePath.find_last_of( "/\\" );
	path = executablePath.substr( 0, foundSlash );
}

std::optional<std::string> ResourceManager::GetFileString( const std::string& relativeFilePath ) const
{
	std::fstream file;
	file.open( path + "/" + relativeFilePath, std::ios::in | std::ios::binary );
	if( !file.is_open() )
	{
		std::cerr << "ERROR::FILE_LOADING!\n";
		std::cerr << "Failed to open file: " << GetFileName( relativeFilePath ).value_or( relativeFilePath ) << "\n";
		return std::nullopt;
	}
	
	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::LoadShaders( const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath )
{
	std::string vertexString = GetFileString( vertexPath ).value_or( std::string() );
	if( vertexString.empty() )
	{
		std::cerr << "ERROR::SHADER NOT LOADED!\n";
		return nullptr;
	}

	std::string fragmentString = GetFileString( fragmentPath ).value_or( std::string() );
	if ( fragmentString.empty() )
	{
		std::cerr << "ERROR::SHADER NOT LOADED!\n";
		return nullptr;
	}

	auto program = shaderPrograms[shaderName] = std::make_shared<Renderer::ShaderProgram>( vertexString, fragmentString );

	if( program->GetStatus() )
		return program;

	std::cerr << "ERROR::SHADER NOT LOADED!\n";
	std::cerr << "INFO::VERTEX: " << GetFileName( vertexPath ).value_or( vertexPath ) << std::endl 
			  << "INFO::FRAGMENT: " << GetFileName( fragmentPath ).value_or( fragmentPath ) << std::endl;				
	
	return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::GetShaderProgram( const std::string& shaderName )
{
	auto shaderProgram = shaderPrograms.find( shaderName )->second;
	if( !shaderProgram )
		std::cerr << "ERROR::GETTING SHADER: " << shaderName << "\n";

	return shaderProgram;
}

void ResourceManager::LoadTexture(const std::string& textureName, const std::string& texturePath)
{
	int width;
	int height;
	int nrChannels;

	// flip the texture vertically, as the loaded 
	// texture will have inverted values
	// ------------------------------------------
	stbi_set_flip_vertically_on_load( true );
	unsigned char* pixels = stbi_load( ( path + "/" + texturePath ).c_str(), &width, &height, &nrChannels, 0 );
	if( !pixels )
	{
		std::cerr << "ERROR::TEXTURE NOT LOADED!\n";
		std::cerr << "INFO::TEXTURE: " << GetFileName(texturePath).value_or( textureName );
		return;
	}

	stbi_image_free( pixels );
}
