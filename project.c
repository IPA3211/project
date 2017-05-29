/*********************
* date:
* group: handsome
* student ID: 20170259,20170319,20170293,
*
*
********************/

/********************
  message or todo

  1. read map: clear(on main)
  2. error:
  3. input name: clear
  4. func clear:
  5. ranking:
  6. save ranking:
  7. h,j,k,l move:
  8. undo:
  9. new:
  10. exit:
  11. replay:
  12. file load:
  13. save:
  14. help:
  15. top:
  16. each map top:
*********************/

/* FOR WINDOWS */
//#include <termio.h>

/* FOR MAC OS X */
#include <termios.h>

#include <stdio.h>
#include <stdlib.h>

//common var

int map[5][30][30];
int p_map[30][30];
int mapsize[5];

int stage = 0;

char name[10];

//common func
int getch(void){
	int ch;

	struct termios buf;
	struct termios save;

	tcgetattr(0, &save);
	buf = save;

	buf.c_lflag&=~(ICANON|ECHO);
	buf.c_cc[VMIN] = 1;
	buf.c_cc[VTIME] = 0;

	tcsetattr(0, TCSAFLUSH, &buf);

	ch = getchar();
	tcsetattr(0, TCSAFLUSH, &save);

	return ch;
}

//Seung-mo
int readmap(void){

	FILE  *mapf;
	char a;
	int b = -1, i = 0, j = 0;

	mapf = fopen("map.txt", "r");

	for(int x = 0; x <5 ; x++)
		for(int y = 0; y< 30; y++)
			for(int z = 0; z < 30; z++)
				map[x][y][z] = 0;

	while (fscanf(mapf, "%c", &a) != EOF)
	{
		if(a == ' '){
			map[b][i][j] = ' ';
			j++;
		}
		else if(a == '#'){
			map[b][i][j] = '#';
			j++;
		}
		else if(a == '$'){
			map[b][i][j] = '$';
			j++;
		}
		else if(a =='O'){
			map[b][i][j] = 'O';
			j++;
		}
		else if(a =='@'){
			map[b][i][j] = '@';
			j++;
		}
		else if(a =='\n'){
			i++;
			j = 0;
		}
		else if (a == 97){
			mapsize[b] = i;
			b++;
			i =-1;
			j =0;
		}
		else{}
	}

	fclose(mapf);
	return 0;
}

int playmap(int a)
{
	for(int i =0; i < 30; i++)
		for(int j = 0; j < 30; j++)
			p_map[i][j] = map[a][i][j];

	return 0;
}

int showgame()
{
	system("clear");
	for(int i =0; i < mapsize[stage]-1; i++){
		for(int j = 0; j < 30; j++)
			printf("%c", p_map[i][j]);
		printf("\n");
	}
	return 0;
}
//Jae-hyun

//Cheol-soon
int inputname(void)
{
	int nm;

	printf("사용자 명을 입력하시오(최대10자): ");
	for(nm=0;nm<10;nm++)
	   	scanf("%c", &name[nm]); //입력받은 값을 name배열값에 지정.

	return 0;
}

/* display help(d) */
int displayhelp(void){
	char quit; //quit
	//만약 d키가 눌렸을 때 아래의 내용들이 보여짐.//
	printf("-------------------조작법------------------\n");
	printf("-h(왼쪽), j(아래), k(위), l(오른쪽) : 창고지기 조정\n");
	printf("-u(undo) : 이전에 있던 위치로 돌아가기 (최대 5번 할 수 있음.)\n");
	printf("-r(replay) : 현재 맵을 처음부터 다시 시작(게임시간은 계속 유지.)\n");
	printf("-n(new) : 첫 번째 맵부터 다시 시작(현재까지의 시간 기록 삭제.)\n");
	printf("-e(exit) : 게임 종료.\n");
	printf("-s(save) : 현재상태 파일에 저장\n");
	printf("-f(file load) : 저장한 파일 불러와서 이어서 게임시작.\n");
	printf("-d(display help) : 명령어 보여줌.\n");
	printf("-t(top) : 게임 순위 보기.(t만 입력하면 전체 순위, t다음 숫자가 오면 해당 맵의 순위)\n");
	printf("----------------나가기 'q'-----------------\n");

	quit == getchar();
	if (quit == 113) //'q'의 아스키 코드값은 113이다. 113이 입력되면 나가기.
		return 0;
}

/* new(n) */
int newgame(void)



//Jae-woo

//main

int main(void)
{
	readmap();
	playmap(stage);
	showgame();
}
