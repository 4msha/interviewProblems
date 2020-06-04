#include<bits/stdc++.h>
using namespace std;


class date{
    public:
      int year_;
      int month_;
      int day_;
    public:
      date();
      date(const int& d,const int& m,const int& y)
      :year_(y),month_(m),day_(d){
       
      };

    int day()const{return day_;};
    int month() const{ return month_;};
    int year() const{return year_;};

    void setDay(const int&day){date::day_=day;};
    void setMonth(const int&month){date::month_=month;};
    void setYear(const int&year){date::year_=year;}

        
    bool valid()const{
        if(year_<0) return false;
        if(month_>12 || month_<1) return false;
        if(day_>31 || day_<1) return false;
        if(day_==31&&(month_==2 || month_==4 || month_==6 || month_==9 || month_==11))
        return false;
        if(day_==30 && month_==2) return false;

        if(year_<2000){
            if((day_==29 && month_==2) && !((year_-1900)%4==0)) return false;
        }  

        if(year_>2000){
            if((day_==29 && month_==2) && !((year_-2000)%4==0)) return false;
        }

        return true;
    }

    friend ostream& operator <<(ostream& os,const date& d){
        os<<d.year()<<" - "<<d.month()<<" - "<<d.day();
        return os;
    }

    inline date next_date( date& d){     
        d.setDay(d.day()+1);
        if(d.valid()) return d;
        d.setDay(1);
        d.setMonth(d.month()+1);
        if(d.valid()) return d;
        d.setMonth(1);
        d.setYear(d.year()+1);
        if(d.valid()) return d;
    return d;
    }


    date operator++(int){
        date d=*this;
        *this=next_date(*this);
        return d;
    }

    friend bool operator <(const date& d1,const date& d2){
        if(!d1.valid())return false;
        if(!d2.valid()) return false;
        if(d1.year()<d2.year()) return true;
        else if(d1.year()>d2.year()) return false;
        else{
            if(d1.month()<d2.month()) return true;
            else if(d1.month()>d2.month()) return false;
            else{
                if(d1.day()<d2.day()) return true;
                else return false;
            }
        }
        return false;
    }

      
};

/// -------------------end of class----------------------------------------// 



date makeDate(string s){
    int d,y,m;
    int i{0};
    int count=0;
    string temp;
    while(i<s.length()){
        if(s[i]=='-'){
           if(count==0){
             y=stoi(temp);
             count=1;
           }
           else if(count==1)
             m=stoi(temp);

             temp="";
             i++;
        }
        temp+=s[i];
        i++;
    }
    d=stoi(temp);
    date rDate=date(d,m,y);
    return rDate;
}

map<string,int> insertAllDate(map<string,int>& myMap){
    int count{-1};
    map<string,int> result;
    auto i=myMap.begin();
    result.insert(make_pair(i->first,i->second));
    for(auto i=myMap.begin();i!=myMap.end();i++){
        date d1=makeDate(i->first);
        date tempD=makeDate(i->first);
        int val1=i->second;
        i++;
        if(i==myMap.end())
          break;
        date d2=makeDate(i->first);
        int val2=i->second;


        while(tempD<d2){
            tempD++;
            count++;
        }
        int increment;
        if(count!=0)
         increment=(val2-val1)/count;
        else
        increment=val2-val1;

        while(d1<d2){
            d1++;
            string temp=to_string(d1.year())+"-";
            if(d1.month()/10==0)
            temp+="0";
            temp+=to_string(d1.month())+"-";
            if(d1.day()/10==0)
            temp+="0";
            temp+=to_string(d1.day());

            val1+=increment;
            result.insert(make_pair(temp,val1));
        }
        i--;
    }

    return result;
}
int main(){
    map<string,int> myMap;

    myMap.insert(make_pair("2019-01-10",10));
    myMap.insert(make_pair("2019-01-11",20));
    myMap.insert(make_pair("2019-01-16",0));

    cout<<"INITIAL MAP\n";
    for(auto i:myMap)
      cout<<i.first<<" -> "<<i.second<<endl;

    myMap=insertAllDate(myMap);

    cout<<"FINAL MAP\n";
    for(auto i:myMap)
      cout<<i.first<<" -> "<<i.second<<endl;

    return 0;
}