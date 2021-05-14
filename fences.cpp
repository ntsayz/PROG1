#include <iostream>
#include <fstream> // library for file handling
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unistd.h>
#include <iterator>
#include <thread>
#include <queue>
#include <tuple>
#include <cstdlib>
#include <climits>
#include <tuple>
#include <cmath>
#include <math.h>
#include <time.h>
#include <iomanip>

using namespace std;
// using namespace std::chrono;
// using namespace std::chrono;
// using namespace std::chrono;
// using namespace std::chrono;



struct Player {
  string username;
  bool is_alive;
  bool continuar;
  int score;
  bool win;
};


//30 de 04

char charValidation();
short menu();
void getRules();
void getLeaderboard();
void fail();
void openFail();
bool pushtoLeaderboard();
short getMenuChoice();
void clearScreen();
void getIndex(vector<char> v, char K);
void loadMaze(string MAZE_FILE, vector <vector<char> >& maze);
template<class T>
void printVector(std::vector<std::vector<T> > const &matrix);
void loadGame(Player& player,vector <vector<char> >& maze, short& player_posX, short& player_posY,short& robot_posX, short& robot_posY);
bool CanMoveOrCanNot(char& pos, Player& player);
void goDown(Player& player,short& curr_posX,short& curr_posY, vector <vector<char> >& maze);
void goDownRobot(Player& player,short& robot_posX,short& robot_posY, vector <vector<char> >& maze);
void goUpRobot(Player& player,short& robot_posX,short& robot_posY,vector <vector<char> >& maze);
void goUp(Player& player,short& curr_posX,short& curr_posY,vector <vector<char> >& maze);
void goLeftRobot(Player& player,short& robot_posX,short& robot_posY,vector< vector <char> >& maze);
void goLeft(Player& player,short& curr_posX,short& curr_posY,vector< vector <char> >& maze);
void goRight(Player& player,short& curr_posX,short& curr_posY,vector <vector<char> >& maze);
void goRightRobot(Player& player,short& robot_posX,short& robot_posY,vector <vector<char> >& maze);
void loadPlayerPos(vector <vector<char> >& maze, short& player_posY, short& player_posX);
void robotColision(Player& player,short& curr_posX,short& curr_posY,char& pos, vector <vector<char> >& maze);
void playerMove(Player& player, vector <vector<char> >& maze, short& player_posX, short& player_posY);
void RobotPath(Player& player,vector <vector<char> >& maze, short& player_posX, short& player_posY, short& robot_posX, short& robot_posY);
void calculateDistanceAndGo(Player& player,vector <vector<char> >& maze, short& player_posX, short& player_posY, short& robot_posX, short& robot_posY);
void getPlayerInfo(Player& player,string& MAZE_FILE);
void goDownLeft(Player& player,short& curr_posX,short& curr_posY, vector <vector<char> >& maze);
void goUpLeft(Player& player,short& curr_posX,short& curr_posY,vector <vector<char> >& maze);
void goDownRight(Player& player,short& curr_posX,short& curr_posY, vector <vector<char> >& maze);
void goUpRight(Player& player,short& curr_posX,short& curr_posY,vector <vector<char> >& maze);
short menu1();

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
    os << "[";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i];
        if (i != v.size() - 1)
            os << "";
    }
    os << "]";
    return os;
}



int main(){
    std::vector<std::vector<char> > maze; 
    char aw;
    short player_posX = 0, player_posY = 0, op,op1, robot_posX = 0,robot_posY = 0;
    bool isPlaying = true;
    Player player;
    player.win = false;
   

    string MAZE_FILE = "MAZE_01.TXT";

    do{
        op = menu();
        switch(op){
            
            case 1:
                loadMaze(MAZE_FILE,maze);
                getRules();
                cout << "Do you understand the rules ?(Y/N)" << endl;

                aw = charValidation();
                if (aw =='y' || aw == 'Y'){
                    clearScreen();
                    break;
                }
                clearScreen();
                    
                break;
                
            case 2:
                clearScreen();
                getPlayerInfo(player,MAZE_FILE);
                clearScreen();
                do{
                    op1 = menu1();
                    switch(op1){
                        case 1:
                            player.is_alive = true;
                            loadMaze(MAZE_FILE,maze);
                            loadPlayerPos(maze,player_posX, player_posY);

                            while(player.is_alive){
                                loadGame(player,maze, player_posX, player_posY,robot_posX,robot_posY);

                            }  
                            maze[player_posY][player_posX] = 'h';
                            printVector(maze);
                            break;
                        case 2:
                            break;
                        default:
                            fail();       
                    }
                            

                }while(op1!=2);
                break;
            case 3:
                isPlaying = false;
                break;

            case 4:
                getPlayerInfo(player,MAZE_FILE);
                loadMaze(MAZE_FILE,maze);
                loadPlayerPos(maze,player_posX, player_posY);
                player.is_alive = true;

                do{
                    loadGame(player,maze, player_posX, player_posY,robot_posX,robot_posY);

                    if (player.is_alive == false){
                        cout << "you died" << endl;

                    }
                }while(player.is_alive);
                maze[player_posY][player_posX] = 'h';
                printVector(maze);
                cout << "your score is " << player.score << endl;
                
                break;
                
            default :
                fail();
        }
        
    }while(isPlaying);

    return 0;
}

void getPlayerInfo(Player& player,string& MAZE_FILE){
    string x;
    cout << "Insert your name\n-->" << endl;
    cin >> player.username;
    cout << "Insert the number of the maze that you want to play (eg:. 01,12,27)\nIt has to exist in this directory\n-->" << endl;
    cin >> x;
    MAZE_FILE = "MAZE_" + x + ".TXT";

}

template<class T>
void printVector(std::vector<std::vector<T> > const &matrix) {
    for (std::vector<T> row: matrix)
    {
        for (T val: row) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}
void loadMaze(string MAZE_FILE, vector< vector<char> >& maze) {
    std::string line;
    std::ifstream infile(MAZE_FILE);

    while (std::getline(infile, line)) {
        std::vector<char> row;

        for (char &c : line) {
            row.push_back(c);
        }

        maze.push_back(row);
    }
    printVector(maze);
    if (maze.size() >1){
        clearScreen();
    }else{
        openFail();
    }
    cout << endl;
}

void getRules(){
    string FILE_NAME = "MAZE_RULES.TXT";
    char lines;
    fstream rulesFile;
    
    rulesFile.open(FILE_NAME, ios::in); // opens file
            
    if (!rulesFile){                            // checks if file exists
        openFail();
    }
    else{
                
        while (1){                               // reads all content in file
            rulesFile >> std::noskipws>> lines;  

            if(rulesFile.eof()){                // if the file reaches its end, stop
                break;
            }
            cout << lines;
        }
    }
    rulesFile.close();
    cout << endl;
}

void fail(){
    
    cerr << "SOMETHING WENT WRONG" << endl;
}

void openFail(){
    cerr << "ERROR: FILE COULD NOT BE FOUND!" << endl;
}

short menu(){
    short menuInput;
    do{

        cout << "----------MENU-----------\n1-RULES\n2-GO\n3-EXIT\n-------------------------" << endl;

        menuInput = getMenuChoice();
        

        if(menuInput < 0 || menuInput > 5){
            
            cout << "ERROR: FAULTY INPUT...TRY AGAIN"<<endl;
        }

    }while(menuInput < 0 || menuInput >= 5);

    return menuInput;
}
short menu1(){
    short menuInput;
    do{

        cout << "-------------------------\n1-PLAY\n2-EXIT\n-------------------------" << endl;

        menuInput = getMenuChoice();
        

        if(menuInput < 0 || menuInput > 2){
            
            cout << "ERROR: FAULTY INPUT...TRY AGAIN"<<endl;
        }

    }while(menuInput < 0 || menuInput > 2);

    return menuInput;
}


/*
bool pushtoLeaderboard(Player player){ // TODO: garantir que data foi pushed to lb antes de continuar

    ofstream my_file;
    std::vector<int> v;
    
    my_file.open("MAZE_02_WINNERS.TXT", ios::out | ios::app);
    
    if(!my_file)
    {
        cout <<"File not found";
    }
    else
    {
        typedef std::pair <string,int>pair_pair;
        std::vector<pair_pair>pairs;
        pairs.push_back(std::make_pair(player.username,player.score));
        for(int i = 0 ; i <=pairs.size();i++)
        {
            my_file << pairs[i].first <<setw(12)<< pairs[i].second << endl;
            //v.push_back(pairs[i].second);
        }
        //int index=std::max_element(v.begin(), v.end())-v.begin();
        
        my_file.close();
        
        FILE *fp;
        fp=fopen("MAZE_02_WINNERS.txt","a+");
        char names[pairs.size()];
        int scores;



        f(fp !=NULL)
        {
            fscanf(fp,"%s %i",names,&scores);
            for(int i=0;i<pairs.size();i++)
            {
                //fprintf(fp,"%s        %i\n",pairs[i].first.c_str(),pairs[i].second);
                fscanf(fp,"%s %i",pairs[i].first.c_str(),pairs[i].second);
                if(pairs[i].first)
            }
        }


    }

        if(my_file.eof)
        {
            return true;
        }

    // //funcao to  


}
*/
void getLeaderboard(){
    ifstream f;

    f.open("MAZE_02_WINNERS.TXT");

    if (!f.is_open()){

        openFail();
    }
    cout << "ya";
}
short getMenuChoice(){

    short menuChoice;

    cout << "-->";
    cin >> menuChoice;

    while(std::cin.good()==false){
        cout << "ERROR: Faulty input...Try again!"<<endl;

        std::cin.clear();
        std::cin.ignore(2 , '\n');

        cout << "-->";
        cin >> menuChoice;
    }

    return menuChoice;
}
char charValidation(){

    char input;

    cout << "-->";
    cin >> input;

    while(std::cin.good()==false){
        cout << "ERROR: Faulty input...Try again!"<<endl;

        std::cin.clear();
        std::cin.ignore(4 , '\n');

        cout << "-->";
        cin >> input;
    }

    return input;

}




void clearScreen(){

  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

void goLeft(Player& player,short& curr_posX,short& curr_posY,vector< vector <char> >& maze){
    
    char pos = maze[curr_posY][curr_posX-1];
    
    if (curr_posX-1!=0){  //still not sure se pode ir pra fence desliagda + mudar esses valores que y tem que ser maior, menor ou igual a   {  

        if(maze[curr_posY][curr_posX] == 'H'){

            if(CanMoveOrCanNot(pos,player)){
                maze[curr_posY][curr_posX-1] = 'H';
                maze[curr_posY][curr_posX] = ' ';
                curr_posX = curr_posX-1;
                curr_posY = curr_posY;
            }else{
                cout << "try again" << endl;
                maze[curr_posY][curr_posX] = 'H';
                curr_posX = curr_posX;
                curr_posY = curr_posY;
            }
        }
    }
    else{
        if(pos == 'r'){
            cout << "try again" << endl;
            maze[curr_posY][curr_posX] = 'H';
            curr_posX = curr_posX;
            curr_posY = curr_posY;
            player.continuar = false;
        }
        else if(pos == '*'){
            player.is_alive = false;
        }
    }
   
}

void goLeftRobot(Player& player,short& robot_posX,short& robot_posY,vector< vector <char> >& maze){

    
    char pos = maze[robot_posY][robot_posX-1];
    
    if (robot_posX-1!=0){ 

        if(maze[robot_posY][robot_posX-1] == 'R'){

            
            if(pos == 'r' || pos == 'R' || pos == '*'){
                maze[robot_posY][robot_posX-1] = 'r';
                maze[robot_posY][robot_posX] = ' ';
            
            }else if(pos == 'P'){
                maze[robot_posY][robot_posX-1] = 'h';
                maze[robot_posY][robot_posX] = 'R';
                player.is_alive = false;

            }
            else{
                maze[robot_posY][robot_posX-1] = 'R';
                maze[robot_posY][robot_posX] = ' ';
            }
            robot_posX = robot_posX-1;
            robot_posY = robot_posY;
            
        }

    
    }
    else{

        if(pos == 'r' || pos == 'R' || pos == '*'){
            maze[robot_posY][robot_posX-1] = 'r';
            maze[robot_posY][robot_posX] = ' ';
            robot_posX = robot_posX-1;
            robot_posY = robot_posY;
        }
    }
   
}


void goRight(Player& player,short& curr_posX,short& curr_posY,vector <vector<char> >& maze) {// nao devia ser startx porcausa de quando a funcao for called ???? { 
    
    char pos = maze[curr_posY][curr_posX+1];
    
    if (curr_posX+1!=19){ // still not sure se pode ir pra fence desliagda + mudar esses valores que y tem que ser maior, menor ou igual a { 
        
        if(maze[curr_posY][curr_posX] == 'H'){

            if(CanMoveOrCanNot(pos,player)){
                maze[curr_posY][curr_posX+1] = 'H';
                maze[curr_posY][curr_posX] = ' ';
                curr_posX = curr_posX+1;
                curr_posY = curr_posY;
            }else{
                cout << "try again" << endl;
                maze[curr_posY][curr_posX] = 'H';
                curr_posX = curr_posX;
                curr_posY = curr_posY;
            }
            
        }
    }
    else{
        if(pos == 'r'){
            cout << "try again" << endl;
            maze[curr_posY][curr_posX] = 'H';
            curr_posX = curr_posX;
            curr_posY = curr_posY;
            
        }
        else if(pos == '*'){
            player.is_alive = false;
        }
    }
}

void goRightRobot(Player& player,short& robot_posX,short& robot_posY,vector <vector<char> >& maze){ // nao devia ser startx porcausa de quando a funcao for called ???? { 
    
    char pos = maze[robot_posY][robot_posX+1];
    
    if (robot_posX+1!=19){ // still not sure se pode ir pra fence desliagda + mudar esses valores que y tem que ser maior, menor ou igual a { 
        
        if(maze[robot_posY][robot_posX] == 'R'){

            
            if (pos == 'r' || pos == 'R' || pos == '*'){
                maze[robot_posY][robot_posX+1] = 'r';
                maze[robot_posY][robot_posX] = ' ';

            }else if(pos == 'P'){
                maze[robot_posY][robot_posX+1] = 'h';
                maze[robot_posY][robot_posX] = 'R';
                player.is_alive = false;

            }
            else{
                maze[robot_posY][robot_posX+1] = 'R';
                maze[robot_posY][robot_posX] = ' ';
            }

            robot_posX = robot_posX+1;
            robot_posY = robot_posY;
    }    }

    else{

        if(pos == 'r' || pos == 'R' || pos == '*'){
            maze[robot_posY][robot_posX+1] = 'r';
            maze[robot_posY][robot_posX] = ' ';
            robot_posX = robot_posX+1;
            robot_posY = robot_posY;
        }
       
    }
}


void goUp(Player& player,short& curr_posX,short& curr_posY,vector <vector<char> >& maze){ // nao devia ser startx porcausa de quando a funcao for called ???? { 
    
    char pos = maze[curr_posY-1][curr_posX];

    
    if (curr_posY-1!=0){ // still not sure se pode ir pra fence desliagda + mudar esses valores que y tem que ser maior, menor ou igual a  { 
        
        if(maze[curr_posY][curr_posX] == 'H'){

            if(CanMoveOrCanNot(pos,player)){
                maze[curr_posY-1][curr_posX] = 'H';
                maze[curr_posY][curr_posX] = ' ';
                curr_posX = curr_posX;
                curr_posY = curr_posY-1;
            }else{
                cout << "try again" << endl;
                maze[curr_posY][curr_posX] = 'H';
                curr_posX = curr_posX;
                curr_posY = curr_posY;
            }
            
        }
        
    }
    else{
        if(pos == 'r'){
    
            cout << "try again" << endl;
            maze[curr_posY][curr_posX] = 'H';
            curr_posX = curr_posX;
            curr_posY = curr_posY;  
            player.continuar = false;
        }
        else if(pos == '*'){
            player.is_alive = false;
        }
    }

}

void goUpRobot(Player& player,short& robot_posX,short& robot_posY,vector <vector<char> >& maze){ 
    
    char pos = maze[robot_posY-1][robot_posX];

    
    if ((robot_posY-1)!=0){ 
        
       if (maze[robot_posY][robot_posX] == 'R'){

            if(pos == 'r' || pos == 'R' || pos == '*')
            {
                maze[robot_posY-1][robot_posX] = 'r';
                maze[robot_posY][robot_posX] = ' ';
                robot_posX = robot_posX;
                robot_posY = robot_posY-1;

            }else if(pos == 'H'){
                maze[robot_posY+1][robot_posX] = 'h';
                maze[robot_posY][robot_posX] = 'R';
                player.is_alive = false;

            }
            else{
                maze[robot_posY-1][robot_posX] = 'R';
                maze[robot_posY][robot_posX] = ' ';
                robot_posX = robot_posX;
                robot_posY = robot_posY-1;
            }
        }
        
    }else {
        if(pos == 'r' || pos == 'R' || pos == '*'){
            maze[robot_posY-1][robot_posX] = 'r';
            maze[robot_posY][robot_posX] = ' ';
            robot_posX = robot_posX;
            robot_posY = robot_posY-1;
        }
        
    }

}

void goDown(Player& player,short& curr_posX,short& curr_posY, vector <vector<char> >& maze){ // nao devia ser startx porcausa de quando a funcao for called ???? { 
    
    char pos = maze[curr_posY+1][curr_posX];

    if (curr_posY+1!=9){ // still not sure se pode ir pra fence desliagda + mudar esses valores que y tem que ser maior, menor ou igual a  { 
        
        if(maze[curr_posY][curr_posX] == 'H'){

            if(CanMoveOrCanNot(pos,player)){
                maze[curr_posY+1][curr_posX] = 'H';
                maze[curr_posY][curr_posX] = ' ';
                curr_posX = curr_posX;
                curr_posY = curr_posY+1;
            }else{
                cout << "try again" << endl;
                maze[curr_posY][curr_posX] = 'H';
                curr_posX = curr_posX;
                curr_posY = curr_posY;
            }
            
        }
    }
    else{
        if(pos == 'r'){
            cout << "try again" << endl;
            maze[curr_posY][curr_posX] = 'H';
            curr_posX = curr_posX;
            curr_posY = curr_posY;
            player.continuar = false;
        }
        else if(pos == '*'){
            player.is_alive = false;
        }
    }

}

void goDownLeft(Player& player,short& curr_posX,short& curr_posY, vector <vector<char> >& maze){ // nao devia ser startx porcausa de quando a funcao for called ???? { 
    
    char pos = maze[curr_posY+1][curr_posX-1];

    if (curr_posY+1!=9){ // still not sure se pode ir pra fence desliagda + mudar esses valores que y tem que ser maior, menor ou igual a  { 
        
        if(maze[curr_posY][curr_posX] == 'H'){

            if(CanMoveOrCanNot(pos,player)){
                maze[curr_posY+1][curr_posX-1] = 'H';
                maze[curr_posY][curr_posX] = ' ';
                curr_posX = curr_posX-1;
                curr_posY = curr_posY+1;
            }else{
                cout << "try again" << endl;
                maze[curr_posY][curr_posX] = 'H';
                curr_posX = curr_posX;
                curr_posY = curr_posY;
            }
            
        }
        
    }
    else{
        if(pos == 'r'){
            cout << "try again" << endl;
            maze[curr_posY][curr_posX] = 'H';
            curr_posX = curr_posX;
            curr_posY = curr_posY;
            player.continuar = false;
        }
        else if(pos == '*'){
            player.is_alive = false;
        }
    }

}

void goUpLeft(Player& player,short& curr_posX,short& curr_posY,vector <vector<char> >& maze){ // nao devia ser startx porcausa de quando a funcao for called ???? { 
    
    char pos = maze[curr_posY-1][curr_posX-1];

    
    if (curr_posY-1!=0){ // still not sure se pode ir pra fence desliagda + mudar esses valores que y tem que ser maior, menor ou igual a  { 
        
        if(maze[curr_posY][curr_posX] == 'H'){

            if(CanMoveOrCanNot(pos,player)){
                maze[curr_posY-1][curr_posX-1] = 'H';
                maze[curr_posY][curr_posX] = ' ';
                curr_posX = curr_posX-1;
                curr_posY = curr_posY-1;
            }else{
                cout << "try again" << endl;
                maze[curr_posY][curr_posX] = 'H';
                curr_posX = curr_posX;
                curr_posY = curr_posY;
            }
            
        }
        
    }
    else{
        if(pos == 'r'){
            cout << "try again" << endl;
            maze[curr_posY][curr_posX] = 'H';
            curr_posX = curr_posX;
            curr_posY = curr_posY;
            player.continuar = false;
        }
        else if(pos == '*'){
            player.is_alive = false;
        }
    }

}

void goDownRight(Player& player,short& curr_posX,short& curr_posY, vector <vector<char> >& maze){ // nao devia ser startx porcausa de quando a funcao for called ???? { 
    
    char pos = maze[curr_posY+1][curr_posX+1];

    if (curr_posY+1!=9){ // still not sure se pode ir pra fence desliagda + mudar esses valores que y tem que ser maior, menor ou igual a  { 
        
        if(maze[curr_posY][curr_posX] == 'H'){

            if(CanMoveOrCanNot(pos,player)){
                maze[curr_posY+1][curr_posX+1] = 'H';
                maze[curr_posY][curr_posX] = ' ';
                curr_posX = curr_posX+1;
                curr_posY = curr_posY+1;
            }else{
                cout << "try again" << endl;
                maze[curr_posY][curr_posX] = 'H';
                curr_posX = curr_posX;
                curr_posY = curr_posY;
            }
            
        }
        
    }
    else{
        if(pos == 'r'){
            cout << "try again" << endl;
            maze[curr_posY][curr_posX] = 'H';
            curr_posX = curr_posX;
            curr_posY = curr_posY;
            player.continuar = false;
        }
        else if(pos == '*'){
            player.is_alive = false;
        }
    }

}

void goUpRight(Player& player,short& curr_posX,short& curr_posY,vector <vector<char> >& maze){ // nao devia ser startx porcausa de quando a funcao for called ???? { 
    
    char pos = maze[curr_posY-1][curr_posX+1];

    
    if (curr_posY-1!=0){ // still not sure se pode ir pra fence desliagda + mudar esses valores que y tem que ser maior, menor ou igual a  { 
        
        if(maze[curr_posY][curr_posX] == 'H'){

            if(CanMoveOrCanNot(pos,player)){
                maze[curr_posY-1][curr_posX+1] = 'H';
                maze[curr_posY][curr_posX] = ' ';
                curr_posX = curr_posX+1;
                curr_posY = curr_posY-1;
            }else{
                cout << "try again" << endl;
                maze[curr_posY][curr_posX] = 'H';
                curr_posX = curr_posX;
                curr_posY = curr_posY;
            }
            
        }
        
    }
    else{
        if(pos == 'r'){
            cout << "try again" << endl;
            maze[curr_posY][curr_posX] = 'H';
            curr_posX = curr_posX;
            curr_posY = curr_posY;
            player.continuar = false;
        }
        else if(pos == '*'){
            player.is_alive = false;
        }
    }

}


void goDownRobot(Player& player,short& robot_posX,short& robot_posY, vector <vector<char> >& maze){ // nao devia ser startx porcausa de quando a funcao for called ???? { 
    
    char pos = maze[robot_posY+1][robot_posX];

    if (robot_posY+1!=9){ // still not sure se pode ir pra fence desliagda + mudar esses valores que y tem que ser maior, menor ou igual a  { 
        
        if(maze[robot_posY][robot_posX] == 'R'){

            if(pos == 'r' || pos == 'R' || pos == '*'){
                maze[robot_posY+1][robot_posX] = 'r';
                maze[robot_posY][robot_posX] = ' ';
                robot_posX = robot_posX;
                robot_posY = robot_posY+1;
            }else if(pos == 'H'){
                maze[robot_posY+1][robot_posX] = 'X';
                maze[robot_posY][robot_posX] = 'R';
                player.is_alive = false;

            }
            else{
                maze[robot_posY+1][robot_posX] = 'R';
                maze[robot_posY][robot_posX] = ' ';
                robot_posX = robot_posX;
                robot_posY = robot_posY+1;
            }
            
               
        }
        
    }
    else 
    {
        if(pos == 'r' || pos == 'R' || pos == '*'){
            maze[robot_posY+1][robot_posX] = 'r';
            maze[robot_posY][robot_posX] = ' ';
            robot_posX = robot_posX;
            robot_posY = robot_posY+1;
        }
    }

}



void getIndex(vector<char> v, char K, short& player_posX)
{
    auto it = find(v.begin(), v.end(), K);
 
    // If element was found
    if (it != v.end())
    {
     
        // calculating the index
        // of K
        player_posX = it - v.begin();
        cout << player_posX  << endl;
    }
    else {
        // If the element is not
        // present in the vector
        cout << "-1" << endl;
    }
    
}


void loadPlayerPos(vector <vector<char> >& maze, short& player_posX, short& player_posY){
    
    for (int i = 0; i < maze.size(); i++)
    {
        for (int j = 0; j < maze[i].size(); j++)
        {
            if(maze[i][j] == 'H' ){
               getIndex(maze[i],'H',player_posX );
               player_posY = i;
               //cout << "The player position is x: " << player_posX << " y: " << player_posY << endl;
                
            }
        }   
    }

}



void loadGame(Player& player, vector <vector<char> >& maze, short& player_posX, short& player_posY, short& robot_posX, short& robot_posY){
    
    
    printVector(maze);
    playerMove(player, maze, player_posX, player_posY);
    calculateDistanceAndGo(player,maze,player_posX,player_posY,robot_posX, robot_posY);
    RobotPath(player, maze, player_posX, player_posY, robot_posX, robot_posY);
    clearScreen();

}

void playerMove(Player& player, vector <vector<char> >& maze, short& player_posX, short& player_posY){
    //cout << "playermove" << endl;
    short move = charValidation();
    switch (move){
        case 'W':
        case 'w':
            goUp(player, player_posX,player_posY, maze);
            break;
        case 'X':
        case 'x':
            goDown(player, player_posX,player_posY, maze);
            break;
        case 'D':
        case 'd':
            goRight(player, player_posX,player_posY, maze);
            break;
        case 'A':
        case 'a':
            goLeft(player, player_posX,player_posY, maze);
            break;
        case 'Q':
        case 'q':
            goUpLeft(player, player_posX, player_posY, maze);
            break;
        case 'Z':
        case 'z':
            goDownLeft(player, player_posX, player_posY, maze);
            break;
        case 'E':
        case 'e':
            goUpRight(player, player_posX,player_posY, maze);
            break;
        case 'C':
        case 'c':
            goDownRight(player, player_posX,player_posY, maze);
            break;
        case 'S':
        case 's':
            break;
        case 'I':
        case 'i':
            //player.is_alive = false;
        default:
            break;
    }
    clearScreen();
    

}


bool CanMoveOrCanNot(char& pos, Player& player){

    switch (pos){
        case ' ':
            //cout << "Valid Move " << endl;
            break;
        case '*':
            cout << "you died" << endl;
            player.is_alive = false;
            player.continuar = false;
            break;
        case 'R':
            player.is_alive = false;
            player.continuar = false;
        case 'r':
            cout << "Invalid move , try again" << endl;
            player.continuar = false;
            break; 
    }
    return player.is_alive;
}


void RobotPath(Player& player,vector <vector<char> >& maze, short& player_posX, short& player_posY, short& robot_posX, short& robot_posY){
    if (player_posX == robot_posX){
        if (player_posY < robot_posY){
            goUpRobot(player, robot_posX,robot_posY, maze);
        }
        else{ // curr_posY > curr_posY
            goDownRobot(player,robot_posX,robot_posY, maze);
        }
    }
    else if (player_posY == robot_posY){
        if (player_posX < robot_posX){
            goLeftRobot(player, robot_posX,robot_posY, maze);
        }
        else{
            goRightRobot(player, robot_posX,robot_posY, maze);
        }
    }
    else if ((player_posX != robot_posX) && (player_posY != robot_posY)){
        if ((player_posX > robot_posX) && (player_posY < robot_posY)){
            goUpRobot(player, robot_posX,robot_posY, maze);
            goRightRobot(player, robot_posX,robot_posY, maze);
        }
        else if ((player_posX > robot_posX) && (player_posY > robot_posY)){
            goDownRobot(player, robot_posX,robot_posY, maze);
            goRightRobot(player, robot_posX,robot_posY, maze);
        }
        else if ((player_posX < robot_posX) && (player_posY < robot_posY)){
            goUpRobot(player, robot_posX,robot_posY, maze);
            goLeftRobot(player, robot_posX,robot_posY, maze);
        }
        else if ((player_posX < robot_posX) && (player_posY > robot_posY)){
            goDownRobot(player, robot_posX,robot_posY, maze);
            goLeftRobot(player, robot_posX,robot_posY, maze);
        }
    }
}

void calculateDistanceAndGo(Player& player,vector <vector<char> >& maze, short& player_posX, short& player_posY, short& robot_posX, short& robot_posY){
    
    for (short i = 0; i < maze.size(); i++)
    {
        for (short j = 0; j < maze[i].size() ; j++){

            if(maze[i][j] == 'R'){
               robot_posX = j;
               robot_posY = i;
               break;
            }
            else if(maze[i][j] == ' '|| maze[i][j] == '*'|| maze[i][j] == 'H'|| maze[i][j] == 'r' ||maze[i][j] == 'h'){

                cout << "CONGRATULATIONS, YOU HAVE DEFEATED THE EVIL ROBOTS!!!" << endl;
                player.win = true;
            }
            
        }
    }

}
