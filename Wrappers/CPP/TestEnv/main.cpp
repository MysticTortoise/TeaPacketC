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

    std::array paramList = {Graphics::DisplayParams{1920, 1080}};
    Graphics::Display::InitDefaultDisplays(paramList);

    while (System::ShouldRun())
    {
        System::Process();

        auto display = Graphics::Display(0);
        display.BeginRender();
        Graphics::ClearColor(255, 0, 0);

        display.FinishRender();

        Graphics::Display::PresentAll();
        Graphics::Display::WaitForVSync();
    }

    Bundled::DeInit();
}
