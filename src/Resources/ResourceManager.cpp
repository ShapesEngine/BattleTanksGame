#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"

#include <sstream>
#include <fstream>
#include <iostream>

ResourceManager::ResourceManager( const std::string& executablePath )
{
	// Finding and getting substr without slash
	// ----------------------------------------
	size_t foundSlash = executablePath.find_last_of( "/\\" );
	path = executablePath.substr( 0, foundSlash );
	std::string pr = executablePath.substr( executablePath.find_last_of("/\\") + 1, executablePath.length() );
}

std::optional<std::string> ResourceManager::GetFileString( const std::string& relativeFilePath ) const
{
	std::fstream file;
	file.open( path + "/" + relativeFilePath, std::ios::in | std::ios::binary );
	if( !file.is_open() )
	{
		std::cerr << "ERROR::FILE_LOADING:\n";
		std::cerr << "Failed to open file: " << relativeFilePath.substr( relativeFilePath.find_last_of( "/\\" ) + 1, relativeFilePath.length() ) 
				  << "\n";
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
	std::cerr << "INFO::VERTEX: " << vertexPath << std::endl 
			  << "INFO::FRAGMENT: " << fragmentPath << std::endl;
				
	
	return nullptr;
}

std::shared_ptr<Renderer::ShaderProgram> ResourceManager::GetShaderProgram( const std::string& shaderName )
{
	auto shaderProgram = shaderPrograms.find( shaderName )->second;
	if( !shaderProgram )
		std::cerr << "ERROR::GETTING SHADER: " << shaderName << "\n";

	return shaderProgram;
}
