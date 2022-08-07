/******************************************************************************
filename: destroy_particle_on_remove_timer.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of DestroyParticleOnRemoveTimer
  which handles deleting of particles when their lifetime (timer) ends.
******************************************************************************/
#pragma once

struct DestroyParticleOnRemoveTimer : xecs::system::instance
{
	constexpr static auto typedef_v =
		xecs::system::type::notify_moved_out
		{
			.m_pName = "DestroyParticleOnRemoveTimer"
		};

	using query = std::tuple
		<
			xecs::query::must<Timer, ParticleTag>
		>;

	__inline void operator()(xecs::component::entity& entity) noexcept
	{
		DeleteEntity(entity);
	}
};