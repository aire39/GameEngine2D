#ifndef DATAPROPERTYVIEWER_H
#define DATAPROPERTYVIEWER_H


#include <wx/window.h>
#include <wx/colour.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>

class projectTreeView;

class DataPropertyViewer : public wxPropertyGrid
{
    DECLARE_EVENT_TABLE()

    private:

        projectTreeView * tree_viewer;

        wxPGProperty * pg_ctg;
        wxStringProperty  pg_name;
        wxColourProperty  pg_color;
        wxFloatProperty   pg_opacity;
        wxPGProperty * pg_position;
            wxFloatProperty  * pg_x;
            wxFloatProperty  * pg_y;
            wxFloatProperty  * pg_z;
        wxFloatProperty   pg_rotate;
        wxPGProperty * pg_scale;
            wxFloatProperty  * pg_sx;
            wxFloatProperty  * pg_sy;
            wxFloatProperty  * pg_sz;
        wxIntProperty     pg_layer;

        ///////////////////////////////////////
        wxPGProperty * pg_ctg_texture;
            wxIntProperty   pg_textureRepeatX;
            wxIntProperty   pg_textureRepeatY;
            wxBoolProperty  pg_textureFlipX;
            wxBoolProperty  pg_textureFlipY;

        ///////////////////////////////////////
        wxPGProperty * pg_ctg_text;
            wxStringProperty pg_text;
            wxStringProperty pg_font;

        ///////////////////////////////////////
        wxPGProperty * pg_ctg_animation;
            wxBoolProperty  pg_enable_animation;
            wxEnumProperty *pg_attached_animation;
            wxArrayString   anim_name_array;
            wxIntProperty   pg_start_frame;
            wxIntProperty   pg_end_frame;
            wxIntProperty   pg_frame_rate;
            wxEnumProperty  pg_play_options;

    public:
        DataPropertyViewer(wxWindow * parent, wxWindowID id=wxID_ANY);
        ~DataPropertyViewer();

        void BindTreeViewer( projectTreeView * tree_viewer );

        void SetDataName(std::string name);
        void SetDataColor(float r, float g, float b);
        void SetDataOpacity(float o=1.0f);
        void SetDataPosition(float x, float y, float z);
        void SetDataRotate(float r);
        void SetDataScale(float x, float y, float z);
        void SetDataLayer(int layer);
        ////////////////
        void SetDataText(std::string);

        ////////////////
        void SetDataEnableAnim(bool b);
        void SetDataAttachdAnimation(wxArrayString str_array);
        void SetDataStartframe(int frame);
        void SetDataFramerate(int framerate);

        ////////////////
        void SetDataTextureRepeatX(int x=1);
        void SetDataTextureRepeatY(int y=1);
        void SetDataTextureFlipX(bool b = true);
        void SetDataTextureFlipY(bool b = true);

        /////////////////////////////////
        /////////////////////////////////
        /////////////////////////////////

        std::string GetDataName();
        float * GetDataColor();
        float   GetDataOpacity();
        float * GetDataPosition();
        float   GetDataRotate();
        float * GetDataScale();
        int     GetDataLayer();
        //////////////////
        std::string GetDataText();

        //////////////////
        bool GetDataEnableAnim();
        int  GetDataAttachedAnimationChoice();
        int  GetDataStartframe();
        int  GetDataFramerate();

        ///////////////////
        int  GetDataTextureRepeatX();
        int  GetDataTextureRepeatY();
        bool GetDataTextureFlipX();
        bool GetDataTextureFlipY();

        /////////////////////////////////
        /////////////////////////////////
        /////////////////////////////////

        void UseAnimationCategory(bool b = true, std::string specific_type_param="default");
        void UseTextCategory(bool b = true);
        void UseTextureCategory(bool b = true, std::string specific_type_param="default");
};

#endif // DATAPROPERTYVIEWER_H
