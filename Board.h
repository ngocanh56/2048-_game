enum Direction {LEFT,RIGHT,UP,DOWN};
int Size[]={1,40,80,79,57,74,75,89,60,70,93,120};
int Num[]={0,0,0,0,0,0,0,0,0,0,0,0,0}; // number of picture for animation
class Board
{
private:
    int SizeCell;
    int numRow;
    int numColumn;
    int timer;
    int X,Y;
    vector<vector<int> > matrix; // value of cell
    vector<vector<bool> > ed; // check merge cell
public:
    void initBoard(); // modify value
    void createCell();
    void createBoard(); // board of newgame
    void printBoard(bool enlarge);
    void resetEd();
    void printCell(int i,int j,int x,int y,int w,int h);
    bool modifyCell(int x,int y,Direction check); // merge cell
    void modifyBoard(Direction check); // change board after step
    bool Endgame();
    void printEndgame();
    void Modify_Num_of_Animation(); //animation
};

void Board::initBoard()
{
    X=19 ,Y=19;
    SizeCell=127;
    numRow=4,numColumn=4;

    timer=0;// times of programe

    matrix.resize(numRow);
    for(int i=0;i<numRow;i++)
    {
        matrix[i].resize(numColumn,1);
    }

    resetEd();
}
void Board:: resetEd()
{
    ed.resize(numRow);
    for(int i=0;i<numRow;i++)
        {
            ed[i].resize(numColumn);
            ed[i]={0};
        }
}
void Board::createCell()
{
    vector<pair<int,int> >luu;
    for(int i=0;i<numRow;i++)
    for(int j=0;j<numColumn;j++)
    if(matrix[i][j]==1) luu.push_back({i,j});

    int x=rand()%luu.size();
    ed[luu[x].first][luu[x].second]=1;
    if(rand()%6!=0)
    matrix[luu[x].first][luu[x].second] = 2;
    else matrix[luu[x].first][luu[x].second] = 4;
}
void Board::createBoard()
{
    createCell();
    createCell();
}
void Board::printCell(int i,int j,int x,int y,int w,int h)
{
    int index = (int)log2(matrix[i][j]);
    stringstream ss;string path; string Name;

    ss<<Num[index];ss>>path; ss.clear();
    ss<<index; ss>>Name; ss.clear();
    if(index==11 )
    {
            if(path.size()==1 ) path="00"+path;
            if(path.size()==2 ) path="0"+path;
            path= "Number" +Name+ "/frame_" + path + "_delay-0.07s.gif";
    }
    else
    {
            if(path.size()==1) path='0'+path;
            path= "Number" +Name+ "/frame_" + path + "_delay-0.05s.gif";
    }
    image.loadImage(path);
    image.render(x,y,w,h);
}
void Board::printBoard(bool enlarge)
{
    SDL_SetRenderDrawColor(g_renderer,221,204,235,0);
    SDL_RenderClear(g_renderer);
    DrawRectangle(X-10,Y-10,SizeCell*4+20,SizeCell*4+20,58,8,62,255);
    for(int i=0;i<numRow;i++)
    for(int j=0;j<numColumn;j++)
    {
        int coorX=X+SizeCell*i;
        int coorY=Y+SizeCell*j;
        if(enlarge && ed[i][j]) printCell(i,j,coorX,coorY,SizeCell,SizeCell);
        else printCell(i,j,coorX+10,coorY+10,SizeCell-20,SizeCell-20);

    }
    Modify_Num_of_Animation();
    SDL_RenderPresent(g_renderer);
}
bool Board::modifyCell(int i,int j,Direction check)
{
    if(matrix[i][j]==1) return false;
    int u,v;
    if(check==LEFT) { u=-1; v=0;}
    else if (check==RIGHT){u=1; v=0;}
    else if (check==UP) {u=0; v=-1;}
    else if(check==DOWN) {u=0;v=1;}

    u += i; v += j;
    if(u<0 || v<0 || u>=numRow || v>=numColumn) return false;
    if(matrix[u][v]==1)
    {
        matrix[u][v]=matrix[i][j];
        matrix[i][j]=1;
        return true;
    }
    else
    if( !ed[u][v] && !ed[i][j] && matrix[i][j]==matrix[u][v])
    {
        matrix[u][v]=2*matrix[u][v];
        matrix[i][j]=1;
        ed[u][v]=true;
        return true;
    }
    return false;
}
void Board::modifyBoard(Direction check)
{
    bool quit=false;
    int num=0;
    resetEd();

    while(!quit)
    {
        printBoard(false);
        quit=true;
        num++;
        if (check==UP)
        {
            for (int i=0;i<numRow;++i)
            for (int j=0;j<numColumn;++j)
            if (modifyCell(i,j,check)) quit=false;
        }
        else if(check==DOWN)
            {
                for (int i=0;i<numRow;++i)
                for (int j=numColumn-1;j>=0;--j)
                if (modifyCell(i,j,check)) quit=false;
            }
        else
        if (check==LEFT)
        {
            for (int j=0;j<numColumn;++j)
            for (int i=0;i<numRow;++i)
                if (modifyCell(i,j,check)) quit=false;
        }
        else if(check==RIGHT)
        {
            for (int j=0;j<numColumn;++j)
            for (int i=numRow-1;i>=0;--i)
                if (modifyCell(i,j,check)) quit=false;
        }
        if(quit==true && num==1) return;
        //do not create new cells if not moving
    }
    createCell();
    printBoard(true);
}
void Board::Modify_Num_of_Animation()
{
    int kt[13]; memset(kt,0,sizeof(kt)); //check value is in board ?

    for (int i=0;i<numRow;++i)
    for (int j=0;j<numColumn;++j)
    {
        int value=log2(matrix[i][j]);
        kt[value]=1;
    }
    for (int value=0;value<=11;++value)
    Num[value]=(Num[value]+kt[value])%Size[value];
}
bool Board::Endgame()
{
    for (int i=0;i<numRow;++i)
    for (int j=0;j<numColumn;++j)
        if(matrix[i][j]==1) return false;
    for (int i=0;i<numRow;++i)
    for (int j=0;j<numColumn;++j)
    {
       if(i>=1 && matrix[i][j]==matrix[i-1][j]) return false;
       if(i<numRow-1 && matrix[i][j]==matrix[i+1][j]) return false;
       if(j>=1 && matrix[i][j]==matrix[i][j-1]) return false;
       if(j<numColumn-1 && matrix[i][j]==matrix[i][j+1]) return false;
    }
    return true;
}
void Board::printEndgame()
{
    timer=(timer+1)%98;
    stringstream ss;string path;

    ss<<timer;ss>>path; ss.clear();

    if(path.size()==1) path='0'+path;
    path= "Gameover/frame_" + path + "_delay-0.05s.gif";
    image.loadImage(path);
    image.render(X-10,Y-10,SizeCell*4+20,SizeCell*4+20);
}
