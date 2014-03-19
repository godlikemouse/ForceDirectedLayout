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

#ifndef __NODE_H
#define __NODE_H

#include <string>
#include <stdlib.h>
#include <map>

using namespace std;

class NodeLayout {

  public:
    NodeLayout();

    float offset_x;
    float offset_y;
    float offset_z;
    float tmp_pos_x;
    float tmp_pos_y;
    float tmp_pos_z;
    float force;
    float force_z;

};

class Node {

	public:
    Node();

	string id;
	float x;
	float y;
	float z;
	NodeLayout layout;
	map<string, string> attributes;

};

#endif
