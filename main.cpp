#include <iostream>
#include <fstream> // library for file handling
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unistd.h>
#include <iterator>
// #include <thread>
#include <queue>
#include <tuple>
#include <cstdlib>
#include <climits>




//27 de 04
using namespace std;

char charValidation();
short menu();
void getRules();
void getLeaderboard();
void fail();
void openFail();
bool pushtoLeaderboard();
short getMenuChoice();
void clearScreen();
void loadMaze(string MAZE_FILE, vector <vector<char> >& maze);

//void printVector(std::vector<Maze> const &input);
//void display(vector<Maze>& vect);

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

	short op;
    char w;
    char aw;
	bool isPlaying = true;
	do{
		op = menu();
		switch(op){
			case 1:

                //loadMaze("MAZE_01.TXT",maze);
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

                while(1){

                    loadMaze("MAZE_01.TXT",maze);
                    cout << "yea" << endl; 
                    w = charValidation();
                    if (w=='y'){
                        break;
                    }
                }
			case 3:
				isPlaying = false;
				break;
			default :
				fail();
		}
        
	}while(isPlaying);

	return 0; 
}

void loadMaze(string MAZE_FILE, vector< vector<char> >& maze) {
    char byte = 0;
    

    /*
    
    for (const auto &i : bytes) {
        cout << i << "-";
    }
    cout << endl;
    input_file.close();
    vect[count].upc << "\nManufacturer: " << vect[count].manufacturer << "\nProduct Name: " << vect[count].name << "\nPrice: $" << vect[count].price << "\nQuantity: " << vect[count].quantity << "\nTotal Value: $" << vect[count].value << endl;
    */

    
	//char line;
	fstream mazeFile;

	mazeFile.open(MAZE_FILE, ios::in); // opens file
			
	if (!mazeFile){  // checks if file exists
		openFail();
	}
	else{
        	
		while (mazeFile.get(byte)){                // reads all content in file  
			if(mazeFile.eof()){                // if the file reaches its end, stop
				break;
			}
            
            mazeFile >> std::noskipws;
            
            for(int i =0; i < 10; i++){
                vector<char> temp;
                for(int j=0; i < 20; j++){
                    temp.push_back(byte);
                }
                maze.push_back(temp);
            }
            
            //maze.push_back(byte);            
        
        	//cout << line;          
	    }
	}
	mazeFile.close();
    for(int i =0 ; i < maze.size(); i++){
        for(int j=0; j < maze[i].size(); i++){
            cout << maze[i][j];
        }
    }
	cout << endl;
}
/*
void findPath(vector<vector<char>> &maze){

    int vertices;
    int distance[20];
    int INFINITY=20;
    int parent[20];
    int source=maze[1][1];
    bool visited[20]={0};  
    cin>>vertices; 
    void initialize(bool& vertices,int& distance[20],int& INFINITY=20, int& parent[20] ){
        for(int i = 0; i < vertices ; i++){
        distance[i]=INFINITY;
        parent[i]=i;
        
        }
        distance[source]=0;
    }
    int getNearest(bool& vertices,int& INFINITY=20, int& vertices,int& diatance[20]){
        int minvalue=INFINITY;
        int minnode = 0;
        for(int i = 0; i<vertices; i++){
            if(!visited[i] && dis[i]< minvalue){
                minvalue = distance[i];
                minnode= i;
        }
        return minnode;
    } 

   
    void dijkstra_Algorithm(bool& vertices, ){
        for(int = 0 ;i < vertices ; i++){
            int nearest = getNearest();
        visited[nearest] = true;

        for(int adiNodes=0; adiNode < vertices ; adiNode++){
            if(maze[nearest][adiNode] != INFINITE && distance[adiNode]<distance[nearest][adiNode]{
                distance[adiNode] = distance[nearest] + maze[nearest][adiNode];
                parent[adiNode] = nearest;
            }
        
        }
     }
    }
        
    for(int i = 0;i < vertices ;i++){
        for(int j=0;j<vertices;j++){
            cin>> maze[i][j];
        }
    }
    cin>>source;
    initialize();
    dijkstra_Algorithm();

    

    
}
*/
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

		cout << "----------MENU-----------\n1-RULES\n2-PLAY\n3-EXIT\n-------------------------" << endl;

		menuInput = getMenuChoice();
		

		if(menuInput < 0 || menuInput > 4){
            
			cout << "ERROR: FAULTY INPUT...TRY AGAIN"<<endl;
		}

	}while(menuInput < 0 || menuInput > 4);

	return menuInput;
}


/*
bool pushtoLeaderboard(){ // TODO: garantir que data foi pushed to lb antes de continuar
	
      fstream my_file;
        my_file.open("MAZE_02_WINNERS.txt", ios::out);
		if(!my_file)
		{
			cout <<"File not found"; 
		}
		else
		{
            my_file << "-----------------\n";
			my_file << "|Player" << setw(9) << "Time" << "|\n";
            my_file << "|---------------|\n";
			my_file << "|" << player.username << setw(10) << player.score << "|\n";
			my_file << "-----------------";
			my_file.close();
		}


        if(my_file.eof)
        {
            return true
        }

	//funcao to  


}*/
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
		std::cin.ignore(4 , '\n');

		cout << "-->";
		cin >> menuChoice;
	}

	return menuChoice;


}
char charValidation(){

	char choice;

	cout << "-->";
	cin >> choice;

	while(std::cin.good()==false){
		cout << "ERROR: Faulty input...Try again!"<<endl;

		std::cin.clear();
		std::cin.ignore(4 , '\n');

		cout << "-->";
		cin >> choice;
	}

	return choice;


}




void clearScreen()
{
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

/*
Maze goLeft(int &x,int &y,vector< vector <char>> &maze[][19]) nao devia ser startx porcausa de quando a funcao for called ???? {
    if ((maze[x][y-1]==' '|| maze[x][y-1]=='*') || maze[x][y-1]=='R') || maze[x][y-1]=='r') && (y-1!=0))  still not sure se pode ir pra fence desliagda + mudar esses valores que y tem que ser maior, menor ou igual a   {  
        switch (maze[x][y-1]){
                case ' ':
                    cout >> "Valid Move boyy";
                    break;
                case '*':
                     cout >> "if para ver se a fence ta ligada ou nao"
                                "se estiver ligada he dies"
                                "se nao estive ligada, Invalid Move Boy try again"
                    break;
                case 'R':
                    cout >> "You`re dead my g";
                case 'r':
                    cout >> "Invalid move nigga, try again";
	            
	            
        }
    }
	
    else {
	    cout<<"CHANGE PRA DIZER PORQUE QUE NAO PODE!";	
    }
}



Maze goRight(int &x,int &y,vector< vector <char>> &maze) nao devia ser startx porcausa de quando a funcao for called ???? { 
    if ((maze[x][y+1]==' ' || maze[x][y+1]=='*' || maze[x][y+1]=='R' || maze[x][y+1]=='r') && (y+1!=19))  still not sure se pode ir pra fence desliagda + mudar esses valores que y tem que ser maior, menor ou igual a { 
        switch (maze[x][y+1]){
                case ' ':
                    cout >> "Valid Move boyy";
                    break;
                case '*':
                     cout >> "if para ver se a fence ta ligada ou nao"
                                "se estiver ligada he dies"
                                "se nao estive ligada, Invalid Move Boy try again"
                    break;
                case 'R':
                    cout >> "You`re dead my g";
                case 'r':
                    cout >> "Invalid move nigga, try again";
	            
        }

    }
   else {
	    cout<<"CHANGE PRA DIZER QUE NAO PODE";
    }

}


Maze goUp(int &x,int &y,vector< vector <char>>& maze) nao devia ser startx porcausa de quando a funcao for called ???? { 
    if ((maze[x-1][y]==' ' || maze[x-1][y]=='*' || maze[x-1][y]=='R' || maze[x-1][y]=='r') && (x-1!=0)) still not sure se pode ir pra fence desliagda + mudar esses valores que y tem que ser maior, menor ou igual a  { 
         switch (maze[x-1][y]){
                case ' ':
                    cout >> "Valid Move boyy";
                    break;
                case '*':
                     cout >> "if para ver se a fence ta ligada ou nao"
                                "se estiver ligada he dies"
                                "se nao estive ligada, Invalid Move Boy try again"
                    break;
                case 'R':
                    cout >> "You`re dead my g";
                case 'r':
                    cout >> "Invalid move nigga, try again";
	            
        }


}

Maze goDown(int &x,int &y, vector< vector <char>>& maze) nao devia ser startx porcausa de quando a funcao for called ???? { 
    if ((maze[x+1][y]==' ' || maze[x+1][y]=='*' || maze[x+1][y]=='R' || maze[x+1][y]=='r') && (x+1!=9))  still not sure se pode ir pra fence desliagda + mudar esses valores que y tem que ser maior, menor ou igual a  { 
        switch (maze[x+1][y]){
                case ' ':
                    cout >> "Valid Move boyy";
                    break;
                case '*':
                     cout >> "if para ver se a fence ta ligada ou nao"
                                "se estiver ligada he dies"
                                "se nao estive ligada, Invalid Move Boy try again"
                    break;
                case 'R':
                    cout >> "You`re dead my g";
                case 'r':
                    cout >> "Invalid move nigga, try again";
	            
        }

    }

}
*/