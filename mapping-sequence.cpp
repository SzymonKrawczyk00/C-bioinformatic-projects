#include "AKwB_04.hpp"

void get_multi_set(vector<int> &v)
{
    fstream filemultiset;
    filemultiset.open("multizbior.txt" , ios::in);
    if( filemultiset.good()==false) {              //sprawdz prawidlowosc pliku
       cout<<"Such file does not exist!"<<endl;
       return;
    }

    int num;
    while(filemultiset>>num)
    {
        v.push_back(num);
    }

    filemultiset.close();
    return;
}


unsigned long long silnia(int x)
{
  unsigned long long value=1;
    for(int i=1;i<=x;++i)
    {
        value*=i;
    }
    return value;
}


int restrictive_sites(unsigned int s)
{
    int k=0;
    int x=0;

    do
    {
        k++;
        //cout<<"K :"<<k<<endl;
        //x=silnia(k+2);
        //x=x/(silnia(k)*2);
         x=silnia(k+2)/(silnia(k)*2);
        //cout<<"x: "<<x<<endl;
        if(x>s)
        {
            cout<<"blad w instancji, za duzo lub za malo elementow!"<<endl;
            return 0;
        }
    }
    while(x!=s);
    return k;
}

void search_map(int map_element, vector<int> maps, vector<int> multi_set, vector<int> &used, unsigned int *map_size, int *max_elem, unsigned int ind, int *is)
{
    maps.push_back(map_element);
    /*cout<<"mapa: "<<endl;
    for(unsigned int i=0;i<maps.size();i++)//**** wyswietlanie
    {
        cout<<maps[i]<<endl;
    }
    cout<<"Used: "<<endl;
    for(unsigned int i=0;i<used.size();i++)//**** wyswietlanie
    {
        cout<<used[i]<<endl;
    }
    cout<<"Multizbior: "<<endl;
    for(unsigned int i=0;i<multi_set.size();i++)//**** wyswietlanie
    {
        cout<<multi_set[i]<<endl;
    }
*/
    for(int i=0;i<used.size();i++)
    {
        for(int j=0;j<multi_set.size();j++)
        {
            if(multi_set[j]==used[i])
            {
                multi_set.erase(multi_set.begin() + j);
                break;
            }
        }

    }
    used.clear();
    /*cout<<"NOWY MULTIZBIOR: "<<endl;
    for(unsigned int i=0;i<multi_set.size();i++)//**** wyswietlanie
    {
        cout<<multi_set[i]<<endl;
    }
    cout<<"****************************"<<ind<<endl;*/
   int current_map_len;
   int check=1;

   if(ind==*map_size-1 && multi_set.size()==1)
   {
       maps.push_back(multi_set[0]);
       ind++;
   }

   if(ind==*map_size)
   {
      cout<<"Uzyskana mapa: "<<endl;
      for(unsigned i=0;i<maps.size();i++)
      {
          cout<<maps[i]<<"\t";
      }
      cout<<endl;
      *is=1;
   }

   else for (unsigned int i=0; i<multi_set.size(); i++)
   {
      int elem=multi_set[i];
      //cout<<"nowy element do mapy: "<<elem<<endl;
      current_map_len=elem;
      //cout<<"cur elem: "<<current_map_len<<endl;
      used.push_back(elem);
        //cout<<"Used: "<<endl;
   /* for(unsigned int i=0;i<used.size();i++)//**** wyswietlanie
    {
        cout<<used[i]<<endl;
    }
       cout<<"mapa: "<<endl;
    for(unsigned int i=0;i<maps.size();i++)//**** wyswietlanie
    {
        cout<<maps[i]<<endl;
    }*/
      for(unsigned int i=maps.size();i>0;i--)
      {
         // cout<<"mm: "<<maps[i-1]<<endl;
          current_map_len+=maps[i-1];
           //cout<<"cur elem: "<<current_map_len<<endl;
          used.push_back(current_map_len);
          if(find(multi_set.begin(), multi_set.end(), current_map_len) == multi_set.end())
          {
              check =0;
              break;
          }
          else
              continue;
      }
      //cout<<"CCCCCCCCCCCC: "<<check<<endl;
      if(multi_set.size()-used.size() != 1)
           used.push_back(*max_elem-current_map_len);

      if (check==1 &&  find(multi_set.begin(), multi_set.end(), (*max_elem-current_map_len)) != multi_set.end())
         search_map(elem, maps, multi_set, used, map_size, max_elem, ind+1, is);
      else
        {
         used.clear();
         check=1;
        }
      if (*is==1) break;
   }

}

