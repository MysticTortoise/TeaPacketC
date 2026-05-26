#include "TeaPacket/Bundled/InitDeInit.hpp"
#include "TeaPacket/Graphics/Display.hpp"
#include "TeaPacket/Graphics/Graphics.hpp"
#include "TeaPacket/System/System.hpp"

#include <array>

using namespace TeaPacket;
int main()
{
    if (!Bundled::Init())
    {
        Bundled::DeInit();
        return -1;
    }

    Graphics::Display::InitDefaultDisplays({Graphics::DisplayParams{1920, 1080}});

    while (System::ShouldRun())
    {
        System::Process();

        auto display = Graphics::Display(0);
        display.BeginRender();
        Graphics::ClearColor(255, 0, 0);

        Graphics::Display::FinishRender();

        Graphics::Display::PresentAll(true);
    }

    Bundled::DeInit();
}
