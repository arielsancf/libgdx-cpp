
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

#ifndef GDX_CPP_SCENES_SCENE2D_LAYOUT_HPP_
#define GDX_CPP_SCENES_SCENE2D_LAYOUT_HPP_

namespace gdx {
namespace scenes {
namespace scene2d {

class Layout {
public:
    virtual   void layout () = 0;
    virtual   void invalidate () = 0;
    virtual   float getMinWidth () = 0;
    virtual   float getMinHeight () = 0;
    virtual   float getPrefWidth () = 0;
    virtual   float getPrefHeight () = 0;
    virtual   float getMaxWidth () = 0;
    virtual   float getMaxHeight () = 0;
};

} // namespace gdx
} // namespace scenes
} // namespace scene2d

#endif // GDX_CPP_SCENES_SCENE2D_LAYOUT_HPP_
