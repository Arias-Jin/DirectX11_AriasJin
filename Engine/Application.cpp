#include "Application.h"

#include "Input.h"

#include "Renderer.h"

#include "SceneManager.h"

#include "Time.h"

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
        Update();
        FixedUpdate();
        Render();
    }

    void Application::Initialize()
    {
        Time::Initialize();
        Input::Initialize();

        renderer::Initialize();
        SceneManager::Initialize();
    }

    // CPU UPDATE
    void Application::Update()
    {
        Time::Update();
        Input::Update();

        SceneManager::Update();
    }

    // GPU UPDATE
    void Application::FixedUpdate()
    {
        SceneManager::FixedUpdate();
    }

    void Application::Render()
    {
        Time::Render(mHdc);
        SceneManager::Render();

        mGraphicDevice->Render();
    }

    void Application::SetWindow(HWND hwnd, UINT width, UINT height)
    {
        if (mGraphicDevice == nullptr)
        {
            mHwnd = hwnd;
            mHdc = GetDC(mHwnd);
            mWidth = width;
            mHeight = height;

            ValidationMode validationMode = ValidationMode::Disabled;
            mGraphicDevice = std::make_unique<GraphicDevice_DX11>();
            graphics::GetDevice() = mGraphicDevice.get();
        }

        RECT windowRect = { 0, 0, (LONG)width, (LONG)height };
        AdjustWindowRect(&windowRect, WS_OVERLAPPEDWINDOW, false);
        SetWindowPos(mHwnd, nullptr, 0, 0, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top, 0);
        ShowWindow(mHwnd, true);
        UpdateWindow(mHwnd);
    }
}