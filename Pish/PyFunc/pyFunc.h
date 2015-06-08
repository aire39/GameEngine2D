#ifndef PYFUNC_H
#define PYFUNC_H

#include "../Common/amath.h"

BOOST_PYTHON_MODULE(pshVectorMath)
{
/*
    class_< Vec4<float> >("vec4", init<>())
        .add_property("x", &Vec4<float>::setX, &Vec4<float>::getX)
        .add_property("y", &Vec4<float>::setY, &Vec4<float>::getY)
        .add_property("z", &Vec4<float>::setZ, &Vec4<float>::getZ)
        .add_property("w", &Vec4<float>::setW, &Vec4<float>::getW)
        ;
*/
    class_< Vec4<float> >("vec4", init<>())
        .def("setxyzw", &Vec4<float>::setXYZW)
        .def("setxyz" , &Vec4<float>::setXYZ)
        .def("setxy"  , &Vec4<float>::setXY)
        .def("setx"   , &Vec4<float>::setX)
        .def("sety"   , &Vec4<float>::setY)
        .def("setz"   , &Vec4<float>::setZ)
        .def("setw"   , &Vec4<float>::setW)
        .def("getx"   , &Vec4<float>::getX)
        .def("gety"   , &Vec4<float>::getY)
        .def("getz"   , &Vec4<float>::getZ)
        .def("getw"   , &Vec4<float>::getW)
        .def(self + self)
        .def(self += self)
        .def(self - self)
        .def(self -= self)
        .def(self * self)
        .def(self *= self)
        .def(self * float())
        .def(self *= float())
        .def(self / self)
        .def(self /= self)
        .def(self / float())
        .def(self /= float())
        ;

/*
    class_< Vec3<float> >("vec3", init<>())
        .add_property("x", &Vec3<float>::setX, &Vec3<float>::getX)
        .add_property("y", &Vec3<float>::setY, &Vec3<float>::getY)
        .add_property("z", &Vec3<float>::setZ, &Vec3<float>::getZ)
        ;
*/
    class_< Vec3<float> >("vec3", init<>())
        .def("setxyz", &Vec3<float>::setXYZ)
        .def("setxy" , &Vec3<float>::setXY)
        .def("setx"  , &Vec3<float>::setX)
        .def("sety"  , &Vec3<float>::setY)
        .def("setz"  , &Vec3<float>::setZ)
        .def("getx"  , &Vec3<float>::getX)
        .def("gety"  , &Vec3<float>::getY)
        .def("getz"  , &Vec3<float>::getZ)
        .def(self + self)
        .def(self += self)
        .def(self - self)
        .def(self -= self)
        .def(self * self)
        .def(self *= self)
        .def(self * float())
        .def(self *= float())
        .def(self / self)
        .def(self /= self)
        .def(self / float())
        .def(self /= float())
        ;
/*
    class_< Vec2<float> >("vec2", init<>())
        .add_property("x", &Vec2<float>::setX, &Vec2<float>::getX)
        .add_property("y", &Vec2<float>::setY, &Vec2<float>::getY)
        ;
*/

    class_< Vec2<float> >("vec2", init<>())
        .def("setxy", &Vec2<float>::setXY)
        .def("setx" , &Vec2<float>::setX)
        .def("sety" , &Vec2<float>::setY)
        .def("getx" , &Vec2<float>::getX)
        .def("gety" , &Vec2<float>::getY)
        .def(self + self)
        .def(self += self)
        .def(self - self)
        .def(self -= self)
        .def(self * self)
        .def(self *= self)
        .def(self * float())
        .def(self *= float())
        .def(self / self)
        .def(self /= self)
        .def(self / float())
        .def(self /= float())
        ;

	//Vec3<float> (*norm3) (Vec3<float>) = &vector_math::Normalize;
    //def("normalize", norm3);

}

////////////////////
////////////////////
////////////////////

int intersectTest(Entity * obj_1, Entity * obj_2)
{
    //Doesn't take rotation into account yet.

    int is_intersected2 = -1;
    int is_intersected = -1;
    std::vector<int> is_adv;
    is_adv.clear();

    Vec2<float> obj1_point1 = Vec2<float>( obj_1->getPosition().getX()-obj_1->getScale().getX(), obj_1->getPosition().getY()-obj_1->getScale().getY() );
    Vec2<float> obj1_point2 = Vec2<float>( obj_1->getPosition().getX()+obj_1->getScale().getX(), obj_1->getPosition().getY()+obj_1->getScale().getY() );
    Vec2<float> obj1_point3 = Vec2<float>( obj_1->getPosition().getX()-obj_1->getScale().getX(), obj_1->getPosition().getY()+obj_1->getScale().getY() );
    Vec2<float> obj1_point4 = Vec2<float>( obj_1->getPosition().getX()+obj_1->getScale().getX(), obj_1->getPosition().getY()-obj_1->getScale().getY() );


    Vec2<float> obj2_point1 = Vec2<float>( obj_2->getPosition().getX()-obj_2->getScale().getX(), obj_2->getPosition().getY()-obj_2->getScale().getY() );
    Vec2<float> obj2_point2 = Vec2<float>( obj_2->getPosition().getX()+obj_2->getScale().getX(), obj_2->getPosition().getY()+obj_2->getScale().getY() );
    Vec2<float> obj2_point3 = Vec2<float>( obj_2->getPosition().getX()-obj_2->getScale().getX(), obj_2->getPosition().getY()+obj_2->getScale().getY() );
    Vec2<float> obj2_point4 = Vec2<float>( obj_2->getPosition().getX()+obj_2->getScale().getX(), obj_2->getPosition().getY()-obj_2->getScale().getY() );

    //top-right point
    if( obj1_point1.getX() >= obj2_point1.getX() && obj1_point1.getX() <= obj2_point2.getX() )
        if(obj1_point1.getY() >= obj2_point1.getY() && obj1_point1.getY() <= obj2_point2.getY())
        {
            is_intersected = 0;
            is_adv.push_back(0);
        }

    //bottom_left
    if( obj1_point2.getX() >= obj2_point1.getX() && obj1_point2.getX() <= obj2_point2.getX() )
        if(obj1_point2.getY() >= obj2_point1.getY() && obj1_point2.getY() <= obj2_point2.getY())
        {
            is_intersected = 1;
            is_adv.push_back(1);
        }


    //top-left  point
    if( obj1_point4.getX() >= obj2_point3.getX() && obj1_point4.getX() <= obj2_point4.getX() )
        if(obj1_point4.getY() <= obj2_point3.getY() && obj1_point4.getY() >= obj2_point4.getY())
        {
            is_intersected = 2;
            is_adv.push_back(2);
        }

    //bottom-right
    if( obj1_point3.getX() <= obj2_point4.getX() && obj1_point3.getX() >= obj2_point3.getX() )
        if(obj1_point3.getY() >= obj2_point4.getY() && obj1_point3.getY() <= obj2_point3.getY())
        {
            is_intersected = 3;
            is_adv.push_back(3);
        }

    if( is_adv.size() > 0 )
    {
        if( is_adv.size() == 1 )
            is_intersected2 = 0;
        else
            is_intersected2 = 4;

        for(int i=0; i<(int)is_adv.size(); i++)
        {
            is_intersected2 += is_adv[i];
        }

        if( is_adv.size() >= 2 )
        {
            if( ( (is_adv[0] == 1) && (is_adv[1]==2) ) )
                is_intersected2+=2;
        }

    }

    //0 = top_right
    //1 = bottom_left
    //2 = top_left
    //3 = bottom_right


    //6 = top
    //7 = right
    //8 = bottom
    //9 = left

    return is_intersected2;

}

BOOST_PYTHON_MODULE(pshObjectTests)
{
    def("object_intersect_test", &intersectTest);
}

/////////////////////////
/////////////////////////
/////////////////////////

#include "../Management/scriptMng.h"

BOOST_PYTHON_MODULE(pshScriptEngine)
{
    pScript * (scriptMng::*GetScript_0)(int) = &scriptMng::GetScriptByIndex;
    pScript * (scriptMng::*GetScript_1)(std::string) = &scriptMng::getScript;
    class_<scriptMng>("ScriptMng", init<>())
        .def("GetScript", GetScript_0, return_value_policy<reference_existing_object>())
        .def("GetScript", GetScript_1, return_value_policy<reference_existing_object>())
    ;
}

/////////////////////////
/////////////////////////
/////////////////////////

#include "../Management/entityManager.h"
#include "../PyFunc/pshEngine.h"
#include "../Camera/Camera.h"

BOOST_PYTHON_MODULE(pshGameEngine)
{
    Entity * (entityManager::*getEntity_0)(std::string) = &entityManager::getEntity;

    class_<entityManager, boost::noncopyable>("Scene", init<>())
        .def( "getSceneObject",getEntity_0, return_value_policy<reference_existing_object>() )
        .def( "SceneRender", &entityManager::renderEnabled )
        .def( "IsRendering", &entityManager::IsRendering)
        ;

    void (Entity::*setposition0)(float, float, float) = &Entity::setPosition;
    void (Entity::*setposition1)( Vec3<float> )       = &Entity::setPosition;

    void (Entity::*setscale0)(float, float, float) = &Entity::setScale;
    void (Entity::*setscale1)( Vec3<float> )       = &Entity::setScale;

    void (Entity::*setcolor0)(float, float, float, float) = &Entity::setColor;
    void (Entity::*setcolor1)( Vec4<float> )              = &Entity::setColor;

    void (Entity::*settexture0)(std::string) = &Entity::setTexture;

    class_<Entity>("SceneObjectBase", init<>())
        .def("setPosition", setposition0)
        .def("setPosition", setposition1)
        .def("getPosition", &Entity::getPosition)
        .def("setColor"   , setcolor0)
        .def("setColor"   , setcolor1)
        .def("getColor"   , &Entity::getColor)
        .def("setScale"   , setscale0)
        .def("setScale"   , setscale1)
        .def("getScale"   , &Entity::getScale)
        .def("setRotation", &Entity::setRotation)
        .def("getRotation", &Entity::getRotation)
        .def("getName"    , &Entity::getName)
        .def("setLayer"     , &Entity::setLayer)
        .def("getLayer"     , &Entity::getLayer)
        .def("setRenderable", &Entity::isRenderable)
        .def("setTexture"   , settexture0)
    ;

    class_<Sprite, bases<Entity> >("SceneObjectSprite", init<>())
        .def("flipSpriteH"  , &Sprite::flipHorizontalTexCoordinates)
        .def("isSpriteHFlip", &Sprite::isSpriteHFlip)
        .def("flipSpriteV"  , &Sprite::flipVerticleTexCoordinates)
        .def("isSpriteVFlip", &Sprite::isSpriteVFlip)
        .def("PlayAnimation", &Sprite::UseAnimation)
        .def("SetAnimIndex" , &Sprite::play_animationSet)
        .def("SetAnimFPS"   , &Sprite::SetAnimationFPS)
    ;


    void (Tile::*t_sp0)(float, float, float) = &Tile::setPosition;
    void (Tile::*t_sp1)(float[3]) = &Tile::setPosition;
    void (Tile::*t_sp2)(Vec3<float>) = &Tile::setPosition;

    class_<Tile, bases<Entity> >("SceneObjectTile", init<>())
        .def("setPosition", t_sp0)
        .def("setPosition", t_sp1)
        .def("setPosition", t_sp2)
        .def("getPosition", &Tile::getPosition)
    ;

    class_<Text, bases<Entity> >("SceneObjectText", init<std::string>())
        .def("setText"    , &Text::setText)
        .def("getText"    , &Text::getText)
    ;

    class_<Particles>("ParticleSystem", init<>())
        .def("SetEmitter", &Particles::SetEmitter)
        .def("SetNumberOfParticles", &Particles::SetNumberOfParticles)
    ;

    class_<PSysExplode, bases<Particles> >("PSysExplode", init<>())
    ;

    class_<PSysSpray, bases<Particles> >("PSysExplode", init<>())
        .def("SetDirection", &PSysSpray::SetDirection)
    ;

    class_<pshEngine, boost::noncopyable>("pshEngine", init<>())
        .def("SceneManage", &pshEngine::getObjectManager, return_value_policy< reference_existing_object>())
    ;

    void (Camera::*cam2DPan_0)(float, float) = &Camera::cam2DPan;
    void (Camera::*cam2DZoom_0)(float)       = &Camera::cam2DZoom;
    class_<Camera>("SceneCamera", init<>())
        .def("pan"    , cam2DPan_0)
        .def("rotate" , &Camera::cam2DRotate)
        .def("zoom"   , cam2DZoom_0)
    ;

    class_<boost::timer>("pshTimer", init<>())
        .def("Time",    &boost::timer::elapsed)
        .def("Restart", &boost::timer::restart)
    ;

    boost::timer * (pScript::*getvartimer0)(int)          = &pScript::GetVarTimer;
    boost::timer * (pScript::*getvartimer1)(const char *) = &pScript::GetVarTimer;
    std::string (pScript::*getvarstr0)(int)          = &pScript::GetVarStr;
    std::string (pScript::*getvarstr1)(const char *) = &pScript::GetVarStr;
    float (pScript::*getvarfloat0)(int)              = &pScript::GetVarFloat;
    float (pScript::*getvarfloat1)(const char *)     = &pScript::GetVarFloat;
    bool (pScript::*getvarbool0)(int)                = &pScript::GetVarBool;
    bool (pScript::*getvarbool1)(const char *)       = &pScript::GetVarBool;
    int (pScript::*getvarint0)(int)                  = &pScript::GetVarInt;
    int (pScript::*getvarint1)(const char *)         = &pScript::GetVarInt;

    void (pScript::*setvarstr0)(int, std::string)          = &pScript::SetVarStr;
    void (pScript::*setvarstr1)(const char *, std::string) = &pScript::SetVarStr;
    void (pScript::*setvarfloat0)(int, float)              = &pScript::SetVarFloat;
    void (pScript::*setvarfloat1)(const char *, float)     = &pScript::SetVarFloat;
    void (pScript::*setvarbool0)(int, bool)                = &pScript::SetVarBool;
    void (pScript::*setvarbool1)(const char *, bool)       = &pScript::SetVarBool;
    void (pScript::*setvarint0)(int, int)                  = &pScript::SetVarInt;
    void (pScript::*setvarint1)(const char *, int)         = &pScript::SetVarInt;

    class_<pScript>("SceneScript" , init<>())
        .def("SetVarStr", setvarstr0)
        .def("SetVarStr", setvarstr1)
        .def("SetVarFloat", setvarfloat0)
        .def("SetVarFloat", setvarfloat1)
        .def("SetVarBool", setvarbool0)
        .def("SetVarBool", setvarbool1)
        .def("SetVarInt", setvarint0)
        .def("SetVarInt", setvarint1)
        .def("GetVarTimer", getvartimer0, return_value_policy< reference_existing_object>())
        .def("GetVarTimer", getvartimer1, return_value_policy< reference_existing_object>())
        .def("GetVarStr", getvarstr0)
        .def("GetVarStr", getvarstr1)
        .def("GetVarFloat", getvarfloat0)
        .def("GetVarFloat", getvarfloat1)
        .def("GetVarBool", getvarbool0)
        .def("GetVarBool", getvarbool1)
        .def("GetVarInt", getvarint0)
        .def("GetVarInt", getvarint1)
    ;
}

/////////////////////
/////////////////////
/////////////////////

#include "../Common/frameEvent.h"

BOOST_PYTHON_MODULE(pshEvent)
{
    class_<frameEvent>("pshEventKey")
        .def("keyset"  , &frameEvent::setKeyCode)
        .def("keymod"  , &frameEvent::returnkeymod)
        .def("keypress", &frameEvent::returnkeypress)
        .def("iskeydown", &frameEvent::iskeydown)
    ;
}


#endif
