#pragma once

#include <memory>

namespace RenderEngine
{
	class Sprite;

	class SpriteAnimator
	{
	public:
		SpriteAnimator( std::shared_ptr<Sprite> pSprite );
		void Update( uint64_t delta );

		size_t GetCurrentFrame() const { return currentFrame; }

	private:
		std::shared_ptr<Sprite> pSprite;
		size_t currentFrame = 0;
		uint64_t currentFrameDuration;
		uint64_t currentAnimationTime = 0;
	};
}
