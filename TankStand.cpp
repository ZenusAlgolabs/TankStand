#include "Headers.h"
#include "Common.h"
#include "Inputs.h"
#include "EventHandler.h"

extern "C" XI_EXPORT bool run(const char* context)
{
    app = Application::get();
    if (!app)
    {
        displayErrorMessage();
        return false;
    }

    ui = app->userInterface();
    if (!ui)
    {
        displayErrorMessage();
        return false;
    }

    // Create a command definition and add a button to the CREATE panel.
    Ptr<CommandDefinition> cmdDef = ui->commandDefinitions()->itemById("adskTankStandCPPScript");
    if (!cmdDef)
    {
        cmdDef = ui->commandDefinitions()->addButtonDefinition("adskTankStandCPPScript", "Tank Stand", "Creates a Tank Stand component", "Resources/");
        if (!checkReturn(cmdDef))
        {
            displayErrorMessage();
            return false;
        }
    }

    // Connect to the command created event.
    Ptr<CommandCreatedEvent> commandCreatedEvent = cmdDef->commandCreated();
    if (!checkReturn(commandCreatedEvent))
    {
        displayErrorMessage();
        return false;
    }
    bool isOk = commandCreatedEvent->add(&_standCommandCreated);
    if (!isOk)
    {
        displayErrorMessage();
        return false;
    }

    isOk = cmdDef->execute();
    if (!isOk)
    {
        displayErrorMessage();
        return false;
    }

    // Prevent this module from terminating so that the command can continue to run until
    // the user completes the command.
    adsk::autoTerminate(false);

    return true;
}


#ifdef XI_WIN

#include <windows.h>

BOOL APIENTRY DllMain(HMODULE hmodule, DWORD reason, LPVOID reserved)
{
    switch (reason)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

#endif // XI_WIN
