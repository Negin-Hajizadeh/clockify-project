/*
This program was created by (Negin Hajizadeh) and delivered as a university project

For compiling : g++ .\main.cpp -std=c++11
*/

//libraries
#include <iostream>
#include <string.h>
#include <ctime>
#include <stdlib.h>

using namespace std;

/* -------------------- Main functions --------------------*/

int start_menu();

void input_start_menu(int command);

void sign_up(); //Sign up function

void login_check();

void login_menu(int id);

void input_login_menu(int command, int id);

void define_new_projects(int id); //Function to create a new project

void record_projects_time(int id); //Record projects time function

void get_time(int id, int a, int taskNum); //Task time recording function

void reporting(int id); //Reporting function

void input_reporting(int id, int command);

void overview_report(int id); //Overview reporting function

void advanced_report(int id); //Advanced reporting function

void projects_settings(int id); //Project settings function

void selected_project(int id, int projNum);

void input_projects_settings(int command, int id, int projNum);

void change_member_num(int id, int projNum); //Function to change the number of team members

void rename_project_manager(int id, int projNum); //Manager rename function

void increase_salaries(int id, int projNum); //Salary increase function

void delete_project(int id, int projNum); //Delete project function

void users_settings(int id);

void input_user_settings(int id, int command);

void username_setting(int id); //Username change function

void phoneNumber_setting(int id); //Phone number change function

void password_setting(int id); //Password changing function

void logout(); //Logout function

void exit(); //Exit function

/* -------------------- Auxiliary functions --------------------*/

int count_small_letters(char array[]); //Capitalization function

int count_capital_letters(char array[]); //Capitalization function

int count_numbers(char array[]); //Number counting function

void matching_user_pass(char username[], char password[]); //Seting username and password function

void username_check(int number); //Function for checking username conditions

void password_check(int number); //Function for checking password conditions

void phoneNumber_check(int number); //Function for checking phone numbwe conditions

bool repeatitous_user(char username[]); //Non-repetition username function

bool repeatitous_project(char project[], int id); //Non-repetition project function

void print_projects(int id); //Show projects list

void total_time(int id); //Calculate the total time of completing all tasks