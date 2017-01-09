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

#include "file-handler.h"

// Constructor
// @param string filename
// @param string type
// @param CommandSwitches switches
FileHandler::FileHandler(string filename, string type, CommandSwitches& switches){
	filename_ = filename;
	type_ = type;
	switches_ = switches;
}

// Method for reading nodes and edges from a file
// @param vector<Node> nodes
// @param vector<Edge> edges
// @return bool
bool FileHandler::read(vector<Node>& nodes, vector<Edge>& edges){

	if(type_ == "JSON"){
		parse_json(nodes, edges);
	}

	if(type_ == "GraphML"){
		parse_graphml(nodes, edges);
	}

	return true;
}

// Method for writing nodes and edges out to a file
// @param vector<Node> nodes
// @param vector<Edge> edges
// @return bool
bool FileHandler::write(vector<Node>& nodes, vector<Edge>& edges){

	if(type_ == "JSON"){
		write_json(nodes, edges);
	}

	if(type_ == "GraphML"){
		write_graphml(nodes, edges);
	}

	return true;
}

// Method for retrieving the error string.
// @return string
string& FileHandler::error(){
	return error_;
}

// Method for parsing JSON into nodes and edges
// @param vector<Node> nodes
// @param vector<Edge> edges
// @return bool
bool FileHandler::parse_json(vector<Node>& nodes, vector<Edge>& edges){

	ifstream file(filename_.data());
	string json_text;
	string line;

	//read json file
	if(file.is_open()){
		while(getline(file, line)){
			json_text += line;
		}
		file.close();
	}
	else{
		error_ = "Could not open file: " + filename_ + ".";
		return false;
	}

	//parse json
	Json::Value root;
	Json::Reader reader;

	if(!reader.parse(json_text.c_str(), root)){
		error_ = "Failed to parse JSON file.";
		return false;
	}

	Json::Value nodes_array = root["nodes"];
	Json::Value edges_array = root["edges"];

	//load nodes
	for(int i=0; i<nodes_array.size(); i++){
		Json::Value n = nodes_array[i];

		Node node;

		Json::Value id = n["id"];

		if(!id){
			error_ = "JSON \"nodes\" property \"id\" required.";
			return false;
		}

		node.id = id.asString();

		//iterate all node attributes
		for(Json::ValueIterator itr = n.begin(); itr != n.end(); itr++){
			if(itr.key() == "id" ||
			   itr.key() == "x" ||
			   itr.key() == "y" ||
			   itr.key() == "z")
				continue;

			Json::Value prop_name = itr.key();
			Json::Value prop_value = n[prop_name.asString()];
			node.attributes[ prop_name.asString() ] = prop_value.asString();
		}

		nodes.push_back(node);
	}

	//load edges
	for(int i=0; i<edges_array.size(); i++){
		Json::Value e = edges_array[i];

		Json::Value id = e["id"];
		Json::Value source = e["source"];
		Json::Value target = e["target"];

		if(!id){
			error_ = "JSON \"edges\" property \"id\" required.";
			return false;
		}

		if(!source){
			error_ = "JSON \"edges\" property \"source\" required.";
			return false;
		}

		if(!target){
			error_ = "JSON \"edges\" property \"target\" required.";
			return false;
		}


		Edge edge;
		edge.id = id.asString();
		edge.source_id = source.asString();
		edge.target_id = target.asString();

		//iterate all node attributes
		for(Json::ValueIterator itr = e.begin(); itr != e.end(); itr++){
			if(itr.key() == "id" ||
			   itr.key() == "source" ||
			   itr.key() == "target")
				continue;

			Json::Value prop_name = itr.key();
			Json::Value prop_value = e[prop_name.asString()];
			edge.attributes[ prop_name.asString() ] = prop_value.asString();
		}

		edges.push_back(edge);
	}

	return true;
}

// Method for parsing GraphML into nodes and edges.
// @param vector<Node> nodes
// @param vector<Edge> edges
// @return bool
bool FileHandler::parse_graphml(vector<Node>& nodes, vector<Edge>& edges){

	ifstream file(filename_.data());
	string xml_text;
	string line;

	//read xml file
	if(file.is_open()){
		while(getline(file, line)){
			xml_text += line;
		}
		file.close();
	}
	else{
		error_ = "Could not open file: " + filename_ + ".";
		return false;
	}

	xml_document<> doc;
	doc.parse<0>( const_cast<char *>(xml_text.c_str()) );

	//get graphml node
	xml_node<> *root_node = doc.first_node("graphml");

	if(!root_node){
		error_ = "GraphML \"graphml\" root node missing.";
		return false;
	}

	//get graph node
	xml_node<> *graph_node = root_node->first_node("graph");

	if(!graph_node){
		error_ = "GraphML \"graph\" node missing.";
		return false;
	}

	//iterate nodes and edges
	for(xml_node<> * xml_node = graph_node->first_node();
		xml_node; xml_node = xml_node->next_sibling()){

		if( strcmp(xml_node->name(), "node") == 0 ){
			//node

			Node node;

			//iterate attributes
			for(xml_attribute<> *xml_attr = xml_node->first_attribute();
				xml_attr; xml_attr = xml_attr->next_attribute()){

				if( strcmp(xml_attr->name(), "id") == 0 ){
					//id
					node.id = xml_attr->value();
				}
				else{
					//additional attributes
					node.attributes[ xml_attr->name() ] = xml_attr->value();
				}
			}

			nodes.push_back(node);
		}
		else if( strcmp(xml_node->name(), "edge") == 0 ){
			//edge

			Edge edge;

			//iterate attributes
			for(xml_attribute<> *xml_attr = xml_node->first_attribute();
				xml_attr; xml_attr = xml_attr->next_attribute()){

				if( strcmp(xml_attr->name(), "id") == 0 ){
					//id
					edge.id = xml_attr->value();
				}
				else if( strcmp(xml_attr->name(), "source") == 0 ){
					//source
					edge.source_id = xml_attr->value();
				}
				else if( strcmp(xml_attr->name(), "target") == 0 ){
					//target
					edge.target_id = xml_attr->value();
				}
				else{
					//additional attributes
					edge.attributes[ xml_attr->name() ] = xml_attr->value();
				}
			}

			edges.push_back(edge);
		}

	}

	return true;
}

// Method for writing nodes and edges out to a JSON file.
// @param vector<Node> nodes
// @param vector<Edge> edges
// @return bool
bool FileHandler::write_json(vector<Node>& nodes, vector<Edge>& edges){

	Json::Value root;

	//nodes
	Json::Value jsonNodes(Json::arrayValue);

	for(int i=0; i<nodes.size(); i++){
		Node n = nodes[i];

		Json::Value jsonNode;
		jsonNode["id"] = n.id;
		jsonNode["x"] = n.x;
		jsonNode["y"] = n.y;
		jsonNode["z"] = n.z;

		//additional attributes
		for(map<string,string>::iterator itr = n.attributes.begin();
			itr != n.attributes.end();
			itr++){

			jsonNode[ itr->first ] = itr->second;
		}

		jsonNodes.append(jsonNode);
	}

	root["nodes"] = jsonNodes;

	//edges
	Json::Value jsonEdges(Json::arrayValue);

	for(int i=0; i<edges.size(); i++){
		Edge e = edges[i];

		Json::Value jsonEdge;
		jsonEdge["id"] = e.id;
		jsonEdge["source"] = e.source_id;
		jsonEdge["target"] = e.target_id;

		//additional attributes
		for(map<string,string>::iterator itr = e.attributes.begin();
			itr != e.attributes.end();
			itr++){

			jsonEdge[ itr->first ] = itr->second;
		}

		jsonEdges.append(jsonEdge);
	}

	root["edges"] = jsonEdges;

	Json::StyledWriter writer;
	string json_text = writer.write(root);

	if(filename_.empty()){
		//write to std out
		cout << root << endl;
	}
	else{
		//write out to file
		ofstream file(filename_.data());
		file.write(json_text.c_str(), json_text.size());
		file.close();
	}

	return true;
}

// Method for writing nodes and edges out to a GraphML file.
// @param vector<Node> nodes
// @param vector<Edge> edges
// @return bool
bool FileHandler::write_graphml(vector<Node>& nodes, vector<Edge>& edges){

	std::ostringstream stream;

	//graphml header
	stream << "<graphml xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns\" ";
	stream << "xmlns=\"http://graphml.graphdrawing.org/xmlns\" ";
	stream << "xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" ";
	stream << ">";
	stream << endl;

	//write graph
	stream << "<graph id=\"G\" edgedefault=\"directed\">" << endl;

	//write nodes
	for(int i=0; i<nodes.size(); i++){
		Node n = nodes[i];

		stream << "<node ";
		stream << "id=\"" << n.id << "\" ";
		stream << "x=\"" << n.x << "\" ";
		stream << "y=\"" << n.y << "\" ";
		stream << "z=\"" << n.z << "\" ";

		//additional attributes
		for(map<string,string>::iterator itr = n.attributes.begin();
			itr != n.attributes.end();
			itr++){

			stream << itr->first << "=\"" << itr->second << "\" ";
		}

		stream << "/>" << endl;
	}

	//write edges
	for(int i=0; i<edges.size(); i++){
		Edge e = edges[i];

		stream << "<edge ";
		stream << "id=\"" << e.id << "\" ";
		stream << "source=\"" << e.source_id << "\" ";
		stream << "target=\"" << e.target_id << "\" ";

		//additional attributes
		for(map<string,string>::iterator itr = e.attributes.begin();
			itr != e.attributes.end();
			itr++){

			stream << itr->first << "=\"" << itr->second << "\" ";
		}

		stream << "/>" << endl;
	}

	stream << "</graph>" << endl;

	stream << "</graphml>" << endl;

	if(filename_.empty()){
		//write to std out
		cout << stream.str() << endl;
	}
	else{
		//write out to file
		ofstream file(filename_.data());
		std::string xml_text = stream.str();

		file.write(xml_text.c_str(), xml_text.size());
		file.close();
	}

	return true;
}
