#ifndef DEVICES_HPP
#define DEVICES_HPP

#include <string>
#include <vector>
#include "../XmlAble.hpp"
#include "Controller.hpp"
#include "Disk.hpp"
#include "Emulator.hpp"

struct Devices : XmlAble {


	// ToDo
	struct Filesystem {};


	struct Hotdev {
		struct USBSource {
			std::string vendor;
			std::string product;
		};

		struct PCISource {
			int domain;
			int bus;
			int slot;
			int function;
		};

		const std::string mode = "subsystem";
		std::string type;
		bool managed;
	};

	struct Video {
		std::string model;
	};

	// ToDo
	struct GraphicalFrameBuffer {};

	// ToDo
	struct Console {};

	// ToDo
	struct Network {};

	// ToDo
	struct TPM {};

	Emulator emulator;
	std::vector<Disk> disks;
	std::vector<Controller> controllers;

	std::string getXml() override {
		std::string xml = "<devices>";
		for (Controller controller : controllers) {
			xml.append(controller.getXml());
		}
		for (Disk disk : disks) {
			xml.append(disk.getXml());
		}
		xml.append("</devices>");
		return xml;
	}
};
#endif