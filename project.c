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
int player_xy(void);

//common var

char map[5][30][30];
char p_map[30][30];
int  mapsize[5];
int player_x, player_y;//player's x,y


int stage = 0;
int load=0;
int box = 0;

char name[10];
char undo[2][5] = {0,0,0,0,0,0,0,0,0,0};
time_t start,end;
float m_time,alltime=0,savetime;
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
			if(p_map[i][j] == '*')
				printf("$");
			else if (p_map[i][j] == 'P')
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
			if(undo[0][0] != 0)
      	undo_key();
				break;
		case 'r':
			playmap(stage);
			break;
		case 'n':
			stage =0;
			playmap(stage);
			start=time(NULL);
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
  int c;

	printf("(command) %c", a);

	a = getch();

	if((a == 'h')||(a == 'j')||(a == 'k')||(a == 'l')){
		c = ctrl_key(a);
    if(c == 1){
      for(int i = 0; i <2; i++){
        for(int j = 3; j>=0; j--){
          undo[i][j+1] = undo[i][j];
        }
			}
		undo[0][0] = a;
	  undo[1][0] = 0;
		}
    if(c == 2){
      for(int i = 0; i <2; i++){
        for(int j = 3; j>=0; j--){
          undo[i][j+1] = undo[i][j];
        }
			}
		undo[0][0] = a;
		undo[1][0] = 1;
    }
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

int player_xy(void)
{
	for(int i=0;i<30;i++)
	{
		for(int j=0;j<30;j++)
		{
			if ((p_map[i][j] == '@')||(p_map[i][j] == 'P')){
				player_y = i, player_x = j;
				break;
			}
		}
	}
	return 0;
}

/* undo(u) */
int undo_key(void)
{
	player_xy();
	int box_x, box_y;
  char reverse;

	switch (undo[0][0]) {
		case 'l':
			box_x = 1;
			box_y = 0;
			reverse = 'h';
			break;
		case 'k':
			box_x = 0;
			box_y = 1;
			reverse = 'j';
			break;
		case 'j':
			box_x = 0;
			box_y = -1;
			reverse = 'k';
			break;
		case 'h':
			box_x = -1;
			box_y = 0;
			reverse = 'l';
			break;
		default:
			break;
	}

    if(undo[1][0] == 1)
    {
      ctrl_key(reverse);
			if((p_map[player_y+box_y][player_x+box_x] == '*')&&(p_map[player_y][player_x] == ' ')){
				p_map[player_y+box_y][player_x+box_x] = 'O';
				p_map[player_y][player_x] = '$';
			}
			else if((p_map[player_y+box_y][player_x+box_x] == '*')&&(p_map[player_y][player_x] == 'O')) {
      	p_map[player_y+box_y][player_x+box_x] = 'O';
      	p_map[player_y][player_x] = '*';
			}
			else if((p_map[player_y+box_y][player_x+box_x] == '$')&&(p_map[player_y][player_x] == ' ')) {
      	p_map[player_y+box_y][player_x+box_x] = ' ';
      	p_map[player_y][player_x] = '$';
			}
			else if((p_map[player_y+box_y][player_x+box_x] == '$')&&(p_map[player_y][player_x] == 'O')) {
      	p_map[player_y+box_y][player_x+box_x] = ' ';
      	p_map[player_y][player_x] = ' ';
			}
    }
    else if (undo[1][0] == 0)
      ctrl_key(reverse);
		else
		{}
  for(int i = 1; i >=0; i--){
		if(i == 0){
			for(int j = 0; j <5; j++){
			undo[i][j] = undo[i][j+1];
			}
			undo[0][4] = 0;
		}
		else{
      for(int j = 0; j < 5; j++){
        undo[i][j] = undo[i][j+1];
			}
			undo[1][4] = 0;
		}
	}
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
	fscanf(sokoban,"%f",&savetime);
	fscanf(sokoban,"%d",&stage);
	fclose(sokoban);
	load=1;
	start=time(NULL);
}
int save(void)
{ //s키
	end=time(NULL);
	savetime=end-start;
	FILE *sokoban;
	sokoban=fopen("sokoban.txt","w");
	for(int i=0; i<30;i++)
		for(int j=0; j<30; j++)
		{
			fprintf(sokoban,"%c",p_map[i][j]);
		}
	fprintf(sokoban,"%f",savetime);
	fprintf(sokoban,"%d",stage);
	fclose(sokoban);
	start=time(NULL);
}

int timeprint(void){
  if(load==1)
  	m_time=savetime+(end-start);
  else
  	m_time= end-start;
  alltime+=m_time;
  printf("클리어 시간: %f\n",m_time);
  }

int mapclear(void)
{
	if(box==0)
	{
		time(&end);
		timeprint();
		stage++;
		playmap(stage);
	}
}

//jae-hyun
int ranking(void)
{
	FILE = *ranking;
	ranking = fopen("ranking.txt","w");
	if (box == 0)
	{
		int rank[10];
		int rankcount = 10;
		int hold = 0, loop, i;
		int stageR = 0;
		for (loop = 0; loop < rankcount - 1; loop++) {
			for (i = 0; i < rankcount - 1 - loop; i++) {
				if (rank[i] > rank[i + 1]) {
					hold = rank[i];
					rank[i] = rank[i + 1];
					rank[i + 1] = hold;
				}
			}
		}

		for (i = 0; i < rankcount; i++) {
			printf("%d", rank[i]);
		}
		stageR++;
	}
}

int ctrl_key(char ch)
{
    int a, b, c, d;
    for(int i=0;i<30;i++)
    {
      for(int j=0;j<30;j++)
      {
		  if ((p_map[i][j] == '@') || (p_map[i][j] == 'P')) {
			  b = i, a = j;
		  }
      }
    }


      switch (ch) {
        case 'l':
          c = 1;
          d = 0;
          break;
        case 'k':
          c = 0;
          d = 1;
          break;
        case 'j':
          c = 0;
          d = -1;
          break;
        case 'h':
          c = -1;
          d = 0;
          break;
      }

      if(p_map[b][a] == '@')//user on space*******************
      {
        if((p_map[b+d][a+c] == '#'))//wall  1
        {
          return 0;
        }
        else if((p_map[b+d][a+c] == 'O'))//location  2
        {
          p_map[b+d][a+c] = 'P';
          p_map[b][a] = ' ';
          return 1;
        }

        else if((p_map[b+d][a+c] == '$'))//package  3
        {
          if(p_map[b+(d*2)][a+(c*2)] == '#')//package facing wall
          {
            return 0;
          }
          else if(p_map[b+(d*2)][a+(c*2)] == ' ')//package facing space
          {
            p_map[b+(d*2)][a+(c*2)] = '$';
            p_map[b+d][a+c] = '@';
            p_map[b][a] = ' ';
            return 2;
          }
          else if(p_map[b+(d*2)][a+(c*2)] == 'O')//package facing location
          {
            p_map[b+(d*2)][a+(c*2)] = '*';
            p_map[b+d][a+c] = '@';
            p_map[b][a] = ' ';
            return 2;
          }
          else if(p_map[b+(d*2)][a+(c*2)] == '*')//package facing other package on location
          {
            return 0;
          }
          else if(p_map[b+d][a+c] == '$')//packaage facing other package
          {
            return 0;
          }
        }

        else if((p_map[b+d][a+c] == ' '))//space  4
        {
          p_map[b+d][a+c] = '@';
          p_map[b][a] = ' ';
          return 1;
        }

        else if((p_map[b+d][a+c] == '*'))//package on the location  5
        {
          if(p_map[b+(d*2)][a+(c*2)] == '#')//package on location facing wall
          {
            return 0;
          }
          else if(p_map[b+(d*2)][a+(c*2)] == ' ')//package on location facing space
          {
            p_map[b+(d*2)][a+(c*2)] = '$';
            p_map[b+d][a+c] = 'P';
            p_map[b][a] = ' ';
            return 2;
          }
          else if(p_map[b+(d*2)][a+(c*2)] == 'O')//package on location facing location
          {
            p_map[b+(d*2)][a+(c*2)] = '*';
            p_map[b+d][a+c] = 'P';
            p_map[b][a] = ' ';
            return 2;
          }
          else if(p_map[b+(d*2)][a+(c*2)] == '*')//package on location facing other package on location
          {
            return 0;
          }
          else if(p_map[b+d][a+c] == '$')//packaage on location facing other package
          {
            return 0;
          }
        }
      }
      else if(p_map[b][a] == 'P')//user on the location******************
      {
        if((p_map[b+d][a+c] == '#'))//wall                1
        {
          return 0;
        }
        else if((p_map[b+d][a+c] == '$'))//package        2
        {
          if(p_map[b+(d*2)][a+(c*2)] == '#')//package facing wall
          {
            return 0;
          }
          else if(p_map[b+(d*2)][a+(c*2)] == ' ')//package facing space
          {
            p_map[b+(d*2)][a+(c*2)] = '$';
            p_map[b+d][a+c] = '@';
            p_map[b][a] = 'O';
            return 2;
          }
          else if(p_map[b+(d*2)][a+(c*2)] == 'O')//package facing location
          {
            p_map[b+(d*2)][a+(c*2)] = '*';
            p_map[b+d][a+c] = 'P';
            p_map[b][a] = 'O';
            return 2;
          }
          else if(p_map[b+(d*2)][a+(c*2)] == '*')//package facing other package on location
          {
            return 0;
          }
          else if(p_map[b+d][a+c] == '$')//packaage facing other package
          {
            return 0;
          }
        }

        else if((p_map[b+d][a+c] == '*'))//package on the location3
        {
          if(p_map[b+(d*2)][a+(c*2)] == '#')//package on location facing wall
          {
            return 0;
          }
          else if(p_map[b+(d*2)][a+(c*2)] == ' ')//package on location facing space
          {
            p_map[b+(d*2)][a+(c*2)] = '$';
            p_map[b+d][a+c] = 'P';
            p_map[b][a] = 'O';
            return 2;
          }
          else if(p_map[b+(d*2)][a+(c*2)] == 'O')//package on location facing location
          {
            p_map[b+(d*2)][a+(c*2)] = '*';
            p_map[b+d][a+c] = 'P';
            p_map[b][a] = 'O';
            return 2;
          }
          else if(p_map[b+(d*2)][a+(c*2)] == '*')//package on location facing other package on location
          {
            return 0;
          }
          else if(p_map[b+d][a+c] == '$')//packaage on location facing other package
          {
            return 0;
          }
        }

        else if((p_map[b+d][a+c] == ' '))//space              4
        {
          p_map[b+d][a+c] = '@';
          p_map[b][a] = 'O';
          return 1;
        }
        else if((p_map[b+d][a+c] == 'O'))//location          5
        {
          p_map[b+d][a+c] = 'P';
          p_map[b][a] = 'O';
          return 1;
        }
      }
      else if((p_map[b][a] != '@')||(p_map[b][a] != 'P'))
      printf("move error");
      else
      printf("error");
}

int box_check(void)
{
	box = 0;
    for(int i=0;i<30;i++)
    {
      for(int j=0;j<30;j++)
      {
		  if (p_map[i][j] == '$')
			  box++;
      }
    }
}

//main
int main(void)
{
	system("clear");
    readmap();
    error();
    playmap(stage);
	inputname();
    system("clear");
	time(&start);
    while(1){
        printname();
        showgame();
        get_key();
				box_check();
				mapclear();
        gameclear();
				system("clear");
        }
}
