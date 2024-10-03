#include "elements.hpp"
#include "virtualMachine.hpp"
#include <iostream>
#include <fstream>

int main() {
	VirtualMachine vm;

	// Domain
	vm.domain.name = "Win11";
	vm.domain.description = "Um teste";

	// OS
	Os::BootDisk bootdisk;
	vm.os.bootdisk = bootdisk;

	// CPU
	vm.cpu.cpuNum = 10;
	vm.cpu.cpupin.quantVcpu = 10;
	Cpu::CpuPin::VCpuPin vcpupin;

	vcpupin.vcpu = 0;
	vcpupin.cpuset = 1;
	vm.cpu.cpupin.cpus.push_back(vcpupin);

	vcpupin.vcpu = 1;
	vcpupin.cpuset = 7;
	vm.cpu.cpupin.cpus.push_back(vcpupin);

	vcpupin.vcpu = 2;
	vcpupin.cpuset = 2;
	vm.cpu.cpupin.cpus.push_back(vcpupin);

	vcpupin.vcpu = 3;
	vcpupin.cpuset = 8;
	vm.cpu.cpupin.cpus.push_back(vcpupin);

	vcpupin.vcpu = 4;
	vcpupin.cpuset = 3;
	vm.cpu.cpupin.cpus.push_back(vcpupin);

	vcpupin.vcpu = 5;
	vcpupin.cpuset = 9;
	vm.cpu.cpupin.cpus.push_back(vcpupin);

	vcpupin.vcpu = 6;
	vcpupin.cpuset = 4;
	vm.cpu.cpupin.cpus.push_back(vcpupin);

	vcpupin.vcpu = 7;
	vcpupin.cpuset = 10;
	vm.cpu.cpupin.cpus.push_back(vcpupin);

	vcpupin.vcpu = 8;
	vcpupin.cpuset = 5;
	vm.cpu.cpupin.cpus.push_back(vcpupin);

	vcpupin.vcpu = 9;
	vcpupin.cpuset = 11;
	vm.cpu.cpupin.cpus.push_back(vcpupin);

	Cpu::CpuPin::IOThreadPin ioThreadPin;

	ioThreadPin.ioThread = 1;
	ioThreadPin.cpuset = 1;
	vm.cpu.cpupin.ioThreads.push_back(ioThreadPin);

	vm.cpu.cpupin.emulatorPin = 0;

	Cpu::Topology topology;
	topology.cores = 5;
	topology.sockets = 1;
	topology.threads = 2;
	vm.cpu.topology = topology;

	Cpu::Feature feature;
	feature.name = "topoext";
	vm.cpu.features.push_back(feature);

	// Memory
	vm.memory.memory = 10240;

	// SystemClock
	SystemClock::Timer timer;

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

	// Devices

	// Disk
	Device::DiskLocal disco;
	disco.source.file = "/vm_disk/vm_teste.qcow2";
	disco.driver.type = "qcow2";
	disco.target.dev = "sdb";
	disco.target.bus = "sata";
	vm.devices.disks.push_back(disco);

	// Controller
	for (int i = 0; i < 6; i++) {
		Device::Controller controllerPci;
		controllerPci.type = "pci";
		controllerPci.model = "pcie-root-port";
		vm.devices.controllers.push_back(controllerPci);
	}

	// HotDev PCI
	Device::Hotdev::PCISource gpu;
	gpu.bus = 3;
	gpu.domain = 0;
	gpu.function = 0;
	gpu.slot = 0;
	
	// Create an ofstream object for writing to a file
    std::ofstream outFile("output.xml");

    // Check if the file was opened successfully
    if (outFile.is_open()) {
        // Write the string to the file
        outFile << vm.getXml();

        // Close the file
        outFile.close();

        std::cout << "String successfully written to file!" << std::endl;
    } else {
        std::cerr << "Failed to open the file!" << std::endl;
    }
}
