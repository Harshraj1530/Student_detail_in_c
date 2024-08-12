#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
typedef struct Student
{
int roll;
char name[40];
char cs[10];
long int fee;
}STD;

typedef struct Payment
{
int roll;
char idate[12];
long int amt;
}PMT;

void admin();
void showall();
void showone();
void fee_entry();
void fee_history();
void del_record();

int main()
{
int n;
while(1)
{
printf("\n\t\t ARYA Group Of College \n");
printf("\t\t MAIN MENU \n");
printf("\t 1. Admission Entry \n");
printf("\t 2. Fee Payment Entry \n");
printf("\t 3. Student List \n");
printf("\t 4. Record of Student by Roll \n");
printf("\t 5. Payment History \n");
printf("\t 6. Delete Student \n");
printf("\t 7. Exit \n");
printf("\t Choice(1-7) :");
scanf("%d",&n);
switch(n)
{
case 1:
admin();
break;
case 2:
fee_entry();
break;
case 3:
showall();
break;
case 4:
showone();
break;
case 5:
fee_history();
break;
case 6:
del_record();
break;
case 7:
exit(0);
break;
default:
printf("Invalid Choice...");
}
getch();
}
}

/*Function for admission entry */
void admin()
{
FILE *fp;
STD S;
fp = fopen("ARYA.DB","ab");
if(fp==NULL)
{
printf("Unable to craete or open database ");
getch();
return;
}
printf("Input Roll, name, course, fee :");
scanf("%d%s%s%ld",&S.roll,S.name,S.cs,&S.fee);
fwrite(&S,sizeof(S),1,fp);
printf("Recod saved successfully...");
fclose(fp);
}
/*Function to show student list */
void showall()
{
STD S;
FILE *fp;
fp= fopen("ARYA.DB","rb");
if(fp==NULL)
{
printf("Unable to open database file ");
getch();
return;
}
printf("\t\t Student Record\n");
printf("--------------------------------------------\n");
printf("ROLL \t Name \t Course \t Fee \n");
printf("-----------------------------------------------\n");
while(fread(&S,sizeof(S),1,fp)==1)
{
printf("%d\t%s\t  %s\t\t%ld\n",S.roll,S.name,S.cs,S.fee);
}
fclose(fp);
}

/*Function to show student record*/
void showone()
{
STD S;
FILE *fp;
int r,found=0;
fp= fopen("ARYA.DB","rb");
if(fp==NULL)
{
printf("Unable to open database file ");
getch();
return;
}
printf("ENTER ROLL NO :");
scanf("%d",&r);
printf("\t\t Student Record\n");
printf("--------------------------------------------\n");
printf("ROLL \t Name \t Course \t Fee \n");
printf("-----------------------------------------------\n");
while(fread(&S,sizeof(S),1,fp)==1)
{
if(S.roll==r)
{
printf("%d\t%s\t  %s\t\t%ld\n",S.roll,S.name,S.cs,S.fee);
found=1;
break;
}
}
if(found==0)
printf("Invalid roll or roll not found");
fclose(fp);
}

/*Function for fee entry*/
void fee_entry()
{
FILE *fp;
PMT P;
fp = fopen("FEE.DB","ab");
if(fp==NULL)
{
printf("Unable to craete/open fee database");
getch();
return;
}
printf("Input Roll, Date, Amount :");
scanf("%d%s%ld",&P.roll,P.idate,&P.amt);
fwrite(&P,sizeof(P),1,fp);
printf("Record saved successfully...");
fclose(fp);
}

/*Function to display fee history*/
void fee_history()
{
FILE *fp;
PMT P;
int r,found=0;
long int tot=0;
fp = fopen("FEE.DB","rb");
if(fp==NULL)
{
printf("Unable to craete/open fee database");
getch();
return;
}
printf("Enter Roll :");
scanf("%d",&r);
printf("\n Fee Payment History of Roll = %d\n",r);
printf("---------------------------------------\n");
printf("Date \t\t\t Amount \n");
printf("-----------------------------------------\n");
while(fread(&P,sizeof(P),1,fp)==1)
{
if(P.roll==r)
{
printf("%s \t\t %ld \n",P.idate,P.amt);
tot = tot + P.amt;
found=1;
}
}
if(found==0)
printf("Roll not found or invalid roll....");
else
{
printf("----------------------------------------------\n");
printf("\t\t Total Fee Paid = %ld",tot);
}
fclose(fp);
}

/*Function to delete record */
void del_record()
{
FILE *fp1,*fp2;
STD S;
int found=0,r;
fp1 = fopen("ARYA.DB","rb");
fp2 = fopen("temp.db","wb");
if(fp1==NULL || fp2==NULL)
{
printf("Unable to open database file");
getch();
return;
}
printf("Enter Roll :");
scanf("%d",&r);
while(fread(&S,sizeof(S),1,fp1)==1)
{
if(S.roll!=r)
{
fwrite(&S,sizeof(S),1,fp2);
}
if(S.roll==r)
found=1;
}
if(found==1)
printf("Record deleted successfully...");
else
printf("Roll not found...");
_fcloseall();
remove("ARYA.DB");
rename("temp.db","ARYA.DB");
}

