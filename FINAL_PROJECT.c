#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct studentnode
{
    int userid , pswd , marks , attendence , eligibility , flag;
    long long int roll_no;
    char name[30] , fees[1];
    struct studentnode *next;
}student;

student stu , *head=NULL , *newnode , *temp, *temp1;
char actual_answer[]="cddccdbbba", your_answer[11];
int scores=0;
FILE *fp;

void copy(FILE*);
void marks_array(void);
int search(int);
int search_marks(int);
int password(int);
void overwrite(void);
void registeration(void);
void details(void);
void display(void);
void edit(void);
void eligibility(void);
void exam(void);
void result(void);
void leaderboard(int*,int);

int main()
{
    fp=fopen("STUDENT.txt","r");
    if(fp!=NULL)
        copy(fp);
    fclose(fp);
    int ch;
    do
    {
        printf("\n=============================================================\n");
        printf("\nENTER NUMBER WITH RESPECT TO CHOICE ACCORDINGLY\n0 EXIT\n1 REGISTRATION\n2 ENTER DETAILS\n3 SEE DETAILS\n4 EDIT DETAILS\n5 CHECK ELIGIBILTY\n6 ATTEND EXAM\n7 RESULT\n8 LEADERBOARD\n");
        scanf("%d",&ch);
        switch(ch)
        {
            case 0:
                printf("Succesfully exited\n");
                break;
            case 1:
                registeration();
                break;
            case 2:
                details();
                break;
            case 3:
                display();
                break;
            case 4:
                edit();
                break;
            case 5:
                eligibility();
                break;
            case 6:
                exam();
                break;
            case 7:
                result();
                break;
            case 8:
                marks_array();
                break;
            default:
                printf("Wrong Choice\n");
        }
    } while (ch!=0);
}

void copy(FILE *fp1)
{
    rewind(fp1);
    while(fread(&stu,sizeof(stu),1,fp1))
    {
        newnode=(student*)malloc(sizeof(student));
        newnode->next=NULL;
        newnode->userid=stu.userid;
        newnode->pswd=stu.pswd;
        newnode->attendence=stu.attendence;
        newnode->roll_no=stu.roll_no;
        newnode->marks=stu.marks;
        newnode->eligibility=stu.eligibility;
        newnode->flag=stu.flag;
        strcpy(newnode->fees,stu.fees);
        strcpy(newnode->name,stu.name);
        if(head==NULL)
            head=temp=newnode;
        else
        {
            temp->next=newnode;
            temp=newnode;
        }
    }
}

int search(int id1)
{
    temp1=head;
    while(temp1!=NULL)
    {
        if(temp1->userid==id1)
            return 1;
        temp1=temp1->next;
    }
    return 0;
}

int password(int pass)
{
    if(temp1->pswd==pass)
        return 1;
    else
        return 0;
}

void overwrite() 
{
    fp=fopen("STUDENT.txt","w");
    temp1=head;
    while(temp1!=NULL)
    {
        fwrite(temp1,sizeof(student),1,fp);
        temp1=temp1->next;
    }
    fclose(fp);
}

int search_marks(int marks2)
{
    temp1=head;
    while(temp!=NULL)
    {
        if(temp1->marks==marks2)
            return 1;
        temp1=temp1->next;
    }
    return 0;
}

void marks_array()
{
    int arr_marks[100],i=0;
    temp1=head;
    while(temp1!=NULL)
    {
        if(temp1->marks!=-1)
        {
            arr_marks[i]=temp1->marks;
            i++;
        }
        temp1=temp1->next;
    }
    leaderboard(arr_marks,i);
}

void registeration()
{
    printf("\n=============================================================\n");
    printf("HERE REGISTER YOURSELF\n");
    fp=fopen("STUDENT.txt","a");
    int ID;
    newnode=(student*)malloc(sizeof(student));
    printf("Enter your college_id as user_id - ");
    scanf("%d",&ID);
    if(search(ID))
        printf("You are already registered\n");
    else
    {
        newnode=(student*)malloc(sizeof(student));
        newnode->next=NULL;
        printf("Enter your DOB as password in the format DDMMYYYY - ");
        scanf("%d",&newnode->pswd);
        newnode->userid=ID;
        newnode->flag=0;
        fwrite(newnode,sizeof(student),1,fp); 
        if(head==NULL)
            head=temp=newnode;
        else
        {
            temp->next=newnode;
            temp=newnode;
        }
        printf("You are succesfuly Registered\n");
    }
    fclose(fp);
}

void details()
{
    printf("\n=============================================================\n");
    printf("HERE REGISTERED CANDIDATES FILL YOUR DETAILS\n");
    int ID,pwd;
    printf("Enter your userID - ");
    scanf("%d",&ID);
    if(search(ID))
    {
        while(1)
        {
            printf("Enter your password - ");scanf("%d",&pwd);
            if(password(pwd))
            {
                if(temp1->flag==0)
                {
                    printf("Enter your details:-\n");
                    printf("Enter your Name - "); //scanf("%[^\n]s",temp1->name);
                    scanf("%s",temp1->name); //gets(temp1->name);
                    printf("Enter your Roll_No. - "); scanf("%lld",&temp1->roll_no);
                    temp1->marks=-1;
                    temp1->flag=1;
                    printf("Enter your Fees status(enter p/P if paid and n/N if not paid) - "); 
                    scanf("%s",temp1->fees);
                    for(int i=0;(temp1->fees)[i]!='\0';i++)
                    {
                        printf("Enter your Attendence percentage - "); 
                        scanf("%d",&temp1->attendence);
                        if((temp1->fees)[i]=='p' || (temp1->fees)[i]=='P')
                        { 
                            if(temp1->attendence>=75)
                                temp1->eligibility=1;
                            else
                                temp1->eligibility=0;
                        }
                        else
                            temp1->eligibility=0;
                    }
                }
                else
                    printf("You have already given your details\n");
                break;
            }
            else
                printf("You entered wrong password\n");
        }
    }
    else
    {
        printf("You are not registered, First register yourself\n");
        registeration();
    }
    overwrite();
}

void display()
{
    printf("\n=============================================================\n");
    int ID,pwd;
    printf("HERE SEE YOUR DETAILS\n");
    printf("Enter your userID - ");scanf("%d",&ID);
    if(search(ID))
    {
        while(1)
        {
            printf("Enter your password - ");scanf("%d",&pwd);
            if(password(pwd))
            {
                printf("Your details are:-\n");
                printf("CollegeID - %d\n",temp1->userid);
                printf("Name - %s\n",temp1->name);
                printf("Roll_No. - %lld\n",temp1->roll_no);
                printf("Fees status - %s\n",temp1->fees);
                printf("Attendence percentage - %d\n",temp1->attendence);
                break;
            }
            else
                printf("You entered wrong password\n");
        }
    }
    else
    {
        printf("You are not registered, First register yourself\n");
        registeration();
    }
}

void edit()
{
    printf("\n=============================================================\n");
    int ch,ID,pwd;
    printf("HERE EDIT YOUR DETAILS\n");
    printf("Enter your userID - ");scanf("%d",&ID);
    if(search(ID))
    {
        while(1)
        {
            printf("Enter your password - ");scanf("%d",&pwd);
            if(password(pwd))
            {
                do
                {
                    printf("Enter the detail you want to edit\n");
                    printf("You can only edit your name and roll no.\n");
                    printf("1-Nothing\t2-Roll_No.\t3-Name\n");scanf("%d",&ch);
                    switch(ch)
                    {
                        case 1:
                            printf("You have not edited anything\n");
                            break;
                        case 2:
                            printf("Enter your new Roll_No. - ");scanf("%d",&temp1->roll_no);
                            printf("Your Roll_No. is succesfully updated\n");
                            break; 
                        case 3:
                            printf("Enter your new Name spelling - ");scanf("%s",temp1->name);
                            printf("Your Name is succesfully updated\n");
                            break;
                        default:
                            printf("You entered wrong choice\n");
                    }
                }while(ch!=1);
                break;
            }
            else
                printf("You entered wrong password\n");
        }
    }
    else
    {
        printf("You are not registered, First register yourself\n");
        registeration();
    }   
    overwrite();
}

void eligibility()
{
    printf("\n=============================================================\n");
    int ID,pwd;
    printf("HERE CHECK YOUR ELIGIBILITY\n");
    printf("Enter your userID - ");scanf("%d",&ID);
    if(search(ID))
    {
        while(1)
        {
            printf("Enter your password - ");scanf("%d",&pwd);
            if(password(pwd))
            {
                if(temp1->eligibility==1)
                    printf("You are eligible\n");
                else
                    printf("You are not eleigible because either you have ot paid fees or your attendece is less than 75 percent\n");
                break;
            }
            else
                printf("You entered wrong password\n");
        }
    }
    else
    {
        printf("You are not registered, First register yourself\n");
        registeration();
    }
}

void exam()
{
    printf("\n=============================================================\n");
    int ID,pwd;
    printf("HERE ATTEND YOUR EXAM\n");
    printf("Enter your userID - ");scanf("%d",&ID);
    if(search(ID))
    {
        while(1)
        {
            printf("Enter your password - ");scanf("%d",&pwd);
            if(password(pwd))
            {
                if(temp1->eligibility==1)
                {
                    if(temp1->marks==-1)
                    {
                        printf("BELOW ARE GIVEN 10 MCQS CARRYING 2 MARKS EACH WITH ONLY ONE CORRECT ANSWER-JUST ENTER a,b,c OR d ACCOERDING TO THE ANSWER\n\n");
                        printf("Q1-In a circulary linked list organisation, insertion of a record involves the modification of\na)-no pointer\tb)-1 pointer\tc)-2 pointers\td)-3 pointers\n\n");
                        scanf("%s",&your_answer[0]);
                        printf("Q2-Linked list are not suitable for\na)-Stack\tb)-Deque\tc)-AVL Tree\td)-Binary search\n\n");
                        scanf("%s",&your_answer[1]);
                        printf("Q3-Dynamic memory allocation use\na)-Calloc\tb)-Malloc\tc)-Free\td)-All of these\n\n");
                        scanf("%s",&your_answer[2]);
                        printf("Q4-Which type of linked list contains a pointer to the next as well as preious node\na)-Singly Linked List\tb)-Circular Linked List\nc)-Doubly Linked List\td)-All of these\n\n");
                        scanf("%s",&your_answer[3]);
                        printf("Q5-Linked list not suitable for which of the following problems\na)-Insertion sort\tb)-radix sort\nc)-Binary search\td)-Polynomial addition\n\n");
                        scanf("%s",&your_answer[4]);
                        printf("Q6-Self-referential pointer is used in defining\na)-an array\tb)-a node of linked list\tc)-a queue\td)-all of these\n\n");
                        scanf("%s",&your_answer[5]);
                        printf("Q7-Inserting a node after a given node in a doubly linked list require\na)-four pointer exchanges\tb)-two poointer exachanges\nc)-one pointer exchange\td)-no pinter exchange\n\n");
                        scanf("%s",&your_answer[6]);
                        printf("Q8-Binary search is not possible for\na)-array\tb)-linked list\tc)-stack\td)-queue\n\n");
                        scanf("%s",&your_answer[7]);
                        printf("Q9-A linked list can be traversed using\na)-recursion\tb)-both (a) and (c) are correct\nc)-stack\td)-both (a) and (c) are wrong\n\n");
                        scanf("%s",&your_answer[8]);
                        printf("Q10-The data structure used to solve recursive problem is\na)-Linked list\tb)-Queue\tc)-Stack\td)none of these\n\n");
                        scanf("%s",&your_answer[9]);
                        printf("\nYour Answers have been recorded\n");
                        for(int i=0;actual_answer[i]!='\0';i++)
                        {
                            if(actual_answer[i]==your_answer[i])
                                scores++;
                        }
                        temp1->marks=scores*2;
                    }
                    else
                        printf("You have already attended the exam\n");
                }
                else
                    printf("You are not Eligible for the Exam\n");
                break;
            }
            else
                printf("You entered wrong password\n");
        }
    }
    else
    {
        printf("You are not registered, First register yourself\n");
        registeration();
    }
    overwrite();
}

void result()
{
    printf("\n=============================================================\n");
    int ID,pwd;
    printf("HERE SEE YOUR RESULT\n");
    printf("Enter your userID - ");scanf("%d",&ID);
    if(search(ID))
    {
        while(1)
        {
            printf("Enter your password - ");scanf("%d",&pwd);
            if(password(pwd))
            {
                printf("Your Marks are %d\n",temp1->marks);
                printf("You secured %d percent marks\n",((temp1->marks)*100)/20);
                if((((temp1->marks)*100)/20)>=40)
                    printf("You passed\n");
                else
                    printf("You failed\n");
                break;
            }
            else
                printf("You entered wrong password\n");
        }
    }
    else
    {
        printf("You are not registered, First register yourself\n");
        registeration();
    }
    overwrite();
}

void leaderboard(int *arr,int n)
{
    printf("\n=============================================================\n");
    int temp,flag;
    for(int i=0;i<n-1;i++)
    {
        flag=0;
        for(int j=0;j<n-i-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                temp=arr[j+1];
                arr[j+1]=arr[j];
                arr[j]=temp;
                flag=1;
            }
        }
        if(flag==0)
            break;
    }
    // printf("%d\n%d",arr[0],n);
    printf("YOUR RANKS ARE:-\n");
    printf("NAME\t\t\tRANK\n");
    for(int i=n-1;i>=0;i--)
    {
        if(search_marks(arr[i]))
        {
            printf("%s\t\t%d\n",temp1->name,n-i);
        }
    }
}