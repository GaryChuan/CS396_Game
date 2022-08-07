/******************************************************************************
filename: zombie_details.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of the ZombieDetails share component.
******************************************************************************/
#pragma once

struct ZombieDetails
{
	constexpr static auto typedef_v
		= xecs::component::type::share
	{
		.m_pName = "ZombieDetails"
	};

	float mMaxHealth{};
	float mMaxSpeed{};
	float mMaxAcceleration{};
};