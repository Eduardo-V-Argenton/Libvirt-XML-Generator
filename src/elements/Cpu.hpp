#ifndef CPU_HPP
#define CPU_HPP

#include "../XmlAble.hpp"
#include "../Checkable.hpp"
#include <string>
#include <vector>

namespace LibvirtXMLGenerator {
namespace Elements {
namespace CpuElement {

struct Cpu : LibvirtXMLGenerator::Interfaces::XmlAble,LibvirtXMLGenerator::Interfaces::Checkable {
	struct CpuPin : XmlAble {
		struct VCpuPin : XmlAble {
			int vcpu;
			int cpuset;

			std::string getXml() const override;
		};

		struct IOThreadPin : XmlAble {
			int ioThread;
			int cpuset;

			std::string getXml() const override;
		};

		std::string placement = "static";
		int quantVcpu;
		std::vector<VCpuPin> cpus;
		std::vector<IOThreadPin> ioThreads;
		int emulatorPin;

		std::string getXml() const override;
	};

	struct Topology : XmlAble {
		int sockets;
		int cores;
		int threads;

		std::string getXml() const override;
	};

	struct Feature : XmlAble {
		std::string policy = "require";
		std::string name;

		std::string getXml() const override;
	};

	std::string mode = "host-passthrough";
	std::string cache_mode = "passthrough";
	std::string cpuCheck = "none";
	Topology topology;
	CpuPin cpupin;
	std::vector<Feature> features;

	std::string getXml() const override;
	void check() const override;
};
} // namespace CpuElement
} // namespace Elements
} // namespace LibvirtXMLGenerator

#endif
