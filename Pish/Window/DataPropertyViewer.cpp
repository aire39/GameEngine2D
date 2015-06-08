#include "../Window/DataPropertyViewer.h"
#include <iostream>
#include <typeinfo>

DataPropertyViewer::DataPropertyViewer(wxWindow * parent, wxWindowID id) : wxPropertyGrid(parent, id)
{
    SetWindowStyle(wxPG_BOLD_MODIFIED | wxPG_TOOLTIPS);

    pg_ctg_animation = NULL;
    pg_ctg_text = NULL;
    pg_ctg = NULL;
    pg_ctg_texture = NULL;

    pg_attached_animation = NULL;

    tree_viewer = NULL;

    pg_name.SetLabel("name");
    pg_name.SetValue("<none>");

    pg_color.SetLabel("color");
    pg_opacity.SetLabel("opacity");

    pg_rotate.SetLabel("rotate");
    pg_layer.SetLabel("layer");

    //Basic Category
    pg_ctg = Append( new wxPropertyCategory("Properties")); //Causes A Crash When Exiting Program

    Append( &pg_name );
    Append( &pg_color );
    Append( &pg_opacity );
    pg_position = Append( new wxStringProperty(wxT("position"),
                            "name_pos",
                            wxT("<composed>")));


    pg_x = (wxFloatProperty*)AppendIn( pg_position, new wxFloatProperty(wxT("x"),
                                                      wxPG_LABEL,
                                                      0.0f) );

    pg_y = (wxFloatProperty*)AppendIn( pg_position, new wxFloatProperty(wxT("y"),
                                                      wxPG_LABEL,
                                                      0.0f) );

    pg_z = (wxFloatProperty*)AppendIn( pg_position, new wxFloatProperty(wxT("z"),
                                                      wxPG_LABEL,
                                                      0.0f) );


    Append( &pg_rotate );

    pg_scale = Append( new wxStringProperty(wxT("scale"),
                            "name_scale",
                            wxT("<composed>")));

    pg_sx = (wxFloatProperty*)AppendIn( pg_scale, new wxFloatProperty(wxT("x"),
                                                      wxPG_LABEL,
                                                      1.0f) );

    pg_sy = (wxFloatProperty*)AppendIn( pg_scale, new wxFloatProperty(wxT("y"),
                                                      wxPG_LABEL,
                                                      1.0f) );

    pg_sz = (wxFloatProperty*)AppendIn( pg_scale, new wxFloatProperty(wxT("z"),
                                                      wxPG_LABEL,
                                                      1.0f) );

    Append( &pg_layer );

    this->CollapseAll();
    this->SetSplitterLeft();
    //Expand( pg_ctg );
}

DataPropertyViewer::~DataPropertyViewer()
{
    tree_viewer = NULL;
    //Clear();
}

void DataPropertyViewer::BindTreeViewer( projectTreeView * tree_viewer )
{
    this->tree_viewer = tree_viewer;
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//////////////////////////Set Data/////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

///////////////////////////
//////Default Settings/////
///////////////////////////

void DataPropertyViewer::SetDataName(std::string name)
{
    pg_name.SetValue(name.c_str());
}

void DataPropertyViewer::SetDataColor(float r, float g, float b)
{
    char rvalue = 255;
    char gvalue = 255;
    char bvalue = 255;

    if( r < 1.0f )
        rvalue = 255*r;

    if( g < 1.0f )
        gvalue = 255*g;

    if( b < 1.0f )
        bvalue = 255*b;

    pg_color.SetValue(&wxColour(rvalue, gvalue, bvalue));
}

void DataPropertyViewer::SetDataOpacity(float o)
{
    if( o > 1.0f)
        o = 1.0f;
    else if( o < 0.0f)
        o = 0.0f;

    pg_opacity.SetValue(o);
}

void DataPropertyViewer::SetDataPosition(float x, float y, float z)
{
    pg_x->SetValue(x);
    pg_y->SetValue(y);
    pg_z->SetValue(z);
}

void DataPropertyViewer::SetDataRotate(float r)
{
    pg_rotate.SetValue(r);
}

void DataPropertyViewer::SetDataScale(float sx, float sy, float sz)
{
    pg_sx->SetValue(sx);
    pg_sy->SetValue(sy);
    pg_sz->SetValue(sz);
}

void DataPropertyViewer::SetDataLayer(int layer)
{
    pg_layer.SetValue(layer);
}

void DataPropertyViewer::SetDataText(std::string text)
{
    pg_text.SetValue(text.c_str());
}

///////////////////////////
////Animation Settings/////
///////////////////////////

void DataPropertyViewer::SetDataEnableAnim(bool b)
{
    pg_enable_animation.SetValue(b);
}

void DataPropertyViewer::SetDataAttachdAnimation(wxArrayString str_array)
{
    anim_name_array = str_array;
}

void DataPropertyViewer::SetDataFramerate(int framerate)
{
    pg_frame_rate.SetValue(framerate);
}

///////////////////////////
//////Texture Settings/////
///////////////////////////

void DataPropertyViewer::SetDataTextureRepeatX(int x)
{
    pg_textureRepeatX.SetValue(x);
}

void DataPropertyViewer::SetDataTextureRepeatY(int y)
{
    pg_textureRepeatY.SetValue(y);
}

void DataPropertyViewer::SetDataTextureFlipX(bool b)
{
    pg_textureFlipX.SetValue(b);
}

void DataPropertyViewer::SetDataTextureFlipY(bool b)
{
    pg_textureFlipY.SetValue(b);
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//////////////////////////Get Data/////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

///////////////////////////
//////Default Settings/////
///////////////////////////

std::string DataPropertyViewer::GetDataName()
{
    return (const char*)pg_name.GetValue().GetString().c_str();
}

float * DataPropertyViewer::GetDataColor()
{
    wxColour rgb;
    float _color[3];
    rgb << pg_color.GetValue();
    _color[0] = (float)rgb.Red()/255.0f;
    _color[1] = (float)rgb.Green()/255.0f;
    _color[2] = (float)rgb.Blue()/255.0f;

    return &_color[0];
}

float DataPropertyViewer::GetDataOpacity()
{
    return (float)pg_opacity.GetValue().GetDouble();
}

float * DataPropertyViewer::GetDataPosition()
{
    float position[3];

    position[0] = (float)pg_x->GetValue().GetDouble();
    position[1] = (float)pg_y->GetValue().GetDouble();
    position[2] = (float)pg_z->GetValue().GetDouble();

    return &position[0];
}

float DataPropertyViewer::GetDataRotate()
{
    return (float)pg_rotate.GetValue().GetDouble();
}

float * DataPropertyViewer::GetDataScale()
{
    float scale[3];
    scale[0] = (float)pg_sx->GetValue().GetDouble();
    scale[1] = (float)pg_sy->GetValue().GetDouble();
    scale[2] = (float)pg_sz->GetValue().GetDouble();

    return &scale[0];
}

int DataPropertyViewer::GetDataLayer()
{
    return pg_layer.GetValue().GetInteger();
}

std::string DataPropertyViewer::GetDataText()
{
    return (const char*)pg_text.GetValue().GetString().c_str();
}

///////////////////////////
////Animation Settings/////
///////////////////////////

bool DataPropertyViewer::GetDataEnableAnim()
{
    return pg_enable_animation.GetValue().GetBool();
}

int DataPropertyViewer::GetDataAttachedAnimationChoice()
{
    return pg_attached_animation->GetValue().GetInteger();
}

int DataPropertyViewer::GetDataFramerate()
{
    return pg_frame_rate.GetValue().GetInteger();
}

///////////////////////////
//////Texture Settings/////
///////////////////////////

int DataPropertyViewer::GetDataTextureRepeatX()
{
    return pg_textureRepeatX.GetValue().GetInteger();
}

int DataPropertyViewer::GetDataTextureRepeatY()
{
    return pg_textureRepeatY.GetValue().GetInteger();
}

bool DataPropertyViewer::GetDataTextureFlipX()
{
    return pg_textureFlipX.GetValue().GetBool();
}

bool DataPropertyViewer::GetDataTextureFlipY()
{
    return pg_textureFlipY.GetValue().GetBool();
}

///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
//////////////////////////Functions////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

void DataPropertyViewer::UseAnimationCategory(bool b, std::string specific_type_param)
{

    if( b == true )
    {
        pg_enable_animation.SetLabel("enable");
        pg_enable_animation.SetEditor( wxPGEditor_CheckBox );
        pg_frame_rate.SetLabel("frame rate");

        pg_ctg_animation = Append( new wxPropertyCategory("animation") );
        Append( &pg_enable_animation );

        if( specific_type_param.compare("sprite") == 0)
            pg_attached_animation = (wxEnumProperty*)Append( new wxEnumProperty("anims", wxPG_LABEL, anim_name_array) );

        Append( &pg_frame_rate );

        this->CollapseAll();

    }
    else
    {

        if( pg_ctg_animation != NULL )
        {
            RemoveProperty( &pg_frame_rate );

            if( pg_attached_animation != NULL )
            {
                RemoveProperty( pg_attached_animation );
                pg_attached_animation = NULL;
            }

            RemoveProperty( &pg_enable_animation );
            RemoveProperty(pg_ctg_animation);
            pg_ctg_animation = NULL;
        }
    }
}

void DataPropertyViewer::UseTextCategory(bool b)
{

    if( b == true )
    {

        pg_ctg_text = Append( new wxPropertyCategory("text") );

        pg_text.SetLabel("text value");
        pg_text.SetValue("Text");

        Append(&pg_text);

        this->CollapseAll();
    }
    else
    {
        if( pg_ctg_text != NULL )
        {
            RemoveProperty(&pg_text);
            RemoveProperty(pg_ctg_text);
            pg_ctg_text = NULL;
        }
    }

}

void DataPropertyViewer::UseTextureCategory(bool b, std::string specific_type_param)
{
    if( b == true )
    {

        if( specific_type_param.compare("sprite") == 0)
        {
            pg_textureRepeatX.SetLabel("RepeatX");
            pg_textureRepeatY.SetLabel("RepeatY");

            pg_textureFlipX.SetLabel("FlipX");
            pg_textureFlipY.SetLabel("FlipY");
            pg_textureFlipX.SetEditor( wxPGEditor_CheckBox );
            pg_textureFlipY.SetEditor( wxPGEditor_CheckBox );

            pg_ctg_texture = Append( new wxPropertyCategory("texture") );
            Append( &pg_textureRepeatX );
            Append( &pg_textureRepeatY );
            Append( &pg_textureFlipX );
            Append( &pg_textureFlipY );
        }

        this->CollapseAll();

    }
    else
    {

        if( pg_ctg_texture != NULL )
        {
            //if( SelectProperty(&pg_textureRepeatX) )

            RemoveProperty(&pg_textureRepeatX);
            RemoveProperty(&pg_textureRepeatY);
            RemoveProperty(&pg_textureFlipX);
            RemoveProperty(&pg_textureFlipY);
            RemoveProperty(pg_ctg_texture);
            pg_ctg_texture = NULL;

        }
    }
}

BEGIN_EVENT_TABLE( DataPropertyViewer, wxPropertyGrid )
END_EVENT_TABLE()
