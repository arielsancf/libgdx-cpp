
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

#ifndef GDX_CPP_GRAPHICS_G2D_TILED_TILEATLAS_HPP_
#define GDX_CPP_GRAPHICS_G2D_TILED_TILEATLAS_HPP_

namespace gdx {

class TileAtlas: public Disposable {
public:
    TextureRegion& getRegion (int id);
    void dispose ();

protected:


private:
    static std::string& removeExtension (const std::string& s);
    static std::string& removePath (const std::string& s);
    static FileHandle& getRelativeFileHandle (const FileHandle& path,const std::string& relativePath);
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_G2D_TILED_TILEATLAS_HPP_
