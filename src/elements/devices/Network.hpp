// ToDo
#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "../../XmlAble.hpp"
#include <string>
#include <variant>
namespace LibvirtXMLGenerator {
namespace Elements {
namespace Devices {
namespace NetworkElements {

struct NetworkSource{
    virtual std::string getInterface() const = 0; 
};

struct BridgeSource : Interfaces::XmlAble, NetworkSource{
	std::string bridge;

	std::string getXml() const override;
	std::string getInterface() const override;
};

struct NATSource : Interfaces::XmlAble, NetworkSource{
	std::string network;

	std::string getXml() const override;
	std::string getInterface() const override;
};

struct DirectSource : Interfaces::XmlAble, NetworkSource{
	std::string mode;
	std::string dev;
	
	std::string getXml() const override;
	std::string getInterface() const override;
};

struct Network : Interfaces::XmlAble {
	std::string model = "virtio";
	std::string mac;
	std::variant<BridgeSource, NATSource, DirectSource> source;

	std::string getXml() const override;
};

} // namespace NetworkElements
} // namespace Devices
} // namespace Elements
} // namespace LibvirtXMLGenerator
#endif
