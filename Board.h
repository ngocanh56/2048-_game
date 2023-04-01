enum Direction {LEFT,RIGHT,UP,DOWN};
class Board
{
private:
    int SizeCell;
    int numRow;
    int numColumn;
    int X;
    int Y;
    vector<vector<int> > matrix;
public:
    void initBoard();
    void createCell();
    void createBoard();
    void printBoard();
    bool modifyCell(int x,int y,Direction check);
    bool modifyBoard(Direction check);
};

void Board::initBoard()
{
    SizeCell=150; X=19; Y=19;
    numRow=4; numColumn=4;
    matrix.resize(numRow);
    for(int i=0;i<numRow;i++)
    {
        matrix[i].resize(numColumn,1);
        for (int j=0;j<numColumn;++j) matrix[i][j] = 1;
    }

    image.loadImage("Picture\11.gif");
    image.render(X,Y,600,600);
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
        stringstream ss;string path;
        ss<<index;ss>>path;

        path = "Picture/" + path + ".gif";

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
    if(matrix[i][j]==matrix[u][v])
    {
        matrix[u][v]=2*matrix[u][v];
        matrix[i][j]=1;
        return true;
    }
    return false;
}
bool Board::modifyBoard(Direction check)
{
    int num=0;
    bool quit=false;
    while(!quit)
    {
        quit = true;
        if (check==UP)
            {
                for (int i=0;i<numRow;++i)
                for (int j=0;j<numColumn;++j)
                if (modifyCell(i,j,check)) quit = false;
            }
        else if(check==DOWN)
            {
                for (int i=0;i<numRow;++i)
                for (int j=numColumn-1;j>=0;--j)
                if (modifyCell(i,j,check)) quit = false;
            }
        else
        if (check==LEFT)
        {
            for (int j=0;j<numColumn;++j)
            for (int i=0;i<numRow;++i)
                if (modifyCell(i,j,check)) quit = false;
        }
        else if(check==RIGHT)
        {
            for (int j=0;j<numColumn;++j)
            for (int i=numRow-1;i>=0;--i)
                if (modifyCell(i,j,check)) quit = false;
        }
        num++; //std::cout<<k<<" "<<quit<<'\n';
        if(quit && num==1) return false;
        //nếu không có bước di chuyển nào thì ko tạo ô mới
    }
    return true;
}
