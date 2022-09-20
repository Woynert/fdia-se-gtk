#include <string>
#include <iostream>
#include <yaml-cpp/yaml.h>
//using namespace std;

YAML::Node config;

void info_init(){
	config = YAML::LoadFile("../info.yaml");
	return;
}

std::string info_get_title(std::string name){
	return (config[name]["title"].as<std::string>() );
}

std::string info_get_desc(std::string name){
	return (config[name]["desc"].as<std::string>() );
}

//struct HechoInfo{
	//string title;
	//string desc;
//};

//map<string, HechoInfo*> mainData;


/*void info_create_hecho(string name, string title, string desc){

	HechoInfo* hi = new HechoInfo();
	hi->title = title;
	hi->desc  = desc;

	mainData.insert(make_pair(name, hi));
}*/


//string info_get_desc(string name){
	//return (config[name]["desc"].as<string>() );
	////return (mainData[name]->desc);
//}

