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

#ifndef __LAYOUT_H
#define __LAYOUT_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

#include "command-switches.h"
#include "node.h"
#include "edge.h"

using namespace std;

class Layout {

	public:
	Layout(vector<Node>*, vector<Edge>*, CommandSwitches&);
	bool layout();
	string& error();

	private:
	CommandSwitches switches_;
	vector<Node>* nodes_;
	vector<Edge>* edges_;
	float attraction_multiplier_;
	float repulsion_multiplier_;
	int max_iterations_;
	float EPSILON_;
	float attraction_constant_;
	float repulsion_constant_;
	float force_constant_;
	int layout_iterations_;
	float temperature_;
	float repulsion_constant_sq_;
	int width_;
	int height_;
	string error_;

	bool find_node(string, Node**);

};


#endif
