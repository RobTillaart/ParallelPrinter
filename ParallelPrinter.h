#pragma once
//
//    FILE: ParallelPrinter.h
//  AUTHOR: Rob Tillaart
// VERSION: 0.2.0
// PURPOSE: parallel printer class that implements the Print interface
//    DATE: 2013-09-30
//     URL: https://github.com/RobTillaart/ParallelPrinter
//

#include "Arduino.h"

#define PARALLELPRINTER_VERSION "0.2.0"

#define FORMFEED     12

class ParallelPrinter: public Print
{
public:
  ParallelPrinter();  //  assume fixed pins for now, need 11 pins in total!
  ParallelPrinter(uint8_t STROBE, uint8_t BUSY, uint8_t OOP, uint8_t * dataPins );

  void    begin(uint8_t lineLength = 80, uint8_t pageLength = 60);
  size_t  write(uint8_t c);

  //      n = 2,4,6,8
  void    setTabSize(uint8_t n);
  //      n = 1,2,3
  void    setLineFeed(uint8_t n)  { _lineFeed = constrain(n, 1, 3); };
  void    printLineNumber(bool b) { _printLineNumber = b; };
  void    formfeed()              { write(FORMFEED); };
  bool    isOutOfPaper()          { return digitalRead(_oopPin) == LOW; };

  //      n = typical 2000; use with care
  void    setStrobeDelay(uint16_t n) { _strobeDelay = n; };

private:
  // COMMUNICATION
  uint8_t _strobePin;   // inform printer new data on the line.
  uint8_t _busyPin;     // feedback from printer
  uint8_t _oopPin;      // Out of paper.
  uint8_t _pin[8];      // data pins

  void    processSingleChar(uint8_t c);
  void    sendByte(uint8_t c);

  // BEHAVIOR
  uint8_t _pos;
  uint8_t _lineLength;
  uint8_t _lineNr;
  uint8_t _pageLength;
  uint8_t _pageNr;
  uint8_t _tabSize;
  uint8_t _lineFeed;
  
  bool    _printLineNumber;
  uint16_t _strobeDelay;
};

// -- END OF FILE --
