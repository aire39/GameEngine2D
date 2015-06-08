#include "../Core/Animation.h"

Animation::Animation(std::string anim_name)
{
    current_frame = 0;
    fps = 15;
    fps_time = 0.0667;
    reset_position = 0;
    this->anim_name = anim_name;
    animation = new std::vector<unsigned int>;
    s_animation = new std::vector<std::string>;
    s_animation2 = new std::vector<std::string>;

    instanced = false;
}

Animation::Animation( const Animation & anim )
{
    current_frame = 0;
    fps = 15;
    fps_time = 0.0667;
    reset_position = 0;
    this->anim_name = anim.anim_name;
    this->animation = anim.animation;
    this->s_animation = anim.s_animation;
    this->s_animation2 = anim.s_animation2;
    instanced = true;
}

Animation::~Animation()
{
    animation->clear();


    if( !instanced )
    {
        animation->clear();
        delete animation;
        animation = NULL;
        delete s_animation;
        s_animation = NULL;
    }
}

void Animation::AddFrame(unsigned int texture)
{
    animation->push_back(texture);
    end_frame = animation->size();
}

void Animation::RemoveFrame()
{
    animation->pop_back();

    if(end_frame >= (int)animation->size())
        end_frame--;
}

void Animation::RemoveFrame(unsigned int frame)
{
    animation->erase( animation->begin()+frame );

    if(end_frame >= (int)animation->size())
        end_frame--;
}

unsigned int Animation::GetFrame(int frame_number)
{
    if( animation->size() != 0)
    {
        if( frame_number < (int)animation->size() )
            return animation->at(frame_number);
    }

    return 0;
}

unsigned int Animation::CurrentFrame()
{
    //return animation->at(current_frame);
    return current_frame;
}

std::string Animation::AnimName()
{
    return anim_name;
}

void Animation::SetAnimationName(std::string name)
{
    this->anim_name = name;
}

int Animation::GetNumberOfFrames()
{
    return s_animation->size();
}

void Animation::SetFrame(int frame, unsigned int texture)
{
    animation->at(frame) = texture;
}


void Animation::Play()
{
    if( animation_start >= 2 )
    {
        if( timer.elapsed() > fps_time )
        {
            timer.restart();

            current_frame++;

            if( current_frame > (int)s_animation->size()-1 )
                current_frame = 0;
        }
    }
}

//////////////////
//////////////////
//////////////////

AnimationBase::AnimationBase()
{
    animation_start = 0;
    reset_position = 0;

    start_frame = 0;
    current_frame = 0;
    end_frame = 0;

    fps = 12;
    fps_time = 1.0f/(float)fps;
}

AnimationBase::~AnimationBase()
{
}

void AnimationBase::Start()
{
    animation_start = 2;
}

void AnimationBase::EndFrame(int e)
{
    end_frame = e;
}

void AnimationBase::Play()
{
    if( animation_start >= 2 )
    {
        if( timer.elapsed() > fps_time )
        {
            timer.restart();

            current_frame++;

            if( current_frame > (int)end_frame-1 )
                current_frame = 0;
        }
    }
}

void AnimationBase::Stop()
{
    animation_start = 0;
    current_frame = 0;
}

void AnimationBase::Reset()
{
    current_frame = reset_position;
}

void AnimationBase::Pause()
{
    animation_start = 1;
}


void AnimationBase::SetFPS(int fps)
{
    this->fps = fps;
    fps_time = 1.0/float(fps);
}

void AnimationBase::SetFPS(float fps_in_time)
{
    fps_time = fps_in_time;
}

unsigned int AnimationBase::CurrentFrame()
{
    return current_frame;
}

int AnimationBase::GetNumberOfFrames()
{
    return end_frame+1;
}

bool AnimationBase::IsPlaying()
{
    if( animation_start >= 2 )
        return 1;

    return 0;
}

int AnimationBase::GetFrameRate()
{
    return fps;
}

float AnimationBase::GetFrameRatef()
{
    return fps_time;
}

std::string AnimationBase::AnimName()
{
    return "";
}

int AnimationBase::CurrentPlayFrame()
{
    return 0;
}
/////////////////////////////////
/////////////////////////////////
/////////////////////////////////

void Animation::s_AddFrame(std::string texture_name, std::string texture_name2)
{
    s_animation2->push_back(texture_name2);
    s_animation->push_back(texture_name);
    end_frame = s_animation->size();
}

void Animation::s_RemoveFrame(int frame)
{
    s_animation->erase( s_animation->begin()+frame );
    end_frame--;
}

void Animation::s_SetFrame(int frame, std::string texture_name, std::string texture_name2)
{
    (*s_animation)[frame] = texture_name;
    (*s_animation2)[frame] = texture_name2;

}

std::string Animation::s_CurrentFrame()
{
    return (*s_animation)[current_frame];
}

std::string Animation::s_CurrentFrame2()
{
    return (*s_animation2)[current_frame];
}

std::string Animation::s_GetFrame(int frame)
{
    std::string str = "";

    if( s_animation != NULL && s_animation->size() > 0 )
    if( frame >= 0 && frame < end_frame)
        return (*s_animation)[frame];

    std::cout << "Animation::s_GetFrame : Out Of Range!\nReturn <empty string>" << std::endl;
    return str;
}

std::string Animation::s_GetFrame2(int frame)
{
    std::string str = "";

    if( s_animation2 != NULL && s_animation2->size() > 0 )
    if( frame >= 0 && frame < end_frame)
        return (*s_animation2)[frame];

    std::cout << "Animation::s_GetFrame2 : Out Of Range!\nReturn <empty string>" << std::endl;
    return str;
}
