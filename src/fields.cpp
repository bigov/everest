#include "fields.hpp"

namespace ev {

//##
bool field::EditProperties(wxRichTextField* WXUNUSED(obj),
  wxWindow* WXUNUSED(parent), wxRichTextBuffer* WXUNUSED(buffer))
{
  wxString label = GetLabel();
  wxMessageBox(wxString::Format(wxT("Editing %s"), label.c_str()));
  return true;
}

//##
bool field_composte::UpdateField(wxRichTextBuffer* buffer,
  wxRichTextField* obj)
{
  if (buffer)
  {
    wxRichTextAttr attr(buffer->GetAttributes());
    attr.GetTextBoxAttr().Reset();
    attr.SetParagraphSpacingAfter(0);
    attr.SetLineSpacing(10);
    obj->SetAttributes(attr);
  }
  obj->DeleteChildren();
  wxRichTextParagraph* para = new wxRichTextParagraph;
  wxRichTextPlainText* text = new wxRichTextPlainText(GetLabel());
  para->AppendChild(text);
  obj->AppendChild(para);
  return true;
}

} //ev
