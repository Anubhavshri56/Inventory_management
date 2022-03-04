#include<iuom>
#include<uom>
#include<uomdao>
#include<iostream>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
unitOfMeasurement m;
unitOfMeasurementDAO uomdao;
m.setCode(0);
m.setTitle("grams");
try
{
uomdao.add(&m);
}catch(DAOException dao)
{
cout<<dao.what()<<endl;
}
return 0;
}