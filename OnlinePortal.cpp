#include<iostream>
#include<fstream>
using namespace std;

class Helper
{
public:
	static int StringLength(char* arr)
	{
		int size = 0;
		for (int i = 0; arr[i] != '\0'; i++)
		{
			size++;
		}
		return size;
	}

	static void StringCopy(char arr[], char* str)
	{
		int len = StringLength(arr);
		for (int i = 0; i <= len; i++)
		{
			str[i] = arr[i];
		}
	}
};

class EvaluationReport
{

	friend void UpdateStatistics(EvaluationReport* obj, int student, int quizzes_no, int assignment_no);

	char Roll_no[9];
	char* Fname;
	char* Lname;
	int* quizzes;
	int* assignment;
	int total;
	static int GrandTotal;
	static int* max;
	static int* min;
	static int* avg;
public:

	EvaluationReport()
	{
		Fname = nullptr;
		Lname = nullptr;
		quizzes = nullptr;
		assignment = nullptr;
		total = 0;
	}

	EvaluationReport(const EvaluationReport &other)
	{
		Roll_no[9];
		Fname = new char[Helper::StringLength(other.Fname) + 1];
		Lname = new char[Helper::StringLength(other.Lname) + 1];
		quizzes = new int[4];
		assignment = new int[4];
		max = new int[8];
		min = new int[8];
		avg = new int[8];

		for (int i = 0; i<9; i++)
		{
			Roll_no[i] = other.Roll_no[i];
		}

		Helper::StringCopy(other.Fname, Fname);
		Helper::StringCopy(other.Lname, Lname);
		for (int i = 0; i < 4; i++) {
			quizzes[i] = other.quizzes[i];
		}
		for (int i = 0; i < 4; i++) {
			assignment[i] = other.assignment[i];
		}
		for (int i = 0; i < 8; i++) {
			max[i] = other.max[i];
			min[i] = other.min[i];
			avg[i] = other.avg[i];
		}
		total = other.total;
	}

	EvaluationReport& EvaluationReport::operator=(const EvaluationReport& other)
	{
		if (this == &other)
			return *this;

		// Copy Roll_no
		for (int i = 0; i < 9; i++)
			Roll_no[i] = other.Roll_no[i];

		// Copy Fname
		int len1 = Helper::StringLength(other.Fname);
		if (Fname != nullptr) delete[] Fname;
		Fname = new char[len1 + 1];
		Helper::StringCopy(other.Fname, Fname);

		// Copy Lname
		int len2 = Helper::StringLength(other.Lname);
		if (Lname != nullptr) delete[] Lname;
		Lname = new char[len2 + 1];
		Helper::StringCopy(other.Lname, Lname);

		// Copy quizzes
		if (quizzes != nullptr) delete[] quizzes;
		quizzes = new int[4];
		for (int i = 0; i < 4; i++)
			quizzes[i] = other.quizzes[i];

		// Copy assignment
		if (assignment != nullptr) delete[] assignment;
		assignment = new int[4];
		for (int i = 0; i < 4; i++)
			assignment[i] = other.assignment[i];

		// Copy total
		total = other.total;

		return *this;
	}

	~EvaluationReport()
	{
		if (Fname != 0)
			delete Fname;
		if (Lname != 0)
			delete Lname;
		if (quizzes != 0)
			delete quizzes;
		if (assignment != 0)
			delete assignment;
	}

	void Print(int quizz_no, int assignment_no)
	{
		cout << Roll_no;
		cout << "\t";
		cout << Fname;
		cout << " ";
		cout << Lname;
		cout << "\t";
		cout << "\t";

		for (int i = 0; i<quizz_no; i++)
		{
			cout << quizzes[i] << " ";
		}
		cout << "\t";

		for (int i = 0; i<assignment_no; i++)
		{
			cout << assignment[i] << " ";
		}

		cout << "\t";

		cout << total;
		cout << endl;
	}
	static void PrintAll(EvaluationReport* arr,int student ,int quizz_no, int assignment_no)
	{
		for(int i=0 ; i<student ; i++)
		{
			arr[i].Print(quizz_no , assignment_no);
		}
	}

	char* GetRollNo()
	{
		return Roll_no;
	}
	char* GetFname()
	{
		return Fname;
	}
	char* GetLname()
	{
		return Lname;
	}
	int* GetQuizzes()
	{
		return quizzes;
	}
	int* GetAssignment()
	{
		return assignment;
	}
	int GetTotal()
	{
		return total;
	}
	static int GetGrandTotal()
	{
		return GrandTotal;
	}
	int* GetMax()
	{
		return max;
	}
	int* GetMin()
	{
		return min;
	}
	int* GetAvg()
	{
		return avg;
	}


	void SetFname(char* arr)
	{
		int len = Helper::StringLength(arr);
		Fname = new char[len+1];
		Helper::StringCopy(arr , Fname);
	}
	void SetLname(char* arr)
	{
		int len = Helper::StringLength(arr);
		Lname = new char[len + 1];
		Helper::StringCopy(arr, Lname);
	}
	void SetTotal(int sum)
	{
		total = sum;
	}
	void SetQuizzes(int* arr , int len)
	{
		quizzes = new int[len];
		for (int i = 0; i < len; i++)
		{
			quizzes[i] = arr[i];
		}
	}
	void SetAssignment(int* arr, int len)
	{
		assignment = new int[len];
		for (int i = 0; i < len; i++)
		{
			assignment[i] = arr[i];
		}
	}
	static void SetGrandTotal(int sum)
	{
		GrandTotal = sum;
	}

};
int* EvaluationReport::max;
int* EvaluationReport::min;
int* EvaluationReport::avg;
int EvaluationReport::GrandTotal;

void ReadDataFromFile(ifstream& inp, EvaluationReport& obj, int quizz_no, int assignment_no)
{
	inp >> obj.GetRollNo();
	char temp[50];
	inp >> temp;
	obj.SetFname(temp);
	inp >> temp;
	obj.SetLname(temp);


	int* temp_int = new int[quizz_no];
	for (int i = 0; i<quizz_no; i++)
	{
		inp >> temp_int[i];
	}
	obj.SetQuizzes(temp_int , quizz_no);
	delete[]temp_int;
	temp_int = 0;

	temp_int = new int[assignment_no];
	for (int i = 0; i<assignment_no; i++)
	{
		inp >> temp_int[i];
	}
	obj.SetAssignment(temp_int , assignment_no);


	int total = 0;
	for(int i=0 ; i<quizz_no ;i++)
	{
		total = obj.GetQuizzes()[i] + total;
	}
	for(int i=0 ; i<assignment_no ;i++)
	{
		total = obj.GetAssignment()[i] + total;
	}
	obj.SetTotal(total);

	delete[]temp_int;
	temp_int = 0;

}

EvaluationReport* SearchStudentsByKeyWord(EvaluationReport* ptr, int no_of_student, char* str, int& searchStudentSize)
{
	int len = Helper::StringLength(str);

	int size = 1;
	EvaluationReport* arr = new EvaluationReport[size];
	int ind_arr = 0;

	for (int i = 0; i < no_of_student; i++)
	{

		bool roll = false;
		bool Fname = false;
		for (int j = 0; j<9; j++)
		{
			if (ptr[i].GetRollNo()[j] == '-')
			{
				continue;
			}
			if (ptr[i].GetRollNo()[j] == str[0])
			{
				bool isFound = true;

				int ind = 0;
				for (int h = j; h<j + len; h++)
				{
					if (ptr[i].GetRollNo()[h] != str[ind])
					{
						isFound = false;
						break;
					}
					ind++;
				}
				if (isFound)
				{
					roll = true;
					arr[ind_arr] = ptr[i];
					ind_arr++;
					EvaluationReport* new_arr = new EvaluationReport[size + 1];
					for (int x = 0; x< size; x++)
					{
						new_arr[x] = arr[x];
					}
					delete[]arr;
					arr = new_arr;
					size++;
				}
			}

		}

		//first name
		if (roll == false)
		{
			int length = Helper::StringLength(ptr[i].GetFname());
			for (int j = 0; j<length; j++)
			{
				if (ptr[i].GetFname()[j] == str[0])
				{
					bool isFound = true;

					int ind = 0;
					for (int h = j; h<j + len; h++)
					{
						if (ptr[i].GetFname()[h] != str[ind])
						{
							isFound = false;
							break;
						}
						ind++;
					}
					if (isFound)
					{
						Fname = true;
						arr[ind_arr] = ptr[i];
						ind_arr++;
						EvaluationReport* new_arr = new EvaluationReport[size + 1];
						for (int x = 0; x< size; x++)
						{
							new_arr[x] = arr[x];
						}
						delete[]arr;

						arr = new_arr;
						size++;
					}
				}

			}
		}

		if (!roll && !Fname)
		{
			int length = Helper::StringLength(ptr[i].GetLname());
			for (int j = 0; j<length; j++)
			{
				if (ptr[i].GetLname()[j] == str[0])
				{
					bool isFound = true;
					int ind = 0;
					for (int h = j; h<j + len; h++)
					{
						if (ptr[i].GetLname()[h] != str[ind])
						{
							isFound = false;
							break;
						}
						ind++;
					}
					if (isFound)
					{
						arr[ind_arr] = ptr[i];
						ind_arr++;
						EvaluationReport* new_arr = new EvaluationReport[size + 1];
						for (int x = 0; x< size; x++)
						{
							new_arr[x] = arr[x];
						}
						delete[]arr;

						arr = new_arr;
						size++;
					}
				}

			}
		}
	}


	searchStudentSize = size - 1;

	return arr;

}

void SortListByTotal(EvaluationReport* &ptr, int students)
{
	for (int i = 0; i<students - 1; i++)
	{
		for (int j = 0; j<students - i - 1; j++)
		{
			if (ptr[j].GetTotal() > ptr[j + 1].GetTotal())
			{
				EvaluationReport temp;
				temp = ptr[j + 1];
				ptr[j + 1] = ptr[j];
				ptr[j] = temp;
			}
		}
	}
}

void UpdateStatistics(EvaluationReport* obj, int student, int quizzes_no, int assignment_no)
{
	EvaluationReport::max = new int[quizzes_no + assignment_no];
	EvaluationReport::min = new int[quizzes_no + assignment_no];
	EvaluationReport::avg = new int[quizzes_no + assignment_no];


	int index = 0;

	for (int i = 0; i<quizzes_no + assignment_no; i++)
	{
		int maxi = -22;
		if (i < quizzes_no)
		{
			for (int j = 0; j<student; j++)
			{
				if (obj[j].quizzes[i] > maxi)
				{
					maxi = obj[j].quizzes[i];
				}
			}
		}
		else
		{
			for (int j = 0; j<student; j++)
			{
				if (obj[j].assignment[index] > maxi)
				{
					maxi = obj[j].assignment[index];
				}
			}
			index++;
		}
		EvaluationReport::max[i] = maxi;
	}


	index = 0;
	for (int i = 0; i<quizzes_no + assignment_no; i++)
	{
		int mini = 100000;
		if (i<quizzes_no)
		{
			for (int j = 0; j<student; j++)
			{
				if (obj[j].quizzes[i] < mini)
				{
					mini = obj[j].quizzes[i];
				}
			}
		}
		else
		{
			for (int j = 0; j<student; j++)
			{
				if (obj[j].assignment[index] < mini)
				{
					mini = obj[j].assignment[index];
				}
			}
			index++;
		}
		EvaluationReport::min[i] = mini;
	}
	int ind_q = 0;
	int ind_a = 0;

	int avg = -1;
	index = 0;

	for (int i = 0; i<quizzes_no + assignment_no; i++)
	{
		int sum = 0;
		if (i < quizzes_no)
		{
			for (int j = 0; j<student; j++)
			{
				sum = sum + obj[j].quizzes[i];
			}
		}
		else
		{
			for (int j = 0; j<student; j++)
			{
				sum = sum + obj[j].assignment[index];
			}
			index++;
		}
		EvaluationReport::avg[i] = sum / student;
	}
}

void SearchByRoll(EvaluationReport* arr, char* rollno, int students, int quizzes, int assignments, int* total_marks_quizzes, int* total_marks_assignments)
{
	for (int i = 0; i<students; i++)
	{
		bool isFound = true;
		for (int j = 0; j<9; j++)
		{
			if (arr[i].GetRollNo()[j] != rollno[j])
			{
				isFound = false;
				break;

			}
		}
		if (isFound)
		{
			cout << "Name:" << arr[i].GetFname() << " " << arr[i].GetLname() << "\t\t" << "Roll # :" << arr[i].GetRollNo() << endl;
			cout << "Quizzes" << endl;
			cout << "\t" << "Total\t" << "Obtained\t" << "Average\t" << "Max\t" << "Min\t" << endl;

			for (int j = 0; j<quizzes; j++)
			{
				cout << j + 1 << "\t" << total_marks_quizzes[j] << "\t" << arr[i].GetQuizzes()[j] << "\t\t" << arr[i].GetAvg()[j] << "\t" << arr[i].GetMax()[j] << "\t" << arr[i].GetMin()[j] << endl;
			}

			cout << "Assignment" << endl;
			cout << "\t" << "Total\t" << "Obtained\t" << "Average\t" << "Max\t" << "Min\t" << endl;
			for (int j = 0; j<assignments; j++)
			{
				cout << j + 1 << "\t" << total_marks_assignments[j] << "\t" << arr[i].GetAssignment()[j] << "\t\t" << arr[i].GetAvg()[j + quizzes] << "\t" << arr[i].GetMax()[j + quizzes] << "\t" << arr[i].GetMin()[j + quizzes] << endl;
			}

			cout << "Grand Total" << endl;
			cout << "Total\tObtained" << endl;
			cout << EvaluationReport::GetGrandTotal() << "\t" << arr[i].GetTotal() << endl;
		}
	}

}

int main()
{
	ifstream obj;
	obj.open("StudentList.txt");
	int total_student = 0, total_quizzes = 0, total_assignment = 0;
	obj >> total_student;
	obj >> total_quizzes;
	obj >> total_assignment;

	int* total_marks_quizzes = new int[total_quizzes];
	int grandTotal = 0;
	for (int i = 0; i<total_quizzes; i++)
	{
		obj >> total_marks_quizzes[i];
		grandTotal = grandTotal + total_marks_quizzes[i];
	}

	int* total_marks_assignment = new int[total_assignment];
	for (int i = 0; i<total_assignment; i++)
	{
		obj >> total_marks_assignment[i];
		grandTotal = grandTotal + total_marks_assignment[i];
	}

	EvaluationReport::SetGrandTotal(grandTotal);

	cout << "Total\t" << "Q1 " << "Q2 " << "Q3 " << "Q4\t" << "A1 " << "A2 " << "A3 " << "A4\t" << endl << "\t";
	for (int i = 0; i<total_quizzes; i++)
	{
		cout << total_marks_quizzes[i] << " ";
	}
	cout << "\t";
	for (int i = 0; i<total_assignment; i++)
	{
		cout << total_marks_assignment[i] << " ";
	}
	cout << endl;



	EvaluationReport* body = new EvaluationReport[total_student];

	cout << "Roll no.\t" << "Name\t\t\t" << "Q1 " << "Q2 " << "Q3 " << "Q4\t" << "A1 " << "A2 " << "A3 " << "A4\t" << "Total" << endl;

	for (int i = 0; i<total_student; i++)
	{
		ReadDataFromFile(obj, body[i], total_quizzes, total_assignment);
	}
	EvaluationReport::PrintAll(body , total_student , total_quizzes , total_assignment);


	char* arr = new char[50];
	cout << "Enter a String = ";
	cin.getline(arr, '\n');

	int search_size = 0;

	EvaluationReport* search = SearchStudentsByKeyWord(body, total_student, arr, search_size);
	if (search_size > 0)
	{
		cout << "Your Searched Student List is Given Below :" << endl << endl;
		EvaluationReport::PrintAll(search , search_size , total_quizzes, total_assignment);
	}
	else
	{
		cout << "No such Student is Found!!!!" << endl << endl;
	}


	SortListByTotal(body, total_student);
	cout << "Sorted List :" << endl << endl;
	EvaluationReport::PrintAll(body , total_student, total_quizzes, total_assignment);
	
	UpdateStatistics(body, total_student, total_quizzes, total_assignment);

	cout << "Search By roll" << endl;
	
	char temporary[9]= "15L-4023";
	/*cin.getline(arr, '\n');*/
	SearchByRoll(body, temporary, total_student, total_quizzes, total_assignment, total_marks_quizzes, total_marks_assignment);


	//deallocation
	delete[]body;
	delete[]arr;
	delete[]search;
	delete[]total_marks_quizzes;
	delete[]total_marks_assignment;

	body = 0;
	arr = 0;
	search = 0;
	total_marks_quizzes = 0;
	total_marks_assignment = 0;

	system("pause");
	return 0;
}