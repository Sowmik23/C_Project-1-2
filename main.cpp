#include<graphics.h>
#include<stdio.h>
#include<iostream>
#include<math.h>
using namespace std;
#include "My_Header.h"


double p1=0,dart1=0,q1=0,score1=100.00;
char str[80];
#define v 150.0
#define g 10.0
#define pi acos(-1)


struct HighScore
{
public:
    char name[100];
    int H_score1;
};
HighScore players[5];


int check_end=0;
int flag=0;
int arrowleft, arrowtop = 468, arrowright, arrowbottom = 505;
int countscore=0;


int point = 0;
int p=0,dart=0,q=0,score=0;

DWORD screen_width=GetSystemMetrics(SM_CXSCREEN);
DWORD screen_height=GetSystemMetrics(SM_CYSCREEN);


int main()
{
    DWORD screen_width=GetSystemMetrics(SM_CXSCREEN);
    DWORD screen_height=GetSystemMetrics(SM_CYSCREEN);
    initwindow(screen_width,screen_height,"MENU");
    interface_page();
    cleardevice();

    readimagefile("miranda.jpg",0,0,screen_width,screen_height);
    menu(width,height);
    while(1)
    {

        detect_mouseclick(mx,my);
        int option_no=get_option(mx,my,width,height);
        if(option_no<=4)
        {
            select_action(option_no,screen_width,screen_height);
            break;
        }

    }

    getch();
    closegraph();

    return 0;

}

int menu(int width,int height)
{
    width=300;
    height=125;
    POINT mouse_position;
    while(1)
    {
        GetCursorPos(&mouse_position);
        int x=mouse_position.x;
        int y=mouse_position.y;
        if((x>1000)&&(x<1300)&&(y>200)&&(y<325))
        {
            readimagefile("button2.jpg",1005,205,1305,700);
        }
        else if((x>1000)&&(x<1300)&&(y>325)&&(y<450))
        {
            readimagefile("button3.jpg",1005,205,1305,700);
        }
        else if((x>1000)&&(x<1300)&&(y>450)&&(y<575))
        {
            readimagefile("button4.jpg",1005,205,1305,700);
        }
        else if((x>1000)&&(x<1300)&&(y>575)&&(y<700))
        {
            readimagefile("button5.jpg",1005,205,1305,700);
        }
        else
        {
            readimagefile("button1.jpg",1005,205,1305,700);
        }

        if(GetAsyncKeyState(VK_LBUTTON))
        {
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            if((mx>1000)&&(mx<1300)&&(my>200)&&(my<700))
            {
                cleardevice();
                break;
            }

        }

    }
    int option_no=get_option(mx,my,width,height);
    select_action(option_no,screen_width,screen_height);

}



char nam[100];

char pname_add()
{
    int i,j=0;
    char ch;
    initwindow(1300,700,"Enter Name");
    setbkcolor(MAGENTA);
    setcolor(RED);
    setfillstyle(1,MAGENTA);
    floodfill(10,10,WHITE);

    settextstyle(1,HORIZ_DIR,6);
    outtextxy(350,300,"Enter Your Name:");

    nam[0]='_';
    nam[1]='\0';
    setcolor(BLACK);
    settextstyle(1,HORIZ_DIR,2);
    outtextxy(500,400,nam);
    while(1)
    {
        if(kbhit())
        {
            ch=getch();
            if(ch=='\r')
            {
                nam[j]='\0';
                readimagefile("miranda.jpg",0,0,screen_width,screen_height);

                width=300;
                height=125;
                menu(width,height);
                break;
            }
            else if(ch=='\b')
            {
                setbkcolor(MAGENTA);
                setcolor(MAGENTA);
                settextstyle(1,HORIZ_DIR,2);
                outtextxy(500,400,nam);

                j--;
                if(j<0)
                    j=0;
                nam[j]='_';
                nam[j+1]='\0';
            }
            else if(j<20)
            {
                nam[j]=ch;
                j++;
                nam[j]='_';
                nam[j+1]='\0';
            }
            setbkcolor(MAGENTA);
            setcolor(BLACK);
            settextstyle(1,HORIZ_DIR,2);
            outtextxy(500,400,nam);
        }

    }
    // return nam;

}



int get_option(int mx, int my,int width,int height)
{
    if((mx>1000)&&(mx<(1000+width))&&(my>200)&&(my<(200+height)))
    {
        return 1;
    }
    else if((mx>1000)&&(mx<(1000+width))&&(my>200+height)&&(my<(200+(2*height))))
    {
        return 2;
    }
    else if((mx>1000)&&(mx<(1000+width))&&(my>200+(2*height))&&(my<(200+(3*height))))
    {
        return 3;
    }
    else if((mx>1000)&&(mx<(1000+width))&&(my>200+(3*height))&&(my<(200+(4*height))))
    {
        return 4;
    }
    else
    {
        return 5;
    }

}

int detect_mouseclick(int &mx, int &my)
{
    while(1)
    {
        if(GetAsyncKeyState(VK_LBUTTON))
        {
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            break;
        }
        delay(100);
    }
    return 0;
}

int set_bg_color(int color)
{
    for(int i=0; i<2; i++)
    {
        cleardevice();
        setbkcolor(color);
    }
}


int select_action(int option_no,int screen_width,int screen_height)
{
    if(option_no==1)
    {
        Play();
    }
    else if(option_no==2)
    {
        show_high_score(H_score);
        cout<<"option 2 slected"<<endl;
    }
    else if(option_no==3)
    {
        help();
    }
    else if(option_no==4)
    {
        exit();
    }

}


int show_high_score(int &score)
{
    char name[100];
    FILE *fp;
    int i,st=200,st1=250,d;
    if((fp=fopen("high_score.txt","r"))==NULL)
    {
        cout<<"Error reading high score file "<<endl;
    }
    for(i=0; i<5; i++)
    {
        fscanf(fp," %s",players[i].name);
        fscanf(fp,"%d",&players[i].H_score1);
    }

    initwindow(screen_width,screen_height,"High Score");
    char str[100]= {'\0'};
    for(i=0; i<5; i++)
    {

        sprintf(str,"Scorar's Name:     %s      --->  Score : %d ",players[i].name,players[i].H_score1);
        settextstyle(1,0,3);
        outtextxy(50,st,str);

        d=80;
        st=st+d;

    }
    cout<<str<<endl;

    readimagefile("back.jpg",1150,580,1250,650);

    while(1)
    {
        detect_mouseclick(mx,my);

        if((mx>1150&&mx<1250)&&(my>580&&my<650))
        {
            readimagefile("miranda.jpg",0,0,screen_width,screen_height);
            menu(width,height);
            break;
        }
    }

    fclose(fp);
    getch();
}


int update_h_score()
{
    FILE *fp;
    int i,st=200,st1=250,d;
    if((fp=fopen("high_score.txt","r"))==NULL)
    {
        cout<<"Error reading high score file "<<endl;
    }


    for(i=0; i<5; i++)
    {

        fscanf(fp," %s",players[i].name);
        fscanf(fp,"%d",&players[i].H_score1);
    }

    fclose(fp);

    if(players[4].H_score1<score1)
    {

        scanf("%s",players[4].name);
        players[4].H_score1=score1;

        //players[4].name=nam;
        //pname_add();
        //strcpy(players[4].name,nam);

        FILE *fp;
        if((fp=fopen("high_score.txt","w"))==NULL)
        {
            cout<<"Error updating high score file "<<endl;
        }
        int i;
        for(int i=0; i<4; i++)
        {
            for(int j=0; j<=4; j++)
            {
                if(players[j].H_score1<players[j+1].H_score1)
                {
                    HighScore temp;
                    temp=players[j];
                    players[j]=players[j+1];
                    players[j+1]=temp;
                }
            }
        }
        for(i=0; i<5; i++)
        {
            fprintf(fp,"%s ",players[i].name);
            fprintf(fp,"%d\n",players[i].H_score1);
        }
        fclose(fp);
        for(int i=0; i<5; i++)
        {
            cout<<players[i].name<<' '<<players[i].H_score1<<endl;
        }
    }
}



int exit()
{
    cleardevice();
    setcolor(LIGHTBLUE);
    rectangle(83,334,1183,434);
    setfillstyle(10,LIGHTBLUE);
    floodfill(1120,100,LIGHTBLUE);
    setcolor(WHITE);
    settextstyle(1,0,5);
    outtextxy(120,370,"ARE YOU SURE TO EXIT NOW?");
    readimagefile("yesbutton.jpg",83,434,633,509);
    readimagefile("nobutton.jpg",633,434,1183,509);

    while(1)
    {
        detect_mouseclick(mx,my);

        if((mx>83&&mx<633) && (my>434&&my<509))
        {
            printf("1");
            initwindow(screen_width,screen_height);
            setcolor(LIGHTMAGENTA);
            rectangle(100,300,1260,468);
            setfillstyle(1,LIGHTMAGENTA);
            floodfill(200,400,LIGHTMAGENTA);
            readimagefile("thanks.jpg",0,0,screen_width,screen_height);
            delay(1000);
            closegraph();

        }
        else if((mx>633&&mx<1183)&&(my>434&&my<509))
        {
            readimagefile("miranda.jpg",0,0,screen_width,screen_height);
            check_end=0;
            flag=0;
            arrowleft, arrowtop = 468, arrowright, arrowbottom = 505;
            countscore=0;
            point = 0;
            p=0,dart=0,q=0,score=0;
            score=0;
            menu(width,height);
            break;
        }

    }
    return 0;
}

int help()
{
    readimagefile("helpimg.jpg",0,0,1366,768);
    readimagefile("back.jpg",1150,580,1250,650);
    setcolor(WHITE);
    settextstyle(4,0,4);
    outtextxy(10,120,"We are waiting to help you.");
    settextstyle(3,0,3);
    outtextxy(10,180,"1.Your target is to shoot the dartboard.");
    outtextxy(15,210,"If you click space bar arrow will depart.");
    outtextxy(10,240,"2.For shooting dartboard you get at most 10 arrows");
    outtextxy(10,270,"3.If you can shoot in the center of the dartboard,you will get ");
    outtextxy(15,300,"an extra arrow as bonus for again shoot.");
    outtextxy(10,330,"4.In the first level if you scored a minimum score you can go to the next round.");
    outtextxy(10,360,"5.After completing three level properly you will win the game.");
    while(1)
    {
        detect_mouseclick(mx,my);
        if((mx>1150&&mx<1250)&&(my>580&&my<650))
        {
            readimagefile("miranda.jpg",0,0,screen_width,screen_height);
            menu(width,height);
            break;
        }
    }
}

int interface_page()
{
    int i;
    readimagefile("interface.jpg",0,0,screen_width,screen_height);
    rectangle(150,350,350,380);
    int j=0,k=150;
    for(i=0; i<20; i++)
    {
        delay(500);
        j=j+10;
        setcolor(BLUE);
        rectangle(150,350,150+j,380);
        setfillstyle(1,BLUE);
        floodfill(151+(i*10),351,BLUE);
    }
}

int Play()
{
    int x=0,page=0,s=0;
    char str[80];
    check_end=0;
    flag=0;
    arrowleft, arrowtop = 468, arrowright, arrowbottom = 505;
    countscore=0;
    point = 0;
    p=0,dart=0,q=0,score=0;
    score=0;
    while(1)
    {
        int mx,my;
        setactivepage(page);
        setvisualpage(1-page);
        cleardevice();
        int color= YELLOW;
        setcolor(color);
        readimagefile("gg.jpg",0,0,GetSystemMetrics(SM_CXSCREEN),GetSystemMetrics(SM_CYSCREEN));//background
        readimagefile("csedu.jpg",900,400,1050,600);//man
        outtextxy(550,30,"Press 'Esc' to Exit");
        if((GetAsyncKeyState(VK_SPACE)) || (GetAsyncKeyState(253)))
        {
            p=1;
            x=0;
            s=1;
        }
        draw_arrow_box(s);

        if(flag==1)
        {
            p=0;
            flag=0;
        }

        if(p==1)
        {
            readimagefile("csedu2.jpg",900,400,1050,600);//man
            shoot(x);
        }
        if(q==0)dartboarddown(dart);
        if(q==1)dartboardup(dart);
        if((arrowleft<=75)&&(arrowleft>=20))
        {
            SCORE(arrowleft,dart);
            arrowleft=1500;
            arrowright=1600;
        }
        if(check_end==1)
        {
            cleardevice();
            show_total_score();
        }
        setcolor(color);
        sprintf(str,"Total Score: %d",score);
        outtextxy(230,40,str);

        if(GetAsyncKeyState(27))
        {
            exit(1);
            // menu(width,height);
        }

        page=1-page;

    }
    getch();
    closegraph();
    return 0;
}

int shoot(int &x)
{
    x-=6;
    int color= YELLOW;
    setcolor(color);
    line(800+x, 486, 900+x, 486);//arrow
    line(800+x, 487, 900+x, 487);//arrow
    line(800+x,487,808+x,495);//down pin of arrow
    line(800+x,486,808+x,478);//up pin of arrow
    line(801+x,486,808+x,479);
    line(801+x,487,808+x,494);
    arrowleft = 800+x;
    arrowright = 900+x;
    if(x<=-780)
    {
        x=0;
        p=0;
    }
}

int dartboarddown(int &dart)
{
    dart+=3;
    settextstyle(9,HORIZ_DIR,1);
    setfillstyle(1,CYAN);
    bar(20,8+dart,27,147+dart);
    setfillstyle(1,7);
    bar(28,19+dart,35,136+dart);
    setfillstyle(1,BROWN);
    bar(36,30+dart,43,125+dart);
    setfillstyle(1,14);
    bar(44,41+dart,51,114+dart);
    setfillstyle(1,GREEN);
    bar(52,52+dart,59,103+dart);
    setfillstyle(1,MAGENTA);
    bar(60,63+dart,67,92+dart);
    setfillstyle(1,RED);
    bar(68,73+dart,75,82+dart);
    if(dart>560) q=1;
    else q=0;

}

int dartboardup(int &dart)
{
    if(dart<5) q=0;
    else q=1;
    dart-=3;
    setfillstyle(1,CYAN);
    bar(20,8+dart,27,147+dart);
    setfillstyle(1,7);
    bar(28,19+dart,35,136+dart);
    setfillstyle(1,BROWN);
    bar(36,30+dart,43,125+dart);
    setfillstyle(1,14);
    bar(44,41+dart,51,114+dart);
    setfillstyle(1,GREEN);
    bar(52,52+dart,59,103+dart);
    setfillstyle(1,MAGENTA);
    bar(60,63+dart,67,92+dart);
    setfillstyle(1,RED);
    bar(68,73+dart,75,82+dart);
}

int SCORE(int &arrowleft, int dart)
{
    settextstyle(9,HORIZ_DIR,1);
    int color= YELLOW;
    setcolor(color);
    if((arrowleft>=20)&&(arrowleft<=27))
    {
        int x=dart+8;
        if((x>=346)&&(x<=486))
        {
            flag=1;
            score=score+20;
            p=0;
            delay(1000);
            arrowleft=1500;
            arrowright=1600;
        }
        outtextxy(500,80,"Points: 20");
        return 0;
    }
    else if((arrowleft>=28)&&(arrowleft<=35))
    {
        int x=dart+19;
        if((x>=369)&&(x<=486))
        {
            flag=1;

            score=score+30;
            p=0;
            delay(1000);
            arrowleft=1500;
            arrowright=1600;
        }
        outtextxy(500,80,"Points: 30");
        return 0;
    }
    else if((arrowleft>=36)&&(arrowleft<=43))
    {
        int x=dart+30;
        if((x>=391)&&(x<=486))
        {
            flag=1;
            score=score+40;
            p=0;
            delay(1000);
            arrowleft=1500;
            arrowright=1600;
        }
        outtextxy(500,80,"Points: 40");
        return 0;
    }
    else if((arrowleft>=44)&&(arrowleft<=51))
    {
        int x=dart+41;
        if((x>=413)&&(x<=486))
        {
            flag=1;
            score=score+50;
            p=0;
            delay(1000);
            arrowleft=1500;
            arrowright=1600;
        }
        outtextxy(500,80,"Points: 50");
        return 0;
    }
    else if((arrowleft>=52)&&(arrowleft<=59))
    {
        int x=dart+52;
        if((x>=435)&&(x<=486))
        {
            flag=1;
            score=score+60;
            p=0;
            delay(1000);
            arrowleft=1500;
            arrowright=1600;
        }
        outtextxy(500,80,"Points: 60");
        return 0;
    }
    else if((arrowleft>=60)&&(arrowleft<=67))
    {
        int x=dart+63;
        if((x>=457)&&(x<=486))
        {
            flag=1;
            score=score+80;
            p=0;
            delay(1000);
            arrowleft=1500;
            arrowright=1600;
        }
        outtextxy(500,80,"Points: 80");
        return 0;
    }
    else if((arrowleft>=68)&&(arrowleft<=75))
    {
        int x=dart+73;
        if((x>=477)&&(x<=486))
        {
            flag=1;
            score=score+100;
            p=0;
            delay(1000);
            arrowleft=1500;
            arrowright=1600;
        }
        outtextxy(500,80,"Points: 100");
        return 0;
    }
    settextstyle(9,HORIZ_DIR,1);
    outtextxy(500,80,"Total Score:");
}

int draw_arrow_box(int &s)
{
    bar(1100,40,1270,260);
    static double i=10.0;
    for(int j=0; j<i; j++)
    {
        line(1120,60+(j*20),1250,60+(j*20));
        line(1120,60+(j*20),1127,65+(j*20));
        line(1120,60+(j*20),1127,55+(j*20));
    }
    if(s==1)
    {
        i-=0.25;
        s=0;
    }
    if(i<0.0)
    {
        check_end=1;
    }
}

int show_total_score()
{
    initwindow(1366,768);
    set_bg_color(BLACK);
    int i;
    if(score>=200)
    {
        for(i=1; i<=4; i++)
        {
            readimagefile("useinscore3.jpg",0,0,900,600);
            setcolor(WHITE);
            settextstyle(1,HORIZ_DIR,3);
            outtextxy(800,40,"Hurrah!You have got ");
            outtextxy(800,80," the minimun score.");
            outtextxy(850,160,"Wait sometime for  ");
            outtextxy(850,200," the next level.");

            delay(500);

            readimagefile("useinscore1.jpg",0,0,900,600);
            outtextxy(800,40,"Hurrah!You have got ");
            outtextxy(800,80," the minimun score.");
            outtextxy(850,160,"Wait sometime for ");
            outtextxy(850,200," the next level.");
            delay(500);
        }
        cleardevice();
        closegraph();


        level02(); // Level - 02 will Start from here.//
    }
    else if(score<500)
    {
        for(i=1; i<=4; i++)
        {
            readimagefile("useinscore2.jpg",0,0,900,600);
            setcolor(WHITE);
            settextstyle(1,HORIZ_DIR,3);
            outtextxy(800,40,"Sorry!!! you haven't ");
            outtextxy(850,80," scored the minimum score.");
            outtextxy(950,120,"Wait for option.");
            delay(500);
            readimagefile("useinscore.jpg",0,0,900,600);
            outtextxy(800,40,"Sorry!!! you haven't ");
            outtextxy(850,80," scored the minimum score.");
            outtextxy(950,120,"Wait for option.");
            delay(500);
        }
        readimagefile("gameover.jpg",0,0,screen_width,screen_height);
        readimagefile("playagainimg.jpg",1100,600,1180,650);
        readimagefile("exit.jpg",1180,600,1260,650);
        detect_mouseclick(mx,my);
        if((mx>1100&&mx<1180)&&(my>600&&my<650))
        {
            check_end=0;
            flag=0;
            arrowleft, arrowtop = 468, arrowright, arrowbottom = 505;
            countscore=0;
            point = 0;
            p=0,dart=0,q=0,score=0;
            score=0;
            menu(width,height);
        }
        else if((mx>1180&&mx<1260)&&(my>600&&my<650))
        {
            exit();
        }
    }

}

/* ************###################***************Level -02 Start******************#####################*****************/

int level02()
{
    double T,t,m,angle,tempt,x,y,x1,y1,p,B1,j;
    int win1,i,page=0;
    int  arrow_cnt=10;
    char ch[30];

    score1=score;
    win1=initwindow(getmaxwidth(),getmaxheight());
    setcurrentwindow(win1);
    // readimagefile("gg.jpg",0,0,getmaxwidth(),getmaxheight());
    while(1)
    {
        //readimagefile("gg.jpg",0,0,getmaxwidth(),getmaxheight());
        if(arrow_cnt==0)
        {
            cleardevice();
            gameover();
        }
        angle=0.0;
        settextstyle(1,HORIZ_DIR,3);
        sprintf(ch,"You have : %d  arrows to shoot",arrow_cnt);
        outtextxy(500,50,ch);
        sprintf(str,"Total Score: %.2lf",score1);
        outtextxy(130,50,str);
        arch();

        if(arrow_cnt<10 && arrow_cnt>0)
        {
            settextstyle(1,HORIZ_DIR,5);
            outtextxy(300,140,"Shoot Again!!!");
        }

        while(1)
        {
            setactivepage(page);
            // readimagefile("gg.jpg",0,0,getmaxwidth(),getmaxheight());
            dartboard();
            if(GetAsyncKeyState(VK_UP))
            {
                angle+=(1*pi/180);
                cleardevice();
                dartboard();
                arch();

                settextstyle(1,HORIZ_DIR,3);
                sprintf(ch,"You have : %d  arrows to shoot",arrow_cnt);
                outtextxy(500,50,ch);
                sprintf(str,"Total Score: %.2lf",score1);
                outtextxy(130,50,str);
            }
            else if(GetAsyncKeyState(VK_DOWN))
            {
                angle-=(1*pi/180);
                cleardevice();
                dartboard();
                arch();
                settextstyle(1,HORIZ_DIR,3);
                sprintf(ch,"You have : %d  arrows to shoot",arrow_cnt);
                outtextxy(500,50,ch);

                sprintf(str,"Total Score: %.2lf",score1);
                outtextxy(130,50,str);
            }
            if(GetAsyncKeyState(VK_SPACE))
            {
                p=1;
                arrow_cnt--;
                break;
            }
            printf("%d\n",arrow_cnt);
            line(129,getmaxy()-110,90*sin(angle+pi/2)+129,90*cos(angle+pi/2)+getmaxy()-110);
        }
        if(p==1)
        {
            //angle=pi/4;
            printf("%.6lf\n",angle);
            t=(v*sin(angle)/g);
            T=2*t;
            for( i=1,j=2.0; i<100; i++,j+=2.0)
            {
                // readimagefile("gg.jpg",0,0,getmaxwidth(),getmaxheight());
                dartBoardL2(j);
                arch();

                settextstyle(1,HORIZ_DIR,3);
                sprintf(ch,"You have : %d  arrows to shoot",arrow_cnt);
                outtextxy(500,50,ch);

                sprintf(str,"Total Score: %.2lf",score1);
                outtextxy(130,50,str);

                tempt=(T*i)/200;
                x=v*cos(angle)*tempt+129;
                y=v*sin(angle)*tempt-.5*g*tempt*tempt+110;
                x1=90*cos(angle-(angle/100)*i)+x;
                y1=90*sin(angle-(angle/100)*i)+y;

                B1=getmaxy()-y1;
                line(x,getmaxy()-y,x1,B1);
                delay(30);
                cleardevice();
            }

            for( i=1,j=j; i<100; i++,j+=2.0)
            {
                // readimagefile("gg.jpg",0,0,getmaxwidth(),getmaxheight());
                dartBoardL2(j);
                arch();
                settextstyle(1,HORIZ_DIR,3);
                sprintf(ch,"You have : %d  arrows to shoot",arrow_cnt);
                outtextxy(500,50,ch);

                sprintf(str,"Total Score: %.2lf",score1);
                outtextxy(130,50,str);

                tempt=(T*(i+100))/200;
                x=v*cos(angle)*tempt+129;
                y=v*sin(angle)*tempt-.5*g*tempt*tempt+110;
                // printf("%.6lf\n",pi-(angle/500)*i);
                x1=90*cos(-(angle/100)*i)+x;
                y1=90*sin(-(angle/100)*i)+y;

                B1=getmaxy()-y1;
                line(x,getmaxy()-y,x1,B1);
                if((B1>=j+8 && B1 <=j+147) && (x1>=1302 && x1<=1350))
                {
                    Score((double)j,x1,B1);
                    settextstyle(1,HORIZ_DIR,3);
                    sprintf(ch,"You have : %d  arrows to shoot",arrow_cnt);
                    outtextxy(500,50,ch);

                    sprintf(str,"Total Score: %.2lf",score1);
                    outtextxy(130,50,str);
                    break;
                }
                delay(30);
                cleardevice();
            }
        }

    }
    getch();
    closegraph();
}

void dartboard()
{
    double dart=0;
    setfillstyle(1,CYAN);
    bar(1350,8+dart,1357,147+dart);
    setfillstyle(1,7);
    bar(1342,19+dart,1349,136+dart);
    setfillstyle(1,BROWN);
    bar(1334,30+dart,1341,125+dart);
    setfillstyle(1,14);
    bar(1326,41+dart,1333,114+dart);
    setfillstyle(1,GREEN);
    bar(1318,52+dart,1325,103+dart);
    setfillstyle(1,MAGENTA);
    bar(1310,63+dart,1317,92+dart);
    setfillstyle(1,RED);
    bar(1302,73+dart,1309,82+dart);

}

double dartBoardL2(double dart)
{
    if(dart>560) q1=1;
    else q1=0;

    settextstyle(9,HORIZ_DIR,1);
    setfillstyle(1,CYAN);
    bar(1350,8+dart,1357,147+dart);
    setfillstyle(1,7);
    bar(1342,19+dart,1349,136+dart);
    setfillstyle(1,BROWN);
    bar(1334,30+dart,1341,125+dart);
    setfillstyle(1,14);
    bar(1326,41+dart,1333,114+dart);
    setfillstyle(1,GREEN);
    bar(1318,52+dart,1325,103+dart);
    setfillstyle(1,MAGENTA);
    bar(1310,63+dart,1317,92+dart);
    setfillstyle(1,RED);
    bar(1302,73+dart,1309,82+dart);
}

double Score(double dart1,double x1,double B1)
{
    if((B1>=dart1+71)&&(B1<=dart1+82))
    {
        printf("level 0001\n");
        printf("points : 100\n");
        score1=score1+100.0;

        outtextxy(200,100,"Points: 100");

        delay(100);
    }
    else  if(((B1>=dart1+63)&&(B1<=dart1+72)) || ((B1>=dart1+83)&&(B1<=dart1+92)))
    {
        printf("level 0002\n");
        printf("points : 80\n");
        score1=score1+80.0;

        outtextxy(200,100,"Points: 80");

        delay(100);
    }
    else  if(((B1>=dart1+52)&&(B1<=dart1+62)) || ((B1>=dart1+93)&&(B1<=dart1+103)))
    {
        printf("level 0003\n");
        printf("points : 70\n");
        score1=score1+70.0;
        outtextxy(200,100,"Points: 70");

        delay(100);
    }
    else if(((B1>=dart1+41)&&(B1<=dart1+51)) || ((B1>=dart1+104)&&(B1<=dart1+114)))
    {
        printf("level 0004\n");
        printf("points : 60\n");
        score1=score1+80.0;
        outtextxy(200,100,"Points: 60");

        delay(100);
    }
    else  if(((B1>=dart1+30)&&(B1<=dart1+40)) || ((B1>=dart1+115)&&(B1<=dart1+125)))
    {
        printf("level 0005\n");
        printf("points : 50\n");
        score1=score1+50.0;
        outtextxy(200,100,"Points: 50");

        delay(100);
    }
    else if(((B1>=dart1+19)&&(B1<=dart1+29)) || ((B1>=dart1+126)&&(B1<=dart1+136)))
    {
        printf("level 0006\n");
        printf("points : 40\n");
        score1=score1+40.0;
        outtextxy(200,100,"Points: 40");

        delay(100);
    }
    else  if(((B1>=dart1+ 8)&&(B1<=dart1+18)) || ((B1>=dart1+137)&&(B1<=dart1+147)))
    {
        printf("level 0007\n");
        printf("points : 30\n");
        score1=score1+30.0;

        outtextxy(200,100,"Points: 30");

        delay(100);
    }

}


void arch()
{
    int j,k;
    setcolor(BROWN);

    for(j=0; j<9; j++)
    {
        arc(130,590,0,135,30+j);
        arc(180,630,-45,105,30+j);
    }
    for(j=7; j>=0; j--)
    {
        line(205-j,653,195,690+j);
    }
    for(j=7; j>0; j--)
    {
        line(105,570-j,55,570);
    }

    setcolor(WHITE);
    line(62,569,197,692); //Suta

    setfillstyle(1,BROWN);
    setcolor(BROWN);
    line(167,590,170,593);//linkage of arc
    line(166,590,169,594);
    line(165,590,169,595);
    line(164,590,169,596);
    line(163,590,170,597);
    line(162,590,170,598);
    line(161,590,170,599);
    line(160,590,170,600);

    setfillstyle(1,BROWN);

    setcolor(BROWN);
    arc(55,565,140,310,5);
    arc(200,698,120,320,5);

}


int gameover()
{
    int i;
    if(score1>=500.00)
    {

        for(i=1; i<=4; i++)
        {
            readimagefile("useinscore1.jpg",0,0,900,600);

            setcolor(WHITE);
            settextstyle(1,HORIZ_DIR,3);
            outtextxy(800,40,"Hurrah!You Win The Game!!!");

            sprintf(str,"Your Total Score is : %.2lf",score1);
            outtextxy(780,80,str);
            delay(500);

            readimagefile("useinscore3.jpg",0,0,900,600);

            outtextxy(800,40,"Hurrah!You Win The Game!!!");

            sprintf(str,"Your Total Score is : %.2lf",score1);
            outtextxy(780,80,str);
            delay(500);
        }

        update_h_score();
        pname_add();

        cleardevice();
        closegraph();
    }
    else
    {
        for(i=1; i<=4; i++)
        {
            readimagefile("useinscore2.jpg",0,0,900,600);
            setcolor(WHITE);
            settextstyle(1,HORIZ_DIR,3);
            outtextxy(800,40,"Sorry!!! you haven't ");
            outtextxy(850,80," scored the minimum score.");
            outtextxy(950,120,"You loss the Game!");
            delay(1000);
            readimagefile("useinscore.jpg",0,0,900,600);

            outtextxy(800,40,"Sorry!!! you haven't ");
            outtextxy(850,80," scored the minimum score.");
            outtextxy(950,120,"You loss the Game!");
            delay(1000);

        }
        readimagefile("gameover.jpg",0,0,screen_width,screen_height);
        readimagefile("playagainimg.jpg",1100,600,1180,650);
        readimagefile("exit.jpg",1180,600,1260,650);
        detect_mouseclick(mx,my);
        if((mx>1100&&mx<1180)&&(my>600&&my<650))
        {
            check_end=0;
            flag=0;
            arrowleft, arrowtop = 468, arrowright, arrowbottom = 505;
            countscore=0;
            point = 0;
            p=0,dart=0,q=0,score=0;
            score=0;


            menu(width,height);

        }
        else if((mx>1180&&mx<1260)&&(my>600&&my<650))
        {
            exit();
        }
    }

}

