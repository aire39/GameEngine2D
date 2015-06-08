#include "../Window/DataPropertyViewer.h"
#include "../Window/propertyWindow.h"


propertyWindow::propertyWindow(wxWindow * parent, int id) : wxPanel(parent, id)
{
    tree_view = NULL;

    notebook = new wxNotebook(this, 100);
    layout = new wxFlexGridSizer(2, 1, 10, 0);
    data_sheet = new DataPropertyViewer(notebook);

    layout->Add(notebook, 1, wxALL|wxALIGN_CENTER, 0 );

    data_sheet->Connect(wxEVT_PG_CHANGED, wxPropertyGridEventHandler( propertyWindow::SelectedProperty ), 0, this);
    data_sheet->Connect(wxEVT_ENTER_WINDOW, wxMouseEventHandler( propertyWindow::EnterWindow ), 0, this);
}

propertyWindow::~propertyWindow()
{
    #ifdef __WXDEBUG__
        std::cout << "Deleting propertyWindow!" << std::endl;
    #endif

    data_sheet->Disconnect(wxEVT_PG_CHANGED, wxPropertyGridEventHandler( propertyWindow::SelectedProperty ), 0, this);
    data_sheet->Disconnect(wxEVT_ENTER_WINDOW, wxMouseEventHandler( propertyWindow::EnterWindow ), 0, this);

    delete data_sheet;
    delete notebook;

    layout = NULL;
    notebook = NULL;
    data_sheet = NULL;

}

void propertyWindow::HideDataProperty()
{
    data_sheet->Show(false);
    data_sheet->Refresh();
    Refresh();
}

void propertyWindow::BindProjectTree( projectTreeView * tree_view )
{
    this->tree_view = tree_view;

    data_sheet->BindTreeViewer( tree_view );
    notebook->AddPage( this->data_sheet, "Data" );

    notebook->SetSize(0, 0, GetClientSize().GetWidth(), GetClientSize().GetHeight() );
    data_sheet->SetSize( notebook->GetSize().GetWidth()-8, notebook->GetSize().GetHeight()-25 );

    data_sheet->Show(true);
    SetSizerAndFit(layout, true);
    Refresh();
}


void propertyWindow::OnSize(wxSizeEvent & event)
{
    if( tree_view != NULL )
    {
        notebook->SetSize(0, 0,  GetClientSize().GetWidth(), GetClientSize().GetHeight() );

        if( notebook->GetPageText( notebook->GetSelection() ).compare("Data") == 0 )
            data_sheet->SetSize( notebook->GetSize().GetWidth()-8, notebook->GetSize().GetHeight()-25 );
    }
}

void propertyWindow::NotebookPageChanged( wxNotebookEvent & event )
{
    if( notebook->GetPageText( event.GetSelection() ).compare("Data") == 0 )
        data_sheet->SetSize( notebook->GetSize().GetWidth()-8, notebook->GetSize().GetHeight()-25 );
}

void propertyWindow::EnterWindow(wxMouseEvent & event)
{
    event.Skip();

    selected_object = NULL;
    selected_object = tree_view->selectedEntity();
    if( selected_object != NULL )
    {
        data_sheet->Show(true);
        data_sheet->Refresh();
        Update();

        data_sheet->UseAnimationCategory(false);
        data_sheet->UseTextCategory(false);

        if( !selected_object->s_getTexture().empty() )
            data_sheet->UseTextureCategory(false);

        if( notebook->GetPageText( notebook->GetSelection() ).compare("Data") == 0 )
        {
            data_sheet->SetSize( GetClientSize().GetWidth(), GetClientSize().GetHeight() );

            if( selected_object != NULL )
            {
                data_sheet->SetDataName( selected_object->getName() );
                data_sheet->SetDataColor( selected_object->getColor().getX(), selected_object->getColor().getY(), selected_object->getColor().getZ() );
                data_sheet->SetDataOpacity( selected_object->getColor().getW() );
                data_sheet->SetDataPosition( selected_object->getPosition().getX(), selected_object->getPosition().getY(), selected_object->getPosition().getZ() );
                data_sheet->SetDataRotate( selected_object->getRotation() );
                data_sheet->SetDataScale( selected_object->getScale().getX(), selected_object->getScale().getY(), selected_object->getScale().getZ() );
                data_sheet->SetDataLayer( selected_object->getLayer() );

                if( typeid(*selected_object) == typeid(Text) )
                {
                    data_sheet->UseTextCategory(true);
                    data_sheet->UseAnimationCategory(true);

                    data_sheet->SetDataText( ((Text*)selected_object)->getText() );
                    data_sheet->SetDataEnableAnim( ((Text*)selected_object)->IsAnimating() );
                    data_sheet->SetDataFramerate( ((Text*)selected_object)->GetFrameRate() );
                }
                else if( typeid(*selected_object) == typeid(Sprite) )
                {
                    if( ((Sprite*)selected_object)->GetNumberOfAnimation() > 0 )
                    {
                        wxArrayString attached_animations;
                        Sprite *_sprite = ((Sprite*)selected_object);

                        for(int i=0; i<_sprite->GetNumberOfAnimation(); i++)
                            attached_animations.Add( (wxString)_sprite->GetAnimationName(i) );

                        data_sheet->SetDataAttachdAnimation( attached_animations );


                        data_sheet->UseAnimationCategory(true, "sprite");
                        data_sheet->SetDataFramerate( _sprite->GetAnimation(0)->GetFrameRate() );
                    }

                    if( !((Sprite*)selected_object)->s_getTexture().empty() )
                    {
                        data_sheet->SetDataTextureRepeatX( ((Sprite*)selected_object)->getTextureRepeatX() );
                        data_sheet->SetDataTextureRepeatY( ((Sprite*)selected_object)->getTextureRepeatY() );
                        data_sheet->SetDataTextureFlipX( ((Sprite*)selected_object)->isSpriteHFlip() );
                        data_sheet->SetDataTextureFlipY( ((Sprite*)selected_object)->isSpriteVFlip() );
                        data_sheet->UseTextureCategory(true, "sprite");
                    }
                }

            }

        }

        if( notebook != NULL && data_sheet != NULL )
        {
            notebook->SetSize(0, 0, GetClientSize().GetWidth(), GetClientSize().GetHeight() );
            data_sheet->SetSize( notebook->GetSize().GetWidth()-8, notebook->GetSize().GetHeight()-25 );
        }

    }
    else
    {
        data_sheet->Show(false);
        data_sheet->Refresh();
        Update();
    }

    data_sheet->Refresh();

}

void propertyWindow::SelectedProperty( wxPropertyGridEvent & event )
{

    if( event.GetProperty()->GetLabel().compare("name") == 0 )
    {
        data_sheet->SetDataName( selected_object->getName() );
    }
    else if( event.GetProperty()->GetLabel().compare("color") == 0 )
    {
        if( selected_object != NULL )
            selected_object->setColor( data_sheet->GetDataColor()[0], data_sheet->GetDataColor()[1], data_sheet->GetDataColor()[2] );
    }
    else if( event.GetProperty()->GetLabel().compare("opacity") == 0 )
    {
        if( selected_object != NULL )
            selected_object->setColor( data_sheet->GetDataColor()[0], data_sheet->GetDataColor()[1], data_sheet->GetDataColor()[2], data_sheet->GetDataOpacity() );
    }
    else if( event.GetProperty()->GetLabel().compare("position") == 0 )
    {
        if( selected_object != NULL )
            selected_object->setPosition( data_sheet->GetDataPosition()[0], data_sheet->GetDataPosition()[1], data_sheet->GetDataPosition()[2] );
    }
    else if( event.GetProperty()->GetLabel().compare("rotate") == 0 )
    {
        if( selected_object != NULL )
            selected_object->setRotation( data_sheet->GetDataRotate() );
    }
    else if( event.GetProperty()->GetLabel().compare("scale") == 0 )
    {
        if( selected_object != NULL )
            selected_object->setScale( data_sheet->GetDataScale()[0], data_sheet->GetDataScale()[1], data_sheet->GetDataScale()[2] );
    }
    else if( event.GetProperty()->GetLabel().compare("layer") == 0 )
    {
        if( selected_object != NULL )
            selected_object->setLayer( data_sheet->GetDataLayer() );
    }
    else if( event.GetProperty()->GetLabel().compare("text value") == 0 )
    {
        if( selected_object != NULL )
            ((Text*)selected_object)->setText( data_sheet->GetDataText() );
    }
    else if( event.GetProperty()->GetLabel().compare("enable") == 0 )
    {

        if( selected_object != NULL )
        {
            if( typeid(*selected_object) == typeid(Text) )
            {
                Text * _text = (Text*)selected_object;
                _text->AnimateText( data_sheet->GetDataEnableAnim() );
            }
            else if( typeid(*selected_object) == typeid(Sprite) )
            {
                Sprite * _sprite = (Sprite*)selected_object;
                //Add Code Here
                std::cout << "Sprite Has Parameter But Not Implemented!" << std::endl;

                for(int i=0; i<_sprite->GetNumberOfAnimation(); i++)
                {
                    _sprite->play_animationSet(i);
                    _sprite->UseAnimation(false);
                }

                _sprite->play_animationSet( data_sheet->GetDataAttachedAnimationChoice() );
                _sprite->UseAnimation( data_sheet->GetDataEnableAnim() );

            }
        }
    }
    else if( event.GetProperty()->GetLabel().compare("anims") == 0 )
    {

        if( selected_object != NULL )
        {
                Sprite * _sprite = (Sprite*)selected_object;
                data_sheet->SetDataFramerate( _sprite->GetAnimation(event.GetProperty()->GetValue().GetInteger())->GetFrameRate() );
        }
    }
    else if( event.GetProperty()->GetLabel().compare("frame rate") == 0 )
    {
        if( typeid(*selected_object) == typeid(Text) )
        {
            Text * _text = (Text*)selected_object;
            _text->SetFrameRate( data_sheet->GetDataFramerate() );
        }
        else if( typeid(*selected_object) == typeid(Sprite) )
        {
            Sprite * _sprite = (Sprite*)selected_object;
            //Add Code Here
            _sprite->SetAnimationFPS( data_sheet->GetDataAttachedAnimationChoice(), data_sheet->GetDataFramerate() );
        }
    }
    else if( event.GetProperty()->GetLabel().compare("RepeatX") == 0  )
    {
        Sprite * _sprite = (Sprite*)selected_object;
        _sprite->setTextureRepeatX(data_sheet->GetDataTextureRepeatX());
    }
    else if( event.GetProperty()->GetLabel().compare("RepeatY") == 0  )
    {
        Sprite * _sprite = (Sprite*)selected_object;
        _sprite->setTextureRepeatY(data_sheet->GetDataTextureRepeatY());
    }
    else if( event.GetProperty()->GetLabel().compare("FlipX") == 0  )
    {
        Sprite * _sprite = (Sprite*)selected_object;
        _sprite->flipHorizontalTexCoordinates();
    }
    else if( event.GetProperty()->GetLabel().compare("FlipY") == 0  )
    {
        Sprite * _sprite = (Sprite*)selected_object;
        _sprite->flipVerticleTexCoordinates();
    }

    data_sheet->Refresh();

}


BEGIN_EVENT_TABLE( propertyWindow, wxWindow )

    EVT_SIZE( propertyWindow::OnSize )
    EVT_NOTEBOOK_PAGE_CHANGED(100, propertyWindow::NotebookPageChanged)
    EVT_ENTER_WINDOW( propertyWindow::EnterWindow )

END_EVENT_TABLE()
