int H_score,current_score=0,z=0; //High Score

char name[100];

int menu(int width,int height); // Main Menu

int show_high_score(int &a); //High Score File

int get_option(int mx, int my,int width,int height); // Button Option

int detect_mouseclick(int &mx, int &my); //Check mouse position

int select_action(int option_no,int screen_width,int screen_height); //Mouse click option

int update_h_score(); //Add new high score

int help(); //Instruction

int interface_page(); //Background

int set_bg_color(int color);

int mx,my,width=200,height=70;

void screen();

int shoot(int &x); //Arrow shooting

int SCORE(int &arrowleft, int dart); //Count Score

int dartboardup(int &dart); //Upward speed of dartboard

int dartboarddown(int &dart); //Downward speed of dartboard

int Play(); //Level

int exit();

int draw_arrow_box(int &s);


/* These functions are for Level-02 */

int level02();

void dartboard();

double dartBoardL2(double dart);

double Score(double dart,double x1,double B1);

void arch();

int cnttime(); //timmer

int show_total_score();

int gameover();

void high_score(double score1);

char pnam_add();

void high_score(double score1);

double show_high_score(double score1);

