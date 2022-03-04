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
int code;
cout<<"Enter code of Unit of Measurement : ";
cin>>code;
cout<<"Enter Unit of measurement : ";
cin>>title;
uom->setCode(code);
uom->setTitle(title);
unitOfMeasurementManager uomManager;
try
{
uomManager.updateUnitOfMeasurement(uom);
cout<<title<<" updated"<<endl;
}catch(BLException blException)
{
if(blException.hasGenericException()) cout<<blException.getGenericException()<<endl;
if(blException.hasPropertyException("code")) cout<<blException.getPropertyException("code")<<endl;
if(blException.hasPropertyException("title")) cout<<blException.getPropertyException("title")<<endl;
}

return 0;
}