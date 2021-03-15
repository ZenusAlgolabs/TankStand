#pragma once
#ifndef EVENTS_HANDLER_H
#define EVENTS_HANDLER_H

#include "Headers.h"
#include "Common.h"
#include "Beam.h"
#include "Inputs.h"

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

        Ptr<Design> design = product;
        if (!design)
            return;

        drawTankStand(design);

    }
} _standCommandExecute;

class StandCommandInputChangedHandler : public adsk::core::InputChangedEventHandler
{
public:
    void notify(const Ptr<InputChangedEventArgs>& eventArgs) override
    {
        Ptr<CommandInput> changedInput = eventArgs->input();

        if (changedInput->id() == "waterQuality")
        {
            if (_waterQuality->selectedItem()->name() == "Salt")
            {
            }
            else if (_waterQuality->selectedItem()->name() == "Fresh")
            {
            }
        }

        if (changedInput->id() == "structureMaterial")
        {
            if (_structureMaterial->selectedItem()->name() == "Aluminium")
            {
            }
            else if (_structureMaterial->selectedItem()->name() == "Steel")
            {
            }
        }

        _imgInput->isVisible(true);

        // Update the pitch diameter value.
        double diaPitch = 0;
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
        Ptr<Design> des = app->activeProduct();
        if (!checkReturn(des))
        {
            ui->messageBox("A Fusion design must be active when invoking this command.");
            return;
        }

        std::string defaultUnits = des->unitsManager()->defaultLengthUnits();

        // Define the default values and get the previous values from the attributes.
        std::string material= "Aluminium";
        Ptr<Attribute> materialAttrib = des->attributes()->itemByName("TankStand", "material");
        if (checkReturn(materialAttrib))
            material = materialAttrib->value();

        std::string quality;
        Ptr<Attribute> qualityAttrib = des->attributes()->itemByName("TankStand", "quality");
        if (checkReturn(qualityAttrib))
            quality = qualityAttrib->value();

        if (quality == "Fresh")
        {

        }
        else
        {

        }

        Ptr<Command> cmd = eventArgs->command();
        cmd->isExecutedWhenPreEmpted(false);
        Ptr<CommandInputs> inputs = cmd->commandInputs();
        if (!checkReturn(inputs))
            return;

        //Inputs pannel
        tankstand_Inputs_Panel(des, inputs);

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
