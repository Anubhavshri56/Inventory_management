#include<iostream>
#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
unitOfMeasurementManager uomManager;
cout<<"Total Number of unit Of measurement that exists are : "<<uomManager.getUnitOfMeasurementCount()<<endl;
return 0;
}