#ifndef TESTTARGET_H_
#define TESTTARGET_H_
#include "InteractiveDimension.h"
namespace GautierAllegroAPI {
	class TestTarget {
		public:
			TestTarget();
			virtual ~TestTarget();
			static void ImplementationTarget(InteractiveDimension* target);
			static void OutputTestText(const char* text);
		private:
			static bool _TestTextOn;
	};
} /* namespace GautierAllegroAPI */
#endif /* TESTTARGET_H_ */
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