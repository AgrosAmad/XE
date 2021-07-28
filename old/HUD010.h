#pragma once

// STL
#include <string>

// Project
#include "OpenGLWindow.h"
#include "HUDBase.h"
#include "texture.h"

namespace XE
{
    /**
     * HUD for tutorial 010.
     */
    class HUD010 : public HUDBase
    {
    public:
        const static std::string CHRISTMAS_TREE_TEXTURE_KEY;
        const static std::string SNOWFLAKE_TREE_TEXTURE_KEY;

        HUD010(const OpenGLWindow& window);

        /**
         * Checks, if blending in HUD is enabled.
         */
        bool isBlendingEnabled() const;

        /**
         * Toggles blending.
         */
        void toggleBlending();

        /**
         * Renders HUD.
        */
        void renderHUD() const override;

    private:
        bool BlendingEnabled = true; // Flag telling, if blending is enabled

        /**
         * Gets Christmas tree texture.
         */
        const Texture& getChristmasTreeTexture() const;

        /**
         * Gets snowlake texture.
         */
        const Texture& getSnowflakeTexture() const;
    };
} // namespace XE
