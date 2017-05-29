/*********************
* date:
* group: handsome
* student ID: 20170259,20170319,20170293,
*
*
********************/

/********************. read map: clear(on main)
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

//common var


  message or todo

  1int map[5][30][30];
int p_map[30][30];

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

//Jae-woo

//main

int main(void)
{
	readmap();
	playmap(stage);
}
