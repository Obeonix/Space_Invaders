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
#include "resource.h"
#include "utils.h"

// This Include
#include "Ship.h"

// Static Variables

// Static Function Prototypes

// Implementation

CShip::CShip()
{

}

CShip::~CShip()
{

}

bool
CShip::Initialise()
{
    VALIDATE(CEntity::Initialise(IDB_PADDLESPRITE, IDB_PADDLEMASK));

    return (true);
}

void
CShip::Draw()
{
    CEntity::Draw();
}

void
CShip::Process(float _fDeltaTick)
{
    
	float fHalfShipW = static_cast<float>(m_pSprite->GetWidth() / 2.0);

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		m_fX += 400.0f * _fDeltaTick;
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{ 
		m_fX -= 400.0f * _fDeltaTick;
	}
	if (m_fX - fHalfShipW <= 0)
	{
		m_fX = fHalfShipW;
	}
	else if (m_fX + fHalfShipW >= 485)
	{
		m_fX = 485-fHalfShipW;
	}
	
	CEntity::Process(_fDeltaTick);
}
