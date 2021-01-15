/*
	Problem Statement :  	Application is
*/

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include<string.h>
#include<stdlib.h>

struct File
{
	char Fname[256];
	int Fsize;
};

int main(int argc,char *argv[])
{
	int srcfd = 0;
	int destfd = 0;
	int iRet = 0;
	
	struct File fobj;
	int iRead = 0;
	char *data = NULL;
	
	if(argc!=2)
	{
		printf("Error : Inavlid number of arguments\nUse <make help> for help");
		return -1; 
	}
	
	srcfd = open(argv[1],O_RDONLY);
	
	if(srcfd==-1)
	{
		printf("Error : Unable to open %s in read mode\n",argv[1]);
		return -1;
	}
	else
	{
		while((iRet = read(srcfd,&fobj,sizeof(fobj))) != 0)
		{
			destfd = creat(fobj.Fname,0777);
			
			if(destfd==-1)
			{
				printf("Error : Unable to create %s\n",fobj.Fname);
				return -1;
			}
			
			data = (char *)malloc(fobj.Fsize);
						
			iRead = read(srcfd,data,fobj.Fsize);
			
			write(destfd,data,iRead);
		}
	}	
}
