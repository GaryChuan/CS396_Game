/******************************************************************************
filename: zombie_wave.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of the ZombieWave share component.
******************************************************************************/
#pragma once

struct ZombieWave
{
	constexpr static auto typedef_v
		= xecs::component::type::share
	{
		.m_pName = "ZombieWave",
		.m_bBuildFilter = true
	};

	int mID{};
};