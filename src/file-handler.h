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

#ifndef __FILE_HANDLER
#define __FILE_HANDLER

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>

#include "ext/json/json.h"
#include "ext/xml/rapidxml.h"
#include "command-switches.h"
#include "node.h"
#include "edge.h"


using namespace std;
using namespace rapidxml;

class FileHandler {

	public:
	FileHandler(string, string, CommandSwitches&);

	bool read(vector<Node>&, vector<Edge>&);
	bool write(vector<Node>&, vector<Edge>&);
	string& error();

	private:
	string type_;
	string filename_;
	string error_;
	CommandSwitches switches_;

	bool parse_json(vector<Node>&, vector<Edge>&);
	bool write_json(vector<Node>&, vector<Edge>&);
	bool parse_graphml(vector<Node>&, vector<Edge>&);
	bool write_graphml(vector<Node>&, vector<Edge>&);

};

#endif
