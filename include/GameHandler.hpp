#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <IAI.hpp>
#include <AScene.hpp>

class GameHandler
{
public:
    enum eTurn
    {
        EMPTY = 0,
        BLACK_TURN = 1,
        WHITE_TURN = 2,
    };

    enum eGameUnit
    {
        BLACK_STONE = 1,
        WHITE_STONE = 2,
        BOARD_SIZE = 15,
        MAX_STONE = 225,
    };

    enum eGameRule
    {
        RULE_FREESTYLE,
        // No limitation
        // placing more than 5 stones in a row can win
        RULE_STANDARD,
        // No open three: both white & black
        // can place 4-4
        // can place more than 5 stones in a row but not win
        // only 5 stones in a row can win
        RULE_RENJU,
        // No open three, no 4-4, no more than 5 stone: only black
        // white can do open 3-3, 4-4, more than 5 stones
    };

    enum eGameStatus
    {
        GAME_ONGOING,
        GAME_WHITE_WIN,
        GAME_BLACK_WIN,
        GAME_DRAW,
    };

    enum ePlayMode
    {
        MODE_LOCAL,
        MODE_AI,
    };

    enum eAIType
    {
        AI_NOTDEFINED,
        AI_RANDOM,
        AI_MINIMAX,
        AI_MCTS,
    };
    
    enum eBannedMove
    {
        POSSIBLE,
        OPEN_THREE,
        FOUR_FOUR,
    };

public: //pattern
    const std::vector< std::vector<int> > openThree = { { 0, 3, 1, 0, 1, 0 }, \
                                                        { 0, 1, 3, 0, 1, 0 }, \
                                                        { 0, 1, 1, 0, 3, 0 }, \
                                                        { 0, 3, 0, 1, 1, 0 }, \
                                                        { 0, 1, 0, 3, 1, 0 }, \
                                                        { 0, 1, 0, 1, 3, 0 }, \
                                                        { 0, 0, 3, 1, 1, 0, 0 }, \
                                                        { 0, 0, 1, 3, 1, 0, 0 }, \
                                                        { 0, 0, 1, 1, 3, 0, 0 }
                                                    };

public:
    GameHandler(GameHandler::eGameRule rule, \
                GameHandler::ePlayMode mode, \
                eAIType aiType);
    ~GameHandler();

    bool CheckRule(int x, int y);
    bool PlaceStone(int x, int y);
    bool IsGameEnd();

    int  IsPossiblePattern(const std::vector<int>& pattern, int x, int y, int dx, int dy);
    bool IsPossibleMove(int x, int y);
    bool IsLegalMove(int x, int y);
    bool IsOpenThree(int x, int y, std::pair<int, int> dir, eTurn turn);
    int  IsFourStone(int x, int y, std::pair<int, int> dir, eTurn turn);

    bool CheckWin(int count, int color);

    eTurn GetTurn() const;
    eGameStatus GetGameStatus() const;

    std::vector<std::pair<int, int> > GetBlackStoneHistory() const;
    std::vector<std::pair<int, int> > GetWhiteStoneHistory() const;

    void SetBannedMove(eBannedMove bannedMove);
    eBannedMove GetBannedMove() const;

private:
    eTurn mTurn;
    eGameRule mRule;
    ePlayMode mMode;
    eGameStatus mStatus;
    eBannedMove mBannedMove;
    IAI*                mAI;
    
	int mBoard[15][15];

private:
    std::vector<std::pair<int, int> > mBlackStoneHistory;
    std::vector<std::pair<int, int> > mWhiteStoneHistory;
};