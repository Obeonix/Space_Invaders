//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

#pragma once

#if !defined(__LEVEL_H__)
#define __LEVEL_H__

// Library Includes
#include <vector>
#include <string>

// Local Includes

// Types

// Constants

// Prototypes
class CBullet;
class CShip;
class CInvaders;
class CFPSCounter;
class CBackGround;

class CLevel
{
    // Member Functions
public:
    CLevel();
    virtual ~CLevel();

    virtual bool Initialise(int _iWidth, int _iHeight);

    virtual void Draw();
    virtual void Process(float _fDeltaTick);

    CShip* GetPaddle() const;

    int GetInvadersRemaining() const;

protected:
    void ProcessBallWallCollision();
	void ProcessPaddleWallCollison();
    void ProcessBallPaddleCollision();
    void ProcessBallBrickCollision();

    void ProcessCheckForWin();

    void ProcessBulletBounds();

    void UpdateScoreText();
    void DrawScore();
	void DrawFPS();

    void SetInvadersRemaining(int _i);

private:
    CLevel(const CLevel& _kr);
    CLevel& operator= (const CLevel& _kr);

    // Member Variables
public:

protected:
	CBackGround* m_pBackground;
    CBullet* m_pBullet;
    CShip* m_pShip;
    std::vector<CInvaders*> m_vecInvaders;
	CFPSCounter* m_fpsCounter;

    int m_iWidth;
    int m_iHeight;

    int m_iInvadersRemaining;

    std::string m_strScore;

private:

};

#endif    // __LEVEL_H__
