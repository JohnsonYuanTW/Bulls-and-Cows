/* 
�q�Ʀr�{�� C�m�� 105�Ǧ~�פW�Ǵ��춥�{���]�p�����@�~ 
Author: 104403520 �K�l��  105403016 ���ӿ�
2016 All Rights Reserved. 
*/ 
//�ϥΦr�� string 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void swap(char *,char *); //�w�q�L�^�ǭȨ禡swap���ܼƥ洫 �]���Ҭ��r�� �G�ϥΫ��� 
void leader(char*, int); //�w�q�L�^�ǭȨ禡��J�Ʀ��� �]���W�r���r�� �G�ϥΫ��� 
void checkleader(); //�d�߱Ʀ�] 

int main() 
{
	int i, n, randforstring, choose, k, a=0, b=0, count=1; 
	//i,n��for�M���ܼ�, randforstring���üƥ洫�Ϊ��H���ü�, choose�����ﶵ, a,b ���O�������G�XA�XB, count���q������ �w�]��1 
	char inputname[10],  ans[10], guess[4];
	//inputname���̫��J�Ʀ�]�Ϊ��W�r ans�����T���� guess�� �ϥΪ̿�J���|��Ʀr 
	do{
	printf("�п�ܼҦ�\n��1�}�ұƦ�]�A��2�}�l�C���A��L��h�X�C");
	scanf("%d", &choose); //��Jchoose�i�Jswitch�M�w��� 
	switch (choose)
	{
		case 1:
			checkleader(); //�d�߱Ʀ� 
			break;
		case 2:
			srand(time(NULL)); //���H���ؤU�ؤl �ϥβ{�b�t�ήɶ� 
			for(i = 0; i < 10; ++i)
				ans[i] = i; //�N0~9��J�}�Cans[0]~ans[9]�� 
			for(i = 0; i < 10; ++i)
			{
				do 
				{
					randforstring = rand()%10;  //���Ͷü� �ǳƱNans[0]��ans[10-1]�P �üƲ��ͪ��Ʀr �]�N�Orandforstring �洫
				}while(randforstring==0); //�Ӳ�0�����|�D�ʥ洫 �u�|�Q�ʥ洫 �ҥHans[0]�o�����Ȭ�0�ɥu�|�� �ȴ��X�h ���|��ȴ��i�� �p���@�ӲĤ@������0  
				swap(&ans[i], &ans[randforstring]); //call ��� swap �洫 
			} 
			do //do-while a!=4 �b4A���e���򭫽� 
			{
				a=0, b=0; //�k�sAB
				printf("\n�� %d ���q�A�п�J%d��Ʀr: \n", count++, 4);
				scanf("%d", &k); //��J�|��Ʀr 
				if(k==-1) //��J-1�L�X���� 
				{
					printf("����:");
					for(i = 0; i < 4; ++i)
					{
						printf("%d", ans[i]); //�s��s�� ans[0]~ans[3] 
					}
					count--; //�ѩ�b��45��N��count++ �@�����p�^�X �G���^�� 
					printf("\n"); //�L�X���� 
					continue; //���Xdo-while�j��A���pAB�Acount�~��֭p 
				}else if(!(k/1000>0 && k/1000<10)) //�P�_k�O�_�ŦX�d�� 
				{
					count--; //�ѩ�b��45��N��count++ ��J���~���p�^�X �G���^�� 
					printf("��J��T���~�A�Э��s��J(�|��Ʀr�����Ů�)\n");
					continue; //���Xdo-while�j��A���pAB�Acount�~��֭p 
				}
				for(i=3; k; i--, k/=10)
				{
					guess[i] = k % 10 ; //�C�C���J�Ȩ��l�ƫᰣ0 �ӱq�������e �|���Ʀr�}�C�q�Ĺs���}�l 
				}
				for (i=0; i<4; i++)
				{
					for (n=0; n<4; n++)
					{
						if (i==n && ans[i]==guess[n])
						{
							a++;
							continue;
						}
						if (ans[i]==guess[n])
							b++;
					}
				} //for �j��p��A�PB 
				printf("%dA %dB\n", a, b); //�L�XAB 
			}while(a!=4);
			count--; //���\��^�X���ݭn�W�[ ���^�� 
			printf("\n���ߵ���!\n�п�J�z���m�W�G");
			fflush(stdin);
			gets(inputname);
			leader(inputname, count); //�ϥΦr�� inputname �H�� count�ǤJ��� leader 
			break;
		default:
			printf("�h�X");
			break;
	}
	}while(choose == 1 || choose == 2); //��ﶵ�����H�N�� ���{�����ư��� 
	
}

void swap(char *x,char *y) 
{ 
	char tmp; //�����ŧi�Ȧs�r���ܼ�tmp 
	tmp=*x; 
	*x=*y; 
	*y=tmp; //�Q�Ϋ��Х洫x y 
}

void leader(char* inputname, int count)
{
	struct leaderboard
	{
		char name[10];
		int guesstimes;
	}leaderarray[6]; //�w�q���������c�s�J�W�٥H�βq������ 
	int i, j, sp=-1;//i,j��for���ܼ� sp�����ثe���� (�@������sp��1 �H������) 
	FILE *filer; //�ЫإiŪ�ɮ� filer 
	filer = fopen("leaderboard.txt", "r"); //�ȥH�iŪ�Ҧ��}��leaderboard.txt 
	if ( NULL == filer ) //�Y���s�b �h.. 
	{
		FILE *filew; //�ѩ�n�Ы��ɮ� �ϥ�filew�ܼƦW�� 
		printf( "\n�L�w�s�b�Ʀ�]�A�N�۰ʷs���ɮסC\n\n" );  
		filew = fopen("leaderboard.txt", "w"); //���s�b�����ЫإB�i�g�J 
		printf("��1�W:%s ", inputname);
		printf("�q�D����:%d\n\n", count);
		fprintf(filew, "%s ", inputname);
		fprintf(filew, "%d ", count); //�@�w�O�Ĥ@�W�]���S����� �M���q�����Ƽg�J 
		fclose(filew); //���� 
    }
    else //�Y�s�b�h... 
    {
		for (i=0; i<6; i++) //�}�l��J�ɮפ�����Ʀs�J���c�� 
		{
			fscanf(filer, "%s", leaderarray[i].name);
			fscanf(filer, "%d", &leaderarray[i].guesstimes);
			if(feof(filer)) //���ɮ׵��� ������U����(i)��sp 
			{
				sp = i;
				break;
			}
		}
		fclose(filer); //Ū���i���c�F�A�N������
		FILE *filew; //�}��filew 
		filew = fopen("leaderboard.txt", "w"); //�i�g�J�Φ� (��Ƥw�g�i��{���O����) 
		if(count>leaderarray[sp-1].guesstimes) //�P�_�p�G�����q�����Ƥ�̥����٭n�h�� �N���������̫�@�� 
		{
			strcpy(leaderarray[sp].name, inputname);
			leaderarray[sp].guesstimes = count; //sp������ �������w�i�̫�@�� 
		}else //�p�G�p��άO���� 
		{
			for(i=0; i<sp+1; i++) //�]��sp+1�O�]���ثe�ɮפ���sp�� �[�W�s�W���@���@��sp+1�� 
			{
				if(count<=leaderarray[i].guesstimes) //�p�G���i���٭n�p����(�ε���) 
				{
					for (j=4; j>i-1; j--)
					{
						strcpy(leaderarray[j+1].name, leaderarray[j].name); //�N�|��̫�@�����Ჾ�@�� �M���˼ƲĤG��������� 
						leaderarray[j+1].guesstimes = leaderarray[j].guesstimes; //�F���]�t�Ӷ����᪺�C�@������������@�� 
					}
					strcpy(leaderarray[i].name, inputname); //�M��⥻���ƾڿ�J�Ӷ� 
					leaderarray[i].guesstimes = count;
					break;
				}
			}
		}
		if(sp>5)
			sp=5; //�Y�W�L���� �H�����p 
		printf("\n��ܫe���W���:\n");
		for (i=0; i<sp; i++) //�ҥH�b�o�̴N���|�L�X�}�C[4]�]�N�O�Ĥ��� 
		{
			printf("��%d�W:%s ", i+1, leaderarray[i].name);
			printf("�q�D����:%d\n", leaderarray[i].guesstimes);
			fprintf(filew, "%s ", leaderarray[i].name);
			fprintf(filew, "%d ", leaderarray[i].guesstimes);
		}
		//printf("sp = %d", sp); //�L�Xsp���ˬd�ϥ� 
		printf("\n");
		fclose(filew); //���� 
		if(sp==-1)
			printf("��l�Ʀ�]��Ʀ��~�A�{���������C �ЧR���ɮסC"); //���~���� (�쥻�O-1) 
	}
	return; //�����禡 
}

void checkleader()
{
	struct leaderboard
	{
		char name[10];
		int guesstimes;
	}leaderarray[6]; //�w�q���������c�s�J�W�٥H�βq������
	int i, j, sp=-1; //i,j��for���ܼ� sp�����ثe���� (�@������sp��1 �H������)
	FILE *filer; //�ЫإiŪ�ɮ� filer 
	filer = fopen("leaderboard.txt", "r"); //�ȥH�iŪ�Ҧ��}��leaderboard.txt 
	if ( NULL == filer ) //�Y���s�b �h..
	{
		printf( "\n�L�w�s�b�Ʀ�]�C\n\n" );
		return;
	}
	printf("\n��ܫe���W���:\n");
	for (i=0; i<6; i++) //�̷Ӷ���Ū�J�ɮצܵ��c 
	{
		fscanf(filer, "%s", leaderarray[i].name);
		fscanf(filer, "%d", &leaderarray[i].guesstimes);
		if(feof(filer)) //�����ɮ׵��� 
		{
			sp=i;
			break;
		}
	}
	fclose(filer); //���� 
	for (i=0; i<sp; i++) //�L�X���c sp������ 
	{
		printf("��%d�W:%s ", i+1, leaderarray[i].name);
		printf("�q�D����:%d\n", leaderarray[i].guesstimes);
	}
	printf("\n");
	return;
}
