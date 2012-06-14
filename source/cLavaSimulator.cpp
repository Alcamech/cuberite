#include "Globals.h"
#include "cLavaSimulator.h"
#include "Defines.h"
#include "cWorld.h"


cLavaSimulator::cLavaSimulator(cWorld *a_World)
	: cFluidSimulator(a_World)
{
	m_FluidBlock = E_BLOCK_LAVA;
	m_StationaryFluidBlock = E_BLOCK_STATIONARY_LAVA;
	m_MaxHeight = 6;
	m_FlowReduction = 2;
}


bool cLavaSimulator::IsAllowedBlock(char a_BlockID)
{
	return IsBlockLava(a_BlockID);
}