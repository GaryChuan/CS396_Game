/******************************************************************************
filename: health.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of Health component.
******************************************************************************/
#pragma once

struct Health
{
	constexpr static auto typedef_v 
		= xecs::component::type::data
		{
			.m_pName = "Health"
		};

	float mValue;
};