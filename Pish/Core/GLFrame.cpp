#include "GLFrame.h"
#include "../Window/OGLWin.h"
#include "../Common/GApp.h"
#include <boost/python.hpp>
using namespace boost::python;


GLFrame::GLFrame(wxWindow *parent, wxGLContext * glContext, const int* gl_attrib)
    : wxGLCanvas(parent, wxID_ANY, gl_attrib, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE, "GLCanvas", wxNullPalette)
{
    extern bool AppMod;

    this->opengl_context = new wxGLContext(this);

    m_parent = parent;
    Show(true);

    t_access = true;

    SAnim = false;
    paintMode = false;
    //shaderSwitch = 0;

    mTransX = 0.0f;
    mTransY = 0.0f;
    pZoom = cZoom = 1.0f;

    picked_entity = NULL;
    picked_entity_sub = NULL;
    tileEditable = false;

    frame_event = NULL;
    property_window = NULL;

    GridX = GridY = 20;         //GridSize
    Grid_Spacing = 20.0f/10.0f; //GridSize / How Many Squares (Think of value as the diemeter)

    statistic_text   = NULL;
    entity_highlight = NULL;

    selected_manipulator = NULL;
    manipulate_handles   = NULL;
}


GLFrame::~GLFrame()
{
    #ifdef __WXDEBUG__
        std::cout << "Deleting GLFrame!" << std::endl;
    #endif

    //delete psys;
    delete frame_event;
    delete [] manipulate_handles;
    delete statistic_text;
    delete entity_highlight;
    delete camera;
}

bool GLFrame::Init()
{
  ////////////////
  //**Set View**//
  ////////////////
  SetCurrent(*opengl_context);


  /////////////////////////////
  //Initialize Opengl States///
  /////////////////////////////

    glHint( GL_POLYGON_SMOOTH_HINT, GL_NICEST );
    glEnable( GL_LINE_SMOOTH );

    glEnable( GL_TEXTURE_2D );
    glEnable( GL_ALPHA_TEST );
    glEnable( GL_BLEND );
    glEnable( GL_DEPTH_TEST );
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glAlphaFunc( GL_GREATER, 0);
    glBindTexture( GL_TEXTURE_2D, 0 );


    ////////////////////
    //Inialize Objects//
    ////////////////////

    camera = new Camera();
    frame_event = new frameEvent();
    frame_event->BindGLView(this);

    statistic_text   = new Text();
    entity_highlight = new Sprite();

    statistic_text->init();
    entity_highlight->init();

    statistic_text->setName("Statistic FPS");

    manipulate_handles = new Sprite[5]();
    for(int i=0; i<5; i++)
        manipulate_handles[i].init();
    manipulate_handles[0].setName("up/down");
    manipulate_handles[1].setName("left/right");
    manipulate_handles[2].setName("center");
    manipulate_handles[3].setName("scale_u");
    manipulate_handles[4].setName("scale_r");

    //psys = new PSysExplode();
    //psys->setPosition(-5.0f, 0.0f, 0.0f);
    //psys->SetEmitter(entity_highlight);
    //psys->SetType(1);
    //((PSysSpray*)psys)->SetDirection();
    //psys->SetGlobalAcceleration(Vec3<float>(0.0f, -1.0f, 0.0f));
    //psys->SetType(0);
    //psys->SetNumberOfParticles(1000);
    //psys->SetRunTime(-1);



  return TRUE;
}

void GLFrame::RenderGrid(int row, int col)
{
    glDisable( GL_TEXTURE_2D );
    glBegin(GL_LINES);
        glColor3f(0.5f, 0.5f, 0.5f);
        for(int i=0; i<=row*2; i++)
        {
            if((i-row) == 0)
                glColor3f(1.0f, 0.0f, 0.0f);
            else
                glColor3f(0.5f, 0.5f, 0.5f);

            glVertex3f(-row, (i-row)*Grid_Spacing, 0.0f);
            glVertex3f( row, (i-row)*Grid_Spacing, 0.0f);
        }

        for(int i=0; i<=col*2; i++)
        {
            if((i-col) == 0)
                glColor3f(0.0f, 1.0f, 0.0f);
            else
                glColor3f(0.5f, 0.5f, 0.5f);

            glVertex3f((i-col)*Grid_Spacing, -col, 0.0f);
            glVertex3f((i-col)*Grid_Spacing,  col, 0.0f);
        }

        glColor3f(1.0f, 1.0f, 1.0f);

    glEnd();
    glEnable( GL_TEXTURE_2D );
}

void GLFrame::RenderHighlight(float r, float g, float b, float a)
{
    if( picked_entity != NULL )
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDisable(GL_TEXTURE_2D);

        Vec3<float> pscale;
        Vec3<float> ppos;

        pscale = picked_entity->getScale();
        ppos   = picked_entity->getPosition();

        glColor4f(r, g, b, a);
        picked_entity->setScale( picked_entity->getScale().getX()+(0.1f*picked_entity->getScale().getX()), picked_entity->getScale().getY()+(0.1f*picked_entity->getScale().getY()), picked_entity->getScale().getZ() );
        picked_entity->setPosition(picked_entity->getPosition().getX(), picked_entity->getPosition().getY(), picked_entity->getPosition().getZ());
        picked_entity->draw_raw();

        picked_entity->setScale( pscale.getX(), pscale.getY(), pscale.getZ() );
        picked_entity->setPosition(ppos.getX(), ppos.getY(), ppos.getZ());

        glEnable(GL_TEXTURE_2D);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

void GLFrame::RenderManipulator()
{
    if( picked_entity != NULL )
    {
        //0 = up/down
        //1 = left/right
        //2 = 0 and 1
        //3 = scale up
        //4 = scale right

        glPushMatrix();

        glTranslatef(picked_entity->getPosition().getX(), picked_entity->getPosition().getY(), 0.0);

        manipulate_handles[0].setPosition(-0.9, 0.0);
        manipulate_handles[0].setScale(0.1, 1.0);

        manipulate_handles[1].setPosition(0.0, -1.0);
        manipulate_handles[1].setScale(1.0, 0.1);

        manipulate_handles[2].setPosition(-0.35, -0.45);
        manipulate_handles[2].setScale(0.5, 0.5);

        manipulate_handles[3].setPosition(-0.9, 2.0);
        manipulate_handles[3].setScale(0.1, 0.1);

        manipulate_handles[4].setPosition(2.0, -1.0);
        manipulate_handles[4].setScale(0.1, 0.1);

        glColor3f(1.0, 0.0, 0.0);

        glDisable(GL_TEXTURE_2D);
        for(int i=0; i<5; i++)
            manipulate_handles[i].draw_raw();
        glEnable(GL_TEXTURE_2D);

        glPopMatrix();
    }
}

bool GLFrame::Render()
{

    //////////////////////////////////
    //Set Viewport And Clear Buffers//
    //////////////////////////////////
    glViewport(0, 0, GetClientSize().GetWidth(), GetClientSize().GetHeight());
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    ////////////////
    //Setup Camera//
    ////////////////
    camera->setup2D();
    camera->useCamera();

    //Extra Makes the whole scene rotate (I'll delete this later)
    if(SAnim)
        animPass();

    ///////////////
    //Scene Scale//
    ///////////////
    glScalef(10.0f,10.0f,1.0f);

    ////////////////
    //Render Stats//
    ////////////////
    calcFPS();
    //glFlush();

    ///////////////
    ///////////////
    ///////////////

    RenderManipulator();
    RenderHighlight(0.0f, 1.0f, 0.0f);
    //glFlush();

    /////////////////
    //Render Scenes//
    /////////////////
    for(int i=0; i<(int)scene_manager->size(); i++)
        scene_manager->at(i)->Render();
    //glFlush();

    ////////
    //Test//
    ////////
    //psys->Run();

    /////////////////
    //Render Extras//
    /////////////////
    RenderGrid(-(GridX-((int)camera->getZoomPos2D()+120.0f))+abs(camera->getPos2D().getX())+1.0, -(GridY-((int)camera->getZoomPos2D()+120.0f))+abs(camera->getPos2D().getY())+1.0);
    //glFlush();

    return true;
}


void GLFrame::calcFPS()
{
    static int FPS = 0;;
    wxString str;

    wxLongLong tickAfter = wxGetLocalTimeMillis();
    wxLongLong tickDiff = tickAfter - tickBefore;

    FPS++;

    if(tickDiff >= 1000)//1000millisec = 1sec
    {
        tickBefore = tickAfter;

        wxString str = (wxChar *)"fps: ";
        char t[5];

        sprintf(t, "%d", FPS);

        str.Append( (wxChar *) t );

        sfps = str;
        FPS = 0;
    }

    statistic_text->setText((std::string)sfps);
    statistic_text->setScale(0.01f/camera->getZoomPos2D(), 0.01f/camera->getZoomPos2D(), 1.0f);
    statistic_text->SetScreenPosition(20, 10, camera->GetCameraMatrix());
    statistic_text->draw();


    ///////Dummy Call//////
    statistic_text->setText("");
    statistic_text->setScale(0.01f/camera->getZoomPos2D(), 0.01f/camera->getZoomPos2D(), 1.0f);
    statistic_text->SetScreenPosition(20, 30, camera->GetCameraMatrix());
    statistic_text->draw();
    ///////Dummy Call//////

    //////
    str = "CameraPos:";
    str.append( (wxString)convertDouble(camera->getPos2D().getX()) );
    str.append(" , ");
    str.append( (wxString)convertDouble(camera->getPos2D().getY()) );

    statistic_text->setText((std::string)str);
    statistic_text->setScale(0.01f/camera->getZoomPos2D(), 0.01f/camera->getZoomPos2D(), 1.0f);
    statistic_text->SetScreenPosition(20, 30, camera->GetCameraMatrix());
    statistic_text->draw();

}


bool GLFrame::getStartAnim()
{
    return SAnim;
}

bool GLFrame::animPass()
{
  static float theta = 0.0f;
  theta += 0.1f;
  static float g = 0.0f;
  g += 1.0f;

  glTranslatef(cosf(theta)*20, sinf(theta)*20, 0.0f);
  glRotatef(g, 0.0f, 0.0f, 1.0f);

  return true;
}


void GLFrame::LoadTexMng(texMng * texture_manager)
{
    //SetCurrent(*opengl_context);
    this->texture_manager = texture_manager;
}


void GLFrame::LoadSceneManager(std::vector<entityManager*> * scene_manager)
{
    this->scene_manager = scene_manager;
}

void GLFrame::BindPropertyWindow(propertyWindow * property_window)
{
    this->property_window = property_window;
}

void GLFrame::SetPaintMode(bool b)
{
    paintMode = b;
}

void GLFrame::Reset()
{
    picked_entity = NULL;
    picked_entity_sub = NULL;
    entity_highlight = NULL;
}

frameEvent * GLFrame::getFrameEvent()
{
    return frame_event;
}

wxGLContext * GLFrame::GetContext()
{
    return opengl_context;
}

Camera * GLFrame::GetCamera()
{
    return camera;
}

///////////////////////EVENT FUNCTIONS/////////////////////////////////////////////////

void GLFrame::OnEraseBackground(wxEraseEvent& WXUNUSED(event))
{
}

void GLFrame::OnPaint(wxPaintEvent& event)
{
    event.Skip(t_access);

    //SetCurrent(*opengl_context);
    Render();
    SwapBuffers();

}

void GLFrame::OnChar2(wxKeyEvent & event)
{
    frame_event->isKeyPressed(event);
    frame_event->setKeyCode(0);
}

void GLFrame::OnChar(wxKeyEvent& event)
{
    event.Skip(t_access);

    frame_event->isKeyPressed(event); //Is-Down etc//); //to be exposed

    switch( event.GetKeyCode() )
    {
        case '1':

            SAnim ^= true;

            break;

        case 'E':
        case 'e':

            if( picked_entity != NULL)
            {
                if( typeid(*picked_entity) == typeid(Tile))
                {
                    tileEditable ^= true;
                    ((Tile*)picked_entity)->setEditable(tileEditable);
                }
            }

            break;


        case 'P':
        case 'p':

            if(paintMode)
            {
                paintMode ^= true;
                cout << "PaintMode OFF" << endl;
            }
            else
            {
                paintMode ^= true;
                cout << "PaintMode ON" << endl;
            }

            break;

        default:
            event.Skip();
            return;
    }

}

void GLFrame::OnEnterWindow(wxMouseEvent& event)
{
    event.Skip();
    t_access = false;

    ((OGLWin*)m_parent)->OnEnterWindow(event);

    SetFocus();
    SetCurrent(*opengl_context);
    Refresh();

    int w, h;
    GetClientSize(&w, &h);
    glViewport(0, 0, w, h);
    camera->setup2D();

    cout << "\nEntered Draw View\n" << endl;
}

void GLFrame::OnSize(wxSizeEvent& event)
{

    int w, h;
    GetClientSize(&w, &h);

    //SetCurrent(*opengl_context);
    camera->reshapeView(w, h);

    ((OGLWin*)m_parent)->OnSize(event);

}

void GLFrame::OnMouseEvent(wxMouseEvent& event)
{
    event.Skip(t_access);
    //event.Skip();

    //static float tempX = 0.0f;
    //static float tempY = 0.0f;
    static bool *ex_AppMod = &AppMod;

    int width, height;
    width = GetClientSize().GetWidth();
    height = GetClientSize().GetHeight();
    unsigned char r_pixel[3];

    static double mWorldPos[3] = {0,0,0};

    switch(event.GetButton())
    {
        case wxMOUSE_BTN_LEFT:
            {
                if( event.LeftDown() && !event.ControlDown() )
                {
                    mStartX = event.GetX();
                    mStartY = event.GetY();

                    //Y-Axis screen space seeing upside down for some reason.
                    //Fixed By Turning the Y-Value Negative Only During Picking(Not actually sur why though I think
                    //it's because of the screen corrdinates of the window for mouse input opposed to opengls viewport.

                    ///Mouse Event: Object Selection

                    ///Problem: When I add the tile object it can't get picked for some reason.

                    glDisable( GL_TEXTURE_2D );
                    glDisable(GL_DITHER);
                    glDisable( GL_DEPTH_TEST );
                    glShadeModel(GL_FLAT);
                    glClear( GL_COLOR_BUFFER_BIT);


                    ///Init the picked object
                    if(tileEditable == false)
                    {

                        for(int i=0; i<(int)scene_manager->size(); i++)
                            scene_manager->at(i)->pickRender();


                        int viewPort[4];
                        glGetIntegerv(GL_VIEWPORT, viewPort);
                        glReadPixels(event.GetX(), viewPort[3]-event.GetY(), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, r_pixel);
                        //std::cout << "Left-Clicked: " << event.GetX() << " " << event.GetY() << std::endl;
                        std::cout << "Color: " << (int)r_pixel[0] << " " << (int)r_pixel[1] << " " << (int)r_pixel[2] << std::endl;

                        if( selected_manipulator == NULL )
                        for(int i=0; i<(int)scene_manager->size(); i++)
                        {
                            picked_entity = scene_manager->at(i)->getEntity(r_pixel);

                            if(picked_entity != NULL)
                                break;
                        }

                        glPushMatrix();
                        if(picked_entity != NULL)
                        glTranslatef(picked_entity->getPosition().getX(), picked_entity->getPosition().getY(), 0.0);
                        for(int i=0; i<5; i++)
                            manipulate_handles[i].picking();
                        glPopMatrix();

                        glReadPixels(event.GetX(), viewPort[3]-event.GetY(), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, r_pixel);
                        std::cout << "MColor: " << (int)r_pixel[0] << " " << (int)r_pixel[1] << " " << (int)r_pixel[2] << std::endl;

                        for(int i=0; i<5; i++)
                        {
                            if( (manipulate_handles[i].getColorID()[0] == r_pixel[0]) && (manipulate_handles[i].getColorID()[1] == r_pixel[1]) && (manipulate_handles[i].getColorID()[2] == r_pixel[2]))
                            {
                                selected_manipulator = &manipulate_handles[i];
                                break;
                            }
                            else
                                selected_manipulator = NULL;

                        }

                        //picked_entity = entity_highlight; //for testing reason : used this as a shortcut to see if particle system would follow a picked/attached to entity.

                        if(picked_entity != NULL)
                            std::cout << "Selected Object Position:" << picked_entity->getPosition().getX() << " " << picked_entity->getPosition().getY() << " " << picked_entity->getPosition().getZ() << std::endl;

                    }


                    ///Determine Mode (Code used to be able to edit the subObjects of a tile object
                    if( (picked_entity != NULL) && (tileEditable == true))
                    {
                        if( typeid(*picked_entity) == typeid(Tile)  && picked_entity != NULL )
                        {
                            std::cout << "It is a tile!" << std::endl;
                            if( ((Tile*)picked_entity)->isEditable() == true )
                            {
                                std::cout << "tile is editable!" << std::endl;

                                glClear( GL_COLOR_BUFFER_BIT );
                                ((Tile*)picked_entity)->picking();

                                int viewPort[4];
                                glGetIntegerv(GL_VIEWPORT, viewPort);
                                glReadPixels(event.GetX(), viewPort[3]-event.GetY(), 1, 1, GL_RGB, GL_UNSIGNED_BYTE, r_pixel);

                                picked_entity_sub = ((Tile*)picked_entity)->getSubEntity(r_pixel);

                            if(picked_entity_sub != NULL)
                                std::cout << "Selected SubObject Position:" << picked_entity_sub->getPosition().getX() << " " << picked_entity_sub->getPosition().getY() << " " << picked_entity_sub->getPosition().getZ() << std::endl;

                            }
                        }
                    }
                    else
                        std::cout << "Not A Tile Type!" << std::endl;

                    ///Mouse Event: PaintMode Activation

                    if(paintMode && !tileEditable && (picked_entity!=NULL))
                    {
                        picked_entity->setTexture( texture_manager->GetSelectedTexture() ); //Gets Selected Texture From textureResource Window
                        if( typeid(*picked_entity) == typeid(Sprite) )
                            ((Sprite*)picked_entity)->setTextureSub( texture_manager->GetSelectedTexture2() ); //Gets Selected Texture From textureResource Window
                    }

                    if(paintMode && tileEditable && (picked_entity_sub!=NULL))
                    {
                        picked_entity_sub->setTexture( texture_manager->GetSelectedTexture() );
                    }


                    glEnable(GL_DITHER);
                    glEnable( GL_TEXTURE_2D );
                    glEnable( GL_DEPTH_TEST );

                }
                else if( event.LeftDown() && event.ControlDown() )
                {
                    mStartX = event.GetX();
                    mStartY = event.GetY();
                }
                else if( event.LeftUp() && event.ControlDown() )
                {
                    //if( tempX > 0 && tempY > 0 )
                    //{
                        //Picking(multiple objects] code goes here

                        //tempX = event.GetX();
                        //tempY = event.GetY();


                    //}

                    //dm.pickObject(mStartX, mStartY, event.GetX(), event.GetY()); //USE
                    //dm.setPickPref(false);
                }

            }
               break;

        case wxMOUSE_BTN_MIDDLE:
        {
            if( mWorldPos[2] == 0 )
            {
                mWorldPos[1] = 1;

                double projection_matrix[16];
                int view_port[4];

                glGetDoublev( GL_PROJECTION_MATRIX, projection_matrix);
                glGetIntegerv( GL_VIEWPORT, view_port);

                double place_holder = 0;

                if( !gluUnProject( event.GetX(), view_port[3]-event.GetY(), 0, camera->GetCameraMatrix(), projection_matrix, view_port, &mWorldPos[0], &mWorldPos[1], &place_holder) )
                    std::cout << "UnProject Failed -> Moving Enities!" << std::endl;
            }

            mStartX = event.GetX();
            mStartY = event.GetY();

            mLastX = mTransX;
            mLastY = mTransY;

        }
            break;


        case wxMOUSE_BTN_RIGHT:
        {
            sZoom = event.GetY();
            pZoom = cZoom;
        }

        break;

        default:
            event.Skip();
            break;
    }

    //std::cout << event.GetButton() << " " << event.MiddleIsDown() << std::endl;

    if( (event.GetButton() == 2) && (event.Moving() == false) && (event.MiddleIsDown() == true) )
    {
    }

    if( event.Dragging() )
    {

        if( event.LeftIsDown() && !event.ControlDown() )
        {
            ///Mouse Drag: Object Position Change
            if( picked_entity!=NULL )
            {

                if( !tileEditable && picked_entity != NULL )
                {
                    if( selected_manipulator != NULL )
                    {
                        ///////////////////////////
                        //Control For Manipulator//
                        ///////////////////////////
                        if(selected_manipulator->getName().compare("up/down")==0)
                        {
                            double positionInWorld[3];
                            double projection_matrix[16];
                            int view_port[4];

                            glGetDoublev( GL_PROJECTION_MATRIX, projection_matrix);
                            glGetIntegerv( GL_VIEWPORT, view_port);

                            if( !gluUnProject( event.GetX(), event.GetY(), 0, camera->GetCameraMatrix(), projection_matrix, view_port, &positionInWorld[0], &positionInWorld[1], &positionInWorld[2]) )
                                std::cout << "UnProject Failed -> Moving Enities!" << std::endl;

                            Vec3<float> change_position = picked_entity->getPosition();
                            change_position.setY(-(float)positionInWorld[1]/10.0);
                            picked_entity->setPosition(change_position);
                            *ex_AppMod = true;
                        }
                        else if(selected_manipulator->getName().compare("left/right")==0)
                        {
                            double positionInWorld[3];
                            double projection_matrix[16];
                            int view_port[4];

                            glGetDoublev( GL_PROJECTION_MATRIX, projection_matrix);
                            glGetIntegerv( GL_VIEWPORT, view_port);

                            if( !gluUnProject( event.GetX(), event.GetY(), 0, camera->GetCameraMatrix(), projection_matrix, view_port, &positionInWorld[0], &positionInWorld[1], &positionInWorld[2]) )
                                std::cout << "UnProject Failed -> Moving Enities!" << std::endl;

                            Vec3<float> change_position = picked_entity->getPosition();
                            change_position.setX((float)positionInWorld[0]/10.0);
                            picked_entity->setPosition(change_position);
                            *ex_AppMod = true;
                        }
                        else if(selected_manipulator->getName().compare("center")==0)
                        {
                            double positionInWorld[3];
                            double projection_matrix[16];
                            int view_port[4];

                            glGetDoublev( GL_PROJECTION_MATRIX, projection_matrix);
                            glGetIntegerv( GL_VIEWPORT, view_port);

                            if( !gluUnProject( event.GetX(), event.GetY(), 0, camera->GetCameraMatrix(), projection_matrix, view_port, &positionInWorld[0], &positionInWorld[1], &positionInWorld[2]) )
                                std::cout << "UnProject Failed -> Moving Enities!" << std::endl;

                            picked_entity->setPosition((positionInWorld[0]/10.0), -positionInWorld[1]/10.0, 0.0f);
                            *ex_AppMod = true;
                        }
                        else if(selected_manipulator->getName().compare("scale_r")==0)
                        {
                            double positionInWorld[3];
                            double projection_matrix[16];
                            int view_port[4];

                            glGetDoublev( GL_PROJECTION_MATRIX, projection_matrix);
                            glGetIntegerv( GL_VIEWPORT, view_port);

                            if( !gluUnProject( event.GetX(), event.GetY(), 0, camera->GetCameraMatrix(), projection_matrix, view_port, &positionInWorld[0], &positionInWorld[1], &positionInWorld[2]) )
                                std::cout << "UnProject Failed -> Moving Enities!" << std::endl;

                            picked_entity->setScale((positionInWorld[0]/10.0), picked_entity->getScale().getY());
                            *ex_AppMod = true;
                        }
                        else if(selected_manipulator->getName().compare("scale_u")==0)
                        {
                            double positionInWorld[3];
                            double projection_matrix[16];
                            int view_port[4];

                            glGetDoublev( GL_PROJECTION_MATRIX, projection_matrix);
                            glGetIntegerv( GL_VIEWPORT, view_port);

                            if( !gluUnProject( event.GetX(), event.GetY(), 0, camera->GetCameraMatrix(), projection_matrix, view_port, &positionInWorld[0], &positionInWorld[1], &positionInWorld[2]) )
                                std::cout << "UnProject Failed -> Moving Enities!" << std::endl;

                            picked_entity->setScale(picked_entity->getScale().getX(), -(positionInWorld[1]/10.0));
                            *ex_AppMod = true;
                        }


                    }
                    else
                    {
                        //////////////////////////
                        //General Object Control//
                        //////////////////////////
                        double positionInWorld[3];
                        double projection_matrix[16];
                        int view_port[4];

                        glGetDoublev( GL_PROJECTION_MATRIX, projection_matrix);
                        glGetIntegerv( GL_VIEWPORT, view_port);

                        if( !gluUnProject( event.GetX(), event.GetY(), 0, camera->GetCameraMatrix(), projection_matrix, view_port, &positionInWorld[0], &positionInWorld[1], &positionInWorld[2]) )
                            std::cout << "UnProject Failed -> Moving Enities!" << std::endl;

                        picked_entity->setPosition((positionInWorld[0]/10.0), -positionInWorld[1]/10.0, 0.0f);
                        *ex_AppMod = true;
                    }
                }
                else if(tileEditable)
                {
                    mTransX = picked_entity_sub->getPosition().getX() + ((event.GetX() - mStartX)/(width/1.0f));
                    mTransY = picked_entity_sub->getPosition().getY()+ ((mStartY - event.GetY())/(height/1.0f));

                    if( picked_entity_sub != NULL )
                    picked_entity_sub->setPosition(mTransX, mTransY, 0.0f);
                }

                if( property_window != NULL )
                    property_window->EnterWindow(event);
            }
        }


        if( event.MiddleIsDown() )
        {
            ///Mouse Drag: Camera Position Change

            double positionInWorld[3];
            double projection_matrix[16];
            int view_port[4];

            glGetDoublev( GL_PROJECTION_MATRIX, projection_matrix);
            glGetIntegerv( GL_VIEWPORT, view_port);



            if( !gluUnProject( event.GetX(), view_port[3]-event.GetY(), 0, camera->GetCameraMatrix(), projection_matrix, view_port, &positionInWorld[0], &positionInWorld[1], &positionInWorld[2]) )
                std::cout << "UnProject Failed -> Moving Enities!" << std::endl;
            std::cout << camera->getPos2D().getX() << ", " << positionInWorld[0]/2.0 << std::endl;

            camera->cam2DPan( camera->getPos2D().getX() + (positionInWorld[0]-mWorldPos[0])/2.0, camera->getPos2D().getY() + (positionInWorld[1]-mWorldPos[1])/2.0);
            std::cout << "**ex_AppMod:" << *ex_AppMod << std::endl;

        }
        else
            mWorldPos[2] = 0;


		if( event.RightIsDown() && !event.ControlDown() )
        {
            ///Mouse Drag: Camera Zoom Change
            cZoom = camera->getZoomPos2D() + (((event.GetY() - sZoom) * -1)/50.0f);

            if(cZoom < 0.1f )
                cZoom = 0.101f;
            else if(cZoom > 50.0f)
                cZoom = 49.999f;

            camera->cam2DZoom(cZoom);

            if( event.GetY() <= 20 )
            {
                pZoom = cZoom;//*1.5f;
                WarpPointer(event.GetX(), GetClientSize().GetHeight()-25);
            }
            else if( event.GetY() >= GetClientSize().GetHeight()-20 )
            {
                pZoom = cZoom;//*-1.5f;
                WarpPointer(event.GetX(), 25);
            }

        }


        if( event.ControlDown() && event.LeftIsDown())
        {
            //cout << "Control+LeftClick" << endl; //WORKS

            //Vec3<float> tempPt1, tempPt2;

            ///camera->pointInSpace2D(mStartX, mStartY, tempPt1); //Very Useful
            ///camera->pointInSpace2D(event.GetX(), event.GetY(), tempPt2);

            //dm.setPickPref(tempPt1, tempPt2);
            //dm.setPickPref(true);
            //dm.setPickPref( camera->getPos2D() );

        }

        if( event.ControlDown() && event.RightIsDown())
        {
            //Basic Camera Rotation

            static float mrotate = 0.0f;
            mrotate += 1.0f;

            camera->cam2DRotate(mrotate);

        }


        //////////////////
        //IsDragging END//
        //////////////////
    }


}




void GLFrame::OnLeaveWindow(wxMouseEvent& WXUNUSED(event))
{
    t_access = true;
    cout << "Leaving draw" << endl;
}

void GLFrame::onIdle(wxIdleEvent & event)
{
    wxPaintEvent pevent(wxEVT_PAINT);
    AddPendingEvent(pevent);

    event.RequestMore();
    event.Skip();
}

BEGIN_EVENT_TABLE(GLFrame, wxGLCanvas)
    EVT_SIZE(GLFrame::OnSize)
    EVT_PAINT(GLFrame::OnPaint)
    EVT_ENTER_WINDOW( GLFrame::OnEnterWindow )
    EVT_ERASE_BACKGROUND(GLFrame::OnEraseBackground)
    EVT_MOUSE_EVENTS(GLFrame::OnMouseEvent)
    EVT_LEAVE_WINDOW(GLFrame::OnLeaveWindow)
    EVT_IDLE(GLFrame::onIdle)
    EVT_KEY_DOWN(GLFrame::OnChar)
    EVT_KEY_UP(GLFrame::OnChar2)
END_EVENT_TABLE()
