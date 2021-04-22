/*Start of project------------------------------------------------------------------------------*/
/*Header Files---------------------------------------------------------------------------------*/
#include<iostream.h>
#include<fstream.h>
#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>

/*Predefining global variables-----------------------------------------------------------------*/
char *play[] = {"qwe","rty","uio"};				//just initialised the gameplay
char d;								//for input of row/column
const int x[] = {372,439,506}; 				// x coordinates of the texts
const int y[] = {122,189,256}; 				//y coordinates of the texts

/*Defining class player------------------------------------------------------------------------*/
class player
{
	char id ;               //x or o
	int point;
	char name[20] ;	//20 characters
	char warcry[30];
	player* pass;

    public:
	player()
	{
		point = 0 ;
		id = ' ';
        		strcpy(name,"                    ");				//20 spaces
		strcpy(warcry, "                              ");			//30 spaces
		pass = NULL;
	}
void getdata(player* a,char b)
	{
		pass = a;
        		id = b;
	}

void getdata()
	{
		cout<<"Enter a name for "<<id<<"..(max - 20 characters):\n";
		gets(name);
		strcpy(warcry,name);
		strcat(warcry, " WINS !");
	}
	void win() {point++;}					//increases point
	char identify() {return id;}					//returns X or O
	int points() {return point;}					//returns individual score
	void win_warcry()						//displays “obj wins !”, if won
	{
		settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
		outtextxy(350,400, warcry);
	}
	char* names() {return name ; }
	player* playing();
};
player* player:: playing()	             //defines the actions of the player object while playing
	{
		start:
		int j=-1,k=-1;
		cout<<"\n"<<name<<"\'s chance\n";
		while(j==-1)
		{
		  d = getch();					//getch() used to hide numeric inputs
		  switch(d)
		  {
			  case '1': j=0;break;
			  case '2': j=1;break;
			  case '3': j=2;break;
			  default : cout<<"\nEnter the row again";
		  }
		}
		while(k==-1)
		{
		  d = getch();
		  switch(d)
		  {
			  case '1': k=0;break;
			  case '2': k=1;break;
			  case '3': k=2;break;
			  default : cout<<"\nEnter the column again";
		  }
		}
		if(play[k][j]=='X'|| play[k][j]=='O')			//prevents overwriting
			{goto start;}
		else
		{
			outtextxy(x[k],y[j],(char*)&id);
			play[k][j] = id;
		}
		  points();
		  cout<<"\nPress any key\n";
		  getch();
		  return pass; 		//passes it to the other player
}
/*Declaring object pointers--------------------------------------------------------------------*/
player* player_1 = new player;
player* player_2 = new player;
player* dummy;

/*Declaring the functions----------------------------------------------------------------------*/
int points();		//awards points and declares win/draw (returns 1 if no win/draw)
int check_not_full();		//checks if play[3][3] is fully used up (returns 0 if so)
void gameplay();	//the actual gameplay

/*Main function------------ -------------------------------------------------------------------*/
void main()
{
	  clrscr();
	  int gd = DETECT, gm;
        	  player_1->getdata(player_2,'X');
	  player_1->getdata();
	  clrscr();
       	 player_2->getdata(player_1,'O');
	 player_2->getdata();
	 clrscr();
     	 initgraph(&gd, &gm, "C:\\turboc3\\bgi");
     	 settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 2);
	  setcolor(EGA_WHITE);
	  rectangle(350,100,551,301);
	  line(350,167,550,167);  //demarcates 1st row
	  line(350,234,550,234);  //demarcates 2nd and 3rd rows
	  line(417,100,417,300);  // demarcates 1st column
	  line(484,100,484,300);  // demarcates 2nd and 3rd row 
	  outtextxy(335,y[0],"1"); 
	  outtextxy(335,y[1],"2"); 
	  outtextxy(335,y[2],"3"); 
	  outtextxy(x[0],75,"1"); 
	  outtextxy(x[1],75,"2");
	  outtextxy(x[2],75,"3");
	  outtextxy(280,y[1],"Row"); 
	  outtextxy(415,55,"Column");
      line(220,0,220,700);	//to separate board from working column
	  settextstyle(SANS_SERIF_FONT, HORIZ_DIR, 3);
	  setcolor(EGA_YELLOW);
	  outtextxy(378,20, "Tic Tac Toe");		//heading
	  cout<<"Enter the row number\nand then the column number\n";
	  gameplay();
	  outtextxy(350,425,"Press any key to continue");
	  getch();
	  cleardevice();
	  closegraph();
	  clrscr();
	  int ch;
	  repeat:
	  cout<<"Press any key to continue";
	  getch();  
 clrscr();

/*Menu driven operation after game----------------------------------------------------------*/
	  cout<<"Menu\n\n";		
	  cout<<"1.Save this game\'s scores.\n2.Read previous score history.\n3.Clear score history.\n4.About\n5.Exit. ";
	  cout<<"\n\nEnter your option: ";
	  cin>>ch;
	  switch(ch)
	  {
		  case 1:		clrscr();
		  			ofstream fout1,fout2;
		  		  	fout1.open("points1",ios::app|ios::binary);
					fout2.open("points2",ios::app|ios::binary);
					fout1<<"Player 1 - ("<<player_1->names()<< ") : \n";
					fout2<<player_1->points();
					fout1<<"Player 2 - ("<<player_2->names()<< ") : \n";
					fout2<<player_2->points();
                          			fout1.close();
									fout2.close();
					break;
		case 2:			clrscr();
					ifstream fin1,fin2;
					char b,c;
					fin1.open("points1",ios::ate|ios::binary);
					fin2.open("points2",ios::ate|ios::binary);
					fin1.seekg(0);
					fin2.seekg(0);
					while(fin1)
					{
						fin1.get(b);
						if(b=='\n')
						{
							fin2.get(c);
							cout.put(c);
						}
						cout.put(b);
					}
					fin1.close();
					fin2.close();

					break;
           		 case 3:     		clrscr();
								fout1.open("points1", ios::trunc);
								fout2.open("points2", ios::trunc);
            					fout1.close();
								fout2.close();
                            			break;
		case 4:			clrscr();
cout<<"All Rights Reserved...\nThe authors of this   program (hereby referred to as Varky and Maddy) will   \n1. have the sole right to alter this program";

cout<<"\n2. thank all our brothers in helping us to get our program in perfect condition.";
					break;
		case 5:     		delete player_1;
    					delete player_2;
	  				exit(1);
		default:    		break;
	  }
	  goto repeat;
}

/*End of Menu driven operation --------------------------------------------------------------*/
/*Function Definitions-------------------------------------------------------------------------*/
int points()							
{
	if(play[0][0]==play[1][1] && play[1][1]==play[2][2])         //diagonal 1 checking
	{									//(primary diagonal)
		if(play[0][0]=='X')
			player_1->win();
		else
			player_2->win();
	}
	else if(play[2][0]==play[1][1] && play[1][1]==play[0][2])	//diagonal 2 checking
	{
		if(play[2][0]=='X')
			player_1->win();
		else
			player_2->win();
	}
	for(int i=0; i<3; i++)
	{
			if(play[0][i]==play[1][i] && play[1][i]==play[2][i])	       //row check
			{
				if(play[1][i]=='X')
					player_1->win();
				else
					player_2->win();
			}

			else if(play[i][0]==play[i][1] && play[i][1]==play[i][2])   //column check
			{
				if(play[i][0]=='X')
					player_1->win();
				else
					player_2->win();
			}
	}

	if(player_1->points()!=0)
		{player_1->win_warcry() ; return 1;}
	else if(player_2->points()!=0)
		{player_2->win_warcry() ; return 1;}
	else if(player_1->points()==player_2->points() && (check_not_full()==0))
		{outtextxy(350,400,"Its a draw") ; return 1 ;}
	else
		return 0;
}
int check_not_full()         //checks whether the gameboard is full (returns false if full)
{
	int a = 0 ;
	for(int i=0 ; i<3 ; i++)
	{
		for(int j=0 ; j<3 ; j++)
		{
			if(play[i][j]!='X' && play[i][j]!='O');
				{a=1 ; break ; }
		}
	}
	return a ; 
}
void gameplay()		//the function dealing with the actual gameplay
{
	dummy = player_1 ; 
	while(points()==0)
	{
		dummy = dummy->playing() ; 
	}
}
/*End of project-------------------------------------------------------------------------------*/