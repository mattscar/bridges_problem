#include <iostream>

#include "yaml.h"

using Hiker = std::pair<std::string, double>;
using HikerVec = std::vector<Hiker>;

// Function prototypes
std::vector<HikerVec> initHikers(const YAML::Node&);
double moveForward(HikerVec&, HikerVec&, int, double, int, bool);
double moveBack(HikerVec&, HikerVec&, int, double);

int main() {

	// Total crossing time
	double tm = 0.0;

	// Contains a vector of hikers for each bridge
	std::vector<HikerVec> hikers;

	// Load YAML file
	YAML::Node doc = YAML::LoadFile("bridges.yaml");
	
	// Verify that hikers and bridges are present
	if(!doc["hikers"]) {
		std::cerr << "Couldn't find hikers. Exiting." << std::endl;
		exit(EXIT_FAILURE);
	}
	if(!doc["bridges"]) {
		std::cerr << "Couldn't find bridges. Exiting." << std::endl;
		exit(EXIT_FAILURE);
	}
	
	// Create vector of hikers for each bridge
	hikers = initHikers(doc);
	
	// Iterate through bridges
	YAML::Node bridgeNode = doc["bridges"];
	double len;
	for (std::size_t i=0; i<bridgeNode.size(); i++) {
	
		// Get bridge length and starting/ending hikers
		len = bridgeNode[i]["length"].as<double>();
		HikerVec& startHikers = hikers[i];
		HikerVec& endHikers = hikers[i+1];
		
		// Passes depend on the number of hikers
		switch(startHikers.size()) {
		
			case 0: break;
			case 1: tm += moveForward(startHikers, endHikers, i, len, 1, true); break;
			case 2: tm += moveForward(startHikers, endHikers, i, len, 2, true); break;
			case 3:
				tm += moveForward(startHikers, endHikers, i, len, 2, true); 
				tm += moveBack(startHikers, endHikers, i, len);
				tm += moveForward(startHikers, endHikers, i, len, 2, true); 
				break;
			default:
				tm += moveForward(startHikers, endHikers, i, len, 2, true); 
				tm += moveBack(startHikers, endHikers, i, len);
				while(startHikers.size() > 3) {
					tm += moveForward(startHikers, endHikers, i, len, 2, true); 
					tm += moveBack(startHikers, endHikers, i, len);
				}
				tm += moveForward(startHikers, endHikers, i, len, 2, false); 	
				tm += moveBack(startHikers, endHikers, i, len);		
				tm += moveForward(startHikers, endHikers, i, len, 2, true); 		
				break;
		}
		std::cout << std::endl;
	}

	std::cout << "Total crossing time: " << tm << " min" << std::endl;
	return 0;
}

// Construct the container of hikers for each bridge
std::vector<HikerVec> initHikers(const YAML::Node& doc) {
	
	std::vector<HikerVec> vec;
	HikerVec tmpVec;
	std::string hikerName;
	double hikerSpeed;
	
	// Create a vector of hikers for each bridge
	for(const auto& bridge: doc["bridges"]) {
		for(const auto& hiker: bridge["hikers"]) {
			hikerName = hiker.as<std::string>();
			hikerSpeed = doc["hikers"][hikerName].as<double>();
			tmpVec.emplace_back(hikerName, hikerSpeed);
		}
		vec.push_back(tmpVec);
		tmpVec.clear();
	}
	
	// Add an empty vector for the end of the last bridge
	vec.push_back(tmpVec);
	return vec;	
}

// Move one or two hikers forward across the bridge
double moveForward(HikerVec& startHikers, HikerVec& endHikers, int i, double length, int numHikers, bool isFastest) {

	Hiker tmp1, tmp2;
	double tm;

	// Sort starting hikers - slowest first, fastest last
	std::sort(startHikers.begin(), startHikers.end(), [](auto& l, auto& r) {
		return l.second < r.second;
	});

	if(isFastest) {
	
		// Move fastest 1 or 2 hikers across bridge
		switch(numHikers) {
			case 1:
				tmp1 = startHikers.back();
				startHikers.pop_back();
				tm = length/tmp1.second;
				std::cout << "Hiker " << tmp1.first << " moves forward across Bridge " << i << " in " << tm << " min" << std::endl;
				endHikers.emplace_back(tmp1);
				break;
			case 2:
				tmp1 = startHikers.back();
				startHikers.pop_back();
				tmp2 = startHikers.back();
				startHikers.pop_back();
				tm = length/tmp2.second;
				std::cout << "Hikers " << tmp1.first << " and " << tmp2.first << " move forward across Bridge " << i << " in " << tm << " min" << std::endl;
				endHikers.emplace_back(tmp2);
				endHikers.emplace_back(tmp1);
				break;
			default:
				std::cerr << "Only one or two hikers can cross" << std::endl; break;
		} 
	} else {
	
		// Move slowest 2 hikers across bridge
		tmp1 = startHikers[0];
		tmp2 = startHikers[1];
		startHikers.erase(startHikers.begin(), startHikers.begin()+2);
		tm = length/tmp1.second;
		std::cout << "Hikers " << tmp1.first << " and " << tmp2.first << " move forward across Bridge " << i << " in " << tm << " min" << std::endl;
		endHikers.insert(endHikers.begin(), tmp1);
		endHikers.insert(endHikers.begin()+1, tmp2);
	}

	return tm;
}

// Move the fastest hiker back across the bridge
double moveBack(HikerVec& startHikers, HikerVec& endHikers, int i, double length) {

	Hiker tmp;
	double tm;

	// Sort ending hikers - slowest first, fastest last
	std::sort(endHikers.begin(), endHikers.end(), [](auto& l, auto& r) {
		return l.second < r.second;
	});

	tmp = endHikers.back();
	endHikers.pop_back();
	tm = length/tmp.second;
	std::cout << "Hiker " << tmp.first << " moves back across Bridge " << i << " in " << tm << " min" << std::endl;
	startHikers.emplace_back(tmp);

	return tm;
}
