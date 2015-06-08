#ifndef PROPERTYWINDOW_H
#define PROPERTYWINDOW_H

#include <wx/notebook.h>
#include <wx/sizer.h>

#include "../Window/projectTreeView.h"
#include "../Core/Animation.h"

class projectTreeView;
class DataPropertyViewer;
class wxPropertyGridEvent;
class Entity;

class propertyWindow : public wxPanel
{
    DECLARE_EVENT_TABLE()

    private:

        wxNotebook      * notebook;
        wxFlexGridSizer * layout;

        projectTreeView * tree_view;
        Entity          * selected_object;

        DataPropertyViewer * data_sheet;

    public:

        propertyWindow( wxWindow * parent=NULL, int id=0 );
        ~propertyWindow();

        void BindProjectTree( projectTreeView * tree_view );

        void OnSize( wxSizeEvent & event );
        void NotebookPageChanged( wxNotebookEvent & event );
        void EnterWindow(wxMouseEvent & event);

        void SelectedProperty( wxPropertyGridEvent & event );

        void HideDataProperty();

};

#endif // PROPERTYWINDOW_H
