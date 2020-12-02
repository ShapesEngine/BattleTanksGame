#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"

#define STB_IMAGE_IMPLEMENTATION
// if you'd like to use other texture image extensions
// make sure that you define appropriate key
#define STBI_ONLY_PNG
#include "stb_image.h"

#include <rapidjson/document.h>
#include <rapidjson/error/en.h>

#include <sstream>
#include <fstream>
#include <iostream>

ResourceManager::ShaderProgramsMap ResourceManager::shaderPrograms;
ResourceManager::TexturesMap ResourceManager::textures;
ResourceManager::SpritesMap ResourceManager::sprites;
std::string ResourceManager::path;
std::vector<std::vector<std::string>> ResourceManager::levels;

std::optional<std::string> ResourceManager::GetFileString( const std::string& relativeFilePath )
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

void ResourceManager::SetExecutablePath( const std::string& executablePath )
{
	// Finding and getting substr without slash
	// ----------------------------------------
	size_t foundSlash = executablePath.find_last_of( "/\\" );
	path = executablePath.substr( 0, foundSlash );
}

void ResourceManager::UnloadAllResources()
{
	shaderPrograms.clear();
	textures.clear();
	sprites.clear();
}

std::shared_ptr<RenderEngine::ShaderProgram> ResourceManager::LoadShaders( const std::string& shaderName, const std::string& vertexPath, const std::string& fragmentPath )
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

	auto program = shaderPrograms[shaderName] = std::make_shared<RenderEngine::ShaderProgram>( vertexString, fragmentString );

	if( program->GetStatus() )
		return program;

	std::cerr << "ERROR::SHADER NOT LOADED!\n";
	std::cerr << "INFO::VERTEX: " << GetFileName( vertexPath ).value_or( vertexPath ) << std::endl 
			  << "INFO::FRAGMENT: " << GetFileName( fragmentPath ).value_or( fragmentPath ) << std::endl;				
	
	return nullptr;
}

std::shared_ptr<RenderEngine::ShaderProgram> ResourceManager::GetShaderProgram( const std::string& shaderName )
{
	auto shaderProgram = shaderPrograms.find( shaderName )->second;
	if( !shaderProgram )
		std::cerr << "ERROR::FINDING SHADER: " << shaderName << "\n";

	return shaderProgram;
}

std::shared_ptr<RenderEngine::Texture2D> ResourceManager::LoadTexture(const std::string& textureName, const std::string& texturePath)
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
		std::cerr << __LINE__ << "\n";
		std::cerr << "INFO::TEXTURE: " << GetFileName(texturePath).value_or( textureName );
		return nullptr;
	}

	auto texture = textures[textureName] = std::make_shared<RenderEngine::Texture2D>( width, height, pixels, nrChannels );
	stbi_image_free( pixels );
	return texture;
}

std::shared_ptr<RenderEngine::Texture2D> ResourceManager::GetTexture( const std::string& textureName )
{
	auto texture = textures.find( textureName )->second;
	if ( !texture )
		std::cerr << "ERROR::FINDING TEXTURE: " << textureName << "\n";

	return texture;
}

std::shared_ptr<RenderEngine::Sprite> ResourceManager::LoadSprite( const std::string& spriteName, 
															   const std::string& textureName, 
															   const std::string& shaderName, 
															   const std::string& subTextureName )
{
	auto pTexture = GetTexture( textureName );
	if( !pTexture )
		std::cerr << "ERROR::GETTING TEXTURE: " << textureName << ". SPRITE NAME: " << spriteName << ".\n";

	auto pShader = GetShaderProgram( shaderName );
	if( !pShader )
		std::cerr << "ERROR::GETTING SHADER PROGRAM: " << shaderName << ". SPRITE NAME: " << spriteName << ".\n";

	auto sprite = sprites[spriteName] = std::make_shared<RenderEngine::Sprite>( pTexture, 
																			subTextureName,
																			pShader );
	
	return sprite;
}

std::shared_ptr<RenderEngine::Sprite> ResourceManager::GetSprite( const std::string& spriteName )
{
	auto sprite = sprites.find( spriteName )->second;
	if( !sprite )
		std::cerr << "ERROR::FINDING SPRITE: " << spriteName << "\n";

	return sprite;
}

std::shared_ptr<RenderEngine::Texture2D> ResourceManager::LoadTextureAtlas( std::string textureName, 
																		std::string texturePath, 
																		std::vector<std::string> subTextures, 
																		const uint32_t subTextureWidth, 
																		const uint32_t subTextureHeight )
{
	auto pTexture = LoadTexture( std::move( textureName ), std::move( texturePath ) );
	if( pTexture )
	{
		const uint32_t textureWidth = pTexture->GetWidth();
		const uint32_t textureHeight = pTexture->GetHeight();
		uint32_t currentTextureOffsetX = 0;
		uint32_t currentTextureOffsetY = textureHeight;
		const float textureOffset = 0.1F;
		for( auto& currentSubTextureName : subTextures )
		{
			// adding textureoffset to discard neighbor subtexture pixels
			glm::vec2 leftBottomUV( float( currentTextureOffsetX + textureOffset ) / textureWidth, float( currentTextureOffsetY - subTextureHeight + textureOffset ) / textureHeight );
			// adding textureoffset to discard neighbor subtexture pixels
			glm::vec2 rightTopUV( float( currentTextureOffsetX + subTextureWidth - textureOffset ) / textureWidth, float( currentTextureOffsetY - textureOffset ) / textureHeight );
			pTexture->AddSubTexture( std::move( currentSubTextureName ), leftBottomUV, rightTopUV );

			currentTextureOffsetX += subTextureWidth;
			if( currentTextureOffsetX >= textureWidth )
			{
				currentTextureOffsetX = 0;
				currentTextureOffsetY -= subTextureHeight;
			}
		}
	}
	return pTexture;
}

bool ResourceManager::loadJSONResources( const std::string& relativeFilePath )
{
	if( const auto tempFile = GetFileString( relativeFilePath ) )
	{
		rapidjson::Document document;
		rapidjson::ParseResult parseResult = document.Parse( tempFile->c_str() );

		if( !parseResult )
		{
			std::cerr << "ERROR::JSON File Parsing!\n" << "Message: " << rapidjson::GetParseError_En( parseResult.Code() ) << "(" <<
				parseResult.Offset() << ")" << std::endl;
			std::cerr << "JSON File: " << relativeFilePath << "\n";
			return false;
		}

		auto shadersIt = document.FindMember( "shaders" );
		if( shadersIt != document.MemberEnd() )
		{
			for( const auto& currentShader : shadersIt->value.GetArray() )
			{
				const std::string& name = currentShader["name"].GetString();
				const std::string& filePath_v = currentShader["filepath_v"].GetString();
				const std::string& filePath_f = currentShader["filepath_f"].GetString();
				LoadShaders( name, filePath_v, filePath_f );
			}
		}

		auto textureAtlasesIt = document.FindMember( "textureAtlases" );
		if( textureAtlasesIt != document.MemberEnd() )
		{
			for( const auto& currentTexAtlas : textureAtlasesIt->value.GetArray() )
			{
				const std::string& name = currentTexAtlas["name"].GetString();
				const std::string& filePath = currentTexAtlas["filepath"].GetString();
				const uint32_t subtexture_width = currentTexAtlas["subtexture_width"].GetUint();
				const uint32_t subtexture_height = currentTexAtlas["subtexture_height"].GetUint();
				const auto texAtlasArr = currentTexAtlas["subtextures"].GetArray();
				std::vector<std::string> subtextures;
				subtextures.reserve( texAtlasArr.Size() );
				for( const auto& currentSubtexture : texAtlasArr )
				{
					subtextures.emplace_back( currentSubtexture.GetString() );
				}
				LoadTextureAtlas( name, filePath, subtextures, subtexture_width, subtexture_height );
			}
		}

		auto levelsIt = document.FindMember( "levels" );
		if( levelsIt != document.MemberEnd() )
		{
			for( const auto& currentLevel : levelsIt->value.GetArray() )
			{
				const auto description = currentLevel["description"].GetArray();
				std::vector<std::string> levelRows;
				size_t maxLength = 0;
				levelRows.reserve( description.Size() );
				for( const auto& currentRow : description )
				{
					levelRows.emplace_back( currentRow.GetString() );
					if( maxLength < levelRows.back().length() )
					{
						maxLength = levelRows.back().length();
					}
				}

				for( auto& currentRow : levelRows )
				{
					while( currentRow.length() < maxLength )
					{
						currentRow.append( "D" );
					}
				}
				levels.emplace_back( std::move( levelRows ) );
			}
		}
		
		auto spritesIt = document.FindMember( "sprites" );
		if( spritesIt != document.MemberEnd() )
		{
			for( const auto& currentSprite : spritesIt->value.GetArray() )
			{
				const std::string name = currentSprite["name"].GetString();
				const std::string textureAtlas = currentSprite["texture_atlas"].GetString();
				const std::string shader = currentSprite["shader"].GetString();
				const std::string subTexture = currentSprite["subTextureName"].GetString();

				auto pSprite = LoadSprite( name, textureAtlas, shader, subTexture );
				if( !pSprite )
				{
					continue;
				}

				auto framesIt = currentSprite.FindMember( "frames" );
				if( framesIt != currentSprite.MemberEnd() )
				{
					const auto framesArray = framesIt->value.GetArray();
					std::vector<RenderEngine::Sprite::FrameDesc> framesDescriptions;
					framesDescriptions.reserve( framesArray.Size() );
					for( const auto& currentFrame : framesArray )
					{
						const std::string subTextureStr = currentFrame["subtexture"].GetString();
						const uint64_t duration = currentFrame["duration"].GetDouble();
						const auto pTextureAtlas = GetTexture( textureAtlas );
						const auto pSubTexture = pTextureAtlas->GetSubTexture( subTextureStr );
						framesDescriptions.emplace_back( pSubTexture.leftBottomUV, pSubTexture.rightTopUV, duration );
					}
					pSprite->InsertFrames( std::move( framesDescriptions ) );
				}
			}
		}

		return true;
	}
	std::cerr << "ERROR::JSON Resource Not Loaded!\n";
	return false;
}
