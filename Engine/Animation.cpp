#include "Animation.h"

#include "Renderer.h"

#include "Time.h"

namespace arias
{
	Animation::Animation() :
		mAnimator(nullptr),
		mAnimationName{},
		mAtlas(nullptr),
		mSpriteSheet{},
		mIndex(-1),
		mTime(0.0f),
		mbComplete(false)
	{
	}

	Animation::~Animation()
	{
	}

	UINT Animation::Update()
	{
		if (mbComplete)
		{
			return -1;
		}

		mTime += Time::DeltaTime();

		if (mSpriteSheet[mIndex].duration < mTime)
		{
			mTime = 0.0f;
			++mIndex;

			if (mSpriteSheet.size() <= mIndex)
			{
				mbComplete = true;
				mIndex = mSpriteSheet.size() - 1;
			}

			return (UINT)mIndex;
		}

		return -1;
	}
	
	void Animation::FixedUpdate()
	{
	}
	
	void Animation::Render()
	{
	}
	
	void Animation::Create(const std::wstring& name, std::shared_ptr<Texture> atlas, Vector2 leftTop, Vector2 size, Vector2 offset, UINT spriteLength, float duration)
	{
		mAnimationName = name;
		mAtlas = atlas;

		float width = (float)atlas->GetWidth();
		float height = (float)atlas->GetHeight();

		int maxSpritesPerRow = (int)(width / size.x);
		int rowIndex = 0;

		for (size_t i = 0; i < spriteLength; ++i)
		{
			Sprite sprite = {};
			sprite.leftTop = Vector2((leftTop.x + (size.x * (float)(i % maxSpritesPerRow))) / width, (leftTop.y + (size.y * (float)rowIndex)) / height);
			sprite.size = Vector2(size.x / width, size.y / height);
			sprite.offset = offset;
			sprite.duration = duration;
			sprite.atlasSize = Vector2(size.x / width, size.y / height);

			mSpriteSheet.push_back(sprite);

			if ((i + 1) % maxSpritesPerRow == 0)
			{
				rowIndex++;
			}
		}
	}

	void Animation::BindShader()
	{
		mAtlas->BindShader(eShaderStage::PS, 12);

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animation];

		renderer::AnimationCB info = {};
		info.type = (UINT)eAnimationType::SecondDimension;
		info.leftTop = mSpriteSheet[mIndex].leftTop;
		info.offset = mSpriteSheet[mIndex].offset;
		info.size = mSpriteSheet[mIndex].size;
		info.atlasSize = mSpriteSheet[mIndex].atlasSize;

		cb->Bind(&info);
		cb->SetPipeline(eShaderStage::PS);
	}
	
	void Animation::Reset()
	{
		mTime = 0.0f;
		mIndex = 0;
		mbComplete = false;
	}
	
	void Animation::Clear()
	{
		// Texture clear
		Texture::Clear(12);

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Animation];
		renderer::AnimationCB info = {};
		info.type = (UINT)eAnimationType::None;

		cb->Bind(&info);
		cb->SetPipeline(eShaderStage::PS);
	}
}