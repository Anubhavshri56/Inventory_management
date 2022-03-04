#include<iostream>
#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>
#include<forward_list>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
abc::IUnitOfMeasurement *uom;
unitOfMeasurementManager uomManager;
string title;
int code;
cout<<"enter Title : ";
cin>>title;
try
{
uom=uomManager.getUnitOfMeasurementByTitle(title);
cout<<"Code : "<<uom->getCode()<<" Title : "<<uom->getTitle()<<endl;
}catch(BLException blException)
{
if(blException.hasGenericException()) cout<<blException.getGenericException();
if(blException.hasPropertyException("code")) cout<<blException.getPropertyException("code");
if(blException.hasPropertyException("title")) cout<<blException.getPropertyException("title");
}
return 0;
}