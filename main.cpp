#include <iostream>
#include <time.h>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//Prototyping
void menu();
void decimelToBinary(int input, const int BASE, vector<int>& binary); // & pass as a refrence
void decimelToHex(int input, const int BASE);
int decimelToOctal(int input, const int BASE, vector<int> octal);
void upcCalculator(string input, int evenTotal, int oddTotal, int oddEven, int result);
void upcChecker(string input, int evenTotal, int oddTotal, int oddEven, int result, int num);
//Asks the user questions with randomly generated numbers and operators. After the 7 questions if correct it will output the time it took you to do it.
//When testing i inputed the wrong anwers to see if the function would tell you that the answer was incorrect aswell as checking if each operator done what it should and not 6 + 6 = 0 
void keepCounting()
{
	//Declare/Initialise variables
	int num[2] = { rand() % 10 };
	int input, answer{}, randNum;
	const char OPERATORS[5] = { '+','-','*','/','%' };

	clock_t start = clock(); //gets start time

	for (int i = 1; i <= 8; i++) {
		num[1] = { rand() % 10 };
		randNum = rand() % sizeof(OPERATORS); //sizeof() -> http://www.cplusplus.com/reference/array/array/size/ :)

		cout << "\nQuestion " << i << ": " << num[0] << OPERATORS[randNum] << num[1] << " = ";

		cin >> input;

		switch (randNum)
		{
		case 0:
			answer = num[0] + num[1];
			break;
		case 1:
			answer = num[0] - num[1];
			break;
		case 2:
			answer = num[0] * num[1];
			break;
		case 3:
			if (num[1] == 0)
			{
				i--;
				cout << "Number cannot be divided by zero. Try again.";
				break;
			}
			answer = num[0] / num[1];
			break;
		case 4:
			answer = num[0] % num[1];
			break;
		default:
			break;
		}

		if (input != answer)
		{
			cout << "\nIncorrect :( The answer was: " << answer << "\n\n";
			break;
		}

		if (i == 8)
		{
			clock_t stop = clock(); //gets end time
			double timeInSeconds = (stop - start) / CLOCKS_PER_SEC; //Get difference in seconds

			cout << "\nQuestions completed in " << timeInSeconds << " seconds\n\n";
			menu();
		}
		num[0] = answer;
	}
	menu();
}
//Declare/Initialise variables which will are passed into functions
//When testing outputed the variables(BASE[2], input) i wanted to pass to ensure that they where correct
void numberConversion()
{
	//Declare/Initialise variables
	int input;
	vector<int> binary;
	vector<int> octal;
	const int BASE[3] = { 2,8,16 };

	cout << "\nNumber Conversion Tool" << endl;
	cout << "===========================================\n";
	cout << "Please enter positive decimal number: ";

	cin >> input;
	//Calling functions
	decimelToBinary(input, BASE[0], binary);
	decimelToHex(input, BASE[2]);
	decimelToOctal(input, BASE[1], octal);
	menu();
}
//Converts the input(decimal) to a Binary value
//When testing i ouputted the remainder when looping then i added it to a vector and reversed it as it was the wrong way around.
void decimelToBinary(int input, const int BASE, vector<int>& binary)
{
	//Declaring variable
	int rem;

	for (int i = 0; input > 0; i++)
	{
		rem = input % BASE;
		input /= BASE; //input = input / base
		binary.push_back(rem); //Inserts rem to the vector
	}

	reverse(begin(binary), end(binary)); // Reverses the vector

	cout << "\nBinary: ";

	for (int j = 0; j < binary.size(); j++) //Loops through the vector 
	{
		cout << binary.at(j); //Outputs the vector
	}
	cout << endl;
}
//Converts the input(decimal) to a Octal value
//When testing i ouputed each variable after it was modified and then executed each scope/line of code.
int decimelToOctal(int input, const int BASE, vector<int> octal)
{
	int rem = input % BASE;
	input /= BASE; //input = input / BASE;

	octal.push_back(rem);//Inserts rem to the vector

	//Calls the function again. if input isn't > 0 it will execute all of the code above this comment.
	if (input > 0)
	{
		return decimelToOctal(input, BASE, octal);
	}

	reverse(begin(octal), end(octal)); // Reverses the vector

	//Found Answer
	cout << "Octal: ";
	for (int i = 0; i < octal.size(); i++) //Loops through the vector
	{
		cout << octal.at(i); //Outputs the vector
	}
	cout << endl;
}

//Converts the input(decimal) to a hex value.
//When testing i ouputed each variable after it was modified and then executed each scope/line of code.
// I also inputed a number which was less than 9 and greater than 9 to ensure both parts of the if statements work
void decimelToHex(int input, const int BASE)
{
	//Declaring Variables
	int rem;
	string result;

	for (int i = 0; input > 0; i++)
	{
		rem = input % BASE;
		input /= BASE; //input = input / base

		if (rem > 9)
		{
			result = (char)(rem - 10 + 'A');
		}
		else
		{
			result += to_string(rem); //result = result + to_string(rem)
		}
	}
	cout << "Hex: " << result << endl;
}

//Calls a specific function if upcOption is true or false
void UPC(bool upcOption)
{
	//Declare/Initialise Variables
	string input;
	int evenTotal = 0;
	int oddTotal = 0;
	int oddEven = 0;
	int result = 0;
	int num = 0;

	upcOption ? upcCalculator(input, evenTotal, oddTotal, oddEven, result) : upcChecker(input, evenTotal, oddTotal, oddEven, result, num);
	menu();
}
//Generates a UPC number from the given algorithm.
//To test if th efunction worked. I executed each scope to ensure it was the ouput i was looking for.
void upcCalculator(string input, int evenTotal, int oddTotal, int oddEven, int result)
{
	cout << "\nUniversal Product Code (UPC) calculator" << endl;
	cout << "===========================================\n";
	cout << "This calculator will take a 6-digit product code";
	cout << "and generate a trailing 7th check digit to produce" << endl;
	cout << "the final 7 - digit UPC." << endl;
	cout << "Please enter 6 - digit code to generate final UPC code : ";

	cin >> input;

	if (input.length() > 6)
	{
		cout << "\nThe product code entered is greater than 6-digits\n\n";
		menu();
	}
	else
	{
		input.insert(0, 6 - input.length(), '0'); //Inserts a string at the start of  another string with 6-input.length() amount of times. Params: (index start, amount, string)
	}

	for (int i = 0; i < input.length(); i++)//adds the odd numbers together and the even numbers together
	{
		int character = (int)input.at(i) - 48;//ASCII: 48 = 0, 49 = 1, 50 = 2, 51 = 3

		(input.at(i) % 2 == 0) ? evenTotal += character : oddTotal += character;
	}

	result = ((3 * oddTotal) + evenTotal) % 10;

	if (result != 0)
	{
		result = 10 - result;
	}

	input = input + to_string(result); //Example input = 123456 + 1
	cout << "\nThe 7 - digit final UPC is : " << input << endl;
	cout << endl;
}
//Checks if inputed number is a valid UPC number.
void upcChecker(string input, int evenTotal, int oddTotal, int oddEven, int result, int num)
{
	/*ALGORITHM:													TEST:
	input upc code													1234561
	sum the digits in the odd positions ignore check digit			1 + 3 + 5
	multiply by 3												    9 * 3 = 27
	sum numbers in the even position ignore check digit				2 + 4 + 6 = 12
	add step 3 and 4												27 + 12 = 39
	subtract the multiple from the next highest multiple of 10		40 - 39  = 1*/

	cout << "\nUniversal Product Code (UPC) Checker" << endl;
	cout << "===========================================" << endl;
	cout << "Please enter 7-digit UPC to check: " << endl;

	cin >> input;

	if (input.length() < 7)
	{
		for (int i = 0; i < input.length() - 1; i++)//adds the odd numbers together and the even numbers together
		{
			int character = (int)input.at(i) - 48;//ASCII: 48 = 0, 49 = 1, 50 = 2, 51 = 3

			(input.at(i) % 2 == 0) ? evenTotal += character : oddTotal += character;
		}
		//Math to find check digit
		oddEven = ((oddTotal * 3) + evenTotal);
		num = oddEven + (10 - oddEven % 10);
		result = num - oddEven;

		if (result != (int)input.back() - 48)
		{
			cout << "\n\nAn error was detected in the UPC\n\n";
		}
		else
		{
			cout << "\n\nUPC is Valid!\n\n";
		}
	}
	else {
		cout << "Invalid UPC";
	}
}
//This function is called first from main and when you enter an option it will call a function otherwise it will print "Invalid Option" as success is false
//To test this function i inputted an int which wasn't an option to ensure it worked and vice versa
void menu()
{
	int input;
	bool success;

	do
	{
		cout << "\nFoP4CS Mini Applicatons \n";
		cout << "===========================================\n";
		cout << "1) Keep Counting Game \n";
		cout << "2 Number Conversion Tool \n";
		cout << "3) Universal Product Code (UPC) Calculator \n";
		cout << "4) Universal Product Code (UPC) Checker \n";
		cout << "9) Quit \n";
		cout << "===========================================\n";
		cout << "Please Select An Option: ";

		cin >> input;

		switch (input)
		{
		case 1:
			keepCounting();
			success = true;
			break;

		case 2:
			numberConversion();
			success = true;
			break;
		case 3:
			UPC(true);
			success = true;
			break;

		case 4:
			UPC(false);
			success = true;
			break;
		case 9:
			exit(NULL);
			break;

		default:
			cout << "\n\nInvalid Option. \n\n";
			success = false;
			break;
		}
	} while (!success);
}

int main()
{
	//Calls functions
	srand((int)time(NULL));
	menu();

	//End of program so it terminates
	system("pause");
	return 0;
}