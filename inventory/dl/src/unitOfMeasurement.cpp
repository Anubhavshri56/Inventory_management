#include<dl/uom>
#include<dl/iuom>
#include<iostream>
using namespace inventory;
using namespace data_layer;
using namespace std;
unitOfMeasurement::unitOfMeasurement()
{
this->code=0;
this->title="";
}
unitOfMeasurement::unitOfMeasurement(int code,string title)
{
this->code=code;
this->title=title;
}
unitOfMeasurement::unitOfMeasurement(const unitOfMeasurement &other)
{
this->code=other.code;
this->title=other.title;
}
unitOfMeasurement::~unitOfMeasurement()
{
// do nothing
}
void unitOfMeasurement::setCode(int code)
{
this->code=code;
}
int unitOfMeasurement::getCode() const
{
return this->code;
}
void unitOfMeasurement::setTitle(string title)
{
this->title=title;
}
string unitOfMeasurement::getTitle() const
{
return this->title;
}
int unitOfMeasurement::titleLength()
{
return this->title.size();
}
abc::IUnitOfMeasurement & unitOfMeasurement::operator=(const abc::IUnitOfMeasurement &other)
{
this->code=other.getCode();
this->title=other.getTitle();
return *this;
}
int unitOfMeasurement::operator==(const abc::IUnitOfMeasurement &other)
{
return this->code==other.getCode();
}
int unitOfMeasurement::operator!=(const abc::IUnitOfMeasurement &other)
{
return this->code!=other.getCode();
}
int unitOfMeasurement::operator>(const abc::IUnitOfMeasurement &other)
{
return this->code>other.getCode();
}
int unitOfMeasurement::operator<(const abc::IUnitOfMeasurement &other)
{
return this->code<other.getCode();
}
int unitOfMeasurement::operator>=(const abc::IUnitOfMeasurement &other)
{
return this->code>=other.getCode();
}
int unitOfMeasurement::operator<=(const abc::IUnitOfMeasurement &other)
{
return this->code<=other.getCode();
}