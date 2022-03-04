#include<bl/blexception>
using namespace inventory;
using namespace business_layer;
using namespace std;
BLException::BLException()
{
this->genericException="";
}
BLException::BLException(string genericException)
{
this->genericException=genericException;
}
BLException::BLException(const BLException &other)
{
this->genericException=other.genericException;
this->exceptions=other.exceptions;
}
BLException & BLException::operator=(const BLException &other)
{
this->genericException=other.genericException;
this->exceptions=other.exceptions; 
return *this;
}
BLException::~BLException() throw()
{
// do nothing
}
const char * BLException::what() const throw()
{
return this->genericException.c_str();
}
int BLException::hasGenericException()
{
return this->genericException.length()>0;
}
void BLException::setGenericException(string genericException)
{
this->genericException=genericException;
}
string BLException::getGenericException()
{
return this->genericException;
}
void BLException::addPropertyException(string property,string exception)
{
this->exceptions.insert(pair<string,string>(property,exception));
}
string BLException::getPropertyException(string property)
{
map<string,string>::iterator i=this->exceptions.find(property);
if(i==this->exceptions.end()) return string("");
return i->second;
}
int BLException::hasPropertyException(string property)
{
return this->getPropertyException(property).length()>0;
}
int BLException::hasPropertyExceptions()
{
return this->getPropertyExceptionCount()>0;
}
int BLException::hasExceptions()
{
int exceptionCount=0;
if(this->genericException.length()>0) exceptionCount++;
if(this->exceptions.size()>0) exceptionCount++;
return exceptionCount>0;
}
int BLException::getPropertyExceptionCount()
{
return this->exceptions.size();
}