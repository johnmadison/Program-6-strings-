

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
using namespace std;
const int maxp = 50;

struct ptype
{
    string whole, first;
    char mi;
    string last, department;
    int salary;
};

const ptype initrec = {"Archie P. Bunker", "Archie" , 'P' , "Bunker" , "Basketweaving" , 0 };

void initem (ptype p[], int maxp)
{
    int i = 0;
    for (i = 0; i < maxp; i++) p[i]=initrec;
}

void drawline(char ch, int n, ofstream &outf)
{
    for (int i = 0; i < n ; i++) outf << ch;
}
void readem (ptype p[], int &nump)
{
    ifstream inf;
    inf.open("input.dat");
    int i = 0;
    while (!inf.eof())
    {
        getline(inf, p[i].whole, '|');
        getline(inf, p[i].department, '|');
        inf >> p[i].salary >> ws;
        i++;
    }
    nump = i;
}

void stringsplit(ptype p[], int nump)
{
    int i = 0;
    while (i < nump)
    {
        int period, wholelen, lastlen, firstlen;
        period = p[i].whole.find('.');
        p[i].mi = p[i].whole[period - 1];
        wholelen = p[i].whole.length();
        p[i].last = p[i].whole.substr(period + 2, wholelen);
        lastlen = p[i].last.length();
        firstlen = wholelen - lastlen - 4;
        p[i].first = p[i].whole.substr(0, firstlen);
        i++;
    }
}

void swapem(ptype p[], int i)
{
    string tempwhole, tempfirst;
    char tempmi;
    string templast, tempdepartment;
    int tempsalary;
    tempwhole = p[i].whole;
    p[i].whole = p[i+1].whole;
    p[i+1].whole = tempwhole;
    tempfirst = p[i].first;
    p[i].first = p[i+1].first;
    p[i+1].first = tempfirst;
    tempmi = p[i].mi;
    p[i].mi = p[i+1].mi;
    p[i+1].mi = tempmi;
    templast = p[i].last;
    p[i].last = p[i+1].last;
    p[i+1].last = templast;
    tempdepartment = p[i].department;
    p[i].department = p[i+1].department;
    p[i+1].department = tempdepartment;
    tempsalary = p[i].salary;
    p[i].salary = p[i+1].salary;
    p[i+1].salary = tempsalary;
}

void sortem_department(ptype p[], int nump)
{
    int j, i;
    for (j = 0; j <nump -1; j++)
        for (i = 0; i <nump -1; i++)
            if (p[i].department > p[i + 1].department)
            {
                swapem(p, i);
            }
}

void sortem_lastname(ptype p[], int nump)
{
    int j, i;
    for (j = 0; j <nump -1; j++)
        for (i = 0; i <nump -1; i++)
            if (p[i].last > p[i + 1].last)
            {
                swapem(p, i);
            }
}

void printem(ofstream &outf, ptype p[], int nump)
{
    outf << left << setw(20) << "NAME" << setw(20) << "DEPARTMENT" << setw(10) << right << "SALARY($)" << endl;
    drawline('*', 50, outf); outf <<endl;
    int i = 0;
    for (i = 0; i < nump ; i++) outf << left << setw(20) << p[i].whole << setw(20) << p[i].department << setw(10) << right << p[i].salary << endl;
    outf<<endl;
}

void printem_first(ofstream &outf, ptype p[], int nump)
{
    outf << left << setw(20) << "NAME" << setw(12) <<right<< "SALARY($)" << setw(18) << "DEPARTMENT" << endl;
    drawline('*', 50, outf); outf <<endl;
    int i = 0;
    for (i = 0; i < nump ; i++) outf << left << setw(20) << p[i].whole << setw(12) <<right<< p[i].salary << setw(18)<< p[i].department << endl;
    outf<<endl;
}

void printpretty(ofstream &outf, ptype p[], int nump)
{
    outf<<left<<setw(20)<<"NAME"<<right<<setw(12)<<"SALARY($)"<<endl;
    drawline('*', 32, outf); outf <<endl;
    int i = 0;
    for (i = 0; i < nump ; i++)
    {
        string salary = to_string(p[i].salary);
        int len = salary.length();
        int insertpos = len -3;
        while (insertpos > 0){
            salary.insert(insertpos, ",");
            insertpos -=3;
        }
        salary.insert(0, "$");
        string fullname = p[i].last + ", " + p[i].first + " " + p[i].mi + ".";
        outf<<setw(20)<<left<<fullname<<setw(12)<<right<<salary<<endl;
        }
    int totalsalary = 0;
    for (i = 0; i < nump ; i++)
    {
    totalsalary += p[i].salary;
    }
    string printsalary = to_string(totalsalary);
    int printlen = printsalary.length();
    int printpos = printlen - 3;
    while (printpos > 0){
        printsalary.insert(printpos, ",");
        printpos -= 3;
    }
    printsalary.insert(0, "$");
    drawline('*', 32, outf); outf << endl;
    outf << "TOTAL SALARY" <<setw(20)<< printsalary <<endl;
}

int main(int argc, const char * argv[])
{
    ofstream outf;
    outf.open("output.txt");
    ptype p[maxp];
    int nump = 0;
    initem (p, maxp);
    readem(p, nump);
    printem_first(outf, p, nump);
    stringsplit(p, nump);
    sortem_department(p, nump);
    printem(outf, p, nump);
    sortem_lastname(p, nump);
    printpretty(outf, p, nump);
}

