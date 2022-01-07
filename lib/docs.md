# Evolutionary Salesman Module Documentation

This document explains how to properly use the `evo_salesman` Python module. This module wraps some functions from the `libevo` C library, making running an evolutionary simulation pretty straightforward.

This way we have the speed and low overhead from running the simulation in C and the flexibility and low complexity from dealing with the data in Python.

## Running the Simulation

TODO

## Getting the Data

When you run a simulation, as explained in the previous section, data containing generations and cities are generated. This data is not directly returned when the simulation is executed, instead you have to call `get_generations()` and `get_cities()`. These functions will get the corresponding data set by the `libevo` C library and return them as a Python data type.

TODO

## Clearing the Memory

By getting the data as explained in the previous section, you are copying the data allocated by the C library. After that, you can tell the C library to clear this data, freeing memory space.

TODO

## Utilities

The `evo_salesman` module also exports some useful functions that can help dealing with the data you get from the simulations.

TODO
