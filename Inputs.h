#pragma once
#ifndef INPUTS_H
#define INPUTS_H

#include "Headers.h"
#include "Common.h"

std::string material;
std::string quality;

bool getCommandInputValue(Ptr<CommandInput> commandInput, std::string unitType, double* value)
{
    Ptr<ValueCommandInput> valCommandInput = commandInput;
    if (!commandInput)
    {
        *value = 0;
            displayErrorMessage("");
            return false;
    }

    // Verify that the expression is valid.
    Ptr<Design> des = app->activeProduct();
    Ptr<UnitsManager> unitsMgr = des->unitsManager();

    if (unitsMgr->isValidExpression(valCommandInput->expression(), unitType))
    {
        *value = unitsMgr->evaluateExpression(valCommandInput->expression(), unitType);
        return true;
    }
    else
    {
        *value = 0;
        displayErrorMessage("");
        return false;
    }
}

#endif // !INPUTS_H
