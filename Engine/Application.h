#pragma once

#include "CommonInclude.h"

#include "GraphicDevice_DX11.h"
#include "Graphics.h"

namespace arias
{
	class Application
	{
	private:
		HWND mHwnd;

	public:
		Application();
		~Application();

	private:
		bool mInitialized = false;
		std::unique_ptr<graphics::GraphicDevice_DX11> mGraphicDevice;

		HWND mHwnd;
		UINT mWidth;
		UINT mHeight;

	public:
		// Running Main Engine Loop
		void Run();

		virtual void Initialize();

		// CPU UPDATE
		virtual void Update();

		// GPU UPDATE
		virtual void FixedUpdate();
		virtual void Render();
		void SetWindow(HWND hwnd, UINT width, UINT height);

	public:
		void SetHwnd(HWND hwnd) { mHwnd = hwnd; }
		HWND GetHwnd() const { return mHwnd; }
	};
}