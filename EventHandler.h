#pragma once
#ifndef EVENTS_HANDLER_H
#define EVENTS_HANDLER_H

#include "Common.h"
#include "drawStand.h"

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

        // Get the current values.
        double tankHead = _tankHead->value();
        double tankCapacity = _tankCapacity->value();

        // Create the gear.
       drawTankStand(design, tankHead, tankCapacity);
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

            // Set each one to it's current value because otherwised if the user 
            // has edited it, the value won't update in the dialog because 
            // apparently it remembers the units when the value was edited.
            // Setting the value using the API resets this.
            _tankCapacity->value(_tankCapacity->value());
            _tankCapacity->unitType(units);
            _tankHead->value(_tankHead->value());
            _tankHead->unitType(units);
        }

        // Update the pitch diameter value.
        if (_structureMaterial->selectedItem()->name() == "Aluminium")
        {
        }
        else if (_structureMaterial->selectedItem()->name() == "Steel")
        {
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

        std::string defaultUnits = design->unitsManager()->defaultLengthUnits();

        // Determine whether to use inches or millimeters as the intial default.
        if (defaultUnits == "in" || defaultUnits == "ft")
        {
            units = "in";
        }
        else
        {
            units = "m";
        }

        // Define the default values and get the previous values from the attributes.
        std::string material;
        if (units == "in")
        {
            material = "Aluminium";
        }
        else
        {
            material = "Steel";
        }

        Ptr<Attribute> structureMaterialAttribute = design->attributes()->itemByName("TankStand", "material");
        if (checkReturn(structureMaterialAttribute))
            material = structureMaterialAttribute->value();
        if (material == "Aluminium")
        {
            units = "in";
        }
        else
        {
            units = "m";
        }

        std::string tankCapacity = "0";
        Ptr<Attribute> tankCapacityAttribute = design->attributes()->itemByName("TankStand", "tankCapacity");
        if (checkReturn(tankCapacityAttribute))
            tankCapacity = tankCapacityAttribute->value();

        std::string tankHead = std::to_string(2000); //dimensions in cm
        Ptr<Attribute> tankHeadAttribute = design->attributes()->itemByName("TankStand", "tankHead");
        if (checkReturn(tankHeadAttribute))
            tankHead = tankHeadAttribute->value();

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

        _tankCapacity = inputs->addValueInput("tankCapacity", "Tank Capacity", units, ValueInput::createByReal(std::stod(tankCapacity)));
        if (!checkReturn(_tankCapacity))
            return;

        _tankHead = inputs->addValueInput("tankHead", "Tank Head", units, ValueInput::createByReal(std::stod(tankHead)));
        if (!checkReturn(_tankHead))
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
