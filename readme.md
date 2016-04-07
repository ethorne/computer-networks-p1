# Project 1 - Network Finger
This is a simple warm-up project for a Computer Networks class. The assignment is to implement a client and server for passing finger data back and forth.

## usage
Compile with `make`. There is also a `make clean` that removes all the executables. Run fingerserver with `./fingerserver` and pass in an argument for a port to listen on. Run fingerclient with `./fingerclient` an arbitrary number of times, passing in one argument formatted like so:
  - `username@hostname:<port>`
  - `thornee1@cs1.seattleu.edu:10221`

## assumptions
The machine that the server is running on has the `finger` utility installed in `/usr/bin/finger`
