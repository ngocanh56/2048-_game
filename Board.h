enum Direction {LEFT,RIGHT,UP,DOWN};
int Size[]={1,40,80,79,57,74,75,89,60,70,93,10};
int Num[]={0,0,0,0,0,0,0,0,0,0,0,0,0}; // in ra ảnh mấy của animation
class Board
{
private:
    int SizeCell;
    int numRow;
    int numColumn;
    int X;
    int Y;
    vector<vector<int> > Index;
    vector<vector<int> > matrix;
    vector<vector<int> > ed;
public:
    void initBoard();
    void createCell();
    void createBoard();
    void printBoard();
    void ModifyIndex();
    bool modifyCell(int x,int y,Direction check);
    bool modifyBoard(Direction check);
    bool Endgame();
    void resetEd();
};

void Board::initBoard()
{
    SizeCell=150; X=19; Y=19;
    numRow=4; numColumn=4;

    Index.resize(numRow);
    for(int i=0;i<numRow;i++)
    {
        Index[i].resize(numColumn,0);
    }

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
    if(rand()%6!=0)
    matrix[luu[x].first][luu[x].second] = 2;
    else matrix[luu[x].first][luu[x].second] = 4;
}
void Board::createBoard()
{
    createCell();
    createCell();
}
void Board::printBoard()
{
    for(int i=0;i<numRow;i++)
    for(int j=0;j<numColumn;j++)
    {
        int coorX=X+SizeCell*i;
        int coorY=Y+SizeCell*j;

        int index = (int)log2(matrix[i][j]);
        stringstream ss;string path; string Name;

        ss<<Num[index];ss>>path; ss.clear();
        ss<<index; ss>>Name; ss.clear();

        if(path.size()==1) path='0'+path;
        path= "Number" +Name+ "/frame_" + path + "_delay-0.05s.gif";

        image.loadImage(path);
        image.render(coorX,coorY,SizeCell,SizeCell);
    }
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
        matrix[u][v]=pow(2,10)*matrix[u][v];

        ed[u][v]=true;
        matrix[i][j]=1;
        return true;
    }
    return false;
}
bool Board::modifyBoard(Direction check)
{
    bool quit=false;
    int num=0;
    resetEd();

    while(!quit)
    {
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
        if(quit==true && num==1) return false;
    }
    //num++; //std::cout<<k<<" "<<quit<<'\n';
    //nếu không có bước di chuyển nào thì ko tạo ô mới
    return true;
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
//lu
void Board::ModifyIndex()
{
    int kt[13]; memset(kt,0,sizeof(kt));

    for (int i=0;i<numRow;++i)
    for (int j=0;j<numColumn;++j)
    {
        int value=log2(matrix[i][j]);
        kt[value]=1;
    }
    for (int value=0;value<=11;++value)
    Num[value]=(Num[value]+kt[value])%Size[value];
}
