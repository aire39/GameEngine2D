#include "../Management/animationManager.h"

animationManager::animationManager()
{
}

animationManager::~animationManager()
{
    #ifdef __WXDEBUG__
        std::cout << "Deleting animationManager!" << std::endl;
    #endif

    RemoveAll();

}

void animationManager::InsertAnimation(std::string name, Animation * anim)
{
    animations.insert( AnimManager::value_type(name, anim) );
    animationsv.push_back(anim);
}

void animationManager::ChangeAnimationName( std::string prev_name, std::string new_name )
{
    Animation * _animation = NULL;

    if( animations.find(prev_name) != animations.end() )
    {
        AnimManager::iterator it = animations.find(prev_name);

        _animation = it->second;
        _animation->SetAnimationName(new_name);

        animations.erase(it);
        animations.insert( AnimManager::value_type(new_name, _animation) );
    }
    else
        std::cout << "animationManager::ChangeAnimationName -> Animation not Found!" << std::endl;
}

int animationManager::number_of_animations()
{
    return animationsv.size();
}

Animation * animationManager::getAnimation(std::string anim_name)
{
    Animation * temp = NULL;

    if( animations.find(anim_name) != animations.end() )
        temp = animations.find(anim_name)->second;

    return temp;
}

Animation * animationManager::getAnimation(int anim_index)
{
    if((animationsv.size()<=0) || (anim_index>=(int)animationsv.size()) )
        return NULL;

    return animationsv[anim_index];
}

void animationManager::RemoveAnimation(int index)
{
    Animation * _anim = animationsv[index];
    animations.erase(_anim->AnimName());

    delete _anim;
    animationsv[index] = NULL;
    _anim = NULL;

    animationsv.erase( animationsv.begin()+index );
}

void animationManager::RemoveAnimation(std::string anim_name)
{
    Animation* _anim;
    std::string searchstr = animations.find(anim_name)->first;
    _anim = animations.find(anim_name)->second;

    for(int i=0; i<(int)animationsv.size(); i++)
        if( searchstr.compare(animationsv[i]->AnimName()) == 0 )
        {
            animationsv.erase( animationsv.begin()+i );
            break;
        }

    animations.erase( searchstr );
    delete _anim;


}

void animationManager::RemoveAll()
{
    if( animationsv.size() != 0 )
    {
        for(int i=0; i<(int)animationsv.size(); i++)
            delete animationsv[i];

        animationsv.clear();
        animations.clear();
    }
}
