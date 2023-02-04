#pragma once

#include "Entity.h"

namespace arias
{
	class Resource : public Entity
	{
	public:
		Resource();
		virtual ~Resource();

	private:
		std::wstring mKey;
		std::wstring mPath;

	public:
		virtual HRESULT Load(const std::wstring& path) = 0;

	public:
		void SetKey(const std::wstring& key) { mKey = key; }
		const std::wstring& GetKey() const { return mKey; }

		void SetPath(const std::wstring& path) { mPath = path; }
		const std::wstring& GetPath() const { return mPath; }
	};
}
