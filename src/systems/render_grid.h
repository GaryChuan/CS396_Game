/******************************************************************************
filename: render_grid.h
author: Gary Chuan gary.chuan@digipen.edu
Project: CS396 Final Project
Description:
  This file contains the definition of RenderGrid which renders the grid.
  It is currently unused. Used for debugging purposes only.
******************************************************************************/
struct RenderGrid : xecs::system::instance
{
    constexpr static auto typedef_v = xecs::system::type::child_update<Renderer, Renderer::Update>
    {
        .m_pName = "render_grid"
    };

    using query = std::tuple
        <
        xecs::query::must<xecs::component::share_as_data_exclusive_tag>
        >;

    __inline
        void operator()(const GridCell& GridCell, const xecs::component::share_filter& ShareFilter) noexcept
    {
        // Hide nodes where there are not entities
        if constexpr (false)
        {
            int nEntities = 0;
            for (auto& ArchetypeCell : ShareFilter.m_lEntries)
                for (auto& Family : ArchetypeCell.m_lFamilies)
                    nEntities += static_cast<int>(Family->m_DefaultPool.Size());
            if (nEntities == 0) return;
        }

        const float X = ((GridCell.x - 1) + 0.5f + (GridCell.y & 1) * 0.5f) * Grid::CELL_WIDTH;
        const float Y = (GridCell.y + 0.5f) * Grid::CELL_HEIGHT;
        constexpr auto SizeX = Grid::CELL_WIDTH / 2.0f - 1;
        constexpr auto SizeY = Grid::CELL_HEIGHT / 2.0f - 1;

        glBegin(GL_QUADS);
        glColor3f(0.25f, 0.25f, 0.25f);
        glVertex2i(X - SizeX, Y - SizeY);
        glVertex2i(X - SizeX, Y + SizeY);
        glVertex2i(X + SizeX, Y + SizeY);
        glVertex2i(X + SizeX, Y - SizeY);
        glEnd();

        enum print
        {
            NONE
            , FAMILIES
            , ENTITIES
            , ARCHETYPES
            , GRIDCELL_XY
            , MAX_DISPLAY
        };

        // What are we printing?
        switch (print::ENTITIES)
        {
        case print::ARCHETYPES:
        {
            glColor3f(1.0f, 1.0f, 1.0f);
            // GlutPrint(X, Y - 15, "%d", ShareFilter.m_lEntries.size());
            break;
        }
        case print::FAMILIES:
        {
            int nFamilies = 0;
            for (auto& ArchetypeCell : ShareFilter.m_lEntries)
                nFamilies += static_cast<int>(ArchetypeCell.m_lFamilies.size());

            glColor3f(1.0f, 1.0f, 1.0f);
            // GlutPrint(X, Y - 15, "%d", nFamilies);
            break;
        }
        case print::ENTITIES:
        {
            int nEntities = 0;
            for (auto& ArchetypeCell : ShareFilter.m_lEntries)
                for (auto& Family : ArchetypeCell.m_lFamilies)
                    nEntities += static_cast<int>(Family->m_DefaultPool.Size());

            glColor3f(1.0f, 1.0f, 1.0f);
            // GlutPrint(X, Y - 15, "%d", nEntities);
            break;
        }
        case print::GRIDCELL_XY:
        {
            glColor3f(1.0f, 1.0f, 1.0f);
            // GlutPrint(X - 23, Y - 15, "%d,%d", GridCell.m_X, GridCell.m_Y);
            break;
        }
        }
    }
};
