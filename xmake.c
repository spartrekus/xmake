

/* include the X library headers */
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>

/* include some silly stuff */
#include <stdio.h>
#include <stdlib.h>

/* here are our X variables */
Display *dis;
int screen;
Window win;
GC gc;

/* here are our X routines declared! */
void init_x();
void close_x();
void redraw();


void init_x() 
{
/* get the colors black and white (see section for details) */        
	unsigned long black,white;

	dis=XOpenDisplay((char *)0);
   	screen=DefaultScreen(dis);
	black=BlackPixel(dis,screen),
	white=WhitePixel(dis, screen);
   	win=XCreateSimpleWindow(dis,DefaultRootWindow(dis),0,0,	300, 300, 5,black, white);
	XSetStandardProperties(dis,win,"XMAKE","Hi",None,NULL,0,NULL);
	XSelectInput(dis, win, ExposureMask|ButtonPressMask|KeyPressMask);
        gc=XCreateGC(dis, win, 0,0);        
	XSetBackground(dis,gc,white);
	XSetForeground(dis,gc,black);
	XClearWindow(dis, win);
	XMapRaised(dis, win);
};

void close_x() {
	XFreeGC(dis, gc);
	XDestroyWindow(dis,win);
	XCloseDisplay(dis);	
	exit(1);				
};

void redraw() {
	XClearWindow(dis, win);
};

void mxprint( int yy , int xx , char *mystring) 
{
              int x = xx; int y= yy;  char text[255];			
  	                    //XSetForeground(dis,gc,rand()%event.xbutton.x%255);
                            strcpy(text,"Hello World!"); 
			    XDrawString(dis,win,gc,x,y, text, strlen(text));  
};



int main () 
{
	XEvent event;		/* the XEvent declaration !!! */
	KeySym key;		/* a dealie-bob to handle KeyPress Events */	
	char text[255];		/* a char buffer for KeyPress Events */

	init_x();
        int gameover = 0;
	/* look for events forever... */
	while( gameover == 0 ) {		
		/* get the next event and stuff it into our event variable.
		   Note:  only events we set the mask for are detected!
		*/
		XNextEvent(dis, &event);
	
		if (event.type==Expose && event.xexpose.count==0) {
		/* the window was exposed redraw it! */
			redraw();
		}
		if (event.type==KeyPress&&
		    XLookupString(&event.xkey,text,255,&key,0)==1) {
		/* use the XLookupString routine to convert the invent
		   KeyPress data into regular text.  Weird but necessary...
		*/
  		       
                       if (text[0]=='q') {   gameover = 1;       }  

                       else if (text[0]=='l') {    mxprint( 250, 250, "line" );   } 

                       else if (text[0]=='u') {    mxprint( 50, 50, "hello" );   } 

                       else if (text[0]=='t') {    int x = 100; int y= 100; 		
  	                    //XSetForeground(dis,gc,rand()%event.xbutton.x%255);
                            strcpy(text,"Hello World!"); 
			    XDrawString(dis,win,gc,x,y, text, strlen(text));     } 
                       else if (text[0]=='i') 
                       {
				close_x();
		       }
		        printf("You pressed the %c key!\n",text[0]);
		}


		if (event.type==ButtonPress) 
                {
		/* tell where the mouse Button was Pressed */
			int x=event.xbutton.x, y=event.xbutton.y;

			strcpy(text,"Make !");
			XSetForeground(dis,gc,rand()%event.xbutton.x%255); 
			XDrawString(dis,win,gc,x,y, text, strlen(text));
                        printf( 	"the position %d %d \n",  event.xbutton.y, y=event.xbutton.x  );
                        system( " make " );
		}
	}

       	close_x();
}



