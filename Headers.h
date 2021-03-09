#pragma once

#include <Core/CoreAll.h>
#include <Fusion/FusionAll.h>
#include <Core/Utils.h>
#include <Core/Application/Application.h>
#include <Core/Application/Product.h>
#include <Core/Application/ValueInput.h>
#include <Core/Application/UnitsManager.h>
#include <Core/Application/ObjectCollection.h>
#include <Core/Geometry/Point3D.h>
#include <Core/Geometry/Matrix3D.h>
#include <Core/Geometry/Surface.h>
#include <Core/Geometry/Curve3D.h>
#include <Core/Geometry/Line3D.h>
#include <Core/UserInterface/UserInterface.h>
#include <Core/UserInterface/CommandCreatedEventHandler.h>
#include <Core/UserInterface/CommandCreatedEvent.h>
#include <Core/UserInterface/CommandCreatedEventArgs.h>
#include <Core/UserInterface/CommandEvent.h>
#include <Core/UserInterface/CommandEventArgs.h>
#include <Core/UserInterface/CommandEventHandler.h>
#include <Core/UserInterface/ValidateInputsEventHandler.h>
#include <Core/UserInterface/ValidateInputsEvent.h>
#include <Core/UserInterface/ValidateInputsEventArgs.h>
#include <Core/UserInterface/InputChangedEventHandler.h>
#include <Core/UserInterface/InputChangedEvent.h>
#include <Core/UserInterface/InputChangedEventArgs.h>
#include <Core/UserInterface/Command.h>
#include <Core/UserInterface/CommandDefinition.h>
#include <Core/UserInterface/CommandDefinitions.h>
#include <Core/UserInterface/CommandInputs.h>
#include <Core/UserInterface/ValueCommandInput.h>
#include <Core/UserInterface/StringValueCommandInput.h>
#include <Core/UserInterface/DropDownCommandInput.h>
#include <Core/UserInterface/ListItems.h>
#include <Core/UserInterface/ListItem.h>
#include <Core/UserInterface/ImageCommandInput.h>
#include <Core/UserInterface/TextBoxCommandInput.h>
#include <Core/UserInterface/ToolbarPanelList.h>
#include <Core/UserInterface/ToolbarPanels.h>
#include <Core/UserInterface/ToolbarPanel.h>
#include <Core/UserInterface/ToolbarControls.h>
#include <Core/UserInterface/ToolbarControl.h>
#include <Core/UserInterface/CommandControl.h>
#include <Core/UserInterface/Workspaces.h>
#include <Core/UserInterface/Workspace.h>
#include <Core/Application/Attributes.h>
#include <Core/Application/Attribute.h>
#include <Fusion/Fusion/Design.h>
#include <Fusion/Components/Component.h>
#include <Fusion/Components/Occurrences.h>
#include <Fusion/Components/Occurrence.h>
#include <Fusion/BRep/BRepFaces.h>
#include <Fusion/BRep/BRepFace.h>
#include <Fusion/BRep/BRepEdges.h>
#include <Fusion/BRep/BRepEdge.h>
#include <Fusion/BRep/BRepBody.h>
#include <Fusion/Construction/ConstructionPlane.h>
#include <Fusion/Sketch/Sketches.h>
#include <Fusion/Sketch/Sketch.h>
#include <Fusion/Sketch/SketchCurves.h>
#include <Fusion/Sketch/SketchLines.h>
#include <Fusion/Sketch/SketchLine.h>
#include <Fusion/Sketch/SketchArcs.h>
#include <Fusion/Sketch/SketchArc.h>
#include <Fusion/Sketch/SketchPoint.h>
#include <Fusion/Sketch/SketchFittedSplines.h>
#include <Fusion/Sketch/SketchFittedSpline.h>
#include <Fusion/Sketch/SketchCircles.h>
#include <Fusion/Sketch/SketchCircle.h>
#include <Fusion/Sketch/GeometricConstraints.h>
#include <Fusion/Sketch/TangentConstraint.h>
#include <Fusion/Sketch/Profile.h>
#include <Fusion/Sketch/Profiles.h>
#include <Fusion/Sketch/ProfileLoops.h>
#include <Fusion/Features/Features.h>
#include <Fusion/Features/ExtrudeFeatures.h>
#include <Fusion/Features/ExtrudeFeatureInput.h>
#include <Fusion/Features/ExtrudeFeature.h>
#include <Fusion/Features/FilletFeatures.h>
#include <Fusion/Features/FilletFeatureInput.h>
#include <Fusion/Features/FilletFeature.h>
#include <Fusion/Features/CircularPatternFeatures.h>
#include <Fusion/Features/CircularPatternFeatureInput.h>
#include <Fusion/Features/CircularPatternFeature.h>
#include <Fusion/Fusion/Timeline.h>
#include <Fusion/Fusion/TimelineObject.h>
#include <Fusion/Fusion/TimelineGroups.h>
#include <Fusion/Fusion/TimelineGroup.h>

#include <sstream>
#define _USE_MATH_DEFINES
#include <math.h>
#include <memory>


#if defined(_WINDOWS) || defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#else
#include <dlfcn.h>
#endif

using namespace adsk::core;
using namespace adsk::fusion;
