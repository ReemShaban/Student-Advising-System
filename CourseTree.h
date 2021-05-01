#ifndef CourseTree_h
#define CourseTree_h

#include "Functions.h"

class CourseNode {
public:
	string Name;
	int Weight;

	CourseNode* PreRequisite;
	vector<CourseNode*> PostRequisites;

	CourseNode(string _Name = "", int _Weight = 0, CourseNode* _PreRequisite = 0);
	CourseNode(const CourseNode& OriginalCourse);
};

///////////////////////////////////////////////////////////////////////////////////////////

void SortByPostRequisites(vector<CourseNode*>& _Given);

///////////////////////////////////////////////////////////////////////////////////////////

class CourseTree {
private:
	CourseNode* Root;

public:
	CourseTree();
	~CourseTree();
	CourseNode* AddCourse(string _Name, int _Weight, CourseNode* _PreRequisite = 0, bool _Save = true);
	void DeleteCourse(CourseNode* _Course, bool _PreserveSubTree = false);
	void EditCourse(CourseNode* _Course, string _Name, int _Weight, CourseNode* _PreRequisite, bool _PreserveSubTree = true);
	void Clear();
	vector<vector<CourseNode*>> Traverse(vector<CourseNode*> Siblings = vector<CourseNode*>());
	int TreeOffset(CourseNode* _Course, bool Post = false);
	void PrintTree();
	vector<CourseNode*> Search(string _Name, vector<CourseNode*> Siblings = vector<CourseNode*>());
	CourseNode* GetCourse(string _Name, vector<CourseNode*> Siblings = vector<CourseNode*>());
	vector<CourseNode*> GetRecommended(int _TotalWeight, vector<CourseNode*> _TakenCourses);
	vector<CourseNode*> GetTakables(vector<CourseNode*> _TakenCourses);
	vector<CourseNode*> GetPreRequisites(CourseNode* _Course, vector<CourseNode*> _TakenCourses);
	bool IsCourseTakable(CourseNode* _Course, vector<CourseNode*> _TakenCourses);
	bool IsCourseExist(string _Name);
	bool IsEmpty();
	void Save(string _Filename = "Courses");
	bool Load(string _Filename = "Courses");
};
#endif
