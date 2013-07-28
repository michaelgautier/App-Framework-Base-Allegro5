#ifndef ATTRIBUTES_VISUAL_DIMENSION_H_
#define ATTRIBUTES_VISUAL_DIMENSION_H_
#include <string>
namespace GautierAllegroAPI {
	using namespace std;
	struct ATTRIBUTES_VISUAL_DIMENSION {
		int Preferred_Width;
		int Preferred_Height;
		int Preferred_X;
		int Preferred_Y;
		int Preferred_Z;
		int Preferred_Rotation_Angle;
		bool Prefers_Fullscreen;
		bool Prefers_Unadorned_Frame;
		string Preferred_Frame_Title_Text;
		string Preferred_Color_Name_Text;
		bool Prefers_Resizable_Frame;
		bool Prefers_Screensaver_Paused;
		int Preferred_Background_Color_R;
		int Preferred_Background_Color_G;
		int Preferred_Background_Color_B;
		bool Prefers_Abilities_Keyboard;
		bool Prefers_Abilities_Mouse;
	};
}
#endif /* ATTRIBUTES_VISUAL_DIMENSION_H_ */
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