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
forward_list<abc::IUnitOfMeasurement *> *unitOfMeasurements;
forward_list<abc::IUnitOfMeasurement *>::iterator i;
abc::IUnitOfMeasurement *uom;
unitOfMeasurementManager uomManager;
unitOfMeasurements=uomManager.getAll();
for(i=unitOfMeasurements->begin();i!=unitOfMeasurements->end();++i)
{
uom=*i;
cout<<uom->getCode()<<", "<<uom->getTitle()<<endl;
}
return 0;
}