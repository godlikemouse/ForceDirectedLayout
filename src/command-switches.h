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

#ifndef __COMMANDSWITCHES_H
#define __COMMANDSWITCHES_H

#include <sstream>

using namespace std;

class CommandSwitches {
	public:
	string in_file;
	string out_file;
	string in_type;
	string out_type;
	string mode;
	bool show_help;

	// Constructor
	CommandSwitches(){
		in_type = "JSON";
		out_type = "JSON";
		mode = "2D";
		show_help = false;
	}

	// Method for retreiving the error string.
	// @return string
	string& error(){
		return error_;
	}

	// Method for determining if the configuration is sane.
	// @return bool
	bool sane(){
		if(in_file.empty()){
			error_ = "--in=[FILE] not specified.";
			return false;
		}

		return true;
	}

	// Method for parsing command line parameters
	// @param int argc
	// @param char** argv
	// @returns bool
	bool parse(int argc, char ** argv){

		if(argc == 1){
			show_help = true;
			return true;
		}

		//iterate options
		for(int i=1; i<argc; i++){
			string arg = argv[i];

			//split on '='
			istringstream iss(arg);
			vector<string> parsed_values;
			while(!iss.eof()){
				string v;
				getline(iss, v, '=');
				parsed_values.push_back(v);
			}

			if(parsed_values.at(0) == "--help"){
				show_help = true;
				return 0;
			}
			else if(parsed_values.at(0) == "--in"){
				in_file = parsed_values.at(1);
				continue;
			}
			else if(parsed_values.at(0) == "--out"){
				out_file = parsed_values.at(1);
				continue;
			}
			else if(parsed_values.at(0) == "--in-type"){
				in_type = parsed_values.at(1);
				continue;
			}
			else if(parsed_values.at(0) == "--out-type"){
				out_type = parsed_values.at(1);
				continue;
			}
			else if(parsed_values.at(0) == "--mode"){
				mode = parsed_values.at(1);
				continue;
			}
		}

		return true;
	}

	private:
	string error_;

};

#endif
