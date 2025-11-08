#include "ConfigMgr.h"

ConfigMgr::~ConfigMgr()
{
	_configMap.clear();
}
ConfigMgr::ConfigMgr()
{
	boost::filesystem::path configFilePath = boost::filesystem::current_path() / "config.ini";
	if (!boost::filesystem::exists(configFilePath)) {
		std::cerr << "Config file not found: " << configFilePath.string() << std::endl;
		return;
	}
	boost::property_tree::ptree pt;
	boost::property_tree::read_ini(configFilePath.string(), pt);
	for (const auto& section : pt) {
		SectionInfo sectionInfo;
		for (const auto& key_value : section.second) {
			sectionInfo._sectionDatas[key_value.first] = key_value.second.get_value<std::string>();
		}
		_configMap[section.first] = sectionInfo;
	}
	//¥Ú”°
	for (auto& sectionPair : _configMap) {
		std::cout << "[" << sectionPair.first << "]" << std::endl;
		for (auto& keyValuePair : sectionPair.second._sectionDatas) {
			std::cout << keyValuePair.first << " = " << keyValuePair.second << std::endl;
		}
	}
}
ConfigMgr::ConfigMgr(const ConfigMgr& src)
{
	_configMap = src._configMap;
}

ConfigMgr& ConfigMgr::operator=(const ConfigMgr& src)
{
	if (this != &src) {
		_configMap = src._configMap;
		return *this;
	}
	else {
		return *this;
	}
}

SectionInfo ConfigMgr::operator[](const std::string& sectionName)
{
	if (_configMap.find(sectionName) == _configMap.end()) {
		return SectionInfo();
	}
	return _configMap[sectionName];
}

ConfigMgr& ConfigMgr::GetInstance()
{
	static ConfigMgr configMgr;
	return configMgr;
}

