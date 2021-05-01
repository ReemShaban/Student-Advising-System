#include "Pages.h"

CourseTree* AppCoursesTree = new CourseTree();
StudentList* AppStudentsList = new StudentList(AppCoursesTree);

void ShowQueries() {
	Menu CoursesManMenu("Queries");
	CoursesManMenu.AddItem("View Courses Tree");
	CoursesManMenu.AddItem("View Course Details");
	CoursesManMenu.AddItem("View All Students");
	CoursesManMenu.AddItem("View Student Details");
	CoursesManMenu.AddItem("Student Available Courses");
	CoursesManMenu.AddItem("Student Recommended Courses");
	CoursesManMenu.AddItem("Student Course Availablilty");
	CoursesManMenu.AddItem("Back to Main Menu");

	while (true)
	{
		switch (CoursesManMenu.Show())
		{
		case 0:
			ShowViewTree();
			break;

		case 1:
			ShowViewCourse();
			break;

		case 2:
			ShowViewStudents();
			break;

		case 3:
			ShowStudentDetails();
			break;

		case 4:
			ShowStudentAvailable();
			break;

		case 5:
			ShowStudentRecommended();
			break;

		case 6:
			ShowStudentCourseAvailability();
			break;

		case 7:
		case -2:
			return;

		default:
			continue;
		}
	}
}

void ShowCoursesManagment() {
	Menu CoursesManMenu("Courses Managment");
	CoursesManMenu.AddItem("Add New Course");
	CoursesManMenu.AddItem("Edit Existing Course");
	CoursesManMenu.AddItem("Delete Course");
	CoursesManMenu.AddItem("Delete All Courses");
	CoursesManMenu.AddItem("Back to Main Menu");

	while (true)
	{
		switch (CoursesManMenu.Show())
		{
		case 0:
			ShowAddCourse();
			break;

		case 1:
			ShowEditCourse();
			break;

		case 2:
			ShowDeleteCourse();
			break;

		case 3:
			ShowClearCourses();
			break;

		case 4:
		case -2:
			return;

		default:
			continue;
		}
	}
}

void ShowStudentsManagment() {
	Menu StudentsManMenu("Students Managment");
	StudentsManMenu.AddItem("Add New Student");
	StudentsManMenu.AddItem("Edit Existing Student");
	StudentsManMenu.AddItem("Assign Student Courses");
	StudentsManMenu.AddItem("Remove Student Courses");
	StudentsManMenu.AddItem("Delete Student");
	StudentsManMenu.AddItem("Delete All Students");
	StudentsManMenu.AddItem("Back to Main Menu");

	while (true)
	{
		switch (StudentsManMenu.Show())
		{
		case 0:
			ShowAddStudent();
			break;

		case 1:
			ShowEditStudent();
			break;

		case 2:
			ShowAssignStudentCourses();
			break;

		case 3:
			ShowRemoveStudentCourses();
			break;

		case 4:
			ShowDeleteStudent();
			break;

		case 5:
			ShowClearStudents();
			break;

		case 6:
		case -2:
			return;

		default:
			continue;
		}
	}
}

void ShowSettings() {
	Menu SettingsMenu("Settings");
	SettingsMenu.AddItem("Change Foreground Color");
	SettingsMenu.AddItem("Change Background Color");
	SettingsMenu.AddItem("Change Password");
	SettingsMenu.AddItem("Back to Main Menu");

	while (true)
	{
		switch (SettingsMenu.Show())
		{
		case 0:
			ForegroundColorSetting();
			break;

		case 1:
			BackgroundColorSetting();
			break;

		case 2:
			ShowChangePassword();
			break;

		case 3:
		case -2:
			return;

		default:
			continue;
		}
	}
}

void ShowAboutUs() {
	string About = "With the rapid upsurge of interest toward Nile University,\nmore and more students have been joining every year.\nThat had led to the advisors having a rough time recommending\nand combining the right courses that perfectly suit each student.\n\nTo solve this cumbersome problem,\nwe have developed an advising system that facilitates the process for the advising team\nand helps make the process smoother and more efficient.\nThe program not only displays courses dependency trees\nand states what courses a student can or cannot take based on the courses they have taken before,\nbut it also recommends the best combination of courses for that student,\nwhich as a result simplifies the task for the advisors and saves their time and effort.\n\nSpecial Thanks To\n------------------------\nDr. Mohamed Elhelw\nEng. Shaymaa Sayed ElKaliouby\nEng. Rameez Barakat Hamza\n\nCreated By\n------------------------\nMohamed Ashraf\nReem Tarek\nHanya Mostafa\nAsmaa Elsayed\n\nCopyrights (C) 2020, CS Elite Team.\n";

	system("cls");
	ShowAppLogo();

	cout << endl;
	cout << AllignString("[About Us]", Allign_Center) << endl;
	cout << endl;
	cout << AllignString("----------------------------------", Allign_Center) << endl;
	cout << endl;

	Delay(1000);

	string TStr = "";
	for (int i = 0; i < About.length(); i++) {
		if (About[i] == '\n') {
			cout << AllignString(TStr, Allign_Center) << endl << endl;
			TStr = "";
			Delay(1000);
		}
		else
		{
			TStr += About[i];
		}
	}

	Delay(3000);
	system("pause");
}

///////////////////////////////////////////////////////////////////////////////////////////

void ShowViewTree() {
	system("cls");
	ShowAppLogo();

	cout << endl;
	cout << AllignString("[View Courses Tree]", Allign_Center) << endl;
	cout << endl;
	cout << AllignString("----------------------------------", Allign_Center) << endl;
	cout << endl;

	Delay(500);

	AppCoursesTree->PrintTree();

	Delay(1000);

	cout << endl;
	system("pause");
}
void ShowViewCourse() {
	string LastOutput = ShowAppLogo();

	LastOutput += "\n";
	LastOutput += (AllignString("[View Course Details]", Allign_Center) + "\n");
	LastOutput += (AllignString("----------------------------------", Allign_Center) + "\n");
	LastOutput += "\n";

	string TIL = "";
	vector<string> CoursesNames;
	vector<vector<CourseNode*>> TCourses = AppCoursesTree->Traverse();
	for (int i = 0; i < TCourses.size(); i++) {
		for (int j = 0; j < TCourses[i].size(); j++) {
			CoursesNames.insert(CoursesNames.end(), TCourses[i][j]->Name);
		}
	}

	TIL = "> Please enter the course name you want to view";
	string CN = ComboBox(TIL, LastOutput, CoursesNames, "", true, false);
	if (CN == "-2") {
		return;
	}
	else
	{
		CourseNode* TCourse = AppCoursesTree->GetCourse(CN);

		cout << endl << endl;
		cout << "Course Name: " << TCourse->Name << endl;
		cout << "Course Weight: " << TCourse->Weight << endl;
		cout << "Course Prerequisite Courses: " << endl;
		vector<CourseNode*> Pre = AppCoursesTree->GetPreRequisites(TCourse, vector<CourseNode*>());
		for (int i = 0; i < Pre.size(); i++) {
			cout << "     " << Pre[i]->Name << endl;
		}
		cout << "Courses that can be registered after taking this course: " << endl;
		for (int i = 0; i < TCourse->PostRequisites.size(); i++) {
			cout << "     " << TCourse->PostRequisites[i]->Name << endl;
		}
	}

	Delay(1000);

	cout << endl;
	system("pause");
}
void ShowViewStudents() {
	system("cls");
	ShowAppLogo();

	cout << endl;
	cout << AllignString("[View All Students]", Allign_Center) << endl;
	cout << endl;
	cout << AllignString("----------------------------------", Allign_Center) << endl;
	cout << endl;

	Delay(500);

	for (int i = 0; i < AppStudentsList->Students.size(); i++) {
		cout << "> " << AppStudentsList->Students[i]->Name << endl;
		Delay(35);
	}

	Delay(1000);

	cout << endl;
	system("pause");
}
void ShowStudentDetails() {
	string LastOutput = ShowAppLogo();

	LastOutput += "\n";
	LastOutput += (AllignString("[View Student Details]", Allign_Center) + "\n");
	LastOutput += (AllignString("----------------------------------", Allign_Center) + "\n");
	LastOutput += "\n";

	string TIL = "";
	vector<string> StudentsNames;
	vector<StudentNode*> TStudents = AppStudentsList->Students;
	for (int i = 0; i < TStudents.size(); i++) {
		StudentsNames.insert(StudentsNames.end(), TStudents[i]->Name);
	}

	TIL = "> Please enter the student name you want to view";
	string SN = ComboBox(TIL, LastOutput, StudentsNames, "", true, false);
	if (SN == "-2") {
		return;
	}
	else
	{
		StudentNode* TStudent = AppStudentsList->GetStudent(SN);

		cout << endl << endl;
		cout << "Student Name: " << TStudent->Name << endl;
		int TCH = 0;
		for (int i = 0; i < TStudent->CoursesTaken.size(); i++) {
			TCH += TStudent->CoursesTaken[i]->Weight;
		}
		cout << "Student Completed Credit Hours: " << TCH << endl;
		cout << "Student Taken Courses: " << endl;
		for (int i = 0; i < TStudent->CoursesTaken.size(); i++) {
			cout << "     " << TStudent->CoursesTaken[i]->Name << endl;
		}
	}

	Delay(1000);

	cout << endl;
	system("pause");
}
void ShowStudentAvailable() {
	string LastOutput = ShowAppLogo();

	LastOutput += "\n";
	LastOutput += (AllignString("[Student Available Courses]", Allign_Center) + "\n");
	LastOutput += (AllignString("----------------------------------", Allign_Center) + "\n");
	LastOutput += "\n";

	string TIL = "";
	vector<string> StudentsNames;
	vector<StudentNode*> TStudents = AppStudentsList->Students;
	for (int i = 0; i < TStudents.size(); i++) {
		StudentsNames.insert(StudentsNames.end(), TStudents[i]->Name);
	}

	TIL = "> Please enter the student name you want to view";
	string SN = ComboBox(TIL, LastOutput, StudentsNames, "", true, false);
	if (SN == "-2") {
		return;
	}
	else
	{
		StudentNode* TStudent = AppStudentsList->GetStudent(SN);

		cout << endl << endl;
		cout << "Student Available Courses: " << endl;
		vector<CourseNode*> Takables = AppCoursesTree->GetTakables(TStudent->CoursesTaken);
		for (int i = 0; i < Takables.size(); i++) {
			cout << "     " << Takables[i]->Name << endl;
		}
	}

	Delay(1000);

	cout << endl;
	system("pause");
}
void ShowStudentRecommended() {
	string LastOutput = ShowAppLogo();

	LastOutput += "\n";
	LastOutput += (AllignString("[Student Recommended Courses]", Allign_Center) + "\n");
	LastOutput += (AllignString("----------------------------------", Allign_Center) + "\n");
	LastOutput += "\n";

	string TIL = "";
	vector<string> StudentsNames;
	vector<StudentNode*> TStudents = AppStudentsList->Students;
	for (int i = 0; i < TStudents.size(); i++) {
		StudentsNames.insert(StudentsNames.end(), TStudents[i]->Name);
	}

	TIL = "> Please enter the student name you want to view";
	string SN = ComboBox(TIL, LastOutput, StudentsNames, "", true, false);
	if (SN == "-2") {
		return;
	}
	else
	{
		LastOutput += (TIL + ": " + SN);
		LastOutput += "\n";

		StudentNode* TStudent = AppStudentsList->GetStudent(SN);

		TIL = "> Please enter the required equivilent credit hours";
		string RCH = InputField(TIL, LastOutput, "", false, true);
		if (RCH == "-2") {
			return;
		}
		else
		{
			LastOutput += (TIL + ": " + RCH);
			LastOutput += "\n\n";
			LastOutput += "Student Recommended Courses: \n";

			system("cls");
			cout << LastOutput;

			vector<CourseNode*> Recommended = AppCoursesTree->GetRecommended(atoi(RCH.c_str()), TStudent->CoursesTaken);
			for (int i = 0; i < Recommended.size(); i++) {
				cout << "     " << Recommended[i]->Name << endl;
				LastOutput += "     " + Recommended[i]->Name + "\n";
			}

			Delay(1000);

			vector<int> CTVector;
			CTVector.push_back('Y');
			CTVector.push_back('N');
			TIL = "> Do you want to register these courses to the student now? [Y]es/[N]o";
			switch (Choice(TIL, LastOutput, CTVector))
			{
			case 'y':
			case 'Y':
				for (int i = 0; i < Recommended.size(); i++) {
					TStudent->CoursesTaken.push_back(Recommended[i]);
				}
				
				AppStudentsList->Save();
				cout << endl << ColorString(">> Recommended courses have been assigned to the student succcessfully.", Green) << endl;
				break;

			case 'n':
			case 'N':
				break;

			case -2:
			default:
				return;
			}
		}
	}

	cout << endl;
	system("pause");
}
void ShowStudentCourseAvailability() {
	string LastOutput = ShowAppLogo();

	LastOutput += "\n";
	LastOutput += (AllignString("[Student Course Availablilty]", Allign_Center) + "\n");
	LastOutput += (AllignString("----------------------------------", Allign_Center) + "\n");
	LastOutput += "\n";

	string TIL = "";
	vector<string> StudentsNames;
	vector<StudentNode*> TStudents = AppStudentsList->Students;
	for (int i = 0; i < TStudents.size(); i++) {
		StudentsNames.insert(StudentsNames.end(), TStudents[i]->Name);
	}

	vector<string> CoursesNames;
	vector<vector<CourseNode*>> TCourses = AppCoursesTree->Traverse();
	for (int i = 0; i < TCourses.size(); i++) {
		for (int j = 0; j < TCourses[i].size(); j++) {
			CoursesNames.insert(CoursesNames.end(), TCourses[i][j]->Name);
		}
	}

	TIL = "> Please enter the student name you want to view";
	string SN = ComboBox(TIL, LastOutput, StudentsNames, "", true, false);
	if (SN == "-2") {
		return;
	}
	else
	{
		LastOutput += (TIL + ": " + SN);
		LastOutput += "\n";

		StudentNode* TStudent = AppStudentsList->GetStudent(SN);

		TIL = "> Please enter the course name you want to check for";
		string CN = ComboBox(TIL, LastOutput, CoursesNames, "", true, false);
		if (CN == "-2") {
			return;
		}
		else
		{
			LastOutput += (TIL + ": " + CN);
			LastOutput += "\n\n";

			CourseNode* TCourse = AppCoursesTree->GetCourse(CN);

			if (!VectorContain(TCourse, TStudent->CoursesTaken)) {
				if (AppCoursesTree->IsCourseTakable(TCourse, TStudent->CoursesTaken)) {
					LastOutput += (ColorString("The course '" + TCourse->Name + "' is available for the student to be taken.", Green) + "\n");
					
					system("cls");
					cout << LastOutput;
					
					Delay(1000);

					vector<int> STVector;
					STVector.push_back('Y');
					STVector.push_back('N');
					TIL = "> Do you want to register this course to the student now? [Y]es/[N]o";
					switch (Choice(TIL, LastOutput, STVector))
					{
					case 'y':
					case 'Y':
						TStudent->CoursesTaken.push_back(TCourse);
						AppStudentsList->Save();
						cout << endl << ColorString(">> Course has been assigned to the student succcessfully.", Green) << endl;
						break;

					case 'n':
					case 'N':
						break;

					case -2:
					default:
						return;
					}
				}
				else
				{
					vector<CourseNode*> Pre = AppCoursesTree->GetPreRequisites(TCourse, TStudent->CoursesTaken);
					cout << endl << ColorString((">> This course is not available for this student yet, consider registering at the course '" + Pre[Pre.size() - 1]->Name + "' first."), Red) << endl;
					Delay(1000);
				}
			}
			else
			{
				cout << endl << ColorString((">> This student has already taken this course before."), Red) << endl;

				Delay(1000);
			}
		}
	}

	cout << endl;
	system("pause");
}

void ShowAddCourse() {
	string LastOutput = ShowAppLogo();

	LastOutput += "\n";
	LastOutput += (AllignString("[Add New Course]", Allign_Center) + "\n");
	LastOutput += (AllignString("----------------------------------", Allign_Center) + "\n");
	LastOutput += "\n";

	string TIL = "";

	while (true) {
		TIL = "> Please enter the new course name";
		string NCN = InputField(TIL, LastOutput);
		if (NCN == "-2") {
			return;
		}
		else
		{
			if (!(AppCoursesTree->IsCourseExist(NCN))) {
				LastOutput += (TIL + ": " + NCN);
				LastOutput += "\n";

				TIL = "> Please enter the new course equivilent credit hours";
				string NCW = InputField(TIL, LastOutput, "", false, true);
				if (NCW == "-2") {
					return;
				}
				else
				{
					LastOutput += (TIL + ": " + NCW);
					LastOutput += "\n";

					vector<string> CoursesNames;
					vector<vector<CourseNode*>> TCourses = AppCoursesTree->Traverse();
					for (int i = 0; i < TCourses.size(); i++) {
						for (int j = 0; j < TCourses[i].size(); j++) {
							CoursesNames.insert(CoursesNames.end(), TCourses[i][j]->Name);
						}
					}

					TIL = "> Please enter the new course prerequisite course";
					string NCPr = ComboBox(TIL, LastOutput, CoursesNames, "", true);
					if (NCPr == "-2") {
						return;
					}
					else
					{
						CourseNode* TPrCourse = 0;
						if (NCPr != "") TPrCourse = AppCoursesTree->GetCourse(NCPr);
						AppCoursesTree->AddCourse(NCN, atoi(NCW.c_str()), TPrCourse);

						cout << endl << ColorString(">> New course was added succcessfully.", Green) << endl;
						system("pause");
						return;
					}
				}
			}
			else
			{
				cout << endl << ColorString(">> Another course with this name already exists, please choose another name or edit the existing course.", Red) << endl;
				system("pause");
			}
		}
	}
}
void ShowEditCourse() {
	string LastOutput = ShowAppLogo();

	LastOutput += "\n";
	LastOutput += (AllignString("[Edit Existing Course]", Allign_Center) + "\n");
	LastOutput += (AllignString("----------------------------------", Allign_Center) + "\n");
	LastOutput += "\n";

	string TIL = "";
	vector<string> CoursesNames;
	vector<vector<CourseNode*>> TCourses = AppCoursesTree->Traverse();
	for (int i = 0; i < TCourses.size(); i++) {
		for (int j = 0; j < TCourses[i].size(); j++) {
			CoursesNames.insert(CoursesNames.end(), TCourses[i][j]->Name);
		}
	}

	while (true) {
		TIL = "> Please enter the course name you want to edit";
		string CN = ComboBox(TIL, LastOutput, CoursesNames, "", true, false);
		if (CN == "-2") {
			return;
		}
		else
		{
			LastOutput += (TIL + ": " + CN);
			LastOutput += "\n";

			CourseNode* TCourse = AppCoursesTree->GetCourse(CN);

			while (true) {
				TIL = "> Please enter the new course name";
				string NCN = InputField(TIL, LastOutput, CN);
				if (NCN == "-2") {
					return;
				}
				else
				{
					if (NCN == TCourse->Name || !(AppCoursesTree->IsCourseExist(NCN))) {
						LastOutput += (TIL + ": " + NCN);
						LastOutput += "\n";

						TIL = "> Please enter the new course equivilent credit hours";
						string NCW = InputField(TIL, LastOutput, to_string(TCourse->Weight), false, true);
						if (NCW == "-2") {
							return;
						}
						else
						{
							LastOutput += (TIL + ": " + NCW);
							LastOutput += "\n";

							TIL = "> Please enter the new course prerequisite course";
							string NCPr = ComboBox(TIL, LastOutput, CoursesNames, (TCourse->PreRequisite->Name != "None" ? TCourse->PreRequisite->Name : ""), true);
							if (NCPr == "-2") {
								return;
							}
							else
							{
								LastOutput += (TIL + ": " + NCPr);
								LastOutput += "\n";

								CourseNode* TPrCourse = 0;
								if (NCPr != "") TPrCourse = AppCoursesTree->GetCourse(NCPr);

								bool Preserve = true;

								vector<int> CTVector;
								CTVector.push_back('Y');
								CTVector.push_back('N');
								TIL = "> Do you want to preserve the course subtree? [Y]es/[N]o";
								switch (Choice(TIL, LastOutput, CTVector))
								{
								case 'y':
								case 'Y':
									Preserve = true;
									break;

								case 'n':
								case 'N':
									Preserve = false;
									break;

								case -2:
								default:
									return;
								}

								AppCoursesTree->EditCourse(TCourse, NCN, atoi(NCW.c_str()), TPrCourse, Preserve);

								cout << endl;
								if (!Preserve) cout << ColorString(">> Course subtree was shifted successfully.", Green) << endl;
								cout << ColorString(">> Course was edited succcessfully.", Green) << endl;
								system("pause");
								return;
							}
						}
					}
					else
					{
						cout << endl << ColorString(">> Another course with this name already exists, please choose another name or edit the existing course.", Red) << endl;
						system("pause");
					}
				}
			}
		}
	}
}
void ShowDeleteCourse() {
	string LastOutput = ShowAppLogo();

	LastOutput += "\n";
	LastOutput += (AllignString("[Delete Course]", Allign_Center) + "\n");
	LastOutput += (AllignString("----------------------------------", Allign_Center) + "\n");
	LastOutput += "\n";

	string TIL = "";
	vector<string> CoursesNames;
	vector<vector<CourseNode*>> TCourses = AppCoursesTree->Traverse();
	for (int i = 0; i < TCourses.size(); i++) {
		for (int j = 0; j < TCourses[i].size(); j++) {
			CoursesNames.insert(CoursesNames.end(), TCourses[i][j]->Name);
		}
	}

	while (true) {
		TIL = "> Please enter the course you want to delete";
		string CN = ComboBox(TIL, LastOutput, CoursesNames, "", true, false);
		if (CN == "-2") {
			return;
		}
		else
		{
			LastOutput += (TIL + ": " + CN);
			LastOutput += "\n";

			CourseNode* TCourse = AppCoursesTree->GetCourse(CN);

			bool Preserve = false;

			vector<int> CTVector;
			CTVector.push_back('Y');
			CTVector.push_back('N');
			TIL = "> Do you want to preserve the course subtree? [Y]es/[N]o";
			switch (Choice(TIL, LastOutput, CTVector))
			{
			case 'y':
			case 'Y':
				Preserve = true;
				break;

			case 'n':
			case 'N':
				Preserve = false;
				break;

			case -2:
			default:
				return;
			}

			AppCoursesTree->DeleteCourse(TCourse, Preserve);

			cout << endl;
			if (Preserve) cout << ColorString(">> Course subtree was shifted successfully.", Green) << endl;
			cout << ColorString(">> Course was deleted succcessfully.", Green) << endl;
			system("pause");
			return;
		}
	}
}
void ShowClearCourses() {
	string LastOutput = ShowAppLogo();

	LastOutput += "\n";
	LastOutput += (AllignString("[Delete All Courses]", Allign_Center) + "\n");
	LastOutput += (AllignString("----------------------------------", Allign_Center) + "\n");
	LastOutput += "\n";

	string TIL = "";

	while (true) {
		vector<int> CTVector;
		CTVector.push_back('Y');
		CTVector.push_back('N');
		TIL = "> Are you sure you want to delete everything? [Y]es/[N]o";
		switch (Choice(TIL, LastOutput, CTVector))
		{
		case 'y':
		case 'Y':
			AppCoursesTree->Clear();

			cout << endl << ColorString(">> All courses were deleted succcessfully.", Green) << endl;
			system("pause");
			return;

		case 'n':
		case 'N':
		case -2:
		default:
			return;
		}
	}
}

void ShowAddStudent() {
	string LastOutput = ShowAppLogo();

	LastOutput += "\n";
	LastOutput += (AllignString("[Add New Student]", Allign_Center) + "\n");
	LastOutput += (AllignString("----------------------------------", Allign_Center) + "\n");
	LastOutput += "\n";

	string TIL = "";

	while (true) {
		TIL = "> Please enter the new Student name";
		string NSN = InputField(TIL, LastOutput);
		if (NSN == "-2") {
			return;
		}
		else
		{
			if (NSN != "") {
				if (!(AppStudentsList->IsStudentExist(NSN))) {
					LastOutput += (TIL + ": " + NSN);
					LastOutput += "\n";

					AppStudentsList->Add(NSN);

					cout << endl << ColorString(">> New student was added succcessfully.", Green) << endl;
					system("pause");
					return;
				}
				else
				{
					cout << endl << ColorString(">> Another student with this name already exists, please choose another name or edit the existing student.", Red) << endl;
					system("pause");
				}
			}
		}
	}
}
void ShowEditStudent() {
	string LastOutput = ShowAppLogo();

	LastOutput += "\n";
	LastOutput += (AllignString("[Edit Existing Student]", Allign_Center) + "\n");
	LastOutput += (AllignString("----------------------------------", Allign_Center) + "\n");
	LastOutput += "\n";

	string TIL = "";
	vector<string> StudentsNames;
	vector<StudentNode*> TStudents = AppStudentsList->Students;
	for (int i = 0; i < TStudents.size(); i++) {
		StudentsNames.insert(StudentsNames.end(), TStudents[i]->Name);
	}

	while (true) {
		TIL = "> Please enter the student name you want to edit";
		string SN = ComboBox(TIL, LastOutput, StudentsNames, "", true, false);
		if (SN == "-2") {
			return;
		}
		else
		{
			LastOutput += (TIL + ": " + SN);
			LastOutput += "\n";

			StudentNode* TStudent = AppStudentsList->GetStudent(SN);

			while (true) {
				TIL = "> Please enter the new student name";
				string NSN = InputField(TIL, LastOutput, SN);
				if (NSN == "-2") {
					return;
				}
				else
				{
					if (NSN == TStudent->Name || !(AppStudentsList->IsStudentExist(NSN))) {
						AppStudentsList->Edit(TStudent, NSN);

						cout << endl << ColorString(">> Student was edited succcessfully.", Green) << endl;
						system("pause");
						return;
					}
					else
					{
						cout << endl << ColorString(">> Another student with this name already exists, please choose another name or edit the existing student.", Red) << endl;
						system("pause");
					}
				}
			}
		}
	}
}
void ShowAssignStudentCourses() {
	string LastOutput = ShowAppLogo();

	LastOutput += "\n";
	LastOutput += (AllignString("[Assign Student Courses]", Allign_Center) + "\n");
	LastOutput += (AllignString("----------------------------------", Allign_Center) + "\n");
	LastOutput += "\n";

	string TIL = "";
	vector<string> StudentsNames;
	vector<StudentNode*> TStudents = AppStudentsList->Students;
	for (int i = 0; i < TStudents.size(); i++) {
		StudentsNames.insert(StudentsNames.end(), TStudents[i]->Name);
	}

	vector<string> CoursesNames;
	vector<vector<CourseNode*>> TCourses = AppCoursesTree->Traverse();
	for (int i = 0; i < TCourses.size(); i++) {
		for (int j = 0; j < TCourses[i].size(); j++) {
			CoursesNames.insert(CoursesNames.end(), TCourses[i][j]->Name);
		}
	}

	while (true) {
		TIL = "> Please enter the student name you want to edit";
		string SN = ComboBox(TIL, LastOutput, StudentsNames, "", true, false);
		if (SN == "-2") {
			return;
		}
		else
		{
			LastOutput += (TIL + ": " + SN);
			LastOutput += "\n";

			StudentNode* TStudent = AppStudentsList->GetStudent(SN);

			while (true) {
				TIL = "> Please enter the course name you want to assign";
				string CN = ComboBox(TIL, LastOutput, CoursesNames, "", true, false);
				if (CN == "-2") {
					return;
				}
				else
				{
					string TLastOutput = (LastOutput + (TIL + ": " + CN));
					TLastOutput += "\n";

					CourseNode* TCourse = AppCoursesTree->GetCourse(CN);

					if (!VectorContain(TCourse, TStudent->CoursesTaken)) {
						if (AppCoursesTree->IsCourseTakable(TCourse, TStudent->CoursesTaken)) {
							TStudent->CoursesTaken.push_back(TCourse);
							AppStudentsList->Save();

							TLastOutput += ColorString(">> Course has been assigned to the student succcessfully.", Green);
							TLastOutput += "\n";

							vector<int> STVector;
							STVector.push_back('Y');
							STVector.push_back('N');
							TIL = "> Do you want to add another course to the same student? [Y]es/[N]o";
							switch (Choice(TIL, TLastOutput, STVector))
							{
							case 'y':
							case 'Y':
								break;

							case 'n':
							case 'N':
							case -2:
							default:
								return;
							}
						}
						else
						{
							vector<CourseNode*> Pre = AppCoursesTree->GetPreRequisites(TCourse, TStudent->CoursesTaken);
							cout << endl << ColorString((">> This course is not available for this student yet, consider registering at the course '" + Pre[Pre.size() - 1]->Name + "' first."), Red) << endl;
							system("pause");
						}
					}
					else
					{
						cout << endl << ColorString((">> This student has already taken this course before, consider registering at another course."), Red) << endl;
						system("pause");
					}
					
				}
			}
		}
	}
}
void ShowRemoveStudentCourses() {
	string LastOutput = ShowAppLogo();

	LastOutput += "\n";
	LastOutput += (AllignString("[Remove Student Courses]", Allign_Center) + "\n");
	LastOutput += (AllignString("----------------------------------", Allign_Center) + "\n");
	LastOutput += "\n";

	string TIL = "";
	vector<string> StudentsNames;
	vector<StudentNode*> TStudents = AppStudentsList->Students;
	for (int i = 0; i < TStudents.size(); i++) {
		StudentsNames.insert(StudentsNames.end(), TStudents[i]->Name);
	}

	while (true) {
		TIL = "> Please enter the student name you want to edit";
		string SN = ComboBox(TIL, LastOutput, StudentsNames, "", true, false);
		if (SN == "-2") {
			return;
		}
		else
		{
			LastOutput += (TIL + ": " + SN);
			LastOutput += "\n";

			StudentNode* TStudent = AppStudentsList->GetStudent(SN);

			vector<string> CoursesNames;
			vector<CourseNode*>& TCourses = TStudent->CoursesTaken;
			
			while (true) {
				CoursesNames.clear();
				for (int i = 0; i < TCourses.size(); i++) {
					CoursesNames.insert(CoursesNames.end(), TCourses[i]->Name);
				}

				TIL = "> Please enter the course name you want to remove";
				string CN = ComboBox(TIL, LastOutput, CoursesNames, "", true, false);
				if (CN == "-2") {
					return;
				}
				else
				{
					string TLastOutput = (LastOutput + (TIL + ": " + CN));
					TLastOutput += "\n";

					CourseNode* TCourse = AppCoursesTree->GetCourse(CN);

					TCourses.erase(remove(TCourses.begin(), TCourses.end(), TCourse), TCourses.end());
					AppStudentsList->Save();

					TLastOutput += ColorString(">> Course has been removed from the student succcessfully.", Green);
					TLastOutput += "\n";

					vector<int> STVector;
					STVector.push_back('Y');
					STVector.push_back('N');
					TIL = "> Do you want to remove another course from the same student? [Y]es/[N]o";
					switch (Choice(TIL, TLastOutput, STVector))
					{
					case 'y':
					case 'Y':
						break;

					case 'n':
					case 'N':
					case -2:
					default:
						return;
					}
				}
			}
		}
	}
}
void ShowDeleteStudent() {
	string LastOutput = ShowAppLogo();

	LastOutput += "\n";
	LastOutput += (AllignString("[Delete Student]", Allign_Center) + "\n");
	LastOutput += (AllignString("----------------------------------", Allign_Center) + "\n");
	LastOutput += "\n";

	string TIL = "";
	vector<string> StudentsNames;
	vector<StudentNode*> TStudents = AppStudentsList->Students;
	for (int i = 0; i < TStudents.size(); i++) {
		StudentsNames.insert(StudentsNames.end(), TStudents[i]->Name);
	}

	while (true) {
		TIL = "> Please enter the student name you want to delete";
		string SN = ComboBox(TIL, LastOutput, StudentsNames, "", true, false);
		if (SN == "-2") {
			return;
		}
		else
		{
			LastOutput += (TIL + ": " + SN);
			LastOutput += "\n";

			StudentNode* TStudent = AppStudentsList->GetStudent(SN);

			AppStudentsList->Remove(TStudent);

			cout << endl << ColorString(">> Student was deleted succcessfully.", Green) << endl;
			system("pause");
			return;
		}
	}
}
void ShowClearStudents() {
	string LastOutput = ShowAppLogo();

	LastOutput += "\n";
	LastOutput += (AllignString("[Delete All Students]", Allign_Center) + "\n");
	LastOutput += (AllignString("----------------------------------", Allign_Center) + "\n");
	LastOutput += "\n";

	string TIL = "";

	while (true) {
		vector<int> STVector;
		STVector.push_back('Y');
		STVector.push_back('N');
		TIL = "> Are you sure you want to delete everything? [Y]es/[N]o";
		switch (Choice(TIL, LastOutput, STVector))
		{
		case 'y':
		case 'Y':
			AppStudentsList->Clear();

			cout << endl << ColorString(">> All students were deleted succcessfully.", Green) << endl;
			system("pause");
			return;

		case 'n':
		case 'N':
		case -2:
		default:
			return;
		}
	}
}

void ForegroundColorSetting() {
	Menu ForegroundColorsMenu("Foreground Color");
	ForegroundColorsMenu.AddItem("Black");
	ForegroundColorsMenu.AddItem("Red");
	ForegroundColorsMenu.AddItem("Green");
	ForegroundColorsMenu.AddItem("Yellow");
	ForegroundColorsMenu.AddItem("Blue");
	ForegroundColorsMenu.AddItem("Magenta");
	ForegroundColorsMenu.AddItem("Cyan");
	ForegroundColorsMenu.AddItem("White");
	ForegroundColorsMenu.AddItem("Back to Settings Menu");

	while (true) {
		ForegroundColorsMenu.SelectedIndex = AppSettings.Forecolor;
		int Sel = ForegroundColorsMenu.Show();
		switch (Sel)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			AppSettings.Forecolor = Sel;
			SetScreenColor(AppSettings.Forecolor, AppSettings.Backcolor);
			AppSettings.Save();
			return;

		case 8:
		case -2:
			return;

		default:
			continue;
		}
	}
}
void BackgroundColorSetting() {
	Menu BackgroundColorsMenu("Background Color");
	BackgroundColorsMenu.AddItem("Black");
	BackgroundColorsMenu.AddItem("Red");
	BackgroundColorsMenu.AddItem("Green");
	BackgroundColorsMenu.AddItem("Yellow");
	BackgroundColorsMenu.AddItem("Blue");
	BackgroundColorsMenu.AddItem("Magenta");
	BackgroundColorsMenu.AddItem("Cyan");
	BackgroundColorsMenu.AddItem("White");
	BackgroundColorsMenu.AddItem("Back to Settings Menu");

	while (true) {
		BackgroundColorsMenu.SelectedIndex = AppSettings.Backcolor;
		int Sel = BackgroundColorsMenu.Show();
		switch (Sel)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			AppSettings.Backcolor = Sel;
			SetScreenColor(AppSettings.Forecolor, AppSettings.Backcolor);
			AppSettings.Save();
			return;

		case 8:
		case -2:
			return;

		default:
			continue;
		}
	}
}
void ShowChangePassword() {
	string LastOutput = ShowAppLogo();

	LastOutput += "\n";
	LastOutput += (AllignString("[Change Password]", Allign_Center) + "\n");
	LastOutput += (AllignString("----------------------------------", Allign_Center) + "\n");
	LastOutput += "\n";

	string TIL = "";

	while (true) {
		system("cls");
		cout << LastOutput;

		TIL = "> Please enter your old password first";
		string OP = InputField(TIL, LastOutput, "", true);
		if (HashString(OP) == AppSettings.Password) {
			LastOutput += (TIL + ": " + MaskString(OP));
			LastOutput += "\n";

			TIL = "> Please enter your new password";
			string NP = InputField(TIL, LastOutput, "", true);
			if (NP == "-2") {
				return;
			}
			else
			{
				LastOutput += (TIL + ": " + MaskString(NP));
				LastOutput += "\n";

				while (true) {
					system("cls");
					cout << LastOutput;

					TIL = "> Please re enter your new password";
					string NPP = InputField(TIL, LastOutput, "", true);
					if (NPP == NP) {
						AppSettings.Password = HashString(NP);
						AppSettings.Save();

						cout << endl << ColorString(">> Password changed succcessfully.", Green) << endl;
						system("pause");
						return;
					}
					else if (NPP == "-2") {
						return;
					}
					else
					{
						cout << endl << ColorString(">> Passwords does not match, please try again.", Red) << endl;
						system("pause");
					}
				}
			}
		}
		else if (OP == "-2") {
			return;
		}
		else
		{
			cout << endl << ColorString(">> Incorrect password, please check you input and try again.", Red) << endl;
			system("pause");
		}
	}
}