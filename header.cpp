/*
This program was created by (Negin Hajizadeh) and delivered as a university project

For compiling : g++ .\main.cpp -std=c++11
*/

#include "header.hpp"

//Difining fixed values
#define user_num 20
#define project_num 120
#define task_num 120

//Defined structures
struct TASK //Structure for tasks information
{
    char taskName[50], startDateTime[50], endDateTime[50];
    int total_h = 0, total_m = 0, total_s = 0;
};

struct PROJECT //Structure for projects information
{
    char projectName[20], projectManager[20];
    int salary, salaryIncrease, memberNum;
    int last_task = 100;
    TASK tasks[task_num];
};

struct USER //Structure for users information
{
    char firstname[21], lastname[21], phoneNumber[12], username[8], password1[14], password2[14];
    int last_project = 100;
    int tasks_performed = 0;
    PROJECT projects[project_num];
};
USER user[20];

//Global variables
int m, n, o;
int last_user = 0;

/* -------------------- Main functions --------------------*/

int start_menu()
{
    cout << "1. Sign Up"
         << endl
         << "2. Login"
         << endl
         << "3. Exit" << endl;
    cin >> n;
    input_start_menu(n);
}

void input_start_menu(int command)
{
    switch (command)
    {
    case 1:
        sign_up();
        return;
    case 2:
        login_check();
        return;
    case 3:
        exit();
        return;
    default:
        cout << ">> Enter a number between 1 to 3:" << endl;
        start_menu();
        return;
    }
}

void sign_up() //Sign up function
{
    cout << "\n-------------------------- Sign Up Menu ---------------------------" << endl;
    cout << ">> Your first name is: ";
    cin >> user[last_user].firstname; //Get user's firstname
    while (true)                      //Check the conditions for firsrname
    {
        if (strlen(user[last_user].firstname) > 20)
        {
            cout << "The number of characters must be equal to or less than 20.\n>> Enter again: ";
            cin >> user[last_user].firstname;
        }
        else
        {
            break;
        }
    }

    cout << ">> Your last name is: ";
    cin >> user[last_user].lastname; //Get user's lastname
    while (true)                     //Check the conditions for lastname
    {
        if (strlen(user[last_user].lastname) > 20)
        {
            cout << "The number of characters must be equal to or less than 20.\n>> Enter again: ";
            cin >> user[last_user].lastname;
        }
        break;
    }

    cout << ">> Your phone number is: ";
    cin >> user[last_user].phoneNumber; //Get user's phone number
    phoneNumber_check(last_user);       //Check the conditions for phone number

    cout << ">> Your username will be (7 characters): ";
    cin >> user[last_user].username; //Get user's username
    username_check(last_user);       //Check the conditions for username

    cout << ">> Enter your password: ";
    cin >> user[last_user].password1; //Get user's password
    password_check(last_user);        //Check the conditions for password

    cout << ">> Repeat your password: ";
    cin >> user[last_user].password2; //Get user's password again to confirm
    while (true)                      //Check the conditions for confirm password
    {
        if (strcmp(user[last_user].password1, user[last_user].password2) != 0)
        {
            cout << "Passwords are not match.\n>> Enter again: ";
            cin >> user[last_user].password2;
        }
        else
        {
            break;
        }
    }

    last_user++; //Get ready for the next user
    cout << "\n----------------------------- Bitok App -----------------------------\n"
         << "Registration completed successfully... Choose (Login) to continiue:" << endl;
    start_menu();
}

void login_check()
{
    char username[7], password[13];

    cout << ">> Enter your username: ";
    cin >> username; //The username that the user uses to log in
    cout << ">> Enter your password: ";
    cin >> password; //The password that the user uses to log in

    matching_user_pass(username, password); //Seting username and password function
}

void login_menu(int id)
{
    cout << "\nChoose one of the following options:" << endl
         << "1. Define a new project" << endl
         << "2. Record project time" << endl
         << "3. Reporting" << endl
         << "4. Project settings" << endl
         << "5. User settings" << endl
         << "6. Logout from user account" << endl
         << "7. Start menu" << endl;
    cin >> m;
    input_login_menu(m, id);
}

void input_login_menu(int command, int id)
{
    switch (command)
    {
    case 1:

        if (user[id].last_project > 109) //If the user had the maximum number of projects
        {
            cout << "\nThe number of your projects has reached the maximum number, can't create a new project\n";
            login_menu(id); //Go back to login menu
        }

        define_new_projects(id);
        break;
    case 2:
        record_projects_time(id);
        break;
    case 3:
        reporting(id);
        break;
    case 4:
        projects_settings(id);
        break;
    case 5:
        users_settings(id);
        break;
    case 6:
        logout();
        break;
    case 7:
        start_menu();
        break;
    default:
        cout << ">> Enter a number between 1 to 7:" << endl;
        login_menu(id);
        break;
    }
}

void define_new_projects(int id) //Function to create a new project
{
    cout << "\n--------------------- Define a new project Menu --------------------" << endl
         << ">> Create a name for your project: ";
    cin >> user[id].projects[user[id].last_project].projectName; //Get project's name

    while (true) //Check project name conditions
    {
        //Check that the project is not duplicated
        if (repeatitous_project(user[id].projects[user[id].last_project].projectName, id) == true)
        {
            cout << "A project with this name has already been created.\n>> Enter another name: ";
            cin >> user[id].projects[user[id].last_project].projectName;
        }
        else
        {
            break;
        }
    }

    cout << ">> Number of team members: "; //Get number of project's member
    cin >> user[id].projects[user[id].last_project].memberNum;
    while (true) //Check number of project's member conditions
    {
        if (user[id].projects[user[id].last_project].memberNum < 1)
        {
            cout << "Group members must be greater than 0.\n>> Enter again: ";
            cin >> user[id].projects[user[id].last_project].memberNum;
        }
        else
        {
            break;
        }
    }

    cout << ">> Project manager is: "; //Get the name of project's manager
    cin >> user[id].projects[user[id].last_project].projectManager;

    cout << ">> Salary in ($/hour) is: "; //Get project's salary
    cin >> user[id].projects[user[id].last_project].salary;
    while (true) //Check project's salary conditions
    {
        if (user[id].projects[user[id].last_project].salary < 1)
        {
            cout << "Salary must be greater than 0.\n>> Enter again: ";
            cin >> user[id].projects[user[id].last_project].salary;
        }
        else
        {
            break;
        }
    }

    cout << "New project successfully created !\n";
    user[id].last_project++; //Get the next project
    login_menu(id);
}

void record_projects_time(int id) //Record projects time function
{
    cout << "\n--------------------- Record project time Menu ---------------------" << endl
         << "Projects made by you:\n";
    print_projects(id); //Listed the projects

    cout << ">> Enter the desired project number to access the settings: ";
    int a;
    cin >> a;

    cout << "\n------------------- Selected project : ( " << user[id].projects[a + 99].projectName << " ) -------------------" << endl
         << ">> Choose a title for this task: ";
    gets(user[id].projects[a + 99].tasks[user[id].projects[a + 99].last_task].taskName);
    gets(user[id].projects[a + 99].tasks[user[id].projects[a + 99].last_task].taskName);

    int taskNum = user[id].projects[a + 99].last_task;
    user[id].projects[a + 99].last_task++;
    get_time(id, a + 99, taskNum);
}

void get_time(int id, int projNum, int taskNum) //Task time recording function
{
    char word[10];
    time_t start, end;
    cout << "If you want to start the task now, enter the word (start)\nIf you don't, enter (exit): ";
    cin >> word;

    if (strcmp("start", word) == 0) //Performed task
    {
        time(&start); //Task start time and date
        cout << "Your task time has started!\nComplete the project and enter the word (end) when done: ";
        cin >> word;

        if (strcmp("end", word) == 0)
        {
            time(&end); //Task end time and date

            int time_taken = int(end - start);

            char *sd = ctime(&start);
            cout << "\nTask start time: " << sd;
            char *ed = ctime(&end);
            cout << "Task end time: " << ed;

            strcpy(user[id].projects[projNum].tasks[taskNum].startDateTime, sd);
            strcpy(user[id].projects[projNum].tasks[taskNum].endDateTime, ed);

            int seconds, minutes, hours;
            minutes = time_taken / 60;
            seconds = time_taken % 60;
            hours = minutes / 60;
            minutes = minutes % 60;

            cout << "Time to perform this task = " << hours << " : " << minutes << " : " << seconds << endl;

            user[id].projects[projNum].tasks[taskNum].total_h = hours;
            user[id].projects[projNum].tasks[taskNum].total_m = minutes;
            user[id].projects[projNum].tasks[taskNum].total_s = seconds;

            user[id].tasks_performed++;
            cout << "New task successfully created !\n";
            login_menu(id);
        }
    }
    else if (strcmp("exit", word) == 0) //Non-performed task
    {
        cout << "New task successfully created !\n";
        login_menu(id);
    }
    else
    {
        cout << "Wrong input ! Try again.\n\n";
        get_time(id, projNum, taskNum);
    }
}

void reporting(int id) //Reporting function
{
    cout << "\n------------------------ Reporting Menu ------------------------" << endl
         << "1. Overview report\n2. Advanced report\n3. Login menu" << endl
         << ">> Select one of the options above: ";
    int a;
    cin >> a;
    input_reporting(id, a);
}

void input_reporting(int id, int command)
{
    switch (command)
    {
    case 1:
        overview_report(id);
        break;
    case 2:
        advanced_report(id);
        break;
    case 3:
        login_menu(id);
    default:
        cout << "Wrong input !" << endl;
        reporting(id);
        break;
    }
}

void overview_report(int id) //Overview reporting function
{
    cout << "\n---------------------- Overview report Menu ----------------------" << endl
         << "Total number of projects: " << user[id].last_project - 100 << endl
         << "Total number of performed tests: " << user[id].tasks_performed << endl
         << "Total time spent on all the tasks = ";
    total_time(id); //Total time of completed tasks
    cout << endl;
    reporting(id);
}

void advanced_report(int id) //Advanced reporting function
{
    char word1[10], word2[10];
    int projectNum = 0, taskNum = 0;
    int hours = 0, minutes = 0, seconds = 0;

    cout << "\n---------------------- Advanced report Menu ----------------------" << endl
         << "Enter the name of each project and then press Enter Key, then type (end)\n(enter the word (all) if you want all the projects):\n";
    gets(word1);
    while (true)
    {
        gets(word1);

        if (strcmp("all", word1) == 0) //The process of counting all projects
        {
            projectNum = user[id].last_project - 100;
            break;
        }

        if (strcmp("end", word1) == 0) //Complete single project count
        {
            break;
        }

        for (int i = 100; i <= user[id].last_project; i++) //Single project counting process
        {
            if (strcmp(user[id].projects[i].projectName, word1) == 0)
            {
                projectNum++;
            }
        }
    }

    cout << "Enter the name of each task and then press Enter Key, then type (end)\n(enter the word (all) if you want all the tasks):\n";
    while (true)
    {
        gets(word2);
        
        if (strcmp("all", word2) == 0) //The process of counting all tasks
        {
            for (int i = 100; i < user[id].last_project; i++)
            {
                for (int j = 100; j < user[id].projects[i].last_task; j++)
                {
                    taskNum++;
                    hours = hours + user[id].projects[i].tasks[j].total_h;
                    minutes = minutes + user[id].projects[i].tasks[j].total_m;
                    seconds = seconds + user[id].projects[i].tasks[j].total_s;
                }
            }
            break;
        }

        if (strcmp("end", word2) == 0) //Complete single task count
        {
            break;
        }

        for (int i = 100; i < user[id].last_project; i++) //Single task counting process
        {
            for (int j = 100; j < user[id].projects[i].last_task; j++)
            {
                if (strcmp(user[id].projects[i].tasks[j].taskName, word2) == 0)
                {
                    taskNum++;
                    hours = hours + user[id].projects[i].tasks[j].total_h;
                    minutes = minutes + user[id].projects[i].tasks[j].total_m;
                    seconds = seconds + user[id].projects[i].tasks[j].total_s;
                }
            }
        }
    }

    minutes = minutes + (seconds / 60);
    hours = hours + (minutes / 60);
    minutes = minutes % 60; //Remaining minutes
    seconds = seconds % 60; //Remaining seconds

    cout << "Number of projects selected: " << projectNum << endl
         << "Number of tasks selected: " << taskNum << endl
         << "Total time that spent on all tasks = " << hours << " : " << minutes << " : " << seconds << endl;
    reporting(id);
}
void projects_settings(int id) //Project settings function
{
    cout << "\n----------------------- Project settings Menu -----------------------" << endl
         << "Projects made by you:\n";
    print_projects(id);

    cout << "Enter the desired project number to access the settings : ";
    int a;
    cin >> a;
    cout << "\n------------------- Selected project : ( " << user[id].projects[a + 99].projectName << " ) -------------------";
    selected_project(id, a + 99);
}

void selected_project(int id, int projNum)
{
    cout << endl
         << "1. Change the number of project members" << endl
         << "2. Rename the project manager" << endl
         << "3. Increase salaries" << endl
         << "4. Delete project" << endl
         << "5. Go back to Login Menu" << endl
         << ">> Choose one of the options: ";
    cin >> o;
    input_projects_settings(o, id, projNum);
}

void input_projects_settings(int command, int id, int projNum)
{
    switch (command)
    {
    case 1:
        change_member_num(id, projNum);
        break;
    case 2:
        rename_project_manager(id, projNum);
        break;
    case 3:
        increase_salaries(id, projNum);
        break;
    case 4:
        delete_project(id, projNum);
        break;
    case 5:
        login_menu(id);
        break;
    default:
        cout << ">> Enter a number between 1 to 5:" << endl;
        selected_project(id, projNum);
    }
}

void change_member_num(int id, int projNum) //Function to change the number of team members
{
    cout << "\n-------------------- Chang project's member Menu --------------------" << endl
         << ">> Enter a new number of members: ";
    cin >> user[id].projects[projNum].memberNum;
    while (true)
    {
        if (user[id].projects[user[id].last_project].memberNum < 1) //Check the conditions
        {
            cout << "Group members must be greater than 0.\n>> Enter again: ";
            cin >> user[id].projects[user[id].last_project].memberNum;
        }
        break;
    }

    selected_project(id, projNum);
}

void rename_project_manager(int id, int projNum) //Manager rename function
{
    cout << "\n-------------------- Rename project manager Menu --------------------" << endl
         << ">> Enter the name of the new project manager: ";
    cin >> user[id].projects[projNum].projectManager;

    selected_project(id, projNum);
}

void increase_salaries(int id, int projNum) //Salary increase function
{
    cout << "\n---------------------- Increase salaries Menu ----------------------" << endl
         << "The last amount that is considered as salary: " << user[id].projects[projNum].salary << endl
         << ">> Enter a new salary: ";
    cin >> user[id].projects[projNum].salaryIncrease; //New salary amount
    while (true)
    {
        if (user[id].projects[projNum].salaryIncrease <= user[id].projects[projNum].salary) //Compare salaries
        {
            cout << "The new salary should be higher than the previous one!\n>> Enter again: ";
            cin >> user[id].projects[projNum].salaryIncrease;
        }
        break;
    }

    cout << "New salary is: " << user[id].projects[projNum].salaryIncrease << " $/hour" << endl;
    selected_project(id, projNum);
}

void delete_project(int id, int projNum) //Delete project function
{
    cout << "\n----------------------- Delete project Menu -----------------------" << endl;
    if (user[id].last_project == 101) //If we had only one project
    {
        cout << "You only have one project and you can not delete it!\n";
        selected_project(id, projNum);
    }
    else
    {
        user[id].last_project--; //Delete project

        cout << "The project completely deleted.\nNew list is:\n";
        for (int i = 100; i < projNum; i++) //Related to previous projects
        {
            cout << i - 99 << ". " << user[id].projects[i].projectName << endl;
        }

        for (int i = projNum; i < user[id].last_project; i++) //Related to next projects
        {
            user[id].projects[i] = user[id].projects[i + 1];
            cout << i - 99 << ". " << user[id].projects[i].projectName << endl;
        }

        selected_project(id, projNum);
    }
}

void users_settings(int id)
{
    cout << "\n----------------------- User settings Menu ------------------------" << endl
         << "1. Username\n2. Phone number\n3. Password\n4. Login menu" << endl
         << ">> Select one of the options above to make the change: ";
    int a;
    cin >> a;
    input_user_settings(id, a);
}

void input_user_settings(int id, int command)
{
    switch (command)
    {
    case 1:
        username_setting(id);
        return;
    case 2:
        phoneNumber_setting(id);
        return;
    case 3:
        password_setting(id);
        return;
    case 4:
        login_menu(id);
        return;
    default:
        cout << "Wrong input !" << endl;
        users_settings(id);
        break;
    }
}

void username_setting(int id) //Username change function
{
    cout << "\n----------------------- Username setting Menu ----------------------" << endl
         << ">> Enter the new username: ";
    cin >> user[id].username;
    username_check(id); //Check the conditions
    cout << "Username changed successfully !\n";
    users_settings(id);
}

void phoneNumber_setting(int id) //Phone number change function
{
    cout << "\n-------------------- Phone number setting Menu ---------------------" << endl
         << ">> Enter the new phone number: ";
    cin >> user[id].phoneNumber;
    phoneNumber_check(id); //Check the conditions
    cout << "Phone number changed successfully !\n\n";
    users_settings(id);
}

void password_setting(int id) //Password changing function
{
    cout << "\n----------------------- Password setting Menu ----------------------" << endl
         << ">> Enter the previous password: ";
    cin >> user[id].password1; //Enter the previous password

    while (true) //Check the conditions
    {
        if (strcmp(user[id].password2, user[id].password1) == 0) //If the previous password was entered correctly
        {
            cout << ">> Enter the new password: ";
            cin >> user[id].password1;
            password_check(id);
            strcpy(user[id].password2, user[id].password1); //Set a new password
            cout << "Password changed successfully !\n\n";
            users_settings(id);
        }
        else
        {
            cout << "The previous password was incorrect.\n>> Enter again: "; //If the previous password wasn't entered correctly
            cin >> user[id].password1;
        }
    }
}

void logout() //Logout function
{
    cout << "\nYou are successfully loged out.\nChoose again:\n";
    start_menu();
}

void exit() //Exit function
{
    return;
}

/* -------------------- Auxiliary functions --------------------*/

int count_small_letters(char array[]) //Capitalization function
{
    int count = 0;

    for (int i = 0; i < strlen(array); i++)
    {
        if (array[i] >= 'a' && array[i] <= 'z')
        {
            count++; //Count small letters
        }
    }

    return count;
}

int count_capital_letters(char array[]) //Capitalization function
{
    int count = 0;

    for (int i = 0; i < strlen(array); i++)
    {
        if (array[i] >= 'A' && array[i] <= 'Z')
        {
            count++; //Count capital letters
        }
    }
    return count;
}

int count_numbers(char array[]) //Number counting function
{
    int count = 0;

    for (int i = 0; i < strlen(array); i++)
    {
        if (array[i] >= '0' && array[i] <= '9')
        {
            count++; //Counting numbers
        }
    }
    return count;
}

void matching_user_pass(char username[], char password[]) //Seting username and password function
{
    for (int id = 0; id <= last_user; id++)
    {
        if (strcmp(user[id].username, username) == 0)
        {
            if (strcmp(user[id].password2, password) == 0)
            {
                cout << "\n------------------------- Bitok Login Menu -------------------------\n"
                     << "Welcome back to your bitok account dear " << user[id].firstname << " !";

                if (user[id].last_project == 100)
                {
                    cout << user[id].firstname << ", this is the first time you enter to Bitok app!\nSo you must create a project.\n";
                    define_new_projects(id);
                }
                else
                {
                    login_menu(id);
                }
            }
            else
            {
                cout << "Password is not correct. Try again!\n";
                login_check();
            }
        }
    }

    cout << "\nA user with this username is not registered in the program.\n";
}

void username_check(int number) //Function for checking username conditions
{
    while (true)
    {
        if (strlen(user[number].username) == 7) //Have 7 characters
        {
            if (user[number].username[0] == '9') //Starts with the number 9
            {
                if (user[number].username[6] == '3' || user[number].username[6] == '5') // Ends to 3 or 5
                {
                    if (repeatitous_user(user[number].username) == false) //Non-repetitious of usernames
                    {
                        break;
                    }
                    else //Repetitious username
                    {
                        cout << "This username already used.\n>> Enter again: ";
                        cin >> user[number].username;
                    }
                }
                else // It does not end in 3 or 5
                {
                    cout << "The last digit of the student number must be 3 or 5.\n>> Enter again: ";
                    cin >> user[number].username;
                }
            }
            else //It does not start with 9
            {
                cout << "The first digit of the student number must be 9.\n>> Enter again: ";
                cin >> user[number].username;
            }
        }
        else //It does not have 7 characters
        {
            cout << "The number of characters was not 7.\n>> Enter again: ";
            cin >> user[number].username;
        }
    }
}

void password_check(int number) //Function for checking password conditions
{
    while (true)
    {
        // Checking password length
        if (strlen(user[number].password1) < 8 || strlen(user[number].password1) > 13)
        {
            cout << "The number of characters must be between 8 and 13.\n>> Enter again: ";
            cin >> user[number].password1;
        }
        else //Checking password conditions
        {
            while (true)
            {
                //Check the number of lowercase letters
                if (count_small_letters(user[number].password1) == 0)
                {
                    cout << "At least one lowercase letter must be used.\n>> Enter again: ";
                    cin >> user[number].password1;
                }
                else
                {
                    break;
                }
            }

            while (true)
            {
                //Check the number of uppercase letters
                if (count_capital_letters(user[number].password1) == 0)
                {
                    cout << "At least one capital letter must be used.\n>> Enter again: ";
                    cin >> user[number].password1;
                }
                else
                {
                    break;
                }
            }

            while (true)
            {
                //Check the number of numbers
                if (count_numbers(user[number].password1) == 0)
                {
                    cout << "At least one number must be used.\n>> Enter again: ";
                    cin >> user[number].password1;
                }
                else
                {
                    break;
                }
            }
            break;
        }
    }
}

void phoneNumber_check(int number) //Function for checking phone number conditions
{
    while (true)
    {
        //Condition of starting the phone number with 09
        if (user[number].phoneNumber[0] != '0' && user[number].phoneNumber[1] != '9')
        {
            cout << "Phone number must start with 09 (exp: 09xxxxxxxxx): ";
            cin >> user[number].phoneNumber;
        }
        //Checking the number of characters
        else if (strlen(user[number].phoneNumber) != 11)
        {
            cout << "The number of characters must be 11.\n>> Enter again: ";
            cin >> user[number].phoneNumber;
        }
        else
        {
            break;
        }
    }
}

bool repeatitous_user(char username[]) //Non-repetition username function
{
    int count = 0;

    for (int i = 0; i <= last_user; i++)
    {
        if (strcmp(user[i].username, username) == 0)
        {
            count++; //Count the number of repetitions of the username
        }
    }

    /* It needs to be explained that because the username is first input,
    it is stored in the structure, so the unique usernames are always 1 ...
    so if (count) equals 1, it indicates that the username is unique. */
    if (count == 1)
    {
        return false; //means: the username is unique
    }
    else
    {
        return true; //means: the username is not unique
    }
}

bool repeatitous_project(char project[], int id) //Non-repetition project function
{
    int count = 0;

    for (int i = 100; i <= user[id].last_project; i++)
    {
        if (strcmp(user[id].projects[i].projectName, project) == 0)
        {
            count++; //Count the number of repetitions of the username
        }
    }

    /* It needs to be explained that because the project is first input,
    it is stored in the structure, so the unique projects are always 1 ...
    so if (count) equals 1, it indicates that the project is unique. */
    if (count == 1)
    {
        return false; //means: the username is unique
    }
    else
    {
        return true; //means: the username is not unique
    }
}

void print_projects(int id) //Show projects list
{
    for (int i = 100; i < user[id].last_project; i++)
    {
        cout << i - 99 << ". " << user[id].projects[i].projectName << endl;
    }
}

void total_time(int id) //Calculate the total time of completing all tasks
{
    int hours = 0, minutes = 0, seconds = 0;
    for (int i = 100; i < user[id].last_project; i++)
    {
        for (int j = 100; j < user[id].projects[i].last_task; j++)
        {
            hours = hours + user[id].projects[i].tasks[j].total_h;     //Total hours
            minutes = minutes + user[id].projects[i].tasks[j].total_m; //Total minutes
            seconds = seconds + user[id].projects[i].tasks[j].total_s; //Total seconds
        }
    }

    minutes = minutes + (seconds / 60);
    hours = hours + (minutes / 60);
    minutes = minutes % 60; //Remaining minutes
    seconds = seconds % 60; //Remaining seconds

    cout << hours << " : " << minutes << " : " << seconds;
}