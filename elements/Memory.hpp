#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <format>
#include <string>
#include "XmlAble.hpp"

struct Memory : XmlAble {
	std::string unit = "M";
	int memory;

	std::string getXml() override {
		return std::format("<memory unit=\"{}\">{}</memory>", unit, memory);
	}
};
#endif