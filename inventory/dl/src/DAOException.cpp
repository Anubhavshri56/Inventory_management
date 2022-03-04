#include<dl/daoexception>
using namespace inventory;
using namespace data_layer;
using namespace std;
DAOException::DAOException()
{
this->message="";
}
DAOException::DAOException(string message)
{
this->message=message;
}
DAOException::DAOException(const DAOException &other)
{
this->message=other.message;
}
DAOException & DAOException::operator=(const DAOException &other)
{
this->message=other.message;
return *this;
}
DAOException::~DAOException() throw()
{
// do nothing
}
const char * DAOException::what() const throw()
{
return this->message.c_str();
}