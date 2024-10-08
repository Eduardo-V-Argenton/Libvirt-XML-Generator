#include "VirtualMachine.hpp"

#include "elements/Cpu.hpp"
#include "elements/Devices.hpp"
#include "elements/Domain.hpp"
// #include "elements/Features.hpp"
#include "elements/Memory.hpp"
#include "elements/Os.hpp"
#include "elements/PowerManagement.hpp"
#include "elements/SystemClock.hpp"

// #include "elements/devices/Console.hpp"
#include "elements/devices/Controller.hpp"
#include "elements/devices/Disk.hpp"
// #include "elements/devices/Emulator.hpp"
// #include "elements/devices/Filesystem.hpp"
#include "elements/devices/Graphics.hpp"
#include "elements/devices/HotDev.hpp"
#include "elements/devices/Network.hpp"
#include "elements/devices/Tpm.hpp"
#include "elements/devices/Video.hpp"

#include <array>
#include <cstdio>
#include <cxxopts.hpp>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

std::string exec(const char *cmd);
std::vector<int> convertStringToVector(const std::string &str);
cxxopts::Options commands();
void setDomain(LibvirtXMLGenerator::VirtualMachine &vm,
			   cxxopts::ParseResult &result);
void setMemory(LibvirtXMLGenerator::VirtualMachine &vm,
			   cxxopts::ParseResult &result);
void setCpu(LibvirtXMLGenerator::VirtualMachine &vm,
			cxxopts::ParseResult &result);
void setOs(LibvirtXMLGenerator::VirtualMachine &vm,
		   cxxopts::ParseResult &result);
// ToDo AutoSystemClock
void setSystemClock(LibvirtXMLGenerator::VirtualMachine &vm,
					cxxopts::ParseResult &result);
void setDisk(LibvirtXMLGenerator::VirtualMachine &vm,
			 cxxopts::ParseResult &result);
void setRemoteDisk(LibvirtXMLGenerator::VirtualMachine &vm,
				   cxxopts::ParseResult &result);
// ToDo autoAddController
void setController(LibvirtXMLGenerator::VirtualMachine &vm,
				   cxxopts::ParseResult &result);
void setHotDevUsb(LibvirtXMLGenerator::VirtualMachine &vm,
				  cxxopts::ParseResult &result);
void setHotDevPci(LibvirtXMLGenerator::VirtualMachine &vm,
				  cxxopts::ParseResult &result);
void saveFile(LibvirtXMLGenerator::VirtualMachine &vm,
			  cxxopts::ParseResult &result);
void setDevices(LibvirtXMLGenerator::VirtualMachine &vm,
				cxxopts::ParseResult &result);
void setPM(LibvirtXMLGenerator::VirtualMachine &vm,
		   cxxopts::ParseResult &result);
void setTpm(LibvirtXMLGenerator::VirtualMachine &vm,
			cxxopts::ParseResult &result);
void setNetwork(LibvirtXMLGenerator::VirtualMachine &vm,
				cxxopts::ParseResult &result);

// ToDo Invalid Argument handling
int main(int argc, char *argv[]) {

	cxxopts::Options options = commands();

	try {
		cxxopts::ParseResult result = options.parse(argc, argv);

		if (result.count("help")) {
			std::cout << options.help() << std::endl;
			return 0;
		}

		LibvirtXMLGenerator::VirtualMachine vm;

		setDomain(vm, result);
		setMemory(vm, result);
		setCpu(vm, result);
		setOs(vm, result);
		setSystemClock(vm, result);
		setDevices(vm, result);
		saveFile(vm, result);

	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}

std::string exec(const char *cmd) {
	std::array<char, 128> buffer;
	std::string result;
	// Open a pipe to the shell command
	std::unique_ptr<FILE, int (*)(FILE *)> pipe(popen(cmd, "r"), pclose);
	if (!pipe) {
		throw std::runtime_error("popen() failed!");
	}
	// Read the output of the command
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result += buffer.data();
	}
	return result;
}

std::vector<int> convertStringToVector(const std::string &str) {
	std::vector<int> result;
	std::stringstream ss(str);
	std::string token;

	// Split the string by commas and convert each token to an integer
	while (std::getline(ss, token, ',')) {
		result.push_back(
			std::stoi(token)); // Convert token to integer and add to vector
	}

	return result;
}

cxxopts::Options commands() {
	cxxopts::Options options(
		"libvirt-xml-generator",
		"Simple Program to generate a XML that can be used with libvirt");

	options.add_options()("h,help", "Show help")(
		"n,name", "VM's name",
		cxxopts::value<std::string>()->default_value("VM"))(
		"t,type", "VM's type, default value is KVM",
		cxxopts::value<std::string>()->default_value("kvm"))(
		"description", "VM's description", cxxopts::value<std::string>())(
		"m,memory", "VM's memory's size in MB",
		cxxopts::value<int>()->default_value("1024"))(
		"cpu-mode", "VM's cpu-mode",
		cxxopts::value<std::string>()->default_value("host-passthrough"))(
		"cpu-topology", "VM's cpu topology, format like sockets,cores,threads",
		cxxopts::value<std::vector<int>>()->default_value("1,1,1"))(
		"auto-cpu-placement",
		"Enable the cpu placement to be automatic, it will ignore the 2 "
		"below"
		" Usually it is less performatic",
		cxxopts::value<bool>()->default_value("false"))(
		"quant-cpu-emulator",
		"Set the quantity of CPUs that'll be used to emulate/control the VM",
		cxxopts::value<int>()->default_value("1"))(
		"quant-cpu-io",
		"Set the quantity of CPUs that'll be used to control IO between the "
		"Host and the VM",
		cxxopts::value<int>()->default_value("1"))(
		"efi", "Enable VM's EFI",
		cxxopts::value<bool>()->default_value("false"))(
		"arch", "VM's architecture",
		cxxopts::value<std::string>()->default_value("x86_64"))(
		"bootmenu-time", "Set BootMenu timeout, if 0 disable bootMenu",
		cxxopts::value<int>()->default_value("0"))(
		"d,disk",
		"Add a virtual disk, format like format,absolute_path_file,dev",
		cxxopts::value<std::vector<std::string>>())(
		"remote-disk",
		"Add a remote disk, format like "
		"format,protocol,url,hostname,port,username,password-type,password,dev",
		cxxopts::value<std::vector<std::string>>())(
		"usb-device", "Add a usb device, format like vendor,product",
		cxxopts::value<std::vector<std::string>>())(
		"pci-device", "Add a pci device, format like domain,bus,slot,function",
		cxxopts::value<std::vector<int>>())(
		"o, output", "Set the output file location",
		cxxopts::value<std::string>()->default_value("output.xml"))(
		"suspend-to-mem", "Enable VM's to suspend to mem",
		cxxopts::value<bool>()->default_value("false"))(
		"suspend-to-disk", "Enable VM's to suspend to disk",
		cxxopts::value<bool>()->default_value("false"))(
		"emulated-tpm",
		"Add a emulated TPM device into VM format like model,version. "
		"Available models are 'crb' and 'tis' and version '1.2' and '2.0'. "
		"Only accept that one or passthrough-tpm, dont both",
		cxxopts::value<std::vector<std::string>>())(
		"passthrough-tpm",
		"Add the host's TPM device into VM format like model,path. "
		"Available models are 'crb' and 'tis'. "
		"Only accept that one or emulated-tpm, dont both",
		cxxopts::value<std::vector<std::string>>())(
		"nat-network", "Add a Nat Network into the VM, enter the network name",
		cxxopts::value<std::string>()->default_value("default"))(
		"nat-network-mac",
		"Add a Nat Network with a mac address into the VM, format like "
		"network-name,mac",
		cxxopts::value<std::vector<std::string>>())(
		"bridge-network", "Add a Bridge Network into the VM, enter the bridge ",
		cxxopts::value<std::string>()->default_value("default"))(
		"bridge-network-mac",
		"Add a Bridge Network with a mac address into the VM, format like "
		"bridge,mac",
		cxxopts::value<std::vector<std::string>>())(
		"direct-network",
		"Add a Direct Network into the VM, format like mode,dev",
		cxxopts::value<std::vector<std::string>>())(
		"direct-network-mac",
		"Add a Direct Network with a mac address into the VM, format like "
		"mode,dev,mac",
		cxxopts::value<std::vector<std::string>>());
	return options;
}

void setDomain(LibvirtXMLGenerator::VirtualMachine &vm,
			   cxxopts::ParseResult &result) {

	vm.domain.name = result["name"].as<std::string>();

	vm.domain.domain = result["type"].as<std::string>();

	if (result.count("description")) {
		vm.domain.description = result["description"].as<std::string>();
	}
}

void setMemory(LibvirtXMLGenerator::VirtualMachine &vm,
			   cxxopts::ParseResult &result) {

	vm.memory.memory = result["memory"].as<int>();
}

void setCpu(LibvirtXMLGenerator::VirtualMachine &vm,
			cxxopts::ParseResult &result) {

	vm.cpu.mode = result["cpu-mode"].as<std::string>();
	std::vector<int> cpuTopology =
		result["cpu-topology"].as<std::vector<int>>();
	if (cpuTopology.size() != 3) {
		throw std::invalid_argument("Invalid CPU Topology");
	}
	int quantVcpu = cpuTopology[0] * cpuTopology[1] * cpuTopology[2];
	bool autoCpuDist = result["auto-cpu-placement"].as<bool>();
	if (!autoCpuDist) {
		int quantCpuEmulator = result["quant-cpu-emulator"].as<int>();
		int quantCpuIO = result["quant-cpu-io"].as<int>();
		vm.cpu.cpupin.quantVcpu = quantVcpu;
		vm.cpu.cpupin.placement = "static";
		LibvirtXMLGenerator::Elements::CpuElement::Cpu::CpuPin::VCpuPin vcpupin;

		const char *command = R"(
                awk -F': ' '/^processor/ {cpu=$2} /^core id/ {core=$2; print cpu "-" core}' /proc/cpuinfo |
                sort -t '-' -k2,2n |
                cut -d'-' -f1 |
                paste -sd ','
            )";

		std::string output = exec(command);

		std::vector<int> hostCpus = convertStringToVector(output);

		if (hostCpus.size() < quantVcpu + quantCpuEmulator + quantCpuIO) {
			throw std::invalid_argument(
				"quant-cpu-emulator + quant-cpu-io + (sockets * cores "
				" * threads) must be equal or less the cpu host number of "
				"cpus");
		}
		int i = 0;
		for (const int &cpu : hostCpus) {
			vcpupin.vcpu = i;
			vcpupin.cpuset = cpu;
			vm.cpu.cpupin.cpus.push_back(vcpupin);
			if (i == quantVcpu - 1) {
				break;
			}
			i++;
		}

		i++;
		LibvirtXMLGenerator::Elements::CpuElement::Cpu::CpuPin::IOThreadPin
			ioThreadPin;
		ioThreadPin.ioThread = 1;
		if (quantCpuIO > 1) {
			ioThreadPin.cpuset = std::to_string(hostCpus[i]) + "-" +
								 std::to_string(hostCpus[i + quantCpuIO]);
		} else {
			ioThreadPin.cpuset = std::to_string(hostCpus[i]);
		}
		vm.cpu.cpupin.ioThreads.push_back(ioThreadPin);

		i += quantCpuIO;
		if (quantCpuIO > 1) {
			vm.cpu.cpupin.emulatorPin =
				std::to_string(hostCpus[i]) + "-" +
				std::to_string(hostCpus[i + quantCpuEmulator]);
		} else {
			vm.cpu.cpupin.emulatorPin = std::to_string(hostCpus[i]);
		}
	} else {
		vm.cpu.cpupin.placement = "auto";
	}

	LibvirtXMLGenerator::Elements::CpuElement::Cpu::Topology topology;
	topology.sockets = cpuTopology[0];
	topology.cores = cpuTopology[1];
	topology.threads = cpuTopology[2];
	vm.cpu.topology = topology;

	// ToDo Auto Features
	LibvirtXMLGenerator::Elements::CpuElement::Cpu::Feature feature;
	feature.name = "topoext";
	vm.cpu.features.push_back(feature);
}

void setOs(LibvirtXMLGenerator::VirtualMachine &vm,
		   cxxopts::ParseResult &result) {

	LibvirtXMLGenerator::Elements::OsElements::Os::BootDisk bootdisk;
	vm.os.bootdisk = bootdisk;
	if (result["efi"].as<bool>()) {
		vm.os.firmware = "efi";
	} else {
		vm.os.firmware = "bios";
	}

	vm.os.type.arch = result["arch"].as<std::string>();

	int bootMenuTimeOut = result["bootmenu-time"].as<int>();
	if (bootMenuTimeOut == 0) {
		vm.os.bootmenu.enable = false;
	} else {
		vm.os.bootmenu.enable = true;
		vm.os.bootmenu.timeout = bootMenuTimeOut;
	}
}

void setSystemClock(LibvirtXMLGenerator::VirtualMachine &vm,
					cxxopts::ParseResult &result) {

	LibvirtXMLGenerator::Elements::SystemClockElements::SystemClock::Timer
		timer;

	timer.name = "rtc";
	timer.tickpolicy = "catchup";
	vm.clock.timers.push_back(timer);

	timer.name = "pit";
	timer.tickpolicy = "delay";
	vm.clock.timers.push_back(timer);

	timer.name = "hpet";
	timer.tickpolicy = "";
	vm.clock.timers.push_back(timer);

	timer.name = "hypervclock";
	vm.clock.timers.push_back(timer);
}

void setDisk(LibvirtXMLGenerator::VirtualMachine &vm,
			 cxxopts::ParseResult &result) {

	if (result.count("disk")) {
		std::vector<std::string> disks =
			result["disk"].as<std::vector<std::string>>();
		if (disks.size() % 3 != 0) {
			throw std::invalid_argument("Invalid Disk");
		}
		LibvirtXMLGenerator::Elements::Devices::DiskElements::Disk disk;
		int numDisks = result.count("disk") * 3;
		for (int i = 0; i < numDisks; i += 3) {
			disk.driver.type = disks[i];
			LibvirtXMLGenerator::Elements::Devices::DiskElements::SourceLocal
				source;
			source.file = disks[i + 1];
			disk.source = source;
			// arrumar o target
			disk.target.dev = disks[i + 2];
			vm.devices.disks.push_back(disk);
		}
	}
}

void setRemoteDisk(LibvirtXMLGenerator::VirtualMachine &vm,
				   cxxopts::ParseResult &result) {

	if (result.count("remote-disk")) {
		std::vector<std::string> disks =
			result["remote-disk"].as<std::vector<std::string>>();
		if (disks.size() % 9 != 0) {
			throw std::invalid_argument("Invalid remote disk");
		}
		LibvirtXMLGenerator::Elements::Devices::DiskElements::Disk disk;
		int numDisks = result.count("disk") * 9;
		for (int i = 0; i < numDisks; i += 9) {
			disk.driver.type = disks[i];
			LibvirtXMLGenerator::Elements::Devices::DiskElements::SourceNetwork
				source;
			source.protocol = disks[i + 1];
			source.name = disks[i + 2];
			source.host.name = disks[i + 3];
			source.host.port = disks[i + 4];
			source.auth.username = disks[i + 5];
			source.auth.passwordType = disks[i + 6];
			source.auth.password = disks[i + 7];
			disk.source = source;
			// arrumar o target
			disk.target.dev = disks[i + 8];
			disk.type = "network";
			vm.devices.disks.push_back(disk);
		}
	}
}
void setController(LibvirtXMLGenerator::VirtualMachine &vm,
				   cxxopts::ParseResult &result) {
	for (int i = 0; i < 6; i++) {
		LibvirtXMLGenerator::Elements::Devices::ControllerElements::Controller
			controllerPci;
		controllerPci.type = "pci";
		controllerPci.model = "pcie-root-port";
		vm.devices.controllers.push_back(controllerPci);
	}
}

void setHotDevUsb(LibvirtXMLGenerator::VirtualMachine &vm,
				  cxxopts::ParseResult &result) {

	if (result.count("usb-device")) {
		std::vector<std::string> hotDevUsbs =
			result["usb-device"].as<std::vector<std::string>>();

		if (hotDevUsbs.size() % 2 != 0) {
			throw std::invalid_argument("Invalid USB device config");
		}
		int numUSBs = result.count("usb-device") * 2;
		LibvirtXMLGenerator::Elements::Devices::HotDevElements::HotDevUSBSource
			usb;
		for (int i = 0; i < numUSBs; i += 2) {
			usb.vendor = hotDevUsbs[0];
			usb.product = hotDevUsbs[1];
			vm.devices.hotDevUSBs.push_back(usb);
		}
	}
}

void setHotDevPci(LibvirtXMLGenerator::VirtualMachine &vm,
				  cxxopts::ParseResult &result) {

	if (result.count("pci-device")) {
		std::vector<int> hotDevPCIs =
			result["pci-device"].as<std::vector<int>>();
		if (hotDevPCIs.size() % 4 != 0) {
			throw std::invalid_argument("Invalid PCI device config");
		}
		int numPCIs = result.count("pci-device") * 4;
		LibvirtXMLGenerator::Elements::Devices::HotDevElements::HotDevPCISource
			gpu;
		for (int i = 0; i < numPCIs; i += 4) {
			gpu.domain = hotDevPCIs[0];
			gpu.bus = hotDevPCIs[1];
			gpu.slot = hotDevPCIs[2];
			gpu.function = hotDevPCIs[3];
			vm.devices.hotDevPCIs.push_back(gpu);
		}
	}
}

void setDevices(LibvirtXMLGenerator::VirtualMachine &vm,
				cxxopts::ParseResult &result) {

	setDisk(vm, result);
	setRemoteDisk(vm, result);
	setController(vm, result);
	setHotDevUsb(vm, result);
	setHotDevPci(vm, result);
	setTpm(vm, result);
	setNetwork(vm, result);
}

void saveFile(LibvirtXMLGenerator::VirtualMachine &vm,
			  cxxopts::ParseResult &result) {

	std::string outputFile = result["output"].as<std::string>();
	std::ofstream outFile(outputFile);

	if (outFile.is_open()) {
		outFile << vm.getXml();

		outFile.close();

		std::cout << "String successfully written to file!" << std::endl;
	} else {
		throw std::runtime_error("Can't write the file");
	}
}

void setPM(LibvirtXMLGenerator::VirtualMachine &vm,
		   cxxopts::ParseResult &result) {

	vm.pm.suspend_to_mem = result["suspend-to-mem"].as<bool>();
	vm.pm.suspend_to_disk = result["suspend-to-disk"].as<bool>();
}

void setTpm(LibvirtXMLGenerator::VirtualMachine &vm,
			cxxopts::ParseResult &result) {

	if (result.count("emulated-tpm") && result.count("passthrough-tpm")) {
		throw std::invalid_argument("Only one TPM type is acceptable");
	} else {
		LibvirtXMLGenerator::Elements::Devices::TpmElements::Tpm tpm;
		if (result.count("emulated-tpm")) {
			std::vector<std::string> tpmVector =
				result["emulated-tpm"].as<std::vector<std::string>>();
			tpm.model = tpmVector[0];
			LibvirtXMLGenerator::Elements::Devices::TpmElements::
				EmulatedTpmBackend backend;
			backend.version = tpmVector[1];
			tpm.backend = backend;
			vm.devices.tpm = tpm;
		} else if (result.count("passthrough-tpm")) {
			std::vector<std::string> tpmVector =
				result["passthrough-tpm"].as<std::vector<std::string>>();

			tpm.model = tpmVector[0];
			LibvirtXMLGenerator::Elements::Devices::TpmElements::
				PassthroughTPMBackend backend;
			backend.hostsPath = tpmVector[1];
			tpm.backend = backend;
			vm.devices.tpm = tpm;
		}
	}
}

void setNetwork(LibvirtXMLGenerator::VirtualMachine &vm,
				cxxopts::ParseResult &result) {
	LibvirtXMLGenerator::Elements::Devices::NetworkElements::Network network;

	if (result.count("nat-network")) {

		std::string networkVector = result["nat-network"].as<std::string>();

		LibvirtXMLGenerator::Elements::Devices::NetworkElements::NATSource
			source;
		int numNetworks = result.count("nat-network");
		for (int i = 0; i < numNetworks; i++) {
			source.network = networkVector;
			network.source = source;
			vm.devices.networks.push_back(network);
		}
	}
	if (result.count("nat-network-mac")) {

		std::vector<std::string> networkVector =
			result["nat-network-mac"].as<std::vector<std::string>>();
		LibvirtXMLGenerator::Elements::Devices::NetworkElements::NATSource
			source;
		int numNetworks = result.count("nat-network-mac") * 2;
		for (int i = 0; i < numNetworks; i += 2) {
			source.network = networkVector[i];
			network.mac = networkVector[i + 1];
			network.source = source;
			vm.devices.networks.push_back(network);
		}
	}
	if (result.count("bridge-network")) {

		std::string networkVector = result["bridge-network"].as<std::string>();

		LibvirtXMLGenerator::Elements::Devices::NetworkElements::BridgeSource
			source;
		int numNetworks = result.count("bridge-network");
		for (int i = 0; i < numNetworks; i++) {
			source.bridge = networkVector[i];
			network.source = source;
			vm.devices.networks.push_back(network);
		}
	}
	if (result.count("bridge-network-mac")) {

		std::vector<std::string> networkVector =
			result["bridge-network-mac"].as<std::vector<std::string>>();
		LibvirtXMLGenerator::Elements::Devices::NetworkElements::BridgeSource
			source;
		int numNetworks = result.count("bridge-network-mac") * 2;
		for (int i = 0; i < numNetworks; i += 2) {
			source.bridge = networkVector[i];
			network.mac = networkVector[i + 1];
			network.source = source;
			vm.devices.networks.push_back(network);
		}
	}
	if (result.count("direct-network")) {

		std::vector<std::string> networkVector =
			result["direct-network"].as<std::vector<std::string>>();
		LibvirtXMLGenerator::Elements::Devices::NetworkElements::DirectSource
			source;
		int numNetworks = result.count("direct-network") * 2;
		for (int i = 0; i < numNetworks; i += 2) {
			source.mode = networkVector[i];
			source.dev = networkVector[i + 1];
			network.source = source;
			vm.devices.networks.push_back(network);
		}
	}
	if (result.count("direct-network-mac")) {

		std::vector<std::string> networkVector =
			result["direct-network-mac"].as<std::vector<std::string>>();
		LibvirtXMLGenerator::Elements::Devices::NetworkElements::DirectSource
			source;
		int numNetworks = result.count("direct-network-mac") * 3;
		for (int i = 0; i < numNetworks; i += 3) {
			source.mode = networkVector[i];
			source.dev = networkVector[i + 1];
			network.mac = networkVector[i + 2];
			network.source = source;
			vm.devices.networks.push_back(network);
		}
	}
}
