/*********************
* date:
* group: handsome
* student ID: 20170259,20170319,20170293,
* 
*
********************/

/********************
  message or todo
  .: 1
  #: 2
  $: 3
  O: 4
  @: 5
  O+$ = $ : 6
*********************/

#include<stdio.h>

//common

int map[5][30][30];
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
			map[b][i][j] = 0;
			j++;
		}
		else if(a == '#'){
			map[b][i][j] = 2;
			j++;
		}
		else if(a == '$'){
			map[b][i][j] = 3;
			j++;
		}
		else if(a =='O'){
			map[b][i][j] = 4;
			j++;
		}
		else if(a =='@'){
			map[b][i][j] = 5;
			j++;
		}
		else if(a =='\n'){
			i++;
			j = 0;
		}
	/*	else if(a == '1'){
			b = 0;
		}
		else if(a == '2'){
			b = 1;
		}
		else if(a == '3'){
			b = 2;
		}*/
		else if (a == 97){
			b++;
		}
		else{}		
	}

	fclose(mapf);
	return 0;
}
//Jae-hyun

//Cheol-soon

//Jae-woo

//main

int main(void)
{
	int a = 0;
	readmap();	
	
	for (int i =0; i < 30; i++){
		for (int j = 0; j < 30; j++)
			printf("%d", map[a][i][j]);
		printf("\n");
	}
}
