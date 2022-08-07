/******************************************************************************
filename: bullet.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of Bullet component.
******************************************************************************/
#pragma once

struct Bullet
{
	constexpr static auto typedef_v
		= xecs::component::type::data
		{
			.m_pName = "Bullet"
		};

	float mDamage{};
	float mPushback{};
};