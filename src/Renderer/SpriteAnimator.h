#pragma once

#include <memory>

namespace RenderEngine
{
	class Sprite;

	class SpriteAnimator
	{
	public:
		SpriteAnimator( std::shared_ptr<Sprite> pSprite );
		void Update( double delta );

		size_t GetCurrentFrame() const { return currentFrame; }

	private:
		std::shared_ptr<Sprite> pSprite;
		size_t currentFrame = 0;
		double currentFrameDuration;
		double currentAnimationTime = 0.0;
	};
}
