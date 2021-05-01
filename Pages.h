#ifndef Pages_h
#define Pages_h

#include "Visuals.h"
#include "StudentList.h"

extern CourseTree* AppCoursesTree;
extern StudentList* AppStudentsList;


void ShowQueries();
void ShowCoursesManagment();
void ShowStudentsManagment();
void ShowSettings();
void ShowAboutUs();

///////////////////////////////////////////////////////////////////////////////////////////

void ShowViewTree();
void ShowViewCourse();
void ShowViewStudents();
void ShowStudentDetails();
void ShowStudentAvailable();
void ShowStudentRecommended();
void ShowStudentCourseAvailability();

void ShowAddCourse();
void ShowEditCourse();
void ShowDeleteCourse();
void ShowClearCourses();

void ShowAddStudent();
void ShowEditStudent();
void ShowAssignStudentCourses();
void ShowRemoveStudentCourses();
void ShowDeleteStudent();
void ShowClearStudents();

void ForegroundColorSetting();
void BackgroundColorSetting();
void ShowChangePassword();

#endif
