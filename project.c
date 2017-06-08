/*********************
 * date:
 * group: handsome
 * student ID: 20170259,20170319,20170293,20170289
 *
 *
 ********************/

/********************
  message or todo

  O + $ = %
  @ + O = *

  1. read map: clear(on main)
  2. error: clear(on main)
  3. input name: clear(on main)
  4. game clear: clear(on main)
  5. ranking: jae-hyun
  6. save ranking: jae-woo
  7. h,j,k,l move: clear(on main)
  8. undo: cheol-soon
  9. new: clear(on main)
  10. exit: jae-woo
  11. replay: jae-hyun
  12. file load: clear(on main)
  13. save: clear(on main)
  14. help: clear(on main)
  15. top: cheol-soon
  16. each map top: cheol-soon
  17. time: jae-woo
 *********************/

/* FOR WINDOWS */
//#include <termio.h>

/* FOR MAC OS X */
#include <termios.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/* FOR ERROR FIX */
int ctrl_key(char ch);
//common var

char map[5][30][30];
char p_map[30][30];
int  mapsize[5];

int stage = 0;
int load=0;

char name[10];
char undo[6];
clock_t start,end;
double m_time,alltime,savetime;
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
				map[x][y][z] = ' ';

	while (fscanf(mapf, "%c", &a) != EOF)
	{
		if((a == ' ')||(a == '#')||(a == '$')||(a =='O')||(a =='@')){
			map[b][i][j] = a;
			j++;
		}
		else if(a =='\n'){
			i++;
			j = 0;
		}
		else if (a == 'm'||a =='e'){
			mapsize[b] = ++i;
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
	for(int i =0; i < mapsize[stage]-1; i++){
		for(int j = 0; j < 30; j++){
			if(p_map == '%')
				printf("$");
			else if (p_map == '*')
				printf("@");
			else
				printf("%c", p_map[i][j]);
		}
		printf("\n");
	}
	return 0;
}
int command(char x){
	switch (x)
	{
		case 'd':
			displayhelp();
			break;
		case 'u':
      undo_key();
			break;
		case 'r':
			break;
		case 'n':
			stage =0;
			playmap(stage);
			break;
		case 'e':
			system("clear");
			printf("SEE YOU ");
			for(int i = 0; i <10; i++)
				printf("%c", name[i]);
			printf("....\n");
			exit(1);
			break;
		case 's':
			save();
			break;
		case 'f':
			fileload();
			break;
		case 't':
			break;
		case '1':
			stage++;
			playmap(stage);
			break;

	}
}

int get_key(void)
{
	static char a;
	static char a_sav;

	printf("(command) %c", a);

	a = getch();

	if((a == 'h')||(a == 'j')||(a == 'k')||(a == 'l')){
		ctrl_key(a);
		undo[4] = undo[3];
		undo[3] = undo[2];
		undo[2] = undo[1];
		undo[1] = undo[0];
		undo[0] = a;

		a = 0;
	}
	else if(a == '\n')
		command(a_sav);
	else;
	a_sav = a;
}

int printname(void){

	printf("\tHello ");
	for(int i = 0; i < 10; i++)
		printf("%c", name[i]);
	printf("\n");
}


//Cheol-soon
int inputname(void)
{
	int nm;

	printf("사용자 명을 입력하시오(최대10자): ");
	for(nm =0; nm<10; nm++){
		scanf("%c", &name[nm]); //입력받은 값을 name배열값에 지정.
		if(name[nm] == '\n')
		{
			name[nm] = 0;
			break;
		}
	}
	return 0;
}

/* display help(d) */
int displayhelp(void){
	//만약 d키가 눌렸을 때 아래의 내용들이 보여짐.//
	system("clear");
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
	if(getch() == 'q');
	else
		displayhelp();
}

/* undo(u) */
int undo_key(void)
{
		if(undo[0] == 'h')
			ctrl_key('l');
		else if(undo[0] == 'j')
			ctrl_key('k');
		else if(undo[0] == 'k')
			ctrl_key('j');
		else if(undo[0] == 'l')
			ctrl_key('h');
		undo[0] = undo[1];
		undo[1] = undo[2];
		undo[2] = undo[3];
		undo[3] = undo[4];
		undo[4] = ' ';
			//이후 화물의 움직임은 생각해본다. 화물의 움직임의 배열을 하나 만듦.
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
				else if(map[b][i][j]=='O')
					place++;
				else{}
			}
		if(box!=place){
			printf("%d맵에 오류가 있습니다.\n", b);
			exit(1);
		}
	}
}
int gameclear(void)
	//game클리어 했을 때
{
	if(stage> 4){
	system("clear");
	printf("축하합니다. 모든 게임을 완료했습니다.\n");
	exit(1);
	}
}
int fileload(void)
{ //f키를 눌렀을 때
	FILE *sokoban;
	sokoban=fopen("sokoban.txt","r");
	for(int i=0;i<30;i++)
		for(int j=0;j<30;j++)
			fscanf(sokoban,"%c",&p_map[i][j]);
	fscanf(sokoban,"%3f",&savetime);
	fscanf(sokoban,"%d",&stage);
	fclose(sokoban);
	load=1;
	start=clock();
}
int save(void)
{ //s키
	end=clock();
	savetime= (end-start)/1000;
	FILE *sokoban;
	sokoban=fopen("sokoban.txt","w");
	for(int i=0; i<30;i++)
		for(int j=0; j<30; j++)
		{
			fprintf(sokoban,"%c",p_map[i][j]);
		}
	fprintf(sokoban,"%3f",savetime);
	fprintf(sokoban,"%d",stage);
	fclose(sokoban);
	start=clock();
}
int timeprint(void){
  if(load==1)
  	m_time=savetime+((end-start)/1000);
  else
  	m_time= (end-start)/1000;
  alltime+=m_time;
  printf("클리어 시간: %3f\n",m_time);
  }
//Jae-hyun
int ctrl_key(char ch)
{
    int a, b, brilliant;
    for(int i=0;i<30;i++)
    {
        for(int j=0;j<30;j++)
        {
            if ((p_map[i][j] == '@')||(p_map[i][j] == '*')){
                b = i, a = j;
                break;
            }
        }
    }
    //right

    if((ch == 'l')&&(p_map[b][a+1] == ' '))//player heading to space
    {
        if(brilliant == 0)
        {
            p_map[b][a] = p_map[b][a+1];
            p_map[b][a+1] = '@';
            a += 1;
        }
        else if(brilliant == 1)
        {
            p_map[b][a] = 'O';
            p_map[b][a+1] = '@';
            a += 1;
            brilliant = 0;
        }
    }
    else if((ch == 'l')&&(p_map[b][a+1]) == '#')//player confronting wall
    {}
    else if((ch == 'l')&&(p_map[b][a+1]) == '$')//player confronting package
    {

        if(p_map[b][a+2] == '#')//package confronting the wall
        {}
        else if(p_map[b][a+2] == ' ')//package heading to space
        {
            p_map[b][a] = p_map[b][a+2];
            p_map[b][a+1] = '@';
            p_map[b][a+2] = '$';
            a += 1;
        }
    }
    else if((ch == 'l')&&(p_map[b][a+1] == 'O'))
    {
        p_map[b][a+1] = p_map[b][a];
        p_map[b][a] = ' ';
        brilliant = 1;//player on the location
        a += 1;
        if(brilliant == 1)
        {
            p_map[b][a] = 'O';
            p_map[b][a+1] = '@';
            a += 1;
            brilliant = 0;
        }
    }
    if((ch == 'l')&&(p_map[b][a+1] == '$')&&(p_map[b][a+2] == 'O'))
    {
        p_map[b][a+1] = p_map[b][a];
        p_map[b][a+2] = '*';
        p_map[b][a] = ' ';
        a += 1;
    }
    else if((ch == 'l')&&(p_map[b][a+1] == '*')&&(p_map[b][a+2] == 'O'))
    {
        p_map[b][a] = 'O';
        p_map[b][a+1] = p_map[b][a+2];
        p_map[b][a+2] = '*';
        a += 1;
        brilliant = 1;
    }
    else if((ch == 'l')&&(p_map[b][a+1] == '*')&&(p_map[b][a+2] == ' '))
    {
        p_map[b][a+1] = p_map[b][a];
        p_map[b][a] = 'O';
        p_map[b][a+2] = '$';
        a += 1;
    }
    if((ch == 'l')&&((p_map[b][a+1] == '$')||(p_map[b][a+1] == '*'))&&((p_map[b][a+2] == '$')||(p_map[b][a+2] == '*')))
    {}

    //left
    if((ch == 'h')&&((p_map[b][a-1] == ' ')||p_map[b][a-1] == 'O'))//player heading to space
    {
        if(brilliant == 0)
        {
            p_map[b][a] = p_map[b][a-1];
            p_map[b][a-1] = '@';
            a -= 1;
        }
        else if(brilliant == 1)
        {
            p_map[b][a] = 'O';
            p_map[b][a+1] = '@';
            a -= 1;
            brilliant = 0;
        }
    }
    else if((ch == 'h')&&(p_map[b][a-1]) == '#')//player confronting wall
    {}
    else if((ch == 'h')&&(p_map[b][a-1]) == '$')//player confronting package
    {

        if(p_map[b][a-2] == '#')//package confronting the wall
        {}
        else if(p_map[b][a-2] == ' ')//package heading to space
        {
            p_map[b][a] = p_map[b][a-2];
            p_map[b][a-1] = '@';
            p_map[b][a-2] = '$';
            a -= 1;
        }
    }
    else if((ch == 'h')&&(p_map[b][a-1] == 'O'))
    {
        p_map[b][a-1] = p_map[b][a];
        p_map[b][a] = ' ';
        brilliant = 1;//player on the location
        a -= 1;
    }
    if((ch == 'h')&&(p_map[b][a-1] == '$')&&(p_map[b][a-2] == 'O'))
    {
        p_map[b][a-1] = p_map[b][a];
        p_map[b][a-2] = '*';
        p_map[b][a] = ' ';
        a -= 1;
    }
    else if((ch == 'h')&&(p_map[b][a-1] == '*')&&(p_map[b][a-2] == 'O'))
    {
        p_map[b][a] = 'O';
        p_map[b][a-1] = p_map[b][a-2];
        p_map[b][a-2] = '*';
        a -= 1;
        brilliant = 1;
    }
    else if((ch == 'h')&&(p_map[b][a-1] == '*')&&(p_map[b][a-2] == ' '))
    {
        p_map[b][a-1] = p_map[b][a];
        p_map[b][a] = 'O';
        p_map[b][a-2] = '$';
        a -= 1;
    }
    if((ch == 'h')&&((p_map[b][a-1] == '$')||(p_map[b][a-1] == '*'))&&((p_map[b][a-2] == '$')||(p_map[b][a-2] == '*')))
    {}
    //up
    if((ch == 'k')&&((p_map[b+1][a] == ' ')||p_map[b+1][a] == 'O'))//player heading to space
    {
        if(brilliant == 0)
        {
            p_map[b][a] = p_map[b+1][a];
            p_map[b+1][a] = '@';
            b += 1;
        }
        else if(brilliant == 1)
        {
            p_map[b][a] = 'O';
            p_map[b+1][a] = '@';
            b += 1;
            brilliant = 0;
        }
    }
    else if((ch == 'k')&&(p_map[b+1][a]) == '#')//player confronting wall
    {}
    else if((ch == 'k')&&(p_map[b+1][a]) == '$')//player confronting package
    {

        if(p_map[b+2][a] == '#')//package confronting the wall
        {}
        else if(p_map[b+2][a] == ' ')//package heading to space
        {
            p_map[b][a] = p_map[b+2][a];
            p_map[b+1][a] = '@';
            p_map[b+2][a] = '$';
            b += 1;
        }
    }
    else if((ch == 'k')&&(p_map[b+1][a] == 'O'))
    {
        p_map[b+1][a] = p_map[b][a];
        p_map[b][a] = ' ';
        brilliant = 1;//player on the location
        b += 1;
    }
    if((ch == 'k')&&(p_map[b+1][a] == '$')&&(p_map[b+2][a] == 'O'))
    {
        p_map[b+1][a] = p_map[b][a];
        p_map[b+2][a] = '*';
        p_map[b][a] = ' ';
        b += 1;
    }
    else if((ch == 'k')&&(p_map[b+1][a] == '*')&&(p_map[b+2][a] == 'O'))
    {
        p_map[b][a] = 'O';
        p_map[b+1][a] = p_map[b+2][a];
        p_map[b+2][a] = '*';
        b += 1;
        brilliant = 1;
    }
    else if((ch == 'k')&&(p_map[b+1][a] == '*')&&(p_map[b+2][a] == ' '))
    {
        p_map[b+1][a] = p_map[b][a];
        p_map[b][a] = 'O';
        p_map[b+2][a] = '$';
        b += 1;
    }
    if((ch == 'k')&&((p_map[b+1][a] == '$')||(p_map[b+1][a] == '*'))&&((p_map[b+2][a] == '$')||(p_map[b+2][a] == '*')))
    {}
    //down
    if((ch == 'j')&&((p_map[b-1][a] == ' ')||p_map[b-1][a] == 'O'))//player heading to space
    {
        if(brilliant == 0)
        {
            p_map[b][a] = p_map[b-1][a];
            p_map[b-1][a] = '@';
            b -= 1;
        }
        else if(brilliant == 1)
        {
            p_map[b][a] = 'O';
            p_map[b-1][a] = '@';
            b -= 1;
            brilliant = 0;
        }
    }
    else if((ch == 'j')&&(p_map[b-1][a]) == '#')//player confronting wall
    {}
    else if((ch == 'j')&&(p_map[b-1][a]) == '$')//player confronting package
    {

        if(p_map[b-2][a] == '#')//package confronting the wall
        {}
        else if(p_map[b-2][a] == ' ')//package heading to space
        {
            p_map[b][a] = p_map[b-2][a];
            p_map[b-1][a] = '@';
            p_map[b-2][a] = '$';
            b -= 1;
        }
    }
    else if((ch == 'j')&&(p_map[b-1][a] == 'O'))
    {
        p_map[b-1][a] = p_map[b][a];
        p_map[b][a] = ' ';
        brilliant = 1;//player on the location
        b -= 1;
    }
    if((ch == 'j')&&(p_map[b-1][a] == '$')&&(p_map[b-2][a] == 'O'))
    {
        p_map[b-1][a] = p_map[b][a];
        p_map[b-2][a] = '*';
        p_map[b][a] = ' ';
        b -= 1;
    }
    else if((ch == 'j')&&(p_map[b-1][a] == '*')&&(p_map[b-2][a] == 'O'))
    {
        p_map[b][a] = 'O';
        p_map[b-1][a] = p_map[b-2][a];
        p_map[b-2][a] = '*';
        b -= 1;
        brilliant = 1;
    }
    else if((ch == 'j')&&(p_map[b-1][a] == '*')&&(p_map[b-2][a] == ' '))
    {
        p_map[b-1][a] = p_map[b][a];
        p_map[b][a] = 'O';
        p_map[b-2][a] = '$';
        b -= 1;
    }
    if((ch == 'j')&&((p_map[b-1][a] == '$')||(p_map[b-1][a] == '*'))&&((p_map[b-2][a] == '$')||(p_map[b-2][a] == '*')))
    {}//main
}

int main(void)
{
	system("clear");
    readmap();
    error();
    playmap(stage);
	inputname();
    system("clear");
    while(1){
        printname();
        showgame();
        get_key();
        gameclear();
        system("clear");
    }
}
