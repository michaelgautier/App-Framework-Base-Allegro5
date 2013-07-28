#ifndef INTERACTIVEDIMENSION_H_
#define INTERACTIVEDIMENSION_H_
#include "ATTRIBUTES_VISUAL_DIMENSION.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <math.h>
namespace GautierAllegroAPI {
	class InteractiveDimension {
		public:
			InteractiveDimension();
			virtual ~InteractiveDimension();
			typedef void (*InteractiveDimensionCallback)(InteractiveDimension*);
			typedef void (*InteractiveDimensionParameterlessCallback)();
			static bool StartDisplayRuntime();
			static bool OperateDisplay(InteractiveDimension* interactiveDimensionTarget);
			void Configure(ATTRIBUTES_VISUAL_DIMENSION dimensionAttributes);
			void Begin();
			void End();
			void EndEvents();
			void RefreshDisplay(string colorName);
			void RegisterMainCallback(InteractiveDimensionCallback &callbackWindowMainFunction);
			void RegisterCreateSubWindowCallback(InteractiveDimensionParameterlessCallback &callbackCreateWindowFunction);
			static bool ProcessDimensions();
			static InteractiveDimension* const CreateNewInteractiveDimension();
		private:
			static bool _IsAllegroInstalled;
			/*Visually, more than 16 windows would be rather cluttered*/
			static const int _OtherInteractiveDimensionsSize = 16;
			static InteractiveDimension* _OtherInteractiveDimensions[_OtherInteractiveDimensionsSize];
			int _Preferred_Width;
			int _Preferred_Height;
			int _Preferred_X;
			int _Preferred_Y;
			int _Preferred_Z;
			int _Preferred_Rotation_Angle;
			int _Preferred_Background_Color_R;
			int _Preferred_Background_Color_G;
			int _Preferred_Background_Color_B;
			string _Preferred_Color_Name_Text;
			string _Preferred_Frame_Title_Text;
			bool _Prefers_Fullscreen;
			bool _Prefers_Unadorned_Frame;
			bool _Prefers_Resizable_Frame;
			bool _Prefers_Screensaver_Paused;
			bool _Prefers_Abilities_Keyboard;
			bool _Prefers_Abilities_Mouse;
			bool _OpConfigured;
			bool _OpBegan;
			bool _OpEnded;
			InteractiveDimensionCallback _CallbackWindowMain;
			InteractiveDimensionParameterlessCallback _CallbackSubWindowNew;
			ALLEGRO_DISPLAY* _AL_Display;
			ALLEGRO_EVENT_QUEUE* _AL_EventQueue;
			ALLEGRO_EVENT_SOURCE* _AL_Default_EventQueue_Event_Source;
			ALLEGRO_EVENT_SOURCE* _AL_Keyboard_Event_Source;
			ALLEGRO_EVENT_SOURCE* _AL_Mouse_Event_Source;
			ALLEGRO_EVENT_SOURCE* _AL_Display_Event_Source;
			void RunMainCallback();
	};
} /* namespace GautierAllegroAPI */
#endif /* INTERACTIVEDIMENSION_H_ */
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