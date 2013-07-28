#include "TestTarget.h"
#include <iostream>
namespace GautierAllegroAPI {
	bool TestTarget::_TestTextOn = false;
	TestTarget::TestTarget() {
		// TODO Auto-generated constructor stub
	}
	TestTarget::~TestTarget() {
		// TODO Auto-generated destructor stub
	}
	void TestTarget::ImplementationTarget(InteractiveDimension* target) {
		//TestTarget::OutputTestText("target called\n");
	}
	void TestTarget::OutputTestText(const char* text) {
		if (_TestTextOn) {
			cout << text;
		}
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