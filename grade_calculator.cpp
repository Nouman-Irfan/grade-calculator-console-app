#include<iostream>
#include<fstream>

using namespace std;

//initialize marks prototype
void initialize(int marks[], int size);

//Read file prototype
void read_file(ifstream& fin, char names[], int marks[], int students);

//Calculate average prototype
void calculateAverage(int marks[], int sum[], int students);

//grade calculator prototype
char calculateGrade(float avg);

//write file prototype
void write_file(ofstream& fout, char names[], int marks[], float avg[], char grade[], int students);

//main function
int main()
{
	int TOTAL_STUDENTS = 0;  // to count total students in file
	char count[100];  // to read lines and count students

    ifstream read("input.txt");  //open file

	if (!read.is_open()) // check if file opened successfully
    {
        cout << "File not found!" << endl;
        return 0;
    }

	// count total students by counting lines in file
    while (read.getline(count, 100))
    {
        TOTAL_STUDENTS++;
    }
	read.close(); //close file after counting students

	// print total students
    cout << "Total Students: " << TOTAL_STUDENTS << endl;

	// declare arrays
	char names[200] = { '\0' };  //it will save all names
    int sum[100]; // to save sum of marks for each student
    int marks[100];   //this array saves the marks size is 50 because total are 10 students and 5 test
    //function calling
    initialize(marks, 100);   

	float avg[100]; // to save average of each student
	char grade[100] = { '\0' }; // to save grade of each student

	//file streams objects
    ifstream fin("input.txt");
    ofstream fout("output.txt");

	// check if file opened successfully
    if (!fin.is_open())
    {
        cout << "File not found!";
        return 0;
    }

	//call read file function to read names and marks from file
    read_file(fin, names, marks, TOTAL_STUDENTS);

	//call calculate average function to calculate average of each student
    calculateAverage(marks, sum, TOTAL_STUDENTS);
    for (int i = 0; i < TOTAL_STUDENTS; i++) //this loop will calculate the averge of students 
    {
        avg[i] = sum[i] / 5.0; 
    }

	// calculate grade for each student
    for (int i = 0; i < TOTAL_STUDENTS; i++)
    {
        grade[i] = calculateGrade(avg[i]);
    }

	//calling write file function to write names, marks, average and grade in output file
    write_file(fout, names, marks, avg, grade, TOTAL_STUDENTS);

	//close file streams objects
    fin.close();
    fout.close();

	//last message on console
    cout << "-----------------------------------------------------------------" << endl;
    cout << "Check output.txt in Project Directory\nGoodBye!!!" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    system("pause");
    return 0;
}
//end of main function
//--------------------------------------------------------------------------------//
//FUNCTION DEFINITIONS
//--------------------------------------------------------------------------------//

//initialize marks function definition
void initialize(int marks[], int size)
{
	for (int i = 0; i < size; i++)  // loop to initialize all marks to 0
        marks[i] = 0;
}

//read file function definition
void read_file(ifstream& fin, char names[], int marks[], int students)
{
	int marks_counter = 0; //marks counter to keep track of marks index in marks array
	int name_counter = 0; //this counter to keep track of names index in names array

	for (int i = 0; i < students; i++)// loop to read each student's name and marks
    {
		char temp_name[20];   // temporary array to read name
        fin >> temp_name;   // read name

        // copy temp into names array
		int j = 0; //counter to copy name character by character from temp to names array
		while (temp_name[j] != '\0') //loop will run until name is fully copied into names array
        {
			// copy character by character
            names[name_counter] = temp_name[j]; 
            name_counter++;
            j++;
        }

		// after copying name, add space to separate names in names array
        names[name_counter] = ' '; // space between names
        name_counter++;

		// read marks for current student
		for (int j = 0; j < 5; j++) // loop to read 5 marks for each student
        {
			//read marks and store in marks array
            fin >> marks[marks_counter];
			marks_counter++;  // increment marks counter to move to next index for next mark
        }
    }
}

//calculate average function definition
void calculateAverage(int marks[], int sum[], int students)
{
	// this function will calculate sum of marks for each student and save in sum array
    int k = 0;
	//loop will calculate sum of marks for each student and save in sum array
    for (int i = 0; i < students; i++)
    {
        sum[i] = 0;

		for (int j = 0; j < 5; j++) // loop to add 5 marks of each student and save in sum array
        {
            sum[i] = sum[i] + marks[k];
			k++; // increment k to move to next mark in marks array
        }
    }
}

//grade calculator function definition
char calculateGrade(float avg)
{
	//this function will return grade based on average marks

	if (avg >= 90 && avg <= 100) //if average is between 90 and 100, return grade A
    {
        return 'A';
    }
	else if (avg >= 80 && avg < 90) //if average is between 80 and 89, return grade B
    {
        return 'B';
    }
	else if (avg >= 70 && avg < 80) //if average is between 70 and 79, return grade C
    {
        return 'C';
    }
	else if (avg >= 60 && avg < 70) //if average is between 60 and 69, return grade D
    {
        return 'D';
    }
	else if (avg >= 0 && avg < 60) //if average is between 0 and 59, return grade F
    {
        return 'F';
    }
	return 'F'; //this return F incase of Invalid average (less than 0 or greater than 100)
}

//definition of write file function
//passing all parameters to write names, marks, average and grade in output file
void write_file(ofstream& fout, char names[], int marks[], float avg[], char grade[], int students) 
{
	//for file output
    fout << "-----------------------------------------------------------------" << endl;
    fout << "Student   Test1   Test2   Test3   Test4   Test5   Average   Grade" << endl;
    fout << "-----------------------------------------------------------------" << endl;
	//for console output
    cout << "-----------------------------------------------------------------" << endl;
    cout << "Student   Test1   Test2   Test3   Test4   Test5   Average   Grade" << endl;
    cout << "-----------------------------------------------------------------" << endl;

	//these counter will keep eye on current index of marks and names array while writing to file
    int marks_counter = 0; //this is counter for marks array
	int name_counter = 0; //this is counter for names array

    //main file writing for loop
	//it is responsible for writing each student's name, marks, average and grade in output file
    for (int i = 0; i < students; i++)
    {
        //names[name_counter] != ' ' this line will print name until space
        while (names[name_counter] != ' ')
        {
			fout << names[name_counter]; //write name char by char in file till space is found
			cout << names[name_counter]; //also print name on console
            name_counter++;
        }

		name_counter++; //moving name counter to next name after space

		fout << "    "; // space after name
        cout << "    ";

		// this loop will write 5 marks for current student in file
        for (int j = 0; j < 5; j++)
        {
            fout << marks[marks_counter] << "      "; //wrietee marks with space on the file
            cout << marks[marks_counter] << "      ";
            marks_counter++;
        }

		// after writing name and marks, write average and grade for current student
        fout << avg[i] << "     " << grade[i] << endl;
        cout << avg[i] << "     " << grade[i] << endl;
    }

    // class average
    float total = 0;
    for (int i = 0; i < students; i++) //this loop add up all averages to calculate class average
    {
        total += avg[i]; //total = total + avg[i]
    }

	// write class average in file by dividing total by number of students
    fout << "-----------------------------------------------------------------" << endl;
    fout << "Class Average = " << total / students << endl;
    fout << "-----------------------------------------------------------------" << endl;
    cout << "-----------------------------------------------------------------" << endl;
    cout << "Class Average = " << total / students << endl;
    cout << "-----------------------------------------------------------------" << endl;
}
