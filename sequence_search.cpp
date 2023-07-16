#include "AKwB_03.hpp"

using namespace std;


void get_data(vector<string> *s, vector<vector<int>> *q)
{
    int line_nr=1;
    char first;
    string line;
    int value;
    vector<int> temp;

    fstream filequal;
    filequal.open("qual1.txt" , ios::in);
    if( filequal.good()==false) {              //sprawdz prawidlowosc pliku
       cout<<"Taki plik nie istnieje!"<<endl;
       return;
    }

    while(getline(filequal, line))   //pobiera wartosci wiarygodnosci
    {
        stringstream ss(line);
        first=line[0];
        if(first=='>' && line_nr==1)
        {
             line_nr++;  //pomija pierwsz� linie
             continue;
        }
        else if(first=='>' && line_nr!=1)
        {
            q->push_back(temp); //wpychanie wektora tymczasowego na wktor qualities
            temp.clear();
        }
        else
        {
            while(ss>>value)
            {
                temp.push_back(value); //wpychanie na wektor tymczasowy pojedynczych wartosci ze strumienia napisowego
            }
        }
        if(filequal.eof())
        {
            q->push_back(temp); //wpychanie wektora tymczasowego na wktor qualities
            temp.clear();       // dziala dla ostatniej linijki
        }
    }
    filequal.close();

    fstream filefasta;
    filefasta.open("fasta1.txt" , ios::in);
    if( filefasta.good()==false) {
        cout<<"Taki plik nie istnieje!"<<endl;
        return;
    }

    while(getline(filefasta, line))   //pobiera sekwencje
    {
        first=line[0];
        if(first=='>')
        {
            continue;                   //dla ulatwienia sekwencja jest w jednej linii, i tak jest kr�tka.
        }
        s->push_back(line);
    }

    filefasta.close();
    return;
}


void delete_nucleotides(vector<string> *s, vector<vector<int>> *q, vector<vector<int>> *p, int tresh)
{

    vector<int> position_helper;
    for(int i=0;i<s->size();i++)
    {
        string seq=(*s)[i];
        string final_seq="";

        for(int j=0;j<(*q)[i].size();j++)
        {
            if((*q)[i][j]<tresh) continue;
            else
            {
              position_helper.push_back(j+1);
              final_seq+=seq[j];
            }
        }
        p->push_back(position_helper);
        position_helper.clear();
        (*s)[i]=final_seq;
    }
}


void Graph::create_graph(vector<string> &s, vector<vector<int>> &p, int sub)
{
    string vertic;
    for(int i=0;i<s.size();i++)
    {
        for(int j=0;j<s[i].size();j++)
        {
            if(j>(s[i].length()-sub))
            {
                break;
            }
            vertic=s[i].substr(j,sub);
            vertices.push_back(vertic);
            seqs.push_back(i);
        }
    }

    for(int i=0;i<p.size();i++)
    {
        for(int j=0;j<p[i].size()-4;j++)
        {
          pos.push_back(p[i][j]);
        }
    }


    for(int i=0;i<vertices.size();i++){
        cout<<i<<"::"<<vertices[i]<<endl;//wektory plaskie pomoga w odczytaniu wyniku koncowego
        cout<<seqs[i]<<endl;
        cout<<pos[i]<<endl;
    }

    g_size=vertices.size();
    //cout<<vertices.size()<<endl;

    matrix=new int*[g_size];
    for(int i=0;i<g_size;i++)
    {
        matrix[i]=new int[g_size];
        for(int j=0;j<g_size;j++)
        {
            matrix[i][j]=0;
        }
    }

    /*vector<string> helper;
    for(int i=0;i<s.size();i++)
    {
        for(int j=0;j<s[i].size();j++)
        {
            if(j>(s[i].length()-sub))
            {
                break;
            }
            vertic=s[i].substr(j,sub);
            helper.push_back(vertic);
        }
        vertices_helper.push_back(helper);
        helper.clear();
    }
*/
    /*for(int i=0;i<vertices_helper.size();i++){          //  WYSWIETLANIE WEKTORA WEKTOROW
        cout<<i<<endl;
        for (auto it = vertices_helper[i].begin();
             it != vertices_helper[i].end(); it++) {

            cout << ' ' << *it << ' ';
        }
        cout<<endl;
        cout<<vertices_helper[i].size()<<endl;
    }*/

    /*for(int i=0;i<vertices_helper.size()-1;i++)
    {
        for(int x=i+1;x<vertices_helper.size()-1;x++)
        {
            for(int j=0;j<vertices_helper[i].size();j++)
            {
                for(int k=0;k<vertices_helper[x].size();k++)
                {
                    if(vertices_helper[i][j]==vertices_helper[x][k])
                    {

                    }
                }
            }
        }
    }*/



    for(int i=0;i<vertices.size();i++)
    {
        for(int j=0;j<vertices.size();j++)
        {
            if(vertices[i]==vertices[j] && seqs[i]!=seqs[j])
            {
                matrix[i][j]=1;
                matrix[j][i]=1;
            }
        }
    }

    for(int i=0;i<vertices.size();i++){
        for(int j=0;j<vertices.size();j++){
            if(matrix[i][j]==1 || matrix[j][i]==1) cout<<i<<"\t"<<j<<endl;
        }
    }




}
