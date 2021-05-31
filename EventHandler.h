#pragma once
#ifndef EVENTS_HANDLER_H
#define EVENTS_HANDLER_H

#include "Common.h"
#include "drawStand.h"

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

// Event handler for the execute event.
class StandCommandExecuteEventHandler : public adsk::core::CommandEventHandler
{
public:
    void notify(const Ptr<CommandEventArgs>& eventArgs) override
    {
        Ptr<Documents> documents = app->documents();
        if (!documents)
            return;

        Ptr<Document> doc = documents->add(DocumentTypes::FusionDesignDocumentType);
        if (!doc)
            return;

        Ptr<Product> product = app->activeProduct();
        if (!product)
            return;

        // Save the current values as attributes.
        Ptr<Design> design = product;
        if (!design)
            return;

        Ptr<Attributes> attribs = design->attributes();
        attribs->add("TankStand", "material", _structureMaterial->selectedItem()->name());
        attribs->add("TankStand", "tankHead", std::to_string(_tankHead->value()));
        attribs->add("TankStand", "tankCapacity", std::to_string(_tankCapacity->value()));
        attribs->add("TankStand", "fluidType", _fluidType->selectedItem()->name());
        attribs->add("TankStand", "fluidDensity", std::to_string(_fluidDensity->value()));
        attribs->add("TankStand", "costPerMeter_Sq", std::to_string(_costPerMeter_Sq->value()));
        attribs->add("TankStand", "costPerMeter_L", std::to_string(_costPerMeter_L->value()));
        attribs->add("TankStand", "costPerMeter_U", std::to_string(_costPerMeter_U->value()));

        // Get the current values.
        string material = _structureMaterial->selectedItem()->name();
        double tankHead = _tankHead->value();
        double tankCapacity = _tankCapacity->value();
        string fluidType = _fluidType->selectedItem()->name();
        double fluidDensity = _fluidDensity->value();
        double costPerMeter_Sq = _costPerMeter_Sq->value();
        double costPerMeter_L = _costPerMeter_L->value();
        double costPerMeter_U = _costPerMeter_U->value();

        // Create the gear.
        drawTankStand(design, material, tankHead, tankCapacity, fluidType, fluidDensity, costPerMeter_Sq, costPerMeter_L, costPerMeter_U);
    }
} _standCommandExecute;

class StandCommandInputChangedHandler : public adsk::core::InputChangedEventHandler
{
public:
    void notify(const Ptr<InputChangedEventArgs>& eventArgs) override
    {
        Ptr<CommandInput> changedInput = eventArgs->input();

        if (changedInput->id() == "material")
        {
            if (_structureMaterial->selectedItem()->name() == "Aluminium")
            {
                _imgInput->isVisible(false);
                units = "m";
            }
            else if (_structureMaterial->selectedItem()->name() == "Steel")
            {
                _imgInput->isVisible(true);
                units = "m";
            }
            _tankCapacity->value(_tankCapacity->value());
            _tankCapacity->unitType(units);
            _tankHead->value(_tankHead->value());
            _tankHead->unitType(units);
        }
    }
} _standCommandInputChanged;

class GearCommandValidateInputsEventHandler : public adsk::core::ValidateInputsEventHandler
{
public:
    void notify(const Ptr<ValidateInputsEventArgs>& eventArgs) override
    {
        displayErrorMessage("");
        _errMessage->text("");
    }
} _standCommandValidateInputs;

class TankStandCommandDestroyEventHandler : public adsk::core::CommandEventHandler
{
public:
    void notify(const Ptr<CommandEventArgs>& eventArgs) override
    {
        // Terminate the script since the command has finished.
        adsk::terminate();
    }
} _standCommandDestroy;

class TankStandCommandCreatedEventHandler : public adsk::core::CommandCreatedEventHandler
{
public:
    void notify(const Ptr<CommandCreatedEventArgs>& eventArgs) override
    {
        // Verify that a Fusion design is active.
        Ptr<Design> design = app->activeProduct();
        if (!checkReturn(design))
        {
            ui->messageBox("A Fusion design must be active when invoking this command.");
            return;
        }
        // Define the default values and get the previous values from the attributes.
        std::string material = "Steel";

        Ptr<Attribute> structureMaterialAttribute = design->attributes()->itemByName("TankStand", "material");
        if (checkReturn(structureMaterialAttribute))
            material = structureMaterialAttribute->value();
        if (material == "Aluminium")
        {
        }
        else
        {
        }

        std::string fluidType = "Water";
        Ptr<Attribute> fluidTypeAttribute = design->attributes()->itemByName("TankStand", "fluidType");
        if (checkReturn(fluidTypeAttribute))
            fluidType = fluidTypeAttribute->value();

        std::string fluidDensity = "0";
        Ptr<Attribute> fluidDensityAttribute = design->attributes()->itemByName("TankStand", "fluidDensity");
        if (checkReturn(fluidDensityAttribute))
            fluidDensity = fluidDensityAttribute->value();

        std::string tankCapacity = "0";
        Ptr<Attribute> tankCapacityAttribute = design->attributes()->itemByName("TankStand", "tankCapacity");
        if (checkReturn(tankCapacityAttribute))
            tankCapacity = tankCapacityAttribute->value();

        std::string tankHead = std::to_string(2000); //dimensions in cm
        Ptr<Attribute> tankHeadAttribute = design->attributes()->itemByName("TankStand", "tankHead");
        if (checkReturn(tankHeadAttribute))
            tankHead = tankHeadAttribute->value();

        std::string costPerMeter_Sq = "0";
        Ptr<Attribute> costPerMeter_SqAttribute = design->attributes()->itemByName("TankStand", "costPerMeter_Sq");
        if (checkReturn(costPerMeter_SqAttribute))
            costPerMeter_Sq = costPerMeter_SqAttribute->value();

        std::string costPerMeter_L = "0";
        Ptr<Attribute> costPerMeter_LAttribute = design->attributes()->itemByName("TankStand", "costPerMeter_L");
        if (checkReturn(costPerMeter_LAttribute))
            costPerMeter_L = costPerMeter_LAttribute->value();

        std::string costPerMeter_U = "0";
        Ptr<Attribute> costPerMeter_UAttribute = design->attributes()->itemByName("TankStand", "costPerMeter_U");
        if (checkReturn(costPerMeter_UAttribute))
            costPerMeter_U = costPerMeter_UAttribute->value();

        Ptr<Command> cmd = eventArgs->command();
        cmd->isExecutedWhenPreEmpted(false);
        Ptr<CommandInputs> inputs = cmd->commandInputs();
        if (!checkReturn(inputs))
            return;

        // Define the command dialog.
        _imgInput = inputs->addImageCommandInput("tankStandImage", "", "Resources/images/TankStand.png");
        if (!checkReturn(_imgInput))
            return;
        _imgInput->isFullWidth(true);
        _imgInput->isVisible(true);

        _structureMaterial = inputs->addDropDownCommandInput("material", "Structure Material", TextListDropDownStyle);
        if (!checkReturn(_structureMaterial))
            return;

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

        _fluidType = inputs->addDropDownCommandInput("fluid", "Fluid", TextListDropDownStyle);
        if (!checkReturn(_fluidType))
            return;

        if (fluidType == "Water")
        {
            _fluidType->listItems()->add("Water", true);
            _fluidType->listItems()->add("Oil", false);
        }
        else
        {
            _fluidType->listItems()->add("Water", false);
            _fluidType->listItems()->add("Oil", true);
        }

        _fluidDensity = inputs->addValueInput("fluidDensity", "Fluid Density", units, ValueInput::createByReal(std::stod(fluidDensity)));
        if (!checkReturn(_fluidDensity))
            return;

        _tankCapacity = inputs->addValueInput("tankCapacity", "Tank Capacity", units, ValueInput::createByReal(std::stod(tankCapacity)));
        if (!checkReturn(_tankCapacity))
            return;

        _tankHead = inputs->addValueInput("tankHead", "Tank Head", units, ValueInput::createByReal(std::stod(tankHead)));
        if (!checkReturn(_tankHead))
            return;

        _costPerMeter_Sq = inputs->addValueInput("costPerMeter", "SqBeam Cost/Meter", units, ValueInput::createByReal(std::stod(costPerMeter_Sq)));
        if (!checkReturn(_costPerMeter_Sq))
            return;

        _costPerMeter_L = inputs->addValueInput("costPerMeter", "LBeam Cost/Meter", units, ValueInput::createByReal(std::stod(costPerMeter_L)));
        if (!checkReturn(_costPerMeter_L))
            return;

        _costPerMeter_U = inputs->addValueInput("costPerMeter", "UBeam Cost/Meter", units, ValueInput::createByReal(std::stod(costPerMeter_U)));
        if (!checkReturn(_costPerMeter_U))
            return;

        _errMessage = inputs->addTextBoxCommandInput("errMessage", "", "", 2, true);
        if (!checkReturn(_errMessage))
            return;
        _errMessage->isFullWidth(true);

        // Connect to the command related events.
        Ptr<InputChangedEvent> inputChangedEvent = cmd->inputChanged();
        if (!inputChangedEvent)
            return;
        bool isOk = inputChangedEvent->add(&_standCommandInputChanged);
        if (!isOk)
            return;

        Ptr<ValidateInputsEvent> validateInputsEvent = cmd->validateInputs();
        if (!validateInputsEvent)
            return;
        isOk = validateInputsEvent->add(&_standCommandValidateInputs);
        if (!isOk)
            return;

        Ptr<CommandEvent> executeEvent = cmd->execute();
        if (!executeEvent)
            return;
        isOk = executeEvent->add(&_standCommandExecute);
        if (!isOk)
            return;

        Ptr<CommandEvent> destroyEvent = cmd->destroy();
        if (!destroyEvent)
            return;

        isOk = destroyEvent->add(&_standCommandDestroy);
        if (!isOk)
            return;
    }
} _standCommandCreated;

#endif // !EVENTS_HANDLER_H
