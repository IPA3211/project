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
FILE  *map

int map[5][30][30];
//Seung-mo
int readmap(void){
	
	int a,b = 0, i = 0, j = 0;

	map = fopen("map", "r");

	while (fscanf(map, "%c", &a) != 'e')
	{	
		if(a == ' '){
			map[b][i][j] = 1;
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
		}
		else if(a == 'm'){
			b++;
		}
		else{}		
	}


}
//Jae-hyun

//Cheol-soon

//Jae-woo

//main

int main(void)
{
	int a;
	scanf("%d" &a);
	
	readmap();

	for (int i =0; i < 30; i++){
		for (int j = 0; j < 30; j++)
			printf("%d" map[a][i][j]);
		printf("\n")
	}
}
