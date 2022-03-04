#include<iostream>
#include<bl/uom>
#include<bl/uommanager>
#include<bl/blexception>
using namespace std;
using namespace inventory;
using namespace business_layer;
int main()
{
int code;
string title;
cout<<"Enter Unit of measurement : ";
cin>>title;
unitOfMeasurementManager uomManager;
if(uomManager.unitOfMeasurementTitleExists(title)) cout<<"Unit Of Measurement Exists"<<endl;
else cout<<"Unit of Measurement does not exists"<<endl;
cout<<"Enter Unit of measurement code : ";
cin>>code;
if(uomManager.unitOfMeasurementCodeExists(code)) cout<<"Unit Of Measurement with that code Exists"<<endl;
else cout<<"Unit of Measurement with that code does not exists"<<endl;
return 0;
}