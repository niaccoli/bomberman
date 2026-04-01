#include <curses.h>
//#include <ncurses.h>

class Map{
protected:
    int rows;
    int cols;
    char** grid;
    WINDOW* win;

public:
    //costruttore
    Map(int h, int w, int start_y, int start_x);

    void initialize_map(int levelID);
    
    void stamp_map();

    bool isWalkable(int y, int x);

    void breakWall();

    WINDOW* getWin();
};