#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void menudriven()
{
        printf("1 ==> ADD RECORD\n");
        printf("2 ==> LIST RECORD\n");
        printf("3 ==> DELETE RECORD\n");
        printf("4 ==> LEAVE\n");
        printf("5 ==> SHOW LEAVE\n");
        printf("6 ==> EXIT\n");
}
int main()
{
        FILE *fp,*fp1,*ft;
        char another = 'y';
        int choice,ch,a;
        struct emp
        {
                char name[40];
                int age;
                int day;
                float bs;
                char startdate[40];
                char enddate[40];

        };
        struct emp e;
        char empname[40];
        long int recsize,file;
        fp = fopen("EMP","rb+");
        if(fp == NULL)
        {
                fp = fopen("EMP","wb+");
                if(fp==NULL)
                {
                        puts("CANNOT OPEN FILE");
                        exit(1);
                }
        }
        fp1=fopen("EMPLEAVE","rb+");
        if(fp1==NULL)
        {
            fp1=fopen("EMPLEAVE","wb+");
            if(fp1==NULL)
            {
                printf("CANNOT OPEN FILE");
                        exit(1);
            }
        }
        recsize = sizeof(e);                //  file = sizeof(fp);
        printf("recsize = %ld\n",recsize);   //  printf("file = %d\n",file);
        while(1)
        {
                menudriven();
                printf("ENTER  YOUR CHOICE\n");
                scanf("%d",&choice);
                switch(choice)
                 {
                      case 1:
                        fseek(fp,0,SEEK_END) ;
                        while(another == 'y')
                        {
                                printf("\n enter name,age and Basic Salary:\n");
                                scanf("%s %d %f",e.name,&e.age,&e.bs);
                                fwrite(&e,recsize,1,fp);
                                printf("\n ADD ANOTHER RECORD (Y/N)");
                                while((ch = fgetc(stdin))!= EOF && ch != '\n');
                                scanf("%c",&another);
                        }
                        break;
                case 2:
                        rewind(fp);
                        while(fread(&e,recsize,1,fp)==1)
                        printf("\n Name= %s\n Age=%d\n Basis salary=%.2f \n",e.name,e.age,e.bs);
                        break;
               case 3:
                        while(another == 'y')
                        {
                            printf("\nEnter the employee name to delete:");
                            scanf("%s",empname);
                                fp1 = fopen("TEMP1","wb");
                                rewind(fp);
                                while(fread(&e,recsize,1,fp) == 1)
                                {
                                   if(strcmp(e.name,empname)!=0)
                                   {

                                      fwrite(&e,recsize,1,fp1);
                                   }
                                }
                                fclose(fp);
                                fclose(fp1);
                                remove("EMP");
                                rename("TEMP1","EMP");
                                fp = fopen("EMP","rb+");
                                printf("Add another record(Y/N)");
                                while((ch = fgetc(stdin))!= EOF && ch != '\n');
                                scanf("%c",&another);
                        }
                        break;
               case 4:
                        fseek(fp1,0,SEEK_END);
                        another='y';
                        while(another == 'y')
                        {
                                printf("\n enter name,Leave start date,Leave end date ,Total Days:\n");
                                scanf("%s",empname);
                                scanf("%s",e.startdate);
                                scanf("%s",e.enddate);
                                scanf("%d",&e.day);
                                fwrite(&e,recsize,1,fp1);
                                printf("\n ADD ANOTHER RECORD (Y/N)");
                                while((ch = fgetc(stdin))!= EOF && ch != '\n');
                                scanf("%c",&another);
                        }
                        break;
                case 5:
                      rewind(fp1);
                      while(fread(&e,recsize,1,fp1)==1)
                      {
                          printf("\n Name:%s \n Leave start date: %s\n Leave end date: %s \n Days: %d\n",e.name,e.startdate,e.enddate,e.day);
                      }
                      break;
                case 6:
                        fclose(fp);
                        exit(0);
                 }
        }
}
