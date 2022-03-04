#include<common/stringutils>
#include<iostream>
using namespace std;
string stringutils::trimmed(const string &other)
{
int i,j,len,e;
len=other.size();
for(i=0;i<len && other[i]==' ';i++);
if(i==len) return string("");
for(j=len-1;other[j]==' ';j--);
char *k;
k=new char[j-i+2];
for(e=0;i<=j;e++,i++) k[e]=other[i];
k[e]='\0';
string c(k);
delete [] k;
return c;
}
int stringutils::compareStringIgnoreCase(const char *str1,const char *str2)
{
if(str1==str2) return 0;
if(str1==NULL) return -1;
if(str2==NULL) return 1;
char d,s;
for(;*str1 && *str2;str1++,str2++)
{
d=*str1;
if(d>=97 && d<=122) d=d-32;
s=*str2;
if(s>=97 && s<=122) s=s-32;
if(s!=d) return d-s;
}
if(*str1==*str2) return 0;
if(*str1=='\0') return -1;
return 1;
}