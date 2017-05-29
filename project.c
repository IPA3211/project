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

//Seung-mo

//Jae-hyun

//Cheol-soon
/* 사용자명 입력받는 것
영문 최대 10문자
작성자: cheolsoon */
int inputname(void)
{
 char name[10]; //입력받은 name값을 배열로 저장
 int nm;

  printf("사용자 명을 입력하시오(최대10자): ");
  for(nm=0;nm<10;nm++)
  scanf("%c", &name[nm]); //입력받은 값을 name배열값에 지정.

  printf("username: %c%c%c%c%c%c%c%c%c", name[0], name[1], name[2], name[3], name[4], name[5], name[6], name[7], name[8], name[9]);

  //
  return 0;
}

//Jae-woo

//main

int main(void)
{

}
