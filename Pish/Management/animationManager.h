#ifndef ANIMATIONMANAGER_H
#define ANIMATIONMANAGER_H

#include "../Core/Animation.h"
#include <map>
#include <vector>


typedef std::map<std::string, Animation*> AnimManager;
typedef std::vector<Animation*> AnimManagerV;

class animationManager
{
    private:

        AnimManager animations;     //animations kept track of [using a map]
        AnimManagerV animationsv;   //animations kept track of [using a vector]

    public:
                            ///Constrcutor
        animationManager();
                            ///Destructor
        ~animationManager();

                                                                                ///Insert Animation
        void InsertAnimation(std::string name, Animation * anim);
                                                                                ///Change Animation Name
        void ChangeAnimationName( std::string prev_name, std::string new_name );
                                                                                ///Get Number Od Animations
        int number_of_animations();

                                                        ///Get Animation By Name
        Animation * getAnimation(std::string anim_name);
                                                        ///Get Animation By Index
        Animation * getAnimation(int anim_index=0);

                                                        ///Remove Animation By Index
        void RemoveAnimation(int index);
                                                        ///Remove Animation By Name
        void RemoveAnimation(std::string anim_name);
                                                        ///Remove All Animations
        void RemoveAll();


};

#endif // ANIMATIONMANAGER_H
