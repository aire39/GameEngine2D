#ifndef MESH_H
#define MESH_H

#include "../Core/Entity.h"
#include "../Common/amath.h"
#include "../Common/GLee.h"
/**
Loads .obj(Alias Wavefront), .3ds(3D Studio Max), .dae(Collada) files
Only have the .obj code to load a 3d mesh atm...
*/
class Mesh : public Entity
{
    private:

        Vec3<float> position;
        void buildObject();

    public:
                ///Constructor
        Mesh();
                ///Destructor
        ~Mesh();
                    ///Initialize Mesh
        void init();
                    ///Render Mesh
        void draw();
};

#endif // MESH_H
