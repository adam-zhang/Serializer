#pragma once
#include <string>
#include <vector>
#include <sstream>

class Serializer
{
public:
	Serializer(void);
	~Serializer(void);
public:
	bool serialize(unsigned int value);
	bool serialize(unsigned short);
	bool serialize(unsigned long long);
	bool serialize(unsigned char);
	bool serialize(const std::string&);
	bool deserialize(unsigned char& c);
	bool deserialize(unsigned short& c);
	bool deserialize(unsigned int&);
	bool deserialize(unsigned long long&);
	bool deserialize(std::string& s);
private:
	std::vector<char> data_;
	size_t current_ ;
private:
	void serialize(const std::vector<char>& );
};

