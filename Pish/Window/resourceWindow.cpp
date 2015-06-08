#include "../Window/resourceWindow.h"


resourceWindow::resourceWindow(wxWindow * parent, wxWindowID id) : wxPanel(parent, id)
{
    notebook = new wxNotebook(this, 5000);
    choice_resource = new wxChoice(this, 5001);
    search_treeView = new wxTextCtrl(this, wxID_ANY);
    listbox = new wxListBox(notebook, 5002);
    layout = new wxFlexGridSizer(3, 1, 0, 0);


    choice_resource->Append("<none>");
    choice_resource->Append("objects");
    choice_resource->Append("scripts");
    choice_resource->Append("textures");
    choice_resource->Append("colliders");
    choice_resource->Append("emitters");
    choice_resource->Append("animations");
    choice_resource->Append("links");
    choice_resource->Append("<all>");

    layout->Add(choice_resource, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
    layout->Add(search_treeView, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );
    layout->Add(notebook, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

    SetSizerAndFit(layout, true);

    search_treeView->Hide();

    animation_manager = NULL;

}

resourceWindow::~resourceWindow()
{
    #ifdef __WXDEBUG__
        std::cout << "Deleting resourceWindow!" << std::endl;
    #endif

    delete notebook;
    delete choice_resource;
    delete search_treeView;
}


void resourceWindow::BindTreeView(projectTreeView * tree_view)
{
    this->tree_view = tree_view;
    notebook->AddPage(tree_view, "Project", true);
    notebook->AddPage(listbox, "Resources", false);
}

void resourceWindow::BindScriptManager(scriptMng * script_manager)
{
    this->script_manager = script_manager;
}

void resourceWindow::BindTextEditor(textEditor * text_editor)
{
    this->text_editor = text_editor;
}

void resourceWindow::BindAnimationManager( animationManager * animation_manager )
{
    this->animation_manager = animation_manager;

}

wxNotebook * resourceWindow::notebookwindow()
{
    return notebook;
}


void resourceWindow::OnSize(wxSizeEvent & event)
{
    notebook->SetSize( 0, 30, GetSize().GetWidth(), GetSize().GetHeight()-30 );
    listbox->SetSize( 0, 30, GetSize().GetWidth(), GetSize().GetHeight()-30 );
    choice_resource->SetSize(wxSize(GetSize().GetWidth()-10, 20));
    search_treeView->SetSize(wxSize(GetSize().GetWidth()-10, 20));

    //if( tree_view != NULL )
    //    tree_view->SetSize( 0, 30, GetSize().GetWidth(), GetSize().GetHeight()-30 );

    std::cout << "Resource Window Changed Size!" << std::endl;
}

void resourceWindow::OnNoteBookSwitch(wxNotebookEvent & event)
{
    if( notebook->GetPageCount() > 0 )
    {
        std::cout << "Notebook Switch Test! " << notebook->GetPageText(notebook->GetSelection()) << std::endl;

        if( notebook->GetPageText(notebook->GetSelection()).compare("Project") == 0 )
        {
            choice_resource->Show(false);
            search_treeView->Show(true);
        }
        else if( notebook->GetPageText(notebook->GetSelection()).compare("Resources") == 0 )
        {
            choice_resource->Show(true);
            search_treeView->Show(false);
        }
    }

}

void resourceWindow::OnChoiceChange(wxCommandEvent & event)
{
    std::cout << "Choice Changed! " << event.GetString() << std::endl;

    if( event.GetString().compare("<none>") == 0)
    {
        listbox->Clear();
    }
    else if( event.GetString().compare("objects") == 0 )
    {
        listbox->Clear();
    }
    else if( event.GetString().compare("scripts") == 0 )
    {
        listbox->Clear();

        if( script_manager->get_number_of_scripts() != 0 )
        {

			std::string * str = new std::string[script_manager->get_number_of_scripts()];
            script_manager->getAllScriptName(str);
            for(int i=0; i<script_manager->get_number_of_scripts(); i++)
                listbox->Append( str[i] );
        }
        else
            listbox->Append("<No Scripts>");
    }
    else if( event.GetString().compare("animations") == 0 )
    {
        listbox->Clear();

        if( animation_manager != NULL )
            if( animation_manager->number_of_animations() != 0 )
            {
                for(int i=0; i<animation_manager->number_of_animations(); i++)
                    listbox->Append( animation_manager->getAnimation(i)->AnimName() );
            }
            else
                listbox->Append("<No Animations>");
        else
            listbox->Append("<Manager Mem Address Missing>");

    }
}

void resourceWindow::OnListBoxItemDClicked(wxCommandEvent & event)
{
    std::cout << "ListBox DClicked! " << event.GetString() << std::endl;

    if( choice_resource->GetString( choice_resource->GetSelection() ).compare("scripts") == 0 )
    {

        if( script_manager->getScript((std::string)event.GetString()) != NULL )
        {
            text_editor->ClearTextEditor();
            text_editor->SetText( script_manager->getScript((std::string)event.GetString())->getData() );
        }
        else
            std::cout << "Not a script!" << std::endl;

    }
}

BEGIN_EVENT_TABLE(resourceWindow, wxPanel)

    EVT_SIZE(resourceWindow::OnSize)
    EVT_NOTEBOOK_PAGE_CHANGED(5000, resourceWindow::OnNoteBookSwitch)
    EVT_CHOICE(5001, resourceWindow::OnChoiceChange)
    EVT_LISTBOX_DCLICK(5002, resourceWindow::OnListBoxItemDClicked)

END_EVENT_TABLE()
