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
#include "Invaders.h"

// Static Variables

// Static Function Prototypes

// Implementation

CInvaders::CInvaders()
: m_bHit(false)
{

}

CInvaders::~CInvaders()
{

}

bool
CInvaders::Initialise()
{
    VALIDATE(CEntity::Initialise(IDB_BRICKSPRITE, IDB_BRICKMASK));

    return (true);
}

void
CInvaders::Draw()
{
    if (!m_bHit)
    {
        CEntity::Draw();
    }
}

void
CInvaders::Process(float _fDeltaTick)
{
    if (!m_bHit)
    {
        CEntity::Process(_fDeltaTick);
    }
}

void
CInvaders::SetHit(bool _b)
{
    m_bHit = _b;
}

bool
CInvaders::IsHit() const
{
    return (m_bHit);
}

