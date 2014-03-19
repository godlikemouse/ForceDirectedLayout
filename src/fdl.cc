/*
 * Copyright 2014 Jason Graves (GodLikeMouse/Collaboradev)
 * http://www.collaboradev.com
 *
 * This file is part of ForceDirectedLayout.
 *
 * ForceDirectedLayout is free software: you can redistribute it
 * and/or modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation, either
 * version 3 of the License, or (at your option) any later version.
 *
 * ForceDirectedLayout is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ForceDirectedLayout. If not, see http://www.gnu.org/licenses/.
 */

#include "fdl.h"

int main(int argc, char ** argv){

	srand(time(NULL));

	CommandSwitches switches;
	std::vector<Node> nodes;
	std::vector<Edge> edges;

	//parse command line arguments
	if(!switches.parse(argc, argv))
		return 0;

	if(switches.show_help){
		show_usage();
		return 0;
	}

	//sanity check
	if(!switches.sane()){
		cerr << switches.error() << endl;
		return 1;
	}

	//read input file
	FileHandler read_handler(switches.in_file, switches.in_type, switches);
	if(!read_handler.read(nodes, edges)){
		cerr << read_handler.error() << endl;
		return 1;
	}

	Layout layout(&nodes, &edges, switches);

	//verify node to link mapping
	if(!layout.error().empty()){
		cerr << layout.error() << endl;
		return 1;
	}

	layout.layout();

	//write output file
	FileHandler write_handler(switches.out_file, switches.out_type, switches);
	if(!write_handler.write(nodes, edges)){
		cerr << write_handler.error() << endl;
		return 1;
	}

	return 0;
}
