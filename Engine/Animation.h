#pragma once
#include "Entity.h"

#include "Texture.h"

using namespace arias::math;
using namespace arias::graphics;

namespace arias
{
	class Animation : public Entity
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;	// 좌측 상단 좌표
			Vector2 size;		// 좌측 상단부터 잘라낼 가로 세로의 픽셀 길이
			Vector2 offset;		// 렌더링 위치 조정하기위한 좌표
			Vector2 atlasSize;	// 텍스처 이미지의 크기
			float duration;		// 프레임간의 시간 간격

			Sprite() :
				leftTop(0.0f, 0.0f),
				size(0.0f, 0.0f),
				offset(0.0f, 0.0f),
				atlasSize(0.0f),
				duration(0.1f)
			{
			}
		};

		Animation();
		Animation(const Animation&);
		~Animation();

	private:
		class Animator* mAnimator;
		std::wstring mAnimationName;
		std::shared_ptr<Texture> mAtlas;
		std::vector<Sprite> mSpriteSheet;
		size_t mIndex;
		float mTime;
		bool mbComplete;

	public:
		UINT Update();
		void FixedUpdate();
		void Render();

	public:
		void Create(const std::wstring& name, std::shared_ptr<Texture> atlas, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration);
		void BindShader();
		void Reset();
		void Clear();

	public:
		void SetFalse() { mbComplete = false; }
		bool IsComplete() { return mbComplete; }

		std::wstring& AnimationName() { return mAnimationName; }
	};
}