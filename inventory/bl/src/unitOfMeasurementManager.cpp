#include<bl/uom>
#include<bl/iuom>
#include<iostream>
#include<bl/iuommanager>
#include<bl/uommanager>
#include<bl/blexception>
#include<common/stringutils>
#include<dl/iuom>
#include<dl/uom>
#include<dl/daoexception>
#include<dl/iuomdao>
#include<dl/uomdao>
#include<forward_list>
#include<map>
#include<utility>
using namespace inventory;
using namespace business_layer;
using namespace std;
using namespace stringutils;
int unitOfMeasurementTitleComparator::operator()(string *left,string *right)
{
return compareStringIgnoreCase(left->c_str(),right->c_str())<0;
}
unitOfMeasurementManager::DataModel unitOfMeasurementManager::dataModel;
unitOfMeasurementManager::DataModel::DataModel()
{
populateDataStructure();
}
unitOfMeasurementManager::DataModel::~DataModel()
{
map<string *,_unitOfMeasurement *>::iterator i1,i2;
for(i1=unitOfMeasurementManager::dataModel.titleWiseMap.begin();i1!=unitOfMeasurementManager::dataModel.titleWiseMap.end();)
{
i2=i1;
i1++;
delete(i2->first);
delete(i2->second);
}
}
void unitOfMeasurementManager::DataModel::populateDataStructure()
{
forward_list<inventory::data_layer::abc::IUnitOfMeasurement *> *dlUnitOfMeasurement;
inventory::data_layer::unitOfMeasurementDAO uom;
try
{
dlUnitOfMeasurement=uom.getAll();
forward_list<inventory::data_layer::abc::IUnitOfMeasurement *>::iterator i;
unitOfMeasurementManager::_unitOfMeasurement *uombl;
inventory::data_layer::abc::IUnitOfMeasurement *iuom;
int code;
string *title;
for(i=dlUnitOfMeasurement->begin();i!=dlUnitOfMeasurement->end();)
{
iuom=*i;
uombl=new _unitOfMeasurement();
code=iuom->getCode();
title=new string(iuom->getTitle());
uombl->code=code;
uombl->title=title;
unitOfMeasurementManager::dataModel.codeWiseMap.insert(pair<int,unitOfMeasurementManager::_unitOfMeasurement *>(code,uombl));
unitOfMeasurementManager::dataModel.titleWiseMap.insert(pair<string *,unitOfMeasurementManager::_unitOfMeasurement *>(title,uombl));
++i;
delete(iuom);
}
delete(dlUnitOfMeasurement);
}catch(inventory::data_layer::DAOException &daoException)
{
//do nothing
}
}
unitOfMeasurementManager::unitOfMeasurementManager()
{
// do Nothing
}
void unitOfMeasurementManager::addUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement)
{
BLException blException;
if(unitOfMeasurement==NULL)
{
blException.setGenericException(string("Unit of Measurement required, NULL value encountered"));
throw blException;
}
int code=unitOfMeasurement->getCode();
string title=unitOfMeasurement->getTitle();
if(code!=0) blException.addPropertyException("code","Code should be zero");
if(title.length()==0) blException.addPropertyException("title","Title required");
if(title.size()>50) blException.addPropertyException("title","Title length exceeded, should be less than 50 characters");
if(blException.hasPropertyExceptions()) throw blException;
map<string *,_unitOfMeasurement *>::iterator i;
i=dataModel.titleWiseMap.find(&title);
if(i!=dataModel.titleWiseMap.end())
{
blException.addPropertyException("title","Given string already exists");
throw blException;
}
inventory::data_layer::unitOfMeasurementDAO uomdao;
try
{
inventory::data_layer::abc::IUnitOfMeasurement *dlUnitOfMeasurement;
dlUnitOfMeasurement=new inventory::data_layer::unitOfMeasurement;
dlUnitOfMeasurement->setCode(0);
dlUnitOfMeasurement->setTitle(title);
uomdao.add(dlUnitOfMeasurement);
unitOfMeasurement->setCode(dlUnitOfMeasurement->getCode());
delete dlUnitOfMeasurement;
string *t=new string(title);
_unitOfMeasurement *blUnitOfMeasurement;
blUnitOfMeasurement=new _unitOfMeasurement;
code=unitOfMeasurement->getCode();
blUnitOfMeasurement->code=code;
blUnitOfMeasurement->title=t;
dataModel.codeWiseMap.insert(pair<int,_unitOfMeasurement *>(code,blUnitOfMeasurement));
dataModel.titleWiseMap.insert(pair<string *,_unitOfMeasurement *>(t,blUnitOfMeasurement));
}catch(inventory::data_layer::DAOException daoException)
{
blException.setGenericException(string(daoException.what()));
throw blException;
}
}
void unitOfMeasurementManager::updateUnitOfMeasurement(abc::IUnitOfMeasurement *unitOfMeasurement)
{
BLException blException;
int code=unitOfMeasurement->getCode();
string title=unitOfMeasurement->getTitle();
if(code<=0 || code>dataModel.codeWiseMap.size()) blException.addPropertyException("code","Invalid Code");
if(title.length()==0) blException.addPropertyException("title","Title Required");
if(title.length()>=50) blException.addPropertyException("title","Title Length exceeded, should be less than 50 characters");
if(blException.hasPropertyExceptions()) throw blException;
map<int,_unitOfMeasurement *>::iterator i;
i=dataModel.codeWiseMap.find(code);
if(i==dataModel.codeWiseMap.end())
{
blException.setGenericException("Code does not Exist");
throw blException;
}
map<string *,_unitOfMeasurement *>::iterator Ititle;
_unitOfMeasurement *_uom;
inventory::data_layer::unitOfMeasurementDAO uomdao;
inventory::data_layer::abc::IUnitOfMeasurement *uom;
uom=new inventory::data_layer::unitOfMeasurement;
uom->setCode(code);
uom->setTitle(title);
Ititle=dataModel.titleWiseMap.find(&title);
if(Ititle!=dataModel.titleWiseMap.end())
{
_uom=i->second;
try
{
uomdao.update(uom);
}catch(inventory::data_layer::DAOException daoException)
{
blException.setGenericException(string(daoException.what()));
throw blException;
}

}
else uomdao.update(uom);
delete uom;
}
void unitOfMeasurementManager::removeUnitOfMeasurementByCode(int code)
{
BLException blException;
if(code<=0 || code>dataModel.codeWiseMap.size())
{
blException.setGenericException("Invalid code");
throw blException;
}
map<int,_unitOfMeasurement *>::iterator i;
i=dataModel.codeWiseMap.find(code);
if(i==dataModel.codeWiseMap.end())
{
blException.setGenericException("Code does not Exists");
throw blException;
}
inventory::data_layer::unitOfMeasurementDAO uomdao;
try
{
uomdao.remove(code);
}catch(inventory::data_layer::DAOException daoException)
{
blException.setGenericException(string(daoException.what()));
throw blException;
}
}
void unitOfMeasurementManager::removeUnitOfMeasurementByTitle(string title)
{
BLException blException;
_unitOfMeasurement *_uom;
map<string *,_unitOfMeasurement *>::iterator i;
i=dataModel.titleWiseMap.find(&title);
if(i==dataModel.titleWiseMap.end())
{
blException.setGenericException("Title does not Exists");
throw blException;
}
_uom=i->second;
inventory::data_layer::unitOfMeasurementDAO uomdao;
try
{
uomdao.remove(_uom->code);
}catch(inventory::data_layer::DAOException daoException)
{
blException.setGenericException(string(daoException.what()));
throw blException;
}
}
abc::IUnitOfMeasurement * unitOfMeasurementManager::getUnitOfMeasurementByCode(int code)
{
BLException blException;
if(code<=0 || code>dataModel.codeWiseMap.size())
{
blException.setGenericException("Invalid code");
throw blException;
}
abc::IUnitOfMeasurement *uom;
uom=new unitOfMeasurement;
_unitOfMeasurement *_uom;
map<int,_unitOfMeasurement *>::iterator i;
i=dataModel.codeWiseMap.find(code);
if(i==dataModel.codeWiseMap.end())
{
blException.setGenericException("Code does not Exists");
throw blException;
}
_uom=i->second;
uom->setCode(_uom->code);
uom->setTitle(*(_uom->title));
return uom;
}
abc::IUnitOfMeasurement * unitOfMeasurementManager::getUnitOfMeasurementByTitle(string title)
{
BLException blException;
abc::IUnitOfMeasurement *uom;
uom=new unitOfMeasurement;
_unitOfMeasurement *_uom;
map<string *,_unitOfMeasurement *>::iterator i;
i=dataModel.titleWiseMap.find(&title);
if(i==dataModel.titleWiseMap.end())
{
blException.setGenericException("title does not Exists");
throw blException;
}
_uom=i->second;
uom->setCode(_uom->code);
uom->setTitle(*(_uom->title));
return uom;
}
forward_list<abc::IUnitOfMeasurement * > * unitOfMeasurementManager::getAll()
{
forward_list<abc::IUnitOfMeasurement *> *unitOfMeasurements;
unitOfMeasurements=new forward_list<abc::IUnitOfMeasurement *>;
map<string *,_unitOfMeasurement *>::iterator i;
forward_list<abc::IUnitOfMeasurement *>::iterator listi=unitOfMeasurements->before_begin();
abc::IUnitOfMeasurement *blUnitOfMeasurement;
_unitOfMeasurement *_uom;
for(i=dataModel.titleWiseMap.begin();i!=dataModel.titleWiseMap.end();++i)
{
_uom=i->second;
blUnitOfMeasurement=new unitOfMeasurement;
blUnitOfMeasurement->setCode(_uom->code);
blUnitOfMeasurement->setTitle(*(_uom->title));
listi=unitOfMeasurements->insert_after(listi,blUnitOfMeasurement);
}
return unitOfMeasurements;
}
int unitOfMeasurementManager::unitOfMeasurementCodeExists(int code)
{
map<int,_unitOfMeasurement *>::iterator i;
i=dataModel.codeWiseMap.find(code);
if(i==dataModel.codeWiseMap.end()) return false;
else return true;
}
int unitOfMeasurementManager::unitOfMeasurementTitleExists(string title)
{
map<string *,_unitOfMeasurement *>::iterator i;
i=dataModel.titleWiseMap.find(&title);
if(i==dataModel.titleWiseMap.end()) return false;
else return true;
}
int unitOfMeasurementManager::getUnitOfMeasurementCount()
{
return dataModel.codeWiseMap.size();
}
