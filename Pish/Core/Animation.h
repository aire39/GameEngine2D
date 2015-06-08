#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include <boost/progress.hpp>

class AnimationBase
{
    protected:

        std::string anim_name;

        int animation_start;
        int reset_position;

        int start_frame;
        int current_frame;
        int end_frame;

        int   fps;
        float fps_time;

        boost::timer timer;

    public:

        AnimationBase();
        virtual ~AnimationBase();

        virtual void Start();
        virtual void EndFrame(int e);
        virtual void Play();
        virtual void Stop();
        virtual void Reset();
        virtual void Pause();

        void SetFPS(int fps=15);
        void SetFPS(float fps_in_time=0.0667);

        virtual unsigned int CurrentFrame();
        virtual int GetNumberOfFrames();
        virtual int GetFrameRate();
        virtual float GetFrameRatef();
        virtual int CurrentPlayFrame();

        bool IsPlaying();

        virtual std::string AnimName();

};

class Animation : public AnimationBase
{
    private:

        bool instanced;
        std::vector<unsigned int> * animation;
        std::vector<std::string>  * s_animation;
        std::vector<std::string>  * s_animation2;

    public:
        Animation(std::string anim_name="Animation");
        Animation( const Animation & anim );
        ~Animation();

        void AddFrame(unsigned int texture=0);
        void RemoveFrame(unsigned int frame);
        void RemoveFrame();

        void SetAnimationName(std::string name);
        void SetFrame(int frame, unsigned int texture);

        unsigned int CurrentFrame();
        unsigned int GetFrame(int frame_number);
        int GetNumberOfFrames();
        std::string AnimName();

        void Play();


        ////////////////////////////////////
        void s_AddFrame(std::string texture_name, std::string texture_name2 = "");
        void s_SetFrame(int frame, std::string texture_name, std::string texture_name2 = "");
        void s_RemoveFrame(int frame);
        std::string s_CurrentFrame();
        std::string s_CurrentFrame2();
        std::string s_GetFrame( int frame );
        std::string s_GetFrame2( int frame );

};

#endif // ANIMATION_H
