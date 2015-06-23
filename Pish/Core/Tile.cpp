#include "../Core/Tile.h"

Tile::Tile()
{
    //e_layer = 0;
    rn_sprite = 5;
    cn_sprite = 5;

    n_sprite = rn_sprite*cn_sprite;

    layer = 0;

    d_tex = 0;

    tile_offset = 2.1f;

    tile_pivot.setXY(0.0f, 0.0f);// Set Objects Pivot
    tile_scale.setXYZ(1.0f, 1.0f, 1.0f);
    tile_color.setXYZW(1.0f, 1.0f, 1.0f, 1.0f);

    edit_tiles = false;
}

Tile::~Tile()
{
    /*
    #ifdef __WXDEBUG__
        std::cout << "deleting tile: " << this->getName() << std::endl;
    #endif
    */

    delete tiles_r;

}

void Tile::Pivot_Visible(bool v_pivot)
{
    glPointSize(5.0f);
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glBegin(GL_POINTS);
        glVertex3fv(tile_pivot.getXYZ());
    glEnd();
    glPopMatrix();

    glColor3f(1.0f, 1.0f, 1.0f);
}

void Tile::setEditable(bool editable)
{
    edit_tiles = editable;
}

bool Tile::isEditable()
{
    return edit_tiles;
}

void Tile::init(scriptMng * script_manager)
{
    tiles_r = new tileEntityManager();

    tiles_r->BindScriptManager(script_manager);
    tiles_r->BindTreeView(tree_view);

    std::string tile_subname;
    char buf[12];

    ///Setup Sub Objects
    wxTreeItemId TileName = tree_view->searchTreeConfine( tree_view->GetSelection(), getName());
    tree_view->SelectItem(TileName);
    tree_view->addSubItem( tree_view->GetSelection(), "tile_objects", "entity", 0 );

    for(int i=0; i<rn_sprite; i++)
    {
        for(int j=0; j<cn_sprite; j++)
        {

            #ifdef __WIN32__
            itoa(j+(i*cn_sprite), buf, 10);
            #else
            sprintf(buf, "%d", j+(i*cn_sprite));
            #endif
            tile_subname = "tile_";
            tile_subname.append(buf);
            //std::cout << "*****TEST ADD TILE: PHASE III (LOOP)******" << std::endl;
            tiles_r->addEntity("sprite", "tile_objects", tile_subname);
            ((Sprite*)tiles_r->getEntity(tile_subname))->setPosition((float(j)*tile_offset)-(((cn_sprite-1)*tile_offset)/2.0f), (float(i)*tile_offset)-(((rn_sprite-1)*tile_offset)/2.0f));

        }
    }

    tree_view->printAllItemID();

}

void Tile::BindTileToScriptManager(scriptMng * script_manager)
{
    tiles_r->BindScriptManager(script_manager);
}

void Tile::BindTileToTreeView(projectTreeView * tree_view)
{
    this->tree_view = tree_view;
}

void Tile::setPosition(float x, float y, float z)
{
    tile_position.setXYZ(tile_pivot.getX()+x, tile_pivot.getY()+y, tile_pivot.getZ()+z);
}

void Tile::setPosition(float position[3])
{
    tile_position.setXYZ(tile_pivot.getX()+position[0], tile_pivot.getY()+position[1], tile_pivot.getZ()+position[2]);
}

void Tile::setPosition(Vec3<float> position)
{
    tile_position.setXYZ(tile_pivot.getX()+position.getX(), tile_pivot.getY()+position.getY(), tile_pivot.getZ()+position.getZ());
}

Vec3<float> Tile::getPosition()
{
    return tile_position;
}

void Tile::setScale(float x, float y, float z)
{
    tile_scale.setXYZ(x, y, z);
}

Vec3<float> Tile::getScale()
{
    return tile_scale;
}

void Tile::setColor(float r, float g, float b, float a)
{
    tile_color.setXYZW(r, g, b, a);
}

Vec4<float> Tile::getColor()
{
    return tile_color;
}

void Tile::setPivot(float x, float y, float z)
{
    tile_pivot.setXYZ(x, y, z);
}

void Tile::setPivot(float position[3])
{
    tile_pivot.setXYZ(position[0], position[1], position[2]);
}

void Tile::setPivot(Vec3<float> position)
{
    tile_pivot.setXYZ(position.getX(), position.getY(), position.getZ());
}

Entity * Tile::getSubEntity(unsigned char * colorID)
{
    return tiles_r->getEntitySub(colorID);
}

void Tile::setTexture(unsigned int textureID)
{
    d_tex = textureID;
    tiles_r->setTextureAll(d_tex);
}

unsigned int Tile::getTexture()
{
    return d_tex;
}

void Tile::picking()
{
    if( is_renderable )
    {
        if(edit_tiles)
        {
            glPushMatrix();
                glTranslatef(tile_position.getX(), tile_position.getY(), tile_position.getZ());
                glScalef(tile_scale.getX(), tile_scale.getY(), tile_scale.getZ());
                tiles_r->pickRender();
                Pivot_Visible(false);
            glPopMatrix();
        }
        else
        {
            glPushMatrix();
                glColor3f(colorID[0]/255.0f, colorID[1]/255.0f, colorID[2]/255.0f);
                glTranslatef(tile_position.getX(), tile_position.getY(), tile_position.getZ());
                glScalef(tile_scale.getX(), tile_scale.getY(), tile_scale.getZ());
                tiles_r->Render_Raw();
                Pivot_Visible(false);
            glPopMatrix();
        }
    }
}

void Tile::draw()
{
    if( is_renderable )
    {
        glPushMatrix();

            glTranslatef(tile_position.getX(), tile_position.getY(), tile_position.getZ());
            glScalef(tile_scale.getX(), tile_scale.getY(), tile_scale.getZ());
            tiles_r->Render();
            Pivot_Visible(true);

        glPopMatrix();
    }
}
