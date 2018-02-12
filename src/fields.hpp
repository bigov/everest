#ifndef __FIELDS_HPP__
#define __FIELDS_HPP__

#include "main.hpp"

namespace ev {

//## A custom field type
class field: public wxRichTextFieldTypeStandard
{
  public:
    field(const wxString& name, const wxString& label,
      int displayStyle = wxRICHTEXT_FIELD_STYLE_RECTANGLE)
      : wxRichTextFieldTypeStandard(name, label, displayStyle) { }

    field(const wxString& name, const wxBitmap& bitmap,
      int displayStyle = wxRICHTEXT_FIELD_STYLE_RECTANGLE)
      : wxRichTextFieldTypeStandard(name, bitmap, displayStyle) { }

    virtual bool CanEditProperties(wxRichTextField* WXUNUSED(obj))
      const wxOVERRIDE { return true; }

    virtual bool EditProperties(wxRichTextField*, wxWindow*, wxRichTextBuffer*)
      wxOVERRIDE;

    virtual wxString GetPropertiesMenuLabel(wxRichTextField* WXUNUSED(obj))
      const wxOVERRIDE { return GetLabel(); }
};

//## A custom composite field type
class field_composte: public field
{
  public:
    field_composte(const wxString& name, const wxString& label):
      field(name, label, wxRICHTEXT_FIELD_STYLE_COMPOSITE) { }

    virtual bool UpdateField(wxRichTextBuffer*, wxRichTextField*) wxOVERRIDE;
};

} //ev

#endif
