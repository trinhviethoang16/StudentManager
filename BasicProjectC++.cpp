#include<iostream>
#include<string>
#include<string.h>
#include<vector>
#include<fstream>
using namespace std;

struct subject
{
    string subjectname;
    float score;
};
typedef subject Subject;

struct student
{
    string name;
    string id;
    string birth;
    vector <Subject> subjectlist;
};
typedef student Student;

void infoStudent(ifstream &FileIn, Student &st)
{
    getline(FileIn, st.name, ',');
    getline(FileIn, st.id, ',');
    getline(FileIn, st.birth);
}

void subjectStudent(ifstream &FileIn, Subject &sj)
{
    getline(FileIn, sj.subjectname, '-');
    FileIn >> sj.score;
}

void dataStudent(ifstream &FileIn, vector<Student> &list)
{
    while(FileIn.eof()==false)
    {
        Student st;
        infoStudent(FileIn, st);
        int n;
        FileIn >> n;
        string temp;
        getline(FileIn, temp); //delete '\n'
        for(int i=0; i<n; i++)
        {
            Subject sj;
            subjectStudent(FileIn, sj);
            getline(FileIn, temp); //delete '\n'
            st.subjectlist.push_back(sj);
        }
        list.push_back(st);
    }
}

void outputInfo(Student st)
{
    cout << "Name: " << st.name << endl;
    cout << "ID: " << st.id << endl;
    cout << "Birth: " << st.birth << endl;
}

void outputSubject(Subject sj)
{
    cout << "Subject name: " << sj.subjectname << endl;
    cout << "Score: " << sj.score << endl;
}

void outputStudent(vector<Student> list)
{
    for(int i=0; i<list.size(); i++)
    {
        cout << "\n\t\tSTUDENT " << i+1 << endl;;
        outputInfo(list[i]);
        for(int j=0; j<list[i].subjectlist.size(); j++)
        {
            cout << "\n\t\tSUBJECT " << j+1 << endl;
            outputSubject(list[i].subjectlist[j]);
        }
    }
}

void findStudentName(vector<Student> list, string name)
{
    int count=1;
    for(int i=0; i<list.size(); i++)
    {
        if(stricmp(list[i].name.c_str(), name.c_str())==0)
        {
            cout << "\n\t\tSTUDENT " << count++ << endl;
            outputInfo(list[i]);
            int n = list[i].subjectlist.size();
            for(int j=0; j<n; j++)
            {
                cout << "\n\t\tSUBJECT " << j+1 << endl;
                outputSubject(list[i].subjectlist[j]);
            }
        }
    }
}

void readSubject(ofstream &FileOut, Subject sj)
{
    FileOut << sj.subjectname << "-" << sj.score;
}

void readDataStudent(ofstream &FileOut, Student st)
{
    FileOut << st.name << "," << st.id << "," << st.birth << endl;
    FileOut << st.subjectlist.size() << endl;
    for(int i=0; i<st.subjectlist.size(); i++)
    {
        readSubject(FileOut, st.subjectlist[i]);
        FileOut << endl;
    }
}

string yearOfBirth(string str) //tach nam sinh khoi ngay/thang/nam
{
    string temp;
    for(int i=str.length()-1; i>=0; i--)
    {
        if(str[i] >= '0' && str[i]<='9')
        {
            temp.insert(temp.begin() + 0, str[i]);
        }
        else
        {
            break;
        }
    }
    return temp;
}

void saveNamSinhFile(ofstream &FileOut, vector<Student> &list, string year)
{
	for (int i=0; i<list.size(); i++)
	{
		string a = yearOfBirth(list[i].birth);
		if (stricmp(a.c_str(), year.c_str()) == 0)
		{
			readDataStudent(FileOut, list[i]);
		}
	}
}

int main()
{
    
    ifstream FileIn;
    vector<Student> list;
    FileIn.open("D:\\Codes\\C-C++\\BaiTapFile\\BaiTapTongHop\\SinhVien.txt", ios_base::in);
    if(FileIn.fail())
    {
        cout << "Can't open file !" << endl;
        return 0;
    }
    
    //Cau 1
    dataStudent(FileIn, list);
    outputStudent(list);

    //Cau 2
    string name;
    cout << "\nEnter student name need to find: ";
    getline(cin, name);
    findStudentName(list, name);

    // Cau 3
    ofstream FileOut;
    FileOut.open("D:\\Codes\\C-C++\\BaiTapFile\\BaiTapTongHop\\NamSinh.txt", ios_base::app);
    string year;
    cout << "\nEnter student year of birth need to find: ";
    getline(cin, year);
    saveNamSinhFile(FileOut, list, year);

    FileIn.close();
    FileOut.close();
    return 0;
}