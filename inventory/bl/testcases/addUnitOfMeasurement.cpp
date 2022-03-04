#include<iostream>
#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
abc::IUnitOfMeasurement *uom;
uom=new unitOfMeasurement;
string title;
cout<<"Enter Unit of measurement : ";
cin>>title;
uom->setCode(0);
uom->setTitle(title);
unitOfMeasurementManager uomManager;
try
{
uomManager.addUnitOfMeasurement(uom);
cout<<title<<" added"<<endl;
}catch(BLException blException)
{
if(blException.hasGenericException()) cout<<blException.getGenericException()<<endl;
if(blException.hasPropertyException("code")) cout<<blException.getPropertyException("code")<<endl;
if(blException.hasPropertyException("title")) cout<<blException.getPropertyException("title")<<endl;
}

return 0;
}