# ArduinoSimpleScopes

## About

The purpose of this code is to allow separation of functionality via scopes while at the same time also allowing to run general code.
An example of usage for this code could be a user interface where each screen runs in one scope.

## Overview

The constructor takes as input an array of scope(s). Each scope defines init, loop and clean function pointers.
Data can be stored for use between loops via a void pointer that is pased to the loop function. this pointer can then reference a structure
for this scope. Scopes can be switched via a call to switchScope from our SimpleScopes object or by returning the scope number (position in the array)
of the scope we want to switch to. When switching scopes we call the clean function for the scope that was active and afterwards call the init function for the scope that we are moving to.

## How to use

Clone this repository into your Arduino/libraries directory

## Example

See test.cpp file