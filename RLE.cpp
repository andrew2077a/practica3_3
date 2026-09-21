#include <iostream>
#include <string>
using namespace std;

string rleCompress(const string& input){
    string compri="";
    //string num="";
    int contador=1;
    for(unsigned int i=0; i<input.length();i++){
        if(i+1<input.length() && input[i]==input[i+1]){
            contador++;
        }
        else{
            if(input[i]>=48&&input[i]<=57){
                compri += to_string(contador);
                compri+="#";
                compri+= input[i];

            }
            else{
                compri += to_string(contador);
                compri += input[i];
            }
            contador=1;
        }
    }
    return compri;
}

string rledescompres(string compri){
    char *ptr=&compri[0];

    string descomprin="",cunt="";
    while(*ptr!='\0'){
        if (*ptr>=48&&*ptr<=57){
            cunt+=*ptr;
        }
        else if (*ptr != '#' || (*(ptr + 1) < '0' || *(ptr + 1) > '9')){
            for(int i =stoi(cunt);i>0;i--){
                descomprin+=*ptr;
            }
            cunt="";
        }
        else{
            for(int i =stoi(cunt);i>0;i--){
                descomprin+=*(ptr+1);
            }
            cunt="";
            ptr++;
        }
        ptr++;
    }
    return descomprin;
}

bool veri( string oring,string descomprin){
    unsigned int num=oring.length();
    if (num!=descomprin.length()){
        return false;
    }
    for(unsigned int i=0;i<num;i++){
        if(oring[i]!=descomprin[i]){
            return false;
        }
    }
    return true;

}
int main(){
    char a[50];
    cout<<"ingresa la frasse"<<endl;
    cin>>a;
    cout<<rleCompress(a)<<endl;
    cout<<rledescompres(rleCompress(a))<<endl;
    if (veri( a,rledescompres(rleCompress(a)))){
        cout<<"IGUALES";
    }
}
