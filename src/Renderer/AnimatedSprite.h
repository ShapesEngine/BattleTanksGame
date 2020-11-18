#pragma once

#include "Sprite.h"

#include <map>
#include <vector>

namespace RenderEngine
{
	class AnimatedSprite : public Sprite
	{
	public:
		typedef std::vector<std::pair<std::string, uint64_t>> animFramesVector;

	public:
		using Sprite::Sprite;

		void SetAnimation( const std::string& animName );
		void Update( size_t deltaTime );
		void Render() const override;

		inline void InsertAnimation( std::string animName, animFramesVector animState ) { animFrames.emplace( std::move( animName ), std::move( animState ) ); }

	private:
		// animation name and animations collection { animation state name and duration of animation in nanoseconds }
		std::map<std::string, animFramesVector> animFrames;
		std::map<std::string, animFramesVector>::const_iterator itCurrentAnimFrame = animFrames.end();

		size_t currentFrameIndex = 0;
		uint64_t currentFrameTime = 0;
		mutable bool isCurrentAnimFrameChanged = false;
	};
}

