#include <Python.h> //For python
#include <iostream> //For basic commands
#include <Windows.h> //For header material
#include <cmath> //For any advanced maths
#include <string> //For strings
#include <stdlib.h> //For library
#include <conio.h> //For console input and output
#include <ctype.h> //For mapping chars
#include <fstream> //For creating fstream strings
#include <vector> //For creating vectors
#include <iomanip> //For manipulating strings

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


void main()
{
	int selection = 0, itemNum = 0, checker = 0; //Initialize values
	string storeItemIndividual; //Initialize input string for option 2
	char continueKey = 'x'; //For continue screens

	while (checker == 0) //Keeps the loop going until exit, for safety measures
	{
		//Main Menu
		system("CLS");
		cout << "==============================================================================" << endl;
		cout << "                                 Corner Grocer                                " << endl;
		cout << "==============================================================================" << endl << endl;
		cout << "Option 1: List all purchased items" << endl << endl;
		cout << "Option 2: List information about a specific item" << endl << endl;
		cout << "Option 3: Create a histogram of daily purchased items" << endl << endl;
		cout << "Option 4: Exit Program" << endl;
		cout << "Please choose your selection using a number 1, 2, or 3." << endl;
		cin >> selection;

		//Check for failed inputs or pointless numbers
		while (cin.fail() || selection > 4 || selection < 1)
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Please input a valid number 1, 2, or 3." << endl;
			cin >> selection;
		}

		//Check selection
		switch (selection) {

		case 1:
			system("CLS"); //Clear screen



			CallProcedure("PrintAllItems"); //Call Python Function
			cout << "Press any key to return to the main menu" << endl;

			continueKey = _getch(); //Gets first input

			break;

		case 2:
			while (continueKey != 'q') //Allows for multiple inputs
			{
				system("CLS");

				cout << "Type the item you wish to find" << endl;
				cin >> storeItemIndividual;

				itemNum = callIntFunc("PrintItem", storeItemIndividual); //Call Python Function

				cout << storeItemIndividual << " was purchased " << itemNum << " times." << endl << endl;
				cout << "To return to the main menu, press q." << endl;
				cout << "To input another item, press any other key." << endl;

				continueKey = _getch(); //Get first char
			}
			continueKey = 'x'; //Reset char for future attempts
			break;

		case 3:
		{ //Brackets were required for ifstream access issues
			system("CLS");
			CallProcedure("PrintHistogram"); //Call Python Function to create .dat file

			ifstream dataFile; //Initialize file accessor
			dataFile.open("frequency.dat"); //Open file
			string storeItem;
			int numberItem;

			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //Used for creating colored text

			cout << endl << "Below is a histogram based on the data file:" << endl;
			while (dataFile >> storeItem >> numberItem) //Continues for length of file
			{
				SetConsoleTextAttribute(hConsole, numberItem + 1); //Adds color to text, 1 is too dark so +1 was added to ensure that color was not used
				cout << left << setw(15) << storeItem; //Output item with proper formatting
				for (int i = 0; i < numberItem; i++) //Outputs the histogram
				{
					cout << "*";
				}
				cout << endl;
			}

			dataFile.close(); //Close file
			SetConsoleTextAttribute(hConsole, 7); //Reset color
			cout << "Press any key to return to the main menu" << endl;

			continueKey = _getch(); //Get first char
			break;
		}

		case 4:
			exit(0); //Exits program
		default:
			break;

		}

	}


}