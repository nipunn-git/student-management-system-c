#include<stdio.h>
#include <stdlib.h>
struct student
{
    char name[50];
    int roll;
    float marks;
};
void addStudent();
void displayStudents();
void searchStudent();
void deleteStudent();
void updateStudent();
int main()
{
    int choice;
    while(1<2)
    {
        printf("1. Add Student\n");
        printf("2. Display all students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n\n");

        printf("Enter choice (1-6) = ");
        scanf("%d",&choice);
        printf("\n-------------------------------------------------------------\n");

        switch(choice)
        {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: exit(0);
            default: printf("Invalid Choice\n");
        }
    }
}

void addStudent()
{
    FILE *fp;
    struct student s;
    fp=fopen("students.dat","ab");

    if(fp==NULL)
    {
        printf("Error in opening the file.\n"); return;
    }

    printf("Enter roll no = ");
    scanf("%d",&s.roll);
    printf("Enter name = ");
    scanf(" %[^\n]",s.name);
    printf("Enter marks = ");
    scanf("%f",&s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    printf("Student record added successfully!\n\n");
    printf("\n-------------------------------------------------------------\n\n");

    fclose(fp);
}

void displayStudents()
{
    FILE *fp;
    struct student s;
    int found=0;

    fp=fopen("students.dat","rb");

    if(fp==NULL)
    {
        printf("No records found.\n"); return;
    }
    printf("\n------Students Record------\n");
    while(fread(&s,sizeof(s),1,fp)==1)
    {
        printf("\nRoll Number : %d", s.roll);
        printf("\nName        : %s\n", s.name);
        printf("Marks       : %.2f\n", s.marks);
        found = 1;
    }
    printf("\n-------------------------------------------------------------\n");

    if(!found)
    {
        printf("File is empty.\n");
        printf("\n-------------------------------------------------------------\n");
    }

    fclose(fp);
}

void searchStudent()
{
    FILE *fp;
    struct student s;
    int rollsearch;
    int found=0;

    fp=fopen("students.dat","rb");

    if(fp==NULL)
    {
        printf("No records found.\n");
        return;
    }

    printf("Enter roll number to search = ");
    scanf("%d",&rollsearch);

    while(fread(&s,sizeof(s),1,fp)==1)
    {
        if(s.roll==rollsearch)
        {
            printf("----Student record FOUND----\n");
            printf("Roll Number : %d\n", s.roll);
            printf("Name        : %s\n", s.name);
            printf("Marks       : %.2f\n", s.marks);
            found=1;
            break;
        }
    }
    printf("\n-------------------------------------------------------------\n");
    if(found!=1)
    {
        printf("Student will roll number %d not found in the record.",rollsearch);
        printf("\n-------------------------------------------------------------\n");
    }
    fclose(fp);
}

void deleteStudent()
{
    FILE *fp, *temp;
    struct student s;
    int delroll;
    int found =0;

    fp=fopen("students.dat", "rb");
    if(fp==NULL)
    {
        printf("No records found.\n"); return;
    }

    temp=fopen("temp.dat","wb");
    if(temp==NULL)
    {
        printf("Error creating temporary file.\n"); return;
        fclose(fp); return;
    }

    printf("Enter roll number to delete = ");
    scanf("%d",&delroll);

    while (fread(&s, sizeof(s), 1, fp) == 1)
    {

        if (s.roll == delroll)
        {
            found = 1;
        }
        else
        {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }
    fclose(fp); fclose(temp);

    remove("students.dat");
    rename("temp.dat","students.dat");

    if (found)
    {
        printf("Student record deleted successfully.\n");
        printf("\n-------------------------------------------------------------\n");
    }
    else
    {
        printf("Student with roll number %d not found.\n", delroll);
        printf("\n-------------------------------------------------------------\n");
    }
}

void updateStudent()
{
    FILE *fp, *temp;
    struct student s;
    int rollToUpdate;
    int found = 0;

    fp = fopen("students.dat", "rb");
    if(fp==NULL)
    {
        printf("No records found.\n");
        return;
    }

    temp = fopen("temp.dat", "wb");
    if(temp==NULL)
    {
        printf("Error creating temporary file.\n");
        fclose(fp);
        return;
    }

    printf("Enter roll number to update: ");
    scanf("%d", &rollToUpdate);

    while (fread(&s, sizeof(s), 1, fp) == 1)
    {

        if (s.roll == rollToUpdate)
        {
            found = 1;
            printf("\nEnter new details:\n");
            printf("Enter new roll number: ");
            scanf("%d", &s.roll);
            getchar();
            printf("Enter new name: ");
            fgets(s.name, sizeof(s.name), stdin);
            printf("Enter new marks: ");
            scanf("%f", &s.marks);
        }
        fwrite(&s,sizeof(s),1,temp);
    }
    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if(found)
    {
        printf("Student record updated successfully.\n");
        printf("\n-------------------------------------------------------------\n");
    }
    else
    {
        printf("Student not found.\n");
        printf("\n-------------------------------------------------------------\n");
    }
}





















