# ParallelPrinter

Arduino library that implements a parallel printer - uses print interface

## Description

This **experimental** library defines a simple parallel printer object.

It implements the **Print interface** to be able to print all datatypes.
It writes every byte over 8 parallel lines including a **STROBE** (clock) pulse,
while waiting for the connected printer to not be **BUSY** or **OUT OF PAPER**.

This library is meant to be a starting point to make a "printer driver" for a 
specific parallel printer. These can often be bought in 2nd hand stores or so.

Have fun!

Note: _This lib is a extended redo of the ParPrinter class._

## Interface

* **ParallelPrinter(strobe, busy, oop, arr)** define 3 control pins + 8 datapins (= arr)

* **begin(linelength, pagelength)** set page parameters
* **write(c)** send a single byte to printer, implements Print interface.

* **setTabSize(n)** tabs are replaced by spaces. n = 2,4,6,8
* **setLineFeed(n)** n = 1,2,3  1 = default
* **printLineNr(b)** true, false
* **formfeed()** to eject current page
* **isOutOfPaper()** check paper tray before printing starts

* **setStrobeDelay(n)** make the strobe pulse shorter == faster printing
allows tuning of performance. Typical value = 2000. Time in micros.
use with care.


## See also

https://en.wikipedia.org/wiki/Parallel_port#Centronics

## Operation

See examples
