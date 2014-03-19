ForceDirectedLayout
===================

A simple C++ based force directed layout system for performing command line layouts of nodes and edges.  Supports JSON and GraphML supported input and output.  Supports additional attributes and parameters in both JSON and GraphML.

## Building

./configure && make

## Quick Start

Read in JSON file, output to GraphML file.

`./fdl --in-type=JSON --in=data/layout.json --out-type=GraphML --out=output.xml`

Read in GraphML file, output JSON to stdout.

`./fdl --in-type=GraphML --in=data/layout.xml --out-type=JSON`
