#include "frame.hpp"

// Create a new application object: this macro will allow wxWidgets to create
// the application object during program execution (it's better than using a
// static object for many reasons) and also implements the accessor function
// wxGetApp() which will return the reference of the right type (i.e. MyApp and
// not wxApp)
wxIMPLEMENT_APP(ev::app);

namespace ev {

// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
frame::frame(const wxString& title, wxWindowID id, const wxPoint& pos,
  const wxSize& size, long style): wxFrame(NULL, id, title, pos, size, style)
{
  #ifdef __WXMAC__
    SetWindowVariant(wxWINDOW_VARIANT_SMALL);
  #endif

    // set the frame icon
    SetIcon(wxICON(sample));

    // create a menu bar
    wxMenu *fileMenu = new wxMenu;

    // the "About" item should be in the help menu
    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(ID_About, wxT("&About\tF1"), wxT("Show about dialog"));

    fileMenu->Append(wxID_OPEN, wxT("&Open\tCtrl+O"), wxT("Open a file"));
    fileMenu->Append(wxID_SAVE, wxT("&Save\tCtrl+S"), wxT("Save a file"));
    fileMenu->Append(wxID_SAVEAS, wxT("&Save As...\tF12"),
                     wxT("Save to a new file"));
    fileMenu->AppendSeparator();
    fileMenu->Append(ID_RELOAD, wxT("&Reload Text\tF2"),
                     wxT("Reload the initial text"));
    fileMenu->AppendSeparator();
    fileMenu->Append(ID_PAGE_SETUP, wxT("Page Set&up..."), wxT("Page setup"));
#if wxUSE_PRINTING_ARCHITECTURE
    fileMenu->Append(ID_PRINT, wxT("&Print...\tCtrl+P"), wxT("Print"));
    fileMenu->Append(ID_PREVIEW, wxT("Print Pre&view"), wxT("Print preview"));
#endif
    fileMenu->AppendSeparator();
    fileMenu->Append(ID_VIEW_HTML, wxT("&View as HTML"), wxT("View HTML"));
    fileMenu->AppendSeparator();
    fileMenu->Append(ID_Quit, wxT("E&xit\tAlt+X"), wxT("Quit this program"));

    wxMenu* editMenu = new wxMenu;
    editMenu->Append(wxID_UNDO, _("&Undo\tCtrl+Z"));
    editMenu->Append(wxID_REDO, _("&Redo\tCtrl+Y"));
    editMenu->AppendSeparator();
    editMenu->Append(wxID_CUT, _("Cu&t\tCtrl+X"));
    editMenu->Append(wxID_COPY, _("&Copy\tCtrl+C"));
    editMenu->Append(wxID_PASTE, _("&Paste\tCtrl+V"));

    editMenu->AppendSeparator();
    editMenu->Append(wxID_SELECTALL, _("Select A&ll\tCtrl+A"));
    editMenu->AppendSeparator();
    editMenu->Append(ID_SET_FONT_SCALE, _("Set &Text Scale..."));
    editMenu->Append(ID_SET_DIMENSION_SCALE, _("Set &Dimension Scale..."));

    wxMenu* formatMenu = new wxMenu;
    formatMenu->AppendCheckItem(ID_FORMAT_BOLD, _("&Bold\tCtrl+B"));
    formatMenu->AppendCheckItem(ID_FORMAT_ITALIC, _("&Italic\tCtrl+I"));
    formatMenu->AppendCheckItem(ID_FORMAT_UNDERLINE, _("&Underline\tCtrl+U"));
    formatMenu->AppendSeparator();
    formatMenu->AppendCheckItem(ID_FORMAT_STRIKETHROUGH, _("Stri&kethrough"));
    formatMenu->AppendCheckItem(ID_FORMAT_SUPERSCRIPT, _("Superscrip&t"));
    formatMenu->AppendCheckItem(ID_FORMAT_SUBSCRIPT, _("Subscrip&t"));
    formatMenu->AppendSeparator();
    formatMenu->AppendCheckItem(ID_FORMAT_ALIGN_LEFT, _("L&eft Align"));
    formatMenu->AppendCheckItem(ID_FORMAT_ALIGN_RIGHT, _("&Right Align"));
    formatMenu->AppendCheckItem(ID_FORMAT_ALIGN_CENTRE, _("&Centre"));
    formatMenu->AppendSeparator();
    formatMenu->Append(ID_FORMAT_INDENT_MORE, _("Indent &More"));
    formatMenu->Append(ID_FORMAT_INDENT_LESS, _("Indent &Less"));
    formatMenu->AppendSeparator();
    formatMenu->Append(ID_FORMAT_PARAGRAPH_SPACING_MORE, _("Increase Paragraph &Spacing"));
    formatMenu->Append(ID_FORMAT_PARAGRAPH_SPACING_LESS, _("Decrease &Paragraph Spacing"));
    formatMenu->AppendSeparator();
    formatMenu->Append(ID_FORMAT_LINE_SPACING_SINGLE, _("Normal Line Spacing"));
    formatMenu->Append(ID_FORMAT_LINE_SPACING_HALF, _("1.5 Line Spacing"));
    formatMenu->Append(ID_FORMAT_LINE_SPACING_DOUBLE, _("Double Line Spacing"));
    formatMenu->AppendSeparator();
    formatMenu->Append(ID_FORMAT_FONT, _("&Font..."));
    formatMenu->Append(ID_FORMAT_IMAGE, _("Image Property"));
    formatMenu->Append(ID_FORMAT_PARAGRAPH, _("&Paragraph..."));
    formatMenu->Append(ID_FORMAT_CONTENT, _("Font and Pa&ragraph...\tShift+Ctrl+F"));
    formatMenu->AppendSeparator();
    formatMenu->Append(ID_SWITCH_STYLE_SHEETS, _("&Switch Style Sheets"));
    formatMenu->Append(ID_MANAGE_STYLES, _("&Manage Styles"));

    wxMenu* listsMenu = new wxMenu;
    listsMenu->Append(ID_FORMAT_BULLETS_AND_NUMBERING, _("Bullets and &Numbering..."));
    listsMenu->AppendSeparator();
    listsMenu->Append(ID_FORMAT_NUMBER_LIST, _("Number List"));
    listsMenu->Append(ID_FORMAT_ITEMIZE_LIST, _("Itemize List"));
    listsMenu->Append(ID_FORMAT_RENUMBER_LIST, _("Renumber List"));
    listsMenu->Append(ID_FORMAT_PROMOTE_LIST, _("Promote List Items"));
    listsMenu->Append(ID_FORMAT_DEMOTE_LIST, _("Demote List Items"));
    listsMenu->Append(ID_FORMAT_CLEAR_LIST, _("Clear List Formatting"));

    wxMenu* tableMenu = new wxMenu;
    tableMenu->Append(ID_TABLE_ADD_COLUMN, _("&Add Column"));
    tableMenu->Append(ID_TABLE_ADD_ROW, _("Add &Row"));
    tableMenu->Append(ID_TABLE_DELETE_COLUMN, _("Delete &Column"));
    tableMenu->Append(ID_TABLE_DELETE_ROW, _("&Delete Row"));

    wxMenu* insertMenu = new wxMenu;
    insertMenu->Append(ID_INSERT_SYMBOL, _("&Symbol...\tCtrl+I"));
    insertMenu->Append(ID_INSERT_URL, _("&URL..."));
    insertMenu->Append(ID_INSERT_IMAGE, _("&Image..."));

    // now append the freshly created menu to the menu bar...
    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, wxT("&File"));
    menuBar->Append(editMenu, wxT("&Edit"));
    menuBar->Append(formatMenu, wxT("F&ormat"));
    menuBar->Append(listsMenu, wxT("&Lists"));
    menuBar->Append(tableMenu, wxT("&Tables"));
    menuBar->Append(insertMenu, wxT("&Insert"));
    menuBar->Append(helpMenu, wxT("&Help"));

    // ... and attach this menu bar to the frame
    SetMenuBar(menuBar);

    // create a status bar just for fun (by default with 1 pane only)
    // but don't create it on limited screen space (mobile device)
    bool is_pda = wxSystemSettings::GetScreenType() <= wxSYS_SCREEN_PDA;

#if wxUSE_STATUSBAR
    if ( !is_pda )
    {
        CreateStatusBar(2);
        SetStatusText(wxT("Welcome to EveRest!"));
    }
#endif

    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(sizer);

    /// On Mac, don't create a 'native' wxToolBar because small bitmaps are not
    /// supported by native toolbars. On Mac, a non-native, small-bitmap toolbar
    /// doesn't show unless it is explicitly managed, hence the use of sizers.
    /// In a real application, use larger icons for the main toolbar to avoid
    /// the need for this workaround. Or, use the toolbar in a container window
    /// as part of a more complex hierarchy, and the toolbar will automatically
    /// be non-native.

    wxSystemOptions::SetOption(wxT("mac.toolbar.no-native"), 1);

    wxToolBar* toolBar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize,
                                       wxNO_BORDER|wxTB_FLAT|wxTB_NODIVIDER|wxTB_NOALIGN);

    sizer->Add(toolBar, 0, wxEXPAND);

    toolBar->AddTool(wxID_OPEN, wxEmptyString, wxBitmap(open_xpm), _("Open"));
    toolBar->AddTool(wxID_SAVEAS, wxEmptyString, wxBitmap(save_xpm), _("Save"));
    toolBar->AddSeparator();
    toolBar->AddTool(wxID_CUT, wxEmptyString, wxBitmap(cut_xpm), _("Cut"));
    toolBar->AddTool(wxID_COPY, wxEmptyString, wxBitmap(copy_xpm), _("Copy"));
    toolBar->AddTool(wxID_PASTE, wxEmptyString, wxBitmap(paste_xpm), _("Paste"));
    toolBar->AddSeparator();
    toolBar->AddTool(wxID_UNDO, wxEmptyString, wxBitmap(undo_xpm), _("Undo"));
    toolBar->AddTool(wxID_REDO, wxEmptyString, wxBitmap(redo_xpm), _("Redo"));
    toolBar->AddSeparator();
    toolBar->AddCheckTool(ID_FORMAT_BOLD, wxEmptyString, wxBitmap(bold_xpm),
                          wxNullBitmap, _("Bold"));
    toolBar->AddCheckTool(ID_FORMAT_ITALIC, wxEmptyString, wxBitmap(italic_xpm),
                          wxNullBitmap, _("Italic"));
    toolBar->AddCheckTool(ID_FORMAT_UNDERLINE, wxEmptyString,
                          wxBitmap(underline_xpm), wxNullBitmap, _("Underline"));
    toolBar->AddSeparator();
    toolBar->AddCheckTool(ID_FORMAT_ALIGN_LEFT, wxEmptyString,
                          wxBitmap(alignleft_xpm), wxNullBitmap, _("Align Left"));
    toolBar->AddCheckTool(ID_FORMAT_ALIGN_CENTRE, wxEmptyString,
                          wxBitmap(centre_xpm), wxNullBitmap, _("Centre"));
    toolBar->AddCheckTool(ID_FORMAT_ALIGN_RIGHT, wxEmptyString,
                          wxBitmap(alignright_xpm), wxNullBitmap, _("Align Right"));
    toolBar->AddSeparator();
    toolBar->AddTool(ID_FORMAT_INDENT_LESS, wxEmptyString,
                     wxBitmap(indentless_xpm), _("Indent Less"));
    toolBar->AddTool(ID_FORMAT_INDENT_MORE, wxEmptyString,
                     wxBitmap(indentmore_xpm), _("Indent More"));
    toolBar->AddSeparator();
    toolBar->AddTool(ID_FORMAT_FONT, wxEmptyString, wxBitmap(font_xpm), _("Font"));
    toolBar->AddSeparator();

    wxRichTextStyleComboCtrl* combo = new wxRichTextStyleComboCtrl(toolBar,
      ID_RICHTEXT_STYLE_COMBO, wxDefaultPosition, wxSize(160, -1), wxCB_READONLY);
    toolBar->AddControl(combo);

    toolBar->Realize();

    wxSplitterWindow* splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE);
    sizer->Add(splitter, 1, wxEXPAND);

    wxFont textFont = wxFont(wxFontInfo(12).Family(wxFONTFAMILY_ROMAN));
    wxFont boldFont = wxFont(wxFontInfo(12).Family(wxFONTFAMILY_ROMAN));
    wxFont italicFont = wxFont(wxFontInfo(12).Family(wxFONTFAMILY_ROMAN).Italic());

    TextCtrl = new text_ctrl(splitter, ID_RICHTEXT_CTRL, wxEmptyString,
      wxDefaultPosition, wxDefaultSize, wxVSCROLL|wxHSCROLL /*|wxWANTS_CHARS*/);
    wxASSERT(!TextCtrl->GetBuffer().GetAttributes().HasFontPixelSize());

    wxFont font(wxFontInfo(12).Family(wxFONTFAMILY_ROMAN));

    TextCtrl->SetFont(font);

    wxASSERT(!TextCtrl->GetBuffer().GetAttributes().HasFontPixelSize());

    TextCtrl->SetMargins(10, 10);

    TextCtrl->SetStyleSheet(wxGetApp().GetStyleSheet());

    combo->SetStyleSheet(wxGetApp().GetStyleSheet());
    combo->SetRichTextCtrl(TextCtrl);
    combo->UpdateStyles();

    wxRichTextStyleListCtrl* styleListCtrl =
      new wxRichTextStyleListCtrl(splitter, ID_RICHTEXT_STYLE_LIST);

    wxSize display = wxGetDisplaySize();
    if ( is_pda && ( display.GetWidth() < display.GetHeight() ) )
    {
        splitter->SplitHorizontally(TextCtrl, styleListCtrl);
    }
    else
    {
        int width = GetClientSize().GetWidth() * 0.8;
        splitter->SplitVertically(TextCtrl, styleListCtrl, width);
        splitter->SetSashGravity(0.8);
    }

    Layout();

    splitter->UpdateSize();

    styleListCtrl->SetStyleSheet(wxGetApp().GetStyleSheet());
    styleListCtrl->SetRichTextCtrl(TextCtrl);
    styleListCtrl->UpdateStyles();

    WriteInitialText();
}

// Write text
void frame::WriteInitialText()
{
  text_ctrl& r = *TextCtrl;

  r.SetDefaultStyle(wxRichTextAttr());

  r.Freeze();

  r.BeginSuppressUndo();

  r.BeginParagraphSpacing(0, 20);

  r.BeginAlignment(wxTEXT_ALIGNMENT_CENTRE);
  r.BeginBold();

  r.BeginFontSize(14);

  wxString lineBreak = (wxChar) 29;

  r.WriteText(wxString(wxT("Welcome to EveRest"))
    + lineBreak + wxT("for editing and presenting styled text and images\n"));
  r.EndFontSize();

  r.BeginItalic();
  r.WriteText(wxT("by Julian Smart"));
  r.EndItalic();

  r.EndBold();
  r.Newline();

  r.WriteImage(wxBitmap(zebra_xpm));

  r.Newline();
  r.Newline();

  r.EndAlignment();

#if 1
    r.BeginAlignment(wxTEXT_ALIGNMENT_CENTRE);
    r.WriteText(wxString(wxT("This is a simple test for a floating left image"
      "test. The zebra image should be placed at the left side of the current"
      "buffer and all the text should flow around it at the right side. This is"
      "a simple test for a floating left image test. The zebra image should be"
      "placed at the left side of the current buffer and all the text should"
      "flow around it at the right side. This is a simple test for a floating"
      "left image test. The zebra image should be placed at the left side of"
      "the current buffer and all the text around it at the right side.")));
    r.Newline();
    r.EndAlignment();
#endif

    r.BeginAlignment(wxTEXT_ALIGNMENT_LEFT);
    wxRichTextAttr imageAttr;
    imageAttr.GetTextBoxAttr().SetFloatMode(wxTEXT_BOX_ATTR_FLOAT_LEFT);
    r.WriteText(wxString(wxT("This is a simple test for a floating left image"
      "test. The zebra image should be placed at the left side of the current"
      "buffer and all text should flow around it at the right side. This is"
      "a simple test for a floating left image test. The zebra image should be"
      "placed at the left side of the current buffer and all the text should "
      "flow around it at the right side. This is a simple test for a floating"
      "left image test. The zebra image should be placed at the left side of"
      "the current buffer and all the text around it at the right side.")));
    r.WriteImage(wxBitmap(zebra_xpm), wxBITMAP_TYPE_PNG, imageAttr);

    imageAttr.GetTextBoxAttr().GetTop().SetValue(200);
    imageAttr.GetTextBoxAttr().GetTop().SetUnits(wxTEXT_ATTR_UNITS_PIXELS);
    imageAttr.GetTextBoxAttr().SetFloatMode(wxTEXT_BOX_ATTR_FLOAT_RIGHT);
    r.WriteImage(wxBitmap(zebra_xpm), wxBITMAP_TYPE_PNG, imageAttr);
    r.WriteText(wxString(wxT("This is a simple test for a floating right image"
      "test. The zebra image should be placed at the right side of the current"
      "buffer and all the text should flow around it at the left side. This is"
      "a simple test for a floating left image test. The zebra image should be"
      "placed at the right side of the current buffer and all the text should"
      "flow around it at the left side. This is a simple test for a floating"
      "left image test. The zebra image should be placed at the right side of"
      "the current buffer and all the text around it at the left side.")));
    r.EndAlignment();
    r.Newline();

    r.WriteText(wxT("What can you do with this thing? "));

    r.WriteImage(wxBitmap(smiley_xpm));
    r.WriteText(wxT(" Well, you can change text "));

    r.BeginTextColour(*wxRED);
    r.WriteText(wxT("colour, like this red bit."));
    r.EndTextColour();

    wxRichTextAttr backgroundColourAttr;
    backgroundColourAttr.SetBackgroundColour(*wxGREEN);
    backgroundColourAttr.SetTextColour(*wxBLUE);
    r.BeginStyle(backgroundColourAttr);
    r.WriteText(wxT(" And this blue on green bit."));
    r.EndStyle();

    r.WriteText(wxT(" Naturally you can make things "));
    r.BeginBold();
    r.WriteText(wxT("bold "));
    r.EndBold();
    r.BeginItalic();
    r.WriteText(wxT("or italic "));
    r.EndItalic();
    r.BeginUnderline();
    r.WriteText(wxT("or underlined."));
    r.EndUnderline();

    r.BeginFontSize(14);
    r.WriteText(wxT(" Different font sizes on the same line is allowed, too."));
    r.EndFontSize();

    r.WriteText(wxT(" Next we'll show an indented paragraph."));

    r.Newline();

    r.BeginLeftIndent(60);
    r.WriteText(wxT("It was in January, the most down-trodden month of an"
      "Edinburgh winter. An attractive woman came into the cafe, remarkable."));
    r.Newline();

    r.EndLeftIndent();

    r.WriteText(wxT("Next, we'll show a first-line indent, achieved using"
                    "BeginLeftIndent(100, -40)."));

    r.Newline();

    r.BeginLeftIndent(100, -40);

    r.WriteText(wxT("It was in January, the most down-trodden month of an"
      "Edinburgh winter. An attractive woman came into the cafe, which is"
      "nothing remarkable."));
    r.Newline();

    r.EndLeftIndent();

    r.WriteText(wxT("Numbered bullets are possible, again using subindents:"));
    r.Newline();

    r.BeginNumberedBullet(1, 100, 60);
    r.WriteText(wxT("This is my first item. Note that wxRichTextCtrl can apply"
      "numbering and bullets automatically based on list styles, but this list"
      "is formatted explicitly by setting indents."));
    r.Newline();
    r.EndNumberedBullet();

    r.BeginNumberedBullet(2, 100, 60);
    r.WriteText(wxT("This is my second item."));
    r.Newline();
    r.EndNumberedBullet();

    r.WriteText(wxT("The following paragraph is right-indented:"));
    r.Newline();

    r.BeginRightIndent(200);

    r.WriteText(wxT("It was in January, the most down-trodden month of an"
      "Edinburgh winter. An attractive woman came into the cafe, which is"
      "nothing remarkable."));
    r.Newline();

    r.EndRightIndent();

    r.WriteText(wxT("The following paragraph is right-aligned with 1.5"
                    "line spacing:"));
    r.Newline();

    r.BeginAlignment(wxTEXT_ALIGNMENT_RIGHT);
    r.BeginLineSpacing(wxTEXT_ATTR_LINE_SPACING_HALF);
    r.WriteText(wxT("It was in January, the most down-trodden month of an"
      "Edinburgh winter. An attractive woman came into the cafe, which is"
      "nothing remarkable."));
    r.Newline();
    r.EndLineSpacing();
    r.EndAlignment();

    wxArrayInt tabs;
    tabs.Add(400);
    tabs.Add(600);
    tabs.Add(800);
    tabs.Add(1000);
    wxRichTextAttr attr;
    attr.SetFlags(wxTEXT_ATTR_TABS);
    attr.SetTabs(tabs);
    r.SetDefaultStyle(attr);

    r.WriteText(wxT("This line contains tabs:\tFirst tab\tSecond tab\tThird tab"));
    r.Newline();

    r.WriteText(wxT("Other notable features of wxRichTextCtrl include:"));
    r.Newline();

    r.BeginSymbolBullet(wxT('*'), 100, 60);
    r.WriteText(wxT("Compatibility with wxTextCtrl API"));
    r.Newline();
    r.EndSymbolBullet();

    r.BeginSymbolBullet(wxT('*'), 100, 60);
    r.WriteText(wxT("Easy stack-based BeginXXX()...EndXXX() style setting in"
                    "addition to SetStyle()"));
    r.Newline();
    r.EndSymbolBullet();

    r.BeginSymbolBullet(wxT('*'), 100, 60);
    r.WriteText(wxT("XML loading and saving"));
    r.Newline();
    r.EndSymbolBullet();

    r.BeginSymbolBullet(wxT('*'), 100, 60);
    r.WriteText(wxT("Undo/Redo, with batching option and Undo suppressing"));
    r.Newline();
    r.EndSymbolBullet();

    r.BeginSymbolBullet(wxT('*'), 100, 60);
    r.WriteText(wxT("Clipboard copy and paste"));
    r.Newline();
    r.EndSymbolBullet();

    r.BeginSymbolBullet(wxT('*'), 100, 60);
    r.WriteText(wxT("wxRichTextStyleSheet with named character and paragraph"
                    "styles, and control for applying named styles"));
    r.Newline();
    r.EndSymbolBullet();

    r.BeginSymbolBullet(wxT('*'), 100, 60);
    r.WriteText(wxT("A design that can easily be extended to other content"
      "types, ultimately with text boxes, tables, controls, and so on"));
    r.Newline();
    r.EndSymbolBullet();

    // Make a style suitable for showing a URL
    wxRichTextAttr urlStyle;
    urlStyle.SetTextColour(*wxBLUE);
    urlStyle.SetFontUnderlined(true);

    r.WriteText(wxT("wxRichTextCtrl can also display URLs, such as this one: "));
    r.BeginStyle(urlStyle);
    r.BeginURL(wxT("http://www.wxwidgets.org"));
    r.WriteText(wxT("The wxWidgets Web Site"));
    r.EndURL();
    r.EndStyle();
    r.WriteText(wxT(". Click on the URL to generate an event."));

    r.Newline();

    r.WriteText(wxT("Note: this sample content was generated programmatically"
      "from within the MyFrame constructor in the demo. The images were loaded"
      "from inline XPMs. Enjoy wxRichTextCtrl!\n"));

    r.EndParagraphSpacing();

#if 1
{
  // Add a text box

  r.Newline();

  wxRichTextAttr attr;
  attr.GetTextBoxAttr().GetMargins().GetLeft().SetValue(20, wxTEXT_ATTR_UNITS_PIXELS);
  attr.GetTextBoxAttr().GetMargins().GetTop().SetValue(20, wxTEXT_ATTR_UNITS_PIXELS);
  attr.GetTextBoxAttr().GetMargins().GetRight().SetValue(20, wxTEXT_ATTR_UNITS_PIXELS);
  attr.GetTextBoxAttr().GetMargins().GetBottom().SetValue(20, wxTEXT_ATTR_UNITS_PIXELS);

  attr.GetTextBoxAttr().GetBorder().SetColour(*wxBLACK);
  attr.GetTextBoxAttr().GetBorder().SetWidth(1, wxTEXT_ATTR_UNITS_PIXELS);
  attr.GetTextBoxAttr().GetBorder().SetStyle(wxTEXT_BOX_ATTR_BORDER_SOLID);

  wxRichTextBox* textBox = r.WriteTextBox(attr);
  r.SetFocusObject(textBox);

  r.WriteText(wxT("This is a text box. Just testing! Once more unto the"
                  "breach, dear friends, once more..."));

  r.SetFocusObject(NULL); // Set the focus back to the main buffer
  r.SetInsertionPointEnd();
}
#endif

#if 1
{
  // Add a table

  r.Newline();

  wxRichTextAttr attr;
  attr.GetTextBoxAttr().GetMargins().GetLeft().SetValue(5, wxTEXT_ATTR_UNITS_PIXELS);
  attr.GetTextBoxAttr().GetMargins().GetTop().SetValue(5, wxTEXT_ATTR_UNITS_PIXELS);
  attr.GetTextBoxAttr().GetMargins().GetRight().SetValue(5, wxTEXT_ATTR_UNITS_PIXELS);
  attr.GetTextBoxAttr().GetMargins().GetBottom().SetValue(5, wxTEXT_ATTR_UNITS_PIXELS);
  attr.GetTextBoxAttr().GetPadding() = attr.GetTextBoxAttr().GetMargins();

  attr.GetTextBoxAttr().GetBorder().SetColour(*wxBLACK);
  attr.GetTextBoxAttr().GetBorder().SetWidth(1, wxTEXT_ATTR_UNITS_PIXELS);
  attr.GetTextBoxAttr().GetBorder().SetStyle(wxTEXT_BOX_ATTR_BORDER_SOLID);

  wxRichTextAttr cellAttr = attr;
  cellAttr.GetTextBoxAttr().GetWidth().SetValue(200, wxTEXT_ATTR_UNITS_PIXELS);
  cellAttr.GetTextBoxAttr().GetHeight().SetValue(150, wxTEXT_ATTR_UNITS_PIXELS);

  wxRichTextTable* table = r.WriteTable(6, 4, attr, cellAttr);

  int i, j;
  for (j = 0; j < table->GetRowCount(); j++)
  {
    for (i = 0; i < table->GetColumnCount(); i++)
    {
      wxString msg = wxString::Format(wxT("This is cell %d, %d"), (j+1), (i+1));
      r.SetFocusObject(table->GetCell(j, i));
      r.WriteText(msg);
    }
  }

  // Demonstrate colspan and rowspan
  wxRichTextCell* cell = table->GetCell(1, 0);
  cell->SetColSpan(2);
  r.SetFocusObject(cell);
  cell->Clear();
  r.WriteText("This cell spans 2 columns");

  cell = table->GetCell(1, 3);
  cell->SetRowSpan(2);
  r.SetFocusObject(cell);
  cell->Clear();
  r.WriteText("This cell spans 2 rows");

  cell = table->GetCell(2, 1);
  cell->SetColSpan(2);
  cell->SetRowSpan(3);
  r.SetFocusObject(cell);
  cell->Clear();
  r.WriteText("This cell spans 2 columns and 3 rows");

  r.SetFocusObject(NULL); // Set the focus back to the main buffer
  r.SetInsertionPointEnd();
}
#endif

    r.Newline(); r.Newline();

    wxRichTextProperties properties;
    r.WriteText(wxT("This is a rectangle field: "));
    r.WriteField(wxT("rectangle"), properties);
    r.WriteText(wxT(" and a begin section field: "));
    r.WriteField(wxT("begin-section"), properties);
    r.WriteText(wxT("This is text between the two tags."));
    r.WriteField(wxT("end-section"), properties);
    r.WriteText(wxT(" Now a bitmap. "));
    r.WriteField(wxT("bitmap"), properties);
    r.WriteText(wxT(" Before we go, here's a composite field: ***"));
    wxRichTextField* field = r.WriteField(wxT("composite"), properties);

    // Creates the composite value (sort of a text box)
    field->UpdateField(& r.GetBuffer());
    r.WriteText(wxT("*** End of composite field."));

    r.Newline();
    r.EndSuppressUndo();

    // Add some locked content first - needs Undo to be enabled
    {
        r.BeginLock();
        r.WriteText(wxString(wxT("This is a locked object.")));
        r.EndLock();

        r.WriteText(wxString(wxT(" This is unlocked text. ")));

        r.BeginLock();
        r.WriteText(wxString(wxT("More locked content.")));
        r.EndLock();
        r.Newline();

        // Flush the Undo buffer
        r.GetCommandProcessor()->ClearCommands();
    }

    r.Thaw();
}

////////////////////////////////////////////////////////////////////////////////
//                   event handlers
////////////////////////////////////////////////////////////////////////////////

void frame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void frame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
  wxString msg;
  msg.Printf( wxT("This is a EveRest - editor for reStructuredText content"));
  wxMessageBox(msg, wxT("About EveRest"), wxOK | wxICON_INFORMATION, this);
}

// Forward command events to the current rich text control, if any
bool frame::ProcessEvent(wxEvent& event)
{
    if (event.IsCommandEvent() && !event.IsKindOf(CLASSINFO(wxChildFocusEvent)))
    {
        // Problem: we can get infinite recursion because the events
        // climb back up to this frame, and repeat.
        // Assume that command events don't cause another command event
        // to be called, so we can rely on inCommand not being overwritten

        static int s_eventType = 0;
        static wxWindowID s_id = 0;

        if (s_id != event.GetId() && s_eventType != event.GetEventType())
        {
            s_eventType = event.GetEventType();
            s_id = event.GetId();

            wxWindow* focusWin = wxFindFocusDescendant(this);
            if (focusWin && focusWin->GetEventHandler()->ProcessEvent(event))
            {
                //s_command = NULL;
                s_eventType = 0;
                s_id = 0;
                return true;
            }

            s_eventType = 0;
            s_id = 0;
        }
        else
        {
            return false;
        }
    }

    return wxFrame::ProcessEvent(event);
}

void frame::OnOpen(wxCommandEvent& WXUNUSED(event))
{
    wxString path;
    wxString filename;
    wxArrayInt fileTypes;

    wxString filter = wxRichTextBuffer::GetExtWildcard(false, false, & fileTypes);
    if (!filter.empty())
        filter += wxT("|");
    filter += wxT("All files (*.*)|*.*");

    wxFileDialog dialog(this,
        _("Choose a filename"),
        path,
        filename,
        filter,
        wxFD_OPEN);

    if (dialog.ShowModal() == wxID_OK)
    {
        wxString path = dialog.GetPath();

        if (!path.empty())
        {
            int filterIndex = dialog.GetFilterIndex();
            int fileType = (filterIndex < (int) fileTypes.GetCount())
                           ? fileTypes[filterIndex]
                           : wxRICHTEXT_TYPE_TEXT;
            TextCtrl->LoadFile(path, fileType);
        }
    }
}

void frame::OnSave(wxCommandEvent& event)
{
  if (TextCtrl->GetFilename().empty())
  {
    OnSaveAs(event);
    return;
  }
  TextCtrl->SaveFile();
}

//##
void frame::OnSaveAs(wxCommandEvent& WXUNUSED(event))
{
  wxString filter = wxRichTextBuffer::GetExtWildcard(false, true);
  wxString path;
  wxString filename;

  wxFileDialog dialog(this, _("Choose a filename"), path, filename,
    filter, wxFD_SAVE);

  if (dialog.ShowModal() == wxID_OK)
  {
      wxString path = dialog.GetPath();

      if (!path.empty())
      {
          //wxBusyCursor busy;
          //wxStopWatch stopwatch;

          TextCtrl->SaveFile(path);

          //long t = stopwatch.Time();
          //wxLogDebug(wxT("Saving took %ldms"), t);
          //wxMessageBox(wxString::Format(wxT("Saving took %ldms"), t));
      }
  }
}

void frame::OnBold(wxCommandEvent& WXUNUSED(event))
{
    TextCtrl->ApplyBoldToSelection();
}

void frame::OnItalic(wxCommandEvent& WXUNUSED(event))
{
    TextCtrl->ApplyItalicToSelection();
}

void frame::OnUnderline(wxCommandEvent& WXUNUSED(event))
{
    TextCtrl->ApplyUnderlineToSelection();
}

void frame::OnStrikethrough(wxCommandEvent& WXUNUSED(event))
{
    TextCtrl->ApplyTextEffectToSelection(wxTEXT_ATTR_EFFECT_STRIKETHROUGH);
}

void frame::OnSuperscript(wxCommandEvent& WXUNUSED(event))
{
    TextCtrl->ApplyTextEffectToSelection(wxTEXT_ATTR_EFFECT_SUPERSCRIPT);
}

void frame::OnSubscript(wxCommandEvent& WXUNUSED(event))
{
    TextCtrl->ApplyTextEffectToSelection(wxTEXT_ATTR_EFFECT_SUBSCRIPT);
}


void frame::OnUpdateBold(wxUpdateUIEvent& event)
{
    event.Check(TextCtrl->IsSelectionBold());
}

void frame::OnUpdateItalic(wxUpdateUIEvent& event)
{
    event.Check(TextCtrl->IsSelectionItalics());
}

void frame::OnUpdateUnderline(wxUpdateUIEvent& event)
{
    event.Check(TextCtrl->IsSelectionUnderlined());
}

void frame::OnUpdateStrikethrough(wxUpdateUIEvent& event)
{
    event.Check(TextCtrl->DoesSelectionHaveTextEffectFlag(wxTEXT_ATTR_EFFECT_STRIKETHROUGH));
}

void frame::OnUpdateSuperscript(wxUpdateUIEvent& event)
{
    event.Check(TextCtrl->DoesSelectionHaveTextEffectFlag(wxTEXT_ATTR_EFFECT_SUPERSCRIPT));
}

void frame::OnUpdateSubscript(wxUpdateUIEvent& event)
{
    event.Check(TextCtrl->DoesSelectionHaveTextEffectFlag(wxTEXT_ATTR_EFFECT_SUBSCRIPT));
}

void frame::OnAlignLeft(wxCommandEvent& WXUNUSED(event))
{
    TextCtrl->ApplyAlignmentToSelection(wxTEXT_ALIGNMENT_LEFT);
}

void frame::OnAlignCentre(wxCommandEvent& WXUNUSED(event))
{
    TextCtrl->ApplyAlignmentToSelection(wxTEXT_ALIGNMENT_CENTRE);
}

void frame::OnAlignRight(wxCommandEvent& WXUNUSED(event))
{
    TextCtrl->ApplyAlignmentToSelection(wxTEXT_ALIGNMENT_RIGHT);
}

void frame::OnUpdateAlignLeft(wxUpdateUIEvent& event)
{
    event.Check(TextCtrl->IsSelectionAligned(wxTEXT_ALIGNMENT_LEFT));
}

void frame::OnUpdateAlignCentre(wxUpdateUIEvent& event)
{
    event.Check(TextCtrl->IsSelectionAligned(wxTEXT_ALIGNMENT_CENTRE));
}

void frame::OnUpdateAlignRight(wxUpdateUIEvent& event)
{
    event.Check(TextCtrl->IsSelectionAligned(wxTEXT_ALIGNMENT_RIGHT));
}

void frame::OnFont(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextRange range;
    if (TextCtrl->HasSelection())
        range = TextCtrl->GetSelectionRange();
    else
        range = wxRichTextRange(0, TextCtrl->GetLastPosition()+1);

    int pages = wxRICHTEXT_FORMAT_FONT;

    wxRichTextFormattingDialog formatDlg(pages, this);
    formatDlg.SetOptions(wxRichTextFormattingDialog::Option_AllowPixelFontSize);
    formatDlg.GetStyle(TextCtrl, range);

    if (formatDlg.ShowModal() == wxID_OK)
    {
        formatDlg.ApplyStyle(TextCtrl, range, wxRICHTEXT_SETSTYLE_WITH_UNDO|wxRICHTEXT_SETSTYLE_OPTIMIZE|wxRICHTEXT_SETSTYLE_CHARACTERS_ONLY);
    }
}

void frame::OnImage(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextRange range;
    wxASSERT(TextCtrl->HasSelection());

    range = TextCtrl->GetSelectionRange();
    wxASSERT(range.ToInternal().GetLength() == 1);

    wxRichTextImage* image = wxDynamicCast(TextCtrl->GetFocusObject()->GetLeafObjectAtPosition(range.GetStart()), wxRichTextImage);
    if (image)
    {
        wxRichTextObjectPropertiesDialog imageDlg(image, this);

        if (imageDlg.ShowModal() == wxID_OK)
        {
            imageDlg.ApplyStyle(TextCtrl);
        }
    }
}

void frame::OnParagraph(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextRange range;
    if (TextCtrl->HasSelection())
        range = TextCtrl->GetSelectionRange();
    else
        range = wxRichTextRange(0, TextCtrl->GetLastPosition()+1);

    int pages = wxRICHTEXT_FORMAT_INDENTS_SPACING|wxRICHTEXT_FORMAT_TABS|wxRICHTEXT_FORMAT_BULLETS;

    wxRichTextFormattingDialog formatDlg(pages, this);
    formatDlg.GetStyle(TextCtrl, range);

    if (formatDlg.ShowModal() == wxID_OK)
    {
        formatDlg.ApplyStyle(TextCtrl, range);
    }
}

void frame::OnFormat(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextRange range;
    if (TextCtrl->HasSelection())
        range = TextCtrl->GetSelectionRange();
    else
        range = wxRichTextRange(0, TextCtrl->GetLastPosition()+1);

    int pages = wxRICHTEXT_FORMAT_FONT|wxRICHTEXT_FORMAT_INDENTS_SPACING|wxRICHTEXT_FORMAT_TABS|wxRICHTEXT_FORMAT_BULLETS;

    wxRichTextFormattingDialog formatDlg(pages, this);
    formatDlg.GetStyle(TextCtrl, range);

    if (formatDlg.ShowModal() == wxID_OK)
    {
        formatDlg.ApplyStyle(TextCtrl, range);
    }
}

void frame::OnUpdateFormat(wxUpdateUIEvent& event)
{
    event.Enable(TextCtrl->HasSelection());
}

void frame::OnUpdateImage(wxUpdateUIEvent& event)
{
    wxRichTextRange range;
    wxRichTextObject *obj;

    range = TextCtrl->GetSelectionRange();
    if (range.ToInternal().GetLength() == 1)
    {
        obj = TextCtrl->GetFocusObject()->GetLeafObjectAtPosition(range.GetStart());
        if (obj && obj->IsKindOf(CLASSINFO(wxRichTextImage)))
        {
            event.Enable(true);
            return;
        }
    }

    event.Enable(false);
}

void frame::OnIndentMore(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextAttr attr;
    attr.SetFlags(wxTEXT_ATTR_LEFT_INDENT);

    if (TextCtrl->GetStyle(TextCtrl->GetInsertionPoint(), attr))
    {
        wxRichTextRange range(TextCtrl->GetInsertionPoint(), TextCtrl->GetInsertionPoint());
        if (TextCtrl->HasSelection())
            range = TextCtrl->GetSelectionRange();

        attr.SetLeftIndent(attr.GetLeftIndent() + 100);

        attr.SetFlags(wxTEXT_ATTR_LEFT_INDENT);
        TextCtrl->SetStyle(range, attr);
    }
}

void frame::OnIndentLess(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextAttr attr;
    attr.SetFlags(wxTEXT_ATTR_LEFT_INDENT);

    if (TextCtrl->GetStyle(TextCtrl->GetInsertionPoint(), attr))
    {
        wxRichTextRange range(TextCtrl->GetInsertionPoint(), TextCtrl->GetInsertionPoint());
        if (TextCtrl->HasSelection())
            range = TextCtrl->GetSelectionRange();

        if (attr.GetLeftIndent() > 0)
        {
            attr.SetLeftIndent(wxMax(0, attr.GetLeftIndent() - 100));

            TextCtrl->SetStyle(range, attr);
        }
    }
}

void frame::OnLineSpacingHalf(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextAttr attr;
    attr.SetFlags(wxTEXT_ATTR_LINE_SPACING);

    if (TextCtrl->GetStyle(TextCtrl->GetInsertionPoint(), attr))
    {
        wxRichTextRange range(TextCtrl->GetInsertionPoint(), TextCtrl->GetInsertionPoint());
        if (TextCtrl->HasSelection())
            range = TextCtrl->GetSelectionRange();

        attr.SetFlags(wxTEXT_ATTR_LINE_SPACING);
        attr.SetLineSpacing(15);

        TextCtrl->SetStyle(range, attr);
    }
}

void frame::OnLineSpacingDouble(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextAttr attr;
    attr.SetFlags(wxTEXT_ATTR_LINE_SPACING);

    if (TextCtrl->GetStyle(TextCtrl->GetInsertionPoint(), attr))
    {
        wxRichTextRange range(TextCtrl->GetInsertionPoint(), TextCtrl->GetInsertionPoint());
        if (TextCtrl->HasSelection())
            range = TextCtrl->GetSelectionRange();

        attr.SetFlags(wxTEXT_ATTR_LINE_SPACING);
        attr.SetLineSpacing(20);

        TextCtrl->SetStyle(range, attr);
    }
}

void frame::OnLineSpacingSingle(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextAttr attr;
    attr.SetFlags(wxTEXT_ATTR_LINE_SPACING);

    if (TextCtrl->GetStyle(TextCtrl->GetInsertionPoint(), attr))
    {
        wxRichTextRange range(TextCtrl->GetInsertionPoint(), TextCtrl->GetInsertionPoint());
        if (TextCtrl->HasSelection())
            range = TextCtrl->GetSelectionRange();

        attr.SetFlags(wxTEXT_ATTR_LINE_SPACING);
        attr.SetLineSpacing(0); // Can also use 10

        TextCtrl->SetStyle(range, attr);
    }
}

void frame::OnParagraphSpacingMore(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextAttr attr;
    attr.SetFlags(wxTEXT_ATTR_PARA_SPACING_AFTER);

    if (TextCtrl->GetStyle(TextCtrl->GetInsertionPoint(), attr))
    {
        wxRichTextRange range(TextCtrl->GetInsertionPoint(), TextCtrl->GetInsertionPoint());
        if (TextCtrl->HasSelection())
            range = TextCtrl->GetSelectionRange();

        attr.SetParagraphSpacingAfter(attr.GetParagraphSpacingAfter() + 20);

        attr.SetFlags(wxTEXT_ATTR_PARA_SPACING_AFTER);
        TextCtrl->SetStyle(range, attr);
    }
}

void frame::OnParagraphSpacingLess(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextAttr attr;
    attr.SetFlags(wxTEXT_ATTR_PARA_SPACING_AFTER);

    if (TextCtrl->GetStyle(TextCtrl->GetInsertionPoint(), attr))
    {
        wxRichTextRange range(TextCtrl->GetInsertionPoint(), TextCtrl->GetInsertionPoint());
        if (TextCtrl->HasSelection())
            range = TextCtrl->GetSelectionRange();

        if (attr.GetParagraphSpacingAfter() >= 20)
        {
            attr.SetParagraphSpacingAfter(attr.GetParagraphSpacingAfter() - 20);

            attr.SetFlags(wxTEXT_ATTR_PARA_SPACING_AFTER);
            TextCtrl->SetStyle(range, attr);
        }
    }
}

void frame::OnReload(wxCommandEvent& WXUNUSED(event))
{
    TextCtrl->Clear();
    WriteInitialText();
}

void frame::OnViewHTML(wxCommandEvent& WXUNUSED(event))
{
    wxDialog dialog(this, wxID_ANY, _("HTML"), wxDefaultPosition,
                    wxSize(500, 400), wxDEFAULT_DIALOG_STYLE);

    wxBoxSizer* boxSizer = new wxBoxSizer(wxVERTICAL);
    dialog.SetSizer(boxSizer);

    wxHtmlWindow* Win = new wxHtmlWindow(& dialog, wxID_ANY, wxDefaultPosition,
                                         wxSize(500, 400), wxSUNKEN_BORDER);
    boxSizer->Add(Win, 1, wxALL, 5);

    wxButton* cancelButton = new wxButton(& dialog, wxID_CANCEL, wxT("&Close"));
    boxSizer->Add(cancelButton, 0, wxALL|wxCENTRE, 5);

    wxString text;
    wxStringOutputStream strStream(& text);

    wxRichTextHTMLHandler htmlHandler;
    htmlHandler.SetFlags(wxRICHTEXT_HANDLER_SAVE_IMAGES_TO_MEMORY);

    wxArrayInt fontSizeMapping;
    fontSizeMapping.Add(7);
    fontSizeMapping.Add(9);
    fontSizeMapping.Add(11);
    fontSizeMapping.Add(12);
    fontSizeMapping.Add(14);
    fontSizeMapping.Add(22);
    fontSizeMapping.Add(100);

    htmlHandler.SetFontSizeMapping(fontSizeMapping);

    if (htmlHandler.SaveFile(& TextCtrl->GetBuffer(), strStream))
    {
        Win->SetPage(text);
    }

    boxSizer->Fit(& dialog);

    dialog.ShowModal();

    // Now delete the temporary in-memory images
    htmlHandler.DeleteTemporaryImages();
}

// You can change the style sheets and have the changes reflected in the control
// content without wiping out character formatting.
void frame::OnSwitchStyleSheets(wxCommandEvent& WXUNUSED(event))
{
    static wxRichTextStyleSheet* gs_AlternateStyleSheet = NULL;

    wxRichTextStyleListCtrl *styleList = (wxRichTextStyleListCtrl*) FindWindow(ID_RICHTEXT_STYLE_LIST);
    wxRichTextStyleComboCtrl* styleCombo = (wxRichTextStyleComboCtrl*) FindWindow(ID_RICHTEXT_STYLE_COMBO);

    wxRichTextStyleSheet* sheet = TextCtrl->GetStyleSheet();

    // One-time creation of an alternate style sheet
    if (!gs_AlternateStyleSheet)
    {
        gs_AlternateStyleSheet = new wxRichTextStyleSheet(*sheet);

        // Make some modifications
        for (int i = 0; i < (int) gs_AlternateStyleSheet->GetParagraphStyleCount(); i++)
        {
            wxRichTextParagraphStyleDefinition* def = gs_AlternateStyleSheet->GetParagraphStyle(i);

            if (def->GetStyle().HasTextColour())
                def->GetStyle().SetTextColour(*wxBLUE);

            if (def->GetStyle().HasAlignment())
            {
                if (def->GetStyle().GetAlignment() == wxTEXT_ALIGNMENT_CENTRE)
                    def->GetStyle().SetAlignment(wxTEXT_ALIGNMENT_RIGHT);
                else if (def->GetStyle().GetAlignment() == wxTEXT_ALIGNMENT_LEFT)
                    def->GetStyle().SetAlignment(wxTEXT_ALIGNMENT_CENTRE);
            }
            if (def->GetStyle().HasLeftIndent())
            {
                def->GetStyle().SetLeftIndent(def->GetStyle().GetLeftIndent() * 2);
            }
        }
    }

    // Switch sheets
    wxRichTextStyleSheet* tmp = gs_AlternateStyleSheet;
    gs_AlternateStyleSheet = sheet;
    sheet = tmp;

    TextCtrl->SetStyleSheet(sheet);
    TextCtrl->ApplyStyleSheet(sheet); // Makes the control reflect the new style definitions

    styleList->SetStyleSheet(sheet);
    styleList->UpdateStyles();

    styleCombo->SetStyleSheet(sheet);
    styleCombo->UpdateStyles();
}

void frame::OnManageStyles(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextStyleSheet* sheet = TextCtrl->GetStyleSheet();

    int flags = wxRICHTEXT_ORGANISER_CREATE_STYLES|wxRICHTEXT_ORGANISER_EDIT_STYLES;

    wxRichTextStyleOrganiserDialog dlg(flags, sheet, NULL, this, wxID_ANY, _("Style Manager"));
    dlg.ShowModal();
}

void frame::OnInsertSymbol(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextAttr attr;
    attr.SetFlags(wxTEXT_ATTR_FONT);
    TextCtrl->GetStyle(TextCtrl->GetInsertionPoint(), attr);

    wxString currentFontName;
    if (attr.HasFont() && attr.GetFont().IsOk())
        currentFontName = attr.GetFont().GetFaceName();

    // Don't set the initial font in the dialog (so the user is choosing
    // 'normal text', i.e. the current font) but do tell the dialog
    // what 'normal text' is.

    wxSymbolPickerDialog dlg(wxT("*"), wxEmptyString, currentFontName, this);

    if (dlg.ShowModal() == wxID_OK)
    {
        if (dlg.HasSelection())
        {
            long insertionPoint = TextCtrl->GetInsertionPoint();

            TextCtrl->WriteText(dlg.GetSymbol());

            if (!dlg.UseNormalFont())
            {
                wxFont font(attr.GetFont());
                font.SetFaceName(dlg.GetFontName());
                attr.SetFont(font);
                TextCtrl->SetStyle(insertionPoint, insertionPoint+1, attr);
            }
        }
    }
}

void frame::OnNumberList(wxCommandEvent& WXUNUSED(event))
{
    if (TextCtrl->HasSelection())
    {
        wxRichTextRange range = TextCtrl->GetSelectionRange();
        TextCtrl->SetListStyle(range, wxT("Numbered List 1"), wxRICHTEXT_SETSTYLE_WITH_UNDO|wxRICHTEXT_SETSTYLE_RENUMBER);
    }
}

void frame::OnBulletsAndNumbering(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextStyleSheet* sheet = TextCtrl->GetStyleSheet();

    int flags = wxRICHTEXT_ORGANISER_BROWSE_NUMBERING;

    wxRichTextStyleOrganiserDialog dlg(flags, sheet, TextCtrl, this, wxID_ANY, _("Bullets and Numbering"));
    if (dlg.ShowModal() == wxID_OK)
    {
        if (dlg.GetSelectedStyleDefinition())
            dlg.ApplyStyle();
    }
}

void frame::OnItemizeList(wxCommandEvent& WXUNUSED(event))
{
    if (TextCtrl->HasSelection())
    {
        wxRichTextRange range = TextCtrl->GetSelectionRange();
        TextCtrl->SetListStyle(range, wxT("Bullet List 1"));
    }
}

void frame::OnRenumberList(wxCommandEvent& WXUNUSED(event))
{
    if (TextCtrl->HasSelection())
    {
        wxRichTextRange range = TextCtrl->GetSelectionRange();
        TextCtrl->NumberList(range, NULL, wxRICHTEXT_SETSTYLE_WITH_UNDO|wxRICHTEXT_SETSTYLE_RENUMBER);
    }
}

void frame::OnPromoteList(wxCommandEvent& WXUNUSED(event))
{
    if (TextCtrl->HasSelection())
    {
        wxRichTextRange range = TextCtrl->GetSelectionRange();
        TextCtrl->PromoteList(1, range, NULL);
    }
}

void frame::OnDemoteList(wxCommandEvent& WXUNUSED(event))
{
    if (TextCtrl->HasSelection())
    {
        wxRichTextRange range = TextCtrl->GetSelectionRange();
        TextCtrl->PromoteList(-1, range, NULL);
    }
}

void frame::OnClearList(wxCommandEvent& WXUNUSED(event))
{
    if (TextCtrl->HasSelection())
    {
        wxRichTextRange range = TextCtrl->GetSelectionRange();
        TextCtrl->ClearListStyle(range);
    }
}

void frame::OnTableAddColumn(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextTable* table = wxDynamicCast(TextCtrl->FindTable(), wxRichTextTable);
    if (table)
    {
        wxRichTextAttr cellAttr = table->GetCell(0, 0)->GetAttributes();
        table->AddColumns(table->GetColumnCount(), 1, cellAttr);
    }
}

void frame::OnTableAddRow(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextTable* table = wxDynamicCast(TextCtrl->FindTable(), wxRichTextTable);
    if (table)
    {
        wxRichTextAttr cellAttr = table->GetCell(0, 0)->GetAttributes();
        table->AddRows(table->GetRowCount(), 1, cellAttr);
    }
}

void frame::OnTableDeleteColumn(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextTable* table = wxDynamicCast(TextCtrl->FindTable(), wxRichTextTable);
    if (table)
    {
        int col = table->GetFocusedCell().GetCol();
        if (col == -1)
        {
            col = table->GetColumnCount() - 1;
        }

        table->DeleteColumns(col, 1);
    }
}

void frame::OnTableDeleteRow(wxCommandEvent& WXUNUSED(event))
{
    wxRichTextTable* table = wxDynamicCast(TextCtrl->FindTable(), wxRichTextTable);
    if (table)
    {
        int row = table->GetFocusedCell().GetRow();
        if (row == -1)
        {
            row = table->GetRowCount() - 1;
        }

        table->DeleteRows(row, 1);
    }
}

void frame::OnTableFocusedUpdateUI(wxUpdateUIEvent& event)
{
    event.Enable(TextCtrl->FindTable() != NULL);
}

void frame::OnTableHasCellsUpdateUI(wxUpdateUIEvent& event)
{
    bool enable(false);
    wxRichTextTable* table = wxDynamicCast(TextCtrl->FindTable(), wxRichTextTable);
    if (table)
    {
        if (event.GetId() == ID_TABLE_DELETE_COLUMN)
        {
            enable = table->GetColumnCount() > 1;
        }
        else
        {
            enable = table->GetRowCount() > 1;
        }
    }

    event.Enable(enable);
}

void frame::OnInsertURL(wxCommandEvent& WXUNUSED(event))
{
    wxString url = wxGetTextFromUser(_("URL:"), _("Insert URL"));
    if (!url.IsEmpty())
    {
        // Make a style suitable for showing a URL
        wxRichTextAttr urlStyle;
        urlStyle.SetTextColour(*wxBLUE);
        urlStyle.SetFontUnderlined(true);

        TextCtrl->BeginStyle(urlStyle);
        TextCtrl->BeginURL(url);
        TextCtrl->WriteText(url);
        TextCtrl->EndURL();
        TextCtrl->EndStyle();
    }
}

void frame::OnInsertImage(wxCommandEvent& WXUNUSED(event))
{
    wxFileDialog dialog(this, _("Choose an image"), "", "", "BMP and GIF files (*.bmp;*.gif)|*.bmp;*.gif|PNG files (*.png)|*.png|JPEG files (*.jpg;*.jpeg)|*.jpg;*.jpeg");
    if (dialog.ShowModal() == wxID_OK)
    {
        wxString path = dialog.GetPath();
        wxImage image;
        if (image.LoadFile(path) && image.GetType() != wxBITMAP_TYPE_INVALID)
            TextCtrl->WriteImage(path, image.GetType());
    }
}

void frame::OnURL(wxTextUrlEvent& event)
{
    wxMessageBox(event.GetString());
}

// Veto style sheet replace events when loading from XML, since we want
// to keep the original style sheet.
void frame::OnStyleSheetReplacing(wxRichTextEvent& event)
{
    event.Veto();
}

#if wxUSE_PRINTING_ARCHITECTURE
void frame::OnPrint(wxCommandEvent& WXUNUSED(event))
{
    wxGetApp().GetPrinting()->PrintBuffer(TextCtrl->GetBuffer());
}

void frame::OnPreview(wxCommandEvent& WXUNUSED(event))
{
    wxGetApp().GetPrinting()->PreviewBuffer(TextCtrl->GetBuffer());
}
#endif

void frame::OnPageSetup(wxCommandEvent& WXUNUSED(event))
{
    wxDialog dialog(this, wxID_ANY, wxT("Testing"), wxPoint(10, 10), wxSize(400, 300), wxDEFAULT_DIALOG_STYLE);

    wxNotebook* nb = new wxNotebook(& dialog, wxID_ANY, wxPoint(5, 5), wxSize(300, 250));
    wxPanel* panel = new wxPanel(nb, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    wxPanel* panel2 = new wxPanel(nb, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    new wxRichTextCtrl(panel, wxID_ANY, wxEmptyString, wxPoint(5, 5), wxSize(200, 150), wxVSCROLL|wxTE_READONLY);
    nb->AddPage(panel, wxT("Page 1"));

    new wxRichTextCtrl(panel2, wxID_ANY, wxEmptyString, wxPoint(5, 5), wxSize(200, 150), wxVSCROLL|wxTE_READONLY);
    nb->AddPage(panel2, wxT("Page 2"));

    new wxButton(& dialog, wxID_OK, wxT("OK"), wxPoint(5, 180));

    dialog.ShowModal();

//    wxGetApp().GetPrinting()->PageSetup();
}

void frame::OnSetFontScale(wxCommandEvent& WXUNUSED(event))
{
    wxString value = wxString::Format(wxT("%g"), TextCtrl->GetFontScale());
    wxString text = wxGetTextFromUser(wxT("Enter a text scale factor:"), wxT("Text Scale Factor"), value, wxGetTopLevelParent(this));
    if (!text.IsEmpty() && value != text)
    {
        double scale = 1.0;
        wxSscanf(text, wxT("%lf"), & scale);
        TextCtrl->SetFontScale(scale, true);
    }
}

void frame::OnSetDimensionScale(wxCommandEvent& WXUNUSED(event))
{
    wxString value = wxString::Format(wxT("%g"), TextCtrl->GetDimensionScale());
    wxString text = wxGetTextFromUser(wxT("Enter a dimension scale factor:"), wxT("Dimension Scale Factor"), value, wxGetTopLevelParent(this));
    if (!text.IsEmpty() && value != text)
    {
        double scale = 1.0;
        wxSscanf(text, wxT("%lf"), & scale);
        TextCtrl->SetDimensionScale(scale, true);
    }
}

// ----------------------------------------------------------------------------
// event tables and other macros for wxWidgets
// ----------------------------------------------------------------------------

// the event tables connect the wxWidgets events with the functions (event
// handlers) which process them. It can be also done at run-time, but for the
// simple menu events like this the static method is much simpler.
wxBEGIN_EVENT_TABLE(frame, wxFrame)
    EVT_MENU(ID_Quit, frame::OnQuit)
    EVT_MENU(ID_About, frame::OnAbout)

    EVT_MENU(wxID_OPEN, frame::OnOpen)
    EVT_MENU(wxID_SAVE, frame::OnSave)
    EVT_MENU(wxID_SAVEAS, frame::OnSaveAs)

    EVT_MENU(ID_FORMAT_BOLD, frame::OnBold)
    EVT_MENU(ID_FORMAT_ITALIC, frame::OnItalic)
    EVT_MENU(ID_FORMAT_UNDERLINE, frame::OnUnderline)

    EVT_MENU(ID_FORMAT_STRIKETHROUGH, frame::OnStrikethrough)
    EVT_MENU(ID_FORMAT_SUPERSCRIPT, frame::OnSuperscript)
    EVT_MENU(ID_FORMAT_SUBSCRIPT, frame::OnSubscript)

    EVT_UPDATE_UI(ID_FORMAT_BOLD, frame::OnUpdateBold)
    EVT_UPDATE_UI(ID_FORMAT_ITALIC, frame::OnUpdateItalic)
    EVT_UPDATE_UI(ID_FORMAT_UNDERLINE, frame::OnUpdateUnderline)

    EVT_UPDATE_UI(ID_FORMAT_STRIKETHROUGH, frame::OnUpdateStrikethrough)
    EVT_UPDATE_UI(ID_FORMAT_SUPERSCRIPT, frame::OnUpdateSuperscript)
    EVT_UPDATE_UI(ID_FORMAT_SUBSCRIPT, frame::OnUpdateSubscript)

    EVT_MENU(ID_FORMAT_ALIGN_LEFT, frame::OnAlignLeft)
    EVT_MENU(ID_FORMAT_ALIGN_CENTRE, frame::OnAlignCentre)
    EVT_MENU(ID_FORMAT_ALIGN_RIGHT, frame::OnAlignRight)

    EVT_UPDATE_UI(ID_FORMAT_ALIGN_LEFT, frame::OnUpdateAlignLeft)
    EVT_UPDATE_UI(ID_FORMAT_ALIGN_CENTRE, frame::OnUpdateAlignCentre)
    EVT_UPDATE_UI(ID_FORMAT_ALIGN_RIGHT, frame::OnUpdateAlignRight)

    EVT_MENU(ID_FORMAT_FONT, frame::OnFont)
    EVT_MENU(ID_FORMAT_IMAGE, frame::OnImage)
    EVT_MENU(ID_FORMAT_PARAGRAPH, frame::OnParagraph)
    EVT_MENU(ID_FORMAT_CONTENT, frame::OnFormat)
    EVT_UPDATE_UI(ID_FORMAT_CONTENT, frame::OnUpdateFormat)
    EVT_UPDATE_UI(ID_FORMAT_FONT, frame::OnUpdateFormat)
    EVT_UPDATE_UI(ID_FORMAT_IMAGE, frame::OnUpdateImage)
    EVT_UPDATE_UI(ID_FORMAT_PARAGRAPH, frame::OnUpdateFormat)
    EVT_MENU(ID_FORMAT_INDENT_MORE, frame::OnIndentMore)
    EVT_MENU(ID_FORMAT_INDENT_LESS, frame::OnIndentLess)

    EVT_MENU(ID_FORMAT_LINE_SPACING_HALF, frame::OnLineSpacingHalf)
    EVT_MENU(ID_FORMAT_LINE_SPACING_SINGLE, frame::OnLineSpacingSingle)
    EVT_MENU(ID_FORMAT_LINE_SPACING_DOUBLE, frame::OnLineSpacingDouble)

    EVT_MENU(ID_FORMAT_PARAGRAPH_SPACING_MORE, frame::OnParagraphSpacingMore)
    EVT_MENU(ID_FORMAT_PARAGRAPH_SPACING_LESS, frame::OnParagraphSpacingLess)

    EVT_MENU(ID_RELOAD, frame::OnReload)

    EVT_MENU(ID_INSERT_SYMBOL, frame::OnInsertSymbol)
    EVT_MENU(ID_INSERT_URL, frame::OnInsertURL)
    EVT_MENU(ID_INSERT_IMAGE, frame::OnInsertImage)

    EVT_MENU(ID_FORMAT_NUMBER_LIST, frame::OnNumberList)
    EVT_MENU(ID_FORMAT_BULLETS_AND_NUMBERING, frame::OnBulletsAndNumbering)
    EVT_MENU(ID_FORMAT_ITEMIZE_LIST, frame::OnItemizeList)
    EVT_MENU(ID_FORMAT_RENUMBER_LIST, frame::OnRenumberList)
    EVT_MENU(ID_FORMAT_PROMOTE_LIST, frame::OnPromoteList)
    EVT_MENU(ID_FORMAT_DEMOTE_LIST, frame::OnDemoteList)
    EVT_MENU(ID_FORMAT_CLEAR_LIST, frame::OnClearList)

    EVT_MENU(ID_TABLE_ADD_COLUMN, frame::OnTableAddColumn)
    EVT_MENU(ID_TABLE_ADD_ROW, frame::OnTableAddRow)
    EVT_MENU(ID_TABLE_DELETE_COLUMN, frame::OnTableDeleteColumn)
    EVT_MENU(ID_TABLE_DELETE_ROW, frame::OnTableDeleteRow)
    EVT_UPDATE_UI_RANGE(ID_TABLE_ADD_COLUMN, ID_TABLE_ADD_ROW, frame::OnTableFocusedUpdateUI)
    EVT_UPDATE_UI_RANGE(ID_TABLE_DELETE_COLUMN, ID_TABLE_DELETE_ROW, frame::OnTableHasCellsUpdateUI)

    EVT_MENU(ID_VIEW_HTML, frame::OnViewHTML)
    EVT_MENU(ID_SWITCH_STYLE_SHEETS, frame::OnSwitchStyleSheets)
    EVT_MENU(ID_MANAGE_STYLES, frame::OnManageStyles)

#if wxUSE_PRINTING_ARCHITECTURE
    EVT_MENU(ID_PRINT, frame::OnPrint)
    EVT_MENU(ID_PREVIEW, frame::OnPreview)
#endif
    EVT_MENU(ID_PAGE_SETUP, frame::OnPageSetup)

    EVT_TEXT_URL(wxID_ANY, frame::OnURL)
    EVT_RICHTEXT_STYLESHEET_REPLACING(wxID_ANY, frame::OnStyleSheetReplacing)

    EVT_MENU(ID_SET_FONT_SCALE, frame::OnSetFontScale)
    EVT_MENU(ID_SET_DIMENSION_SCALE, frame::OnSetDimensionScale)
wxEND_EVENT_TABLE()

} //namespace ev
