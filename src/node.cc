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

#include "node.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

// Constructor
NodeLayout::NodeLayout(){
  offset_x = 0.0f;
  offset_y = 0.0f;
  offset_z = 0.0f;
  tmp_pos_x = 0.0f;
  tmp_pos_y = 0.0f;
  tmp_pos_z = 0.0f;
  force = 0.0f;
  force_z = 0.0f;
}

// Constructor
Node::Node(){
  x = rand() % 10000000 / 1000000.0f;
  y = rand() % 10000000 / 1000000.0f;
  z = rand() % 10000000 / 1000000.0f;
}
