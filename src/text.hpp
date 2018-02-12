#ifndef __TEXT_HPP__
#define __TEXT_HPP__

#include "main.hpp"

namespace ev {

//## Define a new application type, derived from wxApp
class text_ctrl: public wxRichTextCtrl
{
  public:
    text_ctrl( wxWindow* parent, wxWindowID id = -1,
      const wxString& value = wxEmptyString,
      const wxPoint& pos = wxDefaultPosition,
      const wxSize& size = wxDefaultSize,
      long style = wxRE_MULTILINE,
      const wxValidator& validator = wxDefaultValidator,
      const wxString& name = wxTextCtrlNameStr):
      wxRichTextCtrl(parent, id, value, pos, size, style, validator, name)
    {
      m_lockId = 0;
      m_locked = false;
    }

    void SetLockId(long id) { m_lockId = id; }
    long GetLockId() const { return m_lockId; }

    void BeginLock() { m_lockId ++; m_locked = true; }
    void EndLock() { m_locked = false; }
    bool IsLocked() const { return m_locked; }

    static void SetEnhancedDrawingHandler();

    /// Prepares the content just before insertion (or after buffer reset).
    /// Called by the same function in wxRichTextBuffer. Currently is only
    /// called if undo mode is on.
    virtual void PrepareContent(wxRichTextParagraphLayoutBox& container) wxOVERRIDE;

    /// Can we delete this range? Sends an event to the control.
    virtual bool CanDeleteRange(wxRichTextParagraphLayoutBox& container,
                                const wxRichTextRange& range) const wxOVERRIDE;

    /// Can we insert content at this position? Sends an event to the control.
    virtual bool CanInsertContent(wxRichTextParagraphLayoutBox& container,
                                  long pos) const wxOVERRIDE;

    /// Finds a table, either selected or near the cursor
    wxRichTextTable* FindTable() const;

    /// Helper for FindTable()
    wxRichTextObject* FindCurrentPosition() const;

    long m_lockId;
    bool m_locked;
};

//##
class text_draw: public wxRichTextDrawingHandler
{
  public:
    text_draw(void);

    /// Returns @true if this object has virtual attributes that we can provide.
    virtual bool HasVirtualAttributes(wxRichTextObject* obj) const wxOVERRIDE;

    /// Provides virtual attributes that we can provide.
    virtual bool GetVirtualAttributes(wxRichTextAttr& attr,
      wxRichTextObject* obj) const wxOVERRIDE;

    /// Gets the count for mixed virtual attributes for individual positions
    /// within the object. For example, individual characters within a text
    /// object may require special highlighting.
    virtual int GetVirtualSubobjectAttributesCount(
      wxRichTextObject* WXUNUSED(obj)) const wxOVERRIDE { return 0; }

    /// Gets the mixed virtual attributes for individual positions within the
    /// object. For example, individual characters within a text object may
    /// require special highlighting.
    /// Returns the number of virtual attributes found.
    virtual int GetVirtualSubobjectAttributes(wxRichTextObject* WXUNUSED(obj),
      wxArrayInt& WXUNUSED(positions), wxRichTextAttrArray& WXUNUSED(attributes))
      const wxOVERRIDE  { return 0; }

    /// Do we have virtual text for this object? Virtual text allows an
    /// application to replace characters in an object for editing and display
    /// purposes, for example for highlighting special characters.
    virtual bool HasVirtualText(const wxRichTextPlainText* WXUNUSED(obj))
      const wxOVERRIDE { return false; }

    /// Gets the virtual text for this object.
    virtual bool GetVirtualText(const wxRichTextPlainText* WXUNUSED(obj),
      wxString& WXUNUSED(text)) const wxOVERRIDE { return false; }

    wxColour m_lockBackgroundColour;
};

} //ev

#endif
