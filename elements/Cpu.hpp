#ifndef CPU_HPP
#define CPU_HPP

#include <format>
#include <string>
#include <vector>
#include "XmlAble.hpp"

struct Cpu : XmlAble {
	struct CpuPin : XmlAble {
		struct VCpuPin : XmlAble {
			int vcpu;
			int cpuset;

			std::string getXml() override {
				return std::format("<vcpupin vcpu=\"{}\" cpuset=\"{}\"/>", vcpu,
								   cpuset);
			}
		};

		struct IOThreadPin : XmlAble {
			int ioThread;
			int cpuset;

			std::string getXml() override {
				return std::format(
					"<iothreadpin iothread=\"{}\" cpuset=\"{}\"/>", ioThread,
					cpuset);
			}
		};

		std::string placement = "static";
		int quantVcpu;
		std::vector<VCpuPin> cpus;
		std::vector<IOThreadPin> ioThreads;
		int emulatorPin;

		std::string getXml() override {
			std::string xml = std::format("<vcpu placement=\"{}\">{}</vcpu>",
										  placement, quantVcpu);
			if (placement == "static") {
				xml.append(std::format("<cputune>"));
				for (VCpuPin cpu : cpus) {
					xml.append(cpu.getXml());
				}
				for (IOThreadPin ioThread : ioThreads) {
					xml.append(ioThread.getXml());
				}
				xml.append(
					std::format("<emulatorpin cpuset=\"{}\"/>", emulatorPin));
				xml.append(std::format("</cputune>"));
			}
			// ToDo Raise Error
			return xml;
		}
	};

	struct Topology : XmlAble {
		int sockets;
		int cores;
		int threads;

		std::string getXml() override {
			return std::format(
				"<topology sockets=\"{}\" cores=\"{}\" threads=\"{}\" />",
				sockets, cores, threads);
		}
	};
	
	struct Feature : XmlAble {
		std::string policy = "require";
		std::string name;

		std::string getXml() override {
			return std::format("<feature policy=\"{}\" name=\"{}\" />", policy,
							   name);
		}
	};

	std::string mode = "host-passthrough";
	std::string cache_mode = "passthrough";
	std::string check = "none";
	Topology topology;
	int cpuNum;
	CpuPin cpupin;
	std::vector<Feature> features;

	std::string getXml() override {
		std::string xml = std::format(
			"{}<cpu mode=\"{}\" check=\"{}\">{}<cache mode=\"{}\"/>",
			cpupin.getXml(), mode, check, topology.getXml(), cache_mode);
		for (Feature feature : features) {
			xml.append(feature.getXml());
		}
		xml.append(std::format("</cpu>"));
		return xml;
	}
};
#endif