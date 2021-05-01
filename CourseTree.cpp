#include "CourseTree.h"

CourseNode::CourseNode(string _Name, int _Weight, CourseNode* _PreRequisite) {
	Name = _Name;
	Weight = _Weight;
	PreRequisite = _PreRequisite;
}

CourseNode::CourseNode(const CourseNode& OriginalCourse) {
	Name = OriginalCourse.Name;
	Weight = OriginalCourse.Weight;
	PreRequisite = OriginalCourse.PreRequisite;
	PostRequisites = OriginalCourse.PostRequisites;
}

///////////////////////////////////////////////////////////////////////////////////////////

CourseTree::CourseTree() {
	Root = new CourseNode("None");
}

CourseTree::~CourseTree() {
	delete Root;
}

CourseNode* CourseTree::AddCourse(string _Name, int _Weight, CourseNode* _PreRequisite, bool _Save) {
	if (_PreRequisite == 0) _PreRequisite = Root;

	vector<CourseNode*>& TPostRequisites = _PreRequisite->PostRequisites;
	CourseNode* Course = new CourseNode(_Name, _Weight, _PreRequisite);
	TPostRequisites.insert(TPostRequisites.end(), Course);

	if (_Save) Save();
	return Course;
}

void CourseTree::DeleteCourse(CourseNode* _Course, bool _PreserveSubTree) {
	vector<CourseNode*>& TPrePostRequisites = _Course->PreRequisite->PostRequisites;
	TPrePostRequisites.erase(remove(TPrePostRequisites.begin(), TPrePostRequisites.end(), _Course), TPrePostRequisites.end());

	vector<CourseNode*>& TPostRequisites = _Course->PostRequisites;
	if (_PreserveSubTree) {
		for (int i = 0; i < TPostRequisites.size(); i++) {
			TPrePostRequisites.insert(TPrePostRequisites.end(), TPostRequisites[i]);
			TPostRequisites[i]->PreRequisite = _Course->PreRequisite;
		}
	}
	else
	{
		for (int i = 0; i < TPostRequisites.size(); i++) {
			DeleteCourse(TPostRequisites[i]);
		}
	}

	delete _Course;
	Save();
}

void CourseTree::EditCourse(CourseNode* _Course, string _Name, int _Weight, CourseNode* _PreRequisite, bool _PreserveSubTree) {
	if (_PreRequisite == 0) _PreRequisite = Root;

	if (_PreserveSubTree) {
		_Course->Name = _Name;
		_Course->Weight = _Weight;

		if (_Course->PreRequisite != _PreRequisite) {
			vector<CourseNode*>& TVector = _Course->PreRequisite->PostRequisites;
			TVector.erase(remove(TVector.begin(), TVector.end(), _Course), TVector.end());
			_Course->PreRequisite = _PreRequisite;
			_PreRequisite->PostRequisites.push_back(_Course);
		}
	}
	else
	{
		DeleteCourse(_Course, true);
		AddCourse(_Name, _Weight, _PreRequisite, false);
	}

	Save();
}

void CourseTree::Clear() {
	vector<CourseNode*>& TPostRequisites = Root->PostRequisites;
	for (int i = 0; i < TPostRequisites.size(); i++) {
		DeleteCourse(TPostRequisites[i]);
	}

	Save();
}

vector<vector<CourseNode*>> CourseTree::Traverse(vector<CourseNode*> Siblings) {
	vector<vector<CourseNode*>> Levels;

	if (int(Siblings.size()) == 0) Siblings.insert(Siblings.end(), Root);

	vector<CourseNode*> Results;
	for (int i = 0; i < Siblings.size(); i++) {
		for (int j = 0; j < Siblings[i]->PostRequisites.size(); j++)
		{
			Results.insert(Results.end(), Siblings[i]->PostRequisites[j]);
		}
	}

	if (int(Results.size()) > 0) {
		Levels.insert(Levels.end(), Results);
		vector<vector<CourseNode*>> NLevels = Traverse(Results);
		for (int i = 0; i < NLevels.size(); i++) {
			Levels.insert(Levels.end(), NLevels[i]);
		}
	}

	return Levels;
}

int CourseTree::TreeOffset(CourseNode* _Course, bool Post) {
	int Highest = 0;
	CourseNode* TINode = _Course;
	while (TINode != Root) {
		int THigh = 0;
		if (!Post) {
			for (int q = 0; q < TINode->PreRequisite->PostRequisites.size() && TINode->PreRequisite->PostRequisites[q] != TINode; q++) {
				if (TINode->PreRequisite->PostRequisites[q]->PostRequisites.size() == 0) {
					THigh += (7 + TINode->PreRequisite->PostRequisites[q]->Name.length());
				}
			}
		}
		else
		{
			bool Count = false;
			for (int q = 0; q < TINode->PreRequisite->PostRequisites.size(); q++) {
				if (Count && TINode->PreRequisite->PostRequisites[q]->PostRequisites.size() == 0) THigh += (TINode->PreRequisite->PostRequisites[q]->Name.length() + 7);
				if (TINode->PreRequisite->PostRequisites[q] == TINode) Count = true;
			}
		}

		if (THigh > Highest) Highest = THigh;
		TINode = TINode->PreRequisite;
	}

	return Highest;
}

void CourseTree::PrintTree() {
	string Map = "";
	vector<vector<CourseNode*>> Levels = Traverse();
	vector<int> PrevPos;
	vector<int> PrevOst;
	vector<int> PrevLes;
	for (int i = (Levels.size() - 1); i >= 0 ; i--) {
		int CurrIndex = 0;
		vector<int> CurrPos;
		vector<int> CurrOst;
		vector<int> CurrLes;
		string CLevel[] = { "", "", "" };
		CurrOst.push_back(0);

		for (int j = 0; j < Levels[i].size(); j++)
		{
			CourseNode* TCourse = Levels[i][j];
			
			int TCA = 0;
			int TPPosSC = 0;
			int CTCC = TCourse->PostRequisites.size();
			if (CLevel[0] != "") CLevel[0] += MulString(" ", 8);
			if (i != (Levels.size() - 1) && CTCC > 0) {
				TCA = ((PrevPos[CurrIndex + (CTCC - 1)] + PrevLes[CurrIndex + (CTCC - 1)]) - PrevPos[CurrIndex]);
				TCA = (TCA / 2) - 1;
				TCA -= (TCourse->Name.length() / 2);

				TPPosSC = PrevPos[CurrIndex];
				if (CurrIndex > 0) TPPosSC -= (PrevPos[CurrIndex - 1] + PrevLes[CurrIndex - 1] + 8 + PrevOst[CurrIndex]);
			}

			int TCO[] = {0, 0};
			if (Levels.size() >= 3 && i == (Levels.size() - 1)) {
				int OIndex = 0;
				for (OIndex = 0; OIndex < TCourse->PreRequisite->PostRequisites.size() && TCourse->PreRequisite->PostRequisites[OIndex] != TCourse; OIndex++);
				if (OIndex == 0) {
					TCO[0] = TreeOffset(TCourse->PreRequisite);
				}
				else if (OIndex == (TCourse->PreRequisite->PostRequisites.size() - 1))
				{
					TCO[1] = TreeOffset(TCourse->PreRequisite, true);
				}
			}

			CLevel[0] += MulString(" ", TCA + 1);
			CLevel[0] += MulString(" ", TPPosSC);
			CLevel[0] += MulString(" ", TCO[0]);
			CurrPos.push_back(CLevel[0].length());
			CLevel[0] += TCourse->Name;
			CurrLes.push_back(TCourse->Name.length());
			CLevel[0] += MulString(" ", TCA);
			CLevel[0] += MulString(" ", TCO[1]);
			CurrOst.push_back(TCO[1]);

			if (CLevel[1] != "") CLevel[1] += MulString(" ", 8);
			if (i != 0) {
				int TCB = GetMiddle(TCourse->Name.length()) - 1;
				CLevel[1] += MulString(" ", TCA + 1);
				CLevel[1] += MulString(" ", TPPosSC);
				CLevel[1] += MulString(" ", TCO[0]);
				CLevel[1] += MulString(" ", TCB);
				CLevel[1] += '|';
				CLevel[1] += MulString(" ", TCB);
				CLevel[1] += MulString(" ", TCA);
				CLevel[1] += MulString(" ", TCO[1]);
			}


			CurrIndex += TCourse->PostRequisites.size();
		}

		if (i > 0) {
			vector<int> TPCount;
			for (int p = 0; p < Levels[i - 1].size(); p++) TPCount.push_back(Levels[i - 1][p]->PostRequisites.size());

			int TCC = 0;
			for (int p = 0; p < TPCount.size(); p++) {
				int ITCC = 0;
				int IFPC = 0;
				int IUSC = 0;
				bool Pencil = false;

				for (int v = 0; v < CLevel[1].length(); v++) {
					if (CLevel[1][v] == '|') {
						if (IFPC >= TCC) {
							if (++ITCC <= TPCount[p]) {
								Pencil = true;
								
								if (TPCount[p] == 1) {
									CLevel[2] += '|';
								}
								else
								{
									CLevel[2] += ' ';
								}

								if ((ITCC + 1) > TPCount[p]) {
									Pencil = false;

									if (TPCount[p] > 1) {
										int TMid = GetMiddle(IUSC);
										TMid = CLevel[2].length() - TMid - 1;
										CLevel[2][TMid] = '|';
									}
								}
							}
							else
							{
								break;
							}
						}

						IFPC++;
					}
					else if (Pencil)
					{
						CLevel[2] += '_';
						IUSC++;
					}
					else if (IFPC > TCC || TCC == 0)
					{
						CLevel[2] += ' ';
					}
				}

				TCC += TPCount[p];
			}
		}
		

		Map = (CLevel[0] + '\n') + Map;
		if (i > 0) Map = (CLevel[1] + '\n') + Map;
		if (i > 0) Map = (CLevel[2] + '\n') + Map;

		PrevPos = vector<int>(CurrPos);
		PrevOst = vector<int>(CurrOst);
		PrevLes = vector<int>(CurrLes);
	}

	cout << Map;
}

vector<CourseNode*> CourseTree::Search(string _Name, vector<CourseNode*> Siblings) {
	vector<CourseNode*> Courses;
	if (int(Siblings.size()) == 0) Siblings.insert(Siblings.end(), Root);

	CourseNode* Result = 0;
	vector<CourseNode*> Results;
	for (int i = 0; i < Siblings.size(); i++) {
		for (int j = 0; j < Siblings[i]->PostRequisites.size(); j++)
		{
			Result = Siblings[i]->PostRequisites[j];
			if (Result->Name.rfind(_Name, 0) == 0) {
				Courses.insert(Courses.end(), Result);
			}
			Results.insert(Results.end(), Result);
		}
	}

	if (int(Results.size()) > 0) {
		vector<CourseNode*> NCourses = Search(_Name, Results);
		for (int i = 0; i < NCourses.size(); i++) {
			Courses.insert(Courses.end(), NCourses[i]);
		}
	}

	return Courses;
}

CourseNode* CourseTree::GetCourse(string _Name, vector<CourseNode*> Siblings) {
	if (int(Siblings.size()) == 0) Siblings.insert(Siblings.end(), Root);

	CourseNode* Result = 0;
	vector<CourseNode*> Results;
	for (int i = 0; i < Siblings.size(); i++) {
		for (int j = 0; j < Siblings[i]->PostRequisites.size(); j++)
		{
			Result = Siblings[i]->PostRequisites[j];
			if (Result->Name == _Name) {
				return Result;
			}
			Results.insert(Results.end(), Result);
		}
	}

	if (int(Results.size()) > 0) {
		CourseNode* NResult = GetCourse(_Name, Results);
		if (NResult != 0) return NResult;
	}

	return 0;
}

vector<CourseNode*> CourseTree::GetRecommended(int _TotalWeight, vector<CourseNode*> _TakenCourses) {
	vector<CourseNode*> Results;

	vector<CourseNode*> Takables = GetTakables(_TakenCourses);
	SortByPostRequisites(Takables);

	int CH4 = 0;
	int Total = 0;
	for (int i = 0; i < Takables.size() && Total < _TotalWeight; i++)
	{
		if ((Total + Takables[i]->Weight) <= _TotalWeight) {
			if (Takables[i]->Weight == 4) {
				if (CH4 < 2) {
					CH4++;
				}
				else {
					continue;
				}
			}

			Total += Takables[i]->Weight;
			Results.insert(Results.end(), Takables[i]);
		}
	}

Recheck:
	int Remaining = _TotalWeight - Total;
	if (Remaining > 0) {
		vector<CourseNode*> NotTaken;
		for (int i = 0; i < Takables.size(); i++) {
			if (find(Results.begin(), Results.end(), Takables[i]) == Results.end()) {
				NotTaken.insert(NotTaken.end(), Takables[i]);
			}
		}
		SortByPostRequisites(NotTaken);

		for (int i = 0; i < NotTaken.size(); i++) {
			for (int j = 0; j < Results.size(); j++) {
				if (NotTaken[i]->Weight >= (Results[j]->Weight + Remaining) && (NotTaken[i]->Weight - Results[j]->Weight) <= Remaining) {
					if (NotTaken[i]->Weight == 4) {
						if (CH4 < 2) {
							CH4++;
						}
						else {
							continue;
						}
					}

					Results.erase(remove(Results.begin(), Results.end(), Results[j]), Results.end());
					Results.insert(Results.end(), NotTaken[i]);
					Total += Remaining;

					goto Recheck;
				}

			}
		}
		for (int i = 0; i < NotTaken.size(); i++) {
			for (int k = 0; k < NotTaken.size(); k++) {
				if (NotTaken[i] != NotTaken[k]) {
					for (int j = 0; j < Results.size(); j++) {
						int tmp = NotTaken[i]->Weight + NotTaken[k]->Weight;
						if (tmp >= (Results[j]->Weight + Remaining) && (tmp - Results[j]->Weight) <= Remaining) {
							if (NotTaken[i]->Weight == 4) {
								if (CH4 < 2) {
									CH4++;
								}
								else {
									continue;
								}
							}

							Results.erase(remove(Results.begin(), Results.end(), Results[j]), Results.end());
							Results.insert(Results.end(), NotTaken[i]);
							Results.insert(Results.end(), NotTaken[k]);
							Total += Remaining;

							goto Recheck;
						}
					}
				}
			}
		}
	}

	return Results;
}

vector<CourseNode*> CourseTree::GetTakables(vector<CourseNode*> _TakenCourses) {
	vector<CourseNode*> Takables;
	CourseNode* TNode;

	for (int i = 0; i < Root->PostRequisites.size(); i++) {
		TNode = Root->PostRequisites[i];
		if (find(_TakenCourses.begin(), _TakenCourses.end(), TNode) == _TakenCourses.end()) {
			Takables.insert(Takables.end(), TNode);
		}
	}

	for (int i = 0; i < _TakenCourses.size(); i++) {
		for (int j = 0; j < _TakenCourses[i]->PostRequisites.size(); j++) {
			TNode = _TakenCourses[i]->PostRequisites[j];
			if (find(_TakenCourses.begin(), _TakenCourses.end(), TNode) == _TakenCourses.end()) {
				Takables.insert(Takables.end(), TNode);
			}
		}
	}

	return Takables;
}

vector<CourseNode*> CourseTree::GetPreRequisites(CourseNode* _Course, vector<CourseNode*> _TakenCourses) {
	vector<CourseNode*> PreRequisites;

	CourseNode* TNode = _Course->PreRequisite;
	while (TNode != Root) {
		if (find(_TakenCourses.begin(), _TakenCourses.end(), TNode) != _TakenCourses.end()) {
			break;
		}
		else
		{
			PreRequisites.insert(PreRequisites.end(), TNode);
		}

		TNode = TNode->PreRequisite;
	}

	return PreRequisites;
}

bool CourseTree::IsCourseTakable(CourseNode* _Course, vector<CourseNode*> _TakenCourses) {
	return GetPreRequisites(_Course, _TakenCourses).size() == 0;
}

bool CourseTree::IsCourseExist(string _Name) {
	return GetCourse(_Name) != 0;
}

bool CourseTree::IsEmpty() {
	return Root->PostRequisites.size() > 0;
}

void CourseTree::Save(string _Filename) {
	vector<string>NodeData;
	vector<string>AllTreeNodes;
	string Data;
	vector<vector<CourseNode*>> Levels = Traverse();
	for (int i = 0; i < Levels.size(); i++) {
		for (int j = 0; j < Levels[i].size(); j++) {
			CourseNode* TCourse = Levels[i][j];

			NodeData.push_back(TCourse->Name);
			NodeData.push_back(TCourse->PreRequisite->Name);
			NodeData.push_back(to_string(TCourse->Weight));

			Data = CombineStrings(NodeData, '~');
			AllTreeNodes.push_back(Data);
			NodeData.clear();
		}

	}
	
	string WholeTreeData = CombineStrings(AllTreeNodes, '^');

	ofstream myfile;
	myfile.open(_Filename);
	myfile << WholeTreeData;
	myfile.close();
}

bool CourseTree::Load(string _Filename) {
	ifstream FilePointer, StudentsPointer;
	FilePointer.open(_Filename);
	if (FilePointer.fail()) return false;

	string data;
	getline(FilePointer, data);
	if (data != "") {
		vector<string> ParentTokens = SplitString(data, '^');
		vector<string>ChildTokens;
		for (int i = 0; i < ParentTokens.size(); i++) {
			ChildTokens = SplitString(ParentTokens[i], '~');
			int CreditInt = stoi(ChildTokens[2]);
			if (ChildTokens[1] == "None" || ChildTokens[1] == "none") {
				AddCourse(ChildTokens[0], CreditInt, 0, false);
			}
			else {
				AddCourse(ChildTokens[0], CreditInt, GetCourse(ChildTokens[1]), false);
			}
		}
	}

	FilePointer.close();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////

void SortByPostRequisites(vector<CourseNode*>& _Given) {
	bool Clean = false;
	while (!Clean) {
		Clean = true;
		for (int i = 1; i < _Given.size(); i++) {
			if (_Given[i]->PostRequisites.size() > _Given[i - 1]->PostRequisites.size()) {
				VectorSwap(&_Given[i], &_Given[i - 1]);
				Clean = false;
			}
		}
	}
}