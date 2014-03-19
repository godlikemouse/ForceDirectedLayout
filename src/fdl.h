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

#ifndef __FDL_H
#define __FDL_H

#include <iostream>
#include <vector>

#include "command-switches.h"
#include "file-handler.h"
#include "config.h"
#include "layout.h"

using namespace std;

// Method for showing usage
void show_usage(){
	cout << "fdl - " << PACKAGE_STRING << " " << PACKAGE_BUGREPORT << " " << PACKAGE_URL << endl;
	cout << "\t Performs a force directed layout algorithm against the specified file." << endl;
	cout << endl;
	cout << "Usage: fdl [OPTION]... --in=[INPUT-FILE] --out=[OUTPUT-FILE]" << endl;
	cout << endl;
	cout << "Options:" << endl;
	cout << "\t --in-type=TYPE\t\tSpecifies the input file type, default JSON (JSON, GraphML)." << endl;
	cout << "\t --out-type=TYPE\tSpecifies the output file type, default JSON (JSON, GraphML)." << endl;
	cout << "\t --in=FILE\t\tSpecifies the input file." << endl;
	cout << "\t --out=FILE\t\tSpecifies the output file." << endl;
	cout << "\t --mode=MODE\t\tSpecifies the detangle mode, default 2D (2D, 3D)." << endl;
	cout << "\t --help\t\t\tDisplays this help message." << endl;
	cout << endl;
}

#endif
