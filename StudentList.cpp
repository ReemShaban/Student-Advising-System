#include "StudentList.h"

StudentNode::StudentNode(string _Name) {
	Name = _Name;
}

StudentNode::StudentNode(const StudentNode& _Original) {
	Name = _Original.Name;
	CoursesTaken = _Original.CoursesTaken;
}

///////////////////////////////////////////////////////////////////////////////////////////

StudentList::StudentList(CourseTree* _CoursesRefrence) {
	CoursesRefrence = _CoursesRefrence;
}

StudentNode* StudentList::Add(string _Name, bool _Save) {
	StudentNode* TStudent = new StudentNode(_Name);
	Students.insert(Students.end(), TStudent);
	if (_Save) Save();
	return TStudent;
}

void StudentList::Remove(StudentNode* _Student) {
	Students.erase(remove(Students.begin(), Students.end(), _Student), Students.end());
	Save();
}

void StudentList::Clear() {
	Students.clear();
	Save();
}

void StudentList::Edit(StudentNode* _Student, string _Name) {
	_Student->Name = _Name;
	Save();
}

vector<StudentNode*> StudentList::Search(string _Name) {
	vector<StudentNode*> Results;

	for (int i = 0; i < Students.size(); i++) {
		if (Students[i]->Name.rfind(_Name, 0) == 0) {
			Results.insert(Results.end(), Students[i]);
		}
	}

	return Results;
}

StudentNode* StudentList::GetStudent(string _Name) {
	for (int i = 0; i < Students.size(); i++) {
		if (Students[i]->Name == _Name) {
			return Students[i];
		}
	}

	return 0;
}

bool StudentList::IsStudentExist(string _Name) {
	return GetStudent(_Name) != 0;
}

bool StudentList::IsEmpty() {
	return int(Students.size()) == 0;
}

void StudentList::Save(string _Filename) {
	vector<string>StuData;
	vector<string>AllStu;
	for (int i = 0; i < Students.size(); i++)
	{
		StuData.push_back(Students[i]->Name);
		for (int j = 0; j < Students[i]->CoursesTaken.size(); j++) {
			StuData.push_back(Students[i]->CoursesTaken[j]->Name);
		}

		string Info = CombineStrings(StuData, '~');
		
		AllStu.push_back(Info);
		StuData.clear();
	}

	string WholeData = CombineStrings(AllStu, '^');

	ofstream myfile;
	myfile.open(_Filename);
	myfile << WholeData;
	myfile.close();
}

bool StudentList::Load(string _Filename) {
	ifstream StudentsPointer;
	StudentsPointer.open(_Filename);
	if (StudentsPointer.fail())return false;

	string StudentData;
	getline(StudentsPointer, StudentData);
	if (StudentData != "") {
		vector<string> AllStudents = SplitString(StudentData, '^');

		vector<string>EachStudent;
		StudentNode* StudentPtr;
		CourseNode* CoursePtr;
		for (int i = 0; i < AllStudents.size(); i++) {
			EachStudent = SplitString(AllStudents[i], '~');
			StudentPtr = Add(EachStudent[0], false);
			for (int j = 1; j < EachStudent.size(); j++) {
				CoursePtr = CoursesRefrence->GetCourse(EachStudent[j]);
				(StudentPtr->CoursesTaken).push_back(CoursePtr);
			}
		}
	}

	StudentsPointer.close();
	return true;
}