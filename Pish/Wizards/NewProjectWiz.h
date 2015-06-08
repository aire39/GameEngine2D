#ifndef NEWPROJECTWIZ_H
#define NEWPROJECTWIZ_H

#include <wx/wizard.h>
#include "../WizardPages/newprojectpage0.h"
#include "../WizardPages/newprojectpage1.h"
#include <string>

class NewProjectWiz
{
    private:

        wxWizard * wizard;
        newprojectpage0 * new_page0;
        newprojectpage1 * new_page1;

        float scene_bg_color[3];

        std::string path_of_project;
        std::string name_of_project;

    public:

        NewProjectWiz(wxWindow * parent = NULL, wxWindowID id = wxID_ANY);
        ~NewProjectWiz();

        void ShowWizard();
};

#endif // NEWPROJECTWIZ_H
