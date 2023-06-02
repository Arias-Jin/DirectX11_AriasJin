#pragma once

#include "Engine.h"

#include "GraphicDevice_DX11.h"
#include "Graphics.h"

namespace arias
{
	class Application
	{
	public:
		Application();
		~Application();

	private:
		bool mInitialized = false;
		std::unique_ptr<graphics::GraphicDevice_DX11> mGraphicDevice;

		HWND mHwnd;
		HDC mHdc;
		UINT mWidth;
		UINT mHeight;

	public:
		virtual void Initialize();

		// CPU UPDATE
		virtual void Update();

		// GPU UPDATE
		virtual void FixedUpdate();
		virtual void Render();
		virtual void Destroy();

		// Running Main Engine Loop
		void Run();
		void Present();
		void Release();

		void SetWindow(HWND hwnd, UINT width, UINT height);
		Vector2 GetResolutionRatio();

	public:
		void SetHwnd(HWND hwnd) { mHwnd = hwnd; }
		HWND GetHwnd() const { return mHwnd; }

		HDC GetHdc() const { return mHdc; }

		UINT GetWidth() const { return mWidth; }
		UINT GetHeight() const { return mHeight; }

	};
}