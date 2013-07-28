#include "InteractiveDimension.h"
#include "ATTRIBUTES_VISUAL_DIMENSION.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include "TestTarget.h"
#include <math.h>
#include <string>

using namespace std;
using namespace GautierAllegroAPI;
static void CreateSubWindow() {
	InteractiveDimension* InteractiveDimensionObj = InteractiveDimension::CreateNewInteractiveDimension();
	if (InteractiveDimensionObj) {
		ATTRIBUTES_VISUAL_DIMENSION AttributesForVisual;
		AttributesForVisual.Prefers_Abilities_Keyboard = true;
		AttributesForVisual.Prefers_Abilities_Mouse = true;
		AttributesForVisual.Preferred_Frame_Title_Text = "Gautier Sub Window";
		AttributesForVisual.Preferred_Color_Name_Text = "orange";
		AttributesForVisual.Preferred_Width = 500;
		AttributesForVisual.Preferred_Height = 300;
		AttributesForVisual.Prefers_Resizable_Frame = true;
		InteractiveDimensionObj->Configure(AttributesForVisual);
		InteractiveDimension::InteractiveDimensionCallback Callback = TestTarget::ImplementationTarget;
		InteractiveDimensionObj->RegisterMainCallback(Callback);
		TestTarget::OutputTestText("Starting Window\n");
	}
}

static void CreateMainWindow() {
	InteractiveDimension* InteractiveDimensionObj = InteractiveDimension::CreateNewInteractiveDimension();
	if (InteractiveDimensionObj) {
		ATTRIBUTES_VISUAL_DIMENSION AttributesForVisual;
		AttributesForVisual.Prefers_Abilities_Keyboard = true;
		AttributesForVisual.Prefers_Abilities_Mouse = true;
		AttributesForVisual.Preferred_Frame_Title_Text = "Michael Gautier Main Allegro Window";
		AttributesForVisual.Preferred_Color_Name_Text = "blue";
		AttributesForVisual.Preferred_Width = 1024;
		AttributesForVisual.Preferred_Height = 768;
		AttributesForVisual.Prefers_Resizable_Frame = true;
		InteractiveDimensionObj->Configure(AttributesForVisual);
		InteractiveDimension::InteractiveDimensionParameterlessCallback Callback = CreateSubWindow;
		InteractiveDimensionObj->RegisterCreateSubWindowCallback(Callback);
	}
}

int main(int argc, char **argv) {
	bool DisplayRuntimeStarted = InteractiveDimension::StartDisplayRuntime();
	CreateMainWindow();
	if (DisplayRuntimeStarted) {
		bool DisplayRuntimeActive = true;
		while (DisplayRuntimeActive) {
			DisplayRuntimeActive = InteractiveDimension::ProcessDimensions();
		}
	}
	return 0;
}
/*
 Copyright 2013 Michael Gautier
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
	 You may obtain a copy of the License at
	 http://www.apache.org/licenses/LICENSE-2.0
	 Unless required by applicable law or agreed to in writing, software
	 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	 See the License for the specific language governing permissions and
	 limitations under the License.
	 */