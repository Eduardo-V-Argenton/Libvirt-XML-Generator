#include "VirtualMachine.hpp"

#include "elements/Domain.hpp"
#include "elements/Memory.hpp"
#include "elements/Cpu.hpp"
#include "elements/Os.hpp"
#include "elements/Features.hpp"
#include "elements/SystemClock.hpp"
#include "elements/PowerManagement.hpp"
#include "elements/Devices.hpp"

#include "elements/devices/Console.hpp"
#include "elements/devices/Controller.hpp"
#include "elements/devices/Disk.hpp"
#include "elements/devices/Emulator.hpp"
#include "elements/devices/Filesystem.hpp"
#include "elements/devices/GraphicalFrameBuffer.hpp"
#include "elements/devices/HotDev.hpp"
#include "elements/devices/Network.hpp"
#include "elements/devices/Tpm.hpp"
#include "elements/devices/Video.hpp"

#include <cxxopts.hpp>
#include <iostream>
#include <string>
#include <vector>

//ToDo Invalid Argument handling
int main(int argc, char* argv[]) {
    cxxopts::Options options("libvirt-xml-generator", "Simple Program to generate a XML that can be used with libvirt");

    options.add_options()
        ("h,help", 
            "Show help")
        ("n,name",
            "VM's name", 
                cxxopts::value<std::string>()->default_value("VM"))
        ("t,type",
            "VM's type, default value is KVM", 
                cxxopts::value<std::string>()->default_value("kvm"))
        ("description",
            "VM's description", 
                cxxopts::value<std::string>())
        ("m,memory",
            "VM's memory's size in MB", 
                cxxopts::value<std::string>()->default_value("1024"))
        ("cpu-mode",
            "VM's cpu-mode", 
                cxxopts::value<std::string>()->default_value("host-passthrough"))
        ("cpu-topology",
            "VM's cpu topology, format like sockets,cores,threads", 
                cxxopts::value<std::vector<int>>()->default_value("1,1,1"))
        ("auto-cpu-distribution",
            "Enable the core distribution to be automatic", 
                cxxopts::value<bool>()->default_value("false"))
        ("quant-cpu-emulator",
            "Set the quantity of CPUs that'll be used to emulate/control the VM", 
                cxxopts::value<int>()->default_value("1"))
        ("quant-cpu-io",
            "Set the quantity of CPUs that'll be used to control IO between the Host and the VM", 
                cxxopts::value<int>()->default_value("1"))
        ("efi",
            "Enable VM's EFI", 
                cxxopts::value<bool>()->default_value("false"))
        ("arch",
            "VM's architecture", 
                cxxopts::value<std::string>()->default_value("x86_64"))
        ("bootmenu-time",
            "Set BootMenu timeout, if 0 disable bootMenu", 
                cxxopts::value<int>()->default_value("0"))
        ("d,disk",
            "Add a virtual disk, format like format,bus,file. If a file isn't find it will be create",
                cxxopts::value<std::vector<std::string>>()->default_value("qcow2,sata,disk.qcow2"))
        ("usb-device",
            "Add a usb device, pass the id",
                cxxopts::value<std::string>())
        ("pci-device",
            "Add a pci device, format like domain,bus,slot,function",
                cxxopts::value<std::vector<int>>());

    try {
        auto result = options.parse(argc, argv);

        if (result.count("help")) {
            std::cout << options.help() << std::endl;
            return 0;
        }

        LibvirtXMLGenerator::Main::VirtualMachine vm;
       
    	// Domain
        vm.domain.name = result["name"].as<std::string>();
        
        vm.domain.domain = result["type"].as<std::string>();
        
        if (result.count("description")) {
            vm.domain.name = result["description"].as<std::string>();
        }
        
        // Memory
        vm.memory.memory = result["memory"].as<int>();
        
    	// CPU
        vm.cpu.mode = result["cpu-mode"].as<std::string>();
        std::vector<int> cpuTopology = result["cpu-topology"].as<std::vector<int>>();
        int quantVcpu = cpuTopology[0] * cpuTopology[1] * cpuTopology[2];
        bool autoCpuDist = result["auto-cpu-distribution"].as<bool>();
        if (!autoCpuDist) {
            vm.cpu.mode = "static";
            int quantCpuEmulator = result["quant-cpu-emulator"].as<int>();
            int quantCpuIO = result["quant-cpu-io"].as<int>();
            vm.cpu.cpupin.quantVcpu = quantVcpu;
        	LibvirtXMLGenerator::Elements::CpuElement::Cpu::CpuPin::VCpuPin vcpupin;
            
            //ToDo AutoCPU pin using lscpu -e -J
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
            
        	LibvirtXMLGenerator::Elements::CpuElement::Cpu::CpuPin::IOThreadPin ioThreadPin;
            
        	ioThreadPin.ioThread = 1;
        	ioThreadPin.cpuset = 1;
        	vm.cpu.cpupin.ioThreads.push_back(ioThreadPin);
            
        	vm.cpu.cpupin.emulatorPin = 0;
        }else{
            vm.cpu.mode = "auto";
        }
        
    	LibvirtXMLGenerator::Elements::CpuElement::Cpu::Topology topology;
    	topology.sockets = cpuTopology[0];
    	topology.cores = cpuTopology[1];
    	topology.threads = cpuTopology[2];
    	vm.cpu.topology = topology;
        
        //ToDo Auto Features
    	LibvirtXMLGenerator::Elements::CpuElement::Cpu::Feature feature;
    	feature.name = "topoext";
    	vm.cpu.features.push_back(feature);
        
        
    	// OS
    	LibvirtXMLGenerator::Elements::OsElements::Os::BootDisk bootdisk;
    	vm.os.bootdisk = bootdisk;
        if (result["efi"].as<bool>()) {
            vm.os.firmware = "efi";
        }else{
            vm.os.firmware = "bios";
        }
        
        vm.os.type.arch = result["arch"].as<std::string>();
     
        int bootMenuTimeOut = result["bootmenu"].as<int>();
        if( bootMenuTimeOut== 0) {
            vm.os.bootmenu.enable = false; 
        }else {
            vm.os.bootmenu.enable = true; 
            vm.os.bootmenu.timeout = bootMenuTimeOut;
        }
        
    	// ToDo Auto SystemClock
    	LibvirtXMLGenerator::Elements::SystemClockElements::SystemClock::Timer timer;
        
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
        
        // ToDo DEvices
    	// Devices
        
    	// Disk
    	LibvirtXMLGenerator::Elements::Devices::DiskElements::DiskLocal disco;
    	disco.source.file = "/vm_disk/vm_teste.qcow2";
    	disco.driver.type = "qcow2";
    	disco.target.dev = "sdb";
    	disco.target.bus = "sata";
    	vm.devices.disks.push_back(disco);
        
    	// Controller
    	for (int i = 0; i < 6; i++) {
    		LibvirtXMLGenerator::Elements::Devices::ControllerElements::Controller controllerPci;
    		controllerPci.type = "pci";
    		controllerPci.model = "pcie-root-port";
    		vm.devices.controllers.push_back(controllerPci);
    	}
        
    	// HotDev PCI
    	LibvirtXMLGenerator::Elements::Devices::HotDevElements::HotDevPCISource gpu;
    	gpu.bus = 3;
    	gpu.domain = 0;
    	gpu.function = 0;
    	gpu.slot = 0;
    	vm.devices.hotDevPCIs.push_back(gpu);
    	
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
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
