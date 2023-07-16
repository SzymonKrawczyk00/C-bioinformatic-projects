#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <set>
#include "AKwB_02.h"

using namespace std;


Graph::Graph(int v)
{
    this->g_size=v;
    vectors_array=new vector<int>[v]; //vectors_a.. to obiekt a vector<int> to typ //tworzy tablice wektorów//zwraca do wskaznika adres zaalokowanej pamieci
    precursors=new vector<int>[v];
    transformation_array=new vector<int>[v];
}

Graph::~Graph()
{
    delete vectors_array;
    delete precursors;
    delete transformation_array;
}

void Graph::add_arc( int x,int y)
{
    vectors_array[x].push_back(y);
}

void Graph::create_graph()
{
    fstream file;
    file.open("graph_read.txt", ios::in);
    if(file.good()==0){
        cout<<"Such file doesnt exist!"<<endl;
        return;
    }

    int str_line=1;
    string line;
    int vertic;

    while(getline(file,line)){

        stringstream str(line);
        if(str_line==1){
            ++str_line;
            continue;
        }
        else{
        while(str>>vertic){
            builder.push_back(vertic);
        }
        int first=builder[0];
        for(int i=1;i<=(builder.size())-1;i++){
            this->add_arc(first,builder[i]);
        }
        builder.clear();
        }
    }
    file.close();
    return;
}

void Graph::print_graph()
{
    for(int i=0;i<g_size;i++){
        cout<<i;
       /* for(int nbr:vectors_array[i]){
            cout<<" "<<nbr;
        }
        cout<<endl;
    }
}*/
for (auto it = vectors_array[i].begin();
             it != vectors_array[i].end(); it++) {

            cout << ' ' << *it << ' ';
        }
        cout<<endl;
}

}

void Graph::sort_list()
{
    for(int i=0;i<g_size;i++){
    sort(vectors_array[i].begin(), vectors_array[i].end());
    }
}

bool Graph::is_1_graph()
{
    for(int i=0;i<g_size;i++){
    const auto has_duplicate=adjacent_find(vectors_array[i].begin(), vectors_array[i].end());
    if(has_duplicate!=vectors_array[i].end()){
        //cout<<endl<<"DUPA"<<endl;
        return false;

    }
    else continue;
    }
    //cout<<endl<<"TAK"<<endl;
    return true;
}

bool Graph::is_adjoint()
{
    if(this->is_1_graph()==false) {cout<< "niestey nie"<<endl; return false;}

    for(int i=0;i<g_size;i++){
         for(int j=i;j<g_size;j++){ ///!!!!!

             if(i==(g_size-1) && j==(g_size-1)) {cout<< "jest sprz"<<endl; return true;}
             if(i==j)continue;

             else{
             set<int> dup( vectors_array[i].begin(), vectors_array[i].end() );
             dup.insert( vectors_array[j].begin(), vectors_array[j].end() );
             int dup_number= vectors_array[i].size() + vectors_array[j].size() - dup.size();
               if(dup_number!=0){
                 if(vectors_array[i]!=vectors_array[j]){
                    cout<<"niestety nie"<<endl;
                     return false;
                 }
                 else continue;

               }

             }
         }
    }
}

void Graph::check_precursors()
{
    for(int i=0;i<g_size;i++){
        for(int j=0;j<g_size;j++){
            for (auto it = vectors_array[j].begin();
             it != vectors_array[j].end(); it++){
               if((*it)==i){
                 precursors[i].push_back(j);
               }
               else continue;
             }
         }
    }
    for(int i=0;i<g_size;i++){
    for (auto it = precursors[i].begin();
             it != precursors[i].end(); it++) {

            cout << ' ' << *it << ' ';
        }
        cout<<endl;
}
}

 bool Graph::is_linear()
 {
     if(this->is_1_graph()==false) {cout<< "niestey nie"<<endl; return false;}
     this->check_precursors();
     cout<<"wykonane"<<endl;

    for(int i=0;i<g_size;i++){
         for(int j=i;j<g_size;j++){ ///!!!!!

             if(i==(g_size-1) && j==(g_size-1)) {cout<< "jest lin"<<endl; return true;}
             if(i==j)continue;

             else{
             set<int> dup( vectors_array[i].begin(), vectors_array[i].end() );
             dup.insert( vectors_array[j].begin(), vectors_array[j].end() );
             int dup_number= vectors_array[i].size() + vectors_array[j].size() - dup.size();
               if(dup_number!=0){
                 if(vectors_array[i]!=vectors_array[j]){
                    cout<<"niestety nie"<<endl;
                     return false;
                 }
                 else{
                    set<int> dup_precursors( precursors[i].begin(), precursors[i].end() );
                    dup_precursors.insert( precursors[j].begin(), precursors[j].end() );
                    int dup_precursors_number= precursors[i].size() + precursors[j].size() - dup_precursors.size();
                    if(dup_precursors_number!=0) return false;
                 }
               }
            }
         }
     }
 }

 void Graph::transform_and_save()
 {
     int j=0;
     for(int i=0;i<g_size;i++){
        if(i==0){
            transformation_array[i].push_back(j);
            transformation_array[i].push_back(j+1);
            j++;
        }
        else {
            transformation_array[i].push_back(j+1);
            transformation_array[i].push_back(j+2);
            j=j+2;
        }
     }

         for(int i=0;i<g_size;i++){
    for (auto it =transformation_array[i].begin();
             it != transformation_array[i].end(); it++) {

            cout << ' ' << *it << ' ';
        }
        cout<<endl;
}
      int check;
      for(int i=0;i<g_size;i++){

            if(vectors_array[i].size()==0){
                continue;
            }

           for(int j=0;j<vectors_array[i].size();j++){

                int x=i;
                int y=vectors_array[i][j];
                if(x<y){
                    check=transformation_array[y][0];
                    transformation_array[y][0]=transformation_array[x][1];

                     for(int i=0;i<g_size;i++){
                        for (auto it = transformation_array[i].begin();
                        it !=transformation_array[i].end(); it++){
                            if((*it)==check){
                               *it=transformation_array[x][1];
                            }
                        }
                    }
                }

                else{
                    check=transformation_array[x][1];
                    transformation_array[x][1]=transformation_array[y][0];

                     for(int i=0;i<g_size;i++){
                          for (auto it = transformation_array[i].begin();
                          it !=transformation_array[i].end(); it++){
                              if((*it)==check){
                                *it=transformation_array[y][0];
                              }
                          }
                     }
                }
           }
      }

         for(int i=0;i<g_size;i++){
    for (auto it =transformation_array[i].begin();
             it != transformation_array[i].end(); it++) {

            cout << ' ' << *it << ' ';
        }
        cout<<endl;
}

      for(int i=0;i<g_size;i++){

        v1.push_back(transformation_array[i][0]);
        v2.push_back(transformation_array[i][1]);
      }


       /*copy(v2.begin(), v2.end(), back_inserter(v4));
       sort(v4.begin(), v4.end());

       for(int i=0;i<v4.size();i++){

         int maxv1 = *max_element(v1.begin(), v1.end());
         if(v4[i]>maxv1){
            v1.push_back(v4[i]);
         }
       }*/
       for(int i=0;i<v2.size();i++){

         int maxv1 = *max_element(v1.begin(), v1.end());
         if(v2[i]>maxv1){
            v1.push_back(v2[i]);
         }
       }

       copy(v1.begin(), v1.end(), back_inserter(v3));
       v3.insert( v3.end(), v2.begin(), v2.end() ); ///!!!!!
       sort(v3.begin(), v3.end());

       for(int i=0;i<(v3.size()-1);i++){

          if(v3[i+1]==v3[i]+1 || v3[i+1]==v3[i]);
          else{

            int base=v3[i+1];
            int substitution=v3[i]+1;
            for (auto it =v3.begin();
             it != v3.end(); it++) {
                 if(*it==base) *it=substitution;
             }
           // v3[i+1]=v3[i]+1;
            for(int j=0;j<v1.size();j++){
                if(v1[j]==base) v1[j]=substitution;
                if(v2[j]==base) v2[j]=substitution;
            }
          }
       }
       for (auto it =v1.begin();
             it != v1.end(); it++) {

            cout << ' ' << *it << ' ';
        } cout<<endl;

           for (auto it =v2.begin();
             it != v2.end(); it++) {

            cout << ' ' << *it << ' ';
        } cout<<endl;

       int maxv1 = *max_element(v1.begin(), v1.end());
       this->g_size_transformed = maxv1+1;
       vector<int> *transformed_graph=new vector<int>[g_size_transformed];

       while(!v1.empty()){

        if(v1.size()==v2.size()){
        int value=v1.back();
        int which=v2.back();
        v1.pop_back();
        v2.pop_back();
        transformed_graph[value].push_back(which);
        }

        else{
            v1.pop_back();
        }
       }
       cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;

        for(int i=0;i<g_size_transformed;i++){
        cout<<i;

             for (auto it = transformed_graph[i].begin();
             it != transformed_graph[i].end(); it++) {
             cout << ' ' << *it << ' ';
             }
         cout<<endl;
       }

       ofstream file;
       file.open("graph_save.txt");
       if(file.good()==0){
        cout<<"Such file doesnt exist!"<<endl;
        return ;
       }
       file<<g_size_transformed<<endl;
       for(int i=0;i<g_size_transformed;i++){
        file<<i;

             for (auto it = transformed_graph[i].begin();
             it != transformed_graph[i].end(); it++) {
             file << ' ' << *it << ' ';
             }
         file<<endl;
       }
       file.close();

       delete transformed_graph;
 }


int read_graph_size()
{
    ifstream file;
    int v;
    file.open("graph_read.txt");
    if(file.good()==0){
        cout<<"Such file doesnt exist!"<<endl;
        return 0;
    }
    while(!file.eof()){

        file>>v;
        break;
    }
    file.close();
    return v;
}

