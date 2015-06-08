#ifndef TILE_H
#define TILE_H

#include "../Common/amath.h"
#include "../Management/entityManager.h"
//#include <gl/gl.h>

class tileEntityManager;
class entityManager;
class scriptMng;
class projectTreeView;

using namespace vector_math;

class frameEvent;

class Tile : public Entity
{
    private:

        bool edit_tiles;

        Vec3<float> tile_position;  ///Tile Position
        Vec3<float> tile_scale;
        Vec3<float> tile_pivot;     ///Tile Position
        Vec4<float> tile_color;

        tileEntityManager * tiles_r;
        projectTreeView * tree_view;

		int layer;                  ///Active Layer
        unsigned int d_tex;         ///Default Texture

		int n_sprite;               ///Total Number of Sprites
        int rn_sprite;              ///Number of Sprites [row]
        int cn_sprite;              ///Number of Sprites [column]

        float tile_offset;          ///Offset the tiled objects apart from each other

        void Pivot_Visible(bool v_pivot = false);   ///Show Visible Pivot

    public:

        Tile();
        ~Tile();

        void init(scriptMng * script_manager = NULL);
        void BindTileToScriptManager(scriptMng * script_manager);
        void BindTileToTreeView(projectTreeView * tree_view);

        void picking();
        void draw();

        void setPosition(float x=0.0f, float y=0.0f, float z=0.0f);
        void setPosition(float position[3]);
        void setPosition(Vec3<float> position);

        void setScale(float x=1.0f, float y=1.0f, float z=1.0f);
        Vec3<float> getScale();

        void setColor(float r=1.0f, float g=1.0f, float b=1.0f, float a=1.0f);
        Vec4<float> getColor();

        Vec3<float> getPosition();

        void setTexture(unsigned int textureID=0);
        unsigned int  getTexture();

        void setPivot(float x=0.0f, float y=0.0f, float z=0.0f);
        void setPivot(float position[3]);
        void setPivot(Vec3<float> position);

        void setEditable(bool editable = false);
        bool isEditable();

        Entity * getSubEntity(unsigned char * colorID);

};

#endif // TILE_H
