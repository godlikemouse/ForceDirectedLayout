ForceDirectedLayout
===================

A simple C++ based force directed layout system for performing command line layouts of nodes and edges.  Supports JSON and GraphML supported input and output.  Supports additional attributes and parameters in both JSON and GraphML.

## Building

`autoreconf --install && ./configure && make`

## Quick Start

Read in JSON file, output to GraphML file.

`./fdl --in-type=JSON --in=data/layout.json --out-type=GraphML --out=output.xml`

Read in GraphML file, output JSON to stdout.

`./fdl --in-type=GraphML --in=data/layout.xml --out-type=JSON`

## Data Formats

ForceDirectedLayout currently supports JSON and GraphML.  Example data input files are available under the [data](https://github.com/godlikemouse/ForceDirectedLayout/tree/master/data) directory.

* Required node attributes are: id
* Required edge attributes are: id, source and target
* Any additional attributes get passed directly through to the output

## Community

Keep track of development and community news.

* Follow [@Collaboradev on Twitter](https://twitter.com/collaboradev).

## License

ForceDirectedLayout is released under [GPL, version 2.0](http://www.gnu.org/licenses/gpl-2.0.html)
