#pragma once
#ifndef EVENTS_HANDLER_H
#define EVENTS_HANDLER_H

#include "Common.h"
#include "drawStand.h"

bool getCommandInputValue(Ptr<CommandInput> commandInput, 
std::string unitType, double* value)
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

    if (unitsMgr->isValidExpression(valCommandInput->expression(), 
    unitType))
    {
        *value = unitsMgr->evaluateExpression(valCommandInput->expression(), 
        unitType);
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
class StandCommandExecuteEventHandler :
 public adsk::core::CommandEventHandler
{
public:
    void notify(const Ptr<CommandEventArgs>& eventArgs) override
    {
        Ptr<Documents> documents = app->documents();
        if (!documents)
            return;

        Ptr<Document> doc = documents->add(
            DocumentTypes::FusionDesignDocumentType);
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
        attribs->add("TankStand", "tankHead", 
        std::to_string(_tankHead->value()));
        attribs->add("TankStand", "tankCapacity", 
        std::to_string(_tankCapacity->value()));
        attribs->add("TankStand", "costPerMeter_Sq", 
        std::to_string(_costPerMeter_Sq->value()));
        attribs->add("TankStand", "costPerMeter_L", 
        std::to_string(_costPerMeter_L->value()));

        // Get the current values.
        double tankHead = _tankHead->value();
        double tankCapacity = _tankCapacity->value();
        double costPerMeter_Sq = _costPerMeter_Sq->value();
        double costPerMeter_L = _costPerMeter_L->value();

        // Create the gear.
        drawTankStand(design, tankHead, tankCapacity, costPerMeter_Sq,
         costPerMeter_L);
    }
} _standCommandExecute;

class StandCommandInputChangedHandler : 
public adsk::core::InputChangedEventHandler
{
public:
    void notify(const Ptr<InputChangedEventArgs>& eventArgs) override
    {
        Ptr<CommandInput> changedInput = eventArgs->input();

            _tankCapacity->value(_tankCapacity->value());
            _tankCapacity->unitType(units);
            _tankHead->value(_tankHead->value());
            _tankHead->unitType(units);
            _costPerMeter_L->value(_costPerMeter_L->value());
            _costPerMeter_Sq->value(_costPerMeter_Sq->value());
    }
} _standCommandInputChanged;

class GearCommandValidateInputsEventHandler : 
public adsk::core::ValidateInputsEventHandler
{
public:
    void notify(const Ptr<ValidateInputsEventArgs>& eventArgs) override
    {
        displayErrorMessage("");
        _errMessage->text("");
    }
} _standCommandValidateInputs;

class TankStandCommandDestroyEventHandler : 
public adsk::core::CommandEventHandler
{
public:
    void notify(const Ptr<CommandEventArgs>& eventArgs) override
    {
        // Terminate the script since the command has finished.
        adsk::terminate();
    }
} _standCommandDestroy;

class TankStandCommandCreatedEventHandler : 
public adsk::core::CommandCreatedEventHandler
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

        std::string tankCapacity = std::to_string(250000);;
        Ptr<Attribute> tankCapacityAttribute = design->attributes()->itemByName(
            "TankStand", "tankCapacity");
        if (checkReturn(tankCapacityAttribute))
            tankCapacity = tankCapacityAttribute->value();

        std::string tankHead = std::to_string(609.25); //dimensions in cm
        Ptr<Attribute> tankHeadAttribute = design->attributes()->itemByName(
            "TankStand", "tankHead");
        if (checkReturn(tankHeadAttribute))
            tankHead = tankHeadAttribute->value();

        std::string costPerMeter_Sq = "0";
        Ptr<Attribute> costPerMeter_SqAttribute = design->attributes()->itemByName(
            "TankStand", "costPerMeter_Sq");
        if (checkReturn(costPerMeter_SqAttribute))
            costPerMeter_Sq = costPerMeter_SqAttribute->value();

        std::string costPerMeter_L = "0";
        Ptr<Attribute> costPerMeter_LAttribute = design->attributes()->itemByName(
            "TankStand", "costPerMeter_L");
        if (checkReturn(costPerMeter_LAttribute))
            costPerMeter_L = costPerMeter_LAttribute->value();

        Ptr<Command> cmd = eventArgs->command();
        cmd->isExecutedWhenPreEmpted(false);
        Ptr<CommandInputs> inputs = cmd->commandInputs();
        if (!checkReturn(inputs))
            return;

        // Define the command dialog.
        _imgInput = inputs->addImageCommandInput("tankStandImage", "",
         "Resources/images/TankStand.png");
        if (!checkReturn(_imgInput))
            return;
        _imgInput->isFullWidth(true);
        _imgInput->isVisible(true);

        _tankCapacity = inputs->addValueInput("tankCapacity", "Tank Capacity",
         units, ValueInput::createByReal(std::stod(tankCapacity)));
        if (!checkReturn(_tankCapacity))
            return;

        _tankHead = inputs->addValueInput("tankHead", "Tank Head", units,
         ValueInput::createByReal(std::stod(tankHead)));
        if (!checkReturn(_tankHead))
            return;

        _costPerMeter_Sq = inputs->addValueInput("costPerMeter", 
        "SqBeam Cost/Meter", " ", ValueInput::createByReal(std::stod(costPerMeter_Sq)));
        if (!checkReturn(_costPerMeter_Sq))
            return;

        _costPerMeter_L = inputs->addValueInput("costPerMeter",
         "LBeam Cost/Meter", " ", ValueInput::createByReal(std::stod(costPerMeter_L)));
        if (!checkReturn(_costPerMeter_L))
            return;

        _errMessage = inputs->addTextBoxCommandInput("errMessage",
         "", "", 2, true);
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
