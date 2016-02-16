//PROJECT-TETRIS:BLOCKOUT
#include<simplecpp>
#include<time.h>
class colour{
	public:
	int red,blue,green;bool fill;
};
colour red={200,0,0,1} ,pink={200,100,0,1},grey={100,100,100,1},brown={120,20,0,1},green={30,0,200,1};
colour liteblue={50,235,0,1},offwite={220,220,220,1},yellow={220,0,220,1},lgrey={130,130,130,1},dgrey={70,60,60,1};
colour purple={190,140,0,1},orange={255,51,153,1},lred={255,51,51,1},dbrown={153,0,0,1},llgrey={192,192,192,1};
class button {                                    
	public:
	int cx,cy,l,w;string lbl;colour c;
	button( int x,int y,int len,int b,string txt,colour col ,bool bor){  //constucts a rectangle with given attributes
		cx=x;cy=y;l=len;w=b;lbl=txt;c=col;
		 Rectangle r1(cx,cy,l,w);
	    r1.setColor(COLOR(c.red,c.green,c.blue));r1.setFill(c.fill);
	    if(bor)border();
	    r1.imprint();
	    Text t(cx,cy,lbl);t.imprint();
		}
	bool inside(int coordi){
	int x,y;
	x=coordi/65536;y=coordi%65536;
	if((abs(x-cx))<= l/2 && (abs(cy-y))<=w/2)return 1;
	else return 0;
}

void border( ){                     //constructs the border of the button
	Rectangle rec2(cx,cy,l+10,w+10);
	if(c.red>235)c.red=235;
	if(c.blue>235)c.blue=235;
	if(c.green>235)c.green=235;
	rec2.setColor(COLOR((c.red+20),(c.green+20),(c.blue+20)));rec2.setFill(1);
	rec2.imprint();
	}
};//class definiton ends
class Screen1      //stores information about the entire canvas in form of a 2-D array
{
  public:
  class Dot         //represents the characteristics of a single rectangle on the screen
  { public:
    bool state;
    int l,m,n;
    Dot(){state=0; l=0;m=0;n=0;}
  };
  Dot matrix[25][25];
  public:
  
  Screen1(){initCanvas("tetris",1,1);}  
  
};

Screen1 interface;     
class Rect             
{public:
  Rectangle r;
};
Rect array[25][25]; // array of rectangles
void game(short& level);
void home();
class tetraminoes  // class for blocks of various shapes
{
  Rectangle r1,r2,r3,r4;
  int color[3],x[4],y[4],j[4];
  public:        // contains 6 constructors each giving rise to a different shape
  tetraminoes(int a,int b,int c)
  {
    r1.reset(250,70,20,20);r2.reset(250,50,20,20);r3.reset(270,50,20,20);r4.reset(270,70,20,20); 
	x[0]=x[1]=12;x[2]=x[3]=13;y[0]=y[3]=-1;y[1]=y[2]=-2;
	color[0]=a;color[1]=b;color[2]=c; 
    j[0]=0;j[1]=360;j[2]=45;j[3]=90;    
  }
  tetraminoes(int a, int b, int c,char ch)
  {
    r1.reset(250,70,20,20);r2.reset(230,70,20,20);r3.reset(250,50,20,20);r4.reset(270,70,20,20);
    y[0]=y[1]=y[3]=-1; y[2]=-2;	 x[0]=x[2]=12;x[1]=11;x[3]=13;
    color[0]=a;color[1]=b;color[2]=c; 
    j[0]=0;j[1]=270;j[2]=360;j[3]=90;
  }
  tetraminoes(int a,int b,int c, string s)
  {
	r1.reset(250,70,20,20);r2.reset(250,50,20,20);r3.reset(250,30,20,20);r4.reset(250,10,20,20);
	x[0]=x[1]=x[2]=x[3]=12; y[0]=-1;y[1]=-2;y[2]=-3;y[3]=-4;
	color[0]=a;color[1]=b;color[2]=c; 
    j[0]=0;j[1]=j[2]=j[3]=360;
  }
  tetraminoes(int a,int b,int c, float f)
  {
	r1.reset(250,70,20,20);r2.reset(250,50,20,20);r3.reset(250,30,20,20);r4.reset(270,70,20,20);
	x[0]=x[1]=x[2]=12;x[3]=13; y[0]=y[3]=-1;y[1]=-2;y[2]=-3;
	color[0]=a;color[1]=b;color[2]=c; 
    j[0]=0;j[1]=j[2]=360;j[3]=90;
  }
  tetraminoes(int a,int b,int c, int l)
  {
	r1.reset(250,70,20,20),r2.reset(230,70,20,20);r3.reset(250,50,20,20);r4.reset(270,50,20,20);
	x[0]=x[2]=12;x[1]=11;x[3]=13; y[0]=y[1]=-1;y[2]=y[3]=-2;
	color[0]=a;color[1]=b;color[2]=c; 
    j[0]=0;j[1]=270;j[2]=360;j[3]=360+45;
  }
  tetraminoes(int a,int b,int c, char chh, int i)
  {
	r1.reset(250,70,20,20),r2.reset(230,50,20,20);r3.reset(250,50,20,20);r4.reset(270,70,20,20);
	x[0]=x[2]=12;x[1]=11;x[3]=13; y[0]=y[3]=-1;y[2]=y[1]=-2;
	color[0]=a;color[1]=b;color[2]=c; 
    j[0]=0;j[1]=315;j[2]=360;j[3]=90;
  }
  void set()         // sets the initial colour of the blocks
  {
	r1.setColor(COLOR(color[0],color[1],color[2]));r2.setColor(COLOR(color[0],color[1],color[2]));
	r3.setColor(COLOR(color[0],color[1],color[2]));r4.setColor(COLOR(color[0],color[1],color[2]));
    r1.setFill(1);r2.setFill(1);r3.setFill(1);r4.setFill(1);
  }
	
  void rotate(char c)         // functions for rotating the blocks clockwise or
  {                            // counbterclockwise depending on the argument
	int n;
    if(c=='l'){n=1;}
    else if(c=='r'){n=2;}
    for(int i=0;i<4;i++)
    {
      int p=x[i],q=y[i];
      double r=sqrt((x[0]-x[i])*(x[0]-x[i])+(y[0]-y[i])*(y[0]-y[i])); 
      x[i]=x[0]+r*cosine((j[i]+180*n)%360);
      y[i]=y[0]+r*sine((j[i]+180*n)%360);
      if(!(x[i]<25 && x[i]>=0 && y[i]<25)){x[i]=p;y[i]=q;return;}
      if(interface.matrix[x[i]][y[i]].state)
      {x[i]=p;y[i]=q;return;}
    }
    if(c=='r'){for(int i=0;i<4;i++)
    {j[i]=(j[i]+90)%360;}}
    else if(c=='l'){for(int i=0;i<4;i++)
    {j[i]=(j[i]+270)%360;}}
    r1.moveTo(x[0]*20+10,y[0]*20+10+80);
	r2.moveTo(x[1]*20+10,y[1]*20+10+80);
	r3.moveTo(x[2]*20+10,y[2]*20+10+80);
	r4.moveTo(x[3]*20+10,y[3]*20+10+80); wait(0.2);
  }
  bool down(short& level)      // function to move the block down
  {  
	r1.move(0,20); 
    r2.move(0,20);
    r3.move(0,20);
    r4.move(0,20); wait(0.7-level/5.0);  
    y[0]+=1;y[1]+=1;y[2]+=1;y[3]+=1;
    for(int i=0;i<4;i++){if(y[i]<0)return false;}
	return true;
  }
  bool down2(short& level)     // function for hard drop
  {  
	r1.move(0,20); 
    r2.move(0,20);
    r3.move(0,20);
    r4.move(0,20); wait(0.05);  
    y[0]+=1;y[1]+=1;y[2]+=1;y[3]+=1;
    for(int i=0;i<4;i++){if(y[i]<0)return false;}
	return true;
  }
  void right()                  // to move the block right
  { 
	for(int i=0;i<4;i++){if(x[i]==24)return;
		if(!(x[i]<24 && interface.matrix[x[i]+1][y[i]].state==false)){return;}}
    r1.move(20,0);
    r2.move(20,0);
    r3.move(20,0);
    r4.move(20,0); wait(0.2);
    x[0]+=1;x[1]+=1;x[2]+=1;x[3]+=1;
  }
  void left()                  // to move the block left
  { 
	for(int i=0;i<4;i++){if(x[i]==0)return;
		if(y[i]>=0){if(!(x[i]>0 && interface.matrix[x[i]-1][y[i]].state==false)){return;}}}
    r1.move(-20,0);
    r2.move(-20,0);
    r3.move(-20,0);
    r4.move(-20,0); wait(0.2);
    x[0]-=1;x[1]-=1;x[2]-=1;x[3]-=1;
  }
  bool downempty()            // checks whether the space immediately below is empty or not
  {
    for(int i=0;i<4;i++)
    {
	  if(y[i]>=0)
	  {
		 if(!(interface.matrix[x[i]][y[i]+1].state==false && y[i]<24)){return false;}
      }
    }
    
    return true;
  }
  
  friend void adjust(int& );
  int down1(int& score,short& level)    // function responsible for bringing a block down to its final position
  { if(level==1){if(score>=1200)level=2;}
    if(level==2){if(score>=4800)level=3;}
	  button restart(550,400,40,20,"RESTART",llgrey,1);
     button pause(550,440,40,20,"",llgrey,1);
     button quit(550,480,40,20,"QUIT",llgrey,1);
     Text t1(550,440,"PAUSE");
	if(!downempty()){return 10;}
	XEvent event;
	for(int i=0;i<4;i++){ if(interface.matrix[x[i]][0].state){return 10;}}
    while(1)
    {
	  if(!downempty()){
		  for(int i=0;i<4;i++){interface.matrix[x[i]][y[i]].state=true;
			  interface.matrix[x[i]][y[i]].l=color[0];
			  interface.matrix[x[i]][y[i]].m=color[1];
			  interface.matrix[x[i]][y[i]].n=color[2];
			  array[x[i]][y[i]].r.reset(x[i]*20+10,y[i]*20+10+80,20,20);
			  array[x[i]][y[i]].r.setColor(COLOR(color[0],color[1],color[2]));
			  array[x[i]][y[i]].r.setFill(1);
			  array[x[i]][y[i]].r.imprint(); }
	     return 0 ;
	  }
	  
	  if(checkEvent(event))       // to call various functions corresponding to the input given
	  {
	    if(keyPressEvent(event))
	    {
			if(charFromEvent(event)=='a')
			{left();}
			else if(charFromEvent(event)=='d')
			{right();}
			
			else if(charFromEvent(event)=='s')
			{
			    while(downempty()){down2(level);} score+=1;
			}
			else if(charFromEvent(event)=='k')
			{
			    rotate('l');
			}
			else if(charFromEvent(event)=='l')
			{
			    rotate('r');
			}
		//if(!down()){return 10;break;};
		
	}
	else if(mouseButtonPressEvent(event))
	{
		int a=event.xbutton.x,b=event.xbutton.y;
		int where=a*65536+b;
		if(restart.inside(where)){closeCanvas();game(level);}
		else if(quit.inside(where)){closeCanvas(); home();}
		else if(pause.inside(where)){
			t1.reset(550,440,"PLAY");while(true){
				int coord=getClick();
			if(pause.inside(coord)){t1.reset(550,440,"PAUSE");break;}
		}
	}
}
	}if(downempty()){down(level);}
  }}
 
};
class block  // class for a special block which can pass over other blocks to reach an empty space
{             // it has the similar basic structure and function members as class tetraminoes
  Rectangle r1;
  int color[3],x,y;
  public:        
  block(int a,int b,int c)
  {
    r1.reset(250,70,20,20);
	x=12;y=-1;
	color[0]=a;color[1]=b;color[2]=c; 
  }
  void set()         
  {
	r1.setColor(COLOR(color[0],color[1],color[2]));
    r1.setFill(1);
  }
  bool down(short& level)     
  {  
	r1.move(0,20); 
    wait(0.7-level/5.0);  
    y+=1;if(y<0)return false;
	return true;
  }
  bool down2(short& level)     
  {  
	r1.move(0,20); 
     wait(0.05);  
    y+=1;
    if(y<0)return false;
	return true;
  }
  void right()                  
  { 
	if(x==24)return;
		if(y>=0){if(!(x<24 && interface.matrix[x+1][y].state==false)){return;}}
    r1.move(20,0);
    wait(0.2);
    x+=1;
  }
  void left()                  
  { 
   if(x==0)return;
		if(y>=0){if(!(x>0 && interface.matrix[x-1][y].state==false)){return;}}
    r1.move(-20,0);
    wait(0.2);
    x-=1;
  }
   int max(int x)
  {
	
	 for(int k=24;k>=0;k--)
	 {if(interface.matrix[x][k].state==false)return k;}
	 return -1;
  }
  bool downempty()            
  {
    int i=max(x);
    if(y<i && y<24)return true;
    return false;
  }
  
  friend void adjust(int& );
  
  int down1(int& score,short& level)    
  { if(level==1){if(score>=1200)level=2;}
    if(level==2){if(score>=4800)level=3;}
	  button restart(550,400,40,20,"RESTART",llgrey,1);
     button pause(550,440,40,20,"",llgrey,1);
     button quit(550,480,40,20,"QUIT",llgrey,1);
     Text t1(550,440,"PAUSE");
	if(!downempty()){return 10;}
	XEvent event;
 if(interface.matrix[x][0].state){return 10;}
    while(1)
    {
	  if(!downempty()){
		  interface.matrix[x][y].state=true;
			  interface.matrix[x][y].l=color[0];
			  interface.matrix[x][y].m=color[1];
			  interface.matrix[x][y].n=color[2];
			  array[x][y].r.reset(x*20+10,y*20+10+80,20,20);
			  array[x][y].r.setColor(COLOR(color[0],color[1],color[2]));
			  array[x][y].r.setFill(1);
			  array[x][y].r.imprint(); 
	     return 0 ;
	  }
	  
	  if(checkEvent(event))       // to call various functions corresponding to the input given
	  {
	    if(keyPressEvent(event))
	    {
			if(charFromEvent(event)=='a')
			{left();}
			else if(charFromEvent(event)=='d')
			{right();}
			
			else if(charFromEvent(event)=='s')
			{
			    while(downempty()){down2(level);} score+=1;
			}
			
		//if(!down()){return 10;break;};
		
	}
	else if(mouseButtonPressEvent(event))
	{
		int a=event.xbutton.x,b=event.xbutton.y;
		int where=a*65536+b;
		if(restart.inside(where)){closeCanvas();game(level);}
		else if(quit.inside(where)){closeCanvas(); home();}
		else if(pause.inside(where)){
			t1.reset(550,440,"PLAY");while(true){
				int coord=getClick();
			if(pause.inside(coord)){t1.reset(550,440,"PAUSE");break;}
		}
	}
}
	}if(downempty()){down(level);}
  }}
 
};

  void adjust(int& score,short& level)       //
  {int count=0,row[5]={-1,-1,-1,-1,-1},rowno=0;
	for(int j=24;j>=rowno;j--)
    {
      bool pass=true;
      for(int i=0; i<25 && pass==true;i++)
      { 
        pass=pass && interface.matrix[i][j].state;
      } 
      if(pass==true && count==0)
      { count++; 
      row[0]=j;rowno=j-3;}
      else if(pass==true){row[count]=j;count++;}
  }
  if(count>0){int step=1;
        for(int k=row[0]-1;k>=0;k--)
        { if(row[step]==k){step++;continue;}
          for(int i=0;i<25;i++){ 
if(interface.matrix[i][k].state==false)
{
  interface.matrix[i][k+step].state=false;
  if((i%2)==((k+step)%2))
  {  
    interface.matrix[i][k+step].l=interface.matrix[i][k+step].m=interface.matrix[i][k+step].n=0;
    array[i][k].r.setColor(COLOR(0,0,0));array[i][k].r.setFill(1);
  }
  else
  {  
    interface.matrix[i][k+step].l=interface.matrix[i][k+step].m=interface.matrix[i][k+step].n=64;
    array[i][k].r.setColor(COLOR(64,64,64));array[i][k].r.setFill(1);
  }
}
else
{
  interface.matrix[i][k+step]=interface.matrix[i][k];
}
array[i][k].r.move(0,20*step); array[i][k].r.imprint();
array[i][k+step]=array[i][k];

          
	  }}
         for(int l=0;l<count;l++){
         for(int i=0;i<25;i++)
         {  
		  interface.matrix[i][l].state=false;
          array[i][l].r.reset(i*20+10,l*20+10+80,20,20);
          if((l%2)==(i%2))
			{ 
		     array[i][l].r.setColor(COLOR(0,0,0));
		     interface.matrix[i][l].l=interface.matrix[i][l].m=interface.matrix[i][l].n=0;
		    }
		      else {array[i][l].r.setColor(COLOR(64,64,64));
		      interface.matrix[i][l].l=interface.matrix[i][l].m=interface.matrix[i][l].n=64;}
		    
		   
          array[i][l].r.setFill(1); array[i][l].r.imprint();}
        }
      } 
      if(count==1)score=score+40*level;         // adjusting the score when lines are cleared
      if(count==2)score=score+100*level;
      if(count==3)score=score+300*level;
      if(count==4)score=score+1200*level;
    
   
}

  void gameover(int fscore);  
  void game(short& level)           // creates play screen
  { initCanvas("TETRIS: BLOCKOUT ",600,580);
    
	for(int i=0;i<=100;i++)
	{
		Rectangle d(250,330,700-6*i,660-5.8*i);
		d.setColor(COLOR(128-i*3.2,128-i*3.2,128-i*3.2));
		d.setFill(1);
		d.imprint();
	}
		
	  for(int j=0;j<25;j++){
		 
		for(int i=0;i<25;i++){
			interface.matrix[i][j].state=false;
			interface.matrix[i][j].l=0;
			interface.matrix[i][j].m=0;
			interface.matrix[i][j].n=0;
			array[i][j].r.reset(i*20+10,j*20+10+80,20,20);
			if(j%2==0)
			{
		      if(i%2==0)array[i][j].r.setColor(COLOR(0,0,0));
		      else array[i][j].r.setColor(COLOR(64,64,64));
		    }
		    else
		    {
		      if(i%2!=0)array[i][j].r.setColor(COLOR(0,0,0));
		      else array[i][j].r.setColor(COLOR(64,64,64));
		    }
			array[i][j].r.setFill(1);
			array[i][j].r.imprint();}}
		
     //Declare variable to hold seconds on clock.

time_t seconds;
/*
Get value from system clock and
place in seconds variable.
*/
time(&seconds);
/*Convert seconds to a unsigned integer.*/
srand((unsigned int) seconds); 

  int i=0;  float l=0.2; int k=(int)randuv(1,2560)%8,z=(int)randuv(1,2560)%6,score=0;
  if(k==0)k++;
  Rectangle g(550,535,60,60);
  g.setColor(COLOR(192,192,192));g.setFill(1);
 Rectangle r1(550,290,80,160),s1,s2,s3,s4; r1.setColor(COLOR(192,192,192));r1.setFill(1);r1.imprint();
	  Text t5(550,240,"NEXT");
   Text t3(550,140,"LEVEL"); t3.setColor(COLOR(192,192,192));t3.imprint();
  Text t1(550,530,"Score:");
    while(true)
    { 
	  int a,b,c,d,e,f;
	  int nextk=(int)randuv(1,2560)%8,nextz=(int)randuv(1,2560)%6;     //
	  if(nextk==0)nextk++;
	  if(z==0){a=200;b=0;c=0;}
	  else if(z==1){a=0;b=200;c=0;}
	  else if(z==2){a=0;b=0;c=200;}
	  else if(z==3){a=255;b=255;c=0;}
	  else if(z==4){a=139;b=0;c=139;}
	  else if(z==5){a=128;b=0;c=0;}
	 
	  Text t4(550,180,level); t4.setColor(COLOR(192,192,192)); t4.imprint();
	  
	  Text t2(550,550,score);
	  if(nextz==0){d=200;e=0;f=0;}
	  else if(nextz==1){d=0;e=200;f=0;}
	  else if(nextz==2){d=0;e=0;f=200;}
	  else if(nextz==3){d=255;e=255;f=0;}
	  else if(nextz==4){d=139;e=0;f=139;}
	  else if(nextz==5){d=128;e=0;f=0;}
	  if(nextk==1)
	  {s1.reset(540,280,20,20);s2.reset(560,280,20,20);s3.reset(540,300,20,20);s4.reset(560,300,20,20);s1.setColor(COLOR(d,e,f));}
	  else if(nextk==2)
	  {s1.reset(550,260,20,20);s2.reset(550,280,20,20);s3.reset(550,300,20,20);s4.reset(550,320,20,20);s1.setColor(COLOR(d,e,f));}
	  else if(nextk==3)
	  {s1.reset(540,280,20,20);s2.reset(560,320,20,20);s3.reset(540,300,20,20);s4.reset(540,320,20,20);s1.setColor(COLOR(d,e,f));}
	  else if(nextk==4)
	  {s1.reset(550,280,20,20);s2.reset(530,300,20,20);s3.reset(550,300,20,20);s4.reset(570,280,20,20);s1.setColor(COLOR(d,e,f));}
	  else if(nextk==5)
	  {s1.reset(530,300,20,20);s2.reset(550,300,20,20);s3.reset(570,300,20,20);s4.reset(550,280,20,20);s1.setColor(COLOR(d,e,f));}
	  else if(nextk==6)
	  {s1.reset(570,300,20,20);s2.reset(550,300,20,20);s3.reset(550,280,20,20);s4.reset(530,280,20,20);s1.setColor(COLOR(d,e,f));}
	  else if(nextk==7)
	  {s1.reset(570,300,20,20);s2.reset(550,300,0,0);s3.reset(550,280,0,0);s4.reset(530,280,0,0);s1.setColor(COLOR(218,165,32));}
	  
	  s2.setColor(COLOR(d,e,f)); s3.setColor(COLOR(d,e,f)); s4.setColor(COLOR(d,e,f)); 
	  s1.setFill(1);s2.setFill(1);s3.setFill(1);s4.setFill(1);
	  if(k==1){ tetraminoes ob(a,b,c);ob.set(); ob.down1(score,level);}
	  else if(k==5){ tetraminoes ob(a,b,c,'a'); ob.set(); i=ob.down1(score,level);}
	  else if(k==2){ tetraminoes ob(a,b,c,"str"); ob.set(); i=ob.down1(score,level);}
	  else if(k==3){ tetraminoes ob(a,b,c,l); ob.set(); i=ob.down1(score,level);}
	  else if(k==4){ tetraminoes ob(a,b,c,25); ob.set(); i=ob.down1(score,level);}
	 else if(k==6){ tetraminoes ob(a,b,c,'a',25); ob.set(); i=ob.down1(score,level);}
	  else if(k==7){ block ob(218,165,32); ob.set(); i=ob.down1(score,level);}
	  adjust(score,level);
	  if(i==10) break;
	  k=nextk;z=nextz; 
	  
	 if(i==10)break;
}
	Text t(300,250,"Game Over, You Lose!"); t.setColor(COLOR(255,255,255)); wait(2); closeCanvas();
	gameover(score);
}

void home();	

void instruct(){          //creates instruction window
	initCanvas("RULES",1000,700);
	for(int i=0;i<101;i++)
	{
		double points[4][2]={{500-3.9*i,350-2.1*i},{500-3.9*i,-350+2.1*i},{-500+3.9*i,-350+2.1*i},{-650+3.9*i,350-2.1*i}};
		Polygon rect(500,350,points,4);
		rect.setColor(COLOR(38+2*i,15+2*i,223+(i/4)));
		rect.setFill(1);
		rect.imprint();
	}
	button bth(500,590,100,40,"back to home",purple,1);
	Text t1( 500,220,"--> MOVE THE BLOCKS LEFT :'a'       ");
	Text t12(500,240,"                    RIGHT:'d'       ");
	Text t13(500,260,"                    ROTATE RIGHT:'l'");
	Text t14(500,280,"                    ROTATE LEFT:'k' ");
	Text t15(500,300,"                    HARD DROP:'s'   ");
	
	t1.imprint();t12.imprint();t13.imprint();
	Text t2(485,330,"--> IF A COMPLETE ROW IS FORMED,THE BLOCKS IN IT VANISH      ");
	t2.imprint();
	Text t3(485,360,"--> WHEN A BLOCK REACHES THE TOP,THE GAME IS OVER            ");
	
	t3.imprint();
	Text t9(485,390,"--> SPECIAL BLOCK: A SINGLE RECTANGLE                            ");
	Text t10(505,410,"         CAN PASS THROUGH SOLID BLOCKS TO OCCUPY THE LAST EMPTY SPACE OF A COLUMN" );
    Text t4(485,440,"--> SCORE: 40*LEVEL POINTS FOR 1 LINE CLEARED                ");t4.imprint();
    Text t5(485,460,"--> FOR 2 LINES CLEARED IN A GO:100*LEVEL , 3 LINES:300*LEVEL");t5.imprint();
    Text t6(485,480,"--> 4 LINES CLEARED :1200*LEVEL                              ");t6.imprint();
    Text ta(485,500,"--> HARD DROP : +1                                           ");t6.imprint();

    Text t7(485,520,"--> IF SCORE>1200, LEVEL UP FROM 1 TO 2                      ");
    Text t8(485,540,"--> IF SCORE>4800, LEVEL UP FROM 2 TO 3                      ");
	int where=getClick(); 
	if(bth.inside(where))
	{closeCanvas();
		home();
	}
}
void gameover(int fscore){              // opens gameover window
	initCanvas("GAMEOVER",500,320);
	for(int i=0;i<4;i++){
		colour c3={240-i*40,240-i*20,240-i*20,1};
		button border3(250,150,500-i*20,300-i*20,"",c3,0);
	}
	button gover(250,150,300,200,"GAME OVER",offwite,1);
		Text score(220,200,"YOUR  FINAL  SCORE :  "),score2(290,200,fscore);
		score.imprint();score2.imprint();
		string s;
		if(fscore ==0)s="GIVE UP!!!";
        else if(fscore <100)s="POOR  SHOW";
        else if(fscore <300)s="WELL PLAYED";
        else if(fscore <500)s="MACHHA DIYA";
        else if(fscore <1000)s="YOU ARE AN AWESOME PLAYER";
        else s="GODDMAXXX";
        Text comment(220,230,s);comment.imprint();
		wait(4);
		closeCanvas();
		home();
}
void play(short level){
	game(level);
	return;
}
void home(){                   //creates home screen 
initCanvas("WELCOME",1000,700);
for(int i=0;i<=5;i++){
	colour c1={i*20,i*20,i*20,1};
	button r1(500,350,1000-i*20,700-i*20,"",c1,0);
	
	}
Rectangle load;Text loadt(140,570,"LOADING");
int sum=0,prd=1;
for(int i=0;i<30;i++){
	  sum +=i;prd=prd*i+1;
	 int k,z; 
	  k=sum %12,z=prd%18;
	  button(75+z*50,75+k*50,45,45,"",lgrey,1);
	  button(75+k*50,75+(z%11)*50,45,45,"",dgrey,1);
	  load.reset(100+i*13.33,570,i*26.66,20);load.setColor(COLOR(230,210,0));load.setFill(1);
  
  }
for(int i=0;i<17;i++){	Line l1(100+i*50,50,100+i*50,650);l1.setColor(COLOR(90,90,90));l1.imprint();  }
for(int i=0;i<11;i++){	Line l2(50,100+i*50,950,100+i*50);l2.setColor(COLOR(90,90,90));l2.imprint();}

button play1(675,125,45,45,"",brown,1),play2(675,175,45,45,"PLAY",brown,1),play3(725,175,45,45,"",brown,1),play4(625,175,45,45,"",brown,1);
button level1(275,175,45,45,"",brown,1),level2(275,225,45,45,"SET",brown,1),level3(275,275,45,45,"LEVEL",brown,1),level4(325,275,45,45,"",brown,1);
button how1(725,375,45,45,"",brown,1),how2(725,425,45,45,"",brown,1),how3(675,425,45,45,"  TO  PLAY",brown,1),how4(625,425,45,45,"  HOW",brown,1);
button quit1(275,525,45,45,"",brown,1),quit2(325,525,45,45,"QUIT",brown,1),quit3(325,475,45,45,"",brown,1),quit4(375,475,45,45,"",brown,1);
loadt.hide();load.hide();

button a1(425,275,45,45,"1",orange,1),a2(425,225,45,45,"",grey,1),a3(425,175,45,45,"",grey,1);
int i=0;
while(1){
	int where=getClick();
	if(level1.inside(where) || level2.inside(where) || level3.inside(where) ||level4.inside(where) ){i=(i+1)%3;
		if(i==0)button a1(425,275,45,45,"1",orange,1),a2(425,225,45,45,"",grey,1),a3(425,175,45,45,"",grey,1);
		else if(i==1)button b1(425,275,45,45,"",lred,1),b2(425,225,45,45,"2",lred,1),b3(425,175,45,45,"",grey,1);
		else button c1(425,275,45,45,"",dbrown,1),c2(425,225,45,45,"",dbrown,1),c3(425,175,45,45,"3",dbrown,1);
		
	}
	else	if(how1.inside(where) || how2.inside(where) || how3.inside(where) || how4.inside(where) ){
		closeCanvas();instruct();
	}
	else	if(play1.inside(where) || play2.inside(where) || play3.inside(where) ||play4.inside(where) ){
		 closeCanvas();play(i+1);
	}
	else if(quit1.inside(where) || quit2.inside(where) || quit3.inside(where) ||quit4.inside(where) ){
		closeCanvas();break;
	}
}
return;
}

main_program{
	home();
}


	
 







	


