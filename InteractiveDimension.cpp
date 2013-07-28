#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <math.h>
#include <string>
#include "ATTRIBUTES_VISUAL_DIMENSION.h"
#include "InteractiveDimension.h"
#include "TestTarget.h"

namespace GautierAllegroAPI {
	bool InteractiveDimension::_IsAllegroInstalled = false;
	InteractiveDimension* InteractiveDimension::_OtherInteractiveDimensions[_OtherInteractiveDimensionsSize] = { };
	InteractiveDimension::InteractiveDimension() {
		_Preferred_Width = (640);
		_Preferred_Height = (480);
		_Preferred_X = (0);
		_Preferred_Y = (0);
		_Preferred_Z = (0);
		_Preferred_Rotation_Angle = (0);
		_Prefers_Fullscreen = (false);
		_Prefers_Unadorned_Frame = (false);
		_Preferred_Frame_Title_Text = ("frame");
		_Prefers_Resizable_Frame = (true);
		_Prefers_Screensaver_Paused = (false);
		_Preferred_Background_Color_R = (0);
		_Preferred_Background_Color_G = (0);
		_Preferred_Background_Color_B = (0);
		_Prefers_Abilities_Keyboard = (true);
		_Prefers_Abilities_Mouse = (true);
		_Preferred_Color_Name_Text = ("black");
		_AL_Default_EventQueue_Event_Source = 0;
		_AL_Keyboard_Event_Source = 0;
		_AL_Mouse_Event_Source = 0;
		_AL_Display_Event_Source = 0;
		_AL_EventQueue = 0;
		_AL_Display = 0;
		_CallbackWindowMain = 0;
		_CallbackSubWindowNew = 0;
		_OpConfigured = false;
		_OpEnded = false;
		_OpBegan = false;
	}

	InteractiveDimension::~InteractiveDimension() {
	}

	/*
	 * Public API
	 * ---------------------------------------------------------------------------
	 */
	bool InteractiveDimension::StartDisplayRuntime() {
		bool IsAllegroInstalled = _IsAllegroInstalled;
		if (!IsAllegroInstalled) {
			TestTarget::OutputTestText("starting\n");
			IsAllegroInstalled = al_is_system_installed();
			if (!IsAllegroInstalled) {
				IsAllegroInstalled = al_init();
			}
			_IsAllegroInstalled = IsAllegroInstalled;
		}
		return IsAllegroInstalled;
	}

	bool InteractiveDimension::OperateDisplay(InteractiveDimension* interactiveDimensionTarget) {
		bool ExplicitEnd = interactiveDimensionTarget->_OpEnded;
		if (!ExplicitEnd) {
			TestTarget::OutputTestText("operating display\n");
			interactiveDimensionTarget->Begin();
			/*
			 ALLEGRO_TIMEOUT EventWaitTimeOut;
			 al_init_timeout(&EventWaitTimeOut, 0.02);
			 */
			interactiveDimensionTarget->RefreshDisplay(
			                                           interactiveDimensionTarget->_Preferred_Color_Name_Text);
			ALLEGRO_EVENT ActiveEvent;
			/*
			 bool EventIsAvailable = al_wait_for_event_until(interactiveDimensionTarget->_AL_EventQueue, &ActiveEvent, &EventWaitTimeOut);
			 */
			bool EventIsAvailable = al_get_next_event(
			                                          interactiveDimensionTarget->_AL_EventQueue, &ActiveEvent);
			if (EventIsAvailable) {
				ALLEGRO_EVENT_TYPE ActiveEventType = ActiveEvent.type;
				bool EventIsValid = false;
				switch (ActiveEventType) {
					case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
						if (ActiveEvent.mouse.button == 1) {
							EventIsValid = true;
							if (interactiveDimensionTarget->_CallbackSubWindowNew) {
								interactiveDimensionTarget->_CallbackSubWindowNew();
								/*
								 * interactiveDimensionTarget->_CallbackSubWindowNew =
								 0;
								 */
							}
						}
						break;
					case ALLEGRO_EVENT_DISPLAY_CLOSE:
						interactiveDimensionTarget->End();
						ExplicitEnd = true;
						TestTarget::OutputTestText("A display closed captured\n");
						break;
					case ALLEGRO_EVENT_DISPLAY_RESIZE:
						al_acknowledge_resize(interactiveDimensionTarget->_AL_Display);
						EventIsValid = true;
						break;
					case ALLEGRO_EVENT_KEY_DOWN:
						if (ActiveEvent.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
							EventIsValid = true;
							TestTarget::OutputTestText("Escape key pressed down\n");
						}
						break;
					default:
						EventIsValid = false;
						break;
				}
				if (EventIsValid) {
					TestTarget::OutputTestText("event ran\n");
				}
			}
		}
		return (ExplicitEnd == false);
	}

	void InteractiveDimension::Configure(ATTRIBUTES_VISUAL_DIMENSION dimensionAttributes) {
		if (!_OpConfigured) {
			_Preferred_Width = dimensionAttributes.Preferred_Width;
			_Preferred_Height = dimensionAttributes.Preferred_Height;
			_Preferred_X = dimensionAttributes.Preferred_X;
			_Preferred_Y = dimensionAttributes.Preferred_Y;
			_Preferred_Z = dimensionAttributes.Preferred_Z;
			_Preferred_Rotation_Angle = dimensionAttributes.Preferred_Rotation_Angle;
			_Prefers_Fullscreen = dimensionAttributes.Prefers_Fullscreen;
			_Prefers_Unadorned_Frame = dimensionAttributes.Prefers_Unadorned_Frame;
			_Preferred_Frame_Title_Text = dimensionAttributes.Preferred_Frame_Title_Text;
			_Prefers_Resizable_Frame = dimensionAttributes.Prefers_Resizable_Frame;
			_Prefers_Screensaver_Paused = dimensionAttributes.Prefers_Screensaver_Paused;
			_Preferred_Background_Color_R = dimensionAttributes.Preferred_Background_Color_R;
			_Preferred_Background_Color_G = dimensionAttributes.Preferred_Background_Color_G;
			_Preferred_Background_Color_B = dimensionAttributes.Preferred_Background_Color_B;
			_Prefers_Abilities_Keyboard = dimensionAttributes.Prefers_Abilities_Keyboard;
			_Prefers_Abilities_Mouse = dimensionAttributes.Prefers_Abilities_Mouse;
			_Preferred_Color_Name_Text = dimensionAttributes.Preferred_Color_Name_Text;
			_OpConfigured = true;
		}
	}

	void InteractiveDimension::Begin() {
		if (!_OpBegan) {
			using namespace std;
			TestTarget::OutputTestText("Allegro Begin\n");
			al_init_primitives_addon();
			_AL_EventQueue = al_create_event_queue();
			/*
			 * al_init_user_event_source(_AL_Default_EventQueue_Event_Source);
			 */
			/*
			 * al_register_event_source
			 (_AL_EventQueue,_AL_Default_EventQueue_Event_Source);
			 */
			if (this->_Prefers_Abilities_Keyboard) {
				bool IsAllegroKeyboardInstalled = al_is_keyboard_installed();
				if (!IsAllegroKeyboardInstalled) {
					IsAllegroKeyboardInstalled = al_install_keyboard();
				}
				if (IsAllegroKeyboardInstalled) {
					_AL_Keyboard_Event_Source = al_get_keyboard_event_source();
					al_register_event_source(_AL_EventQueue,
					                         _AL_Keyboard_Event_Source);
				} else {
					TestTarget::OutputTestText("Allegro Keyboard Not Installed\n");
				}
			}
			if (this->_Prefers_Abilities_Mouse) {
				bool IsAllegroMouseInstalled = al_is_mouse_installed();
				if (!IsAllegroMouseInstalled) {
					IsAllegroMouseInstalled = al_install_mouse();
				}
				if (IsAllegroMouseInstalled) {
					_AL_Mouse_Event_Source = al_get_mouse_event_source();
					al_register_event_source(_AL_EventQueue,
					                         _AL_Mouse_Event_Source);
				}
			}
			if (this->_Prefers_Resizable_Frame) {
				al_set_new_display_flags(ALLEGRO_RESIZABLE | ALLEGRO_WINDOWED);
			}
			_AL_Display = al_create_display(this->_Preferred_Width,
			                                this->_Preferred_Height);
			_AL_Display_Event_Source = al_get_display_event_source(_AL_Display);
			al_register_event_source(_AL_EventQueue, _AL_Display_Event_Source);
			if (this->_Preferred_Frame_Title_Text.length() > 0) {
				const char* _Title_Text = _Preferred_Frame_Title_Text.data();
				al_set_window_title(_AL_Display, _Title_Text);
			}
			_OpBegan = true;
		}
	}

	void InteractiveDimension::End() {
		if (!_OpEnded) {
			TestTarget::OutputTestText("Ending Allegro\n");
			EndEvents();
			if (_AL_Display) {
				al_destroy_display(_AL_Display);
			}
			_OpEnded = true;
		}
	}

	void InteractiveDimension::EndEvents() {
		if (_AL_EventQueue) {

			al_flush_event_queue(_AL_EventQueue);
			ALLEGRO_EVENT_SOURCE* EventSources[] = { _AL_Display_Event_Source,
				_AL_Mouse_Event_Source, _AL_Keyboard_Event_Source,
				_AL_Default_EventQueue_Event_Source };
			for (int EventSourceIndex = 0; EventSourceIndex < 4;
			     EventSourceIndex++) {
				ALLEGRO_EVENT_SOURCE* EventSourceObj =
					EventSources[EventSourceIndex];
				if (EventSourceObj) {
					al_unregister_event_source(_AL_EventQueue, EventSourceObj);
				}
			}
		}
	}

	void InteractiveDimension::RefreshDisplay(string colorName) {
		size_t ColorNameSize = colorName.size();
		ALLEGRO_COLOR BackgroundColor = al_map_rgb(0, 0, 0);
		if (ColorNameSize > 0) {
			BackgroundColor = al_color_name(colorName.c_str());
		}
		al_set_target_backbuffer(_AL_Display);
		al_clear_to_color(BackgroundColor);
		al_flip_display();
	}

	void InteractiveDimension::RegisterMainCallback(InteractiveDimensionCallback &callbackWindowMainFunction) {
		_CallbackWindowMain = callbackWindowMainFunction;
	}

	void InteractiveDimension::RegisterCreateSubWindowCallback(InteractiveDimensionParameterlessCallback &callbackCreateWindowFunction)
	{
		_CallbackSubWindowNew = callbackCreateWindowFunction;
	}

	/*
	 * Private Implementation
	 *
	 --------------------------------------------------------------------------------
	 ----
	 */
	void InteractiveDimension::RunMainCallback() {
		if (_CallbackWindowMain) {
			TestTarget::OutputTestText("getting implementation\n");
			InteractiveDimensionCallback CallbackWindowMainFunc =
				*_CallbackWindowMain;
			TestTarget::OutputTestText("running implementation\n");
			if (CallbackWindowMainFunc) {
				try {
					CallbackWindowMainFunc(this);
					OperateDisplay(this);
				} catch (...) {
					TestTarget::OutputTestText("");
				}
			}
		}
	}

	bool InteractiveDimension::ProcessDimensions() {
		int EmptyDimensionCount = 0;
		bool DimensionsChecked = false;
		if (_OtherInteractiveDimensions) {
			for (int OtherDimensionsIndex = 0;
			     OtherDimensionsIndex < _OtherInteractiveDimensionsSize;
			     OtherDimensionsIndex++) {
				InteractiveDimension* InteractiveDimensionObj =
					_OtherInteractiveDimensions[OtherDimensionsIndex];
				if (!InteractiveDimensionObj) {
					EmptyDimensionCount++;
					continue;
				}
				if (_OtherInteractiveDimensions[OtherDimensionsIndex]) {
					bool DimensionConfigured =
						InteractiveDimensionObj->_OpConfigured;
					bool DimensionActive = InteractiveDimensionObj->_OpBegan;
					bool DimensionTerminated = (InteractiveDimensionObj->_OpEnded
					                            == true);
					bool DimensionToBeErased = false;

					bool DimensionRequiresFirstTimeStart = !(DimensionConfigured
					                                         && DimensionActive);
					if (DimensionRequiresFirstTimeStart) {
						InteractiveDimension::OperateDisplay(
						                                     InteractiveDimensionObj);
					}
					if (DimensionActive) {
						if (DimensionTerminated) {
							DimensionToBeErased = true;
						} else {
							InteractiveDimension::OperateDisplay(
							                                     InteractiveDimensionObj);
							InteractiveDimensionObj->RunMainCallback();
						}
					}
					if (DimensionToBeErased) {
						if (_OtherInteractiveDimensions) {
							_OtherInteractiveDimensions[OtherDimensionsIndex] = 0;
						}
						delete InteractiveDimensionObj;
						TestTarget::OutputTestText("Erased dimension\n");
					}
				}
			}
			DimensionsChecked = true;
		}
		bool DimensionsInUse = true;
		if (DimensionsChecked) {
			if (EmptyDimensionCount == _OtherInteractiveDimensionsSize) {
				DimensionsInUse = false;
			}
		}
		return DimensionsInUse;
	}

	InteractiveDimension* const InteractiveDimension::CreateNewInteractiveDimension() {
			InteractiveDimension* InteractiveDimensionSourceObj = 0;

			if (_OtherInteractiveDimensions) {
				for (int OtherDimensionsIndex = 0;
				     OtherDimensionsIndex < _OtherInteractiveDimensionsSize;
				     OtherDimensionsIndex++) {
					InteractiveDimension* InteractiveDimensionObj =
						_OtherInteractiveDimensions[OtherDimensionsIndex];
					if (!InteractiveDimensionObj) {
						_OtherInteractiveDimensions[OtherDimensionsIndex] =
							new InteractiveDimension;
						InteractiveDimensionSourceObj =
							_OtherInteractiveDimensions[OtherDimensionsIndex];
						break;
					}
				}
			}
			return InteractiveDimensionSourceObj;
		}
} /* namespace GautierAllegroAPI */
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
