#include<iostream>
#include<uom>
#include<uomdao>
#include<forward_list>
using namespace std;
using namespace inventory;
using namespace data_layer;
int main()
{
abc::IUnitOfMeasurement *k;
unitOfMeasurement m;
forward_list<abc::IUnitOfMeasurement *> *list;
forward_list<abc::IUnitOfMeasurement *>::iterator i;
int c;
unitOfMeasurementDAO uomdao;
try
{
list=uomdao.getAll();
}catch(DAOException dao)
{
cout<<dao.what();
return 0;
}
for(i=list->begin();i!=list->end();++i)
{
k=*i;
cout<<"Code : "<<k->getCode()<<" Title : "<<k->getTitle()<<endl;
}
return 0;
}