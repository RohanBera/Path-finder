/* the following program finds the SHORTEST path, and prints the path and length.
 * path and lenght printed ONLY WHEN A PATH EXISTS 
 * preferance order followed : right > down > left > up 
 * algorithm used : lee algorithm
 * data structures implimented : circular queue and stack (recurtion)
 * time complexity : O(n^2)
 */



#include <stdio.h>
#include <stdlib.h>
#include <time.h>		//time function used later

/*defining constants here */

#define MAX 10000

/*declaring global vars here */

struct node
{
  int x, y;
};

struct node queue[MAX];		//queue of type coordinates (x, y)
int    size = 0;		//queue size
int    rear = MAX-1;		//queue last ele pointer
int    front = 0;		//queue first ele pointer


int  i = 0, j = 0;		//[i][j] keeps track of mouse


/* deaclaring functions here */

int    leemethod (int n, int maze[][n]);
int    track (int n, int maze[][n], int x, int y, int len);
void   print (int n, int maze[][n]);
void   colors (char col);
void   enqueue (struct node nd);
struct node dequeue();

/* main FUNCTION STARTS HERE */

int main()
{
  int a,b,n;
  int shpath;

  printf("Enter grid length : \n");
  scanf("%d", &n);

  int  maze[n][n];

  for (a = 0; a < n; a++)
  {
    for (b = 0; b < n; b++)
    {
      maze[a][b] = 0;
    }
  }

  //inbuilt random func
  //walls are set to -1
  //rat is 1
  //others are 0
  //path will later be set to -2

  srand(time(0));
  for (a = 0; a < (n*n)/3; a++)
  {
    maze[rand()%n][rand()%n] = -1;
  }

  maze[0][0] = 1;
  maze[n-1][n-1] = 0;

  print(n, maze);
  printf("\n\n\n");

  shpath = leemethod(n, maze);
  if (shpath == 0)
    exit(1);

  // maze after lee method 

  for (a = 0; a < n; a++)
  {
    for (b = 0; b < n; b++)
    {
      printf("[%d]", maze[a][b]);
    }	    
    printf("\n");
  }	   
  
  printf("\n\n\n");

  // finding shortest path

  track(n, maze, 0, 0, shpath); 
  print(n, maze);

  exit(0);
}


/* leemethod FUNCTION STARTS HERE */

/* based on BREADTH FIRST SEARCH
 * makes use of queues (here, i uesd circular queue)
 * also called as wave Expantion
 */



int  leemethod (int n, int maze[][n])
{
  int visited[n][n];		//keeps track of whether next block previously visited or not 
 
  for (int a = 0; a < n; a++)   
    for (int b = 0; b < n; b++)
      visited[a][b] = 0 ;

  visited[0][0] = 1;		//rat initial location


  struct node temp;
  temp.x = 0, temp.y = 0;
  enqueue(temp);
  
  while (size != 0)		//return when queue is empty or cheese found
  {
    temp = dequeue();
  
    //printf("%d, %d\n",temp.x, temp.y);
  
    i = temp.x;
    j = temp.y;
  
    if (i == n-1 && j == n-1)
    {
      printf("cheese found\n\n\n");
      return maze[n-1][n-1];  
    }	

/* things being checked :
 * next block should be in bound, shouldnt be visited previously & not a wall
 */

    if (i >= 0 && i < n && j+1 >= 0 && j+1 < n && visited[i][j+1] == 0 && maze[i][j+1] != -1)
    {
      temp.x = i, temp.y = j+1;
      enqueue(temp);

      maze[i][j+1] = maze[i][j] + 1;
      //printf("right\n");

      visited[i][j+1] = 1;
    }


    if (i+1 >= 0 && i+1 < n && j >= 0 && j < n && visited[i+1][j] == 0 && maze[i+1][j] != -1)
    {
      temp.x = i+1, temp.y = j;
      enqueue(temp);
      
      //printf("down\n");
      maze[i+1][j] = maze[i][j] + 1;
      	
      visited[i+1][j] = 1;
    }

    //theres a drawback for left and up

    if (i >= 0 && i < n && j-1 >= 0 && j-1 < n && visited[i][j-1] == 0 && maze[i][j-1] != -1)
    {
      temp.x = i, temp.y = j-1;
      enqueue(temp);
      
      //printf("left\n");
      maze[i][j-1] = maze[i][j] + 1;

      visited[i][j-1] = 1;
    }


    if (i-1 >= 0 && i-1 < n && j >= 0 && j < n && visited[i-1][j] == 0 && maze[i-1][j] != -1)
    {
      temp.x = i-1, temp.y = j;
      enqueue(temp);
    
      //printf("up\n");
      maze[i-1][j] = maze[i][j] + 1;
         
      visited[i-1][j] = 1;
    }
  }	  

  if (size == 0)
    printf("No path available \n");
 
  return 0;
}



/*track FUNCTION STARTS HERE*/

/* recursive function
 * logic : if next element > present element 
 *         && not a wall,
 *         then return TRUE.
 */         

int track(int n, int maze[][n], int x, int y, int len) 
{
  if (maze[x][y] == len)
  {
    maze[x][y] = -2;
    return 1;
  }

  if (x >= 0 && x < n && y >= 0 && y < n && maze[x][y] != -1)
  {
    int temp = maze[x][y];
    maze[x][y] = -2;		//helpful during printing 

    if (maze[x][y+1] == temp+1)				//right
      if (track(n, maze, x, y+1, len) == 1)
        return 1;

    if (maze[x+1][y] == temp+1)				//down
      if (track(n, maze, x+1, y, len) == 1)
        return 1;

    if (maze[x][y-1] == temp+1)				//left 
      if (track(n, maze, x, y-1, len) == 1)
        return 1;

    if (maze[x-1][y] == temp+1)				//up
      if (track(n, maze, x-1, y, len) == 1)
        return 1;


    maze[x][y] = temp;		//reseting value, helpful printing
    return 0;
  }

  return 0;
}


/*print FUNCTION STARTS HERE */


void print(int n, int maze[][n]) 
{
  int a,b;

  for (a = 0; a < n; a++)
  {
    for (b = 0; b < n; b++)
    {
      if (a == i && b == j)             //blue  //rat
      {
        colors('b');
        printf("[R]");
      }
      else if (a == n-1 && b == n-1)    //cheese
      {
        colors('b');
        printf("[C]");
      }
      else if (maze[a][b] == -2)         //path        //yello
      {
        colors('y');
        printf("[O]");
      }
      else if (maze[a][b] == -1)         //wall        //magenta
      {
        colors('B');
        printf("[X]");
      }
      else 			         //others      //white
      {
        colors('w');
        printf("[O]");
      }
    }
    printf("\n");
  }
  printf("\033[0m");                     //reset

}


/*colors FUNCTION STARTS HERE*/

void colors(char col)
{
  if (col == 'w')                        //white
    printf("\033[0m");
  else if (col == 'B')                   //magenta
    printf("\033[0;35m");
  else if (col == 'y')                   //yellow
    printf("\033[0;33m");
  else if (col == 'b')                   //blue
    printf("\033[0;34m");
}


/*queue implementation :*/

void enqueue(struct node nd)
{
  if (size == MAX)
  {
    printf("Queue is full\n");
    return;
  }	  
  
  //printf("enqueue\n");
  rear = (rear + 1) % MAX;
  size ++;
  queue[rear] = nd;
  
  return;
}	


struct node dequeue()
{
  struct node data = {0, 0};

  if (size == 0)
  {
    printf("Queue is empty\n");
    return data; 
  }

  data = queue[front];

  front = (front + 1) % MAX;
  size--;

  //printf("dequeue\n");
  return data;
} 
