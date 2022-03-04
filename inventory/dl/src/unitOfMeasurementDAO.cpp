#include<stdio.h>
#include<dl/iuom>
#include<dl/uom>
#include<dl/daoexception>
#include<dl/iuomdao>
#include<dl/uomdao>
#include<iostream>
#include<fstream>
#include<forward_list>
#include<string.h>
#include<common/stringutils>
using namespace std;
using namespace inventory;
using namespace data_layer;
using namespace stringutils;
void unitOfMeasurementDAO::add(abc::IUnitOfMeasurement *unitOfMeasurement)
{
if(!unitOfMeasurement)
{
DAOException exception("NULL value Passed");
throw exception;
}
const string vTitle=unitOfMeasurement->getTitle();
string title=trimmed(vTitle);
int vCode=unitOfMeasurement->getCode();
if(title.length()==0)
{
DAOException exception("Title required");
throw exception;
}
else if(title.length()>50)
{
DAOException exception("Title length exceeded");
throw exception;
}
else if(vCode!=0)
{
throw DAOException("wrong Code");
}
Header header;
_unitOfMeasurement _uom,_uomT;
fstream dataFile(FILE_NAME,ios::in | ios::out | ios::binary);
if(dataFile.fail())
{
ofstream dFile(FILE_NAME,ios::app | ios::binary);
header.lastGeneratedCode=1;
header.numberOfRecords=1;
dFile.write((char *)&header,sizeof(Header));
_uom.code=1;
strcpy(_uom.title,title.c_str());
dFile.write((char *)&_uom,sizeof(_unitOfMeasurement));
dFile.close();
unitOfMeasurement->setCode(1);
return;
}
dataFile.seekg(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.clear();
dataFile.seekg(0,ios::beg);
dataFile.seekp(0,ios::beg);
header.lastGeneratedCode=1;
header.numberOfRecords=1;
dataFile.write((char *)&header,sizeof(Header));
_uom.code=1;
strcpy(_uom.title,title.c_str());
dataFile.write((char *)&_uom,sizeof(_unitOfMeasurement));
dataFile.close();
unitOfMeasurement->setCode(1);
return;
}
while(1)
{
dataFile.read((char *)&_uomT,sizeof(_unitOfMeasurement));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_uomT.title,title.c_str())==0)
{
dataFile.close();
throw DAOException("Title Already Exists");
}
}
dataFile.clear();
header.lastGeneratedCode++;
header.numberOfRecords++;
dataFile.seekp(0,ios::beg);
dataFile.write((char *)&header,sizeof(Header));
_uom.code=header.lastGeneratedCode;
strcpy(_uom.title,title.c_str());
dataFile.seekp(0,ios::end);
dataFile.write((char *)&_uom,sizeof(_unitOfMeasurement));
dataFile.close();
unitOfMeasurement->setCode(header.lastGeneratedCode);
}
void unitOfMeasurementDAO::update(abc::IUnitOfMeasurement *unitOfMeasurement)
{
Header header;
_unitOfMeasurement _uom,_uomT;
int found=0,pos,code;
string title=trimmed(string(unitOfMeasurement->getTitle()));
code=unitOfMeasurement->getCode();
if(code<=0)
{
throw DAOException(string("Wrong Code"));
}
if(title.length()==0)
{
throw DAOException("Title required,length is zero");
}
else if(title.length()>50)
{
throw DAOException(string("Title lenght cannot exceed 50"));
}
fstream dataFile(FILE_NAME,ios::in | ios::out |ios::binary);
if(dataFile.fail())
{
throw DAOException("Unit of Measuremnet does not exist.");
}
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException("Unit of Measuremnet does not exist.");
}
if(header.numberOfRecords==0)
{
dataFile.close();
throw DAOException("Unit of Measuremnet does not exist.");
}
while(1)
{
pos=dataFile.tellg();
dataFile.read((char *)&_uom,sizeof(_unitOfMeasurement));
if(dataFile.fail()) break;
if(code==_uom.code)
{
found=1;
break;
}
}
if(found==0)
{
dataFile.close();
throw DAOException("Unit of Measuremnet does not exist.");
}
dataFile.clear();
dataFile.seekg(sizeof(Header),ios::beg);
while(1)
{
dataFile.read((char *)&_uom,sizeof(_unitOfMeasurement));
if(dataFile.fail()) break;
if(_uom.code!=code && compareStringIgnoreCase(_uom.title,title.c_str())==0)
{
dataFile.close();
throw DAOException("Unit of measurement already exist.");
}
}
dataFile.clear();
dataFile.seekp(pos,ios::beg);
strcpy(_uomT.title,title.c_str());
_uomT.code=code;
dataFile.write((char *)&_uomT,sizeof(_unitOfMeasurement));
dataFile.close();
}
void unitOfMeasurementDAO::remove(int code)
{
Header header;
_unitOfMeasurement _uom,_uomT;
int found=0,pos;
if(code<=0)
{
throw DAOException("Wrong code");
}
fstream dataFile(FILE_NAME,ios::in | ios::out |ios::binary);
if(dataFile.fail())
{
throw DAOException("Unit of Measuremnet does not exist.");
}
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException("Unit of Measuremnet does not exist.");
}
if(header.numberOfRecords==0)
{
dataFile.close();
throw DAOException("Unit of Measuremnet does not exist.");
}
while(1)
{
dataFile.read((char *)&_uom,sizeof(_unitOfMeasurement));
if(dataFile.fail()) break;
if(code==_uom.code)
{
found=1;
break;
}
}
if(found==0)
{
dataFile.close();
throw DAOException("Unit of Measuremnet does not exist.");
}
dataFile.seekg(sizeof(Header),ios::beg);
fstream tmpFile("tmp.tmp",ios::in | ios::out | ios::binary | ios::trunc);
header.numberOfRecords--;
tmpFile.write((char *)&header,sizeof(Header));
while(1)
{
dataFile.read((char *)&_uom,sizeof(_unitOfMeasurement));
if(dataFile.fail()) break;
if(code!=_uom.code)
{
tmpFile.write((char *)&_uom,sizeof(_unitOfMeasurement));
}
}
dataFile.close();
tmpFile.close();
dataFile.open(FILE_NAME,ios::in | ios::out | ios::binary | ios::trunc);
tmpFile.open("tmp.tmp",ios::in | ios::out | ios::binary);
tmpFile.read((char *)&header,sizeof(Header));
dataFile.write((char *)&header,sizeof(Header));
while(1)
{
tmpFile.read((char *)&_uom,sizeof(_unitOfMeasurement));
if(tmpFile.fail()) break;
dataFile.write((char *)&_uom,sizeof(_unitOfMeasurement));
}
dataFile.close();
tmpFile.close();
tmpFile.open("tmp.tmp",ios::trunc);
tmpFile.close();
}
abc::IUnitOfMeasurement * unitOfMeasurementDAO::getByCode(int code)
{
Header header;
_unitOfMeasurement _uom;
ifstream dataFile(FILE_NAME,ios::binary);
char arr[100];
if(dataFile.fail())
{
sprintf(arr,"Invalid unit of Measurement code : %d",code);
throw DAOException(arr);
}
dataFile.seekg(0,ios::beg);
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
sprintf(arr,"Invalid unit of Measurement code : %d",code);
throw DAOException(arr);
}
if(header.numberOfRecords==0)
{
dataFile.close();
sprintf(arr,"Invalid unit of Measurement code : %d",code);
throw DAOException(arr);
}
if(code<=0 ||code>header.lastGeneratedCode)
{
dataFile.close();
sprintf(arr,"Invalid unit of Measurement code : %d",code);
throw DAOException(arr);
}
while(1)
{
dataFile.read((char *)&_uom,sizeof(_unitOfMeasurement));
if(dataFile.fail()) break;
if(code==_uom.code)
{
abc::IUnitOfMeasurement *uom=new unitOfMeasurement;
uom->setCode(_uom.code);
uom->setTitle(_uom.title);
return uom;
}
}
sprintf(arr,"Invalid unit of Measurement code : %d",code);
throw DAOException(arr);
}
abc::IUnitOfMeasurement * unitOfMeasurementDAO::getByTitle(string vTitle)
{
Header header;
_unitOfMeasurement _uom;
string title=trimmed(vTitle);
if(title.length()==0)
{
throw DAOException(string("Unit of measurement does not exists : ")+title);
}
else if(title.length()>50)
{
throw DAOException(string("Unit of measurement does not exists : ")+title);
}
ifstream dataFile(FILE_NAME,ios::binary);
if(dataFile.fail())
{
throw DAOException(string("Unit of measurement does not exists : ")+title);
}
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException(string("Unit of measurement does not exists : ")+title);
}
if(header.numberOfRecords==0)
{
dataFile.close();
throw DAOException(string("Unit of measurement does not exists : ")+title);
}
while(1)
{
dataFile.read((char *)&_uom,sizeof(_unitOfMeasurement));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_uom.title,title.c_str())==0)
{
unitOfMeasurement *uom=new unitOfMeasurement;
uom->setCode(_uom.code);
uom->setTitle(_uom.title);
return uom;
}
}
throw DAOException(string("Unit of measurement does not exists : ")+title);
}
forward_list<abc::IUnitOfMeasurement *> * unitOfMeasurementDAO::getAll()
{
forward_list<abc::IUnitOfMeasurement *> *list;
list=new forward_list<abc::IUnitOfMeasurement *>;
forward_list<abc::IUnitOfMeasurement *>::iterator i;
i=list->before_begin();
Header header;
_unitOfMeasurement _uom;
abc::IUnitOfMeasurement *uom;
ifstream dataFile(FILE_NAME,ios::binary);
if(dataFile.fail())
{
throw DAOException("Unit of Measurements does not exist.");
}
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
throw DAOException("Unit of Measurements does not exist.");
}
if(header.numberOfRecords==0)
{
dataFile.close();
throw DAOException("Unit of Measurements does not exist.");
}
while(1)
{
dataFile.read((char *)&_uom,sizeof(_unitOfMeasurement));
if(dataFile.fail()) break;
uom=new unitOfMeasurement;
uom->setCode(_uom.code);
uom->setTitle(_uom.title);
i=list->insert_after(i,uom);
}
dataFile.close();
return list;
}
int unitOfMeasurementDAO::getCount()
{
Header header;
ifstream dataFile(FILE_NAME,ios::binary);
if(dataFile.fail())
{
return 0;
}
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
return 0;
}
dataFile.close();
return header.numberOfRecords;
}
int unitOfMeasurementDAO::codeExists(int code)
{
Header header;
_unitOfMeasurement _uom;
ifstream dataFile(FILE_NAME,ios::binary);
if(dataFile.fail())
{
return 0;
}
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
return 0;
}
if(header.numberOfRecords==0)
{
dataFile.close();
return 0;
}
if(code<=0 ||code>header.lastGeneratedCode)
{
dataFile.close();
return 0;
}
while(1)
{
dataFile.read((char *)&_uom,sizeof(_unitOfMeasurement));
if(dataFile.fail()) break;
if(code==_uom.code)
{
return 1;
}
}
return 0;
}
int unitOfMeasurementDAO::titleExists(string vTitle)
{
Header header;
_unitOfMeasurement _uom;
string title=trimmed(vTitle);
if(title.length()==0)
{
return 0;
}
else if(title.length()>50)
{
return 0;
}
ifstream dataFile(FILE_NAME,ios::binary);
if(dataFile.fail())
{
return 0;
}
dataFile.read((char *)&header,sizeof(Header));
if(dataFile.fail())
{
dataFile.close();
return 0;
}
if(header.numberOfRecords==0)
{
dataFile.close();
return 0;
}
while(1)
{
dataFile.read((char *)&_uom,sizeof(_unitOfMeasurement));
if(dataFile.fail()) break;
if(compareStringIgnoreCase(_uom.title,title.c_str())==0)
{
return 1;
}
}
return 0;
}
