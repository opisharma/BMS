#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50
#define MAX_PHONE 15
#define MAX_ADDRESS 100
#define MAX_EMAIL 50
#define MAX_CITIZ 20

typedef struct {
    int account;
    char name[MAX_NAME];
    char phone[MAX_PHONE];
    char address[MAX_ADDRESS];
    char email[MAX_EMAIL];
    char citiz[MAX_CITIZ];
    double blnc;
} Record;

Record rec;

void menu();
void add();
void view();
void edit();
void del();
void search();
void search_acc();
void search_name();
void menuexit();
void about();
void transaction();
void deposit();
void withdrawl();
void chkblnc();
void transfer();

int main() {
    menu();
    return 0;
}

void menu() {
    int choice;
    do {
        printf("\n\t\tTEAM HYPERTEXT ASSASSAIN\n");
        printf("\n\t\t  BANKING SYSTEM MENU\n");
        printf("1. Add Customer\n");
        printf("2. View Customers\n");
        printf("3. Edit Customer\n");
        printf("4. Delete Customer\n");
        printf("5. Search Customer\n");
        printf("6. Transactions\n");
        printf("7. About\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: add(); break;
            case 2: view(); break;
            case 3: edit(); break;
            case 4: del(); break;
            case 5: search(); break;
            case 6: transaction(); break;
            case 7: about(); break;
            case 8: menuexit(); break;
            default: printf("Invalid choice. Try again.\n");
        }
    } while (choice != 8);
}

void add() {
    FILE *f = fopen("record.bin", "ab");
    if (!f) {
        perror("Error opening file");
        return;
    }
    printf("\n\t\tADD CUSTOMER ACCOUNT\n");
    printf("Enter Account Number: ");
    scanf("%d", &rec.account);
    printf("Enter Name: ");
    scanf(" %[^\n]", rec.name);
    printf("Enter Phone Number: ");
    scanf(" %[^\n]", rec.phone);
    printf("Enter Address: ");
    scanf(" %[^\n]", rec.address);
    printf("Enter E-mail: ");
    scanf(" %[^\n]", rec.email);
    printf("Enter Citizenship No.: ");
    scanf(" %[^\n]", rec.citiz);
    printf("Enter Balance: $");
    scanf("%lf", &rec.blnc);
    fwrite(&rec, sizeof(rec), 1, f);
    fclose(f);
    printf("Record Successfully Added.\n");
}

void view() {
    FILE *f = fopen("record.bin", "rb");
    if (!f) {
        perror("Error opening file");
        return;
    }
    printf("\n\t\tVIEW CUSTOMER ACCOUNTS\n");
    while (fread(&rec, sizeof(rec), 1, f)) {
        printf("Account Number: %d\n", rec.account);
        printf("Name: %s\n", rec.name);
        printf("Phone Number: %s\n", rec.phone);
        printf("Address: %s\n", rec.address);
        printf("E-mail: %s\n", rec.email);
        printf("Citizenship No.: %s\n", rec.citiz);
        printf("Balance: $%.2lf\n", rec.blnc);
        printf("------------------------------------------------\n");
    }
    fclose(f);
}

void edit() {
    int acc_no;
    FILE *f = fopen("record.bin", "rb");
    FILE *temp = fopen("temp.bin", "wb");
    if (!f || !temp) {
        perror("Error opening file");
        return;
    }
    printf("\n\t\tEDIT CUSTOMER ACCOUNT\n");
    printf("Enter Account Number: ");
    scanf("%d", &acc_no);
    while (fread(&rec, sizeof(rec), 1, f)) {
        if (rec.account == acc_no) {
            printf("Enter New Name: ");
            scanf(" %[^\n]", rec.name);
            printf("Enter New Phone Number: ");
            scanf(" %[^\n]", rec.phone);
            printf("Enter New Address: ");
            scanf(" %[^\n]", rec.address);
            printf("Enter New E-mail: ");
            scanf(" %[^\n]", rec.email);
            printf("Enter New Citizenship No.: ");
            scanf(" %[^\n]", rec.citiz);
            printf("Enter New Balance: $");
            scanf("%lf", &rec.blnc);
        }
        fwrite(&rec, sizeof(rec), 1, temp);
    }
    fclose(f);
    fclose(temp);
    remove("record.bin");
    rename("temp.bin", "record.bin");
    printf("Record Successfully Updated.\n");
}

void del() {
    int acc_no;
    FILE *f = fopen("record.bin", "rb");
    FILE *temp = fopen("temp.bin", "wb");
    if (!f || !temp) {
        perror("Error opening file");
        return;
    }
    printf("\n\t\tDELETE CUSTOMER ACCOUNT\n");
    printf("Enter Account Number to delete: ");
    scanf("%d", &acc_no);
    while (fread(&rec, sizeof(rec), 1, f)) {
        if (rec.account != acc_no) {
            fwrite(&rec, sizeof(rec), 1, temp);
        }
    }
    fclose(f);
    fclose(temp);
    remove("record.bin");
    rename("temp.bin", "record.bin");
    printf("Record Successfully Deleted.\n");
}

void search() {
    int choice;
    printf("\n\t\tSEARCH CUSTOMER ACCOUNT\n");
    printf("1. Search by Account Number\n");
    printf("2. Search by Name\n");
    printf("3. Go Back\n");
    printf("Enter Your Choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1: search_acc(); break;
        case 2: search_name(); break;
        case 3: return;
        default: printf("Invalid choice. Try again.\n"); search();
    }
}

void search_acc() {
    int acc_no;
    FILE *f = fopen("record.bin", "rb");
    if (!f) {
        perror("Error opening file");
        return;
    }
    printf("\n\t\tSEARCH BY ACCOUNT NUMBER\n");
    printf("Enter Account Number: ");
    scanf("%d", &acc_no);
    while (fread(&rec, sizeof(rec), 1, f)) {
        if (rec.account == acc_no) {
            printf("Account Number: %d\n", rec.account);
            printf("Name: %s\n", rec.name);
            printf("Phone Number: %s\n", rec.phone);
            printf("Address: %s\n", rec.address);
            printf("E-mail: %s\n", rec.email);
            printf("Citizenship No.: %s\n", rec.citiz);
            printf("Balance: $%.2lf\n", rec.blnc);
            fclose(f);
            return;
        }
    }
    fclose(f);
    printf("Account Not Found.\n");
}

void search_name() {
    char name[MAX_NAME];
    FILE *f = fopen("record.bin", "rb");
    if (!f) {
        perror("Error opening file");
        return;
    }
    printf("\n\t\tSEARCH BY NAME\n");
    printf("Enter Name: ");
    scanf(" %[^\n]", name);
    while (fread(&rec, sizeof(rec), 1, f)) {
        if (strcmp(rec.name, name) == 0) {
            printf("Account Number: %d\n", rec.account);
            printf("Name: %s\n", rec.name);
            printf("Phone Number: %s\n", rec.phone);
            printf("Address: %s\n", rec.address);
            printf("E-mail: %s\n", rec.email);
            printf("Citizenship No.: %s\n", rec.citiz);
            printf("Balance: $%.2lf\n", rec.blnc);
            fclose(f);
            return;
        }
    }
    fclose(f);
    printf("Name Not Found.\n");
}

void menuexit() {
    printf("\nYou Have Logged Out Successfully.\n");
    exit(0);
}

void about() {
    printf("\n\t\tABOUT US\n");
    printf("TBC Banking System Version 1.0\n");
    printf("Developed by TBC Team\n");
    printf("All Rights Reserved.\n");
}

void transaction() {
    int choice;
    printf("\n\t\tTRANSACTION\n");
    printf("1. Deposit\n");
    printf("2. Withdraw\n");
    printf("3. Check Balance\n");
    printf("4. Transfer Money\n");  // New option
    printf("5. Go Back\n");
    printf("Enter Your Choice: ");
    scanf("%d", &choice);
    switch (choice) {
        case 1: deposit(); break;
        case 2: withdrawl(); break;
        case 3: chkblnc(); break;
        case 4: transfer(); break;  // Call the transfer function
        case 5: return;
        default: printf("Invalid choice. Try again.\n"); transaction();
    }
}

void deposit() {
    int acc_no;
    double amount;
    FILE *f = fopen("record.bin", "rb+");
    if (!f) {
        perror("Error opening file");
        return;
    }
    printf("\n\t\tDEPOSIT\n");
    printf("Enter Account Number: ");
    scanf("%d", &acc_no);
    printf("Enter Amount to Deposit: $");
    scanf("%lf", &amount);
    while (fread(&rec, sizeof(rec), 1, f)) {
        if (rec.account == acc_no) {
            rec.blnc += amount;
            fseek(f, -sizeof(rec), SEEK_CUR);
            fwrite(&rec, sizeof(rec), 1, f);
            printf("Deposit Successful.\n");
            fclose(f);
            return;
        }
    }
    fclose(f);
    printf("Account Not Found.\n");
}

void withdrawl() {
    int acc_no;
    double amount;
    FILE *f = fopen("record.bin", "rb+");
    if (!f) {
        perror("Error opening file");
        return;
    }
    printf("\n\t\tWITHDRAWAL\n");
    printf("Enter Account Number: ");
    scanf("%d", &acc_no);
    printf("Enter Amount to Withdraw: $");
    scanf("%lf", &amount);
    while (fread(&rec, sizeof(rec), 1, f)) {
        if (rec.account == acc_no) {
            if (rec.blnc >= amount) {
                rec.blnc -= amount;
                fseek(f, -sizeof(rec), SEEK_CUR);
                fwrite(&rec, sizeof(rec), 1, f);
                printf("Withdrawal Successful.\n");
            } else {
                printf("Insufficient Balance.\n");
            }
            fclose(f);
            return;
        }
    }
    fclose(f);
    printf("Account Not Found.\n");
}

void chkblnc() {
    int acc_no;
    FILE *f = fopen("record.bin", "rb");
    if (!f) {
        perror("Error opening file");
        return;
    }
    printf("\n\t\tCHECK BALANCE\n");
    printf("Enter Account Number: ");
    scanf("%d", &acc_no);
    while (fread(&rec, sizeof(rec), 1, f)) {
        if (rec.account == acc_no) {
            printf("Account Number: %d\n", rec.account);
            printf("Balance: $%.2lf\n", rec.blnc);
            fclose(f);
            return;
        }
    }
    fclose(f);
    printf("Account Not Found.\n");
}

void transfer() {
    int from_acc, to_acc;
    double amount;
    int found_from = 0, found_to = 0;
    Record from_rec, to_rec;
    FILE *f = fopen("record.bin", "rb+");

    if (!f) {
        perror("Error opening file");
        return;
    }

    printf("\n\t\tTRANSFER MONEY\n");
    printf("Enter Your Account Number: ");
    scanf("%d", &from_acc);
    printf("Enter Recipient's Account Number: ");
    scanf("%d", &to_acc);
    printf("Enter Amount to Transfer: $");
    scanf("%lf", &amount);

    while (fread(&rec, sizeof(rec), 1, f)) {
        if (rec.account == from_acc) {
            from_rec = rec;
            found_from = 1;
        }
        if (rec.account == to_acc) {
            to_rec = rec;
            found_to = 1;
        }
    }

    if (found_from && found_to) {
        if (from_rec.blnc >= amount) {
            from_rec.blnc -= amount;
            to_rec.blnc += amount;

            fseek(f, 0, SEEK_SET);

            while (fread(&rec, sizeof(rec), 1, f)) {
                if (rec.account == from_acc) {
                    fseek(f, -sizeof(rec), SEEK_CUR);
                    fwrite(&from_rec, sizeof(from_rec), 1, f);
                }
                if (rec.account == to_acc) {
                    fseek(f, -sizeof(rec), SEEK_CUR);
                    fwrite(&to_rec, sizeof(to_rec), 1, f);
                }
            }
            printf("Transfer Successful.\n");
        } else {
            printf("Insufficient Balance in your account.\n");
        }
    } else {
        printf("Account(s) Not Found.\n");
    }

    fclose(f);
}
