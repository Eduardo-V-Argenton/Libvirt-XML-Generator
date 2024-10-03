#ifndef ELEMENTS_HPP
#define ELEMENTS_HPP

#include <format>
#include <string>
#include <variant>
#include <vector>

using namespace std;

struct XmlAble {
	virtual std::string getXml() = 0;
};

struct Domain : XmlAble {
	std::string domain = "kvm";
	std::string name;
	std::string description;

	std::string getXml() override {
		return std::format(
			"<domain "
			"type=\"{}\"><name>{}</name><description>{}</description>",
			domain, name, description);
	};
};

struct Os : XmlAble {
	struct BootDisk : XmlAble {
		std::string type = "hd";
		// disk??

		std::string getXml() override {
			return std::format("<boot dev=\"{}\"/>", type);
		}
	};

	struct BootMenu : XmlAble {
		bool enable = false;
		int timeout = 2;

		std::string getXml() override {
			return std::format("<bootmenu enable=\"{}\" timeout=\"{}\"/>",
							   enable ? "yes" : "no", timeout);
		}
	};

	struct Type : XmlAble {
		std::string arch = "x86_64";
		std::string machine = "q35";
		std::string type = "hvm";

		std::string getXml() override {
			return std::format("<type arch=\"{}\" machine=\"{}\">{}</type>",
							   arch, machine, type);
		}
	};

	std::string firmware = "efi";
	Type type;
	std::string secure = "no";
	BootDisk bootdisk;
	BootMenu bootmenu;

	std::string getXml() override {
		return std::format("<os firmware=\"{}\">{}{}{}</os>", firmware,
						   type.getXml(), bootdisk.getXml(), bootmenu.getXml());
	}
};

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
		vector<VCpuPin> cpus;
		vector<IOThreadPin> ioThreads;
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
	vector<Feature> features;

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

struct Memory : XmlAble {
	std::string unit = "M";
	int memory;

	std::string getXml() override {
		return std::format("<memory unit=\"{}\">{}</memory>", unit, memory);
	}
};

struct Features : XmlAble {
	struct SpinLocks : XmlAble {
		bool enabled = true;
		int retries = 8191;

		std::string getXml() override {
			return std::format("<spinlocks state=\"{}\" retries=\"{}\"/>",
							   enabled ? "on" : "off", retries);
		}
	};
	struct HyperV : XmlAble {
		bool relaxed = true;
		bool vapic = true;
		SpinLocks spinLocks;

		std::string getXml() override {
			return std::format("<hyperv><relaxed state=\"{}\"/><vapic "
							   "state=\"{}\"/>{}</hyperv>",
							   relaxed ? "on" : "off", vapic ? "on" : "off",
							   spinLocks.getXml());
		}
	};
	bool acpi = true;
	bool apic = true;
	bool vmport = false;
	std::string ioapic = "kvm";
	HyperV hyperv;

	std::string getXml() override {
		std::string xml = std::format("<features>");

		if (acpi) {
			xml.append("<acpi/>");
		}
		if (apic) {
			xml.append("<apic/>");
		}
		// ToDo dont append if not using hyperV
		xml.append(hyperv.getXml());
		xml.append(
			std::format("<vmport state=\"{}\"/>", vmport ? "on" : "off"));
		xml.append(std::format("</features>"));

		return xml;
	}
};

struct SystemClock : XmlAble {
	struct Timer : XmlAble {
		std::string name;
		std::string tickpolicy = "";
		bool present = true;

		std::string getXml() override {
			std::string xml = std::format("<timer name=\"{}\" present=\"{}\"",
										  name, present ? "yes" : "no");
			if (tickpolicy != "") {
				xml.append(std::format(" tickpolicy=\"{}\"", tickpolicy));
			}
			xml.append(std::format("/>"));
			return xml;
		}
	};

	std::string offset = "localtime";
	vector<Timer> timers;

	std::string getXml() override {
		std::string xml = std::format("<clock offset=\"{}\">", offset);
		for (Timer timer : timers) {
			xml.append(timer.getXml());
		}
		xml.append(std::format("</clock>"));
		return xml;
	}
};

struct PowerManagement : XmlAble {
	bool suspend_to_disk = false;
	bool suspend_to_mem = false;

	std::string getXml() override {
		return std::format(
			"<pm><suspend-to-mem enabled=\"{}\"/><suspend-to-disk "
			"enabled=\"{}\"/></pm>",
			suspend_to_mem ? "yes" : "no", suspend_to_disk ? "yes" : "no");
	}
};

struct Emulator : XmlAble {
	std::string emulator;

	std::string getXml() override {
		return std::format("<emulator>{}</emulator>", emulator);
	}
};

struct Disk : XmlAble {
  protected:
	Disk() = default;

  public:
	struct Source : XmlAble {
		std::string getXml() override { return ""; }
	};

	struct Driver : XmlAble {
		std::string name = "qemu";
		std::string type;

		std::string getXml() override {
			return std::format("<driver name=\"{}\" type=\"{}\" />", name,
							   type);
		}
	};

	struct Target : XmlAble {
		std::string dev;
		std::string bus;

		std::string getXml() override {
			return std::format("<target dev=\"{}\" bus=\"{}\" />", dev, bus);
		}
	};

	std::string type = "file";
	std::string device = "disk";
	// std::string snapshot = "";  /ToDo implementar snapshot
	bool readonly = false;
	Target target;
	Source source;
	Driver driver;

	std::string getXml() override {
		return std::format("<disk type=\"{}\" device=\"{}\">{}{}{}{}</disk>",
						   type, device, driver.getXml(), source.getXml(),
						   driver.getXml(), readonly ? "</readonly>" : "");
	}
};

struct DiskLocal : Disk {

	struct Source : XmlAble {
		std::string file;

		std::string getXml() override {
			return std::format("<source file=\"{}\" />", file);
		}
	};
};

struct DiskNetwork : Disk {

	struct Source : XmlAble {
		struct Host : XmlAble {
			std::string name = "";
			std::string port = "";

			std::string getXml() override {
				return std::format("<host name=\"{}\" port=\"{}\" />", name,
								   port);
			}
		};

		struct Auth : XmlAble {
			std::string username = "";
			std::string type = "";
			std::string usage = "";

			std::string getXml() override {
				return std::format("<auth username=\"{}\" ><secret type=\"{}\" "
								   "usage=\"{}\" /></auth>",
								   username, type, usage);
			}
		};

		std::string protocol;
		std::string name;
		std::string query = "";
		bool ssl;
		Host host;
		Auth auth;

		std::string getXml() override {
			std::string xml = std::format("<source protocol=\"{}\" name=\"{}\"",
										  protocol, name);

			if (query != "") {
				xml.append(std::format(" query=\"{}\" ", query));
			}
			xml.append(">");
			xml.append(host.getXml());
			if (auth.username != "") {
				xml.append(auth.getXml());
			}
			xml.append(std::format("<ssl verify=\"{}\"/>", ssl ? "yes" : "no"));
			xml.append("</source>");
			return xml;
		}
	};
};

// ToDo
struct Filesystem {};

struct Controller {
	struct USB {
		std::string model;
		int ports;
	};

	struct Pci {
		std::string model;
	};
};

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

using Devices =
	std::variant<Emulator, Disk, Filesystem, Controller::Pci, Controller::USB,
				 Hotdev::PCISource, Hotdev::USBSource, Video,
				 GraphicalFrameBuffer, Console, Network, TPM>;

#endif
