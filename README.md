
[![Arduino CI](https://github.com/RobTillaart/ParallelPrinter/workflows/Arduino%20CI/badge.svg)](https://github.com/marketplace/actions/arduino_ci)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/RobTillaart/ParallelPrinter/blob/master/LICENSE)
[![GitHub release](https://img.shields.io/github/release/RobTillaart/ParallelPrinter.svg?maxAge=3600)](https://github.com/RobTillaart/ParallelPrinter/releases)

# ParallelPrinter

Arduino library that implements a parallel printer - uses print interface

## Description

This **experimental** library defines a simple parallel printer object.

It implements the **Print interface** to be able to print all datatypes using **print()** and **println()**
The printer writes every byte over 8 parallel lines including a **STROBE** (clock) pulse,
while waiting for the connected printer not to be **BUSY** or **OUT OF PAPER**.

This library is meant to be a starting point to make a "printer driver" for a 
specific parallel printer. These can often be bought in 2nd hand stores or so.

Have fun!

**Note:** This lib is a extended redo of the ParPrinter class.

## Interface

### Constructor

- **ParallelPrinter()** uses default pins (10, 2, 12, \[3,4,5,6,7,8,9,10\])
- **ParallelPrinter(strobe, busy, oop, arr)** define 3 control pins + 8 datapins (= arr)
- **begin(linelength, pagelength)** set line and page length parameters

### Print interface
- **write(c)** send a single byte to printer, implements Print interface. Therefor all **print()** and **println()** functions will work.
- **formfeed()** to eject current page.

### Config

- **getLineLength()** idem
- **getPageLength()** idem
- **getLineNumber()** idem
- **getPageNumber()** idem
- **getPosition()**   idem
- **setTabSize(n)** tabs are replaced by spaces. n = 2,4,6,8
- **getTabSize()** returns tabSize set
- **setLineFeed(n)** n = 1,2,3  1 = default
- **getLineFeed()** returns lineFeed set
- **printLineNr(b)** true, false


### Expert mode 

- **isOutOfPaper()** to check paper tray before printing starts.
- **setStrobeDelay(n = 2000)** make the strobe pulse shorter == faster printing
allows tuning of performance. Default value = 2000. Time in microseconds.
- **getStrobeDelay()** returns value set.


## See also

https://en.wikipedia.org/wiki/Parallel_port#Centronics

## Operation

See examples
