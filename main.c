/*=============================================================================
  Project/Company-Name
  (c) 2023 Project/Company-Name

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

@brief main.c
  This is the main.c file for the debuggable binary

==============================================================================*/
#include <stdio.h>
#include <sys/types.h>
#include "bitfield.h"

int main() {
    // initialize the module(s)
    BITFIELD_fnInit();

    // run the application
    BITFIELD_fnStart();

    printf("bitfield binary ran!\n");
    return 0;
}
