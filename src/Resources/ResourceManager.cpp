#include "ResourceManager.h"
#include "../Renderer/ShaderProgram.h"
#include "../Renderer/Texture2D.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/AnimatedSprite.h"

#define STB_IMAGE_IMPLEMENTATION
// if you'd like to use other texture image extensions
// make sure that you define appropriate key
#define STBI_ONLY_PNG
#include "stb_image.h"

#include <sstream>
#include <fstream>
#include <iostream>

ResourceManager::ShaderProgramsMap ResourceManager::shaderPrograms;
ResourceManager::TexturesMap ResourceManager::textures;
ResourceManager::SpritesMap ResourceManager::sprites;
ResourceManager::AnimatedSpritesMap ResourceManager::animatedSprites;
std::string ResourceManager::path;

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
	animatedSprites.clear();
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
		std::cerr << "ERROR::FINDING SHADER: " << shaderName << "\n";

	return shaderProgram;
}

std::shared_ptr<Renderer::Texture2D> ResourceManager::LoadTexture(const std::string& textureName, const std::string& texturePath)
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
		return nullptr;
	}

	auto texture = textures[textureName] = std::make_shared<Renderer::Texture2D>( width, height, pixels, nrChannels );
	stbi_image_free( pixels );
	return texture;
}

std::shared_ptr<Renderer::Texture2D> ResourceManager::GetTexture( const std::string& textureName )
{
	auto texture = textures.find( textureName )->second;
	if ( !texture )
		std::cerr << "ERROR::FINDING TEXTURE: " << textureName << "\n";

	return texture;
}

std::shared_ptr<Renderer::Sprite> ResourceManager::LoadSprite( const std::string& spriteName, 
															   const std::string& textureName, 
															   const std::string& shaderName, 
															   const uint32_t spriteWidth, 
															   const uint32_t spriteHeight,
															   const std::string& subTextureName )
{
	auto pTexture = GetTexture( textureName );
	if( !pTexture )
		std::cerr << "ERROR::GETTING TEXTURE: " << textureName << ". SPRITE NAME: " << spriteName << ".\n";

	auto pShader = GetShaderProgram( shaderName );
	if( !pShader )
		std::cerr << "ERROR::GETTING SHADER PROGRAM: " << shaderName << ". SPRITE NAME: " << spriteName << ".\n";

	auto sprite = sprites[spriteName] = std::make_shared<Renderer::Sprite>( pTexture, 
																			subTextureName,
																			pShader, 
																			glm::vec2( 0.f ), 
																			glm::vec2( spriteWidth, spriteHeight ) );
	
	return sprite;
}

std::shared_ptr<Renderer::Sprite> ResourceManager::GetSprite( const std::string& spriteName )
{
	auto sprite = sprites.find( spriteName )->second;
	if( !sprite )
		std::cerr << "ERROR::FINDING SPRITE: " << spriteName << "\n";

	return sprite;
}

std::shared_ptr<Renderer::AnimatedSprite> ResourceManager::LoadAnimatedSprite( const std::string& spriteName, const std::string& textureName, const std::string& shaderName, const uint32_t spriteWidth, const uint32_t spriteHeight, const std::string& subTextureName )
{
	auto pTexture = GetTexture( textureName );
	if( !pTexture )
		std::cerr << "ERROR::GETTING TEXTURE: " << textureName << ". ANIMATEDSPRITE NAME: " << spriteName << ".\n";

	auto pShader = GetShaderProgram( shaderName );
	if( !pShader )
		std::cerr << "ERROR::GETTING SHADER PROGRAM: " << shaderName << ". ANIMATEDSPRITE NAME: " << spriteName << ".\n";

	auto animatedSprite = animatedSprites[spriteName] = std::make_shared<Renderer::AnimatedSprite>( pTexture,
																			subTextureName,
																			pShader,
																			glm::vec2( 0.f ),
																			glm::vec2( spriteWidth, spriteHeight ) );

	return animatedSprite;
}

std::shared_ptr<Renderer::AnimatedSprite> ResourceManager::GetAnimatedSprite( const std::string& spriteName )
{
	auto animatedSprite = animatedSprites.find( spriteName )->second;
	if( !animatedSprite )
		std::cerr << "ERROR::FINDING ANIMATEDSPRITE: " << spriteName << "\n";

	return animatedSprite;
}

std::shared_ptr<Renderer::Texture2D> ResourceManager::LoadTextureAtlas( std::string textureName, 
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
		for( auto& currentSubTextureName : subTextures )
		{
			glm::vec2 leftBottomUV( static_cast<float>( currentTextureOffsetX ) / textureWidth, static_cast<float>( currentTextureOffsetY - subTextureHeight ) / textureHeight );
			glm::vec2 rightTopUV( static_cast<float>( currentTextureOffsetX + subTextureWidth ) / textureWidth, static_cast<float>( currentTextureOffsetY ) / textureHeight );
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
