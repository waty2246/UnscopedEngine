#include"Objects/TriangleObject.h"
#include "Objects/TextureObject.h"
#include "DemoApplication.h"

namespace ue
{
    DemoApplication::DemoApplication():
        _frameCount(0),
        _frameTime(0.0),
        _scene(std::make_unique<TextureObject>()),
        _graphics(),
        _windowTitle(),
        _movementComponent(std::make_unique<MovementComponent>()),
        _hasInit(false)
    {
    }

    void DemoApplication::Init(uintptr_t state)
    {
        if (_hasInit)
        {
            return;
        }
        _hasInit = true;

        //Init graphics
        _graphics = this->GetService<IGraphicsController>();
        _graphics->Init(state);

        //Init camera
        _camera = this->GetService<CameraComponent>();
        _camera->Init(state);

        _timer= this->GetService<TimerComponent>();
        _input = this->GetService<DemoInputComponent>();
        _input->Init(state);

        _window = this->GetService<IWindow, IFlexibleWindow>();
        _window->SetWindowTitle(L"");

        _movementComponent->Init(state);

        //Init scene
        _scene->Init(state);

        _windowTitle = _window->GetWindowTitle()+L" FPS:";
    }

    bool DemoApplication::Frame()
    {
        this->ReportFrameRate();
        _input->Frame();

        if (_input->IsTerminateTrigger())
        {
            return false;
        }
        //std::cout << _input->GetMousePosition().GetX() << std::endl;

        _movementComponent->Frame();
        _camera->Frame();
        _scene->Frame();

        _graphics->BeginRender();
        this->Render();
        _graphics->EndRender();

        Sleep(30);
        return true;
    }

    void DemoApplication::Render()
    {
        //Render Scenes
        _scene->Render();
    }

    void DemoApplication::ReportFrameRate()
    {
        _frameTime += _timer->GetFrameTime(TimeUnit::MILLISECOND);
        if (_frameTime > 1000.0)
        {
            _window->SetWindowTitle(_windowTitle + std::to_wstring(_frameCount));
            _frameCount = 0;
            _frameTime -= 1000.0;
        }
        ++_frameCount;
    }
}

