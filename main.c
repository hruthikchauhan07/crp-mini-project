#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define a structure for User Account
struct User {
    char username[50];
    char password[50];
    char name[100];
    int age;
    char phone_number[15];
    char email[100];
};

// Define a structure for Crime Report
struct CrimeReport {
    char crime_type[50];
    char location[100];
    time_t timestamp;
    int is_ongoing;
    char reporting_status[20];
    char reporter_username[50];
};

// Function to create a new user account
void create_user_account(struct User* users, int* num_users) {
    // Prompt the user to input information for a new user account
    printf("Enter your name: ");
    scanf("%s", users[*num_users].name);

    printf("Enter your age: ");
    scanf("%d", &users[*num_users].age);

    printf("Enter your phone number: ");
    scanf("%s", users[*num_users].phone_number);

    printf("Enter your email: ");
    scanf("%s", users[*num_users].email);

    printf("Create a username: ");
    scanf("%s", users[*num_users].username);

    printf("Create a password: ");
    scanf("%s", users[*num_users].password);

    (*num_users)++;
    printf("Account created successfully.\n");
}

// Function to perform user login
int login(struct User* users, int num_users, char* entered_username, char* entered_password) {
    // Check entered username and password against existing user accounts
    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, entered_username) == 0 && strcmp(users[i].password, entered_password) == 0) {
            printf("Login successful. Welcome, %s!\n", users[i].name);
            return 1;  // Return 1 for successful login
        }
    }

    // Inform the user about invalid login credentials
    printf("Invalid username or password. Please try again.\n");
    return 0;  // Return 0 for unsuccessful login
}

// Function to submit a crime report
void submit_crime_report(struct CrimeReport* reports, int* num_reports, char* reporter_username) {
    // Prompt the user to input information for a new crime report
    printf("Enter crime type: ");
    scanf("%s", reports[*num_reports].crime_type);

    printf("Enter location: ");
    scanf("%s", reports[*num_reports].location);

    reports[*num_reports].timestamp = time(NULL);

    printf("Is the crime ongoing? (1 for yes, 0 for no): ");
    scanf("%d", &reports[*num_reports].is_ongoing);

    strcpy(reports[*num_reports].reporting_status, "Pending");
    strcpy(reports[*num_reports].reporter_username, reporter_username);

    (*num_reports)++;
    printf("Crime report submitted successfully.\n");
}

// Function to display crime reports
void display_crime_reports(struct CrimeReport* reports, int num_reports) {
    // Display information for each crime report
    for (int i = 0; i < num_reports; i++) {
        printf("%d. Type: %s, Location: %s, Timestamp: %ld, Status: %s, Reporter: %s\n",
               i + 1, reports[i].crime_type, reports[i].location,
               reports[i].timestamp, reports[i].reporting_status, reports[i].reporter_username);
    }
}

// Function for police to view reported crimes using master key
void view_reported_crimes(struct CrimeReport* reports, int num_reports) {
    // Prompt the user to enter a master key for police access
    char master_key[50];
    printf("Enter the master key: ");
    scanf("%s", master_key);

    // Basic master key validation (In a real-world scenario, use a more secure authentication mechanism)
    if (strcmp(master_key, "supersecretkey") == 0) {
        // Grant access to view reported crimes
        printf("\nViewing Reported Crimes:\n");
        display_crime_reports(reports, num_reports);
    } else {
        // Deny access if the master key is invalid
        printf("Invalid master key. Access denied.\n");
    }
}

int main() {
    // Define the maximum number of users and reports
    const int MAX_USERS = 100;
    const int MAX_REPORTS = 100;

    // Create arrays to store user accounts and crime reports
    struct User users[MAX_USERS];
    struct CrimeReport reports[MAX_REPORTS];

    // Variables to track the number of users and reports
    int num_users = 0;
    int num_reports = 0;

    // Main menu
    while (1) {
        // Display the main menu options
        printf("\nCrime Reporting Platform\n");
        printf("1. Create User Account\n");
        printf("2. Login\n");
        printf("3. Submit Crime Report\n");
        printf("4. View Crime Reports\n");
        printf("5. Police Access\n");
        printf("6. Exit\n");

        // Prompt the user to select an option
        int choice;
        printf("Enter your choice (1/2/3/4/5/6): ");
        scanf("%d", &choice);

        // Perform actions based on user's choice
        switch (choice) {
            case 1:
                // Create a new user account
                if (num_users < MAX_USERS) {
                    create_user_account(users, &num_users);
                } else {
                    printf("Maximum number of users reached.\n");
                }
                break;

            case 2: {
                // User login
                char entered_username[50];
                char entered_password[50];

                printf("Enter your username: ");
                scanf("%s", entered_username);

                printf("Enter your password: ");
                scanf("%s", entered_password);

                int login_result = login(users, num_users, entered_username, entered_password);
                if (login_result) {
                    // Proceed to user-specific actions after successful login
                    while (1) {
                        printf("\nWelcome, %s!\n", entered_username);
                        printf("1. Submit Crime Report\n");
                        printf("2. View Crime Reports\n");
                        printf("3. Logout\n");

                        // Prompt the user to select an option after login
                        int user_choice;
                        printf("Enter your choice (1/2/3): ");
                        scanf("%d", &user_choice);

                        // Perform actions based on user's choice after login
                        switch (user_choice) {
                            case 1:
                                // Submit a crime report
                                submit_crime_report(reports, &num_reports, entered_username);
                                break;

                            case 2:
                                // View crime reports
                                display_crime_reports(reports, num_reports);
                                break;

                            case 3:
                                // Logout
                                printf("Logging out. Goodbye!\n");
                                login_result = 0;
                                break;

                            default:
                                // Handle invalid choice after login
                                printf("Invalid choice. Please enter 1, 2, or 3.\n");
                        }

                        // Exit the loop if the user logs out
                        if (!login_result) {
                            break;
                        }
                    }
                }
            }
            break;

            case 3:
                // Submit a crime report
                if (num_users > 0) {
                    submit_crime_report(reports, &num_reports, "");
                } else {
                    // Inform the user if no users are available
                    printf("No users available. Please create a user account first.\n");
                }
                break;

            case 4:
                // View crime reports
                display_crime_reports(reports, num_reports);
                break;

            case 5:
                // Police access to view reported crimes
                view_reported_crimes(reports, num_reports);
                break;

            case 6:
                // Exit the program
                printf("Exiting the Crime Reporting Platform. Goodbye!\n");
                exit(0);

            default:
                // Handle invalid choice in the main menu
                printf("Invalid choice. Please enter 1, 2, 3, 4, 5, or 6.\n");
        }
    }

    return 0;
}