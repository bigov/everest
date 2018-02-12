#include "text.hpp"

namespace ev {

//##
text_draw::text_draw(void)
{
  SetName(wxT("enhanceddrawing"));
  m_lockBackgroundColour = wxColour(220, 220, 220);
  return;
}

//##
bool text_draw::HasVirtualAttributes(wxRichTextObject* obj) const
{
  return obj->GetProperties().HasProperty(wxT("Lock"));
}

//##
bool text_draw::GetVirtualAttributes(wxRichTextAttr& attr,
                                     wxRichTextObject* obj) const
{
  if (obj->GetProperties().HasProperty(wxT("Lock")))
  {
    attr.SetBackgroundColour(m_lockBackgroundColour);
    return true;
  }
  return false;
}

//##
void text_ctrl::PrepareContent(wxRichTextParagraphLayoutBox& container)
{
  if (IsLocked())
  {
    // Lock all content that's about to be added to the control
    wxRichTextObjectList::compatibility_iterator node =
      container.GetChildren().GetFirst();

    while (node)
    {
      wxRichTextParagraph* para = wxDynamicCast(node->GetData(), wxRichTextParagraph);
      if (para)
      {
        wxRichTextObjectList::compatibility_iterator childNode = para->GetChildren().GetFirst();
        while (childNode)
        {
          wxRichTextObject* obj = childNode->GetData();
          obj->GetProperties().SetProperty(wxT("Lock"), m_lockId);
          childNode = childNode->GetNext();
        }
      }
      node = node->GetNext();
    }
  }
}

//##
bool text_ctrl::CanDeleteRange(wxRichTextParagraphLayoutBox& container, const wxRichTextRange& range) const
{
  long i;
  for (i = range.GetStart(); i < range.GetEnd(); i++)
  {
    wxRichTextObject* obj = container.GetLeafObjectAtPosition(i);
    if (obj && obj->GetProperties().HasProperty(wxT("Lock")))
    {
      return false;
    }
  }
  return true;
}

//##
bool text_ctrl::CanInsertContent(wxRichTextParagraphLayoutBox& container, long pos) const
{
  wxRichTextObject* child1 = container.GetLeafObjectAtPosition(pos);
  wxRichTextObject* child2 = container.GetLeafObjectAtPosition(pos-1);

  long lock1 = -1, lock2 = -1;

  if (child1 && child1->GetProperties().HasProperty(wxT("Lock")))
    lock1 = child1->GetProperties().GetPropertyLong(wxT("Lock"));
  if (child2 && child2->GetProperties().HasProperty(wxT("Lock")))
    lock2 = child2->GetProperties().GetPropertyLong(wxT("Lock"));

  if (lock1 != -1 && lock1 == lock2)
    return false;

  // Don't allow insertion before a locked object if it's at the beginning of the buffer.
  if (pos == 0 && lock1 != -1)
    return false;

  return true;
}

//##
void text_ctrl::SetEnhancedDrawingHandler()
{
    wxRichTextBuffer::AddDrawingHandler(new text_draw);
}

//##
wxRichTextObject* text_ctrl::FindCurrentPosition() const
{
  long position = -1;

  if (HasSelection())  // First see if there's a selection
  {
    wxRichTextRange range = GetSelectionRange();
    if (range.ToInternal().GetLength() == 1)
    {
      position = range.GetStart();
    }
  }

  if (position == -1)  // Failing that, near cursor
  {
    position = GetAdjustedCaretPosition(GetCaretPosition());
  }

  wxRichTextObject* obj = GetFocusObject()->GetLeafObjectAtPosition(position);

  return obj;
}

//##
wxRichTextTable* text_ctrl::FindTable() const
{
  wxRichTextObject* obj = FindCurrentPosition();

  // It could be a table or a cell (or neither)
  wxRichTextTable* table = wxDynamicCast(obj, wxRichTextTable);

  if (table)
  {
    return table;
  }

  while (obj)
  {
    obj = obj->GetParent();
    wxRichTextTable* table = wxDynamicCast(obj, wxRichTextTable);
    if (table)
    {
      return table;
    }
  }

  return NULL;
}

} //ev
