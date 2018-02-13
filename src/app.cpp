#include "app.hpp"

namespace ev {

// 'Main program' equivalent: the program execution "starts" here
bool app::OnInit()
{
  if( !wxApp::OnInit() ) return false;

  #if wxUSE_HELP
    wxHelpProvider::Set(new wxSimpleHelpProvider);
  #endif

  m_styleSheet = new wxRichTextStyleSheet;

  #if wxUSE_PRINTING_ARCHITECTURE
    m_printing = new wxRichTextPrinting(wxT("Test Document"));
    m_printing->SetFooterText(wxT("@TITLE@"), wxRICHTEXT_PAGE_ALL, wxRICHTEXT_PAGE_CENTRE);
    m_printing->SetFooterText(wxT("Page @PAGENUM@"), wxRICHTEXT_PAGE_ALL, wxRICHTEXT_PAGE_RIGHT);
  #endif

  CreateStyles();

  text_ctrl::SetEnhancedDrawingHandler();

  // Add extra handlers (plain text is automatically added)
  wxRichTextBuffer::AddHandler(new wxRichTextXMLHandler);
  wxRichTextBuffer::AddHandler(new wxRichTextHTMLHandler);

  // Add field types

  wxRichTextBuffer::AddFieldType(new field(wxT("rectangle"), wxT("RECTANGLE"),
    wxRichTextFieldTypeStandard::wxRICHTEXT_FIELD_STYLE_RECTANGLE));

  wxRichTextFieldTypeStandard* s1 =
    new wxRichTextFieldTypeStandard(wxT("begin-section"), wxT("SECTION"),
      wxRichTextFieldTypeStandard::wxRICHTEXT_FIELD_STYLE_START_TAG);
  s1->SetBackgroundColour(*wxBLUE);

  wxRichTextFieldTypeStandard* s2 =
    new wxRichTextFieldTypeStandard(wxT("end-section"), wxT("SECTION"),
      wxRichTextFieldTypeStandard::wxRICHTEXT_FIELD_STYLE_END_TAG);
  s2->SetBackgroundColour(*wxBLUE);

  wxRichTextFieldTypeStandard* s3 = new wxRichTextFieldTypeStandard(wxT("bitmap"),
    wxBitmap(paste_xpm), wxRichTextFieldTypeStandard::wxRICHTEXT_FIELD_STYLE_NO_BORDER);

  wxRichTextBuffer::AddFieldType(s1);
  wxRichTextBuffer::AddFieldType(s2);
  wxRichTextBuffer::AddFieldType(s3);

  field_composte* s4 = new field_composte(wxT("composite"), wxT("This is a field value"));
  wxRichTextBuffer::AddFieldType(s4);

  // Add image handlers
#if wxUSE_LIBPNG
  wxImage::AddHandler( new wxPNGHandler );
#endif

#if wxUSE_LIBJPEG
  wxImage::AddHandler( new wxJPEGHandler );
#endif

#if wxUSE_GIF
  wxImage::AddHandler( new wxGIFHandler );
#endif

#if wxUSE_FILESYSTEM
  wxFileSystem::AddHandler( new wxMemoryFSHandler );
#endif

  // create the main application window
  wxSize size = wxGetDisplaySize();
  size.Scale(0.75, 0.75);
  frame *Frame = new frame(wxT("EveRest text editor"), wxID_ANY,
                                 wxDefaultPosition, size);

#if wxUSE_PRINTING_ARCHITECTURE
  m_printing->SetParentWindow(Frame);
#endif

  // and show it (the frames, unlike simple controls,
  // are not shown when created initially)
  Frame->Show(true);

  // success: wxApp::OnRun() will be called which will enter the main message
  // loop and the application will run. If we returned false here, the
  // application would exit immediately.
  return true;
}

//##
int app::OnExit()
{

  #if wxUSE_PRINTING_ARCHITECTURE
    delete m_printing;
  #endif

  delete m_styleSheet;
  return 0;
}

//## Paragraph styles
void app::CreateStyles()
{

  wxFont romanFont(wxFontInfo(12).Family(wxFONTFAMILY_ROMAN));
  wxFont swissFont(wxFontInfo(12).Family(wxFONTFAMILY_SWISS));

  wxRichTextParagraphStyleDefinition* normalPara =
    new wxRichTextParagraphStyleDefinition(wxT("Normal"));

  wxRichTextAttr normalAttr;
  normalAttr.SetFontFaceName(romanFont.GetFaceName());
  normalAttr.SetFontSize(12);
  // Let's set all attributes for this style
  normalAttr.SetFlags(wxTEXT_ATTR_FONT | wxTEXT_ATTR_BACKGROUND_COLOUR | wxTEXT_ATTR_TEXT_COLOUR|wxTEXT_ATTR_ALIGNMENT|wxTEXT_ATTR_LEFT_INDENT|wxTEXT_ATTR_RIGHT_INDENT|wxTEXT_ATTR_TABS|
                          wxTEXT_ATTR_PARA_SPACING_BEFORE|wxTEXT_ATTR_PARA_SPACING_AFTER|wxTEXT_ATTR_LINE_SPACING|
                          wxTEXT_ATTR_BULLET_STYLE|wxTEXT_ATTR_BULLET_NUMBER);
  normalPara->SetStyle(normalAttr);

  m_styleSheet->AddParagraphStyle(normalPara);

  wxRichTextParagraphStyleDefinition* indentedPara =
      new wxRichTextParagraphStyleDefinition(wxT("Indented"));

  wxRichTextAttr indentedAttr;
  indentedAttr.SetFontFaceName(romanFont.GetFaceName());
  indentedAttr.SetFontSize(12);
  indentedAttr.SetLeftIndent(100, 0);
  // We only want to affect indentation
  indentedAttr.SetFlags(wxTEXT_ATTR_LEFT_INDENT|wxTEXT_ATTR_RIGHT_INDENT);
  indentedPara->SetStyle(indentedAttr);

  m_styleSheet->AddParagraphStyle(indentedPara);

  wxRichTextParagraphStyleDefinition* indentedPara2 =
    new wxRichTextParagraphStyleDefinition(wxT("Red Bold Indented"));

  wxRichTextAttr indentedAttr2;
  indentedAttr2.SetFontFaceName(romanFont.GetFaceName());
  indentedAttr2.SetFontSize(12);
  indentedAttr2.SetFontWeight(wxFONTWEIGHT_BOLD);
  indentedAttr2.SetTextColour(*wxRED);
  indentedAttr2.SetFontSize(12);
  indentedAttr2.SetLeftIndent(100, 0);
  // We want to affect indentation, font and text colour
  indentedAttr2.SetFlags(wxTEXT_ATTR_LEFT_INDENT | wxTEXT_ATTR_RIGHT_INDENT |
                         wxTEXT_ATTR_FONT | wxTEXT_ATTR_TEXT_COLOUR);
  indentedPara2->SetStyle(indentedAttr2);

  m_styleSheet->AddParagraphStyle(indentedPara2);

  wxRichTextParagraphStyleDefinition* flIndentedPara =
    new wxRichTextParagraphStyleDefinition(wxT("First Line Indented"));

  wxRichTextAttr flIndentedAttr;
  flIndentedAttr.SetFontFaceName(swissFont.GetFaceName());
  flIndentedAttr.SetFontSize(12);
  flIndentedAttr.SetLeftIndent(100, -100);
  // We only want to affect indentation
  flIndentedAttr.SetFlags(wxTEXT_ATTR_LEFT_INDENT|wxTEXT_ATTR_RIGHT_INDENT);
  flIndentedPara->SetStyle(flIndentedAttr);

  m_styleSheet->AddParagraphStyle(flIndentedPara);

  // Character styles

  wxRichTextCharacterStyleDefinition* boldDef =
    new wxRichTextCharacterStyleDefinition(wxT("Bold"));

  wxRichTextAttr boldAttr;
  boldAttr.SetFontFaceName(romanFont.GetFaceName());
  boldAttr.SetFontSize(12);
  boldAttr.SetFontWeight(wxFONTWEIGHT_BOLD);
  // We only want to affect boldness
  boldAttr.SetFlags(wxTEXT_ATTR_FONT_WEIGHT);
  boldDef->SetStyle(boldAttr);

  m_styleSheet->AddCharacterStyle(boldDef);

  wxRichTextCharacterStyleDefinition* italicDef =
    new wxRichTextCharacterStyleDefinition(wxT("Italic"));

  wxRichTextAttr italicAttr;
  italicAttr.SetFontFaceName(romanFont.GetFaceName());
  italicAttr.SetFontSize(12);
  italicAttr.SetFontStyle(wxFONTSTYLE_ITALIC);
  // We only want to affect italics
  italicAttr.SetFlags(wxTEXT_ATTR_FONT_ITALIC);
  italicDef->SetStyle(italicAttr);

  m_styleSheet->AddCharacterStyle(italicDef);

  wxRichTextCharacterStyleDefinition* redDef =
    new wxRichTextCharacterStyleDefinition(wxT("Red Bold"));

  wxRichTextAttr redAttr;
  redAttr.SetFontFaceName(romanFont.GetFaceName());
  redAttr.SetFontSize(12);
  redAttr.SetFontWeight(wxFONTWEIGHT_BOLD);
  redAttr.SetTextColour(*wxRED);
  // We only want to affect colour, weight and face
  redAttr.SetFlags(wxTEXT_ATTR_FONT_FACE|wxTEXT_ATTR_FONT_WEIGHT|wxTEXT_ATTR_TEXT_COLOUR);
  redDef->SetStyle(redAttr);

  m_styleSheet->AddCharacterStyle(redDef);

  wxRichTextListStyleDefinition* bulletList =
    new wxRichTextListStyleDefinition(wxT("Bullet List 1"));

  int i;
  for (i = 0; i < 10; i++)
  {
    wxString bulletText;
    if (i == 0)
        bulletText = wxT("standard/circle");
    else if (i == 1)
        bulletText = wxT("standard/square");
    else if (i == 2)
        bulletText = wxT("standard/circle");
    else if (i == 3)
        bulletText = wxT("standard/square");
    else
        bulletText = wxT("standard/circle");

    bulletList->SetAttributes(i, (i+1)*60, 60, wxTEXT_ATTR_BULLET_STYLE_STANDARD, bulletText);
  }

  m_styleSheet->AddListStyle(bulletList);

  wxRichTextListStyleDefinition* numberedList =
    new wxRichTextListStyleDefinition(wxT("Numbered List 1"));

  for (i = 0; i < 10; i++)
  {
    long numberStyle;
    if (i == 0)
        numberStyle = wxTEXT_ATTR_BULLET_STYLE_ARABIC|wxTEXT_ATTR_BULLET_STYLE_PERIOD;
    else if (i == 1)
        numberStyle = wxTEXT_ATTR_BULLET_STYLE_LETTERS_LOWER|wxTEXT_ATTR_BULLET_STYLE_PARENTHESES;
    else if (i == 2)
        numberStyle = wxTEXT_ATTR_BULLET_STYLE_ROMAN_LOWER|wxTEXT_ATTR_BULLET_STYLE_PARENTHESES;
    else if (i == 3)
        numberStyle = wxTEXT_ATTR_BULLET_STYLE_ROMAN_UPPER|wxTEXT_ATTR_BULLET_STYLE_PARENTHESES;
    else
        numberStyle = wxTEXT_ATTR_BULLET_STYLE_ARABIC|wxTEXT_ATTR_BULLET_STYLE_PERIOD;

    numberStyle |= wxTEXT_ATTR_BULLET_STYLE_ALIGN_RIGHT;

    numberedList->SetAttributes(i, (i+1)*60, 60, numberStyle);
  }

  m_styleSheet->AddListStyle(numberedList);

  wxRichTextListStyleDefinition* outlineList =
    new wxRichTextListStyleDefinition(wxT("Outline List 1"));

  for (i = 0; i < 10; i++)
  {
    long numberStyle;
    if (i < 4)
        numberStyle = wxTEXT_ATTR_BULLET_STYLE_OUTLINE|wxTEXT_ATTR_BULLET_STYLE_PERIOD;
    else
        numberStyle = wxTEXT_ATTR_BULLET_STYLE_ARABIC|wxTEXT_ATTR_BULLET_STYLE_PERIOD;

    outlineList->SetAttributes(i, (i+1)*120, 120, numberStyle);
  }

  m_styleSheet->AddListStyle(outlineList);
}

} //namespace ev
