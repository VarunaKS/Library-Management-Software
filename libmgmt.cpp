#include<fstream.h>
#include<conio.h>
#include<process.h>
#include<stdio.h>
#include<string.h>
#include<iomanip.h>
#include<graphics.h>
#include<dos.h>


class book{
int bkno;
char title[30],author[30];
char status[30];
public:
	void readb()
	{
	cout<<"Title"<<endl;
	gets(title);
	cout<<"Author"<<endl;
	gets(author);
	cout<<"Book Number"<<endl;
	cin>>bkno;
	stat();
	}
void dispb()
{
cout<<"\n"<<bkno<<"\t";
cout<<"Title:  "<<title<<endl;
cout<<"\tAuthor:  "<<author<<setw(29)<<status<<endl;
}
	void stat()
	{
	strcpy(status,"Available");
	}
void changestat()
{
strcpy(status,"Issued");
}
	int getbookno()
	{
	return bkno;
	}
char*gettitle()
{
return title;
}
	char*getauthor()
	{
	return author;
	}
char*getstatus()
{
return status;
}
};
fstream f,g;
book b;
char ch='y ';
int op,found=1,count=0,bno;
char bname[30],aname[30];
/*essential func*/
	void showall()
	{
	f.open("library.txt",ios::in|ios::binary);
	while(f.read((char*)&b,sizeof(b)))
	{
	b.dispb();
	}
	f.close();
	}
void search()
{
 cout<<"1.Search by title"<<endl;
 cout<<"2.Search by author"<<endl;
 cout<<"3.Search available books"<<endl;
 cout<<"Enter choice"<<endl;
 cin>>op;
 f.open("library.txt",ios::in|ios::binary);
 f.seekg(0);
 if(op==1)
 {
 cout<<"Enter title to be searched"<<endl;
 gets(bname);

 while(f.read((char*)&b,sizeof(b)))
 {
 if(strcmp(bname,b.gettitle())==0)
 {
 found=0;
 cout<<endl;
 b.dispb();
 }}
 if(found)
 cout<<"No match found"<<endl;
 }
 else if(op==2)
 {
 cout<<"Enter author to be searched"<<endl;
 gets(aname);
 while(f.read((char*)&b,sizeof(b)))
 {
 if(strcmp(aname,b.getauthor())==0)
 {
 found=0;
 cout<<endl;
 b.dispb();
 }
 }
 if(found)
 cout<<"No match found"<<endl;
 }
 else if(op==3)
 {
 cout<<"List of available books in the library";

  while(f.read((char*)&b,sizeof(b)))
 {
 if(strcmp(b.getstatus(),"Available")==0)
 {
 found=0;
 cout<<endl;
 b.dispb();
 }
 }
 if(found)
 cout<<"No match found"<<endl;
 }
 f.close();
 }


	void issue()
	{
	f.open("library.txt",ios::in|ios::out|ios::binary);
	cout<<"Enter book no to confirm"<<endl;
	cin>>bno;
	while(!f.eof())
	{
	int pos=f.tellg();
	f.read((char*)&b,sizeof(b));
	if(bno==b.getbookno()&&strcmp(b.getstatus(),"Available")==0)
	{
	b.changestat();
	cout<<"Book is successfully issued"<<endl;	
	b.dispb();
	f.seekg(pos);
	f.write((char*)&b,sizeof(b));
	break;
	}
	else if(bno==b.getbookno()&&strcmp(b.getstatus(),"Issued")==0)
	{
	f.read((char*)&b,sizeof(b));
	cout<<"This book is already issued"<<endl;
	break;
	}
	}//while
	f.close();
	}

void returnbook()
{
cout<<"\nEnter book number to be returned"<<endl;
cin>>bno;
f.open("library.txt",ios::in|ios::out|ios::binary);
while(!f.eof())
{
 int pos=f.tellg();
 f.read((char*)&b,sizeof(b));
 if(bno==b.getbookno())
 {
 b.stat();
 cout<<"Book is successfully returned"<<endl;
 b.dispb();
 f.seekg(pos);
 f.write((char*)&b,sizeof(b));
 break;
 }
 }
 f.close();
 }

	void avail()
	{
	cout<<"1.Available books"<<endl;
	cout<<"2.Issued books"<<endl;
	cout<<"3.Total books"<<endl;
	cout<<"Enter your choice"<<endl;
	cin>>op;
	f.open("library.txt",ios::in|ios::out|ios::binary);
	if(op==1)
	{
	count=0;
	while(f.read((char*)&b,sizeof(b)))	
	{
	if(strcmp(b.getstatus(),"Available")==0)
	count++;
	}
	cout<<"Available books in the library: "<<count<<endl;
	}//if
	else if(op==2)
	{
	count=0;
	while(f.read((char*)&b,sizeof(b)))
	{
	if(strcmp(b.getstatus(),"Issued")==0)
	count++;
	}
	cout<<"Books issued in the library: "<<count<<endl;
	}//if
	else if(op==3)
	{
	f.read((char*)&b,sizeof(b));
	f.seekg(0,ios::end);
	count=f.tellg()/sizeof(b);
	cout<<"Total books in the library: "<<count<<endl;
	}
	f.close();
}



	void deleteb()
	{
	char confirm='n';char got='f';
	f.open("library.txt",ios::in|ios::binary);
	g.open("temp.txt",ios::out|ios::binary);
	cout<<"Enter book no whose record is to be deleted"<<endl;
	cin>>bno;
	while(f.read((char*)&b,sizeof(b)))
	{
	if(b.getbookno()==bno)
	{
	got='t';
	cout<<"Are Yyou sure you want to delete this record(y/n)"<<endl;
	cin>>confirm;
	b.dispb();
	cout<<"RECORD IS SUCCESSFULLY DELETED"<<endl;
	if(confirm=='n')
	g.write((char*)&b,sizeof(b));
	}
	else
	g.write((char*)&b,sizeof(b));//while
	}
	f.close();
	g.close();
	remove("library.txt");
	rename("temp.txt","library.txt");
	if(got=='f')
	cout<<"RECORD NOT FOUND"<<endl;
	else
	{
	cout<<"\n\nChanged list of books in the library"<<endl;
	showall();
	}
	}

void main()
{

clrscr();
char id[30],pswd[10];
textbackground(BLACK);
textcolor(RED);
cout<<"\n\n\n\n\n\t\t\t\t";
cprintf("LIBRARY MANAGEMENT");
cout<<"\n\n\n\n\t\t\t\t";
cprintf(" MADE BY: ");
cout<<"\n\n\t\t\t\t";
cprintf("SIMRAN MEHTA");
cout<<"\n\t\t\t\t";
cprintf("VARUNA K S");
cout<<"\n\n\t\t\t\t";
cprintf("Class:XII");
cout<<endl;

for(int long k=0;k<=9999999;k++);
for(k=0;k<=9999999;k++);
 for(k=0;k<=9999999;k++);
 for(k=0;k<=9999999;k++);
 for(k=0;k<=9999999;k++);
//password

clrscr();
textcolor(BLACK);
cout<<"\n\n\n\n\t\t\t";
cprintf("LOGIN");
cout<<endl;
textcolor(WHITE);
cout<<"\t\t\t";
for(int a=0;a<=6;a++)
for(int long s=0;s<=9999999;s++);
cprintf("USER ID:");
gets(id);
if(strcmp(id,"simran@lib.com")==0)
{
for(int j=1;j<=3;j++)
{
cout<<"\n\t\t\t";
cprintf("PASSWORD: ");
gets(pswd);
cout<<endl;
if(strcmp(pswd,"17051998")==0)
{
cout<<"\t\t\t";
cprintf("YOU MAY PROCEED");
cout<<endl;
break;
}else
{
cout<<"\t\t\t***ACCESS DENIED\n\t\t\tWRONG USER ID OR PASSWORD***"<<endl;
cout<<"\t\t\t***"<<3-j<<" "<<"CHANCE(S) LEFT***"<<endl;
if(j==3)
exit(0);
}}}
else if(strcmp(id,"varuna@lib.com")==0)
{
for(int j=1;j<=3;j++)
{
cout<<"\n\t\t\t";
cprintf("PASSWORD: ");
gets(pswd);
cout<<endl;
if(strcmp(pswd,"23011998")==0)
{
cout<<"\t\t\t";
cprintf("YOU MAY PROCEED");
cout<<endl;
break;
}else
{
cout<<"***ACCESS DENIED\nWRONG USER ID OR PASSWORD***"<<endl;
cout<<"***"<<3-j<<"CHANCE LEFT***"<<endl;
if(j==3)
exit(0);
}}}
else
{
cout<<"\n\n\t\tWRONG USER ID!"<<endl;
for(k=0;k<=9999999;k++);
exit(0);
}



for(k=0;k<=9999999;k++);
for(k=0;k<=9999999;k++);

clrscr();
cout<<"\n\n\n\n\n\n\n\t\t\t";
cprintf("WELCOME TO \"ELORE LIBRARY\"");
for(int x=0;x<=5;x++)
{
for(k=0;k<=9999999;k++);
for(k=0;k<=9999999;k++);
}
cout<<"\n\n\t\t\t\t  3"<<endl;
for(k=0;k<=9999999;k++);
cout<<"\n\t\t\t\t  2"<<endl;
for(k=0;k<=9999999;k++);
cout<<"\n\t\t\t\t  1"<<endl;
for(k=0;k<=9999999;k++);

while(ch=='y'||ch=='Y')
{
clrscr();
textbackground(BLACK);
textcolor(GREEN);
cprintf("\t\t\t\t HERE YOU GO \t\t\t\t");
cout<<endl<<endl;
cout<<"1. Add new books"<<endl;
cout<<"2. List of all books in library"<<endl;
cout<<"3. Search books"<<endl;
cout<<"4. Issue books"<<endl;
cout<<"5. Return books"<<endl;
cout<<"6. Count of books"<<endl;
cout<<"7. Delete record"<<endl;
cout<<"8. Exit\n"<<endl;
cprintf("Enter your choice");
cout<<endl;
cin>>op;
switch(op)
{
case 1:clrscr();
f.open("library.txt",ios::in|ios::out|ios::app|ios::binary);
while(ch=='y'||ch=='Y')
{
b.readb();
f.write((char*)&b,sizeof(b));
cout<<"\nDo you want to add more books?(y/n)"<<endl;
cin>>ch;
}
f.close();
break;

case 2:clrscr();
showall();
break;
case 3:
search();
if(found==0){
cout<<"Want to issue a book?"<<endl;
cin>>ch;
if(ch=='y'||ch=='Y')
{
issue();
}
else
exit(0);
}
break;
case 4:
clrscr();
search();
issue();
break;
case 5:
clrscr();
returnbook();
break;
case 6:
avail();
break;
case 7:
clrscr();
showall();
deleteb();
break;
case 8:
{
int z,l=0,gd=DETECT;
int gm;
initgraph(&gd,&gm,"C:\\TC\\bgi");
settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
setcolor(3);
outtextxy(150,224,"THANK YOU FOR VISITING");
for(int j=20;j<70;j+=10)
{
setcolor(GREEN);
circle (100,80,j);
delay(100);
}
for(j=20;j<70;j+=10)
{
setcolor(GREEN);
circle (300,100,j);
delay(100);
}
for(j=20;j<70;j+=10)
{
setcolor(GREEN);
circle (500,80,j);
delay(100);
}
for(j=20;j<70;j+=10)
{
setcolor(GREEN);
circle (570,250,j);
delay(100);
}
for(j=20;j<70;j+=10)
{
setcolor(GREEN);
circle (60,250,j);
delay(100);
}
for(j=20;j<70;j+=10)
{
setcolor(GREEN);
circle (100,395,j);
delay(100);
}
for(j=20;j<70;j+=10)
{
setcolor(GREEN);
circle (300,415,j);
delay(100);
}
for(j=20;j<70;j+=10)
{
setcolor(GREEN);
circle (500,395,j);
delay(100);
}
	for(j=20;j<70;j+=10)
	{
	setcolor(YELLOW);
	circle (500,395,j);
	delay(100);
	}
	for(j=20;j<70;j+=10)
	{
	setcolor(YELLOW);
	circle (300,415,j);
	delay(100);
	}
	for(j=20;j<70;j+=10)
	{
	setcolor(YELLOW);
	circle (100,395,j);
	delay(100);
	}
	for(j=20;j<70;j+=10)
	{
	setcolor(YELLOW);
	circle (60,250,j);
	delay(100);
	}
	for(j=20;j<70;j+=10)
	{
	setcolor(YELLOW);
	circle (570,250,j);
	delay(100);
	}
	for(j=20;j<70;j+=10)
	{
	setcolor(YELLOW);
	circle (500,80,j);
	delay(100);
	}
	for(j=20;j<70;j+=10)
	{
	setcolor(YELLOW);
	circle (300,100,j);
	delay(100);
	}
	for(j=20;j<70;j+=10)
	{
	setcolor(YELLOW);
	circle (100,80,j);
	delay(100);
	}
		for(j=20;j<70;j+=10)
		{
		setcolor(BLUE);
		circle (100,80,j);
		delay(100);
		}
		for(j=20;j<70;j+=10)
		{
		setcolor(BLUE);
		circle (300,100,j);
		delay(100);
		}
		for(j=20;j<70;j+=10)
		{
		setcolor(BLUE);
		circle (500,80,j);
		delay(100);
		}
		for(j=20;j<70;j+=10)
		{
		setcolor(BLUE);
		circle (570,250,j);
		delay(100);
		}
		for(j=20;j<70;j+=10)
		{
		setcolor(BLUE);
		circle (60,250,j);
		delay(100);
		}
		for(j=20;j<70;j+=10)
		{
		setcolor(BLUE);
		circle (100,395,j);
		delay(100);
		}
		for(j=20;j<70;j+=10)
		{
		setcolor(BLUE);
		circle (300,415,j);
		delay(100);
		}
		for(j=20;j<70;j+=10)
		{
		setcolor(BLUE);
		circle (500,395,j);
		delay(100);
		}
		getch();
graphdefaults();
clearviewport();
setbkcolor(BLACK);
setviewport(0,0,670,440,1);
}
exit(0);
break;
default:
{
int z2,l2=0,gd=DETECT;
int gm;
initgraph(&gd,&gm,"C:\\TC\\bgi");
settextstyle(SANS_SERIF_FONT,HORIZ_DIR,3);
setcolor(3);
outtextxy(150,224,"THANK YOU FOR VISITING");
for(int j=20;j<70;j+=10)
{
setcolor(GREEN);
circle (100,80,j);
delay(100);
}
for(j=20;j<70;j+=10)
{
setcolor(GREEN);
circle (300,100,j);
delay(100);
}
for(j=20;j<70;j+=10)
{
setcolor(GREEN);
circle (500,80,j);
delay(100);
}
for(j=20;j<70;j+=10)
{
setcolor(GREEN);
circle (570,250,j);
delay(100);
}
for(j=20;j<70;j+=10)
{
setcolor(GREEN);
circle (60,250,j);
delay(100);
}
for(j=20;j<70;j+=10)
{
setcolor(GREEN);
circle (100,395,j);
delay(100);
}
for(j=20;j<70;j+=10)
{
setcolor(GREEN);
circle (300,415,j);
delay(100);
}
for(j=20;j<70;j+=10)
{
setcolor(GREEN);
circle (500,395,j);
delay(100);
}
	for(j=20;j<70;j+=10)
	{
	setcolor(YELLOW);
	circle (500,395,j);
	delay(100);
	}
	for(j=20;j<70;j+=10)
	{
	setcolor(YELLOW);
	circle (300,415,j);
	delay(100);
	}
	for(j=20;j<70;j+=10)
	{
	setcolor(YELLOW);
	circle (100,395,j);
	delay(100);
	}
	for(j=20;j<70;j+=10)
	{
	setcolor(YELLOW);
	circle (60,250,j);
	delay(100);
	}
	for(j=20;j<70;j+=10)
	{
	setcolor(YELLOW);
	circle (570,250,j);
	delay(100);
	}
	for(j=20;j<70;j+=10)
	{
	setcolor(YELLOW);
	circle (500,80,j);
	delay(100);
	}
	for(j=20;j<70;j+=10)
	{
	setcolor(YELLOW);
	circle (300,100,j);
	delay(100);
	}
	for(j=20;j<70;j+=10)
	{
	setcolor(YELLOW);
	circle (100,80,j);
	delay(100);
	}
		for(j=20;j<70;j+=10)
		{
		setcolor(BLUE);
		circle (100,80,j);
		delay(100);
		}
		for(j=20;j<70;j+=10)
		{
		setcolor(BLUE);
		circle (300,100,j);
		delay(100);
		}
		for(j=20;j<70;j+=10)
		{
		setcolor(BLUE);
		circle (500,80,j);
		delay(100);
		}
		for(j=20;j<70;j+=10)
		{
		setcolor(BLUE);
		circle (570,250,j);
		delay(100);
		}
		for(j=20;j<70;j+=10)
		{
		setcolor(BLUE);
		circle (60,250,j);
		delay(100);
		}
		for(j=20;j<70;j+=10)
		{
		setcolor(BLUE);
		circle (100,395,j);
		delay(100);
		}
		for(j=20;j<70;j+=10)
		{
		setcolor(BLUE);
		circle (300,415,j);
		delay(100);
		}
		for(j=20;j<70;j+=10)
		{
		setcolor(BLUE);
		circle (500,395,j);
		delay(100);
		}
		getch();
graphdefaults();
clearviewport();
setbkcolor(BLACK);
setviewport(0,0,670,440,1);
 }
exit(0);
break;
}
cout<<"\nDo you want to continue?(y/n)"<<endl;
cin>>ch;
}getch();
}
