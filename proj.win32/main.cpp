#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"

//TODO: все проходы по вектору как в с++ 11
//TODO: observer между Map и Shape, подумать где ещё
//TODO: deal with includes

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // create the application instance
    AppDelegate app;
    return Application::getInstance()->run();
}
