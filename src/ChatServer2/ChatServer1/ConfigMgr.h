#pragma once
#include "const.h"

struct SectionInfo {
	SectionInfo() {}
	~SectionInfo() {
		_sectionDatas.clear();
	}

	SectionInfo(const SectionInfo& src) {
		_sectionDatas = src._sectionDatas;
	}
	SectionInfo& operator=(const SectionInfo& src) {
		if (this != &src) {
			_sectionDatas = src._sectionDatas;
			return *this;
		}
		else {
			return *this;
		}
	}

	std::map<std::string, std::string> _sectionDatas;

	//重载[]操作符，方便访问
	std::string operator[](const std::string& key) {
		if (_sectionDatas.find(key) == _sectionDatas.end()) {
			return "";
		}
		return _sectionDatas[key];
	}
};

class ConfigMgr
{
public:
	~ConfigMgr();
	//拷贝构造
	ConfigMgr(const ConfigMgr& src);
	//赋值运算符重载
	ConfigMgr& operator=(const ConfigMgr& src);
	SectionInfo operator[](const std::string& sectionName);

	static ConfigMgr& GetInstance();

private:
	ConfigMgr();
	std::map<std::string, SectionInfo> _configMap;
};

