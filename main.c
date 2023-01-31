#include "lib.h"
#define RESETCOLOR "\033[0m"
typedef struct{
    int x;
    int y;
}loc;
void print_menu(int *flag,HANDLE h); //Menu of the program
void drawlowerbound();
void drawupperbound();
void rightbound();
void leftbound();
void bound(); // combination of drawing bounds into one function
void initialize(loc snake[],int size,int x,int y);
void createsnake(loc snake[],int size);
void createsnake2(loc snake[],int size);
void delete_presnake(loc snake[],int size); // delete the old snake when moving
void allocate_add(loc **snake,loc t,int *size); // add the head of the snake when moving
void delete(loc **snake, int *size); //remove the tail of the snake
bool checkapple(loc snake[],int xapple,int yapple,int size);//when generating random apple,checking and preventing apple in snake body
void createapple(int *xapple,int *yapple,loc snake[],int size); // generate apple
int checkhittingapple(int *xapple,int *yapple,int x0,int y0); //when hit the apple, increase length of snake and generate new apple
bool checkgame_bound(int x0,int y0); // gameover condition
bool checkgame_tail(loc snake[],int size); //gameover condition
bool checksnake(loc snake[],int size); // gameover condition of the two mentioned above
void print_score(int *score,int *highscore,FILE *f); // Display score on the screen
void Gameover(int *score,int *highscore, FILE *g,FILE *f); // save the highscore to the file and print if the player break the score
void bite_snake1(loc snake[],loc snake2[],int *size,int size2);
void bite_eachother(loc**snake,loc**snake2,int *size,int *size2); 
void Gameover_double(int score1,int score2);
void print_score_double(int score1,int score2);
void updatecolor(HANDLE h,int x); //Setting color for the text
int main()
{
    FILE *g; //file handling to store the score of every playing.
    FILE *f; //file handling to store the highest score after each time
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    int flag=0;
    print_menu(&flag,h);
    while (flag!=3)// The player can play again.  If flag =3 when the user can end the game and exit from the program.
    {
    if(flag==1)
    {
    int size=7;
    bool gameover=false;
    bound();
    loc *snake=(loc *)malloc(sizeof(loc)*7); //dynamic snake
    initialize(snake,size,50,13);
    createsnake(snake,size);
    loc t;
    t.x=50; //the starting point of snake
    t.y=13; //the starting point of snake
    srand(time(NULL));
    //check and create apple
    int xapple=0,yapple=0;
    createapple(&xapple,&yapple,snake,size);
    int check=3;// sua random sau
    int score=0; //the current score
    int highscore=0; // the record after plenty of play
    while (gameover==false)
    {
        delete_presnake(snake,size);
        print_score(&score,&highscore,f);
        if(kbhit())
        {
            char kitu=getch();
            if (kitu==-32)
            {

                kitu=getch();
                if(kitu==72&& check!=0)//up
                    check=1;
                else if(kitu==80 && check!=1)//down
                    check=0;
                else if(kitu==75 && check!=3)//left
                    check=2;
                else if(kitu==77 && check!=2)//right
                    check=3;
            }
        }
        if (check==0)
            t.y++;  //up
        else if(check == 1)
            t.y--;  //left
        else if (check==2)
            t.x--;//left //right 
        else if(check==3)
            t.x++; // down
        // updatesnake(toadox,toadoy,x,y,&xapple,&yapple);
        if (checkhittingapple(&xapple,&yapple,snake[0].x,snake[0].y)==0)
        {
        allocate_add(&snake,t,&size); //adding one section to the head
        delete(&snake,&size);//delete tail
        createsnake(snake,size); //update the snake in new position
        }
        else
        {
        score=score+5;
        allocate_add(&snake,t,&size);
        createapple(&xapple,&yapple,snake,size); //generate new apple
        createsnake(snake,size); //update snake
        }
       // check bound and tail
        gameover=checksnake(snake,size); // the stop condition
        Sleep(100);
    }
       free(snake); //destroy 
       Gameover(&score,&highscore,g,f); // printf the score or the record after the end.
    } //the end of mode single player
    
    else // starting of mode double players
    {
    int size=7; // give the initial size of first snake 
    int size2=9; //give the initial size of second snake
    bound(); //drawing bound
    loc *snake1= (loc*)malloc(sizeof(loc)*size); //allocate memory for snakes
    loc *snake2= (loc*)malloc(sizeof(loc)*size2);
    initialize(snake1,size,50,13);
    initialize(snake2,size2,20,20);
   //createsnake(snake1,size);
   //createsnake(snake2,size2);
    bool gameover1=false;
    bool gameover2=false;
    loc t1;
    t1.x=50;
    t1.y=13;
    loc t2;
    t2.x=20;
    t2.y=20;
    srand(time(NULL)); //set a different seed of random
    int xapple=0,yapple=0;
    createapple(&xapple,&yapple,snake1,size); // generate an apple inside the bound
    int check1=3; //initializing variable check to modify the UP,LEFT,RIGHT,DOWN direction
    int check2=3;
    int score1=0; //Setting the score of snake 1 at the beginning
    int score2=0; //Setting the score of snake 2 at the beginning
    while (gameover1==false && gameover2== false)
    {
        //control snake1
        delete_presnake(snake1,size);
        print_score_double(score1,score2);
        if(kbhit())
        {
            char kitu=getch();
                if(kitu ==119 && check2!=0)//up 'w'
                    check2=1;
                else if(kitu==115 && check2!=1)//down 's'
                    check2=0;
                else if(kitu==97 &&  check2!=3)//left 'a'
                    check2=2;
                else if(kitu==100 && check2!=2)//right 'd'
                    check2=3;
                if(kitu ==105 && check1!=0)//up 'i'
                {
                    check1=1;
                }
                else if(kitu==107 && check1!=1)//down 'k'
                    check1=0;
                else if(kitu==106 &&  check1!=3)//left 'j'
                    check1=2;
                else if(kitu==108 && check1!=2)//right 'l'
                    check1=3;
        }
        //control snake1
        if (check1==0)
            t1.y++;
        else if(check1 == 1)
            t1.y--;
        else if (check1==2)
            t1.x--;//left
        else if(check1==3)
            t1.x++;
        //control snake2
        if (check2==0)
            t2.y++; //up
        else if(check2==1)
            t2.y--; //to the down
        else if(check2==2)
            t2.x--; //to the left
        else if(check2==3)
            t2.x++; //right
        //update snake1, similary with the previous one
        if (checkhittingapple(&xapple,&yapple,snake1[0].x,snake1[0].y)==0)
        {
        allocate_add(&snake1,t1,&size); // adding head by one section
        delete(&snake1,&size);//delete tail 
        createsnake(snake1,size);// update new snake
        }
        else
        {
        score1=score1+5; //increase the score by 5
       //createaple(&xapple,&yapple,snake,size);
        allocate_add(&snake1,t1,&size); //adding head by one section without deleting the tail
        createapple(&xapple,&yapple,snake1,size);// create new apple
        createsnake(snake1,size); //update new snake with the increased length
        }
        //update snake 2 with the same structure as the snake 1
        delete_presnake(snake2,size2);
        if (checkhittingapple(&xapple,&yapple,snake2[0].x,snake2[0].y)==0)
        {
        allocate_add(&snake2,t2,&size2);
        delete(&snake2,&size2);//delete tail
        createsnake2(snake2,size2);
        }
        else
        {
        score2=score2+5;
        allocate_add(&snake2,t2,&size2);
        createapple(&xapple,&yapple,snake1,size); //generate new apple
        createsnake2(snake2,size2); //update snake
        }
        if (checksnake(snake1,size)==true)
        {
            delete_presnake(snake1,size);
            size=0;
            free(snake1);
            gameover1=checksnake(snake2,size2);
        }
        else if (checksnake(snake2,size2)==true)
        {
             delete_presnake(snake2,size2);
             size2=0;
             free(snake2);
             gameover2=checksnake(snake1,size);
        }
        bite_eachother(&snake1,&snake2,&size,&size2); // eating head of each other, making both snakes die
        bite_eachother(&snake2,&snake1,&size2,&size); //eating head of each other
        bite_snake1(snake1,snake2,&size,size2); //snake2 bite the tail of snake1
        bite_snake1(snake2,snake1,&size2,size); //snake1 bite the tail of snake2
        if (size==0 && size2==0)
         {
             delete_presnake(snake1,size); //Delete the shape of snake before exitting
             delete_presnake(snake2,size2);
             gameover2=true; 
             break;
         }
         Sleep(100);
    }
    getch(); //Pause the output console
    Gameover_double(score1,score2);
    free(snake1); //avoid memory leakage
    free(snake2); //avoid memory leakage
    } // end of double player mode
    getch();
    system("cls"); //clear screen again
    print_menu(&flag,h); // ask the user to continue playing or stopping the program
    }

    return 0;
}
// List of functions are explained in details in the developement doc
void drawupperbound()
{
    int x=10,y=1;
    while(x<100)
    {
        gotoXY(x,y);
        printf("+");
        x++;  
    }
}
void drawlowerbound()
{
    int x=10,y=26;
    while(x<100)
    {
        gotoXY(x,y);
        printf("+");
        x++;
    }

}
void leftbound()
{
    int x=10,y=1;
    while(y<26)
    {
        gotoXY(x,y);
        printf("+");
        y++;
    }
}
void rightbound()
{
    int x=100,y=1;
    while(y<26)
    {
        gotoXY(x,y);
        printf("+");
        y++;
    }
}

void bound()
{
    drawupperbound();
    drawlowerbound();
    rightbound();
    leftbound();
}

void initialize(loc snake[],int size,int x,int y)
{
    for (int i=0; i<size; i++)
    {
        snake[i].x=x; //initializing an array of coordinates
        snake[i].y=y;
        x--;
    }
}
void createsnake(loc snake[],int size)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,5); //Setting color to the text(shape) of snake
    for (int i=0; i<size; i++)
    {
        gotoXY(snake[i].x,snake[i].y);
            char c=220;
            printf("%c",c); // the shape of snake consists of rectangles joining together
    }
    printf(RESETCOLOR);
}
void createsnake2(loc snake[],int size)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,2);
    for (int i=0; i<size; i++)
    {
        gotoXY(snake[i].x,snake[i].y);
            char c=220;
            printf("%c",c); // the shape of snake consists of rectangles joining together
    }
    printf(RESETCOLOR);
}
////Steps to control the snake 
void delete_presnake(loc snake[],int size)
{
    for (int i=0; i<size; i++)
    {
        gotoXY(snake[i].x,snake[i].y); //place the cursor to (x,y)
        printf(" ");  ////delete previous shape of snake
    }
}
void allocate_add(loc **snake,loc t,int *size)
{
    int len=*size;
    loc *newsnake=(loc *)malloc(sizeof(loc)*(len+1));
    for (int i=0;i<len;i++)
    {
        newsnake[i]=(*snake)[i];
    }
    newsnake[len]=t;
    //shifting array to the right
    loc temp=newsnake[len];
    for (int i=len;i>=1;i--)
    {
        newsnake[i]=newsnake[i-1];
    }
    newsnake[0]=temp;
    free(*snake);
    *snake=newsnake;
    *size=len+1;
}
void delete(loc **snake, int *size)
{
    int len=*size;
    loc *newsnake=(loc *)malloc(sizeof(loc)*(len-1));
    for (int i=0;i<len-1;i++)
    {
        newsnake[i]=(*snake)[i];
    }
    free(*snake);
    *snake=newsnake;
    *size=len-1; // delete the tail and reduce size by 1
}
bool checkapple(loc snake[],int xapple,int yapple,int size)//check apple in snake body
{
    for (int i=0; i<size; i++)
    {
        if (xapple==snake[i].x&& yapple==snake[i].y)
        {
            return true;//eat apple
        }
    }
    return false;// run by their own
}
void createapple(int *xapple,int *yapple,loc snake[],int size)
{
    do
    {
        *xapple=rand()%(99-11+1)+11;
        //random giua 2 khoang bound
        *yapple=rand()%(25-2+1)+2;
    }
    while (checkapple(snake,*xapple,*yapple,size)==true);
    gotoXY(*xapple,*yapple);
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE); 
    SetConsoleTextAttribute(h,12); //coloring the apple
    printf("$");
    printf(RESETCOLOR); // reset to default color afterward.
}
int checkhittingapple(int *xapple,int *yapple,int x0,int y0)
{
    if (x0==*xapple && y0==*yapple)
    {
        //score=score+5;
        return 1;
    }
    return 0;
}
bool checkgame_bound(int x0,int y0)
{
    if (y0==1&&(x0>=10 && x0<=100))
    {
        return true;// game done
    }
    else if(y0==26 &&(x0>=10 && x0<=100))
    {
        return true;
    }
    else if(x0==100 &&(y0>=1 && y0<=26))
    {
        return true;
    }
    else if(x0==10 &&(y0>=1 && y0<=26))
    {
        return true;
    }
    return false;
}
bool checkgame_tail(loc snake[],int size)
{
    for (int i=1; i<size; i++)
    {
        if ((snake[0].x==snake[i].x)&& (snake[0].y==snake[i].y))
        {
            return true;
        }
    }
    return false;
}

bool checksnake(loc snake[],int size)
{
    bool gameover1=checkgame_tail(snake,size);
    bool gameover2=checkgame_bound(snake[0].x,snake[0].y);
    if (gameover1==true||gameover2==true)
    {
        return true;
    }
    return false;
}
void bite_snake1(loc snake[],loc snake2[],int *size,int size2)
{
    //snake 2 hit snake 1
    for (int i=0;i<*size;i++)
    {
           if (snake2[0].x==snake[i].x && snake2[0].y==snake[i].y)
           {
            for(int k=i;k<*size;k++)
            {
                gotoXY(snake[k].x,snake[k].y);
                printf(" ");
            }
            *size=i;
            break;
           }
    }
}
void bite_eachother(loc**snake,loc**snake2,int *size,int *size2) //the heads hit each other, making snake die.
{
    int len= *size;
    int len2= *size2;
    // for the case len and len2 >=2
    if(((*snake2)[0].x==(*snake)[0].x &&(*snake2)[0].y==(*snake)[0].y)||((*snake2)[0].x==(*snake)[1].x &&(*snake2)[0].y==(*snake)[1].y))
    {
        if ((*snake2)[1].y==(*snake)[1].y)
        {
        delete_presnake(*snake,*size);
        *size=0;
        }
    }
    if (len==1 || len2==1)
    {
        if ((*snake2)[0].y==(*snake)[0].y && abs((*snake2)[0].x-(*snake)[0].x )<=1)
        {
        delete_presnake(*snake,*size);
        *size=0;
        }
    }
}
//menu of the program
void print_menu(int *flag,HANDLE h)
{
    h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h,1);
    printf("\t\t WELCOME TO SNAKE GAME\n");
     printf(RESETCOLOR);
        printf(" Please choose the mode of playing\n"
        "1.Single player\n"
        "2.Double players\n"
        "3.Exit if the user do not want to play\n"
        );
    int n;
    scanf("%d",&n);
    system("cls");

    getchar();
    switch(n)
    {
    case 1: system("cls"); *flag=1; printf("Press enter to start"); getchar();system("cls"); break;
    case 2: system("cls"); *flag=2; printf("Press enter to start");getchar();system("cls");break;
    case 3: * flag=3; break;
    default: *flag=3; break;
    }
}
// update the score of single mode
void print_score(int *score,int *highscore,FILE *f)
{
   int x=0,y=0;
   gotoXY(x,y);
   printf(" ");
   printf("Current&High:%d %d",*score,*highscore);
   f=fopen("highscore.txt","r");
   fscanf(f,"%d",highscore);
   fclose(f);
}
// Gameover condition of single mode
void Gameover(int *score,int *highscore, FILE *g,FILE *f)
{
    printf("\a");
    Sleep(1500);
    system("Cls");
    g=fopen("Score.txt","a"); //saving scores to the file 
    fprintf(g,"%d ",*score);
    fclose(g);
    if (*score>*highscore) // saving the record(highest score) to the file, making it to the record in new playing.
    {
        printf(" New Highscore:%d!!!!\n\n",*score);
        Sleep(1000);
        f=fopen("highscore.txt","w");
        fprintf(f,"%d",*score);
        fclose(f);
    }
    getchar();
    system("Cls");
    printf("\n\n           Gameover");
    printf("               Score:%d\n\n",*score);
}
//update score of double mode
void print_score_double(int score1,int score2)
{
   int x=0,y=0;
   gotoXY(x,y);
   printf(" ");
printf("Current score:Player 1 %d & Player2 %d",score1,score2);
}
//gamover condition of double mode
void Gameover_double(int score1,int score2)
{
    printf("\a");
    Sleep(1000);
    system("Cls");
    if (score1>score2)
    {
        printf("Player 1:%d & Player2:%d",score1,score2);
        printf("\n");
        printf("Player 1 winner");
    }
    else if (score1==score2)
    {
        printf("Result: Draw");
    }
    else
    {
        printf("Player 1:%d & Player2:%d",score1,score2);
        printf("\n");
        printf("Player 2 winner");
    }
}
// Setting color for the text
void updatecolor(HANDLE h,int x)
{
     h = GetStdHandle(STD_OUTPUT_HANDLE);
     SetConsoleTextAttribute(h,x);
}