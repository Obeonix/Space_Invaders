//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School.
//
// File Name	: 
// Description	: 
// Author		: Your Name
// Mail			: your.name@mediadesign.school.nz
//

// Library Includes

// Local Includes
#include "Game.h"
#include "Ship.h"
#include "Invaders.h"
//#include "Bullet.h"
#include "utils.h"
#include "backbuffer.h"
#include "framecounter.h"
#include "background.h"

// This Include
#include "Level.h"

// Static Variables

// Static Function Prototypes

// Implementation

#define CHEAT_BOUNCE_ON_BACK_WALL

CLevel::CLevel()
: m_iInvadersRemaining(0)
, m_pShip(0)
, m_pBullet(0)
, m_iWidth(0)
, m_iHeight(0)
, m_fpsCounter(0)
{

}

CLevel::~CLevel()
{
    while (m_vecInvaders.size() > 0)
    {
        CInvaders* pInvaders = m_vecInvaders[m_vecInvaders.size() - 1];

        m_vecInvaders.pop_back();

        delete pInvaders;
    }

    delete m_pShip;
    m_pShip = 0;

    delete m_pBullet;
    m_pBullet = 0;

	delete m_fpsCounter;
	m_fpsCounter = 0;

	delete m_pBackground;
	m_pBackground = 0;

}

bool
CLevel::Initialise(int _iWidth, int _iHeight)
{
    m_iWidth = _iWidth;
    m_iHeight = _iHeight;

    const float fBulletVelY = 275.0f;

	m_pBackground = new CBackGround();
	VALIDATE(m_pBackground->Initialise());
	//Set the background position to start from {0,0}
	m_pBackground->SetX((float)m_iWidth / 2);
	m_pBackground->SetY((float)m_iHeight / 2);

	//m_pBullet = new CBullet();
    //VALIDATE(m_pBullet->Initialise(m_iWidth / 2.0f, m_iHeight / 2.0f,  fBulletVelY));

    m_pShip = new CShip();
    VALIDATE(m_pShip->Initialise());

    // Set the paddle's position to be centered on the x, 
    // and a little bit up from the bottom of the window.
    m_pShip->SetX(_iWidth / 2.0f);
    m_pShip->SetY(_iHeight - ( 0.75f * m_pShip->GetHeight()));

    const int kiNumInavders = 45;
    const int kiStartX = 50;
    const int kiGap = 15;

    int iCurrentX = kiStartX;
    int iCurrentY = kiStartX;

    for (int i = 0; i < kiNumInavders; ++i)
    {
        CInvaders* pInvaders = new CInvaders();
        VALIDATE(pInvaders->Initialise());

        pInvaders->SetX(static_cast<float>(iCurrentX));
        pInvaders->SetY(static_cast<float>(iCurrentY));

        iCurrentX += static_cast<int>(pInvaders->GetWidth()) + kiGap;

        if (iCurrentX > _iWidth - 20)
        {
            iCurrentX = kiStartX;
            iCurrentY += 40;
        }

        m_vecInvaders.push_back(pInvaders);
    }

    SetInvadersRemaining(kiNumInavders);
	m_fpsCounter = new CFPSCounter();
	VALIDATE(m_fpsCounter->Initialise());

    return (true);
}

void
CLevel::Draw()
{
	m_pBackground->Draw();
	for (unsigned int i = 0; i < m_vecInvaders.size(); ++i)
    {
        m_vecInvaders[i]->Draw();
    }

    m_pShip->Draw();
    //m_pBullet->Draw();

    DrawScore();
	DrawFPS();
}

void
CLevel::Process(float _fDeltaTick)
{
	m_pBackground->Process(_fDeltaTick);
	//m_pBullet->Process(_fDeltaTick);
	m_pShip->Process(_fDeltaTick);
	//ProcessBallWallCollision();
	//ProcessPaddleWallCollison();
    //ProcessBallPaddleCollision();
    //ProcessBallBrickCollision();

   // ProcessCheckForWin();
	//ProcessBulletBounds();

    for (unsigned int i = 0; i < m_vecInvaders.size(); ++i)
    {
        m_vecInvaders[i]->Process(_fDeltaTick);
    }
	
   
    
	m_fpsCounter->CountFramesPerSecond(_fDeltaTick);
}

CShip* 
CLevel::GetPaddle() const
{
    return (m_pShip);
}

//void 
//CLevel::ProcessBallWallCollision()
//{
//    float fBallX = m_pBullet->GetX();
//    float fBallY = m_pBullet->GetY();
//    float fBallW = m_pBullet->GetWidth();
//    float fBallH = m_pBullet->GetHeight();
//
//    float fHalfBallW = fBallW / 2;
//	float fHalfBallH = fBallH / 2;
//
//  
//	if (fBallY < fHalfBallH) //represents the situation when the ball has hit the top wall
//    {
//        m_pBullet->SetVelocityY(m_pBullet->GetVelocityY() * -1); //reverse the ball's y velocity
//    }
//
//#ifdef CHEAT_BOUNCE_ON_BACK_WALL
//	if (fBallY  > m_iHeight - fHalfBallH)  //represents the situation when the ball has hit the bottom wall
//    {
//        m_pBullet->SetVelocityY(m_pBullet->GetVelocityY() * -1); //reverse the ball's y velocity
//    }
//#endif //CHEAT_BOUNCE_ON_BACK_WALL
//}



//
//void
//CLevel::ProcessBallPaddleCollision()
//{
//    float fBallR = m_pBullet->GetRadius();
//
//    float fBallX = m_pBullet->GetX();
//    float fBallY = m_pBullet->GetY(); 
//
//    float fPaddleX = m_pShip->GetX();
//    float fPaddleY = m_pShip->GetY();
//
//    float fPaddleH = m_pShip->GetHeight();
//    float fPaddleW = m_pShip->GetWidth();
//
//    if ((fBallX + fBallR > fPaddleX - fPaddleW / 2) && //ball.right > paddle.left
//        (fBallX - fBallR < fPaddleX + fPaddleW / 2) && //ball.left < paddle.right
//        (fBallY + fBallR > fPaddleY - fPaddleH / 2) && //ball.bottom > paddle.top
//        (fBallY - fBallR < fPaddleY + fPaddleH / 2))  //ball.top < paddle.bottom
//    {
//        m_pBullet->SetY((fPaddleY - fPaddleH / 2) - fBallR);  //Set the ball.bottom = paddle.top; to prevent the ball from going through the paddle!
//        m_pBullet->SetVelocityY(m_pBullet->GetVelocityY() * -1); //Reverse ball's Y direction
//    }
//}

//void
//CLevel::ProcessBallBrickCollision()
//{
//    for (unsigned int i = 0; i < m_vecInvaders.size(); ++i)
//    {
//        if (!m_vecInvaders[i]->IsHit())
//        {
//            float fBallR = m_pBullet->GetRadius();
//
//            float fBallX = m_pBullet->GetX();
//            float fBallY = m_pBullet->GetY(); 
//
//            float fBrickX = m_vecInvaders[i]->GetX();
//            float fBrickY = m_vecInvaders[i]->GetY();
//
//            float fBrickH = m_vecInvaders[i]->GetHeight();
//            float fBrickW = m_vecInvaders[i]->GetWidth();
//
//            if ((fBallX + fBallR > fBrickX - fBrickW / 2) &&
//                (fBallX - fBallR < fBrickX + fBrickW / 2) &&
//                (fBallY + fBallR > fBrickY - fBrickH / 2) &&
//                (fBallY - fBallR < fBrickY + fBrickH / 2))
//            {
//                //Hit the front side of the brick...
//                m_pBullet->SetY((fBrickY + fBrickH / 2.0f) + fBallR);
//                m_pBullet->SetVelocityY(m_pBullet->GetVelocityY() * -1);
//                m_vecInvaders[i]->SetHit(true);
//
//                SetInvadersRemaining(GetInvadersRemaining() - 1);
//            }
//        }
//    }
//}

void
CLevel::ProcessCheckForWin()
{
    for (unsigned int i = 0; i < m_vecInvaders.size(); ++i)
    {
        if (!m_vecInvaders[i]->IsHit())
        {
            return;
        }
    }

    CGame::GetInstance().GameOverWon();
}

//void
//CLevel::ProcessBulletBounds()
//{
//	if (m_pBullet->GetX() < 0)
//    {
//        m_pBullet->SetX(0);
//    }
//	else if (m_pBullet->GetX() > m_iWidth)
//    {
//        m_pBullet->SetX(static_cast<float>(m_iWidth));
//    }
//
//    if (m_pBullet->GetY() < 0)
//    {
//        m_pBullet->SetY(0.0f);
//    }
//    else if (m_pBullet->GetY() > m_iHeight)
//    {
//        CGame::GetInstance().GameOverLost();
//        //m_pBall->SetY(static_cast<float>(m_iHeight));
//    }
//}

int 
CLevel::GetInvadersRemaining() const
{
    return (m_iInvadersRemaining);
}

void 
CLevel::SetInvadersRemaining(int _i)
{
    m_iInvadersRemaining = _i;
    UpdateScoreText();
}

void
CLevel::DrawScore()
{
    HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC();

    const int kiX = 0;
    const int kiY = m_iHeight - 14;
	SetBkMode(hdc, TRANSPARENT);
	COLORREF oldcolor = static_cast<COLORREF>(SetTextColor( hdc,RGB(255,255,255)));

    TextOutA(hdc, 35, 6, m_strScore.c_str(), static_cast<int>(m_strScore.size()));
}



void 
CLevel::UpdateScoreText()
{
    m_strScore = "Invooders Remooning: ";

    m_strScore += ToString(GetInvadersRemaining());
}


void 
CLevel::DrawFPS()
{

	HDC hdc = CGame::GetInstance().GetBackBuffer()->GetBFDC(); 
	

	m_fpsCounter->DrawFPSText(hdc, m_iWidth-145, 20);

}
