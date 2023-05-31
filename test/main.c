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
  This is the main.c file for the ctest binary

==============================================================================*/
#include <stdio.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "bitfield.h"
#include "bitfield_test.h"

int main() {

    // Initialize the module(s)
    BITFIELD_fnInit();

    // Run the application
    BITFIELD_fnStart();

    const struct CMUnitTest tests[] = {
      cmocka_unit_test(bitfield_fnTestBaseline),
      cmocka_unit_test(bitfield_fnTestCreatePacket),
      cmocka_unit_test(bitfield_fnTestValidatePacket),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}

