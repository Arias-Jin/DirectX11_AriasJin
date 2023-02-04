#include "Application.h"

namespace arias
{
    using namespace graphics;

    Application::Application() :
        mInitialized(false),
        mGraphicDevice(nullptr),
        mHwnd(nullptr),
        mWidth(0),
        mHeight(0)
    {
    }

    Application::~Application()
    {
    }

    // Running Main Engine Loop
    void Application::Run()
    {
    }

    void Application::Initialize()
    {
    }

    // CPU UPDATE
    void Application::Update()
    {
    }

    // GPU UPDATE
    void Application::FixedUpdate()
    {
    }

    void Application::Render()
    {
    }

    void Application::SetWindow(HWND hwnd, UINT width, UINT height)
    {
        if (mGraphicDevice == nullptr)
        {
            mHwnd = hwnd;
            mWidth = width;
            mHeight = height;

            ValidationMode validationMode = ValidationMode::Disabled;
            mGraphicDevice = std::make_unique<GraphicDevice_DX11>();
        }

        RECT windowRect = { 0, 0, (LONG)width, (LONG)height };
        AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);
        SetWindowPos(mHwnd, nullptr, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, 0);
        ShowWindow(mHwnd, true);
        UpdateWindow(mHwnd);
    }
}