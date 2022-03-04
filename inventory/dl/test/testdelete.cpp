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
try
{
uomdao.remove(8);
}catch(DAOException dao)
{
cout<<dao.what()<<endl;
}
return 0;
}