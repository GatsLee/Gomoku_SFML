#include <AIMinMax.hpp>

bool AIMinMax::cmpWeight(struct sCoor a, struct sCoor b)
{
    return a.weight > b.weight;
}

AIMinMax::AIMinMax(int turn)
    : mStartPoint(std::make_pair(-1, -1))
    , mAnsPoint(std::make_pair(-1, -1))
{
    mTurn[0] = (turn == 1) ? 1 : 2;
    mTurn[1] = turn;
}

AIMinMax::~AIMinMax()
{}

void AIMinMax::Init()
{
	//0,2,25,421,1200000,10000000 },{ 0,1,22,105,17000,10000000
	// my or your / num / enemy / space
	//num=1 일때 빈공간 0인것만 1 나머지는 0
	//map[5][9] = 1; map[5][10] = 2; map[5][11] = 2; map[5][13] = 2; map[5][14] = 1;
	w2[0][1][0][0] = 2; w2[1][1][0][0] = 1;
	w2[0][1][0][1] = 2; w2[1][1][0][1] = 0;
	//num=2 일때
	w2[0][2][0][0] = 25, w2[1][2][0][0] = 4;
	w2[0][2][0][1] = 25, w2[1][2][0][1] = 1;
	w2[0][2][1][1] = 2; w2[1][2][1][1] = 1;
	w2[0][2][1][0] = 2; w2[1][2][1][0] = 1;
	

	//num=3
	w2[0][3][0][0] = 521, w2[1][3][0][0] = 105;
	w2[0][3][0][1] = 301; w2[1][3][0][1] = 13;	
	w2[0][3][1][0] = 301, w2[1][3][1][0] = 13;
	w2[0][3][1][1] = 301, w2[1][3][1][1] = 13;
	//num=4
	w2[0][4][0][0] = 21000; w2[0][4][1][0] = 20010; w2[0][4][2][0] = 20010;
	w2[1][4][0][0] = 4001; w2[1][4][1][0] = 4001; w2[1][4][2][0] = 4001;
}

/**
 * @brief update the board with the new point: player
 * 
 * @param x 
 * @param y 
 */
void AIMinMax::UpdateBoard(int x, int y)
{
    mBoard[x][y] = mTurn[0];
}

void AIMinMax::FindPossiblePoints()
{
    mPossiblePoints.clear();
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (mBoard[i][j] == 0 && mWeight[i][j] > 0)
            {
                mPossiblePoints.push_back(std::make_pair(i, j));
            }
        }
    }
}

void AIMinMax::SetWeight(int curTurn[2])
{
    memset(mWeight, 0, sizeof(mWeight));

    for (int type = 0; type < 2; type++)
    {
        for (int i = 0; i < 15; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                int sum = 0;
                tCount count[5];
                if (mBoard[i][j]) continue;
                for (int d = 0; d < 4; d++)
                {
                    int nx, ny;
                    int cnt = 1;
                    int zeroCnt = 0;
                    int zeroCnt1 = 0;
                    int remember = 0;
                    int zeroCnt2 = 0;
                    int num = 0;
                    int enemyCnt = 0;
                    int before;

                    while (true) {
						nx = i + (cnt * dir[d][0]), ny = j + (cnt * dir[d][1]);
						before = mBoard[nx - dir[d][0]][ny - dir[d][1]];
						if (nx < 0 || ny < 0 || nx >= 15 || ny >= 15) {
							if (remember || zeroCnt1 == 0) {
								enemyCnt++;
							}
							if (before != 0)remember = zeroCnt1;

							break;
						}
						if (mBoard[nx][ny] == mTurn[(type + 1) % 2]) {
							if (remember || zeroCnt1 == 0) {
								enemyCnt++;
							}
							if (before != 0)remember = zeroCnt1;

							break;
						}

						if (mBoard[nx][ny] == mTurn[type]) {
							remember = zeroCnt1;
							num++;
						}
						if (mBoard[nx][ny] == 0)zeroCnt1++;
						if (zeroCnt1 >= 2)break;
						cnt++;
					}
					//cout <<"d: "<<d<< "remember " << remember <<" length "<<length<< endl;
					zeroCnt1 = remember;
					cnt = 1;
					remember = 0;

                    while (true)
                    {
                        nx = i + (cnt * dir[d + 4][0]), ny = j + (cnt * dir[d + 4][1]);
						if (nx < 0 || ny < 0 || nx >= 15 || ny >= 15)
                        {
							if (remember || zeroCnt2 == 0) {
								enemyCnt++;
							}
							if (before != 0)remember = zeroCnt2;
							break;
						}
						if (mBoard[nx][ny] == mTurn[(type + 1) % 2])
                        {
							if (remember || zeroCnt2 == 0) {
								enemyCnt++;
							}
							if (before != 0)remember = zeroCnt2;
							break;
						}

						if (mBoard[nx][ny] == mTurn[type])
                        {
							remember = zeroCnt2;
							num++;
						}
						if (mBoard[nx][ny] == 0)zeroCnt2++;
						if (zeroCnt2 >= 2) break;
						cnt++;
                    }
                    zeroCnt2 = remember;
                    zeroCnt = zeroCnt1 + zeroCnt2;
                    count[d] = {num, zeroCnt, enemyCnt};
                }

                for (int d = 0; d < 4; d++)
                {
                    int num = count[d].weight, enemy = count[d].enemy, emptyspace = count[d].emptySpace;
					int temp_w = w2[(type + 1) % 2][num][enemy][emptyspace];
					//빈 공간은 하나만 감당, num+emptyspace>=5,enemy 2개 가중치 부여하지 않는다. 
					if (emptyspace >= 2 || num + emptyspace >= 5)continue;
					if (num != 4 && enemy >= 2)continue;
					sum += temp_w;
                }
                mWeight[i][j] += sum;
                if (mBoard[i][j]) mWeight[i][j] = 0;
            }
        }
    }
}

void AIMinMax::SearchBestMove(int depth, int curTurn)
{
    int curColor[2] = {0,0};
    if (curTurn == 1)
    {
        curColor[0] = mTurn[0];
        curColor[1] = mTurn[1];
    }
    else
    {
        curColor[0] = mTurn[1];
        curColor[1] = mTurn[0];
    }
    int high = 0;
    SetWeight(curColor);
    std::deque<tCoor> savePos;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            int weight = mWeight[i][j];
            if (weight > 0)
            {
                if (weight >= 301 || weight == 302) weight = 24;
                else if (weight >= 118 && weight <= 200) weight = 320;
                savePos.push_back({i, j, weight});
                high = std::max(high, weight);
            }
        }
    }

    sort(savePos.begin(), savePos.end(), cmpWeight);

    int curMax = savePos.front().weight;
    int idx = 0;
    for (int i = 1; i < savePos.size(); i++)
    {
        idx = i;
        int num = savePos[i].weight;
        if (num != curMax) break;
    }

    savePos.erase(savePos.begin() + idx, savePos.end());

    int tempColor;
    if (curTurn == 1) tempColor = 2;
    else tempColor = 1;
    if (depth % 2 == 1 && checkWin(tempColor))
    {
        return;
    }
    if (mTflag)
    {
        return;
    }

    if (!mTflag && (depth % 2 == 1 && ((curMax >= 326 && curMax < 406) || curMax >= 521)))
    {
        if (!((105 <= curMax && curMax <= 300) || (4000 <= curMax && curMax <= 20000)))
        {
            mTflag = true;
            mCurBestMove = std::make_pair(savePos.front().x, savePos.front().y);
            return;
        }
    }

    if (depth == MAX_DEPTH)
    {
        return;
    }

    if (curTurn == 1)
    {
        for (auto &pos : savePos)
        {
            int x = pos.x, y = pos.y;
            mBoard[x][y] = mTurn[1];
            SearchBestMove(depth + 1, 2);
            mBoard[x][y] = 0;
        }
    }
    else if (curTurn == 2)
    {
        for (auto &pos : savePos)
        {
            int x = pos.x, y = pos.y;
            mBoard[x][y] = mTurn[0];
            SearchBestMove(depth + 1, 1);
            mBoard[x][y] = 0;
        }
    }
}
/**
 * @brief main function to calculate the AI move
 * 
 */
void AIMinMax::CalculateAIMove()
{
    SetWeight(mTurn);
    std::deque<tCoor> savePos;

    int highestWeight = 0;
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 15; i++)
        {
            int weight = mWeight[i][j];
            if (weight > 0)
            {
                if (weight >= 301 || weight == 302) weight = 24;
                else if (weight >= 118 && weight <= 200) weight = 320;
                savePos.push_back({i, j, weight});
                if (highestWeight < weight)
                {
                    highestWeight = weight;
                    mCurBestMove = std::make_pair(i, j);
                }
            }
        }
    }

    sort(savePos.begin(), savePos.end(), cmpWeight);

    int curMax = savePos.front().weight;
    if (!(curMax >= 326 && curMax < 406) || curMax >= 521)
    {
        for (auto &pos : savePos)
        {
            int x = pos.x, y = pos.y;
            mBoard[x][y] = mTurn[1];
            SearchBestMove(0, mTurn[1]);
            mBoard[x][y] = 0;
        }
    }
    if (!mPossiblePoints.empty())
    {
        mCurBestMove = mPossiblePoints.front();
    }
}

std::pair<int, int> AIMinMax::GetBestMove() const
{
    return mCurBestMove;
}

void AIMinMax::SetBestMove(int x, int y)
{
    mCurBestMove = std::make_pair(x, y);
}

bool AIMinMax::IsCalculated() const
{
    return mTflag;
}