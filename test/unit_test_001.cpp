//
//    FILE: unit_test_001.cpp
//  AUTHOR: Rob Tillaart
//    DATE: 2021-01-04
// PURPOSE: unit tests for the ParallelPrinter library
//          https://github.com/RobTillaart/ParallelPrinter
//          https://github.com/Arduino-CI/arduino_ci/blob/master/REFERENCE.md
//

// supported assertions
// ----------------------------
// assertEqual(expected, actual);               // a == b
// assertNotEqual(unwanted, actual);            // a != b
// assertComparativeEquivalent(expected, actual);    // abs(a - b) == 0 or (!(a > b) && !(a < b))
// assertComparativeNotEquivalent(unwanted, actual); // abs(a - b) > 0  or ((a > b) || (a < b))
// assertLess(upperBound, actual);              // a < b
// assertMore(lowerBound, actual);              // a > b
// assertLessOrEqual(upperBound, actual);       // a <= b
// assertMoreOrEqual(lowerBound, actual);       // a >= b
// assertTrue(actual);
// assertFalse(actual);
// assertNull(actual);

// // special cases for floats
// assertEqualFloat(expected, actual, epsilon);    // fabs(a - b) <= epsilon
// assertNotEqualFloat(unwanted, actual, epsilon); // fabs(a - b) >= epsilon
// assertInfinity(actual);                         // isinf(a)
// assertNotInfinity(actual);                      // !isinf(a)
// assertNAN(arg);                                 // isnan(a)
// assertNotNAN(arg);                              // !isnan(a)

#include <ArduinoUnitTests.h>

#define assertEqualFloat(arg1, arg2, arg3)  assertOp("assertEqualFloat", "expected", fabs(arg1 - arg2), compareLessOrEqual, "<=", "actual", arg3)
// #define assertEqualINF(arg)  assertOp("assertEqualINF", "expected", INFINITY, compareEqual, "==", "actual", arg)
// #define assertEqualNAN(arg)  assertOp("assertEqualNAN", "expected", true, compareEqual, "==", "actual", isnan(arg))


#include "Arduino.h"
#include "ParallelPrinter.h"



unittest_setup()
{
}

unittest_teardown()
{
}

/*
unittest(test_new_operator)
{
  assertEqualINF(exp(800));
  assertEqualINF(0.0/0.0);
  assertEqualINF(42);
  
  assertEqualNAN(INFINITY - INFINITY);
  assertEqualNAN(0.0/0.0);
  assertEqualNAN(42);
}
*/

// minimal

unittest(test_constructor_basic)
{
  fprintf(stderr, "VERSION: %s\n", PARALLELPRINTER_VERSION);

  ParallelPrinter PP;
  
  PP.begin();
  assertEqual(80, PP.getLineLength());
  assertEqual(60, PP.getPageLength());
  assertEqual(0, PP.getLineNumber());
  assertEqual(0, PP.getPageNumber());
  assertEqual(0, PP.getPosition());
  assertEqual(2, PP.getTabSize());
  assertEqual(1, PP.getLineFeed());

  PP.formfeed();
  PP.println("This is a test");
  PP.print("Hello World");
  assertEqual(0, PP.getLineNumber());
  assertEqual(0, PP.getPageNumber());
  assertEqual(0, PP.getPosition());
}


unittest(test_tabs_linefeed)
{
  ParallelPrinter PP;

  fprintf(stderr, "0\t");
  PP.setTabSize(0);
  assertEqual(2, PP.getTabSize());  // minimum tab size
    
  for (int tab = 2; tab < 10; tab +=2 )
  {
    fprintf(stderr, "%d\t", tab);
    PP.setTabSize(tab);
    assertEqual(tab, PP.getTabSize());
  }


  fprintf(stderr, "0\t");
  PP.setLineFeed(0);
  assertEqual(1, PP.getLineFeed());  // minimum LF size
  
  for (int LF = 0; LF < 4; LF +=2 )
  {
    fprintf(stderr, "%d\t", LF);
    PP.setLineFeed(LF);
    assertEqual(LF, PP.getLineFeed());
  }
}


unittest(test_OutOfPaper)
{
  GodmodeState* state = GODMODE();
  state->reset();

  ParallelPrinter PP;

  state->digitalPin[12] = 0;
  assertFalse(PP.isOutOfPaper());

  state->digitalPin[12] = 1;
  assertTrue(PP.isOutOfPaper());
}

unittest_main()

// --------
