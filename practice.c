첫번째 int 에서 N은 4인데 선언된 숫자는 5개 이므로 에러두번째 int 에서 N-5 가 음수이므로 에러가 뜬다세번째 int 에서 3.0은 소수이므로 에러가 뜬다x-1에서 x는 정수가 아니므로 에러뜬다.\
 #include <stdio.h>
 #include <termio.h>
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

 int main(void){
    int input_char;

    while (1){
       printf("Type a letter : ");
       input_char = getch();
       if (input_char == 'y')
          printf("You inputed Yes\n");
       else if (input_char == 'q'){
          printf("Bye\n");
          break;
       }
       else
          printf("You inputed %c\n", input_char);
    } 
    return 0;
 }
#include <stdio.h>
#include <stdlib.h>
int main(void){
   FILE  *pro, *sol;
   int    c, i, opd1, opd2;

   if ((pro = fopen("problems", "w")) == NULL){
      printf("오류 : problems 파일을 열 수 없습니다.\n");
      exit(1);
   }
   for (i = 0; i < 50; i++)
      fprintf(pro, "%d + %d = \n", rand() % 1000, rand() % 1000);
   fclose(pro);

   if ((pro = fopen("problems", "r")) == NULL){
      printf("오류 : problems 파일을 열 수 없습니다.\n");
      exit(1);
   }
   if ((sol = fopen("solutions", "w")) == NULL){
      printf("오류 : solutions 파일을 열 수 없습니다.\n");
      exit(1);
   }

   while (fscanf(pro, "%d + %d = \n", &opd1, &opd2) != EOF)
      fprintf(sol, "%d + %d = %d\n", opd1, opd2, opd1 + opd2);

   fclose(pro);
   fclose(sol);

   return 0;
}
