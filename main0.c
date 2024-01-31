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
    struct User* next;
};

// Define a structure for Crime Report
struct CrimeReport {
    char crime_type[50];
    char location[100];
    time_t timestamp;
    int is_ongoing;
    char reporting_status[20];
    char reporter_username[50];
    struct CrimeReport* next;
};

// Function to create a new user account
void insertUser(struct User** head) {
    struct User* newUser = (struct User*)malloc(sizeof(struct User));
    if (newUser == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    printf("Enter your name: ");
    scanf("%s", newUser->name);

    printf("Enter your age: ");
    scanf("%d", &newUser->age);

    printf("Enter your phone number: ");
    scanf("%s", newUser->phone_number);

    printf("Enter your email: ");
    scanf("%s", newUser->email);

    printf("Create a username: ");
    scanf("%s", newUser->username);

    printf("Create a password: ");
    scanf("%s", newUser->password);

    newUser->next = NULL;

    // Insert at the beginning of the list
    newUser->next = *head;
    *head = newUser;

    printf("Account created successfully.\n");
}

// Function to perform user login
int loginUser(struct User* head, char* entered_username, char* entered_password) {
    // Check entered username and password against existing user accounts
    struct User* current = head;
    while (current != NULL) {
        if (strcmp(current->username, entered_username) == 0 && strcmp(current->password, entered_password) == 0) {
            printf("Login successful. Welcome, %s!\n", current->name);
            return 1;  // Return 1 for successful login
        }
        current = current->next;
    }

    // Inform the user about invalid login credentials
    printf("Invalid username or password. Please try again.\n");
    return 0;  // Return 0 for unsuccessful login
}

// Function to submit a crime report
void submitCrimeReport(struct CrimeReport** head, const char* crime_type, const char* location, int is_ongoing, const char* reporter_username) {
    struct CrimeReport* newReport = (struct CrimeReport*)malloc(sizeof(struct CrimeReport));
    if (newReport == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    strcpy(newReport->crime_type, crime_type);
    strcpy(newReport->location, location);
    newReport->timestamp = time(NULL);
    newReport->is_ongoing = is_ongoing;
    strcpy(newReport->reporting_status, "Pending");
    strcpy(newReport->reporter_username, reporter_username);
    newReport->next = NULL;

    // Insert at the beginning of the list
    newReport->next = *head;
    *head = newReport;

    printf("Crime report submitted successfully.\n");
}

void displayCrimeReports(struct CrimeReport* head) {
    struct CrimeReport* current = head;
    // Display information for each crime report
    while (current != NULL) {
        printf("Type: %s, Location: %s, Timestamp: %ld, Status: %s, Reporter: %s\n",
               current->crime_type, current->location, current->timestamp,
               current->reporting_status, current->reporter_username);
        current = current->next;
    }
}

void viewReportedCrimes(struct CrimeReport* head) {
    // Prompt the user to enter a master key for police access
    char master_key[50];
    printf("Enter the master key: ");
    scanf("%s", master_key);

    // Basic master key validation (In a real-world scenario, use a more secure authentication mechanism)
    if (strcmp(master_key, "TMKPOLDPT") == 0) {
        // Grant access to view reported crimes
        printf("\nViewing Reported Crimes:\n");
        displayCrimeReports(head);
    } else {
        // Deny access if the master key is invalid
        printf("Invalid master key. Access denied.\n");
    }
}

int main() {
    // Pointers to the head of linked lists for users and crime reports
    struct User* usersHead = NULL;
    struct CrimeReport* reportsHead = NULL;

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
                insertUser(&usersHead);
                break;

            case 2: {
                // User login
                char entered_username[50];
                char entered_password[50];

                printf("Enter your username: ");
                scanf("%s", entered_username);

                printf("Enter your password: ");
                scanf("%s", entered_password);

                int login_result = loginUser(usersHead, entered_username, entered_password);
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
                                {
                                    char crime_type[50];
                                    char location[100];
                                    int is_ongoing;

                                    printf("Enter crime type: ");
                                    scanf("%s", crime_type);

                                    printf("Enter location: ");
                                    scanf("%s", location);

                                    printf("Is the crime ongoing? (1 for yes, 0 for no): ");
                                    scanf("%d", &is_ongoing);

                                    submitCrimeReport(&reportsHead, crime_type, location, is_ongoing, entered_username);
                                }
                                break;

                            case 2:
                                // View crime reports
                                displayCrimeReports(reportsHead);
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
                {
                    char crime_type[50];
                    char location[100];
                    int is_ongoing;

                    printf("Enter crime type: ");
                    scanf("%s", crime_type);

                    printf("Enter location: ");
                    scanf("%s", location);

                    printf("Is the crime ongoing? (1 for yes, 0 for no): ");
                    scanf("%d", &is_ongoing);

                    submitCrimeReport(&reportsHead, crime_type, location, is_ongoing, "");
                }
                break;

            case 4:
                // View crime reports
                displayCrimeReports(reportsHead);
                break;

            case 5:
                // Police access to view reported crimes
                viewReportedCrimes(reportsHead);
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

    // Free allocated memory before exiting
    struct User* current_user = usersHead;
    struct User* next_user;

    while (current_user != NULL) {
        next_user = current_user->next;
        free(current_user);
        current_user = next_user;
    }

    struct CrimeReport* current_report = reportsHead;
    struct CrimeReport* next_report;

    while (current_report != NULL) {
        next_report = current_report->next;
        free(current_report);
        current_report = next_report;
    }

    return 0;
}
