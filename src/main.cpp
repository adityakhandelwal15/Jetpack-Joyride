#include "main.h"
#include "timer.h"
#include "star.h"
#include "rect.h"
#include "polygon.h"
#include "tri.h"
#include "beams.h"
#include "dragon.h"
#include "semi.h"
#include "boom.h"
#include "circle.h"
#include "line.h"
#include "fireline.h"
#include "water_balloon.h"
#include <math.h>
#include <vector>
#include <ctime>
using namespace std;
// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
const double PI=3.14159265;
double angle=PI,mag_speed;

int farc = 0,saved = 10,magnef = 0;
float y_speed=-0.05;
float boomerang_x_speed = 0.06;
float boomerang_y_speed = 0.06;
GLMatrices Matrices;
GLuint     programID;
GLFWwindow *window;
int score=0;
int shoot = 0;
int busy = 0;
int busy1 = 0;
int shield = 0;
float water_speed=0.06;
int signal_dragon = 1;
float redspeed=0;
time_t current_time;
line a,b,c,d,e,f,g;
int signal_firebeam = 1;
std::vector<Rect> rectangles;
std::vector<fireline> fire;
std::vector<beams> fire_beams;
std::vector<beams> magneticlines;
std::vector<Rect> wall;
std::vector<Rect> rectangles2;
std::vector<polygon> coins;
std::vector<polygon> coins2;
std::vector<polygon> poly;
std::vector<polygon> cr;
std::vector<polygon> bonus;
std::vector<line> digit;
std::vector<polygon> golu;
Star star1;
Rect magnet;
Rect magnet2;
semi arc;
polygon tip;
water_balloon water_ball;
water_balloon redball;
int flag=0,ignition=0;
tri r;
tri r2;
circle slut,sluty;
polygon eye1;
polygon eye2;
dragon vicerious;
boom boomerang;

float screen_zoom = 1, screen_center_x = 0, screen_center_y = 0;
float camera_rotation_angle = 0;
float fall_speed;
Timer t60(1.0 / 60);
float ground_level = -2;
/* Render the scene with openGL */
/* Edit this function according to your assignment */
void draw() {
    // clear the color and depth in the frame buffer
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram (programID);

    glm::vec3 eye ( 0,0,1 );
    glm::vec3 target (0, 0, 0);
    glm::vec3 up (0, 1, 0);
    Matrices.view = glm::lookAt( eye, target, up ); // Rotating Camera for 3D
    glm::mat4 VP = Matrices.projection * Matrices.view;

    glm::mat4 MVP;  // MVP = Projection * View * Model
    for(auto i:rectangles)
    {
        i.draw(VP);
    }
    for(auto i:rectangles2)
    {
        i.draw(VP);
    }
    int j=0;
    tip.draw(VP);
    sluty.draw(VP);

    slut.draw(VP);
    for(auto i:coins)
    {
    	bounding_box_t a;
    	bounding_box_t b;
    	a.x = i.position.x;
    	a.y = i.position.y;
    	b.x = star1.position.x;
    	b.y = star1.position.y;
    	a.width = 0.2;
    	a.height = 0.2;
    	b.width = 0.9;
    	b.height = 0.9;
    	if(!detect_collision(a,b))
   		{
   			i.draw(VP);
   		}
   		else
   		{
   			coins.erase(coins.begin()+j);
   			score++;
   		}
   		j++;
    }
    j = 0;
    for(auto i:bonus)
    {
        bounding_box_t a;
        bounding_box_t b;
        a.x = i.position.x;
        a.y = i.position.y;
        b.x = star1.position.x;
        b.y = star1.position.y;
        a.width = 0.2;
        a.height = 0.2;
        b.width = 0.9;
        b.height = 0.9;
        if(!detect_collision(a,b))
        {
            i.draw(VP);
        }
        else
        {
            bonus.erase(bonus.begin()+j);
            score+=10;
        }
        j++;
    }
    j = 0;
    for(auto i:coins2)
    {
        bounding_box_t a;
        bounding_box_t b;
        a.x = i.position.x;
        a.y = i.position.y;
        b.x = star1.position.x;
        b.y = star1.position.y;
        a.width = 0.2;
        a.height = 0.2;
        b.width = 0.9;
        b.height = 0.9;
        if(!detect_collision(a,b))
        {
            i.draw(VP);
        }
        else
        {
            coins2.erase(coins2.begin()+j);
            score+=2;
        }
        j++;
    }
    j = 0;
    for(auto i:poly)
    {
    	bounding_box_t a;
    	bounding_box_t b;
    	a.x = i.position.x;
    	a.y = i.position.y;
    	b.x = star1.position.x;
    	b.y = star1.position.y;
    	a.width = 0.2;
    	a.height = 0.2;
    	b.width = 0.9;
    	b.height = 0.9;
        if(!detect_collision(a,b))
   		{
   			i.draw(VP);
   		}
   		else
   		{
            score+=5;
   			poly.erase(poly.begin()+j);
   			shield = 1;
			current_time = time(NULL);
   		}
   		j++;
    }
    star1.draw(VP);

    
    j = 0;
    for(auto i:fire_beams)
    {
        bounding_box_t a;
    	bounding_box_t b;
    	bounding_box_t c;

    	a.x = i.position.x+0.2;
    	a.y = i.position.y;
    	b.x = star1.position.x;
    	b.y = star1.position.y;
    	a.width = 0.5;
    	a.height = 0.02;
    	b.width = 0.8;
    	b.height = 0.8;
    	c.height = 0.5;
    	c.width = 0.5;
    	c.x = water_ball.position.x;
    	c.y = water_ball.position.y;
        if(detect_collision(a,b) && shield == 0 && farc == 0)
   		{
   			quit(window);
   		}
   		else if(detect_collision(a,c))
   		{
   			fire_beams.erase(fire_beams.begin()+j);
   		}
        i.draw(VP);
        j++;
    }
    j = 0;
    for(auto i:cr)
    {
        bounding_box_t a;
        bounding_box_t b;

        a.x = i.position.x;
        a.y = i.position.y;
        b.x = star1.position.x;
        b.y = star1.position.y;
        a.width = 0.15;
        a.height = 0.15;
        b.width = 0.8;
        b.height = 0.9;
        if(detect_collision(a,b) && shield == 0 && farc == 0 )
        {
            quit(window);
        }
        i.draw(VP);
        j++;
    }
    for(auto i:fire)
    {	
        i.draw(VP);
    }
    if (ignition == 1)
    {
        r.set_position(star1.position.x+0.3,star1.position.y-0.07);
        r2.set_position(star1.position.x-0.3,star1.position.y-0.07);
        r.draw(VP);
        r2.draw(VP);
    }
   	water_ball.draw(VP);
   	redball.draw(VP);
   	
   	bounding_box_t a;
	bounding_box_t b;
	a.x = redball.position.x;
	a.y = redball.position.y;
	b.x = star1.position.x;
	b.y = star1.position.y;
	a.width = 0.4;
	a.height = 0.4;
	b.width = 0.8;
	b.height = 0.8;
	

    if(detect_collision(a,b) && shield == 0 && farc == 0)
	{
		quit(window);
	}
    eye1.set_position(star1.position.x+0.3,star1.position.y+0.4);
    eye2.set_position(star1.position.x-0.3,star1.position.y+0.4);
    eye1.draw(VP);
    eye2.draw(VP);
    if(shield == 1)
    {
    	arc.position.x = star1.position.x;
    	arc.position.y = star1.position.y+0.1;

    }
    if (shield == 1 && time(NULL)-current_time>2)
    {
    	shield = 0;
    	arc.position.x = 10;
    	arc.position.y = 10;
    }
    arc.draw(VP);
    magnet.draw(VP);
    magnet2.draw(VP);
    // bounding_box_ a;
    // bounding_box_t b;
    a.x = boomerang.position.x;
    a.y = boomerang.position.y;
    b.x = star1.position.x;
    b.y = star1.position.y;
    a.width = 0.4;
    a.height = 0.4;
    b.width = 0.8;
    b.height = 0.8;
    if(detect_collision(a,b) && shield == 0 && boomerang_x_speed<0 && farc == 0)
    {
        quit(window);
    }
    a.x = slut.position.x-1.1;
    a.y = slut.position.y;
    b.x = star1.position.x;
    b.y = star1.position.y;
    a.width = 0.2;
    a.height = 0.2;
    b.width = 0.8;
    b.height = 0.8;
    if (detect_collision(a,b) )
    {
        farc = 1;   
    }
    

    if(magnet.position.x - star1.position.x > 0 &&  magnet.position.x - star1.position.x < 1.5 && star1.position.x<3.2 && farc==0 )
    {
         star1.position.x += (magnet.position.x+0.5 - star1.position.x)/40;
         if (star1.position.y <2)
         {
            magnef = 1;
             star1.position.y+=mag_speed;
             mag_speed+=0.0001;

         }
         else
         {
            magnef = 0;
            mag_speed = 0;
         }
    }
    else if (abs(magnet.position.x - star1.position.x) < 1.5 && star1.position.x>-3.2 && farc==0 && magnet.position.x - star1.position.x<0 )
    {
        star1.position.x += (magnet.position.x+0.5 - star1.position.x)/40;
        if (star1.position.y <2)
         {
            magnef = 1;

             star1.position.y+=mag_speed;
             mag_speed+=0.0001;
         }
         else
         {
            magnef = 0;
            mag_speed = 0;
         }

    }
    else
    {
        magnef = 0;
    }
    vicerious.draw(VP);
    for(auto i:magneticlines)
    {
        i.draw(VP);
    }
        string s;
        int temp = score;
        int unit = temp%10;
        temp = temp/10;
        int tens = temp%10; 
        if (unit==0)
        {
            s = "1111110";
        }
        else if (unit == 1)
        {
            s = "0110000";
        }else if (unit == 2)
        {
            s = "1101101";
        }else if (unit == 3)
        {
            s = "1111001";
        }else if (unit == 4)
        {
            s = "0110011";
        }else if (unit == 5)
        {
            s = "1011011";
        }else if (unit == 6)
        {
            s = "1011111";
        }else if (unit == 7)
        {
            s = "1110000";
        }else if (unit == 8)
        {
            s = "1111111";
        }else if (unit == 9)
        {
            s = "1111011";
        }
        if (tens==0)
        {
            s = s+"1111110";
        }
        if (tens == 1)
        {
            s = s+"0110000";
        }else if (tens == 2)
        {
            s = s+"1101101";
        }else if (tens == 3)
        {
            s = s+"1111001";
        }else if (tens == 4)
        {
            s = s+"0110011";
        }else if (tens == 5)
        {
            s = s+"1011011";
        }else if (tens == 6)
        {
            s = s+"1011111";
        }else if (tens == 7)
        {
            s = s+"1110000";
        }else if (tens == 8)
        {
            s = s+"1111111";
        }else if (tens == 9)
        {
            s = s+"1111011";
        }

        j = 0;
    for(auto i:digit)
    {
        if(s[j]=='1')
        {
            i.draw(VP);
        }

        j++;
    }
    boomerang.draw(VP);
    for(auto i:bonus)
    {
        i.draw(VP);
    } 
    
    for(auto i:wall)
    {
        i.draw(VP);
    }
}

void tick_input(GLFWwindow *window) {
    int left  = glfwGetKey(window, GLFW_KEY_LEFT);
    int right = glfwGetKey(window, GLFW_KEY_RIGHT);
    int w = glfwGetKey(window, GLFW_KEY_W);
    int d = glfwGetKey(window, GLFW_KEY_D);
    int a = glfwGetKey(window, GLFW_KEY_A);
    int f = glfwGetKey(window, GLFW_KEY_F);
    int g = glfwGetKey(window, GLFW_KEY_G);
    int m = glfwGetKey(window, GLFW_KEY_M);
    int n = glfwGetKey(window, GLFW_KEY_N);
    int space = glfwGetKey(window, GLFW_KEY_SPACE);
    if (farc == 0)
    {
       	if (w && star1.position.y<3.15)
        {
            ignition = 1;
            star1.position.y+=0.03;
            fall_speed = 0;
        }
        else if(magnef == 0)
        {
            ignition = 0;
            if(star1.position.y > ground_level-0.23)
            {
                star1.position.y -= fall_speed;
                fall_speed+=0.007;
            }
            else
            {
                star1.position.y = ground_level-0.23;
            }
        }
        if (d && star1.position.x<3.2)
        {
            star1.position.x+=0.03;
        
        }
        if (a && star1.position.x>-3.2)
        {
            star1.position.x-=0.03;
        
        }
    }
    else
    {
        // star1.position.x+=0.05;
        // if(saved == 10)
        // {
        //     saved = star1.position.x;
        // }
        // star1.position.y+= y_speed;
        // y_speed +=0.0022;
        // if (y_speed>0.05 && star1.position.x - saved > 2 )
        // {
        //     farc = 0;
        //     y_speed = -0.05;
        //     saved = 10;
        // }
        angle+=0.01;
        star1.position.x = slut.position.x + cos(angle);
        star1.position.y = slut.position.y + sin(angle);
        if (d && angle<=2*PI)
        {
            angle+=0.02;
            star1.position.x = slut.position.x + cos(angle);
            star1.position.y = slut.position.y + sin(angle);

        }
        else if(a && angle>=PI)
        {
            angle-=0.02;
            star1.position.x = slut.position.x+cos(angle);
            star1.position.y = slut.position.y+sin(angle);
        }
        else if(angle>2*PI || angle < 0)
        {
            farc = 0;
            angle = PI;
        }
    }

    if(space && !busy)
    {
    	water_ball.position.x = star1.position.x+ 1;
    	water_ball.position.y = star1.position.y+ 1;
    	shoot = 1;
    }
    else
    {

    	if(water_ball.position.y>-2.2)
	    {
	    	busy = 1;
		    water_ball.position.y += water_speed;
		    water_speed = water_speed -  0.0008f;
		}
		else
		{
            water_ball.position.y = -10;
			busy = 0;
			water_speed = 0.06;
		}
    }
    if(vicerious.position.x<6 && !busy1)
    {
    	redball.position.x = vicerious.position.x-0.4;
    	redball.position.y = vicerious.position.y-0.4;
    	busy1 = 1;
    }
    else
    {

	    if(redball.position.y>-3 )
	    {
	    	busy1 = 1;
		    redball.position.y += redspeed;
		    redball.position.x -= 0.04;
		    redspeed = redspeed -  0.0003f;
		}
		else
		{
	        redball.position.y = -10;
			busy1 = 0;
			redspeed = 0.0;
		}
	}

    if (m)
    {
        screen_zoom+=0.01;
        reset_screen();
    }
    if (n)
    {
        if(screen_zoom>1)
        screen_zoom-=0.01;
        reset_screen();
    }


}

void tick_elements() {
    boomerang_x_speed-=0.0004;
    boomerang_y_speed-=0.00045;
    boomerang.tick(boomerang_x_speed,boomerang_y_speed);
    
        slut.tick();
        sluty.tick();
        tip.tick();
    
    if (boomerang.position.y<-20)
    {
        boomerang_x_speed = 0.06;
        boomerang_y_speed = 0.06;
        boomerang.position.x = -2;
        boomerang.position.y = -1;
    }
    for(auto &i:coins)
    {
        i.tick();
    }for(auto &i:coins2)
    {
        i.tick();
    }
    for(auto &i:poly)
    {
        i.tick();
    }
    for(auto &i:rectangles)
    {
        i.tick();
    }
    for(auto &i:rectangles2)
    {
        i.tick();
    }
    for(auto &i:fire)
    {
        i.tick();
    }
    for(auto &i:bonus)
    {
        i.tick();
    }
    for(auto &i:cr)
    {
        i.tick();
    }

    for(auto &i:fire_beams)
    {
        i.tick(signal_firebeam);
        if (i.position.y>3)
        {
        	signal_firebeam = -1;
        }
        else if(i.position.y<-1)
        {
        	signal_firebeam = 1;
        }
    }
    water_ball.tick(0);
    magnet.tick();
    magnet2.tick();
    for(auto &i:magneticlines)
    {
        i.tick(0);
    }
    if (vicerious.position.y>3)
    {
    	signal_dragon = -1;
    }
    if(vicerious.position.y<1)
    {
    	signal_dragon = 1;
    }
    vicerious.tick(signal_dragon);
}

void initGL(GLFWwindow *window, int width, int height) {

    slut = circle(0,0,COLOR_BACKGROUND,50,1);
    sluty = circle(0,0,COLOR_RED,50,1.1);
    tip = polygon(-1.1,0,COLOR_GOLD,50);
   
    for (float i = 0; i < 2; ++i)
    {
        a = line(3-i/2-i/8-0.2,3.4,COLOR_GREEN,0);
        digit.push_back(a);

        a = line(3.5-i/2-i/8-0.2,3,COLOR_GREEN,90);
        digit.push_back(a);

        a = line(3.5-i/2-i/8-0.2,2.5,COLOR_GREEN,90);
        digit.push_back(a);

        a = line(3-i/2-i/8-0.2,2.5,COLOR_GREEN,0);
        digit.push_back(a);

        a = line(3-i/2-i/8-0.2,2.5,COLOR_GREEN,90);
        digit.push_back(a);

        a = line(3-i/2-i/8-0.2,3,COLOR_GREEN,90);
        digit.push_back(a);

        a = line(3-i/2-i/8-0.2,2.9,COLOR_GREEN,0);
        digit.push_back(a);
    }

    r =  tri(1, ground_level+1, COLOR_FLAME);
    r2 =  tri(1, ground_level+1, COLOR_FLAME);
    eye1 = polygon(1, ground_level+3, COLOR_BLACK,100);
    eye2 = polygon(1, ground_level+3, COLOR_BLACK,100);
    arc = semi(10,10,COLOR_GREY);
    water_ball = water_balloon(-100,-100,COLOR_Water,100);
    redball = water_balloon(-100,-100,COLOR_RED,100);
    magnet = Rect(1,2,COLOR_BLACK);
    magnet2 = Rect(2,2,COLOR_BLACK);
    boomerang = boom(-2,-2,COLOR_GREY);
    for (int i = 0; i < 30; ++i)
    {
        polygon p;
        float r = rand()%200;
        float e = rand()%300;
        r = r;
        e = e/100;
        
        for(float j=0;j<10;j++)
        {
            p = polygon(r+j/10, ground_level+2+e+j/10, COLOR_FLAME,40);
            cr.push_back(p);
        }
    }
    for (int i = 0; i < 10; ++i)
    {
        beams b;
        float f = i;
        b = beams(1.5,2+f/20, COLOR_Purple);
        magneticlines.push_back(b);
  
    }
    for (int i = 0; i < 10; ++i)
    {
        polygon p;
        float r = rand()%200;
        float e = rand()%300;
        r = r;
        e = e/100;
        p = polygon(r, ground_level+2+e, COLOR_GOLD,4);
        bonus.push_back(p);
    }
    vicerious = dragon(2,2,COLOR_Purple);
	for (int i = 0; i < 10; ++i)
    {
        fireline p;
        float r = rand()%200;
        float e = rand()%300;
        float h = rand()%30;
        r = r;
        e = e/100;
        p = fireline(r, ground_level+2+e, COLOR_GOLD,h+5,0.5);
        fire.push_back(p);

    }
    for (int i = 0; i < 30; ++i)
    {
        float r = rand()%200;
        float e = rand()%300;
        r = r;
        e = e/100;
        for (int i = 0; i < 10; ++i)
        {

        	beams b;
        	float f = i;
        	b = beams(r, ground_level+2+f/20, COLOR_GOLD);
        	fire_beams.push_back(b);
      
      	}

    }
    for (int i = 0; i < 30; ++i)
    {
        Rect R ;
        R = Rect(-4+i/3, ground_level-1, COLOR_BLACK);
        rectangles.push_back(R);
    }
    for (int i = 0; i < 20; ++i)
    {
        Rect R ;
        R = Rect(-3.7+i/2, ground_level+5.7, COLOR_GREY);
        wall.push_back(R);
    }
    for (int i = 0; i < 20; ++i)
    {
        Rect R ;
        R = Rect(-4.2+i/2, ground_level+5.7, COLOR_BLACK);
        wall.push_back(R);
    }
    for (int i = 0; i < 20; ++i)
    {
        Rect R ;
        R = Rect(3.7, ground_level+i/2, COLOR_GREY);
        wall.push_back(R);
    }
    for (int i = 0; i < 20; ++i)
    {
        Rect R ;
        R = Rect(3.7, ground_level+i/2-0.5, COLOR_BLACK);
        wall.push_back(R);
    }
    for (int i = 0; i < 20; ++i)
    {
        Rect R ;
        R = Rect(-4.2, ground_level+i/2, COLOR_GREY);
        wall.push_back(R);
    }
    for (int i = 0; i < 20; ++i)
    {
        Rect R ;
        R = Rect(-4.2, ground_level+i/2-0.5, COLOR_BLACK);
        wall.push_back(R);
    }

    for (int i = 0; i < 40; ++i)
    {
        polygon p;
        float r = rand()%400;
        float e = rand()%300;
        r = r;
        e = e/100;
        p = polygon(r, ground_level+2+e, COLOR_CHOC,5);
        poly.push_back(p);
    }

    for (int i = 0; i < 70; ++i)
    {
        polygon p;
        float r = rand()%200;
        float e = rand()%300;
        r = r;
        e = e/100;
        if(i%2==0)
        {
            p = polygon(r, ground_level+2+e, COLOR_GOLD,100);
            coins2.push_back(p);

        }
    	else
        {   
            p = polygon(r, ground_level+2+e, COLOR_BLACK,100);
            coins.push_back(p);

        }


    }
    for (int i = 0; i < 30; ++i)
    {
        Rect R ;
        R = Rect(-3.5+i/3, ground_level-1, COLOR_RED);
        rectangles2.push_back(R);
    }
    for (int i = 0; i < 30; ++i)
    {
        Rect R ;
        R = Rect(-4+i/3, ground_level-1.5, COLOR_RED);
        rectangles.push_back(R);
    }
    for (int i = 0; i < 30; ++i)
    {
        Rect R ;
        R = Rect(-3.5+i/3, ground_level-1.5, COLOR_BLACK);
        rectangles2.push_back(R);
    }
    for (int i = 0; i < 30; ++i)
    {
        Rect R ;
        R = Rect(-4+i/3, ground_level-2, COLOR_BLACK);
        rectangles.push_back(R);
    }
    for (int i = 0; i < 30; ++i)
    {
        Rect R ;
        R = Rect(-3.5+i/3, ground_level-2, COLOR_RED);
        rectangles2.push_back(R);
    }
    star1       = Star(-2, ground_level, COLOR_JET);

    // Create and compile our GLSL program from the shaders
    programID = LoadShaders("Sample_GL.vert", "Sample_GL.frag");
    // Get a handle for our "MVP" uniform
    Matrices.MatrixID = glGetUniformLocation(programID, "MVP");


    reshapeWindow (window, width, height);

    // Background color of the scene
    glClearColor (COLOR_BACKGROUND.r / 256.0, COLOR_BACKGROUND.g / 256.0, COLOR_BACKGROUND.b / 256.0, 0.0f); // R, G, B, A
    glClearDepth (1.0f);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LEQUAL);

    cout << "VENDOR: " << glGetString(GL_VENDOR) << endl;
    cout << "RENDERER: " << glGetString(GL_RENDERER) << endl;
    cout << "VERSION: " << glGetString(GL_VERSION) << endl;
    cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
}


int main(int argc, char **argv) {
    srand(time(0));
    int width  = 600;
    int height = 600;

    window = initGLFW(width, height);

    initGL (window, width, height);

    /* Draw in loop */
    while (!glfwWindowShouldClose(window)) {
        // Process timers

        if (t60.processTick()) 
        {
            // 60 fps
            // OpenGL Draw commands
            draw();
            // Swap Frame Buffer in double buffering
            glfwSwapBuffers(window);

            tick_elements();
            tick_input(window);
        }

        // Poll for Keyboard and mouse events
        glfwPollEvents();
    }

    quit(window);
}

bool detect_collision(bounding_box_t a, bounding_box_t b) {
    return (abs(a.x - b.x) * 2 < (a.width + b.width)) &&
           (abs(a.y - b.y) * 2 < (a.height + b.height));
}

void reset_screen() {
    float top    = screen_center_y + 4 / screen_zoom;
    float bottom = screen_center_y - 4 / screen_zoom;
    float left   = screen_center_x - 4 / screen_zoom;
    float right  = screen_center_x + 4 / screen_zoom;
    Matrices.projection = glm::ortho(left, right, bottom, top, 0.1f, 500.0f);
}
