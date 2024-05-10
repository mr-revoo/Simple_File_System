#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include "assistFile.c"

#define NAME_LENGTH 50

void listFile()
{
    char filePath[100] , command[200] , valid;
    printf("Do you want to show list of files in the current path %s ? ['Y' / 'N'] : " ,showPath());
    scanf(" %c" ,&valid);
    if(valid == 'Y' || valid == 'y') {
        strcpy(command, "ls -l ");
        system(command);
    } 
    else if (valid == 'N' || valid == 'n') {
        printf("Enter the folder path that you want to list its files, for example: Folder1/Folder2/Folder3: \n");
        scanf("%s", filePath);
        if(access(filePath, F_OK) == 0)
        {
            sprintf(command, "ls -l %s", filePath);
            system(command);
        }
        else
            printf("Can't Found This path\n");
    } 
    else {
        printf("Invalid choice\n");
    }
    printf("__________________________________________________\n");
}


void listDirectories()
{
    char filePath[100] , command[200] , valid;
    printf("Do you want to show list of directories in the current path %s ? ['Y' / 'N'] : ", showPath());
    scanf(" %c", &valid);
    if(valid == 'Y' || valid == 'y') {
        strcpy(command, "ls ");
        system(command);
    } 
    else if (valid == 'N' || valid == 'n') {
        printf("Enter the folder path that you want to list its directories, for example: Folder1/Folder2/Folder3: \n");
        scanf("%s", filePath);
        if(access(filePath, F_OK) == 0)
        {
            sprintf(command, "ls %s", filePath);
            system(command);
        }
        else
            printf("Can't Found This path\n");
    }
    else {
        printf("Invalid choice\n");
    }
    printf("__________________________________________________\n");
}




void createFile() {
    char PathFile_Name[100], command[200] , path[100] , FileName[100];
    char *currentPath = showPath();
    printf("To create file in this path %s write file Name EX: Z.txt\n",currentPath);
    printf("To create file in Another path write path + file Name EX: Folder1/Folder2/Z.txt\n");
    printf("Enter Name of File : ");
    scanf("%s",PathFile_Name);
    separatePathAndFileName(PathFile_Name , path , FileName);
    if(access(path ,F_OK) == 0 || path[0] == '\0')
    {
        if(FileName[0] != '\0')
        {
            strcpy(command, "touch ");
            strcat(command, PathFile_Name);
            system(command);
            printf("create file Successful\n");
        }
        else
            printf("Can't Create File because there is no name entered\n");
    }
    else
        printf("Can't Found this path\n");
    printf("__________________________________________________\n");
}



void createDirectories(){
    char PathFile_Name[100], command[200] , path[100] , FolderName[100];
    char *currentPath = showPath();
    printf("To create Directories in this path %s write Directories Name EX: Zamalek\n",path);
    printf("To create Directories in Another path write path + Directories Name EX: Folder1/Folder2/Zamalek\n");
    printf("Enter Name of Directories : ");
    scanf("%s",PathFile_Name);
    separatePathAndFileName(PathFile_Name , path , FolderName);
    if(access(path ,F_OK) == 0 || path[0] == '\0')
    {
        if(FolderName[0] != '\0')
        {
            strcpy(command, "mkdir -p ");
            strcat(command, PathFile_Name);
            system(command);
            printf("create Directories Successful\n");
        }
        else
            printf("Can't Create Directories because there is no name entered\n");
    }
    else
        printf("Can't Found this path\n");
    printf("__________________________________________________\n");
}



void RemoveFile(){
    char PathFile_Name[100], command[200] , path[100] , FileName[100];
    char *currentPath = showPath();
    printf("if the File in this path ['%s'] write file Name Ex : ex.txt\n",currentPath);
    printf("if the File in Another path write Path + file Name Ex : Folder1/Folder2/ex\n");
    printf("Enter fileName : ");
    strcpy(command , "rm ");
    scanf("%s",PathFile_Name);
    separatePathAndFileName(PathFile_Name , path , FileName);
    if(access(PathFile_Name , F_OK) == 0)
    {
        if(FileName[0] != '\0')
        {
            strcat(command, PathFile_Name);
            system(command);
            printf("Delete file Successful\n");
        }
        else
            printf("Can't Delete File because there is no name entered\n");
    }
    else
        printf("Can't Found this File\n");
    printf("__________________________________________________\n");
}



void RemoveDirectories(){
    char PathFile_Name[100], command[200] , path[100] , FolderName[100];
    char *currentPath = showPath();
    printf("if the Directories in this path ['%s'] write Directories Name Ex : photo\n",currentPath);
    printf("if the Directories in Another path write Path + Directories Name Ex : Folder1/Folder2/photo\n");
    printf("Enter fileName : ");
    scanf("%s",PathFile_Name);
    separatePathAndFileName(PathFile_Name , path , FolderName);
    if(access(PathFile_Name , F_OK) == 0)
    {
        if(FolderName[0] != '\0')
        {
            char checkCommand[200];
            sprintf(checkCommand, "ls -A %s | wc -l", PathFile_Name);
            FILE *checkEmpty = popen(checkCommand, "r");
            int contentCount;
            fscanf(checkEmpty, "%d", &contentCount);
            pclose(checkEmpty);
            if(contentCount > 0)
            {
                char A;
                printf("Note : This Directories is Not empty you are sure ['Y | N'] ?\n");
                scanf(" %c", &A);
                if(A == 'Y' || A == 'y') {
                    strcpy(command , "rm -r ");
                    strcat(command, PathFile_Name);
                    system(command);
                    printf("Delete file Successful\n");
                }
                else if(A == 'N' || A == 'n')
                    printf("Cancel deletion\n");
                else
                    printf("invalid choice\n");
            }
            else
            {
                strcpy(command , "rmdir ");
                strcat(command, PathFile_Name);
                system(command);
                printf("Delete file Successful\n");
            }
        }
        else
            printf("Can't Delete FolderName because there is no name entered\n");
    }
    else
        printf("Can't Found this File\n");
    printf("__________________________________________________\n");
}


void createSymbolicLinkFiles()
{
    char targetPath[100], Newpath[100] , command[200] , valid , NewName[50],separatePath[100] , separateFileName[100];
    char *currentPath = showPath();
    strcpy(command , "ln -s ");
    printf("Enter The targetPath Ex: moaz/...... \n");
    scanf("%s",targetPath);
    if(access(targetPath , F_OK) == 0)
    {
        strcat(command , "~/");
        strcat(command , targetPath);
        strcat(command , " ");
        printf("Do you want To create symbolic Link in current path ['%s'] ? ['Y | N'] : " ,currentPath);
        scanf(" %c" ,&valid);
        if(valid == 'Y' || valid == 'y')
        {
            char valid1;
            printf("do you want to create it as The same Name ['Y | N'] : ");
            scanf(" %c",&valid1);
            if(valid1 == 'Y' || valid1 == 'y')
            {
                system(command);
                printf("Create symbolic Link Files Successful\n");
                printf("%s\n",command);
            }
            else if(valid1 == 'n' || valid1 == 'N')
            {
                printf("Enter Another Name : ");
                scanf("%s", NewName);
                strcat(command , NewName);
                system(command);
                printf("Create symbolic Link Files Successful\n");
                printf("%s\n",command);
            }
            else
                printf("invalid choice\n");
        }
        else if(valid == 'N' || valid == 'n')
        {
            printf("Enter path + FolderName : Ex : Desktop(/NewName [if you want])\n");
            scanf("%s" , Newpath);
            separatePathAndFileName(Newpath , separatePath , separateFileName);
            if(access(separatePath , F_OK) == 0)
            {
                strcat(command , "~/");
                strcat(command , separatePath);
                strcat(command , separateFileName);
                system(command);
                printf("Create symbolic Link Files Successful\n");
                printf("%s\n",command);
            }
            else
            {
                printf("Can't Found this File\n");
                printf("%s\n",command);
            }
        }
        else
            printf("invalid choice\n");
    }
    else
        printf("Can't Found this File\n");
    printf("__________________________________________________\n");
}

void showMenu(){
    printf("____________________________________\n");
    printf("              Menu\n");
    printf("____________________________________\n");
    printf("1.~ To list file\n");
    printf("2.~ To list directories.\n");
    printf("3.~ To create File.\n");
    printf("4.~ To Delete File.\n");
    printf("5.~ To create directories.\n");
    printf("6.~ To Delete directories.\n");
    printf("7.~ To Create Symbolic Link Files\n");
    printf("8.~ show current path\n");
    printf("9.~ Change File Permissions\n");
    printf("10.~ Exit.\n");

}

int isValidMode(mode_t mode) {
    if (mode >= 0 && mode <= 0777)
        return 1;
    else 
        return 0;
}

void changeFilePermissions(){
    char filename[50];
    char command[100];
    char permission[100];
    char confirm;

    printf("Enter the filename: ");
    scanf("%s", filename);

    printf("The permissions of file '%s' are:\n", filename);
    snprintf(command, 50, "stat -c '%%A' \"%s\"", filename);
    system(command);

    printf("\nDo you want to change the permission of the file? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        printf("\nr : read\nw : write\nx : execute\n(e.g., u+rw, g-w, a+x):\n");
        printf("\nEnter the new permissions: ");
        scanf("%s", permission);

        snprintf(command, 50, "chmod %s \"%s\"", permission, filename);
        int status = system(command);

        if (status == 0) {
            printf("Permissions changed successfully for file '%s'.\n", filename);
        } else {
            printf("Failed to change permissions for file '%s'.\n", filename);
            return ;
        }
    } else {
        printf("Permission change canceled.\n");
        return;
    }
}



int main() 
{
    int choice;
    printf("____________________________________\n");
    printf("Welcome to the File Manager system\n");
    do{
        showMenu();
        printf("enter the process you Need: ");
        scanf("%d",&choice);
        switch (choice)
        {
            case 1:
                listFile();
                break;
            case 2:
                listDirectories();
                break;
            case 3:
                createFile();
                break;
            case 4:
                RemoveFile();
                break;
            case 5:
                createDirectories();
                break;
            case 6:
                RemoveDirectories();
                break;
            case 7:
                createSymbolicLinkFiles();
                break;
            case 8:
                printf("The Current Path is : %s\n",showPath());
                break;
            case 9:
                changeFilePermissions();
                break;
            case 10:
                return 0;
                break;
            default:
                printf("invalid choice\n");
        }
    } while(choice != 10);
    return 0;
}
