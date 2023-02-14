#pragma once

#include "Engine.h"

namespace arias
{
	class Entity
	{
	public:
		Entity();
		Entity(const Entity& other);
		virtual ~Entity();

	private:
		std::wstring mName;
		const UINT64 mID;

	public:
		void SetName(const std::wstring& name) { mName = name; }
		const std::wstring& GetName() const { return mName; }

		UINT64 GetID() const { return mID; }
	};
}