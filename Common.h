#pragma once
#ifndef COMMON_H
#define COMMON_H

#include "Headers.h"

// Globals
Ptr<Application> app;
Ptr<UserInterface> ui;
std::string units = "mm";

// Global command input declarations.
Ptr<DropDownCommandInput> _waterQuality;
Ptr<DropDownCommandInput> _structureMaterial;
Ptr<TextBoxCommandInput> _errMessage;
Ptr<ImageCommandInput> _imgInput;
Ptr<ValueCommandInput> _tankCapacity;
Ptr<ValueCommandInput> _tankHead;

bool checkReturn(Ptr<Base> returnObj)
{
    if (returnObj)
        return true;
    else
        if (app && ui)
        {
            std::string errDesc;
            app->getLastError(&errDesc);
            ui->messageBox(errDesc);
            return false;
        }
        else
            return false;
}

bool is_digits(const std::string& str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

void displayErrorMessage()
{
    // get error message
    std::string errorMessage;
    int errorCode = app->getLastError(&errorMessage);
    if (GenericErrors::Ok != errorCode)
        ui->messageBox(errorMessage);
}
#endif // !COMMON_H
