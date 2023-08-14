#pragma once
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
class Config {

public:
	Config(std::string name) {
		this->path = name; //Set path to cfg file
		this->input = std::ifstream(this->path); //open input
	}

	void open() {
		this->outputstream = std::ofstream(this->path); //open output for config writing
	}

	void close() {
		this->outputstream.close(); //close output after writing config
	}

	template <typename tp>
	tp set(std::string name, tp value) {
		outputstream << name << " " << value << std::endl; //Write to config
		return true;
	}

	template <class tg>
	tg get(std::string name) {
		this->input.close(); //Close Input
		this->input = std::ifstream(this->path); //Jump back to idx 0 of txt file
		std::vector<std::string>stack;
		std::string buffer;
		while (this->input >> buffer) {
			stack.push_back(buffer); //push all options into vector
		}
		for (int i = 0; i < stack.size(); i++) {
			if (stack.at(i) == name) {

				return atof(stack.at(i + 1).c_str()); //if option found get value from idx + 1
			}
		}
	}
private:
	std::string path;
	std::ifstream input;
	std::ofstream outputstream;
};
