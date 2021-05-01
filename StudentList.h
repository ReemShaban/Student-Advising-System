#ifndef StudentList_h
#define StudentList_h

#include "CourseTree.h"

class StudentNode {
public:
	string Name;
	vector<CourseNode*> CoursesTaken;

	StudentNode(string _Name = "");
	StudentNode(const StudentNode& _Original);
};

///////////////////////////////////////////////////////////////////////////////////////////

class StudentList
{
public:
	vector<StudentNode*> Students;
	CourseTree* CoursesRefrence;

	StudentList(CourseTree* _CoursesRefrence = 0);
	StudentNode* Add(string _Name, bool _Save = true);
	void Remove(StudentNode* _Student);
	void Clear();
	void Edit(StudentNode* _Student, string _Name);
	vector<StudentNode*> Search(string _Name);
	StudentNode* GetStudent(string _Name);
	bool IsStudentExist(string _Name);
	bool IsEmpty();
	void Save(string _Filename = "Students");
	bool Load(string _Filename = "Students");
};
#endif