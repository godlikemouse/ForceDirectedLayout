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

#include "layout.h"

// Constructor
// @param vector<Node> nodes
// @param vector<Edge> edges
// @param CommandSwitches switches
Layout::Layout(vector<Node>* nodes, vector<Edge>* edges, CommandSwitches& switches){

	switches_ = switches;
	nodes_ = nodes;
	edges_ = edges;

	width_ = 1024;
	height_ = 768;
	layout_iterations_ = 0;
	attraction_multiplier_ = 5.0f;
	repulsion_multiplier_ = 0.75f;
	max_iterations_ = 1000;
	EPSILON_ = 0.000001f;
	temperature_ = width_ / 10.0f;
	force_constant_ = sqrt(height_ * width_ / nodes_->size());
	attraction_constant_ = attraction_multiplier_ * force_constant_;
	repulsion_constant_ = repulsion_multiplier_ * force_constant_;
	repulsion_constant_sq_ = repulsion_constant_ * repulsion_constant_;

	clog << "Mapping nodes" << endl;

	//map link to nodes
	for(int i=0; i<edges_->size(); i++){
		Edge& e = edges_->at(i);

		if(!find_node(e.source_id, &(e.source))){
			error_ = "Could not find source node: " + e.source_id + " for edge: " + e.id + ".";
		}

		if(!find_node(e.target_id, &(e.target))){
			error_ = "Could not find target node: " + e.target_id + " for edge: " + e.id + ".";
		}
	}

}

// Method for finding a node by id.
// @param string id
// @param Node** node
// @return bool
bool Layout::find_node(string id, Node** node){
	for(int i=0; i<nodes_->size(); i++){
		if(nodes_->at(i).id == id){
			*node= &(nodes_->at(i));
			return true;
		}
	}

	return false;
}

// Method for performing the force directed layout.
// @return bool
bool Layout::layout(){

	clog << "Performing layout" << flush;

	bool mode_3d = switches_.mode == "3D" ? true : false;

	while(layout_iterations_ < max_iterations_ && temperature_ > 0.000001f){

		if(layout_iterations_ % 10 == 0)
			clog << "." << flush;

		//calculate repulsion
		for(int i=0; i<nodes_->size(); i++){

			Node& node_v = nodes_->at(i);

			if(i == 0){
				node_v.layout.offset_x = 0;
				node_v.layout.offset_y = 0;
				node_v.layout.offset_z = 0;
			}

			node_v.layout.force = 0;

			node_v.layout.tmp_pos_x = max(node_v.layout.tmp_pos_x, node_v.x);
			node_v.layout.tmp_pos_y = max(node_v.layout.tmp_pos_y, node_v.y);

			if(mode_3d)
				node_v.layout.tmp_pos_z = max(node_v.layout.tmp_pos_z, node_v.z);


			for(int j=i+1; j<nodes_->size(); j++){
				if(i == j) continue;

				Node& node_u = nodes_->at(j);

				node_u.layout.tmp_pos_x = max(node_u.layout.tmp_pos_x, node_u.x);
				node_u.layout.tmp_pos_y = max(node_u.layout.tmp_pos_y, node_u.y);

				if(mode_3d)
					node_u.layout.tmp_pos_z = max(node_u.layout.tmp_pos_z, node_u.z);

				float delta_x = node_v.layout.tmp_pos_x - node_u.layout.tmp_pos_x;
				float delta_y = node_v.layout.tmp_pos_y - node_u.layout.tmp_pos_y;

				float delta_z = 0.0f;
				if(mode_3d)
					delta_z = node_v.layout.tmp_pos_z - node_u.layout.tmp_pos_z;

				float dx = sqrt((delta_x * delta_x) + (delta_y * delta_y));

				float dy = 0.0f;
				if(mode_3d)
					dy = sqrt((delta_z * delta_z) + (delta_y * delta_y));

				float delta_length = max(EPSILON_, dx);

				float delta_length_z = 0.0f;
				if(mode_3d)
					delta_length_z = max(EPSILON_, dy);

				float force = repulsion_constant_sq_ / delta_length;

				float force_z = 0.0f;
				if(mode_3d)
					force_z = repulsion_constant_sq_ / delta_length_z;

				node_v.layout.force += force;
				node_u.layout.force += force;

				float dxf = (delta_x / delta_length) * force;
				float dyf = (delta_y / delta_length) * force;

				float dzf = 0.0f;
				if(mode_3d)
					dzf = (delta_z / delta_length_z) * force_z;

				node_v.layout.offset_x += dxf;
				node_v.layout.offset_y += dyf;

				if(i == 0){
					node_u.layout.offset_x = 0.0f;
					node_u.layout.offset_y = 0.0f;
					node_u.layout.offset_z = 0.0f;
				}

				node_u.layout.offset_x -= dxf;
				node_u.layout.offset_y -= dyf;

				if(mode_3d){
					node_v.layout.offset_z += dzf;
					node_u.layout.offset_z -= dzf;
				}
			}

		}


		//calculate attraction
		for(int i=0; i<edges_->size(); i++){
			Edge& edge = edges_->at(i);

			float delta_x = edge.source->layout.tmp_pos_x - edge.target->layout.tmp_pos_x;
			float delta_y = edge.source->layout.tmp_pos_y - edge.target->layout.tmp_pos_y;

			float delta_z = 0.0f;
			if(mode_3d)
				delta_z = edge.source->layout.tmp_pos_z - edge.target->layout.tmp_pos_z;

			float dx = sqrt((delta_x * delta_x) + (delta_y * delta_y));

			float dy = 0.0f;
			if(mode_3d)
				dy = sqrt((delta_z * delta_z) + (delta_y * delta_y));

			float delta_length = max(EPSILON_, dx);

			float delta_length_z = 0.0f;
			if(mode_3d)
				delta_length_z = max(EPSILON_, dy);

			float force = (delta_length * delta_length) / attraction_constant_;

			float force_z = 0.0f;
			if(mode_3d)
				force_z = (delta_length_z * delta_length_z) / attraction_constant_;

			edge.source->layout.force -= force;
			edge.target->layout.force += force;

			float dxf = (delta_x / delta_length) * force;
			float dyf = (delta_y / delta_length) * force;

			float dzf = 0.0f;
			if(mode_3d)
				dzf = (delta_z / delta_length_z) * force_z;

			edge.source->layout.offset_x -= dxf;
			edge.source->layout.offset_y -= dyf;

			if(mode_3d)
				edge.source->layout.offset_z -= dzf;

			edge.target->layout.offset_x += dxf;
			edge.target->layout.offset_y += dyf;

			if(mode_3d)
				edge.target->layout.offset_z += dzf;
		}

		//calculate positions
		for(int i=0; i<nodes_->size(); i++){
			Node& node = nodes_->at(i);

			float dx = sqrt((node.layout.offset_x * node.layout.offset_x) + (node.layout.offset_y * node.layout.offset_y));

			float dy = 0.0f;
			if(mode_3d)
				dy = sqrt((node.layout.offset_z * node.layout.offset_z) + (node.layout.offset_y * node.layout.offset_y));

			float delta_length = max(EPSILON_, dx);

			float delta_length_z = 0.0f;
			if(mode_3d)
				delta_length_z = max(EPSILON_, dy);

			node.layout.tmp_pos_x += (node.layout.offset_x / delta_length) * min(delta_length, temperature_);
			node.layout.tmp_pos_y += (node.layout.offset_y / delta_length) * min(delta_length, temperature_);

			if(mode_3d)
				node.layout.tmp_pos_z += (node.layout.offset_z / delta_length_z) * min(delta_length_z, temperature_);

			node.x -= (node.x - node.layout.tmp_pos_x)/10;
			node.y -= (node.y - node.layout.tmp_pos_y)/10;

			if(mode_3d)
				node.z -= (node.z - node.layout.tmp_pos_z)/10;
		}

		temperature_ *= (1.0f - (layout_iterations_ / max_iterations_));
		layout_iterations_++;
	}

	clog << endl;

	return true;
}

// Method for retrieving the error string.
// @return string
string& Layout::error(){
	return error_;
}
