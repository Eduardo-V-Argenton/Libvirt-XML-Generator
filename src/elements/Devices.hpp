#ifndef DEVICES_HPP
#define DEVICES_HPP

#include "../XmlAble.hpp"
#include "devices/Controller.hpp"
#include "devices/Disk.hpp"
#include "devices/Emulator.hpp"
#include <string>
#include <vector>

namespace PlaceHolder {
namespace Elements {
namespace DeviceElements {

struct Devices : PlaceHolder::Interfaces::XmlAble {

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

	PlaceHolder::Elements::Devices::EmulatorElements::Emulator emulator;
	std::vector<PlaceHolder::Elements::Devices::DiskElements::Disk> disks;
	std::vector<PlaceHolder::Elements::Devices::ControllerElements::Controller>
		controllers;

	std::string getXml() const override;
};
} // namespace DeviceElements
} // namespace Elements
} // namespace PlaceHolder
#endif
