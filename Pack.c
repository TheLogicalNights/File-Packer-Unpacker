/*
	Problem Statement : 	Application which is used to combine all regular files from the directory into one regular file.
*/

#include<stdio.h>
#include<dirent.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<string.h>

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
	
	struct dirent *dirptr = NULL;
	DIR *pDir = NULL;
	struct stat fileptr;
	struct File fobj;
	
	char path[500] = {'\0'};
	char data[1024] = {'\0'};
	char namesize[512] = {'\0'};
	
	if(argc!=3)
	{
		printf("Error : Invalid number of arguments\nUse <make help> for help\n");
		return -1;
	}
	
	pDir = opendir(argv[1]);
	if(pDir==NULL)
	{
		printf("Error : Unable to open directory %s\n",argv[1]);
		return -1;
	}
	else
	{
		while((dirptr = readdir(pDir))!=NULL)
		{
			sprintf(path,"%s/%s",argv[1],dirptr->d_name);
			srcfd = open(path,O_RDONLY);
			if(srcfd==-1)
			{
				printf("Error : Unable to open %s in read mode\n",path);
				closedir(pDir);
				break;
			}
			else
			{
				fstat(srcfd,&fileptr);
				if(S_ISREG(fileptr.st_mode))
				{
					strcpy(fobj.Fname,dirptr->d_name);
					fobj.Fsize = fileptr.st_size;
				
					destfd = open(argv[2],O_WRONLY|O_APPEND|O_CREAT,0777);
					
					if(destfd==-1)
					{
						printf("Error : Unable to open %s in write mode\n",argv[2]);
						break;
					}
					else
					{
						write(destfd,&fobj,sizeof(fobj));
						
						while((iRet = read(srcfd,data,sizeof(data))) != 0)
						{
							data[iRet] = '\0';
							write(destfd,data,iRet);
						}
					}
				}
			}
		}
	}
	close(srcfd);
	close(destfd);
	closedir(pDir);
	return 0;
}
