
/*
    Copyright 2011 Aevum Software aevum @ aevumlab.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
    @author Ozires Bortolon de Faria ozires@aevumlab.com
*/

#include "NinePatch.hpp"
#include <stdexcept>
#include "gdx-cpp/graphics/Texture.hpp"
#include "gdx-cpp/graphics/g2d/SpriteBatch.hpp"
#include "TextureRegion.hpp"

using namespace gdx;

NinePatch::NinePatch ( const Texture::ptr& texture, int left, int right, int top, int bottom ) {
    initialize(TextureRegion(texture), left, right, top, bottom);
}

NinePatch::NinePatch (TextureRegion region, int left, int right, int top, int bottom) {
    initialize(region, left, right, top, bottom);
}

void NinePatch::initialize(TextureRegion region, int left, int right, int top, int bottom)
{
    int middleWidth = region.getRegionWidth() - left - right;
    int middleHeight = region.getRegionHeight() - top - bottom;
    
    patches[0] = TextureRegion(region, 0, 0, left, top);
    patches[1] = TextureRegion(region, left, 0, middleWidth, top);
    patches[2] = TextureRegion(region, left + middleWidth, 0, right, top);
    patches[3] = TextureRegion(region, 0, top, left, middleHeight);
    patches[4] = TextureRegion(region, left, top, middleWidth, middleHeight);
    patches[5] = TextureRegion(region, left + middleWidth, top, right, middleHeight);
    patches[6] = TextureRegion(region, 0, top + middleHeight, left, bottom);
    patches[7] = TextureRegion(region, left, top + middleHeight, middleWidth, bottom);
    patches[8] = TextureRegion(region, left + middleWidth, top + middleHeight, right, bottom);
}

NinePatch::NinePatch ( std::array< TextureRegion, 9 >& _patches ): patches(_patches)
{
    if (patches.size() != 9) gdx_log_error("NinePatch","NinePatch needs nine TextureRegions");
    this->patches = patches;
    checkValidity();
}

void NinePatch::checkValidity () {
    if (patches[(int)Sides::BOTTOM_LEFT].getRegionWidth() != patches[(int)Sides::TOP_LEFT].getRegionWidth()
            || patches[(int)Sides::BOTTOM_LEFT].getRegionWidth() != patches[(int)Sides::MIDDLE_LEFT].getRegionWidth()) {
        gdx_log_error("NinePatch","Left side patches must have the same width");
    }

    if (patches[(int)Sides::BOTTOM_RIGHT].getRegionWidth() != patches[(int)Sides::TOP_RIGHT].getRegionWidth()
            || patches[(int)Sides::BOTTOM_RIGHT].getRegionWidth() != patches[(int)Sides::MIDDLE_RIGHT].getRegionWidth()) {
        gdx_log_error("NinePatch","Right side patches must have the same width");
    }

    if (patches[(int)Sides::BOTTOM_LEFT].getRegionHeight() != patches[(int)Sides::BOTTOM_CENTER].getRegionHeight()
            || patches[(int)Sides::BOTTOM_LEFT].getRegionHeight() != patches[(int)Sides::BOTTOM_RIGHT].getRegionHeight()) {
        gdx_log_error("NinePatch","Bottom patches must have the same height");
    }

    if (patches[(int)Sides::TOP_LEFT].getRegionHeight() != patches[(int)Sides::TOP_CENTER].getRegionHeight()
            || patches[(int)Sides::TOP_LEFT].getRegionHeight() != patches[(int)Sides::TOP_RIGHT].getRegionHeight()) {
        gdx_log_error("NinePatch","Top patches must have the same height");
    }
}

void NinePatch::draw (SpriteBatch& batch,float x,float y,float width,float height) {
    float centerColumnX = x;
    if (patches[(int)Sides::BOTTOM_LEFT].isValid())
        centerColumnX += patches[(int)Sides::BOTTOM_LEFT].getRegionWidth();
    else if (patches[(int)Sides::MIDDLE_LEFT].isValid())
        centerColumnX += patches[(int)Sides::MIDDLE_LEFT].getRegionWidth();
    else if (patches[(int)Sides::TOP_LEFT].isValid()) //
        centerColumnX += patches[(int)Sides::TOP_LEFT].getRegionWidth();

    float rightColumnX = x + width;
    if (patches[(int)Sides::BOTTOM_RIGHT].isValid())
        rightColumnX -= patches[(int)Sides::BOTTOM_RIGHT].getRegionWidth();
    else if (patches[(int)Sides::MIDDLE_RIGHT].isValid())
        rightColumnX += patches[(int)Sides::MIDDLE_RIGHT].getRegionWidth();
    else if (patches[(int)Sides::TOP_RIGHT].isValid()) //
        rightColumnX += patches[(int)Sides::TOP_RIGHT].getRegionWidth();

    float middleRowY = y;
    if (patches[(int)Sides::TOP_LEFT].isValid())
        middleRowY += patches[(int)Sides::TOP_LEFT].getRegionHeight();
    else if (patches[(int)Sides::TOP_CENTER].isValid())
        middleRowY += patches[(int)Sides::TOP_CENTER].getRegionHeight();
    else if (patches[(int)Sides::TOP_RIGHT].isValid()) //
        middleRowY += patches[(int)Sides::TOP_RIGHT].getRegionHeight();

    float topRowY = y + height;
    if (patches[(int)Sides::TOP_LEFT].isValid())
        topRowY -= patches[(int)Sides::TOP_LEFT].getRegionHeight();
    else if (patches[(int)Sides::TOP_CENTER].isValid())
        topRowY -= patches[(int)Sides::TOP_CENTER].getRegionHeight();
    else if (patches[(int)Sides::TOP_RIGHT].isValid()) //
        topRowY -= patches[(int)Sides::TOP_RIGHT].getRegionHeight();

    // Bottom row
    if (patches[(int)Sides::BOTTOM_LEFT].isValid()) batch.draw(patches[(int)Sides::BOTTOM_LEFT], x, y, centerColumnX - x, middleRowY - y);
    if (patches[(int)Sides::BOTTOM_CENTER].isValid())
        batch.draw(patches[(int)Sides::BOTTOM_CENTER], centerColumnX, y, rightColumnX - centerColumnX, middleRowY - y);
    if (patches[(int)Sides::BOTTOM_RIGHT].isValid())
        batch.draw(patches[(int)Sides::BOTTOM_RIGHT], rightColumnX, y, x + width - rightColumnX, middleRowY - y);

    // Middle row
    if (patches[(int)Sides::MIDDLE_LEFT].isValid()) batch.draw(patches[(int)Sides::MIDDLE_LEFT], x, middleRowY, centerColumnX - x, topRowY - middleRowY);
    if (patches[(int)Sides::MIDDLE_CENTER].isValid())
        batch.draw(patches[(int)Sides::MIDDLE_CENTER], centerColumnX, middleRowY, rightColumnX - centerColumnX, topRowY - middleRowY);
    if (patches[(int)Sides::MIDDLE_RIGHT].isValid())
        batch.draw(patches[(int)Sides::MIDDLE_RIGHT], rightColumnX, middleRowY, x + width - rightColumnX, topRowY - middleRowY);

    // Top row
    if (patches[(int)Sides::TOP_LEFT].isValid()) batch.draw(patches[(int)Sides::TOP_LEFT], x, topRowY, centerColumnX - x, y + height - topRowY);
    if (patches[(int)Sides::TOP_CENTER].isValid())
        batch.draw(patches[(int)Sides::TOP_CENTER], centerColumnX, topRowY, rightColumnX - centerColumnX, y + height - topRowY);
    if (patches[(int)Sides::TOP_RIGHT].isValid())
        batch.draw(patches[(int)Sides::TOP_RIGHT], rightColumnX, topRowY, x + width - rightColumnX, y + height - topRowY);
}

float NinePatch::getLeftWidth () {
    return !patches[(int)Sides::TOP_LEFT].isValid() ? 0 : patches[(int)Sides::TOP_LEFT].getRegionWidth();
}

float NinePatch::getRightWidth () {
    return !patches[(int)Sides::TOP_RIGHT].isValid() ? 0 : patches[(int)Sides::TOP_RIGHT].getRegionWidth();
}

float NinePatch::getTopHeight () {
    return !patches[(int)Sides::TOP_RIGHT].isValid() ? 0 : patches[(int)Sides::TOP_RIGHT].getRegionHeight();
}

float NinePatch::getBottomHeight () {
    return !patches[(int)Sides::BOTTOM_RIGHT].isValid() ? 0 : patches[(int)Sides::BOTTOM_RIGHT].getRegionHeight();
}

float NinePatch::getTotalHeight () {
    float totalHeight = getTopHeight() + getBottomHeight();
    if (patches[(int)Sides::MIDDLE_CENTER].isValid()) totalHeight += patches[(int)Sides::MIDDLE_CENTER].getRegionHeight();
    
    return totalHeight;
}

float NinePatch::getTotalWidth () {
    float totalWidth = getLeftWidth() + getRightWidth();
    if (patches[(int)Sides::MIDDLE_CENTER].isValid()) totalWidth += patches[(int)Sides::MIDDLE_CENTER].getRegionWidth();
    
    return totalWidth;
}

std::array< TextureRegion, 9 > NinePatch::getPatches()
{
    return patches;
}

NinePatch::NinePatch( TextureRegion region )
{
    patches[4] = region;
}
