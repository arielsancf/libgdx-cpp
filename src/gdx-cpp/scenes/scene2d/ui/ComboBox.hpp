
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

#ifndef GDX_CPP_SCENES_SCENE2D_UI_COMBOBOX_HPP_
#define GDX_CPP_SCENES_SCENE2D_UI_COMBOBOX_HPP_

namespace gdx {
namespace scenes {
namespace scene2d {
namespace ui {

class ComboBox {
public:
    void setStyle (const ComboBoxStyle& style);
    void setItems ();
    void layout ();
    void draw (const gdx::SpriteBatch& batch,float parentAlpha);
    bool touchDown (float x,float y,int pointer);
    void touchUp (float x,float y,int pointer);
    void touchDragged (float x,float y,int pointer);
    void selected (const ComboBox& comboBox,int selectionIndex,const std::string& selection);
    void setSelectionListener (const SelectionListener& listener);
    void draw (const gdx::SpriteBatch& batch,float parentAlpha);
    bool touchDown (float x,float y,int pointer);
    void touchUp (float x,float y,int pointer);
    void touchDragged (float x,float y,int pointer);
    bool touchMoved (float x,float y);
    gdx::Actor& hit (float x,float y);
    void act (float delta);
    void setSelection (int selection);
    int getSelectionIndex ();
    std::string& getSelection ();
    float getPrefWidth ();
    float getPrefHeight ();
    ComboBox (const gdx::Stage& stage,const Skin& skin);
    ComboBox (const gdx::Stage& stage,const ComboBoxStyle& style);
    ComboBox (const gdx::Stage& stage,const ComboBoxStyle& style,const std::string& name);

protected:
    Stage stage ;
    ComboBoxStyle style ;
    String[] items ;
    int selection = 0;
    TextBounds bounds = new TextBounds();
    Vector2 screenCoords = new Vector2();
    ComboList list = null;
    SelectionListener listener ;

private:
    void layout ();
};

} // namespace gdx
} // namespace scenes
} // namespace scene2d
} // namespace ui

#endif // GDX_CPP_SCENES_SCENE2D_UI_COMBOBOX_HPP_
