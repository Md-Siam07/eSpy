#include<bits/stdc++.h>
#include "Headers.h"
using namespace std;

string convertToString(char* a, int size)
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        s = s + a[i];
    }
    return s;
}
// regular expression
vector<int> myPatternMatcher(const char* text, const char* pattern, int m, int n)
{
    vector<int> ret;
    if (*pattern == '\0' || n == 0) {
        printf("The pattern occurs with shift 0");
    }

    if (*text == '\0' || n > m) {
        //printf("Pattern not found");
    }

    int next[n + 1];

    for (int i = 0; i < n + 1; i++) {
        next[i] = 0;
    }

    for (int i = 1; i < n; i++)
    {
        int j = next[i + 1];

        while (j > 0 && pattern[j] != pattern[i]) {
            j = next[j];
        }

        if (j > 0 || pattern[j] == pattern[i]) {
            next[i + 1] = j + 1;
        }
    }

    for (int i = 0, j = 0; i < m; i++)
    {
        if (*(text + i) == *(pattern + j))
        {
            if (++j == n) {
                printf("The pattern occurs with shift %d\n", i - j + 1);
                ret.push_back(i-j+1);
            }
        }
        else if (j > 0)
        {
            j = next[j];
            i--;
        }
    }
    return ret;
}

void parse()
{
    FILE *fp = fopen("top_level_domain.txt","r");
    char domain[100][100];
    //char web[100][100];
    int domainN=0;
    while(fgets(domain[domainN],100,fp)!=0)
    {

        int len = strlen(domain[domainN]);
        domain[domainN][len-1]='\0';
        //cout<< domain[i];
        domainN++;
    }
    fclose(fp);

    FILE *log = fopen("log.txt","r");
    FILE *wFile = fopen("browsed_websites.txt","w");
    char buffer[5120];

    while(fgets(buffer,5120,log)!=0)
    {
        //int bufN = strlen(buffer);
        cout<< buffer<<endl;
        for(int i=0; i<domainN;i++)
        {
            vector<int> matched = myPatternMatcher(buffer,domain[i],strlen(buffer),strlen(domain[i]));
            if(matched.size())
            {
                for(int it=0; it< (int)matched.size(); it++)
                {
                    int index = matched[it];
                    string dom = convertToString(domain[i], strlen(domain[i]));
                    string parsedWebsite = dom;
                    parsedWebsite += "\n";
                    for(int j = index-1; j>=0; j--)
                    {
                        if(j>=2 && buffer[j]== 'w' && buffer[j-1] == 'w' && buffer[j-2] == 'w')
                        {
                            parsedWebsite = "www"+parsedWebsite;
                            break;
                        }

                        if(buffer[j]== ' ' || buffer[j]== ']' || buffer[j]=='\'' || buffer[j] == '\"' || buffer[j]== '}')
                        {
                            break;
                        }

                        parsedWebsite = buffer[j]+ parsedWebsite;
                    }
                    cout<< parsedWebsite;
                    char toWrite[100];
                    for(int ii =0;ii< (int)parsedWebsite.size();ii++)
                    {
                        toWrite[ii]=parsedWebsite[ii];
                        cout<< toWrite[ii];
                    }
                    toWrite[parsedWebsite.size()]='\0';
                    fputs(toWrite,wFile);
                }
            }
        }
    }
    fclose(log);
    fclose(wFile);
}


