#include "../Wizards/NewProjectWiz.h"

NewProjectWiz::NewProjectWiz(wxWindow * parent, wxWindowID id)
{
    wizard = new wxWizard(parent, id);
    new_page0 = new newprojectpage0(wizard);
    new_page1 = new newprojectpage1(wizard);

    wizard->SetPageSize( wxSize(600,450) );

    new_page0->SetNext(new_page1);
    new_page1->SetPrev(new_page0);

}

NewProjectWiz::~NewProjectWiz()
{
    delete new_page0;
    delete new_page1;
    delete wizard;
}


void NewProjectWiz::ShowWizard()
{
    wizard->RunWizard(new_page0);
}
