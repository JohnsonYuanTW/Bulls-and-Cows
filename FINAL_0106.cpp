/* 
猜數字程式 C練習 105學年度上學期初階程式設計期末作業 
Author: 104403520 袁子晉  105403016 陳皇翰
2016 All Rights Reserved. 
*/ 
//使用字串 string 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void swap(char *,char *); //定義無回傳值函式swap使變數交換 因為皆為字串 故使用指標 
void leader(char*, int); //定義無回傳值函式輸入排行資料 因為名字為字串 故使用指標 
void checkleader(); //查詢排行榜 

int main() 
{
	int i, n, randforstring, choose, k, a=0, b=0, count=1; 
	//i,n為for專用變數, randforstring為亂數交換用的隨機亂數, choose紀錄選項, a,b 分別紀錄結果幾A幾B, count為猜的次數 預設為1 
	char inputname[10],  ans[10], guess[4];
	//inputname為最後輸入排行榜用的名字 ans為正確答案 guess為 使用者輸入的四位數字 
	do{
	printf("請選擇模式\n按1開啟排行榜，按2開始遊戲，其他鍵退出。");
	scanf("%d", &choose); //輸入choose進入switch決定選單 
	switch (choose)
	{
		case 1:
			checkleader(); //查詢排行 
			break;
		case 2:
			srand(time(NULL)); //為隨機種下種子 使用現在系統時間 
			for(i = 0; i < 10; ++i)
				ans[i] = i; //將0~9放入陣列ans[0]~ans[9]中 
			for(i = 0; i < 10; ++i)
			{
				do 
				{
					randforstring = rand()%10;  //產生亂數 準備將ans[0]到ans[10-1]與 亂數產生的數字 也就是randforstring 交換
				}while(randforstring==0); //而第0項不會主動交換 只會被動交換 所以ans[0]這項的值為0時只會把 值換出去 不會把值換進來 如此一來第一項不為0  
				swap(&ans[i], &ans[randforstring]); //call 函示 swap 交換 
			} 
			do //do-while a!=4 在4A之前持續重複 
			{
				a=0, b=0; //歸零AB
				printf("\n第 %d 次猜，請輸入%d位數字: \n", count++, 4);
				scanf("%d", &k); //輸入四位數字 
				if(k==-1) //輸入-1印出答案 
				{
					printf("答案:");
					for(i = 0; i < 4; ++i)
					{
						printf("%d", ans[i]); //連續存取 ans[0]~ans[3] 
					}
					count--; //由於在第45行就做count++ 作弊不計回合 故扣回來 
					printf("\n"); //印出換行 
					continue; //跳出do-while迴圈，重計AB，count繼續累計 
				}else if(!(k/1000>0 && k/1000<10)) //判斷k是否符合範圍 
				{
					count--; //由於在第45行就做count++ 輸入錯誤不計回合 故扣回來 
					printf("輸入資訊錯誤，請重新輸入(四位數字不須空格)\n");
					continue; //跳出do-while迴圈，重計AB，count繼續累計 
				}
				for(i=3; k; i--, k/=10)
				{
					guess[i] = k % 10 ; //慢慢把輸入值取餘數後除0 而從末項往前 會讓數字陣列從第零項開始 
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
				} //for 迴圈計算A與B 
				printf("%dA %dB\n", a, b); //印出AB 
			}while(a!=4);
			count--; //成功當回合不需要增加 扣回來 
			printf("\n恭喜答對!\n請輸入您的姓名：");
			fflush(stdin);
			gets(inputname);
			leader(inputname, count); //使用字串 inputname 以及 count傳入函數 leader 
			break;
		default:
			printf("退出");
			break;
	}
	}while(choose == 1 || choose == 2); //當選項不為隨意時 讓程式重複執行 
	
}

void swap(char *x,char *y) 
{ 
	char tmp; //首先宣告暫存字元變數tmp 
	tmp=*x; 
	*x=*y; 
	*y=tmp; //利用指標交換x y 
}

void leader(char* inputname, int count)
{
	struct leaderboard
	{
		char name[10];
		int guesstimes;
	}leaderarray[6]; //定義六項的結構存入名稱以及猜的次數 
	int i, j, sp=-1;//i,j為for用變數 sp紀錄目前項數 (一項的話sp為1 以此類推) 
	FILE *filer; //創建可讀檔案 filer 
	filer = fopen("leaderboard.txt", "r"); //僅以可讀模式開啟leaderboard.txt 
	if ( NULL == filer ) //若不存在 則.. 
	{
		FILE *filew; //由於要創建檔案 使用filew變數名稱 
		printf( "\n無已存在排行榜，將自動新建檔案。\n\n" );  
		filew = fopen("leaderboard.txt", "w"); //不存在直接創建且可寫入 
		printf("第1名:%s ", inputname);
		printf("猜題次數:%d\n\n", count);
		fprintf(filew, "%s ", inputname);
		fprintf(filew, "%d ", count); //一定是第一名因為沒有資料 然後把猜的次數寫入 
		fclose(filew); //關檔 
    }
    else //若存在則... 
    {
		for (i=0; i<6; i++) //開始輸入檔案內的資料存入結構中 
		{
			fscanf(filer, "%s", leaderarray[i].name);
			fscanf(filer, "%d", &leaderarray[i].guesstimes);
			if(feof(filer)) //當檔案結束 紀錄當下項數(i)為sp 
			{
				sp = i;
				break;
			}
		}
		fclose(filer); //讀取進結構了，就先關檔
		FILE *filew; //開檔filew 
		filew = fopen("leaderboard.txt", "w"); //可寫入形式 (資料已經進到程式記憶體) 
		if(count>leaderarray[sp-1].guesstimes) //判斷如果本次猜的項數比最末項還要多次 就直接成為最後一項 
		{
			strcpy(leaderarray[sp].name, inputname);
			leaderarray[sp].guesstimes = count; //sp為項數 直接指定進最後一項 
		}else //如果小於或是等於 
		{
			for(i=0; i<sp+1; i++) //跑到sp+1是因為目前檔案內有sp項 加上新增的一項共有sp+1項 
			{
				if(count<=leaderarray[i].guesstimes) //如果比第i項還要小的話(或等於) 
				{
					for (j=4; j>i-1; j--)
					{
						strcpy(leaderarray[j+1].name, leaderarray[j].name); //就會把最後一項往後移一項 然後把倒數第二項往後推移 
						leaderarray[j+1].guesstimes = leaderarray[j].guesstimes; //達到把包含該項之後的每一項都往後推移一項 
					}
					strcpy(leaderarray[i].name, inputname); //然後把本次數據輸入該項 
					leaderarray[i].guesstimes = count;
					break;
				}
			}
		}
		if(sp>5)
			sp=5; //若超過五項 以五項計 
		printf("\n顯示前五名資料:\n");
		for (i=0; i<sp; i++) //所以在這裡就不會印出陣列[4]也就是第五項 
		{
			printf("第%d名:%s ", i+1, leaderarray[i].name);
			printf("猜題次數:%d\n", leaderarray[i].guesstimes);
			fprintf(filew, "%s ", leaderarray[i].name);
			fprintf(filew, "%d ", leaderarray[i].guesstimes);
		}
		//printf("sp = %d", sp); //印出sp供檢查使用 
		printf("\n");
		fclose(filew); //關檔 
		if(sp==-1)
			printf("原始排行榜資料有誤，程式停止執行。 請刪除檔案。"); //錯誤偵測 (原本是-1) 
	}
	return; //結束函式 
}

void checkleader()
{
	struct leaderboard
	{
		char name[10];
		int guesstimes;
	}leaderarray[6]; //定義六項的結構存入名稱以及猜的次數
	int i, j, sp=-1; //i,j為for用變數 sp紀錄目前項數 (一項的話sp為1 以此類推)
	FILE *filer; //創建可讀檔案 filer 
	filer = fopen("leaderboard.txt", "r"); //僅以可讀模式開啟leaderboard.txt 
	if ( NULL == filer ) //若不存在 則..
	{
		printf( "\n無已存在排行榜。\n\n" );
		return;
	}
	printf("\n顯示前五名資料:\n");
	for (i=0; i<6; i++) //依照順序讀入檔案至結構 
	{
		fscanf(filer, "%s", leaderarray[i].name);
		fscanf(filer, "%d", &leaderarray[i].guesstimes);
		if(feof(filer)) //直到檔案結束 
		{
			sp=i;
			break;
		}
	}
	fclose(filer); //關檔 
	for (i=0; i<sp; i++) //印出結構 sp為項數 
	{
		printf("第%d名:%s ", i+1, leaderarray[i].name);
		printf("猜題次數:%d\n", leaderarray[i].guesstimes);
	}
	printf("\n");
	return;
}
