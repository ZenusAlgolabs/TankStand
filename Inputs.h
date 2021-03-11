#pragma once
#ifndef INPUTS_H
#define INPUTS_H

#include "Headers.h"
#include "Common.h"

std::string material;
std::string quality;

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

    _imgInput->isVisible(true);

    _waterQuality = inputs->addDropDownCommandInput("waterQuality", "Quality", TextListDropDownStyle);
    if (!checkReturn(_waterQuality))
        return;

    _structureMaterial = inputs->addDropDownCommandInput("structureMaterial", "Material", TextListDropDownStyle);
    if (!checkReturn(_structureMaterial))
        return;

    if (quality == "Fresh")
    {
        _waterQuality->listItems()->add("Fresh", true);
        _waterQuality->listItems()->add("Salty", false);
    }
    else
    {
        _waterQuality->listItems()->add("Fresh", false);
        _waterQuality->listItems()->add("Salty", true);
    }

    if (material == "Aluminium")
    {
        _structureMaterial->listItems()->add("Aluminium", true);
        _structureMaterial->listItems()->add("Steel", false);
    }
    else
    {
        _structureMaterial->listItems()->add("Aluminium", false);
        _structureMaterial->listItems()->add("Steel", true);
    }

    _errMessage = inputs->addTextBoxCommandInput("errMessage", "", "", 2, true);
    if (!checkReturn(_errMessage))
        return;
    _errMessage->isFullWidth(true);

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
