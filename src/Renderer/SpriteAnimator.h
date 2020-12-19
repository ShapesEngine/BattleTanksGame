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
		void Reset();

		inline size_t GetCurrentFrame() const { return currentFrame; }
		inline double GetTotalDuration() const { return totalDuration; }		

	private:
		std::shared_ptr<Sprite> pSprite;
		size_t currentFrame;
		double currentFrameDuration;
		double currentAnimationTime;
		double totalDuration = 0.0;
	};
}
