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
#include <termio.h>

/* FOR MAC OS X */
//#include <termios.h>

#include <stdio.h>
#include <stdlib.h>

//common var

int map[5][30][30];
int p_map[30][30];
int mapsize[5];

int stage = 1;

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
int ctrl_key(void)
{
	int a, b;
  for(int i=0;i<30;i++)
  {
    for(int j=0;j<30;j++)
    {
      if (p_map[i][j] == '@'){
        b = i, a = j;
      break;
	  }
    }
   }
  char ch;
  ch = getch();
    if((ch == 'l')&&(p_map[b][a+1]) == ' ')//right
    {
      p_map[b][a] = p_map[b][a+1];
      p_map[b][a+1] = '@';
      a += 1;
    }
    else if((ch == 'l')&&(p_map[b][a+1]) == '#')
    {

    }
    else if((ch == 'l')&&(p_map[b][a+1]) == '$')
    {
      if(p_map[b][a+2] == '#')
      {}
      else if(p_map[b][a+2] == ' ')
      {
        p_map[b][a] = p_map[b][a+2];
        p_map[b][a+1] = '@';
        p_map[b][a+2] = '$';
				a += 1;
      }
    }
		if((ch == 'h')&&(p_map[b][a-1]) == ' ')//left
		{
			p_map[b][a] = p_map[b][a-1];
			p_map[b][a-1] = '@';
			a -= 1;
		}
		else if((ch == 'h')&&(p_map[b][a-1]) == '#')
		{

		}
		else if((ch == 'h')&&(p_map[b][a-1]) == '$')
		{
			if(p_map[b][a-2] == '#')
			{}
			else if(p_map[b][a-2] == ' ')
			{
				p_map[b][a] = p_map[b][a-2];
				p_map[b][a-1] = '@';
				p_map[b][a-2] = '$';
			}
		}
}

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
int error(void){
    int box=0, place=0;
    for(int b=0; b<5; b++){
        for(int i=0; i<30; i++)
            for(int j=0; j<30; j++)
            {
                if(map[b][i][j]=='$')
                    box++;
                else if(map[b][i][j]=='o')
                    place++;
                else{}
            }
        if(box!=place){
            printf("맵에 오류가 있습니다.\n");
            exit();
        }
    }
}

//main

int main(void)
{
	readmap();
	playmap(stage);
	while(1){
	showgame();
	ctrl_key();
	}
}
