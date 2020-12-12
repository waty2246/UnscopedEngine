#include <iostream>
#include"System/SystemController.h"
#include"System/IApplication.h"
#include"System/WindowBuilder.h"
#include"Components/TimerComponent.h"
#include"Demo/DemoApplication.h"
#include"Demo/Components/DemoInputComponent.h"
#include"Demo/System/DemoEventHandler.h"
#include"Graphics/DX11/DX11GraphicsController.h"

int main()
{
    try 
    {
        ue::SystemController sc;

        auto window = std::make_unique<ue::WindowBuilder>()
            ->SetWindowMode(ue::WindowMode::WINDOW)
            ->SetPositionX(100)
            ->SetPositionY(100)
            ->SetScreenHeight(800)
            ->SetScreenWidth(1200)
            ->SetWindowTitle(L"Demo Unscoped Engine")
            ->Build();

        sc.GetServiceBuilder()
            ->AddService<ue::IApplication>(new ue::DemoApplication())
            ->AddService<ue::IWindow>(window)
            ->AddService<ue::IGraphicsController>(new ue::DX11GraphicsController())
            ->AddService<ue::TimerComponent>(new ue::TimerComponent())
            ->AddService<ue::CameraComponent>(new ue::CameraComponent())
            ->AddService<ue::DemoInputComponent>(new ue::DemoInputComponent());

        window = nullptr;

        sc.Init();
        sc.Run(new ue::DemoEventHandler());
    }
    catch (std::exception& ex)
    {
        MessageBoxA(nullptr, ex.what(), "Exception information", MB_OK);
    }
    return 0;
}
