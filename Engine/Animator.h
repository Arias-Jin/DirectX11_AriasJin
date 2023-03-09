#pragma once
#include "Component.h"

#include "Animation.h"

namespace arias
{
	class Animator : public Component
	{
	public:
		struct Events
		{
			struct Event
			{
				void operator=(std::function<void()> func)
				{
					mEvent = std::move(func);
				}

				void operator()()
				{
					if (mEvent)
					{
						mEvent();
					}
				}

				std::function<void()> mEvent;
			};

			Event mStartEvent;
			Event mCompleteEvent;
			Event mEndEvent;
		};

		Animator();
		~Animator();

	private:
		std::map<std::wstring, Animation*> mAnimations;
		std::map<std::wstring, Events*> mEvents;
		Animation* mActiveAnimation;
		bool mbLoop;

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	public:
		bool Create(const std::wstring& name, std::shared_ptr<Texture> atlas, Vector2 leftTop, Vector2 size, Vector2 offset, UINT colLength, UINT spriteLength, float duration);

		Animation* FindAnimation(const std::wstring& name);
		Events* FindEvents(const std::wstring& name);
		void Play(std::wstring& name, bool loop = true);

		void Binds();
		void Clear();

		std::function<void()>& GetStartEvent(const std::wstring& name);
		std::function<void()>& GetCompleteEvent(const std::wstring& name);
		std::function<void()>& GetEndEvent(const std::wstring& name);
	};
}