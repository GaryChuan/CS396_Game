#pragma once

struct Grid
{
	static constexpr int CELL_WIDTH = 64;
	static constexpr int CELL_HEIGHT = 42;
	static constexpr int MAX_RESOLUTION_WIDTH = 1024;
	static constexpr int MAX_RESOLUTION_HEIGHT = 800;
	static constexpr std::int16_t CELL_ROW_COUNT = static_cast<std::int16_t>(MAX_RESOLUTION_WIDTH / CELL_WIDTH + 1);
	static constexpr std::int16_t CELL_COL_COUNT = static_cast<std::int16_t>(MAX_RESOLUTION_HEIGHT / CELL_HEIGHT + 1);

	template <typename TFunction>
	static constexpr __inline bool Search
	(
		xecs::system::instance& system,
		const xecs::component::share_filter& gridCellShareFilter,
		const std::int16_t xPos, const std::int16_t yPos,
		const xecs::query::instance& query,
		TFunction&& func
	) noexcept
	{
		static constexpr auto directions
			= std::array<std::int16_t, 2 * 6>
			{
				-1, 0,
				-1, 1,
				-1, 0,
				 0, 1,
				-1, 1,
				 0, 1
			};

		if (system.Foreach(gridCellShareFilter, query, std::forward<TFunction&&>(func)))
		{
			return true;
		}

		const int i = (yPos & 1) * (2 * 3);

		for (std::int16_t y = std::max(0, yPos - 1), 
			 endY = std::min(CELL_ROW_COUNT - 1, yPos + 1);
			 y <= endY; ++y)
		{
			auto shareFilter = system.findShareFilter
			(
				GridCell{ .x = xPos + directions[i], .y = yPos }
			);

			if (shareFilter 
			&& system.Foreach(
				*shareFilter, query, 
				std::forward<TFunction&&>(func)))
			{
				return true;
			}

			shareFilter = system.findShareFilter
			(
				GridCell{ .x = xPos + directions[i + 1], .y = yPos }
			);

			if (shareFilter
				&& system.Foreach(
					*shareFilter, query,
					std::forward<TFunction&&>(func)))
			{
				return true;
			}
		}

		return false;
	}

	__inline static constexpr GridCell ComputeGridCellFromWorldPosition(const xcore::vector2& pos)
	{
		const auto X = static_cast<int>(pos.m_X / (CELL_WIDTH / 2.0f));
		const auto Y = std::max(0, std::min(static_cast<int>(pos.m_Y / CELL_HEIGHT), CELL_ROW_COUNT - 1));
		const auto x = 1 & ((X ^ Y) & Y);
		
		return
		{ 
			static_cast<std::int16_t>(std::max(0, std::min(1 + ((X - x) >> 1), CELL_COL_COUNT - 1))), 
			static_cast<std::int16_t>(Y)
		};
	}
};