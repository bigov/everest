#ifndef __EV_FRAME_HPP__
#define __EV_FRAME_HPP__

#include "app.hpp"
#include "text.hpp"

namespace ev {


// Define a new frame type: this is going to be our main frame
class frame : public wxFrame
{
  public:
    // ctor(s)
    frame(const wxString& title, wxWindowID id,
          const wxPoint& pos = wxDefaultPosition,
          const wxSize& size = wxDefaultSize,
          long style = wxDEFAULT_FRAME_STYLE);

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnSaveAs(wxCommandEvent& event);

    void OnBold(wxCommandEvent& event);
    void OnItalic(wxCommandEvent& event);
    void OnUnderline(wxCommandEvent& event);

    void OnStrikethrough(wxCommandEvent& event);
    void OnSuperscript(wxCommandEvent& event);
    void OnSubscript(wxCommandEvent& event);

    void OnUpdateBold(wxUpdateUIEvent& event);
    void OnUpdateItalic(wxUpdateUIEvent& event);
    void OnUpdateUnderline(wxUpdateUIEvent& event);
    void OnUpdateStrikethrough(wxUpdateUIEvent& event);
    void OnUpdateSuperscript(wxUpdateUIEvent& event);
    void OnUpdateSubscript(wxUpdateUIEvent& event);

    void OnAlignLeft(wxCommandEvent& event);
    void OnAlignCentre(wxCommandEvent& event);
    void OnAlignRight(wxCommandEvent& event);

    void OnUpdateAlignLeft(wxUpdateUIEvent& event);
    void OnUpdateAlignCentre(wxUpdateUIEvent& event);
    void OnUpdateAlignRight(wxUpdateUIEvent& event);

    void OnIndentMore(wxCommandEvent& event);
    void OnIndentLess(wxCommandEvent& event);

    void OnFont(wxCommandEvent& event);
    void OnImage(wxCommandEvent& event);
    void OnUpdateImage(wxUpdateUIEvent& event);
    void OnParagraph(wxCommandEvent& event);
    void OnFormat(wxCommandEvent& event);
    void OnUpdateFormat(wxUpdateUIEvent& event);

    void OnInsertSymbol(wxCommandEvent& event);

    void OnLineSpacingHalf(wxCommandEvent& event);
    void OnLineSpacingDouble(wxCommandEvent& event);
    void OnLineSpacingSingle(wxCommandEvent& event);

    void OnParagraphSpacingMore(wxCommandEvent& event);
    void OnParagraphSpacingLess(wxCommandEvent& event);

    void OnNumberList(wxCommandEvent& event);
    void OnBulletsAndNumbering(wxCommandEvent& event);
    void OnItemizeList(wxCommandEvent& event);
    void OnRenumberList(wxCommandEvent& event);
    void OnPromoteList(wxCommandEvent& event);
    void OnDemoteList(wxCommandEvent& event);
    void OnClearList(wxCommandEvent& event);

    void OnTableAddColumn(wxCommandEvent& event);
    void OnTableAddRow(wxCommandEvent& event);
    void OnTableDeleteColumn(wxCommandEvent& event);
    void OnTableDeleteRow(wxCommandEvent& event);
    void OnTableFocusedUpdateUI(wxUpdateUIEvent& event);
    void OnTableHasCellsUpdateUI(wxUpdateUIEvent& event);

    void OnReload(wxCommandEvent& event);

    void OnViewHTML(wxCommandEvent& event);

    void OnSwitchStyleSheets(wxCommandEvent& event);
    void OnManageStyles(wxCommandEvent& event);

    void OnInsertURL(wxCommandEvent& event);
    void OnURL(wxTextUrlEvent& event);
    void OnStyleSheetReplacing(wxRichTextEvent& event);

    #if wxUSE_PRINTING_ARCHITECTURE
      void OnPrint(wxCommandEvent& event);
      void OnPreview(wxCommandEvent& event);
    #endif

    void OnPageSetup(wxCommandEvent& event);

    void OnInsertImage(wxCommandEvent& event);

    void OnSetFontScale(wxCommandEvent& event);
    void OnSetDimensionScale(wxCommandEvent& event);

  protected:
    // Forward command events to the current rich text control, if any
    bool ProcessEvent(wxEvent& event) wxOVERRIDE;

    // Write text
    void WriteInitialText();

  private:
    // any class wishing to process wxWidgets events must use this macro
    wxDECLARE_EVENT_TABLE();
    text_ctrl* TextCtrl;
};

} //namespace ev

#endif
