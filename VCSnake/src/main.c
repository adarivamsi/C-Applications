/**Snake Bite Game Developed by Adari Vamsi
   --------------Version 1.1---------------
   Grab the Input device to Play Harder
   Adari Vamsi Visual Efx
*/
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <process.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

int length,bend_no,len,life;
char key;

void record();
void load();
void Delay(long double);
void Move();
void Food();
int Score();
void Print();
void gotoxy(int x, int y);
void GotoXY(int x,int y);
void Bend();
void Border();
void Down();
void Left();
void Up();
void Right();
void ExitGame();
int Scoreonly();

struct coordinate
{
    int x,y,direction;
};

typedef struct coordinate coordinate;

coordinate head,bend[500],food,body[30];

int main()
{
    char key;

    Print();

    system("cls");

    load();

    length=5;
    head.x=25;
    head.y=20;
    head.direction=RIGHT;

    Border();

    Food(); //to generate food coordinates initially

    life=3; //Number of Lives

    bend[0]=head;

    Move(); //initialing initial bend coordinate

    return 0;
}

void Move()
{
    int a,i;

    do{

        Food();
        fflush(stdin);

        len=0;

        for(i=0;i<30;i++)
        {
            body[i].x=0;

            body[i].y=0;

            if(i==length)

            break;
        }

        Delay(length);

        Border();

        if(head.direction==RIGHT)

            Right();

        else if(head.direction==LEFT)

            Left();

        else if(head.direction==DOWN)

            Down();

        else if(head.direction==UP)

            Up();

        ExitGame();
    }

    while(!kbhit());

    a=getch();

    if(a==27)

    {
        system("cls");

        exit(0);
    }

    key=getch();

    if((key==RIGHT&&head.direction!=LEFT&&head.direction!=RIGHT)||(key==LEFT&&head.direction!=RIGHT&&head.direction!=LEFT)||(key==UP&&head.direction!=DOWN&&head.direction!=UP)||(key==DOWN&&head.direction!=UP&&head.direction!=DOWN))
    {

        bend_no++;

        bend[bend_no]=head;

        head.direction=key;

        if(key==UP)

            head.y--;

        if(key==DOWN)

            head.y++;

        if(key==RIGHT)

            head.x++;

        if(key==LEFT)

            head.x--;

        Move();
    }

    else if(key==27)
    {
        system("cls");

        exit(0);
    }

    else
    {
        printf("\a");

        Move();
    }
}

void gotoxy(int x, int y)
{
 COORD coord;

 coord.X = x;

 coord.Y = y;

 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void GotoXY(int x, int y)
{
    HANDLE a;
    COORD b;
    fflush(stdout);
    b.X = x;
    b.Y = y;
    a = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(a,b);
 }

void load()
{
    int row,col,r,c,q;
    gotoxy(36,14);
    printf("loading...");
    gotoxy(30,15);
    for(r=1;r<=20;r++){
    for(q=0;q<=100000000;q++);//to display the character slowly
    printf("%c",177);}
    getch();
}

void Down()
{
    int i;
    for(i=0;i<=(head.y-bend[bend_no].y)&&len<length;i++)
    {
        GotoXY(head.x,head.y-i);
        {
            if(len==0)
                printf("O");
            else
                printf("#");
        }
        body[len].x=head.x;
        body[len].y=head.y-i;
        len++;
    }
    Bend();
    if(!kbhit())
        head.y++;
}

void Delay(long double k)
{
    Score();
    long double i;
    for(i=0;i<=(10000000);i++);
}

void ExitGame()
{
    int i,check=0;
    for(i=4;i<length;i++)   //starts with 4 because it needs minimum 4 element to touch its own body
    {
        if(body[0].x==body[i].x&&body[0].y==body[i].y)
        {
            check++;    //check's value increases as the coordinates of head is equal to any other body coordinate
        }
        if(i==length||check!=0)
            break;
    }

    if(head.x<=10||head.x>=70||head.y<=10||head.y>=30||check!=0)
    {
        life--;
        if(life>=0)
        {
            head.x=25;
            head.y=20;
            bend_no=0;
            head.direction=RIGHT;
            Move();
        }
        else
        {
            system("cls");
            printf("All LIVES Completed\nBetter Luck Next Time!!!\nPress any key to quit the GAME\n");
            record();
            exit(0);
        }
    }
}

void Food()
{
    if(head.x==food.x&&head.y==food.y)
    {
        length++;
        time_t a;
        a=time(0);
        srand(a);
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)
            food.y+=11;
    }
    else if(food.x==0)/*to create food for the first time coz global variable are initialized with 0*/
    {
        food.x=rand()%70;
        if(food.x<=10)
            food.x+=11;
        food.y=rand()%30;
        if(food.y<=10)
            food.y+=11;
    }
}

void Left()
{
    int i;
    for(i=0;i<=(bend[bend_no].x-head.x)&&len<length;i++)
    {
        GotoXY((head.x+i),head.y);
       {
                if(len==0)
                    printf("O");
                else
                    printf("#");
        }
        body[len].x=head.x+i;
        body[len].y=head.y;
        len++;
    }
    Bend();
    if(!kbhit())
        head.x--;

}

void Right()
{
    int i;
    for(i=0;i<=(head.x-bend[bend_no].x)&&len<length;i++)
    {
        body[len].x=head.x-i;
        body[len].y=head.y;
        GotoXY(body[len].x,body[len].y);
        {
            if(len==0)
                printf("O");
            else
                printf("#");
        }
        len++;
    }
    Bend();
    if(!kbhit())
        head.x++;
}

void Bend()
{
    int i,j,diff;
    for(i=bend_no;i>=0&&len<length;i--)
    {
            if(bend[i].x==bend[i-1].x)
            {
                diff=bend[i].y-bend[i-1].y;
                if(diff<0)
                    for(j=1;j<=(-diff);j++)
                    {
                        body[len].x=bend[i].x;
                        body[len].y=bend[i].y+j;
                        GotoXY(body[len].x,body[len].y);
                        printf("#");
                        len++;
                        if(len==length)
                            break;
                    }
                else if(diff>0)
                    for(j=1;j<=diff;j++)
                    {
                        body[len].x=bend[i].x;
                        body[len].y=bend[i].y-j;
                        GotoXY(body[len].x,body[len].y);
                        printf("#");
                        len++;
                        if(len==length)
                            break;
                    }
            }
        else if(bend[i].y==bend[i-1].y)
        {
            diff=bend[i].x-bend[i-1].x;
            if(diff<0)
                for(j=1;j<=(-diff)&&len<length;j++)
                {
                   body[len].x=bend[i].x+j;
                    body[len].y=bend[i].y;
                    GotoXY(body[len].x,body[len].y);
                        printf("#");
                   len++;
                   if(len==length)
                           break;
               }
           else if(diff>0)
               for(j=1;j<=diff&&len<length;j++)
               {
                   body[len].x=bend[i].x-j;
                   body[len].y=bend[i].y;
                   GotoXY(body[len].x,body[len].y);
                       printf("#");
                   len++;
                   if(len==length)
                       break;
               }
       }
   }
}

void Border()
{
   system("cls");
   int i;
   GotoXY(food.x,food.y);   /*displaying food*/
       printf("V");
   for(i=10;i<71;i++)
   {
       GotoXY(i,10);
           printf("!");
       GotoXY(i,30);
           printf("!");
   }
   for(i=10;i<31;i++)
   {
       GotoXY(10,i);
           printf("!");
       GotoXY(70,i);
       printf("!");
   }
}

void Print()
{
   printf("\n\n\n\t---------> VC <-----------\n\n\n\tSnake Bite Welcomes you :D\n\n\n\t( Press Any Key to Continue )\n");
   getch();
   system("cls");
   printf("Game instructions:\n");
   printf("\n1. Movements of the Snake to be controlled by Arrows.\n\n2. Grab every bite of --> VC <-- which acts as FOOD to your Snake.\n\n3. Every Bite you grab makes your body strong increasing the score.\n\n4. Three Chances for your Game every time you hit a wall or snakes body you will be losing a LIFE.\n\n5. You can even PAUSE the game in its middle by pressing any key. To continue the paused game \n   press any other key once again\n\n6. At any time you can QUIT by pressing ESC \n");
   printf("\n\nPress any key to Begin the\n\n\t---> GAME <---");
   if(getch()==27)
   exit(0);
}

void record(){
   char plname[20],nplname[20],cha,c;
   int i,j,px;
   FILE *info;
   info=fopen("scores.txt","a+");
   getch();
   system("cls");
   printf("Enter your Snake Name\n");
   scanf("%[^\n]",plname);
   //************************
   for(j=0;plname[j]!='\0';j++){ //to convert the first letter after space to capital
   nplname[0]=toupper(plname[0]);
   if(plname[j-1]==' '){
   nplname[j]=toupper(plname[j]);
   nplname[j-1]=plname[j-1];}
   else nplname[j]=plname[j];
   }
   nplname[j]='\0';
   //*****************************
   fprintf(info,"Snake Name :%s\n",nplname);

    //for date and time
   time_t mytime;
  mytime = time(NULL);
  fprintf(info,"Last Attempt On :%s",ctime(&mytime));
     //**************************
     fprintf(info,"Score:%d\n",px=Scoreonly());//call score to display score
   for(i=0;i<=50;i++)
   fprintf(info,"%c",'_');
   fprintf(info,"\n");
   fclose(info);
   printf("Wanna see your past records press 'y'\'n'");
   cha=getch();
   system("cls");
   if(cha=='y'){
   info=fopen("scores.txt","r");
   do{
       putchar(c=getc(info));
       }while(c!=EOF);}
     fclose(info);
}

int Score()
{
   int score;
   GotoXY(20,8);
   score=length-5;
   printf("Total Score : %d",(length-5));
   score=length-5;
   GotoXY(50,8);
   printf("Chance : %d",life);
   return score;
}

int Scoreonly()
{
int score=Score();
system("cls");
return score;
}

void Up()
{
   int i;
   for(i=0;i<=(bend[bend_no].y-head.y)&&len<length;i++)
   {
       GotoXY(head.x,head.y+i);
       {
           if(len==0)
               printf("O");
           else
               printf("#");
       }
       body[len].x=head.x;
       body[len].y=head.y+i;
       len++;
   }
   Bend();
   if(!kbhit())
       head.y--;
}
/**Snake Bite Game Developed by Adari Vamsi
   --------------Version 1.1---------------
   Grab the Input device to Play Harder
   Adari Vamsi Visual Efx
*/
