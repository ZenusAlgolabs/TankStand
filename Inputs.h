#pragma once
#ifndef INPUTS_H
#define INPUTS_H

#include "Headers.h"
#include "Common.h"

void tankstand_Inputs_Panel(Ptr<Design> des, Ptr<CommandInputs> inputs)
{
    std::string capacity = std::to_string(13 * 2.54);
    Ptr<Attribute> capacityAttrib = des->attributes()->itemByName("TankStand", "capacity");
    if (checkReturn(capacityAttrib))
        capacity = capacityAttrib->value();

    std::string head = std::to_string(9 * 25.4);
    Ptr<Attribute> headAttrib = des->attributes()->itemByName("TankStand", "head");
    if (checkReturn(headAttrib))
        head = headAttrib->value();

    // Define the command dialog.
    _imgInput = inputs->addImageCommandInput("tankStandImage", "", "Resources/images/TankStand.png");
    if (!checkReturn(_imgInput))
        return;
    _imgInput->isFullWidth(true);

    //Capacity
    _tankCapacity = inputs->addValueInput("capacity", "Capacity", units, ValueInput::createByReal(std::stod(capacity)));
    if (!checkReturn(_tankCapacity))
        return;

    //Head
    _tankHead = inputs->addValueInput("head", "Head", units, ValueInput::createByReal(std::stod(head)));
    if (!checkReturn(_tankHead))
        return;
}

bool getCommandInputValue(Ptr<CommandInput> commandInput, std::string unitType, double* value)
{
    Ptr<ValueCommandInput> valCommandInput = commandInput;
    if (!commandInput)
    {
        *value = 0;
            displayErrorMessage();
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
        displayErrorMessage();
        return false;
    }
}

#endif // !INPUTS_H
