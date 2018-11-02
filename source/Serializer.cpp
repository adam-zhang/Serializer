//#include <WinSock2.h>
#include <algorithm>
#include "Serializer.h"

using namespace std;

//#pragma comment(lib, "ws2_32.lib")

Serializer::Serializer(void)
	: current_(0)
{
}


Serializer::~Serializer(void)
{
}

bool Serializer::serialize( unsigned int value)
{
	char* c = (char*)&value;
	vector<char> v(c, c + sizeof(unsigned int));
	serialize(v);
	return true;
}

bool Serializer::serialize(unsigned short value)
{
	char* c = (char*)&value;
	vector<char> v(c, c + sizeof(unsigned short));
	serialize(v);
	return true;
}

bool Serializer::serialize(unsigned char value)
{
	data_.push_back(value);
	return true;
}

bool Serializer::serialize(const string& s)
{
	size_t size = s.size();
	serialize(size);
	for(auto i = 0; i != size; ++i)
		serialize((unsigned char)s[i]);
	return true;
}

bool Serializer::deserialize(string& s)
{
	size_t size;
	deserialize(size);
	for(auto i = 0; i != size; ++i)
	{
		char c;
		deserialize((unsigned char&)c);
		s.push_back(c);
	}
	return true;
}

bool Serializer::serialize(unsigned long long value)
{
	unsigned int temp = (value << 32) >> 32;
	serialize(temp);
	temp = value >> 32;
	serialize(temp);
	return true;
}

void Serializer::serialize(const vector<char>& v)
{
	for(auto i = v.begin(); i != v.end(); ++i)
		data_ .push_back(*i);
}

bool Serializer::deserialize(unsigned char& value)
{
	value = data_[current_];
	++current_;
	return true;
}

bool Serializer::deserialize(unsigned short& value)
{
	size_t size = sizeof(unsigned short);
	unsigned short* s = (unsigned short*)&data_[current_];
	value = *s;
	current_ += size;
	return true;
}

bool Serializer::deserialize(unsigned int& value)
{
	size_t size = sizeof(unsigned int);
	unsigned int* i = (unsigned int*)&data_[current_];
	value = *i;
	current_ += size;
	return true;
}

bool Serializer::deserialize(unsigned long long& value)
{
	unsigned int high;
	deserialize(high);
	unsigned int low;
	deserialize(low);
	value = high << 32 + low;
	return true;
}