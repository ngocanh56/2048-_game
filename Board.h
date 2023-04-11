enum Direction {LEFT,RIGHT,UP,DOWN};
int Size[]={1,40,80,79,57,74,75,89,60,70,93,120};
int Num[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // number of picture for animation
class Board
{
private:
    int numRow;
    int numColumn;
    int timer;
    int score;
    vector<vector<int> > matrix; // value of cell
    vector<vector<bool> > ed; // check merge cell
public:
    void set_up_Board();
    void modifyBoard(Direction check);
    bool Merge_Cell(int x,int y,Direction check);
    void createCell();
    void Background();
    void printBoard(bool enlarge);
    void printCell(int i,int j,int x,int y,int w,int h);
    void printScore(int Score,bool check_best);
    bool Endgame();
    void printEndgame();
    void Num_of_Animation();
    void get_Best();
    void update_Best();
};
void Board::set_up_Board()
{
    numRow=4,numColumn=4;

    timer=0; number=0; score=0;

    get_Best();
    matrix.clear();
    matrix.resize(numRow);
    for(int i=0;i<numRow;i++)
    matrix[i].resize(numColumn,1);

    ed.resize(numRow);
    for(int i=0;i<numRow;i++)
    ed[i].resize(numColumn,false);

    createCell();
    createCell();
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
bool Board::Merge_Cell(int i,int j,Direction check)
{
    if(matrix[i][j]==1) return false;
    int u=i,v=j;
    if(check==LEFT)   u--; else
    if(check==RIGHT)  u++; else
    if(check==UP)     v--; else
    if(check==DOWN)   v++;

    if(u<0 || v<0 || u>=numRow || v>=numColumn) return false;
    if(matrix[u][v]==1)
    {
        swap(matrix[u][v],matrix[i][j]);
        return true;
    }
    else
    if( !ed[u][v] && !ed[i][j] && matrix[i][j]==matrix[u][v])
    {
        matrix[u][v]=2*matrix[u][v];
        score+=matrix[u][v];
        best=max(best,score);
        update_Best();
        matrix[i][j]=1;
        ed[u][v]=true;
        return true;
    }
    return false;
}
//change board after step
void Board::modifyBoard(Direction check)
{
    bool quit=false; int num=0;

    for(int i=0;i<numRow;i++)
    for(int j=0;j<numColumn;j++)
    ed[i][j]=0;

    while(!quit)
    {
        printBoard(false); quit=true; num++;
        if (check==UP)
        {
            for (int i=0;i<numRow;++i)
            for (int j=0;j<numColumn;++j)
            if (Merge_Cell(i,j,check)) quit=false;
        }
        else if(check==DOWN)
            {
                for (int i=0;i<numRow;++i)
                for (int j=numColumn-1;j>=0;--j)
                if (Merge_Cell(i,j,check)) quit=false;
            }
        else
        if (check==LEFT)
        {
            for (int j=0;j<numColumn;++j)
            for (int i=0;i<numRow;++i)
                if (Merge_Cell(i,j,check)) quit=false;
        }
        else if(check==RIGHT)
        {
            for (int j=0;j<numColumn;++j)
            for (int i=numRow-1;i>=0;--i)
                if (Merge_Cell(i,j,check)) quit=false;
        }
        if(quit==true && num==1) return;
        //do not create new cells if not moving
        SDL_Delay(30);
    }

    music=Mix_LoadMUS("Sound/merge1.wav");
    Mix_PlayMusic(music,1);

    createCell();
    printBoard(true);
}
void Board::Background()
{
    BACKGROUND.render(0,0,screen_width,screen_height);

    TITLE.render(X-10,Y-300,SizeCell*4+20,SizeCell*2-20);

    image.loadImage("Display/restart.jpg");
    image.render(X+SizeCell*3-13,264,62,60);

    image.loadImage("Display/cancel.jpg");
    image.render(X+SizeCell*3+52,264,62,62);
}
void Board::printBoard(bool enlarge)
{

    SDL_RenderClear(g_renderer);
    Background();
    DrawRectangle(X-10,Y-10,SizeCell*4+20,SizeCell*4+20,58,8,62,255);

    for(int i=0;i<numRow;i++)
    for(int j=0;j<numColumn;j++)
    {
        int coorX=X+SizeCell*i;
        int coorY=Y+SizeCell*j;
        if(enlarge && ed[i][j]) printCell(i,j,coorX,coorY,SizeCell,SizeCell);
        else printCell(i,j,coorX+10,coorY+10,SizeCell-20,SizeCell-20);
    }
    Num_of_Animation();
    printScore(score,0);
    printScore(best,1);
    SDL_RenderPresent(g_renderer);
}
void Board::printCell(int i,int j,int x,int y,int w,int h)
{
    int index = (int)log2(matrix[i][j]);
    string path=to_string(Num[index]);
    string Name=to_string(index);

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
void Board::printScore(int Score,bool check_best)
{
    string SCORE=to_string(Score);
    while (SCORE.size()<=5) SCORE='0'+SCORE;
    SDL_Color white={255,255,255};
    image.loadText(SCORE,white);
    image.render(X+SizeCell*3,210-check_best*70,90,45);

    //cout<<SCORE<<'\n';
}
void Board::Num_of_Animation()
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
void Board::get_Best()
{
    ifstream file("High_Score.txt");
    file>>best;
}
void Board::update_Best()
{
    ofstream file("High_Score.txt");
    file<<best;
}
bool Board::Endgame()
{
    if(game_over==true) return true;
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

    string path=to_string(timer);
    if(path.size()==1) path='0'+path;
    path= "Gameover/frame_" + path + "_delay-0.05s.gif";

    image.loadImage(path);
    image.render(X-10,Y-10,SizeCell*4+20,SizeCell*4+20);
}
